# The Dawn of Big Data

We live in an era in which we are all connected over the Internet and expect to find results instantaneously, whether the question concerns the best turkey recipe or what to buy mom for her birthday. We also expect the results to be useful and tailored to our needs.

Because of this, companies have become focused on delivering more targeted information, such as recommendations or online ads, and their ability to do so directly influences their success as a business. Systems like Hadoop† now enable them to gather and process petabytes of data, and the need to collect even more data continues to increase with, for example, the development of new machine learning algorithms.

In the past, the only option to retain all the collected data was to prune it to, for example, retain the last N days. While this is a viable approach in the short term, it lacks the opportunities that having all the data, which may have been collected for months or years, offers: you can build mathematical models that span the entire time range, or amend an algorithm to perform better and rerun it with all the previous data.

Hadoop excels at storing data of arbitrary, semi-, or even unstructured formats, since it lets you decide how to interpret the data at analysis time, allowing you to change the way you classify the data at any time: once you have updated the algorithms, you simply run the analysis again. 

Hadoop also complements existing database systems of almost any kind. It offers a limitless pool into which one can sink data and still pull out what is needed when the time is right. It is optimized for large file storage and batch-oriented, streaming access. This makes analysis easy and fast, but users also need access to the final data, not in batch mode but using random access - this is akin to a full table scan versus using indexes in a database system.

We are used to querying databases when it comes to random access for structured data. RDBMSes are the most prominent, but there are also quite a few specialized variations and implementations, like object-oriented databases. Most RDBMSes strive to implement Codd’s 12 rules,§ which forces them to comply to very rigid requirements. The architecture used underneath is well researched and has not changed significantly in quite some time. The recent advent of different approaches, like column-oriented or massively parallel processing (MPP) databases, has shown that we can rethink the technology to fit specific workloads, but most solutions still implement all or the majority
of Codd’s 12 rules in an attempt to not break with tradition.

Note, though, that HBase is not a column-oriented database in the typical RDBMS sense, but utilizes an on-disk column storage format. This is also where the majority of similarities end, because although HBase stores data on disk in a column-oriented format, it is distinctly different from traditional columnar databases: whereas columnar databases excel at providing real-time analytical access to data, HBase excels at providing key-based access to a specific cell of data, or a sequential range of cells.

The speed at which data is created today is already greatly increased, compared to only just a few years back. We can take for granted that this is only going to increase further, and with the rapid pace of globalization the problem is only exacerbated. Websites like Google, Amazon, eBay, and Facebook now reach the majority of people on this planet. The term planet-size web application comes to mind, and in this case it is fitting.

