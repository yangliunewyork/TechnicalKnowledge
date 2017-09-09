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

A data model is the model through which we perceive and manipulate our data. For people using a database, the data model describes how we interact with the data in the database. This is distinct from a storage model, which describes how the database stores and manipulates the data internally.


The dominant data model of the last couple of decades is the relational data model, which is best visualized as a set of tables, rather like a page of a spreadsheet. Each table has rows, with each row representing some entity of interest. We describe this entity through columns, each having a single value. A column may refer to another row in the same or different table, which constitutes a relationship between those entities.

One of the most obvious shifts with NoSQL is a move away from the relational model. Each NoSQL solution has a different model that it uses, which we put into four categories widely used in the NoSQL ecosystem: key-value, document, column-family, and graph. Of these, the first three share a common characteristic of their data models which we will call aggregate orientation.

## 2.1. Aggregates

The relational model takes the information that we want to store and divides it into tuples (rows). A tuple is a limited data structure: It captures a set of values, so you cannot nest one tuple within another to get nested records, nor can you put a list of values or tuples within another. This simplicity underpins the relational model—it allows us to think of all operations as operating on and returning tuples.

Aggregate orientation takes a different approach. It recognizes that often, you want to operate on data in units that have a more complex structure than a set of tuples. It can be handy to think in terms of a complex record that allows lists and other record structures to be nested inside it. As we’ll see, key-value, document, and column-family databases all make use of this more complex record.

Aggregate is a term that comes from Domain-Driven Design. In Domain-Driven Design, an aggregate is a collection of related objects that we wish to treat as a unit. In particular, it is a unit for data manipulation and management of consistency. Typically, we like to update aggregates with atomic operations and communicate with our data storage in terms of aggregates. This definition matches really well with how key-value, document, and column-family databases work. Dealing in aggregates makes it much easier for these databases to handle operating on a cluster, since the aggregate makes a natural unit for replication and sharding. Aggregates are also often easier for application programmers to work with, since they often manipulate data through aggregate structures.

### 2.1.2. Consequences of Aggregate Orientation

Various data modeling techniques have provided ways of marking aggregate or composite structures. The problem, however, is that modelers rarely provide any semantics for what makes an aggregate relationship different from any other; where there are semantics, they vary. When working with aggregate-oriented databases, we have a clearer semantics to consider by focusing on the unit of interaction with the data storage. __It is, however, not a logical data property: It’s all about how the data is being used by applications—a concern that is often outside the bounds of data modeling.__

Relational databases have no concept of aggregate within their data model, so we call them __aggregate-ignorant__. In the NoSQL world, graph databases are also aggregate-ignorant. Being aggregate-ignorant is not a bad thing. It’s often difficult to draw aggregate boundaries well, particularly if the same data is used in many different contexts. An order makes a good aggregate when a customer is making and reviewing orders, and when the retailer is processing orders. However, if a retailer wants to analyze its product sales over the last few months, then an order aggregate becomes a trouble. To get to product sales history, you’ll have to dig into every aggregate in the database. So an aggregate structure may help with some data interactions but be an obstacle for others. An aggregate-ignorant model allows you to easily look at the data in different ways, so it is a better choice when you don’t have a primary structure for manipulating your data.


Aggregates have an important consequence for transactions. Relational databases allow you to manipulate any combination of rows from any tables in a single transaction. Such transactions are called ACID transactions: Atomic, Consistent, Isolated, and Durable. ACID is a rather contrived acronym; the real point is the atomicity: Many rows spanning many tables are updated as a single operation. This operation either succeeds or fails in its entirety, and concurrent operations are isolated from each other so they cannot see a partial update.

## 2.2. Key-Value and Document Data Models
We said earlier on that key-value and document databases were strongly aggregate- oriented. What we meant by this was that we think of these databases as primarily constructed through aggregates. Both of these types of databases consist of lots of aggregates with each aggregate having a key or ID that’s used to get at the data.

The two models differ in that in a key-value database, the aggregate is opaque to the database—just some big blob of mostly meaningless bits. In contrast, a document database is able to see a structure in the aggregate. The advantage of opacity is that we can store whatever we like in the aggregate. The database may impose some general size limit, but other than that we have complete freedom. A document database imposes limits on what we can place in it, defining allowable structures and types. In return, however, we get more flexibility in access.

With a key-value store, we can only access an aggregate by lookup based on its key. With a document database, we can submit queries to the database based on the fields in the aggregate, we can retrieve part of the aggregate rather than the whole thing, and database can create indexes based on the contents of the aggregate.


In practice, the line between key-value and document gets a bit blurry. People often put an ID field in a document database to do a key-value style lookup. Databases classified as key-value databases may allow you structures for data beyond just an opaque aggregate. 

Despite this blurriness, the general distinction still holds. With key-value databases, we expect to mostly look up aggregates using a key. With document databases, we mostly expect to submit some form of query based on the internal structure of the document; this might be a key, but it’s more likely to be something else.

## 2.3. Column-Family Stores

One of the early and influential NoSQL databases was Google’s BigTable. Its name conjured up a tabular structure which it realized with sparse columns and no schema. As you’ll soon see, it doesn’t help to think of this structure as a table; rather, it is a two-level map. But, however you think about the structure, it has been a model that influenced later databases such as HBase and Cassandra.

## 2.4. Summarizing Aggregate-OrientedDatabases


What they all share is the notion of an aggregate indexed by a key that you can use for lookup. This aggregate is central to running on a cluster, as the database will ensure that all the data for an aggregate is stored together on one node. The aggregate also acts as the atomic unit for updates, providing a useful, if limited, amount of transactional control.

Within that notion of aggregate, we have some differences. The key-value data model treats the aggregate as an opaque whole, which means you can only do key lookup for the whole aggregate—you cannot run a query nor retrieve a part of the aggregate.
The document model makes the aggregate transparent to the database allowing you to do queries and partial retrievals.

However, since the document has no schema, the database cannot act much on the structure of the document to optimize the storage and retrieval of parts of the aggregate.

Column-family models divide the aggregate into column families, allowing the database to treat them as units of data within the row aggregate. This imposes some structure on the aggregate but allows the database to take advantage of that structure to improve its accessibility.

## 2.6. Key Points

* An aggregate is a collection of data that we interact with as a unit. Aggregates form the boundaries for ACID operations with the database.
* Key-value, document, and column-family databases can all be seen as forms of aggregate-oriented database.
* Aggregates make it easier for the database to manage data storage over clusters.
* Aggregate-oriented databases work best when most data interaction is done with the same aggregate; aggregate-ignorant databases are better when interactions use data organized in many different formations.

# Chapter 3. More Details on Data Models

## 3.1. Relationships

An important aspect of relationships between aggregates is how they handle updates. Aggregate-oriented databases treat the aggregate as the unit of data- retrieval. Consequently, atomicity is only supported within the contents of a single aggregate. If you update multiple aggregates at once, you have to deal yourself with a failure partway through. Relational databases help you with this by allowing you to modify multiple records in a single transaction, providing ACID guarantees while altering many rows.

All of this means that aggregate-oriented databases become more awkward as you need to operate across multiple aggregates. There are various ways to deal with this,  but the fundamental awkwardness remains.This may imply that if you have data based on lots of relationships, you should prefer a relational database over a NoSQL store. While that’s true for aggregate-oriented databases, it’s worth remembering that relational databases aren’t all that stellar with complex relationships either. While you can express queries involving joins in SQL, things quickly get very hairy—both with SQL writing and with the resulting performance—as the number of joins mounts up.This makes it a good moment to introduce another category of databases that’s often lumped into the NoSQL pile.

## 3.2. Graph Databases

Graph databases are an odd fish in the NoSQL pond. Most NoSQL databases were inspired by the need to run on clusters, which led to aggregate-oriented data models of large records with simple connections. Graph databases are motivated by a different frustration with relational databases and thus have an opposite model— small records with complex interconnections.


Graph databases specialize in capturing this sort of information—but on a much larger scale than a readable diagram could capture. This is ideal for capturing any data consisting of complex relationships such as social networks, product preferences, or eligibility rules.

The fundamental data model of a graph database is very simple: nodes connected by edges (also called arcs). Beyond this essential characteristic there is a lot of variation in data models—in particular, what mechanisms you have to store data in your nodes and edges.

Once you have built up a graph of nodes and edges, a graph database allows you to query that network with query operations designed with this kind of graph in mind. This is where the important differences between graph and relational databases come in. Although relational databases can implement relationships using foreign keys, the joins required to navigate around can get quite expensive— which means performance is often poor for highly connected data models. Graph databases make traversal along the relationships very cheap. A large part of this is because graph databases shift most of the work of navigating relationships from query time to insert time. This naturally pays off for situations where querying performance is more important than insert speed.

The emphasis on relationships makes graph databases very different from aggregate-oriented databases. This data model difference has consequences in other aspects, too; you’ll find such databases are more likely to run on a single server rather than distributed across clusters. ACID transactions need to cover multiple nodes and edges to maintain consistency. The only thing they have in common with aggregate-oriented databases is their rejection of the relational model and an upsurge in attention they received around the same time as the rest of the NoSQL field.

## 3.3. Schemaless Databases

A common theme across all the forms of NoSQL databases is that they are schemaless. When you want to store data in a relational database, you first have to define a schema—a defined structure for the database which says what tables exist, which columns exist, and what data types each column can hold. Before you store some data, you have to have the schema defined for it.

With NoSQL databases, storing data is much more casual. A key-value store allows you to store any data you like under a key. A document database effectively does the same thing, since it makes no restrictions on the structure of the documents you store. Column-family databases allow you to store any data under any column you like. Graph databases allow you to freely add new edges and freely add properties to nodes and edges as you wish.

dvocates of schemalessness rejoice in this freedom and flexibility. With a schema, you have to figure out in advance what you need to store, but that can be hard to do. Without a schema binding you, you can easily store whatever you need. This allows you to easily change your data storage as you learn more about your project. You can easily add new things as you discover them. Furthermore, if you find you don’t need some things anymore, you can just stop storing them, without worrying about losing old data as you would if you delete columns in a relational schema.

As well as handling changes, a schemaless store also makes it easier to deal with __nonuniform data: data where each record has a different set of fields__. A schema puts all rows of a table into a straightjacket, which becomes awkward if you have different kinds of data in different rows. You either end up with lots of columns that are usually null (a sparse table), or you end up with meaningless columns. Schemalessness avoids this, allowing each record to contain just what it needs—no more, no less.


The vital, if sometimes inconvenient, fact is that whenever we write a program that accesses data, that program almost always relies on some form of implicit schema. So, however schemaless our database is, there is usually an implicit schema present. __This implicit schema is a set of assumptions about the data’s structure in the code that manipulates the data.__

Having the implicit schema in the application code results in some problems. It means that in order to understand what data is present you have to dig into the application code. If that code is well structured you should be able to find a clear place from which to deduce the schema. But there are no guarantees; it all depends on how clear the application code is. Furthermore, the database remains ignorant of the schema—it can’t use the schema to help it decide how to store and retrieve data efficiently. It can’t apply its own validations upon that data to ensure that different applications don’t manipulate data in an inconsistent way.

Essentially, a schemaless database shifts the schema into the application code that accesses it. This becomes problematic if multiple applications, developed by different people, access the same database. These problems can be reduced with a couple of approaches. One is to encapsulate all database interaction within a single application and integrate it with other applications using web services. This fits in well with many people’s current preference for using web services for integration. Another approach is to clearly delineate different areas of an aggregate for access by different applications. These could be different sections in a document database or different column families an a column-family database.

## 3.4. Materialized Views

When we talked about aggregate-oriented data models, we stressed their advantages. If you want to access orders, it’s useful to have all the data for an order contained in a single aggregate that can be stored and accessed as a unit. But aggregate-orientation has a corresponding disadvantage: What happens if a product manager wants to know how much a particular item has sold over the last couple of weeks? Now the aggregate-orientation works against you, forcing you to potentially read every order in the database to answer the question. You can reduce this burden by building an index on the product, but you’re still working against the aggregate structure.

