#### Common
A set of components and interfaces for distributed filesystems and general I/O (serialization, Java RPC, persistent data structures).

#### Avro
A serialization system for efficient, cross-language RPC, and persistent data storage.

#### MapReduce
A distributed data processing model and execution environment that runs on large clusters of commodity machines.

#### HDFS
A distributed filesystem that runs on large clusters of commodity machines.

#### Pig
A data flow language and execution environment for exploring very large datasets. Pig runs on HDFS and MapReduce clusters.

#### Hive
A distributed data warehouse. Hive manages data stored in HDFS and provides a query language based on SQL (and which is translated by the runtime engine to MapReduce jobs) for querying the data.

#### HBase
A distributed, column-oriented database. HBase uses HDFS for its underlying storage, and supports both batch-style computations using MapReduce and point queries (random reads).

#### ZooKeeper
A distributed, highly available coordination service. ZooKeeper provides primitives such as distributed locks that can be used for building distributed applications.

#### Sqoop
A tool for efficiently moving data between relational databases and HDFS.
