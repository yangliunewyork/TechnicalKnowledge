* https://severalnines.com/resources/tutorials/mysql-replication-high-availability-tutorial

aster/slave is a model of communication where one device or process has unidirectional control over one or more other devices. In some systems a master is selected from a group of eligible devices, with the other devices acting in the role of slaves.

# Case Study

## Topology for MySQL Replication

#### Master with Slaves (Single Replication)

![alt](https://severalnines.com/sites/default/files/resources/tutorials/mysql-replication-tutorial/image16.png)

This the most straightforward MySQL replication topology. One master receives writes, one or more slaves replicate from the same master via asynchronous or semi-synchronous replication. If the designated master goes down, the most up-to-date slave must be promoted as new master. The remaining slaves resume the replication from the new master.

#### Master with Relay Slaves (Chain Replication)

![alt](https://severalnines.com/sites/default/files/resources/tutorials/mysql-replication-tutorial/image25.png)

This setup use an intermediate master to act as a relay to the other slaves in the replication chain. When there are many slaves connected to a master, the network interface of the master can get overloaded. This topology allows the read replicas to pull the replication stream from the relay server to offload the master server. On the slave relay server, binary logging and log_slave_updates must be enabled, whereby updates received by the slave server from the master server are logged to the slave's own binary log.

Using slave relay has its problems:

* log_slave_updates has some performance penalty.
* Replication lag on the slave relay server will generate delay on all of its slaves.
* Rogue transactions on the slave relay server will infect of all its slaves.
* If a slave relay server fails and you are not using GTID, all of its slaves stop replicating and they need to be reinitialized.

#### Master with Active Master (Circular Replication)

![alt](https://severalnines.com/sites/default/files/resources/tutorials/mysql-replication-tutorial/image13.png)

Also known as ring topology, this setup requires two or more MySQL servers which act as master. All masters receive writes and generate binlogs with a few caveats:

* You need to set auto-increment offset on each server to avoid primary key collisions.
* There is no conflict resolution.
* MySQL Replication currently does not support any locking protocol between master and slave to guarantee the atomicity of a distributed update across two different servers.
* Common practice is to only write to one master and the other master acts as a hot-standby node. Still, if you have slaves below that tier, you have to switch to the new master manually if the designated master fails.

#### Master with Backup Master (Multiple Replication)

The master pushes changes to a backup master and to one or more slaves. Semi-synchronous replication is used between master and backup master. Master sends update to backup master and waits with transaction commit. Backup master gets update, writes to its relay log and flushes to disk. Backup master then acknowledges receipt of the transaction to the master, and proceeds with transaction commit. Semi-sync replication has a performance impact, but the risk for data loss is minimized.

![alt](https://severalnines.com/sites/default/files/resources/tutorials/mysql-replication-tutorial/image21.png)

This topology works well when performing master failover in case the master goes down. The backup master acts as a warm-standby server as it has the highest probability of having up-to-date data when compared to other slaves.

#### Multiple Masters to Single Slave (Multi-Source Replication)

Multi-Source Replication enables a replication slave to receive transactions from multiple sources simultaneously. Multi-source replication can be used to backup multiple servers to a single server, to merge table shards, and consolidate data from multiple servers to a single server.

![alt](https://severalnines.com/sites/default/files/resources/tutorials/mysql-replication-tutorial/image15.png)

gtid-domain-id configured to distinguish the originating transactions while MySQL uses a separate replication channel for each master the slave replicates from. In MySQL, masters in a multi-source replication topology can be configured to use either global transaction identifier (GTID) based replication, or binary log position-based replication.

#### Galera with Replication Slave (Hybrid Replication)

Hybrid replication is a combination of MySQL asynchronous replication and virtually synchronous replication provided by Galera. The deployment is now simplified with the implementation of GTID in MySQL replication, where setting up and performing master failover has become a straightforward process on the slave side.

![alt](https://severalnines.com/sites/default/files/resources/tutorials/mysql-replication-tutorial/image22.png)

Galera cluster performance is as fast as the slowest node. Having an asynchronous replication slave can minimize the impact on the cluster if you send long-running reporting/OLAP type queries to the slave, or if you perform heavy jobs that require locks like mysqldump. The slave can also serve as a live backup for onsite and offsite disaster recovery.
