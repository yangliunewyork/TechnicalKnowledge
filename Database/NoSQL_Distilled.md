# Chapter 1. Why NoSQL?

## 1.1. The Value of Relational Databases

### 1.1.1. Getting at Persistent Data

__Probably the most obvious value of a database is keeping large amounts of persistent data.__ Most computer architectures have the notion of two areas of memory: a fast volatile “main memory” and a larger but slower “backing store.” Main memory is both limited in space and loses all data when you lose power or something bad happens to the operating system. Therefore, to keep data around, we write it to a backing store, commonly seen a disk (although these days that disk can be persistent memory).

The backing store can be organized in all sorts of ways. For many productivity applications (such as word processors), it’s a file in the file system of the operating system. For most enterprise applications, however, the backing store is a database. The database allows more flexibility than a file system in storing large amounts of data in a way that allows an application program to get at small bits of that information quickly and easily.

### 1.1.2. Concurrency

Enterprise applications tend to have many people looking at the same body of data at once, possibly modifying that data. Most of the time they are working on different areas of that data, but occasionally they operate on the same bit of data. As a result, we have to worry about coordinating these interactions to avoid such things as double booking of hotel rooms.

Concurrency is notoriously difficult to get right, with all sorts of errors that can trap even the most careful programmers. Since enterprise applications can have lots of users and other systems all working concurrently, there’s a lot of room for bad things to happen. Relational databases help handle this by controlling all access to their data through transactions. While this isn’t a cure-all (you still have to handle a transactional error when you try to book a room that’s just gone), the transactional mechanism has worked well to contain the complexity of concurrency.

Transactions also play a role in error handling. With transactions, you can make a change, and if an error occurs during the processing of the change you can roll back the transaction to clean things up.

### 1.1.3. Integration

Enterprise applications live in a rich ecosystem that requires multiple applications, written by different teams, to collaborate in order to get things done. This kind of inter-application collaboration is awkward because it means pushing the human organizational boundaries. Applications often need to use the same data and updates made through one application have to be visible to others.

A common way to do this is shared database integration where multiple applications store their data in a single database. Using a single database allows all the applications to use each others’ data easily, while the database’s concurrency control handles multiple applications in the same way as it handles multiple users in a single application.

### 1.1.4. A (Mostly) Standard Model

Relational databases have succeeded because they provide the core benefits we outlined earlier in a (mostly) standard way. As a result, developers and database professionals can learn the basic relational model and apply it in many projects. Although there are differences between different relational databases, the core mechanisms remain the same: Different vendors’ SQL dialects are similar, transactions operate in mostly the same way.

## 1.2. Impedance Mismatch

For application developers, the biggest frustration has been what’s commonly called the __impedance mismatch__: the difference between the relational model and the in-memory data structures. The relational data model organizes data into a structure of tables and rows, or more properly, relations and tuples. In the relational model, a tuple is a set of name-value pairs and a relation is a set of tuples. (The relational definition of a tuple is slightly different from that in mathematics and many programming languages with a tuple data type, where a tuple is a sequence of values.) All operations in SQL consume and return relations, which leads to the mathematically elegant relational algebra.

This foundation on relations provides a certain elegance and simplicity, but it also introduces limitations. In particular, the values in a relational tuple have to be simple—they cannot contain any structure, such as a nested record or a list. This limitation isn’t true for in-memory data structures, which can take on much richer structures than relations. As a result, if you want to use a richer in-memory data structure, you have to translate it to a relational representation to store it on disk. Hence the impedance mismatch—two different representations that require translation.

## 1.3. Application andIntegration Databases

The exact reasons why relational databases triumphed over OO databases are still the subject of an occasional pub debate for developers of a certain age. But in our view, the primary factor was the role of SQL as an integration mechanism between applications. In this scenario, the database acts as an __integration database__—with multiple applications, usually developed by separate teams, storing their data in a common database. This improves communication because all the applications are operating on a consistent set of persistent data.

## 1.4. Attack of the Clusters

As large properties moved towards clusters, that revealed a new problem— relational databases are not designed to be run on clusters. Clustered relational databases, such as the Oracle RAC or Microsoft SQL Server, work on the concept of a shared disk subsystem. They use a cluster-aware file system that writes to a highly available disk subsystem—but this means the cluster still has the disk subsystem as a single point of failure. Relational databases could also be run as separate servers for different sets of data, effectively sharding the database. While this separates the load, all the sharding has to be controlled by the application which has to keep track of which database server to talk to for each bit of data. Also, we lose any querying, referential integrity, transactions, or consistency controls that cross shards.

 As the 2000s drew on, both companies produced brief but highly influential papers about their efforts: BigTable from Google and Dynamo from Amazon.
 
 ## 1.5. The Emergence of NoSQL
 
 The “ not-only” interpretation does have its value, as it describes the ecosystem that many people think is the future of databases. This is in fact what we consider to be the most important contribution of this way of thinking—it’s better to think of NoSQL as a movement rather than a technology. We don’t think that relational databases are going away—they are still going to be the most common form of database in use. Even though we’ve written this book, we still recommend relational databases. Their familiarity, stability, feature set, and available support are compelling arguments for most projects.
 
 ## 1.6. Key Points
 
* Relational databases have been a successful technology for twenty years, providing persistence, concurrency control, and an integration mechanism.
* Application developers have been frustrated with the impedance mismatch between the relational model and the in-memory data structures.
* There is a movement away from using databases as integration points towards encapsulating databases within applications and integrating through services.
* The vital factor for a change in data storage was the need to support large volumes of data by running on clusters. Relational databases are not designed to run efficiently on clusters.
* NoSQL is an accidental neologism. There is no prescriptive definition— all you can make is an observation of common characteristics.
* The common characteristics of NoSQL databases are 
  * Not using the relational model
  * Running well on clusters
  * Open-source
  * Built for the 21st century web estates
  * Schemaless
*  The most important result of the rise of NoSQL is Polyglot Persistence.

# Chapter 2. Aggregate Data Models












