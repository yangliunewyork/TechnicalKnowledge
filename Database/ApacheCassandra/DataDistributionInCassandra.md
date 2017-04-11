Cassandra's peer-to-peer architecture and scalability characteristics are directly tied to its data placement scheme. Cassandra employs a __distributed hash table__ data structure that allows for data to be stored and retrieved by key quickly and efficiently. __Consistent hashing__ is at the core of this strategy, as it enables all nodes to understand where data exists in the cluster without complicated coordination mechanisms.

## Distributed hash tables
When we take the basic idea of a hash table and partition it out to multiple nodes, this is called a __distributed hash table (DHT)__. Each node in the DHT must share the same hash function, such that hash results on one node match all the others.

In order to determine the location of a given piece of data in the cluster, we need some means of associating an object with the node that owns it. We could ask every node in the cluster, but this would be problematic for at least two important reasons. First, this strategy doesn't scale well, as the overhead would grow with the number of nodes. Second, every node in the cluster would have to be available to answer requests in order to definitively state that a given item does not exist. A shared index could address this, but the result would be additional complexity and another point of failure.

Therefore, a key objective of the hash function in a DHT is to map a key to the node that owns it, such that a request can be made to the correct node. But the simple hash function discussed previously is no longer appropriate for mapping data to a node. The simple hash is problematic in a distributed system, because n translates to the number of nodes in the cluster and we know that n changes as nodes are added or removed.

## Consistent hashing

The solution is consistent hashing. Introduced as a term in 1997, consistent hashing was originally used as a means of routing requests among a large number of web servers. It's easy to see how the web could benefit from a hash mechanism that allows any node in the network to efficiently determine the location of an object, in spite of the constant shifting of nodes in and out of the network. This is the fundamental objective of consistent hashing.

##### How it works
With consistent hashing, the buckets are arranged in a ring with a predefined range. The exact range depends on the partitioner being used. Keys are then hashed to produce a value that lies somewhere along the ring. Nodes are assigned a range.

Therefore, for a five-node cluster, a ring with evenly distributed token ranges would look like this, presuming the default Murmur3Partitioner is used:

