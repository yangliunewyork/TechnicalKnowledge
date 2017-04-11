## Introduction
What does it mean for a data store to be highly available? When designing or configuring a system for high availability, architects typically hope to offer some guarantee of uptime even in the presence of failure.The exact definition of high availability depends on the requirements of the application. This concept has gained increasing significance in the context of web applications, real-time systems, and other use cases that cannot afford any downtime. Database systems must not only guarantee system uptime, the ability to fulfill requests, but also ensure that the data itself remains available.

Traditionally, it has been difficult to make databases highly available, especially the relational database systems that have dominated the scene for the last couple of decades. These systems are most often designed to run on a single large machine, making it challenging to scale out to multiple machines.

## Introducing the ACID properties
One of the most significant obstacles that prevents traditional databases from achieving high availability is that they attempt to strongly guarantee the ACID properties:

* __Atomicity__ : This guarantees that database updates associated with a transaction occur in an all-or-nothing manner. If some part of the transaction fails, the state of the database remains unchanged.
* __Consistency__ : This assures that the integrity of data will be preserved across all instances of that data. Changes to a value in one location will definitely be reflected in all other locations.
* __Isolation__ : This attempts to ensure that concurrent transactions that manipulate the same data do so in a controlled manner, essentially isolating in-process changes from other clients. Most traditional relational database systems provide various levels of isolation with different guarantees at each level.
* __Durability__ : This ensures that all writes are preserved in nonvolatile storage, most commonly on disk.

Database designers most commonly achieve these properties via write masters, locks, elaborate storage area networks, and the like-all of which tend to sacrifice availability. As a result, achieving some semblance of high availability frequently involves bolt-on components, log shipping, leader election, sharding, and other such strategies that attempt to preserve the original design.

## Monolithic simplicity
The simplest design approach to guarantee ACID properties is to implement a monolithic architecture where all functions reside on a single machine. Since no coordination among nodes is required, the task of enforcing all the system rules is relatively straightforward.

Increasing availability in such architectures typically involves hardware layer improvements, such as RAID arrays, multiple network interfaces, and hot-swappable drives. However, the fact remains that even the most robust database server acts as a single point of failure. This means that if the server fails, the application becomes unavailable. This architecture can be illustrated with the following diagram:

