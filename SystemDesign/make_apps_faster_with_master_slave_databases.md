* https://www.quora.com/What-are-Master-and-Slave-databases-and-how-does-pairing-them-make-web-apps-faster

# What are Master and Slave databases and how does pairing them make web apps faster?

A database is "slaved" to a "master" when it receives a stream of updates from the master in near real-time, functioning as a copy. The "slave" must simply apply the changes that the master validated and approved.

In principle, one could create a master-slave setup by transferring files really fast from one server to the other; but in practice, each database has its own specialized replication protocol.

There are many reasons a replica makes queries return faster. One is that the master's CPU is less burdened by queries while the replica's CPU is less burdened by writes; so there is more CPU available to do work. Another is that data, while nominally stored to disk, is cached in RAM when that is possible; and indeed the OS does this whether the database asks for it or not and can be unpredictable about it. On the master, recently written portions of the database and anything used to support writes -- for example, indexes used to check uniqueness -- will be in RAM all the time; these must share space with the portions of the database loaded to serve queries. The replica needn't load as much data to support its write load (it is writing to the same parts of the database, but can naively commit it without checking anything) and it makes more RAM available to serve queries.

There is also the matter of disk access. When data is written on the master, it must be written to disk before the master can return a successful commit message to the application. To write to disk, the operating system must make the disk head available. If the disk head is far from the place where we need to write the updated or added record, then it must be moved. For the disk head to "seek" can be quite time consuming, relative to other operations. For this reason, database developers have cleverly chosen to have their databases write all changes one right after another, next to each other on the disk, until a few changes have been written. Thus the disk head needn't move at all from the place where it was when the last record was written. This log of records does not store them in the most efficient way -- the database "heap" is where the records are most efficiently stored -- but for a few records at a time, it's not a problem. Every so often, the database software takes all the logged changes and writes them into the heap. This latter step does, indeed, move the disk head; but at least we haven't moved it back and forth all over the heap for each and every change. Reducing seeks greatly improves the database's average performance.

Reads do not allow these kinds of shortcuts. To read data, we must go to its place on disk and read it out. This reintroduces pressure to move the disk head back and forth. A replica has its own disk head (or heads) and can thus take on some of this load of seeking for queries.

One could realize these same benefits by getting a bigger server, too; one with more disks, CPU and RAM. Doing that without downtime is a little tough, though. And whereas a replica gives you an option in the event that the master goes down, one big database server is not any more reliable than one small database server.


