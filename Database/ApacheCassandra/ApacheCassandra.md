## Apache Cassandra
Apache Cassandra is a free and __open-source distributed NoSQL database management system__ designed to handle large amounts of data across many commodity servers, providing __high availability__ with no __single point of failure__. Cassandra offers robust support for clusters spanning multiple datacenters, with asynchronous masterless replication allowing low latency operations for all clients.

Cassandra also places a high value on performance. In 2012, University of Toronto researchers studying NoSQL systems concluded that "In terms of scalability, there is a clear winner throughout our experiments. Cassandra achieves the highest throughput for the maximum number of nodes in all experiments" although "this comes at the price of high write and read latencies."

## History
Avinash Lakshman (one of the authors of Amazon's Dynamo) and Prashant Malik initially developed Cassandra at Facebook to power the Facebook inbox search feature. Facebook released Cassandra as an open-source project on Google code in July 2008.

## Main features

##### Decentralized
Every node in the cluster has the same role. There is no single point of failure. Data is distributed across the cluster (so each node contains different data), but there is no master as every node can service any request.

##### Supports replication and multi data center replication
Replication strategies are configurable. Cassandra is designed as a distributed system, for deployment of large numbers of nodes across multiple data centers. Key features of Cassandra’s distributed architecture are specifically tailored for multiple-data center deployment, for redundancy, for failover and disaster recovery.

##### Scalability
Read and write throughput both increase linearly as new machines are added, with no downtime or interruption to applications.

##### Fault-tolerant
Data is automatically replicated to multiple nodes for fault-tolerance. Replication across multiple data centers is supported. Failed nodes can be replaced with no downtime.

##### Tunable consistency
Writes and reads offer a tunable level of consistency, all the way from "writes never fail" to "block for all replicas to be readable", with the quorum level in the middle.

##### MapReduce support
Cassandra has Hadoop integration, with MapReduce support. There is support also for Apache Pig and Apache Hive.

##### Query language
Cassandra introduced the Cassandra Query Language (CQL). CQL is a simple interface for accessing Cassandra, as an alternative to the traditional Structured Query Language (SQL). CQL adds an abstraction layer that hides implementation details of this structure and provides native syntaxes for collections and other common encodings.[20] Language drivers are available for Java (JDBC), Python (DBAPI2), Node.JS (Helenus), Go (gocql) and C++.

## Known issues
Cassandra is not row level consistent, meaning that inserts and updates into the table that affect the same row that are processed at approximately the same time may affect the non-key columns in inconsistent ways... one update may affect one column while another affects the other, resulting in sets of values within the row that were never specified or intended.

## Data model
Cassandra is essentially a hybrid between a key-value and a column-oriented (or tabular) database management system. Its data model is a partitioned row store with tunable consistency.[18] Rows are organized into tables; the first component of a table's primary key is the partition key; within a partition, rows are clustered by the remaining columns of the key.[24] Other columns may be indexed separately from the primary key.[25]

Tables may be created, dropped, and altered at run-time without blocking updates and queries.

Cassandra cannot do joins or subqueries. Rather, Cassandra emphasizes denormalization through features like collections.[27]
A column family (called "table" since CQL 3) resembles a table in an RDBMS. Column families contain rows and columns. Each row is uniquely identified by a row key. Each row has multiple columns, each of which has a name, value, and a timestamp. Unlike a table in an RDBMS, different rows in the same column family do not have to share the same set of columns, and a column may be added to one or multiple rows at any time.

Each key in Cassandra corresponds to a value which is an object. Each key has values as columns, and columns are grouped together into sets called column families. Thus, each key identifies a row of a variable number of elements. These column families could be considered then as tables. A table in Cassandra is a distributed multi dimensional map indexed by a key. Furthermore, applications can specify the sort order of columns within a Super Column or Simple Column family.

## Clustering
When the cluster for Apache Cassandra is designed, an important point is to select the right partitioner. Two partitioners exist:
* OrderPreservingPartitioner (OPP): This partitioner distributes the key-value pairs in a natural way so that similar keys are not far apart. The advantage is that fewer nodes have to be accessed. The drawback is the uneven distribution of the key-value pairs.
* RandomPartitioner (RP): This partitioner randomly distributes the key-value pairs over the network, resulting in a good load balancing. Compared to OPP, more nodes have to be accessed to get a number of keys.
