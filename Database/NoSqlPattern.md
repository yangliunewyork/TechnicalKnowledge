## Source

* http://horicky.blogspot.com/2009/11/nosql-patterns.html

## Introduction
Over the last couple years, we see an emerging data storage mechanism for storing large scale of data. These storage solution differs quite significantly with the RDBMS model and is also known as the NOSQL. Some of the key players include ...

* GoogleBigTable, HBase, Hypertable
* AmazonDynamo, Voldemort, Cassendra, Riak
* Redis
* CouchDB, MongoDB

These solutions has a number of characteristics in common
* Key value store
* Run on large number of commodity machines
* Data are partitioned and replicated among these machines
* Relax the data consistency requirement. (because the CAP theorem proves that you cannot get Consistency, Availability and Partitioning at the the same time)

The aim of this blog is to extract the underlying technologies that these solutions have in common, and get a deeper understanding on the implication to your application's design. I am not intending to compare the features of these solutions, nor to suggest which one to use.

## API model

The underlying data model can be considered as a large Hashtable (key/value store).

The basic form of API access is

* get(key) -- Extract the value given a key
* put(key, value) -- Create or Update the value given its key
* delete(key) -- Remove the key and its associated value

More advance form of API allows to execute user defined function in the server environment

* execute(key, operation, parameters) -- Invoke an operation to the value (given its key) which is a special data structure (e.g. List, Set, Map .... etc).
* mapreduce(keyList, mapFunc, reduceFunc) -- Invoke a map/reduce function across a key range.

## Machines layout

The underlying infratructure is composed of large number (hundreds or thousands) of cheap, commoditized, unreliable machines connected through a network. We call each machine a physical node (PN). Each PN has the same set of software configuration but may have varying hardware capacity in terms of CPU, memory and disk storage. Within each PN, there will be a variable number of virtual node (VN) running according to the available hardware capacity of the PN.

## Data partitioning (Consistent Hashing)
Since the overall hashtable is distributed across many VNs, we need a way to map each key to the corresponding VN.

One way is to use
> partition = key mod (total_VNs)

The disadvantage of this scheme is when we alter the number of VNs, then the ownership of existing keys has changed dramatically, which requires full data redistribution. Most large scale store use a "consistent hashing" technique to minimize the amount of ownership changes.

In the consistent hashing scheme, the key space is finite and lie on the circumference of a ring. The virtual node id is also allocated from the same key space. For any key, its owner node is defined as the first encountered virtual node if walking clockwise from that key. If the owner node crashes, all the key it owns will be adopted by its clockwise neighbor. Therefore, key redistribution happens only within the neighbor of the crashed node, all other nodes retains the same set of keys.

## Data replication
To provide high reiability from individually unreliable resource, we need to replicate the data partitions.

Replication not only improves the overall reliability of data, it also helps performance by spreading the workload across multiple replicas.

While read-only request can be dispatched to any replicas, update request is more challenging because we need to carefully co-ordinate the update which happens in these replicas.

## Membership Changes

Notice that virtual nodes can join and leave the network at any time without impacting the operation of the ring.

When a new node joins the network

1. The joining node announce its presence and its id to some well known VNs or just broadcast)
2. All the neighbors (left and right side) will adjust the change of key ownership as well as the change of replica memberships. This is typically done synchronously.
3. The joining node starts to bulk copy data from its neighbor in parallel asynchronously.
4. The membership change is asynchronously propagate to the other nodes.

Notice that other nodes may not have their membership view updated yet so they may still forward the request to the old nodes. But since these old nodes (which is the neighbor of the new joined node) has been updated (in step 2), so they will forward the request to the new joined node.

On the other hand, the new joined node may still in the process of downloading the data and not ready to serve yet. We use the vector clock (described below) to determine whether the new joined node is ready to serve the request and if not, the client can contact another replica.