![alt](https://image.slidesharecdn.com/arc309-151009010602-lva1-app6891/95/arc309-getting-to-microservices-cloud-architecture-patterns-47-638.jpg)

A common means of increasing capacity to handle requests on a monolithic architecture is to move the storage layer to a shared component such as a __storage area network (SAN)__ or __network attached storage (NAS)__. Such devices are usually quite robust, with large numbers of disks and high-speed network interfaces. This approach is shown in a modification of the previous diagram, which depicts two database servers using a single NAS.

![alt](http://sprout.ics.uci.edu/past_projects/san/img1.gif)

You'll notice that while this architecture increases the overall request-handling capacity of the system, it simply moves the single failure point from the database server to the storage layer. As a result, there is no real improvement from an availability perspective.

## Scaling consistency – the master-slave model
As distributed systems have become more commonplace, the need for higher capacity distributed databases has grown. Many distributed databases still attempt to maintain ACID guarantees (or in some cases only the consistency aspect, which is the most difficult in a distributed environment), leading to the master-slave architecture.

In this approach, there might be many servers handling requests, but only one server can actually perform writes so as to maintain data in a consistent state. This avoids the scenario where the same data can be modified via concurrent mutation requests to different nodes. The following diagram shows the most basic scenario:

![alt](https://severalnines.com/sites/default/files/resources/tutorials/mysql-replication-tutorial/image44.png)

However, we still have not solved the availability problem, as a failure of the write master would lead to application downtime. It also means that writes do not scale well, since they are all directed to a single machine.

#### Using sharding to scale writes
A variation on the master-slave approach that enables higher write volumes is a technique called sharding, in which the data is partitioned into groups of keys, such that one or more masters can own a known set of keys. For example, a database of user profiles can be partitioned by the last name, such that A-M belongs to one cluster and N-Z belongs to another, as follows:

![alt](https://image.slidesharecdn.com/plsc2014mysqlfabric-140403180103-phpapp01/95/sharding-and-scaleout-using-mysql-fabric-33-638.jpg)

An astute observer will notice that both master-slave and sharding introduce failure points on the master nodes, and in fact the sharding approach introduces multiple points of failure-one for each master! Additionally, the knowledge of where requests for certain keys go rests with the application layer, and adding shards requires manual shuffling of data to accommodate the modified key ranges.

Some systems employ shard managers as a layer of abstraction between the application and the physical shards. This has the effect of removing the requirement that the application must have knowledge of the partition map. However, it does not obviate the need for shuffling data as the cluster grows.

#### Handling the death of the leader
A common means of increasing availability in the event of a failure on a master node is to employ a master failover protocol. The particular semantics of the protocol vary among implementations, but the general principle is that a new master is appointed when the previous one fails. Not all failover algorithms are equal; however, in general, this feature increases availability in a master-slave system.

Even a master-slave database that employs leader election suffers from a number of undesirable traits:

* Applications must understand the database topology
* Data partitions must be carefully planned
* Writes are difficult to scale
* A failover dramatically increases the complexity of the system in general, and especially so for multisite databases
* Adding capacity requires reshuffling data with a potential for downtime

## Breaking with tradition – Cassandra's alternative
The reality is that not every transaction in every application requires full ACID guarantees, and ACID properties themselves can be viewed as more of a continuum where a given transaction might require different degrees of each property.

Cassandra's approach to availability takes this continuum into account. In contrast to its relational predecessors-and even most of its NoSQL contemporaries-its original architects considered availability as a key design objective, with the intent to achieve the elusive goal of 100 percent uptime. Cassandra provides numerous knobs that give the user highly granular control of the ACID properties, all with different trade-offs.

#### Cassandra's peer-to-peer approach
Unlike either monolithic or master-slave designs, Cassandra makes use of an entirely peer- to-peer architecture. All nodes in a Cassandra cluster can accept reads and writes, no matter where the data being written or requested actually belongs in the cluster. Internode communication takes place by means of a gossip protocol, which allows all nodes to quickly receive updates without the need for a master coordinator.

This is a powerful design, as it implies that the system itself is both inherently available and massively scalable. Consider the following diagram:

![alt](https://www.safaribooksonline.com/library/view/cassandra-high-availability/9781783989126/graphics/9126OS_01_05.jpg)

Note that in contrast to the monolithic and master-slave architectures, there are no special nodes. In fact, all nodes are essentially identical and as a result Cassandra has no single point of failure, and therefore no need for complex sharding or leader election. But how does Cassandra avoid sharding?

#### Hashing to the rescue
Cassandra is able to achieve both availability and scalability using a data structure that allows any node in the system to easily determine the location of a particular key in the cluster. This is accomplished by using a distributed hash table (DHT) design based on the Amazon Dynamo architecture.

As we saw in the previous diagram, Cassandra's topology is arranged in a ring, where each node owns a particular range of data. Keys are assigned to a specific node using a process called consistent hashing, which allows nodes to be added or removed without having to rehash every key based on the new range.

The node that owns a given key is determined by the chosen partitioner. Cassandra ships with several partitioner implementations, or developers can define their own by implementing a Java interface.

### Replication across the cluster
One of the most important aspects of a distributed data store is the manner in which it handles replication of data across the cluster. If each partition were only stored on a single node, the system would effectively possess many single points of failure, and a failure of any node could result in catastrophic data loss. Such systems must therefore be able to replicate data across multiple nodes, making the occurrence of such loss less likely.

Cassandra has a sophisticated replication system, offering rack and data center awareness. This means it can be configured to place replicas in such a manner so as to maintain availability even during otherwise catastrophic events such as switch failures, network partitions, or data center outages. Cassandra also includes a mechanism that maintains the replication factor during node failures.

##### Replication across data centers
Perhaps the most unique feature Cassandra provides to achieve high availability is its multiple data center replication system. This system can be easily configured to replicate data across either physical or virtual data centers. This facilitates geographically dispersed data center placement without complex schemes to keep data in sync. It also allows you to create separate data centers for online transactions and heavy analysis workloads, while allowing data written in one data center to be immediately reflected in others.

### The consistency continuum
Closely related to replication is the idea of consistency, the C in ACID that attempts to keep replicas in sync. Cassandra is often referred to as an eventually consistent system, a term that can cause fear and trembling for those who have spent many years relying on the strong consistency characteristics of their favorite relational databases. However, as previously discussed, consistency should be thought of as a continuum, not as an absolute.

With this in mind, __Cassandra can be more accurately described as having tunable consistency__, where the precise degree of consistency guarantee can be specified on a per-statement level. This gives the application architect ultimate control over the trade-offs between consistency, availability, and performance at the call level, rather than forcing a one-size-fits-all strategy onto every use case.

##### The CAP theorem
Any discussion of consistency would be incomplete without at least reviewing the CAP theorem. The CAP acronym refers to three desirable properties in a replicated system:

* Consistency: This means that the data should appear identical across all nodes in the cluster
* Availability: This means that the system should always be available to receive requests
* Partition tolerance: This means that the system should continue to function in the event of a partial failure

In 2000, computer scientist Eric Brewer from the University of California, Berkeley, posited that a replicated service can choose only two of the three properties for any given operation.

The CAP theorem has been widely misappropriated to suggest that entire systems must choose only two of the properties, which has led many to characterize databases as either AP or CP. In fact, most systems do not fit cleanly into either category, and Cassandra is no different.

> ".. all three properties are more continuous than binary. Availability is obviously continuous from 0 to 100 percent, but there are also many levels of consistency, and even partitions have nuances, including disagreement within the system about whether a partition exists”

In that same article, Brewer also pointed out that the definition of consistency in ACID terms differs from the CAP definition. In ACID, consistency refers to the guarantee that all database rules will be followed (unique constraints, foreign key constraints, and the like). The consistency in CAP, on the other hand, as clarified by Brewer, refers only to single-copy consistency, a strict subset of ACID consistency.

The bottom line is that it's important to bear this continuum in mind when designing a system based on Cassandra.

