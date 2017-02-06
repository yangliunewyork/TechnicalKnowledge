## What is Master-Slave databases 
Master databases receive data from applications. Slave databases get copies of that data from the masters. Slaves are therefore read-only from the application's point of view while masters are read-write.

Writes to a database are more "expensive" than reads.  Most web applications require a much higher ratio of reads to writes.  So setting up master-slave replication in the right scenario lets an application distribute its queries efficiently.


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

