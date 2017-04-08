## What is MySQL Cluster ?
MySQL Cluster is a technology providing shared-nothing clustering and auto-sharding for the MySQL database management system. It is designed to provide high availability and high throughput with low latency, while allowing for near linear scalability. MySQL Cluster is implemented through the NDB or NDBCLUSTER storage engine for MySQL ("NDB" stands for Network Database).

## Architecture
MySQL Cluster is designed around a distributed, multi-master ACID compliant architecture with no single point of failure. MySQL Cluster uses automatic sharding (partitioning) to scale out read and write operations on commodity hardware and can be accessed via SQL and Non-SQL (NoSQL) APIs.

#### Replication
Internally MySQL Cluster uses __synchronous replication__ through a __two-phase commit__ mechanism in order to guarantee that data is written to multiple nodes upon committing the data. (This is in contrast to what is usually referred to as "MySQL Replication", which is asynchronous.) Two copies (known as replicas) of the data are required to guarantee availability. MySQL Cluster automatically creates “node groups” from the number of replicas and data nodes specified by the user. Updates are synchronously replicated between members of the node group to protect against data loss and support fast failover between nodes.

It is also possible to replicate asynchronously between clusters; this is sometimes referred to as "MySQL Cluster Replication" or "geographical replication". This is typically used to replicate clusters between data centers for __disaster recovery__ or to reduce the effects of network latency by locating data physically closer to a set of users. Unlike standard MySQL replication, MySQL Cluster's geographic replication uses __optimistic concurrency control__ and the concept of Epochs to provide a mechanism for conflict detection and resolution, enabling active/active clustering between data centers.

#### Horizontal data partitioning
MySQL Cluster is implemented as a fully distributed multi-master database ensuring updates made by any application or SQL node are instantly available to all of the other nodes accessing the cluster, and each data node can accept write operations.

Data within MySQL Cluster (NDB) tables is automatically partitioned across all of the data nodes in the system. This is done based on a hashing algorithm based on the primary key on the table, and is transparent to the end application. Clients can connect to any node in the cluster and have queries automatically access the correct shards needed to satisfy a query or commit a transaction. MySQL Cluster is able to support cross-shard queries and transactions.

Users can define their own partitioning schemes. This allows developers to add “distribution awareness” to applications by partitioning based on a sub-key that is common to all rows being accessed by high running transactions. This ensures that data used to complete transactions is localized on the same shard, thereby reducing network hops.

#### Hybrid storage
MySQL Cluster allows datasets larger than the capacity of a single machine to be stored and accessed across multiple machines.

MySQL Cluster maintains all indexed columns in distributed memory. Non-indexed columns can also be maintained in distributed memory or can be maintained on disk with an in-memory page cache. Storing non-indexed columns on disk allows MySQL Cluster to store datasets larger than the aggregate memory of the clustered machines.

MySQL Cluster writes __Redo logs__ to disk for all data changes as well as check pointing data to disk regularly. This allows the cluster to consistently recover from disk after a full cluster outage. As the Redo logs are written asynchronously with respect to transaction commit, some small number of transactions can be lost if the full cluster fails, however this can be mitigated by using geographic replication or multi-site cluster discussed above. The current default asynchronous write delay is 2 seconds, and is configurable. Normal single point of failure scenarios do not result in any data loss due to the synchronous data replication within the cluster.

When a MySQL Cluster table is maintained in memory, the cluster will only access disk storage to write Redo records and checkpoints. As these writes are sequential and limited random access patterns are involved, MySQL Cluster can achieve higher write throughput rates with limited disk hardware compared to a traditional disk-based caching RDBMS. This checkpointing to disk of in-memory table data can be disabled (on a per-table basis) if disk-based persistence isn't needed.

#### Shared nothing
MySQL Cluster is designed to have no single point of failure. Provided that the cluster is set up correctly, any single node, system, or piece of hardware can fail without the entire cluster failing.

## Implementation
MySQL Cluster uses three different types of nodes (processes) :

* Data node (ndbd/ndbmtd process): These nodes store the data. Tables are automatically sharded across the data nodes which also transparently handle load balancing, replication, failover and self-healing.
* Management node (ndb_mgmd process): Used for configuration and monitoring of the cluster. They are required only to start or restart a cluster node. They can also be configured as arbitrators, but this is not mandatory (MySQL Servers can be configured as arbitrators instead).[5]
* Application node or SQL node (mysqld process): A MySQL server (mysqld) that connects to all of the data nodes in order to perform data storage and retrieval. This node type is optional; it is possible to query data nodes directly via the NDB API, either natively using the C++ API or one of the additional NoSQL APIs described above.
Generally, it is expected that each node will run on a separate physical host, VM or cloud instance (although it is very common to co-locate Management Nodes with MySQL Servers). For best practice, it is recommended not to co-locate nodes within the same node group on a single physical host (as that would represent a single point of failure).