Relational databases have an advantage here because their lack of aggregate structure allows them to support accessing data in different ways. Furthermore, they provide a convenient mechanism that allows you to look at data differently from the way it’s stored—views. A view is like a relational table (it is a relation) but it’s defined by computation over the base tables. When you access a view, the database computes the data in the view—a handy form of encapsulation.

Views provide a mechanism to hide from the client whether data is derived data or base data—but can’t avoid the fact that some views are expensive to compute. To cope with this, __materialized views__ were invented, which are views that are computed in advance and cached on disk. Materialized views are effective for data that is read heavily but can stand being somewhat stale.

Although NoSQL databases don’t have views, they may have precomputed and cached queries, and they reuse the term “ materialized view” to describe them. It’s also much more of a central aspect for aggregate-oriented databases than it is for relational systems, since most applications will have to deal with some queries that don’t fit well with the aggregate structure. 

There are two rough strategies to building a materialized view. The first is the eager approach where you update the materialized view at the same time you update the base data for it. In this case, adding an order would also update the purchase history aggregates for each product. This approach is good when you have more frequent reads of the materialized view than you have writes and you want the materialized views to be as fresh as possible. The application database approach is valuable here as it makes it easier to ensure that any updates to base data also update materialized views.

If you don’t want to pay that overhead on each update, you can run batch jobs to update the materialized views at regular intervals. You’ll need to understand your business requirements to assess how stale your materialized views can be.

You can build materialized views outside of the database by reading the data, computing the view, and saving it back to the database. More often databases will support building materialized views themselves. In this case, you provide the computation that needs to be done, and the database executes the computation when needed according to some parameters that you configure.

Materialized views can be used within the same aggregate. An order document might include an order summary element that provides summary information about the order so that a query for an order summary does not have to transfer the entire order document. Using different column families for materialized views is a common feature of column-family databases. An advantage of doing this is that it allows you to update the materialized view within the same atomic operation.

## 3.6. Key Points

*  Aggregate-oriented databases make inter-aggregate relationships more difficult to handle than intra-aggregate relationships.
* Graph databases organize data into node and edge graphs; they work best for data that has complex relationship structures.
* Schemaless databases allow you to freely add fields to records, but there is usually an implicit schema expected by users of the data.
*  Aggregate-oriented databases often compute materialized views to provide data organized differently from their primary aggregates. This is often done with map-reduce computations.

# Chapter 4. Distribution Models
The primary driver of interest in NoSQL has been its ability to run databases on a large cluster. As data volumes increase, it becomes more difficult and expensive to scale up—buy a bigger server to run the database on. A more appealing option is to scale out—run the database on a cluster of servers. Aggregate orientation fits well with scaling out because the aggregate is a natural unit to use for distribution.

Depending on your distribution model, you can get a data store that will give you the ability to handle larger quantities of data, the ability to process a greater read or write traffic, or more availability in the face of network slowdowns or breakages. These are often important benefits, but they come at a cost. Running over a cluster introduces complexity—so it’s not something to do unless the benefits are compelling.

Broadly, there are two paths to data distribution: replication and sharding. Replication takes the same data and copies it over multiple nodes. Sharding puts different data on different nodes. Replication and sharding are orthogonal techniques: You can use either or both of them. Replication comes into two forms: master-slave and peer-to-peer. 

## 4.1. Single Server
The first and the simplest distribution option is the one we would most often recommend—no distribution at all. Run the database on a single machine that handles all the reads and writes to the data store. We prefer this option because it eliminates all the complexities that the other options introduce; it’s easy for operations people to manage and easy for application developers to reason about.

Although a lot of NoSQL databases are designed around the idea of running on a cluster, it can make sense to use NoSQL with a single-server distribution model if the data model of the NoSQL store is more suited to the application. Graph databases are the obvious category here—these work best in a single-server configuration. If your data usage is mostly about processing aggregates, then a single-server document or key-value store may well be worthwhile because it’s easier on application developers.

## 4.2. Sharding

Often, a busy data store is busy because different people are accessing different parts of the dataset. In these circumstances we can support horizontal scalability by putting different parts of the data onto different servers—a technique that’s called __sharding__.

