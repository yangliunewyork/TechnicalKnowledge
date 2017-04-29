* Reference :  High Performance MySQL

MySQL use often grows organically. In the corporate world, a single application developer may build the company's next killer app on top of MySQL. This initial success with MySQL development typically breeds more projects and more success. As the amount of data you manage using MySQL grows, you'll certainly appreciate its ability to handle large amounts of data efficiently. You may even find that MySQL has become the de facto standard backend storage for your applications.

At the same time, you may also begin to wish for an easy way to copy all the data from one MySQL server to another. Maybe you need to share data with a remote office in your organization, or you might just like to have a "hot spare" available in case your server dies. Fortunately, MySQL has a built-in replication system. You can easily configure a second server as a slave of your master, ensuring that it has an exact copy of all your data.

## Replication Overview
Database replication has an undeserved reputation for being complex to set up and prone to failure. The early versions of MySQL replication were difficult to configure because the process was inadequately documented. In its most basic form, replication consists of two servers: a __master__ and a __slave__. The master records all queries that change data in its __binary log__. The slave connects to the master, reads queries from the master's binary log, and executes them against its local copy of the data.

Before peering under the hood, let's look at the types of problems replication does and doesn't solve. If you're reading this in the hopes of deploying replication to cure a problem, this section may help you decide whether you're on the right track.

### Problems Solved with Replication

##### Data distribution
Need to maintain a copy of your data 10,000 miles away? Replication makes it trivial to do so. As long as you have decent connectivity between two sites, you can replicate a MySQL database. Think of this as scaling geographically.

