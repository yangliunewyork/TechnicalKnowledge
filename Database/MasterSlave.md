## What is Master-Slave databases 
Master databases receive data from applications. Slave databases get copies of that data from the masters. __Slaves are therefore read-only from the application's point of view while masters are read-write.__

Writes to a database are more "expensive" than reads.  Most web applications require a much higher ratio of reads to writes.  So setting up master-slave replication in the right scenario lets an application distribute its queries efficiently.

A database is "slaved" to a "master" when it receives a stream of updates from the master in near real-time, functioning as a copy. The "slave" must simply apply the changes that the master validated and approved.

In principle, one could create a master-slave setup by transferring files really fast from one server to the other; but in practice, each database has its own specialized replication protocol.

There are many reasons a replica makes queries return faster. __One is that the master's CPU is less burdened by queries while the replica's CPU is less burdened by writes; so there is more CPU available to do work.__ Another is that data, while nominally stored to disk, is cached in RAM when that is possible; and indeed the OS does this whether the database asks for it or not and can be unpredictable about it. On the master, recently written portions of the database and anything used to support writes -- for example, indexes used to check uniqueness -- will be in RAM all the time; these must share space with the portions of the database loaded to serve queries. The replica needn't load as much data to support its write load (it is writing to the same parts of the database, but can naively commit it without checking anything) and it makes more RAM available to serve queries.

There is also the matter of disk access. When data is written on the master, it must be written to disk before the master can return a successful commit message to the application. To write to disk, the operating system must make the disk head available. If the disk head is far from the place where we need to write the updated or added record, then it must be moved. For the disk head to "seek" can be quite time consuming, relative to other operations. For this reason, database developers have cleverly chosen to have their databases write all changes one right after another, next to each other on the disk, until a few changes have been written. Thus the disk head needn't move at all from the place where it was when the last record was written. This log of records does not store them in the most efficient way -- the database "heap" is where the records are most efficiently stored -- but for a few records at a time, it's not a problem. Every so often, the database software takes all the logged changes and writes them into the heap. This latter step does, indeed, move the disk head; but at least we haven't moved it back and forth all over the heap for each and every change. Reducing seeks greatly improves the database's average performance.

Reads do not allow these kinds of shortcuts. To read data, we must go to its place on disk and read it out. This reintroduces pressure to move the disk head back and forth. A replica has its own disk head (or heads) and can thus take on some of this load of seeking for queries.

One could realize these same benefits by getting a bigger server, too; one with more disks, CPU and RAM. Doing that without downtime is a little tough, though. And whereas a replica gives you an option in the event that the master goes down, one big database server is not any more reliable than one small database server.

## Master-master vs master-slave database architecture?
There's a fundamental tension:

One copy: consistency is easy, but if it happens to be down everybody is out of the water, and if people are remote then may pay horrid communication costs. Bring portable devices, which may need to operate disconnected, into the picture and one copy won't cut it.

Master Slave: consistency is not too difficult because each piece of data has exactly one owning master. But then what do you do if you can't see that master, some kind of postponed work is needed.

Master-Master: well if you can make it work then it seems to offer everything, no single point of failure, everyone can work all the time. Trouble is it very hard to preserve absolute consistency. 

## Master-Slave Replication

Pros

  * Analytic applications can read from the slave(s) without impacting the master
  * Backups of the entire database of relatively no impact on the master
  * Slaves can be taken offline  and sync back to the master without any downtime

Cons

 * In the instance of a failure a slave has to be promoted to master to take over its place. No automatic failover
 * Downtime and possibly lost of data when a master fails
 * All writes also have to be made to the master in a master-slave design
 * Each additional slave add some load* to the master since the binary log have to be read and data copied to each slave
 * Application might have to be restarted

## Master-master advantages and disadvantages

__Advantages__

* If one master fails, other masters will continue to update the database.
* Masters can be located in several physical sites i.e. distributed across the network.

__Disadvantages__

* Most multi-master replication systems are only loosely consistent, i.e. lazy and asynchronous, violating ACID properties.
* Eager replication systems are complex and introduce some communication latency.
* Issues such as conflict resolution can become intractable as the number of nodes involved rises and the required latency decreases.

