
## Shared nothing architecture
A shared nothing architecture (SN) is a distributed computing architecture in which each node is independent and self-sufficient, and there is no single point of contention across the system. More specifically, none of the nodes share memory or disk storage. People typically contrast SN with systems that keep a large amount of centrally-stored state information, whether in a database, an application server, or any other similar single point of contention.

The advantages of SN architecture versus a central entity that controls the network (a controller-based architecture) include eliminating any single point of failure, allowing self-healing capabilities and providing an advantage with offering non-disruptive upgrade.

## Applications
Shared nothing is popular for web development because of its scalability. As Google has demonstrated, a pure SN system can scale almost infinitely simply by adding nodes in the form of inexpensive computers, since there is no single bottleneck to slow the system down.[5] Google calls this sharding. A SN system typically partitions its data among many nodes on different databases (assigning different computers to deal with different users or queries), or may require every node to maintain its own copy of the application's data, using some kind of coordination protocol. This is often referred to as database sharding.

There is some doubt about whether a web application with many independent web nodes but a single, shared database (clustered or otherwise) should be counted as SN. One of the approaches to achieve SN architecture for stateful applications (which typically maintain state in a centralized database) is the use of a data grid, also known as distributed caching. This still leaves the centralized database as a single point of failure.

Shared nothing architectures have become prevalent in the data warehousing space. There is much debate as to whether the shared nothing approach is superior to shared Disk with sound arguments presented by both camps. Shared nothing architectures certainly take longer to respond to queries that involve joins over large data sets from different partitions (machines). However, the potential for scaling is huge.

## What is shared?

While there is no single point of contention within the software/hardware components of SN systems, information from disparate nodes may still need to be reintegrated at some point. Such points occur wherever an information system that is outside the SN architecture queries information from disparate nodes within the SN architecture for a single purpose. Examples of such external nodes might be:

1. persons (minds) who look at two SN nodes and decide that they hold or process data about the same thing (simply recognising that two nodes belong to the same SN system would be sufficient)
2. any software/hardware system that is written to query different nodes within the SN architecture