![alt](http://apprize.info/php/cassandra_4/cassandra_4.files/image011.jpg)

This diagram represents data ranges (the letters) and the nodes (the numbers) that own those ranges.

When Cassandra receives a key for either a read or a write, the same hash function is applied to the key to determine where it lies in the range. Since all nodes in the cluster are aware of the other nodes' ranges, any node can handle a request for any other node's range. The node receiving the request is called the __coordinator__, and any node can act in this role. If a key does not belong to the coordinator's range, it forwards the request to replicas in the correct range.

## Token assignment
In Cassandra terminology, the start of the hash range is called a __token__.Cassandra determines where to place data by using the tokens assigned to each node. Nodes learn about these token assignments via gossip. Additional replicas are then placed based on the configured replication strategy and snitch. 

##### Manually assigned tokens
Manual token assignment introduces a number of potential issues:

* Adding and removing nodes: When the size of the ring changes, all tokens must be recomputed and configuration files changed. This causes a significant amount of administrative overhead for a large cluster.
* Node rebuilds: In the case of a node rebuild, only a few nodes can participate in bootstrapping the replacement, leading to significant service degradation. We'll discuss this in detail later in this chapter.
* Hot spots: In some cases the relatively large range assigned to each node can cause hot spots if data is not evenly distributed.
* Heterogeneous clusters: With every node assigned a single token, the expectation is that all nodes will hold the same amount of data. Attempting to subdivide ranges to deal with nodes of varying sizes is a difficult and error-prone task.

Because of these issues, the use of vnodes is highly recommended for any new installation. For existing installations, migrating to vnodes will improve the performance, reliability, and administrative requirements of your cluster, especially during topology changes and failure scenarios.

##### Vnodes
The concept behind vnodes is straightforward. Instead of a single token assigned to each node, it is now possible to specify the number of tokens using the ```num_tokens``` configuration property in ```cassandra.yaml```. The default value is 256, which is sufficient for most use cases. A higher number generally results in better data distribution, while a lower number can lessen the time it takes to perform repairs and bootstrap operations. If you decide to use the default, making use of incremental repairs will help to offset this negative side effect.

![alt](http://www.datastax.com/wp-content/uploads/2012/12/VNodesNoShuffle.png)

![alt](http://www.datastax.com/wp-content/uploads/2012/12/VNodesShuffled.png)

Remember that the letters represent ranges of data. You'll notice there are more ranges than nodes after enabling vnodes, and each node now owns multiple ranges.

#### How vnodes improve availability
While technically the cluster remains available during topology changes and node rebuilds, the level of degraded service has the potential to impact availability if the system remains under significant load. Vnodes offer a simple solution to the problems associated with manually assigned tokens.Let's examine the reasons why this is the case.

##### Adding and removing nodes
There are many reasons to change the size of a cluster. Perhaps you're increasing capacity for an anticipated growth in data or transaction volume, or maybe you're adding a data center for increased availability.

Considering that the objective is to handle greater load or provide additional redundancy, any significant performance degradation while adding or bootstrapping a new node is unacceptable as it counteracts these goals. Often in modern high-scale applications, slow is the same as unavailable. Equally important is to insure that new nodes receive a balanced share of the data.

Vnodes improve the bootstrapping process substantially:

* More nodes can participate in data transfer: Since the token ranges are more dispersed throughout the cluster, adding a new node involves ranges from a greater number of the existing nodes. As a result, machines involved in the transfer end up under less load than without vnodes, thus increasing the availability of those ranges.
* Token assignment is automatic: Cassandra handles the allocation of tokens, so there's no need to manually recalculate and reassign a new token for every node in the cluster. As a result, the ring becomes naturally balanced on its own.

##### Node rebuild
Rebuilding a node is a relatively common operation in a large cluster, as nodes will fail for a variety of reasons. Cassandra provides a mechanism for automatically rebuilding a failed node using replicated data.

When each node owns only a single token, that node's entire dataset is replicated to a number of nodes equal to the replication factor minus one. For example, with a replication factor of three, all the data on a given node will be replicated to two other nodes. However, Cassandra will only use one replica in the rebuild operation.

So in this case, a rebuild operation involves three nodes, placing a high load on all three. Imagine that we have a six-node cluster, and Node 2 has failed, requiring a rebuild. In the following diagram, note that each node only contains replicas for three tokens, preventing two of the nodes from participating in the rebuild:

![alt](http://apprize.info/php/cassandra_4/cassandra_4.files/image013.jpg)

We can assume that reads and writes are continuing during this process. With one node down and three working hard to rebuild it, we now have only two out of six nodes operating at full capacity! Even worse, token ranges A and B reside entirely on nodes that are being taxed by this process, which can result in overburdening the entire cluster due to slow response times for those operations.

Vnodes provide significant benefits over manual token management for the rebuild process, as they distribute the load over many more nodes. This is the same concept as the benefit gained during the bootstrapping process. Since each node contains replicas for a larger (and random) variety of the available tokens, Cassandra can use these replicas in the rebuild process. Consider the following illustration of the same rebuild using vnodes:

![alt](http://apprize.info/php/cassandra_4/cassandra_4.files/image014.jpg)

From the diagram you can see that rebuilding Node 2 now involves the entire cluster, thus distributing the workload more evenly. This means each individual node is doing less work than without vnodes, resulting in greater operational stability.

##### Heterogeneous nodes
with nodes that are all identical, at some point older machines will need to be replaced with newer ones. This can create issues when manually assigning tokens, as it can become difficult to effectively choose the right tokens to produce a balanced result. This is especially problematic when adding or removing nodes, as it would become necessary to recompute the tokens to achieve a proper balance.

Vnodes ease this effort by allowing you to specify a number of tokens, instead of having to determine specific ranges. It is much easier to choose a proportionally larger number for newer, more powerful nodes than it is to determine proper token ranges. For example, if you have an existing cluster with 64 vnodes on each node, and you add nodes with twice the resources, you would want to increase the vnodes to 128 to compensate.

## Partitioners
You may recall from the earlier discussion of distributed hash tables that keys are mapped to nodes via an implementation-specific hash function. In Cassandra's architecture, this function is determined by the partitioner you choose. This is a cluster-wide setting specified in ```cassandra.yaml```. 

* Murmur3Partitioner
* RandomPartitioner
* ByteOrderedPartitioner

##### Hotspots

![alt](http://apprize.info/php/cassandra_4/cassandra_4.files/image016.jpg)

The diagram clearly shows that the resulting distribution produces hotspots in Node 1 and Node 4, while Node 5 is significantly underutilized. One perhaps less obvious side effect of this imbalance is the impact on reads and writes. If we presume that both reads and writes follow the same distribution as the data itself (which is a logical assumption in this specific case), the heavier data nodes will also be required to handle more operations than the lighter data nodes.

