Cassandra's peer-to-peer architecture and scalability characteristics are directly tied to its data placement scheme. Cassandra employs a __distributed hash table__ data structure that allows for data to be stored and retrieved by key quickly and efficiently. __Consistent hashing__ is at the core of this strategy, as it enables all nodes to understand where data exists in the cluster without complicated coordination mechanisms.

## Distributed hash tables
When we take the basic idea of a hash table and partition it out to multiple nodes, this is called a __distributed hash table (DHT)__. Each node in the DHT must share the same hash function, such that hash results on one node match all the others.

In order to determine the location of a given piece of data in the cluster, we need some means of associating an object with the node that owns it. We could ask every node in the cluster, but this would be problematic for at least two important reasons. First, this strategy doesn't scale well, as the overhead would grow with the number of nodes. Second, every node in the cluster would have to be available to answer requests in order to definitively state that a given item does not exist. A shared index could address this, but the result would be additional complexity and another point of failure.

Therefore, a key objective of the hash function in a DHT is to map a key to the node that owns it, such that a request can be made to the correct node. But the simple hash function discussed previously is no longer appropriate for mapping data to a node. The simple hash is problematic in a distributed system, because n translates to the number of nodes in the cluster and we know that n changes as nodes are added or removed.

## Consistent hashing