![alt](http://images.slideplayer.com/25/7721050/slides/slide_13.jpg)

In the ideal case, we have different users all talking to different server nodes. Each user only has to talk to one server, so gets rapid responses from that server. The load is balanced out nicely between servers—for example, if we have ten servers, each one only has to handle 10% of the load.

Of course the ideal case is a pretty rare beast. In order to get close to it we have to ensure that data that’s accessed together is clumped together on the same node and that these clumps are arranged on the nodes to provide the best data access.

The first part of this question is how to clump the data up so that one user mostly gets her data from a single server. This is where aggregate orientation comes in really handy. The whole point of aggregates is that we design them to combine data that’s commonly accessed together—so aggregates leap out as an obvious unit of distribution.

When it comes to arranging the data on the nodes, there are several factors that can help improve performance. If you know that most accesses of certain aggregates are based on a physical location, you can place the data close to where it’s being accessed. If you have orders for someone who lives in Boston, you can place that data in your eastern US data center.

Another factor is trying to keep the load even. This means that you should try to arrange aggregates so they are evenly distributed across the nodes which all get equal amounts of the load. This may vary over time, for example if some data tends to be accessed on certain days of the week—so there may be domain-specific rules you’d like to use.

In some cases, it’s useful to put aggregates together if you think they may be read in sequence. The Bigtable paper  described keeping its rows in lexicographic order and sorting web addresses based on reversed domain names (e.g., com.martinfowler). This way data for multiple pages could be accessed together to improve processing efficiency.

Many NoSQL databases offer __auto-sharding__, where the database takes on the responsibility of allocating data to shards and ensuring that data access goes to the right shard. This can make it much easier to use sharding in an application.

__Sharding is particularly valuable for performance because it can improve both read and write performance. Using replication, particularly with caching, can greatly improve read performance but does little for applications that have a lot of writes. Sharding provides a way to horizontally scale writes.__

Sharding does little to improve resilience when used alone. Although the data is on different nodes, a node failure makes that shard’s data unavailable just as surely as it does for a single-server solution. The resilience benefit it does provide is that only the users of the data on that shard will suffer; however, it’s not good to have a database with part of its data missing. With a single server it’s easier to pay the effort and cost to keep that server up and running; clusters usually try to use less reliable machines, and you’re more likely to get a node failure. So in practice, sharding alone is likely to decrease resilience.

In any case the step from a single node to sharding is going to be tricky. We have heard tales of teams getting into trouble because they left sharding to very late, so when they turned it on in production their database became essentially unavailable because the sharding support consumed all the database resources for moving the data onto new shards. The lesson here is to use sharding well before you need to—when you have enough headroom to carry out the sharding.

## 4.3. Master-Slave Replication

With master-slave distribution, you replicate data across multiple nodes. One node is designated as the master, or primary. This master is the authoritative source for the data and is usually responsible for processing any updates to that data. The other nodes are slaves, or secondaries. A replication process synchronizes the slaves with the master.

![alt](http://sungsoo.github.io/images/master-to-slaves.png)

Master-slave replication is most helpful for scaling when you have a read- intensive dataset. You can scale horizontally to handle more read requests by adding more slave nodes and ensuring that all read requests are routed to the slaves. You are still, however, limited by the ability of the master to process updates and its ability to pass those updates on. Consequently it isn’t such a good scheme for datasets with heavy write traffic, although offloading the read traffic will help a bit with handling the write load.


A second advantage of master-slave replication is __read resilience__: Should the master fail, the slaves can still handle read requests. Again, this is useful if most of your data access is reads. The failure of the master does eliminate the ability to handle writes until either the master is restored or a new master is appointed. However, having slaves as replicates of the master does speed up recovery after a failure of the master since a slave can be appointed a new master very quickly.

Masters can be appointed manually or automatically. Manual appointing typically means that when you configure your cluster, you configure one node as the master. With automatic appointment, you create a cluster of nodes and they elect one of themselves to be the master. Apart from simpler configuration, automatic appointment means that the cluster can automatically appoint a new master when a master fails, reducing downtime.


In order to get read resilience, you need to ensure that the read and write paths into your application are different, so that you can handle a failure in the write path and still read. This includes such things as putting the reads and writes through separate database connections—a facility that is not often supported by database interaction libraries. As with any feature, you cannot be sure you have read resilience without good tests that disable the writes and check that reads still occur.

Replication comes with some alluring benefits, but it also comes with an inevitable dark side—inconsistency. You have the danger that different clients, reading different slaves, will see different values because the changes haven’t all propagated to the slaves. In the worst case, that can mean that a client cannot read a write it just made. Even if you use master-slave replication just for hot backup this can be a concern, because if the master fails, any updates not passed on to the backup are lost. 

## 4.4. Peer-to-Peer Replication

Master-slave replication helps with read scalability but doesn’t help with scalability of writes. It provides resilience against failure of a slave, but not of a master. Essentially, the master is still a bottleneck and a single point of failure. Peer-to-peer replication attacks these problems by not having a master. All the replicas have equal weight, they can all accept writes, and the loss of any of them doesn’t prevent access to the data store.

![alt](http://sungsoo.github.io/images/peer-to-peer-replication.png)

The prospect here looks mighty fine. With a peer-to-peer replication cluster, you can ride over node failures without losing access to data. Furthermore, you can easily add nodes to improve your performance. There’s much to like here—but there are complications.

The biggest complication is, again, consistency. When you can write to two different places, you run the risk that two people will attempt to update the same record at the same time—a write-write conflict. Inconsistencies on read lead to problems but at least they are relatively transient. Inconsistent writes are forever.

## 4.6. Key Points

There are two styles of distributing data:
* Sharding distributes different data across multiple servers, so each server acts as the single source for a subset of data.
* Replication copies data across multiple servers, so each bit of data can be found in multiple places.  

A system may use either or both techniques.


Replication comes in two forms:
* Master-slave replication makes one node the authoritative copy that handles writes while slaves synchronize with the master and may handle reads.
* Peer-to-peer replication allows writes to any node; the nodes coordinate to synchronize their copies of the data.

Master-slave replication reduces the chance of update conflicts but peer- to-peer replication avoids loading all writes onto a single point of failure.

# Chapter 5. Consistency

One of the biggest changes from a centralized relational database to a cluster- oriented NoSQL database is in how you think about consistency. Relational databases try to exhibit __strong consistency__ by avoiding all the various inconsistencies that we’ll shortly be discussing. Once you start looking at the NoSQL world, phrases such as “ CAP theorem” and “ eventual consistency” appear, and as soon as you start building something you have to think about what sort of consistency you need for your system.

## 5.1. Update Consistency

Approaches for maintaining consistency in the face of concurrency are often described as __pessimistic__ or __optimistic__. A pessimistic approach works by preventing conflicts from occurring; an optimistic approach lets conflicts occur, but detects them and takes action to sort them out. For update conflicts, the most common pessimistic approach is to have write locks, so that in order to change a value you need to acquire a lock, and the system ensures that only one client can get a lock at a time. 

A common optimistic approach is a __conditional update__ where any client that does an update tests the value just before updating it to see if it’s changed since his last read.

Both the pessimistic and optimistic approaches that we’ve just described rely on a consistent serialization of the updates. With a single server, this is obvious— it has to choose one, then the other. But if there’s more than one server, such as with peer-to-peer replication, then two nodes might apply the updates in a different order, resulting in a different value for the telephone number on each peer. Often, when people talk about concurrency in distributed systems, they talk about sequential consistency—ensuring that all nodes apply operations in the same order.


There is another optimistic way to handle a write-write conflict—save both updates and record that they are in conflict. This approach is familiar to many programmers from version control systems, particularly distributed version control systems that by their nature will often have conflicting commits. The next step again follows from version control: You have to merge the two updates somehow. Maybe you show both values to the user and ask them to sort it out—this is what happens if you update the same contact on your phone and your computer. Alternatively, the computer may be able to perform the merge itself; if it was a phone formatting issue, it may be able to realize that and apply the new number with the standard format. Any automated merge of write-write conflicts is highly domain-specific and needs to be programmed for each particular case.

Often, when people first encounter these issues, their reaction is to prefer pessimistic concurrency because they are determined to avoid conflicts. While in some cases this is the right answer, there is always a tradeoff. Concurrent programming involves a fundamental tradeoff between safety (avoiding errors such as update conflicts) and liveness (responding quickly to clients). Pessimistic approaches often severely degrade the responsiveness of a system to the degree that it becomes unfit for its purpose. This problem is made worse by the danger of errors—pessimistic concurrency often leads to deadlocks, which are hard to prevent and debug.

Replication makes it much more likely to run into write-write conflicts. If different nodes have different copies of some data which can be independently updated, then you’ll get conflicts unless you take specific measures to avoid them. Using a single node as the target for all writes for some data makes it much easier to maintain update consistency. Of the distribution models we discussed earlier, all but peer-to-peer replication do this.

# 5.2.ReadConsistency

A common claim we hear is that NoSQL databases don’t support transactions and thus can’t be consistent. Such claim is mostly wrong because it glosses over lots of important details. Our first clarification is that any statement about lack of transactions usually only applies to some NoSQL databases, in particular the aggregate-oriented ones. In contrast, graph databases tend to support ACID transactions just the same as relational databases.

In situations like this, you can tolerate reasonably long inconsistency windows, but you need read-your-writes consistency which means that, once you’ve made an update, you’re guaranteed to continue seeing that update. One way to get this in an otherwise eventually consistent system is to provide __session consistency__: Within a user’s session there is read-your-writes consistency. This does mean that the user may lose that consistency should their session end for some reason or should the user access the same system simultaneously from different computers, but these cases are relatively rare.


There are a couple of techniques to provide session consistency. A common way, and often the easiest way, is to have a __sticky session__ a session that’s tied to one node (this is also called __session affinity__). A sticky session allows you to ensure that as long as you keep read-your-writes consistency on a node, you’ll get it for sessions too. The downside is that sticky sessions reduce the ability of the load balancer to do its job.


Another approach for session consistency is to use version stamps (“ Version Stamps,”) and ensure every interaction with the data store includes the latest version stamp seen by a session. The server node must then ensure that it has the updates that include that version stamp before responding to a request.

Maintaining session consistency with sticky sessions and master-slave replication can be awkward if you want to read from the slaves to improve read performance but still need to write to the master. One way of handling this is for writes to be sent the slave, who then takes responsibility for forwarding them to the master while maintaining session consistency for its client. Another approach is to switch the session to the master temporarily when doing a write, just long enough that reads are done from the master until the slaves have caught up with the update.

## 5.3. Relaxing Consistency

Consistency is a Good Thing—but, sadly, sometimes we have to sacrifice it. It is always possible to design a system to avoid inconsistencies, but often impossible to do so without making unbearable sacrifices in other characteristics of the system. As a result, we often have to tradeoff consistency for something else. While some architects see this as a disaster, we see it as part of the inevitable tradeoffs involved in system design. Furthermore, different domains have different tolerances for inconsistency, and we need to take this tolerance into account as we make our decisions.

Trading off consistency is a familiar concept even in single-server relational database systems. Here, our principal tool to enforce consistency is the transaction, and transactions can provide strong consistency guarantees. However, transaction systems usually come with the ability to relax isolation levels, allowing queries to read data that hasn’t been committed yet, and in practice we see most applications relax consistency down from the highest isolation level (serialized) in order to get effective performance. We most commonly see people using the read-committed transaction level, which eliminates some read-write conflicts but allows others.

Many systems forgo transactions entirely because the performance impact of transactions is too high. We’ve seen this in a couple different ways. On a small scale, we saw the popularity of MySQL during the days when it didn’t support transactions. Many websites liked the high speed of MySQL and were prepared to live without transactions. At the other end of the scale, some very large websites, such as eBay, have had to forgo transactions in order to perform acceptably—this is particularly true when you need to introduce sharding. Even without these constraints, many application builders need to interact with remote systems that can’t be properly included within a transaction boundary, so updating outside of transactions is a quite common occurrence for enterprise applications.

### 5.3.1. The CAP Theorem

In the NoSQL world it’s common to refer to the CAP theorem as the reason why you may need to relax consistency. It was originally proposed by Eric Brewer in 2000  and given a formal proof by Seth Gilbert and Nancy Lynch a couple of years later.

The basic statement of the CAP theorem is that, given the three properties of Consistency, Availability, and Partition tolerance, you can only get two. Obviously this depends very much on how you define these three properties, and differing opinions have led to several debates on what the real consequences of the CAP theorem are.

Consistency is pretty much as we’ve defined it so far. Availability has a particular meaning in the context of CAP—it means that if you can talk to a node in the cluster, it can read and write data. That’s subtly different from the usual meaning. Partition tolerance means that the cluster can survive communication breakages in the cluster that separate the cluster into multiple partitions unable to communicate with each other (situation known as a __split brain__).

![alt](https://docs.voltdb.com/graphics/NetworkPartition.png)

A single-server system is the obvious example of a CA system—a system that has Consistency and Availability but not Partition tolerance. A single machine can’t partition, so it does not have to worry about partition tolerance. There’s only one node—so if it’s up, it’s available. Being up and keeping consistency is reasonable. This is the world that most relational database systems live in.

So clusters have to be tolerant of network partitions. And here is the real point of the CAP theorem. Although the CAP theorem is often stated as “ you can only get two out of three,” in practice what it’s saying is that in a system that may suffer partitions, as distributed system do, you have to trade off consistency versus availability. This isn’t a binary decision; often, you can trade off a little consistency to get some availability. The resulting system would be neither perfectly consistent nor perfectly available—but would have a combination that is reasonable for your particular needs.

Advocates of NoSQL often say that instead of following the ACID properties of relational transactions, NoSQL systems follow the BASE properties (Basically Available, Soft state, Eventual consistency). Although we feel we ought to mention the BASE acronym here, we don’t think it’s very useful. The acronym is even more contrived than ACID, and neither “ basically available” nor “ soft state” have been well defined. We should also stress that when Brewer introduced the notion of BASE, he saw the tradeoff between ACID and BASE as a spectrum, not a binary choice.

## 5.4. Relaxing Durability
As it turns out, there are cases where you may want to trade off some durability for higher performance. If a database can run mostly in memory, apply updates to its in-memory representation, and periodically flush changes to disk, then it may be able to provide substantially higher responsiveness to requests. The cost is that, should the server crash, any updates since the last flush will be lost.

One example of where this tradeoff may be worthwhile is storing user-session state. A big website may have many users and keep temporary information about what each user is doing in some kind of session state. There’s a lot of activity on this state, creating lots of demand, which affects the responsiveness of the website. The vital point is that losing the session data isn’t too much of a tragedy—it will create some annoyance, but maybe less than a slower website would cause. This makes it a good candidate for nondurable writes. Often, you can specify the durability needs on a call-by-call basis, so that more important updates can force a flush to disk.

Another class of durability tradeoffs comes up with replicated data. A failure of __replication durability__ occurs when a node processes an update but fails before that update is replicated to the other nodes. A simple case of this may happen if you have a master-slave distribution model where the slaves appoint a new master automatically should the existing master fail. If a master does fail, any writes not passed onto the replicas will effectively become lost. Should the master come back online, those updates will conflict with updates that have happened since. We think of this as a durability problem because you think your update has succeeded since the master acknowledged it, but a master node failure caused it to be lost.

## 5.5. Quorums
When you’re trading off consistency or durability, it’s not an all or nothing proposition. The more nodes you involve in a request, the higher is the chance of avoiding an inconsistency. This naturally leads to the question: How many nodes need to be involved to get strong consistency?

Imagine some data replicated over three nodes. You don’t need all nodes to acknowledge a write to ensure strong consistency; all you need is two of them—a majority. If you have conflicting writes, only one can get a majority. This is referred to as a __write quorum__ and expressed in a slightly pretentious inequality of ```W > N / 2``` , meaning the number of nodes participating in the write (W ) must be more than the half the number of nodes involved in replication (N ). The number of replicas is often called the __replication factor__.

Similarly to the write quorum, there is the notion of read quorum: How many nodes you need to contact to be sure you have the most up-to-date change. The read quorum is a bit more complicated because it depends on how many nodes need to confirm a write.

Let’s consider a replication factor of 3. If all writes need two nodes to confirm (W = 2 ) then we need to contact at least two nodes to be sure we’ll get the latest data. If, however, writes are only confirmed by a single node (W = 1 ) we need to talk to all three nodes to be sure we have the latest updates. In this case, since we don’t have a write quorum, we may have an update conflict, but by contacting enough readers we can be sure to detect it. Thus we can get strongly consistent reads even if we don’t have strong consistency on our writes.

This relationship between the number of nodes you need to contact for a read (R ), those confirming a write (W ), and the replication factor (N ) can be captured in an inequality: You can have a strongly consistent read if __R + W > N__ .

These inequalities are written with a peer-to-peer distribution model in mind. If you have a master-slave distribution, you only have to write to the master to avoid write-write conflicts, and similarly only read from the master to avoid read- write conflicts. With this notation, it is common to confuse the number of nodes in the cluster with the replication factor, but these are often different. I may have 100 nodes in my cluster, but only have a replication factor of 3, with most of the distribution occurring due to sharding.

Indeed most authorities suggest that a replication factor of 3 is enough to have good resilience. This allows a single node to fail while still maintaining quora for reads and writes. If you have automatic rebalancing, it won’t take too long for the cluster to create a third replica, so the chances of losing a second replica before a replacement comes up are slight.

The number of nodes participating in an operation can vary with the operation. When writing, we might require quorum for some types of updates but not others, depending on how much we value consistency and availability. Similarly, a read that needs speed but can tolerate staleness should contact less nodes.

Often you may need to take both into account. If you need fast, strongly consistent reads, you could require writes to be acknowledged by all the nodes, thus allowing reads to contact only one (N = 3, W = 3, R = 1). That would mean that your writes are slow, since they have to contact all three nodes, and you would not be able to tolerate losing a node. But in some circumstances that may be the tradeoff to make.

The point to all of this is that you have a range of options to work with and can choose which combination of problems and advantages to prefer. Some writers on NoSQL talk about a simple tradeoff between consistency and availability; we hope you now realize that it’s more flexible—and more complicated—than that.

## 5.7. Key Points

* Write-write conflicts occur when two clients try to write the same data at the same time. Read-write conflicts occur when one client reads inconsistent data in the middle of another client’s write.

* Pessimistic approaches lock data records to prevent conflicts. Optimistic approaches detect conflicts and fix them.

* Distributed systems see read-write conflicts due to some nodes having received updates while other nodes have not. Eventual consistency means that at some point the system will become consistent once all the writes have propagated to all the nodes.

* Clients usually want read-your-writes consistency, which means a client can write and then immediately read the new value. This can be difficult if the read and the write happen on different nodes.

* To get good consistency, you need to involve many nodes in data operations, but this increases latency. So you often have to trade off consistency versus latency.

* The CAP theorem states that if you get a network partition, you have to trade off availability of data versus consistency.

*  Durability can also be traded off against latency, particularly if you want to survive failures with replicated data.

* You do not need to contact all replicants to preserve strong consistency with replication; you just need a large enough quorum.

# Chapter 6. Version Stamps

Many critics of NoSQL databases focus on the lack of support for transactions. Transactions are a useful tool that helps programmers support consistency. One reason why many NoSQL proponents worry less about a lack of transactions is that aggregate-oriented NoSQL databases do support atomic updates within an aggregate —and aggregates are designed so that their data forms a natural unit of update. That said, it’s true that transactional needs are something to take into account when you decide what database to use.

As part of this, it’s important to remember that transactions have limitations. Even within a transactional system we still have to deal with updates that require human intervention and usually cannot be run within transactions because they would involve holding a transaction open for too long. We can cope with these using __version stamps__—which turn out to be handy in other situations as well, particularly as we move away from the single-server distribution model.

## 6.1.Business andSystemTransactions

Usually applications only begin a system transaction at the end of the interaction with the user, so that the locks are only held for a short period of time. The problem, however, is that calculations and decisions may have been made based on data that’s changed. The price list may have updated the price of the Talisker, or someone may have updated the customer’s address, changing the shipping charges.

The broad techniques for handling this are offline concurrency, useful in NoSQL situations too. A particularly useful approach is the Optimistic Offline Lock, a form of conditional update where a client operation rereads any information that the business transaction relies on and checks that it hasn’t changed since it was originally read and displayed to the user. A good way of doing this is to ensure that records in the database contain some form of __version stamp__: a field that changes every time the underlying data in the record changes. When you read the data you keep a note of the version stamp, so that when you write data you can check to see if the version has changed.

You may have come across this technique with updating resources with HTTP. One way of doing this is to use etags. Whenever you get a resource, the server responds with an etag in the header. This etag is an opaque string that indicates the version of the resource. If you then update that resource, you can use a conditional update by supplying the etag that you got from your last GET. If the resource has changed on the server, the etags won’t match and the server will refuse the update, returning a 412 (Precondition Failed) response.

Some databases provide a similar mechanism of conditional update that allows you to ensure updates won’t be based on stale data. You can do this check yourself, although you then have to ensure no other thread can run against the resource between your read and your update. (Sometimes this is called a compare-and-set (CAS) operation, whose name comes from the CAS operations done in processors. The difference is that a processor CAS compares a value before setting it, while a database conditional update compares a version stamp of the value.)

## 6.2. Version Stamps on Multiple Nodes

The basic version stamp works well when you have a single authoritative source for data, such as a single server or master-slave replication. In that case the version stamp is controlled by the master. Any slaves follow the master’s stamps. But this system has to be enhanced in a peer-to-peer distribution model because there’s no longer a single place to set the version stamps.

If you’re asking two nodes for some data, you run into the chance that they may give you different answers. If this happens, your reaction may vary depending on the cause of that difference. It may be that an update has only reached one node but not the other, in which case you can accept the latest (assuming you can tell which one that is). Alternatively, you may have run into an inconsistent update, in which case you need to decide how to deal with that. In this situation, a simple GUID or etag won’t suffice, since these don’t tell you enough about the relationships.

The simplest form of version stamp is a counter. Each time a node updates the data, it increments the counter and puts the value of the counter into the version stamp. If you have blue and green slave replicas of a single master, and the blue node answers with a version stamp of 4 and the green node with 6, you know that the green’s answer is more recent.

In multiple-master cases, we need something fancier. One approach, used by distributed version control systems, is to ensure that all nodes contain a history of version stamps. That way you can see if the blue node’s answer is an ancestor of the green’s answer. This would either require the clients to hold onto version stamp histories, or the server nodes to keep version stamp histories and include them when asked for data. This also detects an inconsistency, which we would see if we get two version stamps and neither of them has the other in their histories. Although version control systems keep these kinds of histories, they aren’t found in NoSQL databases.

A simple but problematic approach is to use timestamps. The main problem here is that it’s usually difficult to ensure that all the nodes have a consistent notion of time, particularly if updates can happen rapidly. Should a node’s clock get out of sync, it can cause all sorts of trouble. In addition, you can’t detect write- write conflicts with timestamps, so it would only work well for the single-master case—and then a counter is usually better.

The most common approach used by peer-to-peer NoSQL systems is a special form of version stamp which we call a __vector stamp__. In essence, a vector stamp is a set of counters, one for each node. A vector stamp for three nodes (blue, green, black) would look something like [blue: 43, green: 54, black: 12]. Each time a node has an internal update, it updates its own counter, so an update in the green node would change the vector to [blue: 43, green: 55, black: 12]. Whenever two nodes communicate, they synchronize their vector stamps. There are several variations of exactly how this synchronization is done. We’re coining the term “ vector stamp” as a general term in this book; you’ll also come across __vector clocks__ and __version vectors__—these are specific forms of vector stamps that differ in how they synchronize.

By using this scheme you can tell if one version stamp is newer than another because the newer stamp will have all its counters greater than or equal to those in the older stamp. So [blue: 1, green: 2, black: 5] is newer than [blue:1, green: 1, black 5] since one ofits counters is greater. Ifboth stamps have a counter greater than the other, e.g. [blue: 1, green: 2, black: 5] and [blue: 2, green: 1, black: 5], then you have a write-write conflict.

There may be missing values in the vector, in which case we use treat the missing value as 0. So [blue: 6, black: 2] would be treated as [blue: 6, green: 0, black: 2]. This allows you to easily add new nodes without invalidating the existing vector stamps.

Vector stamps are a valuable tool that spots inconsistencies, but doesn’t resolve them. Any conflict resolution will depend on the domain you are working in. This is part of the consistency/latency tradeoff. You either have to live with the fact that network partitions may make your system unavailable, or you have to detect and deal with inconsistencies.

## 6.3. Key Points

* Version stamps help you detect concurrency conflicts. When you read data, then update it, you can check the version stamp to ensure nobody updated the data between your read and write.
* Version stamps can be implemented using counters, GUIDs, content hashes, timestamps, or a combination of these.
* With distributed systems, a vector of version stamps allows you to detect when different nodes have conflicting updates.

# Chapter 7. Map-Reduce

The rise of aggregate-oriented databases is in large part due to the growth of clusters. Running on a cluster means you have to make your tradeoffs in data storage differently than when running on a single machine. Clusters don’t just change the rules for data storage—they also change the rules for computation. If you store lots of data on a cluster, processing that data efficiently means you have to think differently about how you organize your processing.


With a centralized database, there are generally two ways you can run the processing logic against it: either on the database server itself or on a client machine. Running it on a client machine gives you more flexibility in choosing a programming environment, which usually makes for programs that are easier to create or extend. This comes at the cost of having to shlep lots of data from the database server. If you need to hit a lot of data, then it makes sense to do the processing on the server, paying the price in programming convenience and increasing the load on the database server.

When you have a cluster, there is good news immediately—you have lots of machines to spread the computation over. However, you also still need to try to reduce the amount of data that needs to be transferred across the network by doing as much processing as you can on the same node as the data it needs.

__The map-reduce pattern (a form of Scatter-Gather) is a way to organize processing in such a way as to take advantage of multiple machines on a cluster while keeping as much processing and the data it needs together on the same machine.__ It first gained prominence with Google’s MapReduce framework. A widely used open-source implementation is part of the Hadoop project, although several databases include their own implementations. As with most patterns, there are differences in detail between these implementations, so we’ll concentrate on the general concept. The name “ map-reduce” reveals its inspiration from the map and reduce operations on collections in functional programming languages.

## 7.1. Basic Map-Reduce

To explain the basic idea, we’ll start from an example we’ve already flogged to death—that of customers and orders. Let’s assume we have chosen orders as our aggregate, with each order having line items. Each line item has a product ID, quantity, and the price charged. This aggregate makes a lot of sense as usually people want to see the whole order in one access. We have lots of orders, so we’ve sharded the dataset over many machines.

However, sales analysis people want to see a product and its total revenue for the last seven days. This report doesn’t fit the aggregate structure that we have— which is the downside of using aggregates. In order to get the product revenue report, you’ll have to visit every machine in the cluster and examine many records on each machine.

This is exactly the kind of situation that calls for __map-reduce__. The first stage in a map-reduce job is the map. __A map is a function whose input is a single aggregate and whose output is a bunch of key-value pairs.__ In this case, the input would be an order. The output would be key-value pairs corresponding to the line items. Each one would have the product ID as the key and an embedded map with the quantity and price as the values.

Each application of the map function is independent of all the others. This allows them to be safely parallelizable, so that a map-reduce framework can create efficient map tasks on each node and freely allocate each order to a map task. This yields a great deal of parallelism and locality of data access. 

A map operation only operates on a single record; the reduce function takes multiple map outputs with the same key and combines their values. So, a map function might yield 1000 line items from orders for “ Database Refactoring”; the reduce function would reduce down to one, with the totals for the quantity and revenue. While the map function is limited to working only on data from a single aggregate, the reduce function can use all values emitted for a single key.


The map-reduce framework arranges for map tasks to be run on the correct nodes to process all the documents and for data to be moved to the reduce function. To make it easier to write the reduce function, the framework collects all the values for a single pair and calls the reduce function once with the key and the collection of all the values for that key. So to run a map-reduce job, you just need to write these two functions.

## 7.2. Partitioning and Combining

In the simplest form, we think of a map-reduce job as having a single reduce function. The outputs from all the map tasks running on the various nodes are concatenated together and sent into the reduce. While this will work, there are things we can do to increase the parallelism and to reduce the data transfer.

The first thing we can do is increase parallelism by partitioning the output of the mappers. Each reduce function operates on the results of a single key. This is a limitation—it means you can’t do anything in the reduce that operates across keys —but it’s also a benefit in that it allows you to run multiple reducers in parallel. To take advantage of this, the results of the mapper are divided up based the key on each processing node. Typically, multiple keys are grouped together into partitions. The framework then takes the data from all the nodes for one partition, combines it into a single group for that partition, and sends it off to a reducer. Multiple reducers can then operate on the partitions in parallel, with the final results merged together. (This step is also called “ shuffling,” and the partitions are sometimes referred to as “buckets” or “regions.”)

The next problem we can deal with is the amount of data being moved from node to node between the map and reduce stages. Much of this data is repetitive, consisting of multiple key-value pairs for the same key. A combiner function cuts this data down by combining all the data for the same key into a single value. A combiner function is, in essence, a reducer function—indeed, in many cases the same function can be used for combining as the final reduction. The reduce function needs a special shape for this to work: Its output must match its input. We call such a function a __combinable reducer__.

When you have combining reducers, the map-reduce framework can safely run not only in parallel (to reduce different partitions), but also in series to reduce the same partition at different times and places. In addition to allowing combining to occur on a node before data transmission, you can also start combining before mappers have finished. This provides a good bit of extra flexibility to the map- reduce processing. Some map-reduce frameworks require all reducers to be combining reducers, which maximizes this flexibility. If you need to do a noncombining reducer with one of these frameworks, you’ll need to separate the processing into pipelined map-reduce steps.

## 7.3. Composing Map-Reduce Calculations

The map-reduce approach is a way of thinking about concurrent processing that trades off flexibility in how you structure your computation for a relatively straightforward model for parallelizing the computation over a cluster. Since it’s a tradeoff, there are constraints on what you can do in your calculations. Within a map task, you can only operate on a single aggregate. Within a reduce task, you can only operate on a single key. This means you have to think differently about structuring your programs so they work well within these constraints.


Map-reduce is a pattern that can be implemented in any programming language. However, the constraints of the style make it a good fit for languages specifically designed for map-reduce computations. Apache Pig [Pig], an offshoot of the Hadoop [Hadoop] project, is a language specifically built to make it easy to write map-reduce programs. It certainly makes it much easier to work with Hadoop than the underlying Java libraries. In a similar vein, if you want to specify map- reduce programs using an SQL-like syntax, there is hive [Hive], another Hadoop offshoot.

The map-reduce pattern is important to know about even outside of the context of NoSQL databases. Google’s original map-reduce system operated on files stored on a distributed file system—an approach that’s used by the open- source Hadoop project. While it takes some thought to get used to the constraints of structuring computations in map-reduce steps, the result is a calculation that is inherently well-suited to running on a cluster. When dealing with high volumes of data, you need to take a cluster-oriented approach. Aggregate-oriented databases fit well with this style of calculation. We think that in the next few years many more organizations will be processing the volumes of data that demand a cluster-oriented solution—and the map-reduce pattern will see more and more use.


7.5. Key Points

* Map-reduce is a pattern to allow computations to be parallelized over a cluster.
* The map task reads data from an aggregate and boils it down to relevant key-value pairs. Maps only read a single record at a time and can thus be parallelized and run on the node that stores the record.
* Reduce tasks take many values for a single key output from map tasks and summarize them into a single output. Each reducer operates on the result of a single key, so it can be parallelized by key.
* Reducers that have the same form for input and output can be combined into pipelines. This improves parallelism and reduces the amount of data to be transferred.
* Map-reduce operations can be composed into pipelines where the output of one reduce is the input to another operation’s map.
* If the result of a map-reduce computation is widely used, it can be stored as a materialized view.
* Materialized views can be updated through incremental map-reduce operations that only compute changes to the view instead of recomputing everything from scratch.

# Chapter 8. Key-Value Databases

A key-value store is a simple hash table, primarily used when all access to the database is via primary key. 

## 8.1. What Is a Key-Value Store

Key-value stores are the simplest NoSQL data stores to use from an API perspective. The client can either get the value for the key, put a value for a key, or delete a key from the data store. The value is a blob that the data store just stores, without caring or knowing what’s inside; it’s the responsibility of the application to understand what was stored. Since key-value stores always use primary-key access, they generally have great performance and can be easily scaled.

## 8.2. Key-Value Store Features

While using any NoSQL data stores, there is an inevitable need to understand how the features compare to the standard RDBMS data stores that we are so used to. The primary reason is to understand what features are missing and how does the application architecture need to change to better use the features of a key-value data store. Some of the features we will discuss for all the NoSQL data stores are consistency, transactions, query features, structure of the data, and scaling.

### 8.2.1. Consistency

Consistency is applicable only for operations on a single key, since these operations are either a get, put, or delete on a single key. Optimistic writes can be performed, but are very expensive to implement, because a change in value cannot be determined by the data store.

In distributed key-value store implementations like Riak, the eventually consistent model of consistency is implemented. Since the value may have already been replicated to other nodes, Riak has two ways of resolving update conflicts: either the newest write wins and older writes loose, or both (all) values are returned allowing the client to resolve the conflict.

### 8.2.2. Transactions

Different products of the key-value store kind have different specifications of transactions. Generally speaking, there are no guarantees on the writes. Many data stores do implement transactions in different ways. Riak uses the concept of __quorum__ implemented by using the W value—replicationfactor —during the write API call.

Assume we have a Riak cluster with a replication factor of 5 and we supply the W value of 3.Whenwriting,the write is reported ass uccessful only when it is written and reported as a success on at least three of the nodes. This allows Riak to have write tolerance;in our example,with N equalto5 and with a W value of 3,the cluster can tolerate N - W = 2 nodes being down for write operations, though we would still have lost some data on those nodes for read.

### 8.2.3. Query Features

All key-value stores can query by the key—and that’s about it. If you have requirements to query by using some attribute of the value column, it’s not possible to use the database: Your application needs to read the value to figure out if the attribute meets the conditions.

Query by key also has an interesting side effect. What if we don’t know the key, especially during ad-hoc querying during debugging? Most of the data stores will not give you a list of all the primary keys; even if they did, retrieving lists of keys and then querying for the value would be very cumbersome. Some key-value databases get around this by providing the ability to search inside the value, such as Riak Search that allows you to query the data just like you would query it using Lucene indexes.

While using key-value stores, lots of thought has to be given to the design of the key. Can the key be generated using some algorithm? Can the key be provided by the user (user ID, email, etc.)? Or derived from timestamps or other data that can be derived outside of the database?

These query characteristics make key-value stores likely candidates for storing session data (with the session ID as the key), shopping cart data, user profiles, and soon. The ```expiry_secs``` property can be used to expire keys after a certain time interval, especially for session/shopping cart objects.

### 8.2.4. Structure of Data

Key-value databases don’t care what is stored in the value part of the key-value pair. The value can be a blob, text, JSON, XML, and so on. In Riak, we can use the Content-Type in the POST request to specify the datatype.

### 8.2.5. Scaling

Many key-value stores scale by using sharding (“ Sharding,” p. 38). With sharding, the value of the key determines on which node the key is stored. Let’s assume we are sharding by the first character of the key; if the key is f 4 b 1 9 d 7 9 5 8 7 d , which starts with an f, it will be sent to different node than the key ad9c7a396542. This kind of sharding setup can increase performance as more nodes are added to the cluster.

Sharding also introduces some problems.If the node used to store f goes down, the data stored on that node becomes unavailable, nor can new data be written with keys that start with f .

Data stores such as Riak allow you to control the aspects of the CAP Theorem (“The CAP Theorem,”p.53):N (number of nodes to store the key-value replicas), R (number of nodes that have to have the data being fetched before the read is considered successful),and W (the number of nodes the write has to be written to before it is considered successful).

Let’s assume we have a 5-node Riak cluster. Setting N to 3 means that all data is replicated to at least three nodes, setting R to 2 means any two nodes must reply to aG ET request for it to be considered successful,and setting W to2 ensures that the PUT requestis written to two nodes before the write is considered successful.

These settings allow us to fine-tune node failures for read or write operations. Based on our need, we can change these values for better read availability or write availability.Generally speaking choose a W value to match your consistency needs; these values can be set as defaults during bucket creation.

## 8.3. Suitable Use Cases

### 8.3.1. Storing Session Information

Generally,every web session is unique and is assigned a unique sessionid value. Applications that store the sessionid on disk or in an RDBMS will greatly benefit from moving to a key-value store, since everything about the session can be stored by a single PUT request or retrieved using GET.This single-request operation makes it very fast, as everything about the session is stored in a single object. Solutions such as Memcached are used by many web applications, and Riak can be used when availability is important.

### 8.3.2. User Profiles, Preferences

Almost every user has a unique userId, username, or some other attribute, as well as preferences such as language, color, timezone, which products the user has access to, and so on. This can all be put into an object, so getting preferences of a user takes a single GET operation.Similarly,product profiles can be stored.

### 8.3.3. Shopping Cart Data

E-commerce websites have shopping carts tied to the user. As we want the shopping carts to be available all the time, across browsers, machines, and sessions,all the shopping information can be put into the value where the key is the u s e r i d . A Riak cluster would be best suited for these kinds of applications.

## 8.4.When Not to Use

### 8.4.1. Relationships among Data

If you need to have relationships between different sets of data, or correlate the data between different sets of keys, key-value stores are not the best solution to use, even though some key-value stores provide link-walking features.

###  8.4.2. Multioperation Transactions

If you’re saving multiple keys and there is a failure to save any one of them, and you want to revert or roll back the rest of the operations, key-value stores are not the best solution to be used.

### 8.4.3. Query by Data

If you need to search the keys based on something found in the value part of the key-value pairs, then key-value stores are not going to perform well for you. There is no way to inspect the value on the database side, with the exception of some products like Riak Search or indexing engines like Lucene [Lucene] or Solr [Solr].

### 8.4.4. Operations by Sets

Since operations are limited to one key at a time, there is no way to operate upon multiple keys at the same time. If you need to operate upon multiple keys, you have to handle this from the client side.

# Chapter 9. Document Databases

Documents are the main concept in document databases. The database stores and retrieves documents, which can be XML, JSON, BSON, and so on. These documents are self-describing, hierarchical tree data structures which can consist of maps, collections, and scalar values. The documents stored are similar to each other but do not have to be exactly the same. Document databases store documents in the value part of the key-value store; think about document databases as key- value stores where the value is examinable. 

## 9.1. What Is a Document Database?

This different representation of data is not the same as in RDBMS where every column has to be defined, and if it does not have data it is marked as empty or set to n u l l . In documents, there are no empty attributes; if a given attribute is not found, we assume that it was not set or not relevant to the document. Documents allow for new attributes to be created without the need to define them or to change the existing documents.

## 9.2. Features


While there are many specialized document databases, we will use MongoDB as a representative of the feature set. Keep in mind that each product has some features that may not be found in other document databases.

Let’s take some time to understand how MongoDB works. Each MongoDB instance has multiple databases, and each database can have multiple collections. When we compare this with RDBMS, an RDBMS instance is the same as MongoDB instance, the schemas in RDBMS are similar to MongoDB databases, and the RDBMS tables are collections in MongoDB. When we store a document, we have to choose which database and collection this document belongs in—for example, database.collection.insert(document), which is usually represented as db.coll.insert(document).

### 9.2.1. Consistency

Consistency in MongoDB database is configured by using the __replica sets__ and choosing to wait for the writes to be replicated to all the slaves or a given number of slaves. Every write can specify the number of servers the write has to be propagated to before it returns as successful.

A command like db.runCommand({ getlasterror : 1 , w : "majority" }) tells the database how strong is the consistency you want.Forexample,if you have one server and specify thew as majority,the write will return immediately since there is only one node. If you have three nodes in the replica set and specify w as majority, the write will have to complete at a minimum oftwo nodes before it is reported as a success.You can increase the w value for stronger consistency but you will suffer on write performance, since now the writes have to complete at more nodes. Replica sets also allow you to increase the read performance by allowing reading from slaves by setting ```s l a v e O k``` ; this parameter can be set on the connection, or database, or collection, or individually for each operation.

Similar to various options available for read, you can change the settings to achieve strong write consistency, if desired. By default, a write is reported successful once the database receives it; you can change this so as to wait for the writes to be synced to disk or to propagate to two or more slaves. This is known as WriteConcern: You make sure that certain writes are written to the master and some slaves by setting WriteConcern to ```REPLICAS_SAFE```.

### 9.2.2. Transactions

Transactions, in the traditional RDBMS sense, mean that you can start modifying the database with insert, update, or delete commands over different tables and then decide ifyou want to keep the changes or not by using commit or rollback. These constructs are generally not available in NoSQL solutions—a write either succeeds or fails. Transactions at the single-document level are known as atomic transactions. Transactions involving more than one operation are not possible, although there are products such as RavenDB that do support transactions across multiple operations.

### 9.2.3. Availability

The CAP theorem (“ The CAP Theorem,” p. 53) dictates that we can have only two of Consistency, Availability, and Partition Tolerance. Document databases try to improve on availability by replicating data using the master-slave setup. The same data is available on multiple nodes and the clients can get to the data even when the primary node is down. Usually, the application code does not have to determine if the primary node is available or not. MongoDB implements replication, providing high availability using __replica sets__.

In a replica set, there are two or more nodes participating in an asynchronous master-slave replication. The replica-set nodes elect the master, or primary, among themselves. Assuming all the nodes have equal voting rights, some nodes can be favored for being closer to the other servers, for having more RAM, and so on; users can affect this by assigning a priority—a number between 0 and 1000—to a node.

All requests go to the master node, and the data is replicated to the slave nodes. If the master node goes down, the remaining nodes in the replica set vote among themselves to elect a new master; all future requests are routed to the new master, and the slave nodes start getting data from the new master. When the node that failed comes back online, it joins in as a slave and catches up with the rest of the nodes by pulling all the data it needs to get current.


The application writes or reads from the primary (master) node. When connection is established, the application only needs to connect to one node (primary or not, does not matter) in the replica set, and the rest of the nodes are discovered automatically. When the primary node goes down, the driver talks to the new primary elected by the replica set. The application does not have to manage any of the communication failures or node selection criteria. Using replica sets gives you the ability to have a highly available document data store. Replica sets are generally used for data redundancy, automated failover, read scaling, server maintenance without downtime, and disaster recovery. 

### 9.2.4. Query Features

Document databases provide different query features. CouchDB allows you to query via views—complex queries on documents which can be either materialized (“ Materialized Views,” p. 30) or dynamic (think of them as RDBMS views which are either materialized or not). With CouchDB, if you need to aggregate the number of reviews for a product as well as the average rating, you could add a view implemented via map-reduce to return the count of reviews and the average of their ratings.

When there are many requests, you don’t want to compute the count and average for every request; instead you can add a materialized view that precomputes the values and stores the results in the database. These materialized views are updated when queried, if any data was changed since the last update.

One of the good features of document databases, as compared to key-value stores, is that we can query the data inside the document without having to retrieve the whole document by its key and then introspect the document. This feature brings these databases closer to the RDBMS query model.

### 9.2.5. Scaling

The idea of scaling is to add nodes or change data storage without simply migrating the database to a bigger box. We are not talking about making application changes to handle more load; instead, we are interested in what features are in the database so that it can handle more load.

Scaling for heavy-read loads can be achieved by adding more read slaves, so that all the reads can be directed to the slaves. Given a heavy-read application, with our 3-node replica-set cluster, we can add more read capacity to the cluster as the read load increases just by adding more slave nodes to the replica set. This is horizontal scaling for reads.

When a new node is added, it will sync up with the existing nodes, join the replica set as secondary node, and start serving read requests. An advantage of this setup is that we do not have to restart any other nodes, and there is no downtime for the application either.

When we want to scale for write, we can start sharding the data. Sharding is similar to partitions in RDBMS where we split data by value in a certain column, such as state or year. With RDBMS, partitions are usually on the same node, so the client application does not have to query a specific partition but can keep querying the base table; the RDBMS takes care of finding the right partition for the query and returns the data.

In sharding, the data is also split by certain field, but then moved to different Mongo nodes. The data is dynamically moved between nodes to ensure that shards are always balanced. We can add more nodes to the cluster and increase the number of writable nodes, enabling horizontal scaling for writes.

Splitting the data ensures that the data is balanced across the shards for optimal write performance; furthermore, each shard can be a replica set ensuring better read performance within the shard. When we add a new shard to this existing sharded cluster, the data will now be balanced across four shards instead of three. As all this data movement and infrastructure refactoring is happening, the application will not experience any downtime, although the cluster may not perform optimally when large amounts of data are being moved to rebalance the shards.

The shard key plays an important role. You may want to place your MongoDB database shards closer to their users, so sharding based on user location may be a good idea. When sharding by customer location, all user data for the East Coast of the USA is in the shards that are served from the East Coast, and all user data for the West Coast is in the shards that are on the West Coast.

## 9.3. Suitable Use Cases

### 9.3.1. Event Logging

Applications have different event logging needs; within the enterprise, there are many different applications that want to log events. Document databases can store all these different types of events and can act as a central data store for event storage. This is especially true when the type of data being captured by the events keeps changing. Events can be sharded by the name of the application where the event originatedorbythetypeofeventsuchasorder_processed orcustomer_logged.

### 9.3.2. Content Management Systems, Blogging Platforms

Since document databases have no predefined schemas and usually understand JSON documents, they work well in content management systems or applications for publishing websites, managing user comments, user registrations, profiles, web- facing documents.

### 9.3.3. Web Analytics or Real-Time Analytics
Document databases can store data for real-time analytics; since parts of the document can be updated, it’s very easy to store page views or unique visitors, and new metrics can be easily added without schema changes.

### 9.3.4. E-Commerce Applications
E-commerce applications often need to have flexible schema for products and orders, as well as the ability to evolve their data models without expensive database refactoring or data migration.

## 9.4.When Not to Use  
There are problem spaces where document databases are not the best solution.

### 9.4.1. Complex Transactions Spanning Different Operations
If you need to have atomic cross-document operations, then document databases may not be for you. However, there are some document databases that do support these kinds of operations, such as RavenDB.

#### 9.4.2. Queries against Varying Aggregate Structure
Flexible schema means that the database does not enforce any restrictions on the schema. Data is saved in the form of application entities. If you need to query these entities ad hoc, your queries will be changing (in RDBMS terms, this would mean that as you join criteria between tables, the tables to join keep changing). Since the data is saved as an aggregate, if the design of the aggregate is constantly changing, you need to save the aggregates at the lowest level of granularity—basically, you need to normalize the data. In this scenario, document databases may not work.

# Chapter 10. Column-Family Stores

Column-family stores, such as Cassandra [Cassandra], HBase [Hbase], Hypertable [Hypertable], and Amazon SimpleDB [Amazon SimpleDB], allow you to store data with keys mapped to values and the values grouped into multiple column families, each column family being a map of data.

## 10.1. What Is a Column-Family Data Store?

Column-family databases store data in column families as rows that have many columns associated with a row key. Column families are groups of related data that is often accessed together. For a Customer, we would often access their Profile information at the same time, but not their Orders.

![alt](http://ptgmedia.pearsoncmg.com/images/art_sadalage_nosql/elementLinks/fig5.png)

## 10.2. Features

Let’s start by looking at how data is structured in Cassandra. The basic unit of storage in Cassandra is a column. A Cassandra column consists of a name-value pair where the name also behaves as the key. Each of these key-value pairs is a single column and is always stored with a timestamp value. The timestamp is used to expire data, resolve write conflicts, deal with stale data, and do other things. Once the column data is no longer used, the space can be reclaimed later during a compaction phase.

```
{
name: "fullName", value: "Martin Fowler", timestamp: 12345667890
}
```

The column has a key of firstName and the value of Martin and has a timestamp attached to it. A row is a collection of columns attached or linked to a key; a collection of similar rows makes a column family. When the columns in a column family are simple columns, the column family is known as __standard column family__.

```
//column family 
{
//row
"pramod-sadalage" : { firstName: "Pramod", lastName: "Sadalage", lastVisit: "2012/12/12"} 
//row
"martin-fowler" : { firstName: "Martin", lastName: "Fowler", location: "Boston"} 
}
```
Each column family can be compared to a container of rows in an RDBMS table where the key identifies the row and the row consists on multiple columns. __The difference is that various rows do not have to have the same columns, and columns can be added to any row at any time without having to add it to other rows.__ We have the pramod-sadalage row and the martin-fowler row with different columns; both rows are part of the column family.

When a column consists of a map of columns, then we have a __super column__. A super column consists of a name and a value which is a map of columns. Think of a super column as a container of columns.

When we use super columns to create a column family, we get a __super column family__.

Super column families are good to keep related data together, but when some of the columns are not needed most of the time, the columns are still fetched and deserialized by Cassandra, which may not be optimal.

Cassandra puts the standard and super column families into __keyspaces__. A keyspace is similar to a database in RDBMS where all column families related to the application are stored. Keyspaces have to be created so that column families can be assigned to them.

##### Why many refer to Cassandra as a Column oriented database?

Reading several papers and documents on internet, I found many contradictory information about the Cassandra data model. There are many which identify it as a column oriented database, other as a row-oriented and then who define it as a hybrid way of both.

According to what I know about how Cassandra stores file, it uses the *-Index.db file to access at the right position of the *-Data.db file where it is stored the bloom filter, column index and then the columns of the required row.

In my opinion, this is strictly row-oriented. Is there something I'm missing?

Yes, the "column-oriented" terminology is a bit confusing.

The model in Cassandra is that rows contain columns. To access the smallest unit of data (a column) you have to specify first the row name (key), then the column name.

So in a columnfamily called Fruit you could have a structure like the following example (with 2 rows), where the fruit types are the row keys, and the columns each have a name and value.

```
apple -> colour  weight  price variety
         "red"   100     40    "Cox"

orange -> colour    weight  price  origin
          "orange"  120     50     "Spain"
```

One difference from a table-based relational database is that one can omit columns (orange has no variety), or add arbitrary columns (orange has origin) at any time. You can still imagine the data above as a table, albeit a sparse one where many values might be empty.

However, a "column-oriented" model can also be used for lists and time series, where every column name is unique (and here we have just one row, but we could have thousands or millions of columns):

```
temperature ->  2012-09-01  2012-09-02  2012-09-03 ...
                40          41          39         ...
```

which is quite different from a relational model, where one would have to model the entries of a time series as rows not columns.

### 10.2.1. Consistency

When a write is received by Cassandra, the data is first recorded in a __commit log__, then written to an in-memory structure known as __memtable__. A write operation is considered successful once it’s written to the commit log and the memtable. Writes are batched in memory and periodically written out to structures known as __SSTable__. SSTables are not written to again after they are flushed; if there are changes to the data, a new SSTable is written. Unused SSTables are reclaimed by __compactation__.

Let’s look at the read operation to see how consistency settings affect it. If we have a consistency setting of ```ONE ``` as the default for all read operations,then when a read request is made, Cassandra returns the data from the first replica, even if the data is stale. If the data is stale, subsequent reads will get the latest (newest) data; this process is known as __read repair__. The low consistency level is good to use when you do not care if you get stale data and/or if you have high read performance requirements.

Similarly, if you are doing writes, Cassandra would write to one node’s commit log and return a response to the client.The consistency of ```ONE``` is good if you have very high write performance requirements and also do not mind if some writes are lost, which may happen if the node goes down before the write is replicated to other nodes.

```
quorum = new ConfigurableConsistencyLevel(); 
quorum.setDefaultReadConsistencyLevel(HConsistencyLevel.QUORUM); quorum.setDefaultWriteConsistencyLevel(HConsistencyLevel.QUORUM);
```

UsingtheQUORUM consistencysettingforbothreadandwriteoperations ensures that majority of the nodes respond to the read and the column with the newest timestamp is returned back to the client, while the replicas that do not have the newest data are repaired via the read repair operations. During write operations, the ```QUORUM``` consistency setting means that the write has to propagate to the majority of the nodes before it is considered successful and the client is notified.

Using ```ALL``` as consistency level means that all nodes will have to respond to reads or writes, which will make the cluster not tolerant to faults—even when one node is down, the write or read is blocked and reported as a failure. It’s therefore upon the system designers to tune the consistency levels as the application requirements change. Within the same application, there may be different requirements of consistency; they can also change based on each operation, for example showing review comments for a product has different consistency requirements compared to reading the status of the last order placed by the customer.

During __keyspace__ creation, we can configure how many replicas of the data we need to store. This number determines the replication factor of the data. If you have a replication factor of 3, the data copied on to three nodes. When writing and reading data with Cassandra, if you specify the consistency values of 2, you get that R + W is greater than the replication factor ( 2 + 2 > 3 ) which gives you better consistency during writes and reads.

We can run the node repair command for the keyspace and force Cassandra to compare every key it’s responsible for with the rest of the replicas. As this operation is expensive, we can also just repair a specific column family or a list of column families:
```
repair ecommerce
repair ecommerce customerInfo
```

While a node is down, the data that was supposed to be stored by that node is handed off to other nodes. As the node comes back online, the changes made to the data are handed back to the node. This technique is known as __hinted handoff__. Hinted handoff allows for faster restore of failed nodes.

### 10.2.2. Transactions

Cassandra does not have transactions in the traditional sense—where we could start multiple writes and then decide if we want to commit the changes or not. In Cassandra, a write is atomic at the row level, which means inserting or updating columns for a given row key will be treated as a single write and will either succeed or fail. Writes are first written to commit logs and memtables, and are only considered good when the write to commit log and memtable was successful. If a node goes down, the commit log is used to apply changes to the node, just like the __redo log__ in Oracle.

You can use external transaction libraries, such as __ZooKeeper__, to synchronize your writes and reads. There are also libraries such as Cages [Cages] that allow you to wrap your transactions over ZooKeeper.

### 10.2.3. Availability

Cassandra is by design highly available, since there is no master in the cluster and every node is a peer in the cluster. The availability of a cluster can be increased by reducing the consistency level of the requests. Availability is governed by the ```( R + W ) > N``` formula (“ Quorums,”) where W is the minimum number of nodes where the write must be successfully written,R is the minimum number of nodes that must respond successfully to a read, and N is the number of nodes participating in the replication of data.You can tune the availability by changing the R and W values for a fixed value of N.

In a 10-node Cassandra cluster with a replication factor for the keyspace set to 3(N = 3),ifwesetR = 2 andW = 2,thenwehave(2 + 2) > 3.Inthis scenario, when one node goes down, availability is not affected much, as the data can be retrieved from the other two nodes. If W = 2 and R = 1 , when two nodes are down the cluster is not available for write but we can still read. Similarly, if R = 2 and W = 1, we can write but the cluster is not available for read. With the R + W > N equation, you are making conscious decisions about consistency tradeoffs.

You should set up your keyspaces and read/write operations based on your needs—higher availability for write or higher availability for read.

### 10.2.4. Query Features

When designing the data model in Cassandra, it is advised to make the columns and column families optimized for reading the data, as it does not have a rich query language; as data is inserted in the column families, data in each row is sorted by column names. If we have a column that is retrieved much more often than other columns, it’s better performance-wise to use that value for the row key instead.

### 10.2.5. Scaling

Scaling an existing Cassandra cluster is a matter of adding more nodes. As no single node is a master, when we add nodes to the cluster we are improving the capacity of the cluster to support more writes and reads. This type of horizontal scaling allows you to have maximum uptime, as the cluster keeps serving requests from the clients while new nodes are being added to the cluster.


## 10.3. Suitable Use Cases

### 10.3.1. Event Logging
Column-family databases with their ability to store any data structures are a great choice to store event information, such as application state or errors encountered by the application. Within the enterprise, all applications can write their events to Cassandra with their own columns and the rowkey of the form appname:timestamp. Since we can scale writes, Cassandra would work ideally for an event logging system.

### 10.3.2. Content Management Systems, Blogging Platforms

Using column families, you can store blog entries with tags, categories, links, and trackbacks in different columns. Comments can be either stored in the same row or moved to a different keyspace; similarly, blog users and the actual blogs can be put into different column families.

### 10.3.3. Counters
Often, in web applications you need to count and categorize visitors of a page to calculate analytics.You can use the CounterColumnType during creation of a column family.

### 10.3.4. Expiring Usage
You may provide demo access to users, or may want to show ad banners on a website for a specific time. You can do this by using expiring columns: Cassandra allows you to have columns which, after a given time, are deleted automatically. This time is known as TTL (Time To Live) and is defined in seconds. The column is deleted after the TTL has elapsed; when the column does not exist, the access can be revoked or the banner can be removed.

## 10.4.When Not to Use

There are problems for which column-family databases are not the best solutions, such as systems that require ACID transactions for writes and reads. If you need the databasetoaggregatethedatausingqueries(suchasSUM orAVG),youhavetodo this on the client side using data retrieved by the client from all the rows.

Cassandra is not great for early prototypes or initial tech spikes: During the early stages, we are not sure how the query patterns may change, and as the query patterns change, we have to change the column family design. This causes friction for the product innovation team and slows down developer productivity. RDBMS impose high cost on schema change, which is traded off for a low cost of query change; in Cassandra, the cost may be higher for query change as compared to schema change.

# Chapter 11. Graph Databases

Graph databases allow you to store entities and relationships between these entities. Entities are also known as nodes, which have properties. Think of a node as an instance of an object in the application. Relations are known as edges that can have properties. Edges have directional significance; nodes are organized by relationships which allow you to find interesting patterns between the nodes. The organization of the graph lets the data to be stored once and then interpreted in different ways based on relationships.

## 11.1. What Is a Graph Database?

Nodes are entities that have properties, such as name. The node of Martin is actually a node that has property ofname set to Martin. A query on the graph is also known as traversing the graph. An advantage of the graph databases is that we can change the traversing requirements without having to change the nodes or edges. If we want to “ get all nodes that like Madonna", we can do so without having to change the existing data or the model of the database, because we can traverse the graph any way we like.

Usually, when we store a graph-like structure in RDBMS, it’s for a single type of relationship (“ who is my manager” is a common example). Adding another relationship to the mix usually means a lot of schema changes and data movement, which is not the case when we are using graph databases. Similarly, in relational databases we model the graph before hand based on the Traversal wewant;if the Traversal changes, the data will have to change. 

In graph databases, traversing the joins or relationships is very fast. The relationship between nodes is not calculated at query time but is actually persisted as a relationship. Traversing persisted relationships is faster than calculating them for every query.

Nodes can have different types of relationships between them, allowing you to both represent relationships between the domain entities and to have secondary relationships for things like category, path, time-trees, quad-trees for spatial indexing, or linked lists for sorted access. Since there is no limit to the number and kind of relationships a node can have, all they can be represented in the same graph database.

## 11.2. Features

There are many graph databases available, such as Neo4J [Neo4J], Infinite Graph [Infinite Graph], OrientDB [OrientDB], or FlockDB [FlockDB] (which is a special case: a graph database that only supports single-depth relationships or adjacency lists, where you cannot traverse more than one level deep for relationships). We will take Neo4J as a representative of the graph database solutions to discuss how they work and how they can be used to solve application problems.

In Neo4J, creating a graph is as simple as creating two nodes and then creating a relationship. Let’s create two nodes, Martin and Pramod:

```
Node martin = graphDb.createNode(); 
martin.setProperty("name", "Martin");
Node pramod = graphDb.createNode();
pramod.setProperty("name", "Pramod");
```

We have assigned the name property of the two nodes the values of Martin and Pramod . Once we have more than one node, we can create a relationship:

```
martin.createRelationshipTo(pramod, FRIEND); 
pramod.createRelationshipTo(martin, FRIEND);
```
We have to create relationship between the nodes in both directions, for the direction of the relationship matters:For example,a product node can be liked by user but the product cannot like the user. This directionality helps in designing a rich domain model. Nodes know about INCOMING and OUTGOING relationships that are traversable both ways.

Relationships are first-class citizens in graph databases; most of the value of graph databases is derived from the relationships. Relationships don’t only have a type, a start node, and an end node, but can have properties of their own. Using these properties on the relationships, we can add intelligence to the relationship— for example, since when did they become friends, what is the distance between the nodes, or what aspects are shared between the nodes. These properties on the relationships can be used to query the graph.

Since most of the power from the graph databases comes from the relationships and their properties, a lot of thought and design work is needed to model the relationships in the domain that we are trying to work with. Adding new relationship types is easy; changing existing nodes and their relationships is similar to data migration, because these changes will have to be done on each node and each relationship in the existing data.

### 11.2.1. Consistency

Since graph databases are operating on connected nodes, most graph database solutions usually do not support distributing the nodes on different servers. There are some solutions, however, that support node distribution across a cluster of servers, such as Infinite Graph. Within a single server, data is always consistent, especially in Neo4J which is fully ACID-compliant. When running Neo4J in a cluster, a write to the master is eventually synchronized to the slaves, while slaves are always available for read. Writes to slaves are allowed and are immediately synchronized to the master; other slaves will not be synchronized immediately, though—they will have to wait for the data to propagate from the master.

Graph databases ensure consistency through transactions. They do not allow dangling relationships: The start node and end node always have to exist, and nodes can only be deleted if they don’t have any relationships attached to them.

### 11.2.2. Transactions

Neo4J is ACID-compliant. Before changing any nodes or adding any relationships to existing nodes, we have to start a transaction. Without wrapping operations in transactions, we will get a NotInTransactionException. Read operations can be done without initiating a transaction.

```
Transaction transaction = database.beginTx(); 
try {
 Node node = database.createNode(); 
 node.setProperty("name", "NoSQL Distilled"); 
 node.setProperty("published", "2012"); 
 transaction.success();
} finally { 
 transaction.finish();
}
```

In the above code, we started a transaction on the database, then created a node and set properties on it.We marked the transaction as success and finally completed it by finish. A transaction has to be marked as success, otherwise Neo4J assumes that it was a failure and rolls it back when finish is issued. Setting success without issuing finish also does not commit the data to the database. This way of managing transactions has to be remembered when developing, as it differs from the standard way of doing transactions in an RDBMS.

### 11.2.3. Availability

Neo4J, as of version 1.8, achieves high availability by providing for replicated slaves. These slaves can also handle writes: When they are written to, they synchronize the write to the current master, and the write is committed first at the master and then at the slave. Other slaves will eventually get the update. Other graph databases, such as Infinite Graph and FlockDB, provide for distributed storage of the nodes.

Neo4J uses the __Apache ZooKeeper__ to keep track of the last transaction IDs persisted on each slave node and the current master node. Once a server starts up, it communicates with ZooKeeper and finds out which server is the master. If the server is the first one to join the cluster, it becomes the master; when a master goes down, the cluster elects a master from the available nodes, thus providing high availability.

### 11.2.4. Query Features

Graph databases are supported by query languages such as Gremlin [Gremlin]. Gremlin is a domain-specific language for traversing graphs; it can traverse all graph databases that implement the Blueprints [Blueprints] property graph. Neo4J also has the Cypher [Cypher] query language for querying the graph. Outside these query languages, Neo4J allows you to query the graph for properties of the nodes, traverse the graph, or navigate the nodes relationships using language bindings.

Properties of a node can be indexed using the indexing service. Similarly, properties of relationships or edges can be indexed, so a node or edge can be found by the value. Indexes should be queried to find the starting node to begin a traversal. Let’s look at searching for the node using node indexing.

If we have the graph shown in Figure 11.1, we can index the nodes as they are added to the database, or we can index all the nodes later by iterating over them. We first need to create an index for the nodes using the IndexManager.

```Index<Node> nodeIndex = graphDb.index().forNodes("nodes");```

We are indexing the nodes for the name property. Neo4J uses Lucene[Lucene] as its indexing service. We will see later that we can also use the full-text search capability of Lucene. When new nodes are created, they can be added to the index.

```
Transaction transaction = graphDb.beginTx(); 
try {
 Index<Node> nodeIndex = graphDb.index().forNodes("nodes"); 
 nodeIndex.add(martin, "name", martin.getProperty("name"));
 nodeIndex.add(pramod, "name", pramod.getProperty("name")); 
 transaction.success();
} finally { 
 transaction.finish();
}
```

Adding nodes to the index is done inside the context of a transaction. Once the nodes are indexed, we can search them using the indexed property.

Finding nodes and their immediate relations is easy, but this can also be achieved in RDBMS databases. Graph databases are really powerful when you want to traverse the graphs at any depth and specify a starting node for the traversal. This is especially useful when you are trying to find nodes that are related to the starting node at more than one level down. As the depth of the graph increases, it makes moresensetotraversetherelationshipsbyusingaTraverser whereyoucan specify that you are looking for INCOMING, OUTGOING, or BOTH types of relationships. You can also make the traverser go top-down or sideways on the graph by using Order values ofBREADTH_FIRST or DEPTH_FIRST. The traversal has to start at some node—in this example, we try to find all the nodes at any depth that are related as a FRIEND with Barbara:

```
Node barbara = nodeIndex.get("name", "Barbara").getSingle();
Traverser friendsTraverser = barbara.traverse(Order.BREADTH_FIRST, StopEvaluator.END_OF_GRAPH, ReturnableEvaluator.ALL_BUT_START_NODE,
EdgeType.FRIEND,
Direction.OUTGOING);
```

The friendsTraverser provides us a way to find all the nodes that are related to Barbara where there lationship type is FRIEND.The nodes can be at any depth—friend of a friend at any level—allowing you to explore tree structures.

### 11.2.5. Scaling

In NoSQL databases, one of the commonly used scaling techniques is sharding, where data is split and distributed across different servers. With graph databases, sharding is difficult, as graph databases are not aggregate-oriented but relationship- oriented. Since any given node can be related to any other node, storing related nodes on the same server is better for graph traversal. Traversing a graph when the nodes are on different machines is not good for performance. Knowing this limitation of the graph databases, we can still scale them using some common techniques described by Jim Webber.

Generally speaking, there are three ways to scale graph databases. Since machines now can come with lots of RAM, we can add enough RAM to the server so that the working set of nodes and relationships is held entirely in memory. This technique is only helpful if the dataset that we are working with will fit in a realistic amount of RAM.

We can improve the read scaling of the database by adding more slaves with read-only access to the data, with all the writes going to the master. This pattern of writing once and reading from many servers is a proven technique in MySQL clusters and is really useful when the dataset is large enough to not fit in a single machine’s RAM, but small enough to be replicated across multiple machines. Slaves can also contribute to availability and read-scaling, as they can be configured to never become a master, remaining always read-only.

When the dataset size makes replication impractical, we can shard the data from the application side using domain- specific knowledge. For example, nodes that relate to the North America can be created on one server while the nodes that relate to Asia on another. This application-level sharding needs to understand that nodes are stored on physically different databases.

## 11.3. Suitable Use Cases

Social networks are where graph databases can be deployed and used very effectively. These social graphs don’t have to be only of the friend kind; for example, they can represent employees, their knowledge, and where they worked with other employees on different projects. Any link-rich domain is well suited for graph databases.

If you have relationships between domain entities from different domains (such as social, spatial, commerce) in a single database, you can make these relationships more valuable by providing the ability to traverse across domains.

### 11.3.2. Routing, Dispatch, and Location-Based Services

Every location or address that has a delivery is a node, and all the nodes where the delivery has to be made by the delivery person can be modeled as a graph of nodes. Relationships between nodes can have the property of distance, thus allowing you to deliver the goods in an efficient manner. Distance and location properties can also be used in graphs of places of interest, so that your application can provide recommendations of good restaurants or entertainment options nearby. You can also create nodes for your points of sales, such as bookstores or restaurants, and notify the users when they are close to any of the nodes to provide location-based services.

### 11.3.3. Recommendation Engines

As nodes and relationships are created in the system, they can be used to make recommendations like “ your friends also bought this product” or “ when invoicing this item, these other items are usually invoiced.” Or, it can be used to make recommendations to travelers mentioning that when other visitors come to Barcelona they usually visit Antonio Gaudi’s creations.

An interesting side effect of using the graph databases for recommendations is that as the data size grows, the number of nodes and relationships available to make the recommendations quickly increases. The same data can also be used to mine information—for example, which products are always bought together, or which items are always invoiced together; alerts can be raised when these conditions are not met. Like other recommendation engines, graph databases can be used to search for patterns in relationships to detect fraud in transactions.

## 11.4.When Not to Use

In some situations, graph databases may not appropriate. When you want to update all or a subset of entities—for example, in an analytics solution where all entities may need to be updated with a changed property—graph databases may not be optimal since changing a property on all the nodes is not a straightforward operation. Even if the data model works for the problem domain, some databases may be unable to handle lots of data, especially in global graph operations (those involving the whole graph).

# Chapter 12. Schema Migrations

## 12.1. Schema Changes

The recent trend in discussing NoSQL databases is to highlight their schemaless nature—it is a popular feature that allows developers to concentrate on the domain design without worrying about schema changes. It’s especially true with the rise of __agile methods__ where responding to changing requirements is important.

Discussions, iterations, and feedback loops involving domain experts and product owners are important to derive the right understanding of the data; these discussions must not be hampered by a database’s schema complexity. With NoSQL data stores, changes to the schema can be made with the least amount of friction, improving developer productivity. We have seen that developing and maintaining an application in the brave new world of schemaless databases requires careful attention to be given to schema migration.

## 12.2. Schema Changes in RDBMS

While developing with standard RDBMS technologies, we develop objects, their corresponding tables, and their relationships.While this data model supports the current object model, life is good. The first time there is a change in the object model, wehavetochangetheobject and change the database table, because without changing the table the application will be out ofsync with the database. Typically, a database schema migration has been a project in itself. For deployment of the schema changes, database change scripts are developed, using diff techniques, for all the changes in the development database. This approach of creating migration scripts during the deployment/release time is error-prone and does not support agile development methods.

It’s very hard to do schema migrations on large datasets in RDBMS, especially if we have to keep the database available to the applications, as large data movements and structural changes usually create locks on the database tables.

## 12.3. Schema Changes in a NoSQL Data Store

An RDBMS database has to be changed before the application is changed. This is what the schema-free, or schemaless, approach tries to avoid, aiming at flexibility of schema changes per entity. Frequent changes to the schema are needed to react to frequent market changes and product innovations.

When developing with NoSQL databases, in some cases the schema does not have to be thought about beforehand. We still have to design and think about other aspects, such as the types of relationships (with graph databases), or the names of the column families, rows, columns, order of columns (with column databases), or how are the keys assigned and what is the structure of the data inside the value object (with key-value stores). Even if we didn’t think about these up front, or if we want to change our decisions, it is easy to do so.

The claim that NoSQL databases are entirely schemaless is misleading; while they store the data without regard to the schema the data adheres to, that schema has to be defined by the application, because the data stream has to be parsed by the application when reading the data from the database. Also, the application has to create the data that would be saved in the database. If the application cannot parse the data from the database, we have a schema mismatch even if, instead of the RDBMS database throwing a error, this error is now encountered by the application. Thus, even in schemaless databases, the schema of the data has to be taken into consideration when refactoring the application. Schema changes especially matter when there is a deployed application and existing production data. 


### 12.3.1. Incremental Migration

![alt](https://martinfowler.com/articles/evodb/stages_refactoring.jpg)

Schema mismatch trips many new converts to the NoSQL world. When schema is changed on the application, we have to make sure to convert all the existing data to the new schema (depending on data size, this might be an expensive operation). Another option would be to make sure that data, before the schema changed, can still be parsed by the new code, and when it’s saved, it is saved back in the new schema. This technique, known as __incremental migration__, will migrate data over time; some data may never get migrated, because it was never accessed. 

When using incremental migration, there could be many versions of the object on the application side that can translate the old schema to the new schema; while saving the object back, it is saved using the new object. This gradual migration of the data helps the application evolve faster.

The incremental migration technique will complicate the object design, especially as new changes are being introduced yet old changes are not being taken out. This period between the change deployment and the last object in the database migrating to the new schema is known as the transition period. Keep it as short as possible and focus it to the minimum possible scope—this will help you keep your objects clean.

### 12.3.2. Migrations in Graph Databases

Graph databases have edges that have types and properties. If you change the type of these edges in the codebase, you no longer can traverse the database, rendering it unusable. To get around this, you can traverse all the edges and change the type of each edge. This operation can be expensive and requires you to write code to migrate all the edges in the database.

If we need to maintain backward compatibility or do not want to change the whole graph in one go, we can just create new edges between the nodes; later when we are comfortable about the change, the old edges can be dropped. We can use traversals with multiple edge types to traverse the graph using the new and old edge types. This technique may help a great deal with large databases, especially if we want to maintain high availability.

### 12.3.3. Changing Aggregate Structure

Sometimes you need to change the schema design, for example by splitting large objects into smaller ones that are stored independently. Suppose you have a customer aggregate that contains all the customers orders, and you want to separate the customer and each of their orders into different aggregate units.

You then have to ensure that the code can work with both versions of the aggregates. If it does not find the old objects, it will look for the new aggregates.

Code that runs in the background can read one aggregate at a time, make the necessary change, and save the data back into different aggregates. The advantage of operating on one aggregate at a time is that this way, you’re not affecting data availability for the application.

## 12.5. Key Points

* Databases with strong schemas, such as relational databases, can be migrated by saving each schema change, plus its data migration, in a version-controlled sequence.
* Schemaless databases still need careful migration due to the implicit schema in any code that accesses the data.
* Schemaless databases can use the same migration techniques as databases with strong schemas.
* Schemaless databases can also read data in a way that’s tolerant to changes in the data’s implicit schema and use incremental migration to update data.

# Chapter 13. Polyglot Persistence

Different databases are designed to solve different problems. Using a single database engine for all of the requirements usually leads to non- performant solutions; storing transactional data, caching session information, traversing graph of customers and the products their friends bought are essentially different problems. Even in the RDBMS space, the requirements of an OLAP and OLTP system are very different—nonetheless, they are often forced into the same schema.

## 13.1. Disparate Data Storage Needs

Many enterprises tend to use the same database engine to store business transactions, session management data, and for other storage needs such as reporting, BI, data warehousing, or logging information.

The session, shopping cart, or order data do not need the same properties of availability, consistency, or backup requirements. Does session management storage need the same rigorous backup/recovery strategy as the e-commerce orders data? Does the session management storage need more availability of an instance of database engine to write/read session data?

In 2006, Neal Ford coined the term __polyglot programming__, to express the idea that applications should be written in a mix of languages to take advantage of the fact that different languages are suitable for tackling different problems. Complex applications combine different types of problems, so picking the right language for each job may be more productive than trying to fit all aspects into a single language.

Similarly, when working on an e-commerce business problem, using a data store for the shopping cart which is highly available and can scale is important, but the same data store cannot help you find products bought by the customers’ friends —which is a totally different question. We use the term __polyglot persistence__ to define this hybrid approach to persistence.

## 13.2. Polyglot Data Store Usage

Let’s take our e-commerce example and use the polyglot persistence approach to see how some of these data stores can be applied. A key-value data store could be used to store the shopping cart data before the order is confirmed by the customer and also store the session data so that the RDBMS is not used for this transient data. Key-value stores make sense here since the shopping cart is usually accessed by user ID and, once confirmed and paid by the customer, can be saved in the RDBMS. Similarly, session data is keyed by the session ID.

![alt](http://ptgmedia.pearsoncmg.com/images/chap13_9780321826626/elementLinks/13fig02.jpg)

If we need to recommend products to customers when they place products into their shopping carts—for example, “ your friends also bought these products” or “ your friends bought these accessories for this product”—then introducing a graph data store in the mix becomes relevant.

![alt](http://ptgmedia.pearsoncmg.com/images/chap13_9780321826626/elementLinks/13fig03.jpg)

It is not necessary for the application to use a single data store for all of its needs, since different databases are built for different purposes and not all problems can be elegantly solved by a singe database.

Even using specialized relational databases for different purposes, such as data warehousing appliances or analytics appliances within the same application, can be viewed as polyglot persistence.

## 13.3. Service Usage over Direct Data Store Usage

As we move towards multiple data stores in the application, there may be other applications in the enterprise that could benefit from the use of our data stores or the data stored in them. Using our example, the graph data store can serve data to other applications that need to understand, for example, which products are being bought by a certain segment of the customer base.

Instead of each application talking independently to the graph database, we can wrap the graph database into a service so that all relationships between the nodes can be saved in one place and queried by all the applications. The data ownership and the APIs provided by the service are more useful than a single application talking to multiple databases.

![alt](http://ptgmedia.pearsoncmg.com/images/chap13_9780321826626/elementLinks/13fig04.jpg)

The philosophy of service wrapping can be taken further: You could wrap all databases into services, letting the application to only talk to a bunch of services. This allows for the databases inside the services to evolve without you having to change the dependent applications.

![alt](http://ptgmedia.pearsoncmg.com/images/chap13_9780321826626/elementLinks/13fig05.jpg)

Many NoSQL data store products, such as Riak and Neo4J, actually provide out-of-the-box REST API’s.

## 13.4. Expanding for Better Functionality

Often, we cannot really change the data storage for a specific usage to something different, because of the existing legacy applications and their dependency on existing data storage. We can, however, add functionality such as caching for better performance, or use indexing engines such as Solrso that search can be more efficient (Figure 13.6). When technologies like this are introduced, we have to make sure data is synchronized between the data storage for the application and the cache or indexing engine.

While doing this, we need to update the indexed data as the data in the application database changes. The process of updating the data can be real-time or batch, as long as we ensure that the application can deal with stale data in the index/search engine. The __event sourcing pattern__ can be used to update the index.

## 13.5. Choosing the Right Technology

There is a rich choice of data storage solutions. Initially, the pendulum had shifted from speciality databases to a single RDBMS database which allows all types of data models to be stored, although with some abstraction. The trend is now shifting back to using the data storage that supports the implementation of solutions natively.

If we want to recommend products to customers based on what’s in their shopping carts and which other products were bought by customers who bought those products, it can be implemented in any of the data stores by persisting the data with the correct attributes to answer our questions. The trick is to use the right technology, so that when the questions change, they can still be asked with the same data store without losing existing data or changing it into new formats.

Let’s go back to our new feature need. We can use RDBMS to solve this using a hierarchal query and modeling the tables accordingly. When we need to change the traversal, we will have to refactor the database, migrate the data, and start persisting new data. Instead, if we had used a data store that tracks relations between nodes, we could have just programmed the new relations and keep using the same data store with minimal changes.

## 13.6. Enterprise Concerns with Polyglot Persistence

Introduction of NoSQL data storage technologies will force the enterprise DBAs to think about how to use the new storage. The enterprise is used to having uniform RDBMS environments; whatever is the database an enterprise starts using first, chances are that over the years all its applications will be built around the same database. In this new world of polyglot persistence, the DBA groups will have to become more poly-skilled—to learn how some of these NoSQL technologies work, how to monitor these systems, back them up, and take data out of and put into these systems.

Once the enterprise decides to use any NoSQL technology, issues such as licensing, support, tools, upgrades, drivers, auditing, and security come up. Many NoSQL technologies are open-source and have an active community of supporters; also, there are companies that provide commercial support. There is not a rich ecosystem of tools, but the tool vendors and the open-source community are catching up, releasing tools such as MongoDB Monitoring Service [Monitoring], Datastax Ops Center [OpsCenter], or Rekon browser for Riak [Rekon].

One other area that enterprises are concerned about is security of the data—the ability to create users and assign privileges to see or not see data at the database level. Most of the NoSQL databases do not have very robust security features, but that’s because they are designed to operate differently. In traditional RDBMS, data was served by the database and we could get to the database using any query tools. With the NoSQL databases, there are query tools as well but the idea is for the application to own the data and serve it using services. With this approach, the responsibility for the security lies with the application. Having said that, there are NoSQL technologies that introduce security features.

## 13.8. Key Points

* Polyglot persistence is about using different data storage technologies to handle varying data storage needs.
* Polyglot persistence can apply across an enterprise or within a single application.
* Encapsulating data access into services reduces the impact of data storage choices on other parts of a system.
* Adding more data storage technologies increases complexity in programming and operations, so the advantages of a good data storage fit need to be weighed against this complexity.

# Chapter 14. Beyond NoSQL