In fact, it's possible to use replication over a network connection that isn't "always on," such as traditional dial-up using PPP. You can simply let the slave fail and reconnect (it'll keep trying for a long time). Or you can use one of the ```SLAVE STOP``` commands (described later) to disable the slave's replication when no connection is available. The master doesn't mind if a slave disconnects for a few hours and then reconnects. But you can't let the slave go for too long without reconnecting to the master, because the older record of changes will eventually be purged to keep the master from running out of disk space.

Of course, you can also use replication between two servers that sit next to each other. Any time you need multiple up-to-date copies of your MySQL data, replication is often the easiest solution. You can even replicate data between two MySQL servers on the same machine, which is often a good way to test a new version of MySQL without using a second machine.

##### Load balancing
If you use MySQL on a large data warehousing application or a popular web site, odds are that your server is running many more read queries (SELECT) than write queries (INSERT, UPDATE, and DELETE). If that's the case, replication is an excellent way to support basic load balancing. By having one or more slave servers, you can spread most of the work among several servers.

The trick, of course, is coming up with an effective way to spread the queries among the available slaves so they get roughly equal workloads. One simple approach is to use round-robin DNS. Assign multiple IP addresses for a hostname such as db-slave.example.com, and your application will connect to one at random each time it opens a new connection to MySQL.

A more sophisticated approach involves the same solutions that are used in web server load balancing. Network load-balancing products from Foundry Networks, Cisco, Nortel, and others work just as well for MySQL as they do for web sites. The same is true of software solutions such as the Linux Virtual Server (LVS) project.

##### Backup and recovery
Backing up a busy MySQL server can be difficult when your clients demand access to the data 24 hours a day. Rather than deal with the complexity of implementing a backup process that minimizes the impact on your clients, you might find it easier simply to configure a slave server and back it up instead. Because the slave will have an exact copy of the data, it's just as good as backing up the master. Plus you'll never impact the clients who are using the master. You might even decide that you don't necessarily need or want to back up the data as long as you have the "hot spare" slave database available in the case of problems with the master.

##### High availability and failover
Using replication, you can avoid making MySQL (or the system hosting it) a single point of failure in your applications. Although there's no out-of-the-box, automated failover solution for MySQL, you can achieve a good degree of high availability using some relatively simple techniques.

Using a creative DNS setup, you can insulate your applications from having to know which server is the master and minimize the effort involved in switching to a slave when the master fails.

Let's suppose you have two MySQL servers, db1.example.com and db2.example.com. Rather than hardcoding the name of the master in your applications, you can set up db.example.com as a CNAME (or alias) in DNS for your master. By using a very low Time To Live (TTL) on the DNS record, you can ensure that clients will not cache the information longer than necessary.

In the event your master goes down, simply update your DNS to point db.example.com at the new master. As soon as the TTL expires, your applications will pick up the new information and connect to the proper server. There will be some time during which the applications can't contact MySQL, but that time will be relatively brief if you use a low enough TTL.

If you'd like to eliminate entirely the need to use DNS, you can play similar games using IP addresses. Because it's trivial to add and remove additional IP addresses from a server, a scheme like this may serve you well:

* Use an IP address for each role, such as 192.168.1.1 for the master and an address in the 192.168.1.100-192.168.120 range for each slave.
* Make sure each machine has its own primary IP address in addition to the role-based IP address.
* When the master goes down, any of the slaves can be scripted to pick up the IP address and immediately take over.
* The master should be set so that if it ever loses its master address or goes down, it doesn't automatically pick up the address again (i.e., it assumes someone else will).

### Problems Not Solved with Replication
Replication doesn't solve every problem. Performance can become an issue with replication because every slave still needs to execute the same write queries as the master. In a very write-heavy application, slaves need to be at least as powerful as the master. If you attempt to use replication to set up a load-balancing system, you may be disappointed. It may be more productive to implement a partitioning system with multiple masters—one for each partition of the data.

Also, there's no guarantee that a slave will be completely in sync with the master at any given moment. If the load on a slave is relatively high, the slave may fall behind and need time to catch up.

Network bandwidth and latency can also become an issue. If the slave is far away from the master (in a network sense) and there isn't sufficient bandwidth, a slave may be able to keep up with the master's query load, but it won't be able to get data fast enough to do so.

Let's look at two specific examples that illustrate problems not easily solved with replication.

##### Real-time data transmission
MySQL's replication isn't the ideal vehicle for transmitting real-time or nearly real-time data such as a stock quote feed or an online auction site. In those applications, it's important that the user sees up-to-date data no matter which database server they use.

The only way to combat MySQL's lack of any latency guarantee is to implement your own monitoring system. It needs to use some sort of heartbeat to verify that each server has a reasonably up-to-date copy of the data. In the event that a server falls too far behind, the monitoring system needs to proactively remove it from the list of active servers until it can catch up.

Of course, you can also build your application in such a way that it updates all the slaves with the newest data. However, that can add a lot of complexity and may not be worth the effort. You'd end up writing a lot of code to handle the exceptional conditions, such as when a single server falls behind or is intermittently inaccessible. Testing and debugging all those situations can be very time-consuming and difficult.

As Derek went over this, he thought, "Wouldn't it be cool if MySQL could provide a query response that signified, `Go ask another server, I'm really busy right now'?" This would allow clients to automatically find willing servers in a multihost DNS rotation.

For example, the client wants to connect to db.example.com (which is db1, db2, and db3). It connects (randomly) to db2, and the server answers the query with "I'm busy; go ask someone else," whereupon the client knows enough to try db1 or db3. Because the client library would be connecting to the same virtual server, it could transparently disconnect from the busy server and connect to some other (hopefully less busy) server.

As a result, all you would need is some automated way for a slave server to know how far behind they are and to shut themselves off from queries when they get too far behind, and you'd have some protection. Of course, this could also be subject to a cascading failure. If all the slaves are very busy, the last thing you'd want is for them to start removing themselves from the pool of available servers.

##### Online ordering
An ordering system is different from a real-time stock quote feed or an auction site in a couple of important ways. First, the ratio of reads to writes is likely to be much lower. There isn't a constant stream of users running read-only queries against the data. Also, when users are running read queries, they're often part of a larger transaction, so you can't send those read queries to a slave. If you did, the slave might not have the correct data yet. Transactions aren't written to the binary log and therefore sent to slaves until they first commit on the master. A slave will contain only committed transactions.

Replication can still be very useful for an order processing system. It's reasonable to use a slave for running nightly reports and queries that don't need the most recent data.

### Replication Performance
Having considered the problems that replication does and doesn't solve, you may still be a bit unsure about using it. Maybe replication is fast enough to get the job done, despite the lack of any performance guarantees built into the system. Wouldn't it be nice to have a general idea of how fast replication really is?

That's exactly what we wanted to know when we first began using replication—partly for our own sanity and partly because we knew a lot of people would soon be interested in MySQL replication. The first question they'd ask is, "How fast is it?" To answer that question, we devised the following simple test to measure the practical minimum replication latency in a particular environment.

A Perl script opened two database connections, one to the master and one to the slave. The master and slave were on the same 100-Mbit switched Ethernet network. The script then inserted a record into the master and immediately attempt to retrieve it from the slave. If the record wasn't available, the script immediately retried. We kept the records intentionally small, containing just an auto-increment column and a VARCHAR field into which we inserted the current time.

The results were encouraging. Of the 1,000 records inserted, 950 of them were available on the first attempt. That left 50 records that required at least a second try. Of those 50, 43 were available on the second attempt. The remaining 7 were there on the third try. The test was quick and very unscientific, but it can help to set realistic expectations.

## Under the Hood

### Replication in 3.23

MySQL's original replication code provides basic replication services. The master logs all write queries to the binary log. The slave reads and executes the queries from the master's binary log. If the two are ever disconnected, the slave attempts to reconnect to the master.

If you follow a query from start to finish, here's what's happening behind the scenes:

1. The client issues a query on the master.
2. The master parses and executes the query.
3. The master records the query in the binary log.
4. The slave reads the query from the master.
5. The slave parses and executes the query.
6. The slave performs a sanity check, comparing its result with the master's. If the query failed on the slave but succeeded on the master, replication stops. The reverse is also true. If the query partially completed on the master but succeeds on the slave, the slave stops and complains.
7. The slave updates the master.info file to reflect the new offset at which it is reading the master's binary log.
8. The slave waits for the next query to appear in the master's binary log. When one appears, it starts over at Step 4.

That's a relatively simple arrangement. The master simply logs any queries that change data. The slave reads those queries from the master, one by one, and executes each of them. If there are any discrepancies between the results on the master and the slave, the slave stops replicating, logs an error, and waits for human intervention.

The simplicity of this system has problems, however. If the master and slave are separated by a slow network, the speed at which replication can occur becomes bounded by the network latency. Why? Because the process is highly serialized. The slave runs in a simple "fetch query, execute query, fetch query, ..." loop. If the "fetch query" half of the loop takes more than a trivial amount of time, the slave may not be able to keep up with the master during very heavy workloads. The master may be able to execute and log 800 queries per second, but if the slave requires 25 msec to fetch each query over the network, it can replicate no more than 40 queries per second.

This can be problematic even with a fast network connection. Suppose the master executes a query that takes five minutes to complete. Maybe it's an UPDATE that affects 50 million records. During the five minutes the slave spends running the same query, it isn't pulling new queries from the master. By the time it completes the query, it's effectively five minutes behind the master, in terms of replication. It has a fair bit of catching up to do. If the master fails during that five-minute window, there's simply no way for the slave to catch up until the master reappears.

### Replication in 4.0
To solve the problem of slaves falling behind because of slow queries or slow networks, the replication code was reworked for Version 4.0. Instead of a single thread on the slave that runs in a "fetch, execute, fetch, ..." loop, there are two replication threads: the IO thread and the SQL thread.

These two threads divide the work in an effort to make sure the slave can always be as up to date as possible. The IO thread is concerned only with replicating queries from the master's binary log. Rather than execute them, it records them into the slave's relay log. The SQL thread reads queries from the local relay log and executes them.

> To keep things simple, the relay log file uses the same storage format as the master's binary log.

To put this in context, let's look at the step-by-step breakdown for replication in MySQL 4.0:

1. The client issues a query on the master.
2. The master parses and executes the query.
3. The master records the query in the binary log.
4. The slave's IO thread reads the query from the master and appends it to the relay log.
5. The slave's IO thread updates the master.info file to reflect the new offset at which it is reading the master's binary log. It then returns to Step 4, waiting for the next query.
6. The slave's SQL thread reads the query from its relay log, parses it, and then executes it.
7. The slave's SQL thread performs a sanity check, comparing its result with the master's. If the query failed on the slave but succeeded on the master, replication stops.
8. The slave's SQL thread updates the relay-log.info file to reflect the new offset at which it is reading the local relay log.
9. The slave's SQL thread waits for the next query to appear in the relay log. When one appears, it starts over at Step 6.

While the steps are presented as a serial list, it's important to realize that Steps 4-5 and 6-9 are running as separate threads and are mostly independent of each other. The IO thread never waits for the SQL thread; it copies queries from the master's binary log as fast as possible, which helps ensure that the slave can bring itself up to date even if the master goes down. The SQL thread waits for the IO thread only after it has reached the end of the relay log. Otherwise it is working as fast as it can to execute the queries waiting for it.

This solution isn't foolproof. It's possible for the IO thread to miss one or more queries if the master crashes before the thread has had a chance to read them. The amount of data that could be missed is greatly reduced compared to the 3.23 implementation, however.

## Replication Architectures

### The Replication Rules
Before looking at the architectures, it helps to understand the basic rules that must be followed in any MySQL replication setup:

* Every slave must have a unique server ID.
* A slave may have only one master.
* A master may have many slaves.
* Slaves can also be masters for other slaves.

The first rule isn't entirely true, but let's assume that it is for right now, and soon enough you'll see why it isn't always necessary. In any case, the rules aren't terribly complex. Those four rules provide quite a bit of flexibility, as the next sections illustrate.

#### Master with slaves
The most basic replication model, a single master with one or more slaves. The master is given server ID 1 and each slave has a different ID.

![alt](http://www.clusterdb.com/wp-content/uploads/2010/10/Multiple_slaves.jpg)

This configuration is useful in situations in which you have few write queries and many reads. Using several slaves, you can effectively spread the workload among many servers. In fact, each of the slaves can be running other services, such as Apache. By following this model, you can scale horizontally with many servers. The only limit you are likely to hit is bandwidth from the master to the slaves. If you have 20 slaves, which each need to pull an average of 500 KB per second, that's a total of 10,000 KB/sec (or nearly 10 Mbits/sec) of bandwidth.

A 100-Mbit network should have little trouble with that volume, but if either the rate of updates to the master increases or you significantly increase the number of slaves, you run the risk of saturating even a 100-Mbit network. In this case, you need to consider gigabit network hardware or an alternative replication architecture, such as the pyramid described later.

#### Slave with two masters
It would be nice to use a single slave to handle two unrelated masters. That allows you to minimize hardware costs and still have a backup server for each master. However, it's a violation of the second rule: a slave can't have two masters.

To get around that limitation, you can run two copies of MySQL on the slave machine. Each MySQL instance is responsible for replicating a different master. In fact, there's no reason you couldn't do this for 5 or 10 distinct MySQL masters. As long as the slave has sufficient disk space, I/O, and CPU power to keep up with all the masters, you shouldn't have any problems.

#### Dual master
Another possibility is to have a pair of masters. This is particularly useful when two geographically separate parts of an organization need write access to the same shared database. Using a dual-master design means that neither site has to endure the latency associated with a WAN connection.

Furthermore, WAN connections are more likely to have brief interruptions or outages. When they occur, neither site will be without access to their data, and when the connection returns to normal, both masters will catch up from each other.Of course, there are drawbacks to this setup. However, if responsibility for your data is relatively well partitioned (site A writes only to customer records, and site B writes only to contract records) you may not have much to worry about.

A logical extension to the dual-master configuration is to add one or more slaves to each master. This has the same benefits and drawbacks of a dual-master arrangement, but it also inherits the master/slave benefits at each site. With a slave available, there is no single point of failure. The slaves can be used to offload read-intensive queries that don't require the absolutely latest data.

#### Replication ring (multi-master)

![alt](https://severalnines.com/sites/default/files/blog/node_5019/image02.png)

The dual-master configuration is really just a special case of the master ring configuration. In a master ring, there are three or more masters that form a ring. Each server is a slave of one of its neighbors and a master to the other.

The benefits of a replication ring are, like a dual-master setup, geographical. Each site has a master so it can update the database without incurring high network latencies. However, this convenience comes at a high price. Master rings are fragile; if a single master is unavailable for any reason, the ring is broken. Queries will flow around the ring only until they reach the break. Full service can't be restored until all nodes are online.

To mitigate the risk of a single node crashing and interrupting service to the ring, you can add one or more slaves at each site. But this does little to guard against a loss of connectivity.

![alt](http://pic002.cnblogs.com/images/2012/93867/2012090320454927.jpg)

#### Pyramid

In large, geographically diverse organizations, there may be a single master that must be replicated to many smaller offices. Rather than configure each slave to contact the master directly, it may be more manageable to use a pyramid design.


## Common Problems

####  Slave Data Changes

It should go without saying that manually changing data on a slave is usually a very bad idea. The same holds true for programmatically changing slave data. By accidentally making changes to data on a slave, you can easily introduce data inconsistencies that may cause replication to fail. It may take hours, days, weeks, or even months for the problem to surface, and when it does, you'll be hard pressed to explain what's going on.

Before MySQL 4.0.14 there was no way to tell MySQL not to allow any changes that don't originate from replication. Instead, the best solution in versions prior to 4.0.14 has an ironic aspect to it: you need to make a change on all the slaves, removing the permissions (or even the accounts) of users who can change data.

But that solution is problematic for other reasons. You'd probably forget about the change after a while. Then, late one night, the master would fail and you would need to promote a slave to master. You'd have to spend a bit of time trying figure out why applications are mysteriously failing.

As of Version 4.0.14, adding read-only to the slave's configuration file allows the slave to process write queries only via replication.

It's worth remembering that MySQL is very trusting when it comes to replication. The slave threads don't switch identities to run each query as the same user that originally executed it on the master. Instead, the slave thread runs with the equivalent of root access on the slave. It can, by design, change any data it needs to change. The trust comes from the fact that the slaves never verify that a particular user has the necessary privileges to run a query that appears in the binary log. It blindly trusts the master and that the master's logs haven't been tampered with.

#### Nonunique Server IDs
This has to be one of the most elusive problems you can encounter with MySQL replication. If you accidentally configure two slaves with the same server ID they'll appear to work just fine if you're not watching closely. But if you watch their error logs carefully or watch the master with mytop (covered in Appendix B), you'll notice something very odd.

On the master, you'll see only one of the two slaves connected at a given moment. Usually all slaves are connecting and replicating all the time. On the slave you'll see frequent disconnect/reconnect messages appearing in the error log, but none of those messages will lead you to believe that the server ID of one slave might be misconfigured.

The only real harm in this situation is that the slaves can't replicate very quickly. Because the slaves (not the master) keep track of their replication progress, there's no need to worry about giving one query to the first slave, one to the other slave, and so on. Both slaves get all the data; they just get it much more slowly.

The only solution to this problem is to be careful when setting up your slaves. If you see symptoms like this, double check the configuration of each slave to ensure that it has the server ID you expect it to. You may find it helpful to keep a master list of slave-to-server-ID mappings so that you don't lose track of which ID belongs to each slave. Consider using numeric values that have some sort of meaning in your setup, such as the last octet of each machine's IP address.

#### Log Corruption or Partial Log Record
The second most elusive problem occurs when a binary log somehow becomes corrupted. When that happens, the slave will typically fail with an error message like:
```
Error in Log_event::read_log_event( ): '...', data_len=92,event_type=2
```
If that ever happens, there's little you can do. The slave is often confused enough that you can't simply try to skip the query and go to the next one. The only solution is to resync with the master and start over.

How does this happen? It's difficult to say. As long as the software is working properly, it could be a hardware or driver problem. Jeremy once saw a system have this problem repeatedly before he found that it had faulty RAM installed. We have heard of it happening on systems with disk controllers that don't have reliable drivers.

#### Bulk-Loading Data

While you can write code to load a lot of data into MySQL quickly, nothing beats the performance of using MySQL's LOAD DATA INFILE and LOAD DATA LOCAL INFILE commands to read data in from a flat file. In fact, the mysqlimport command-line tool uses LOAD DATA INFILE behind the scenes.

In all 3.23.xx versions of MySQL, replicating the LOAD DATA INFILE command is problematic. The contents of the file aren't stored in the binary log; only the query is, so the file must exist on the master until all slaves have copied it (they will do so automatically when they need it). If the file is removed prematurely, slaves can't copy the file, and replication will fail.

The LOAD DATA LOCAL INFILE command isn't affected. When the LOCAL option is specified, the mysql client reads the file from the client and generates the appropriate SQL to insert the data.

To avoid this problem, it's best either to load the data remotely using the latter syntax or to import the data programmatically. Either option ensures that the inserting is done via normal SQL statements that will all be properly logged.

Starting with Version 4.0, MySQL doesn't have this limitation. When a LOAD DATA INFILE command is issued, MySQL actually copies the entire file into the binary log. Slaves don't need to pull a copy of the original file from the master's disk.

#### Nonreplicated Dependencies

If you perform binary log filtering on either the master or the slave, it's quite easy to inadvertently break replication. For example, you may want to have a production database called production and a staging database called staging. The idea is to do all the necessary testing, development, and retesting in the staging database. When all the interim work is complete, you copy the data into the production database.

If the slave ignores queries from the staging database because of a filtering rule like the following, you'll probably end up frustrated:

```
replicate-do-db = production
```

You might try to run a query like this one to populate one of the production tables:

```
INSERT INTO production.sales SELECT * FROM staging.sales
```

This query works fine on the master, but the slaves will all fail because they don't have copies of the staging database. In fact, there's no easy way to make it work. Any attempt to reference the staging database is doomed to fail.

The only real solution in a case like this is to export all the data from the staging database and import it into the production database. You can do this programmatically if you want fine control over the process, or you can simply use mysqldump to dump the data to a text file and reimport it using mysql.

#### Missing Temporary Tables

This is really a special case of the previous example, but it warrants special attention because the real cause is a bit different. Instead of a filtering problem, this is a problem of restarting the slave at the wrong time.

Temporary tables replicate just fine, but if a series of queries that create and use a temporary table are interrupted on a slave by a restart or by stopping and starting replication, replication will fail.

Temporary tables are, by definition, temporary. When the server is restarted, they vanish. When the thread vanishes (such as with a SLAVE STOP or SLAVE STOP SQL_THREAD command), any temporary tables created by that thread vanish.

There is no good solution for this problem. On the application side, it's best if temporary tables are created as late as possible, which helps minimize the time between the creation of the table and when it is actually needed. But even this solution only decreases the likelihood of the problem occurring.

You can avoid temporary tables completely, but that may involve time-consuming application changes. You'd have to ensure that the nontemporary tables created by your application always have unique names and that they are dropped when appropriate.

Because they are transient, this problem also affects Heap tables. They are always dropped explicitly, however so they vanish only when a slave is restarted. Stopping and restarting replication on the slave doesn't affect Heap tables.

#### Binary Log Out of Sync with Transaction Log

We know that MySQL records queries in the binary log after it executes them. We also know that MySQL writes transactions to the binary log after they have been committed. What happens if MySQL crashes, or someone pulls the plug in the microseconds after a transaction has been committed but before it writes the transaction to the binary log?

The result is that the master will contain the results of having completed the transaction, but the slaves will never see it. Ever. The transaction may have been a simple insert, or it could have been something as dramatic as a DROP TABLE command.

There is currently no workaround for this problem. Luckily MySQL crashes are rare. Make sure the power cables are plugged in tightly!

#### Slave Wants to Connect to the Wrong Master

If you change the hostname of your master, it's important to tell slaves using the CHANGE MASTER command:

mysql> CHANGE MASTER TO MASTER_HOST='newmaster.example.com';
You can't simply shut down the slave, edit the my.cnf file, and start it back up. MySQL always uses the master.info file if it exists, despite the settings contained in the my.cnf file.[8]

[8] This is, in my opinion, an easy-to-fix bug, but the MySQL maintainers don't agree. The workaround is to always use the CHANGE MASTER TO command for configuring slaves.

Alternatively, you can manually edit the master.info file, replacing the old hostname with the new one. The danger in relying on this method is that the master.info file can be deprecated, replaced, or radically changed in a future version of MySQL. It's best to stick to the documented way of doing things.

## The Future of Replication