![alt](https://www.safaribooksonline.com/library/view/hbase-the-definitive/9781449314682/httpatomoreillycomsourceoreillyimages889228.png)

# The Problem with Relational Database Systems

RDBMSes have typically played (and, for the foreseeable future at least, will play) an integral role when designing and implementing business applications. As soon as you have to retain information about your users, products, sessions, orders, and so on, you are typically going to use some storage backend providing a persistence layer for the frontend application server. This works well for a limited number of records, but with the dramatic increase of data being retained, some of the architectural implementation details of common database systems show signs of weakness.

Let us use Hush, the HBase URL Shortener mentioned earlier, as an example. Assume that you are building this system so that it initially handles a few thousand users, and that your task is to do so with a reasonable budget—in other words, use free software. The typical scenario here is to use the open source LAMP‡ stack to quickly build out a prototype for the business idea.

The relational database model normalizes the data into a user table, which is accompanied by a url, shorturl, and click table that link to the former by means of a foreign key. The tables also have indexes so that you can look up URLs by their short ID, or the users by their username. If you need to find all the shortened URLs for a particular list of customers, you could run an SQL JOIN over both tables to get a comprehensive list of URLs for each customer that contains not just the shortened URL but also the customer details you need.

In addition, you are making use of built-in features of the database: for example, stored procedures, which allow you to consistently update data from multiple clients while the database system guarantees that there is always coherent data stored in the various tables.

Transactions make it possible to update multiple tables in an atomic fashion so that either all modifications are visible or none are visible. The RDBMS gives you the socalled ACID properties, which means your data is __strongly consistent__. __Referential integrity__ takes care of enforcing relationships between various table schemas, and you get a domainspecific language, namely SQL, that lets you form complex queries over everything. Finally, you do not have to deal with how data is actually stored, but only with higherlevel concepts such as table schemas, which define a fixed layout your application code can reference.

This usually works very well and will serve its purpose for quite some time. If you are lucky, you may be the next hot topic on the Internet, with more and more users joining your site every day. As your user numbers grow, you start to experience an increasing amount of pressure on your shared database server. Adding more application servers is relatively easy, as they share their state only with the central database. Your CPU and I/O load goes up and you start to wonder how long you can sustain this growth rate.

The first step to ease the pressure is to add slave database servers that are used to being read from in parallel. You still have a single master, but that is now only taking writes, and those are much fewer compared to the many reads your website users generate. But what if that starts to fail as well, or slows down as your user count steadily increases?

A common next step is to add a cache—for example, Memcached.‖ Now you can offload the reads to a very fast, in-memory system—however, you are losing consistency guarantees, as you will have to invalidate the cache on modifications of the original value in the database, and you have to do this fast enough to keep the time where the cache and the database views are inconsistent to a minimum.

While this may help you with the amount of reads, you have not yet addressed the writes. Once the master database server is hit too hard with writes, you may replace it with a beefed-up server—scaling up vertically—which simply has more cores, more memory, and faster disks... and costs a lot more money than the initial one. Also note that if you already opted for the master/slave setup mentioned earlier, you need to make the slaves as powerful as the master or the imbalance may mean the slaves fail to keep up with the master’s update rate. This is going to double or triple the cost, if not more.

With more site popularity, you are asked to add more features to your application, which translates into more queries to your database. The SQL JOINs you were happy to run in the past are suddenly slowing down and are simply not performing well enough at scale. You will have to denormalize your schemas. If things get even worse, you will also have to cease your use of stored procedures, as they are also simply becoming too slow to complete. Essentially, you reduce the database to just storing your data in a way that is optimized for your access patterns.

Your load continues to increase as more and more users join your site, so another logical step is to prematerialize the most costly queries from time to time so that you can serve the data to your customers faster. Finally, you start dropping secondary indexes as their maintenance becomes too much of a burden and slows down the database too much. You end up with queries that can only use the primary key and nothing else.

Where do you go from here? What if your load is expected to increase by another order of magnitude or more over the next few months? You could start sharding (see the sidebar titled “Sharding”) your data across many databases, but this turns into an operational nightmare, is very costly, and still does not give you a truly fitting solution. You essentially make do with the RDBMS for lack of an alternative.

##### Sharding
The term sharding describes the logical separation of records into horizontal partitions. The idea is to spread data across multiple storage files—or servers—as opposed to having each stored contiguously. The separation of values into those partitions is performed on fixed boundaries: you have to set fixed rules ahead of time to route values to their appropriate store. With it comes the inherent difficulty of having to reshard the data when one of the horizontal partitions exceeds its capacity. 

Resharding is a very costly operation, since the storage layout has to be rewritten. This entails defining new boundaries and then horizontally splitting the rows across them. Massive copy operations can take a huge toll on I/O performance as well as temporarily elevated storage requirements. And you may still take on updates from the client applications and need to negotiate updates during the resharding process. This can be mitigated by using __virtual shards__, which define a much larger key partitioning range, with each server assigned an equal number of these shards. When you add more servers, you can reassign shards to the new server. This still requires that the data be moved over to the added server. Sharding is often a simple afterthought or is completely left to the operator. Without proper support from the database system, this can wreak havoc on production systems.

# Nonrelational Database Systems, Not-Only SQL or NoSQL?

##### Consistency Models

It seems fitting to talk about consistency a bit more since it is mentioned often throughout this book. On the outset, consistency is about guaranteeing that a database always appears truthful to its clients. Every operation on the database must carry its state from one consistent state to the next. How this is achieved or implemented is not specified explicitly so that a system has multiple choices. In the end, it has to get to the next consistent state, or return to the previous consistent state, to fulfill its obligation. Consistency can be classified in, for example, decreasing order of its properties, or guarantees offered to clients. Here is an informal list:

* Strict : The changes to the data are atomic and appear to take effect instantaneously. This is the highest form of consistency.   
* Sequential : Every client sees all changes in the same order they were applied.    
* Causal : All changes that are causally related are observed in the same order by all clients.    
* Eventual : When no updates occur for a period of time, eventually all updates will propagate through the system and all replicas will be consistent.    
* Weak : No guarantee is made that all updates will propagate and changes may appear out of order to various clients.   

The class of system adhering to eventual consistency can be even further divided into subtler sets, where those sets can also coexist. Werner Vogels, CTO of Amazon, lists them in his post titled 揈ventually Consistent? The article also picks up on the topic of the CAP theorem,* which states that a distributed system can only achieve two out of the following three properties: consistency, availability, and partition tolerance. The CAP theorem is a highly discussed topic, and is certainly not the only way to classify, but it does point out that distributed systems are not easy to develop given certain requirements. Vogels, for example, mentions:

> An important observation is that in larger distributed scale systems, network partitions are a given and as such consistency and availability cannot be achieved at the same time. This means that one has two choices on what to drop; relaxing consistency will allow the system to remain highly available [...] and prioritizing consistency means that under certain conditions the system will not be available.

Relaxing consistency, while at the same time gaining availability, is a powerful proposition. However, it can force handling inconsistencies into the application layer and may increase complexity.

### Dimensions

##### Data model

There are many variations in how the data is stored, which include key/value stores (compare to a HashMap), semistructured, column-oriented stores, and documentoriented stores. How is your application accessing the data? Can the schema evolve over time?

##### Storage model

In-memory or persistent? This is fairly easy to decide since we are comparing with RDBMSes, which usually persist their data to permanent storage, such as physical disks. But you may explicitly need a purely in-memory solution, and there are choices for that too. As far as persistent storage is concerned, does this affect your access pattern in any way?

##### Consistency model

Strictly or eventually consistent? The question is, how does the storage system achieve its goals: does it have to weaken the consistency guarantees? While this seems like a cursory question, it can make all the difference in certain use cases. It may especially affect latency, that is, how fast the system can respond to read and write requests. This is often measured in harvest and yield.†

##### Physical model

Distributed or single machine? What does the architecture look like—is it built from distributed machines or does it only run on single machines with the distribution handled client-side, that is, in your own code? Maybe the distribution is only an afterthought and could cause problems once you need to scale the system. And if it does offer scalability, does it imply specific steps to do so? The easiest solution would be to add one machine at a time, while sharded setups (especially those not supporting virtual shards) sometimes require for each shard to be increased simultaneously because each partition needs to be equally powerful.

##### Read/write performance

You have to understand what your application抯 access patterns look like. Are you designing something that is written to a few times, but is read much more often? Or are you expecting an equal load between reads and writes? Or are you taking in a lot of writes and just a few reads? Does it support range scans or is it better suited doing random reads? Some of the available systems are advantageous for only one of these operations, while others may do well in all of them.

##### Secondary indexes

Secondary indexes allow you to sort and access tables based on different fields and sorting orders. The options here range from systems that have absolutely no secondary indexes and no guaranteed sorting order (like a HashMap, i.e., you need to know the keys) to some that weakly support them, all the way to those that offer them out of the box. Can your application cope, or emulate, if this feature is missing?

##### Failure handling

It is a fact that machines crash, and you need to have a mitigation plan in place that addresses machine failures. How does each data store handle server failures? Is it able to continue operating? This is related to the “Consistency model” dimension discussed earlier, as losing a machine may cause holes in your data store, or even worse, make it completely unavailable. And if you are replacing the server, how easy will it be to get back to being 100% operational? Another scenario is decommissioning a server in a clustered setup, which would most likely be handled the same way.

##### Compression

When you have to store terabytes of data, especially of the kind that consists of prose or human-readable text, it is advantageous to be able to compress the data to gain substantial savings in required raw storage. Some compression algorithms can achieve a 10:1 reduction in storage space needed. Is the compression method pluggable? What types are available?

##### Load balancing

Given that you have a high read or write rate, you may want to invest in a storage system that transparently balances itself while the load shifts over time. It may not be the full answer to your problems, but it may help you to ease into a highthroughput application design.

##### Atomic read-modify-write

While RDBMSes offer you a lot of these operations directly (because you are talking to a central, single server), they can be more difficult to achieve in distributed systems. They allow you to prevent race conditions in multithreaded or sharednothing application server design. Having these compare and swap (CAS) or check and set operations available can reduce client-side complexity.

##### Locking, waits, and deadlocks

It is a known fact that complex transactional processing, like two-phase commits, can increase the possibility of multiple clients waiting for a resource to become available. In a worst-case scenario, this can lead to deadlocks, which are hard to resolve. What kind of locking model does the system you are looking at support? Can it be free of waits, and therefore deadlocks?

### Scalability

While the performance of RDBMSes is well suited for transactional processing, it is less so for very large-scale analytical processing. This refers to very large queries that scan wide ranges of records or entire tables. Analytical databases may contain hundreds or thousands of terabytes, causing queries to exceed what can be done on a single server in a reasonable amount of time. Scaling that server vertically—that is, adding more cores or disks—is simply not good enough.

What is even worse is that with RDBMSes, waits and deadlocks are increasing nonlinearly with the size of the transactions and concurrency—that is, the square of concurrency and the third or even fifth power of the transaction size.‡ Sharding is often an impractical solution, as it has to be done within the application layer, and may involve complex and costly (re)partitioning procedures.

Commercial RDBMSes are available that solve many of these issues, but they are often specialized and only cover certain aspects. Above all, they are very, very expensive. Looking at open source alternatives in the RDBMS space, you will likely have to give up many or all relational features, such as secondary indexes, to gain some level of performance.

The question is, wouldn't it be good to trade relational features permanently for performance? You could denormalize (see the next section) the data model and avoid waits and deadlocks by minimizing necessary locking. How about built-in horizontal scalability without the need to repartition as your data grows? Finally, throw in fault tolerance and data availability, using the same mechanisms that allow scalability, and what you get is a NoSQL solution梞ore specifically, one that matches what HBase has to offer.

### Database (De-)Normalization

At scale, it is often a requirement that we design schema differently, and a good term to describe this principle is Denormalization, Duplication, and Intelligent Keys (DDI). It is about rethinking how data is stored in Bigtable-like storage systems, and how to make use of it in an appropriate way.

Part of the principle is to denormalize schemas by, for example, duplicating data in more than one table so that, at read time, no further aggregation is required. Or the related prematerialization of required views, once again optimizing for fast reads without any further processing.

Consider the HBase URL Shortener, Hush, which allows us to map long URLs to short URLs. The entity relationship diagram (ERD) can be seen

![alt](https://www.safaribooksonline.com/library/view/hbase-the-definitive/9781449314682/httpatomoreillycomsourceoreillyimages889230.png)


How the same schema could be represented in HBase.
![alt](https://www.safaribooksonline.com/library/view/hbase-the-definitive/9781449314682/httpatomoreillycomsourceoreillyimages889232.png)

# Building Blocks














































































