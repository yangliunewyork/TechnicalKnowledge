http://docs.couchdb.org/en/2.1.1/intro/index.html  

CouchDB is a database that completely embraces the web. Store your data with JSON documents. Access your documents with your web browser, via HTTP. Query, combine, and transform your documents with JavaScript. CouchDB works well with modern web and mobile apps. You can distribute your data, efficiently using CouchDB’s [incremental replication](http://docs.couchdb.org/en/2.1.1/replication/intro.html#replication-intro). CouchDB supports master-master setups with [automatic conflict detection](http://docs.couchdb.org/en/2.1.1/replication/conflicts.html#replication-conflicts).

CouchDB comes with a suite of features, such as on-the-fly document transformation and real-time change notifications, that make web development a breeze. It even comes with an easy to use web administration console, served directly out of CouchDB! We care a lot about distributed scaling. CouchDB is highly available and partition tolerant, but is also eventually consistent. And we care a lot about your data. CouchDB has a fault-tolerant storage engine that puts the safety of your data first.

## 1.1. Technical Overview

### 1.1.1. Document Storage

A CouchDB server hosts named databases, which store documents. Each document is uniquely named in the database, and CouchDB provides a RESTful HTTP API for reading and updating (add, edit, delete) database documents.

Documents are the primary unit of data in CouchDB and consist of any number of fields and attachments. Documents also include metadata that’s maintained by the database system. Document fields are uniquely named and contain values of varying types (text, number, boolean, lists, etc), and there is no set limit to text size or element count.

The CouchDB document update model is lockless and optimistic. Document edits are made by client applications loading documents, applying changes, and saving them back to the database. If another client editing the same document saves their changes first, the client gets an edit conflict error on save. To resolve the update conflict, the latest document version can be opened, the edits reapplied and the update tried again.

Document updates (add, edit, delete) are all or nothing, either succeeding entirely or failing completely. The database never contains partially saved or edited documents.

### 1.1.2. ACID Properties

The CouchDB file layout and commitment system features all __Atomic Consistent Isolated Durable (ACID)__ properties. On-disk, CouchDB never overwrites committed data or associated structures, ensuring the database file is always in a consistent state. This is a “crash-only” design where the CouchDB server does not go through a shut down process, it’s simply terminated.

Document updates (add, edit, delete) are serialized, except for binary blobs which are written concurrently. Database readers are never locked out and never have to wait on writers or other readers. Any number of clients can be reading documents without being locked out or interrupted by concurrent updates, even on the same document. CouchDB read operations use a __Multi-Version Concurrency Control (MVCC)__ model where each client sees a consistent snapshot of the database from the beginning to the end of the read operation.

Documents are indexed in __B-trees__ by their name (DocID) and a Sequence ID. Each update to a database instance generates a new sequential number. Sequence IDs are used later for incrementally finding changes in a database. These B-tree indexes are updated simultaneously when documents are saved or deleted. The index updates always occur at the end of the file (append-only updates).

Documents have the advantage of data being already conveniently packaged for storage rather than split out across numerous tables and rows in most database systems. When documents are committed to disk, the document fields and metadata are packed into buffers, sequentially one document after another (helpful later for efficient building of views).

When CouchDB documents are updated, all data and associated indexes are flushed to disk and the transactional commit always leaves the database in a completely consistent state. Commits occur in two steps:

All document data and associated index updates are synchronously flushed to disk.

The updated database header is written in two consecutive, identical chunks to make up the first 4k of the file, and then synchronously flushed to disk.

In the event of an OS crash or power failure during step 1, the partially flushed updates are simply forgotten on restart. If such a crash happens during step 2 (committing the header), a surviving copy of the previous identical headers will remain, ensuring coherency of all previously committed data. Excepting the header area, consistency checks or fix-ups after a crash or a power failure are never necessary.

### 1.1.3. Compaction

Wasted space is recovered by occasional compaction. On schedule, or when the database file exceeds a certain amount of wasted space, the compaction process clones all the active data to a new file and then discards the old file. The database remains completely online the entire time and all updates and reads are allowed to complete successfully. The old database file is deleted only when all the data has been copied and all users transitioned to the new file.

### 1.1.4. Views

ACID properties only deal with storage and updates, but we also need the ability to show our data in interesting and useful ways. Unlike SQL databases where data must be carefully decomposed into tables, data in CouchDB is stored in semi-structured documents. CouchDB documents are flexible and each has its own implicit structure, which alleviates the most difficult problems and pitfalls of bi-directionally replicating table schemas and their contained data.

But beyond acting as a fancy file server, a simple document model for data storage and sharing is too simple to build real applications on – it simply doesn’t do enough of the things we want and expect. We want to slice and dice and see our data in many different ways. What is needed is a way to filter, organize and report on data that hasn’t been decomposed into tables.

#### View Model
To address this problem of adding structure back to unstructured and semi-structured data, CouchDB integrates a view model. Views are the method of aggregating and reporting on the documents in a database, and are built on-demand to aggregate, join and report on database documents. Because views are built dynamically and don’t affect the underlying document, you can have as many different view representations of the same data as you like.

View definitions are strictly virtual and only display the documents from the current database instance, making them separate from the data they display and compatible with replication. CouchDB views are defined inside special design documents and can replicate across database instances like regular documents, so that not only data replicates in CouchDB, but entire application designs replicate too.

#### View Indexes

Views are a dynamic representation of the actual document contents of a database, and CouchDB makes it easy to create useful views of data. But generating a view of a database with hundreds of thousands or millions of documents is time and resource consuming, it’s not something the system should do from scratch each time.

To keep view querying fast, the view engine maintains indexes of its views, and incrementally updates them to reflect changes in the database. CouchDB’s core design is largely optimized around the need for efficient, incremental creation of views and their indexes.

Views and their functions are defined inside special “design” documents, and a design document may contain any number of uniquely named view functions. When a user opens a view and its index is automatically updated, all the views in the same design document are indexed as a single group.

The view builder uses the database sequence ID to determine if the view group is fully up-to-date with the database. If not, the view engine examines all database documents (in packed sequential order) changed since the last refresh. Documents are read in the order they occur in the disk file, reducing the frequency and cost of disk head seeks.

The views can be read and queried simultaneously while also being refreshed. If a client is slowly streaming out the contents of a large view, the same view can be concurrently opened and refreshed for another client without blocking the first client. This is true for any number of simultaneous client readers, who can read and query the view while the index is concurrently being refreshed for other clients without causing problems for the readers.

As documents are processed by the view engine through your ‘map’ and ‘reduce’ functions, their previous row values are removed from the view indexes, if they exist. If the document is selected by a view function, the function results are inserted into the view as a new row.

When view index changes are written to disk, the updates are always appended at the end of the file, serving to both reduce disk head seek times during disk commits and to ensure crashes and power failures can not cause corruption of indexes. If a crash occurs while updating a view index, the incomplete index updates are simply lost and rebuilt incrementally from its previously committed state.

### 1.1.6. Distributed Updates and Replication

CouchDB is a peer-based distributed database system. It allows users and servers to access and update the same shared data while disconnected. Those changes can then be replicated bi-directionally later.

The CouchDB document storage, view and security models are designed to work together to make true bi-directional replication efficient and reliable. Both documents and designs can replicate, allowing full database applications (including application design, logic and data) to be replicated to laptops for offline use, or replicated to servers in remote offices where slow or unreliable connections make sharing data difficult.

The replication process is incremental. At the database level, replication only examines documents updated since the last replication. Then for each updated document, only fields and blobs that have changed are replicated across the network. If replication fails at any step, due to network problems or crash for example, the next replication restarts at the same document where it left off.

Partial replicas can be created and maintained. Replication can be filtered by a JavaScript function, so that only particular documents or those meeting specific criteria are replicated. This can allow users to take subsets of a large shared database application offline for their own use, while maintaining normal interaction with the application and that subset of data.


#### Conflicts

Conflict detection and management are key issues for any distributed edit system. The CouchDB storage system treats edit conflicts as a common state, not an exceptional one. The conflict handling model is simple and “non-destructive” while preserving single document semantics and allowing for decentralized conflict resolution.

CouchDB allows for any number of conflicting documents to exist simultaneously in the database, with each database instance deterministically deciding which document is the “winner” and which are conflicts. Only the winning document can appear in views, while “losing” conflicts are still accessible and remain in the database until deleted or purged during database compaction. Because conflict documents are still regular documents, they replicate just like regular documents and are subject to the same security and validation rules.

When distributed edit conflicts occur, every database replica sees the same winning revision and each has the opportunity to resolve the conflict. Resolving conflicts can be done manually or, depending on the nature of the data and the conflict, by automated agents. The system makes decentralized conflict resolution possible while maintaining single document database semantics.

Conflict management continues to work even if multiple disconnected users or agents attempt to resolve the same conflicts. If resolved conflicts result in more conflicts, the system accommodates them in the same manner, determining the same winner on each machine and maintaining single document semantics.

#### Applications

Using just the basic replication model, many traditionally single server database applications can be made distributed with almost no extra work. CouchDB replication is designed to be immediately useful for basic database applications, while also being extendable for more elaborate and full-featured uses.

With very little database work, it is possible to build a distributed document management application with granular security and full revision histories. Updates to documents can be implemented to exploit incremental field and blob replication, where replicated updates are nearly as efficient and incremental as the actual edit differences (“diffs”).

The CouchDB replication model can be modified for other distributed update models. If the storage engine is enhanced to allow multi-document update transactions, it is possible to perform Subversion-like “all or nothing” atomic commits when replicating with an upstream server, such that any single document conflict or validation failure will cause the entire update to fail. Like Subversion, conflicts would be resolved by doing a “pull” replication to force the conflicts locally, then merging and re-replicating to the upstream server.

## 1.2. Why CouchDB?

### 1.2.1. Relax
If there’s one word to describe CouchDB, it is relax. It is the byline to CouchDB’s official logo and when you start CouchDB, you see:

Apache CouchDB has started. Time to relax.

Why is relaxation important? Developer productivity roughly doubled in the last five years. The chief reason for the boost is more powerful tools that are easier to use. Take Ruby on Rails as an example. It is an infinitely complex framework, but it’s easy to get started with. Rails is a success story because of the core design focus on ease of use. This is one reason why CouchDB is relaxing: learning CouchDB and understanding its core concepts should feel natural to most everybody who has been doing any work on the Web. And it is still pretty easy to explain to non-technical people.

Getting out of the way when creative people try to build specialized solutions is in itself a core feature and one thing that CouchDB aims to get right. We found existing tools too cumbersome to work with during development or in production, and decided to focus on making CouchDB easy, even a pleasure, to use.

Another area of relaxation for CouchDB users is the production setting. If you have a live running application, CouchDB again goes out of its way to avoid troubling you. Its internal architecture is fault-tolerant, and failures occur in a controlled environment and are dealt with gracefully. Single problems do not cascade through an entire server system but stay isolated in single requests.

CouchDB’s core concepts are simple (yet powerful) and well understood. Operations teams (if you have a team; otherwise, that’s you) do not have to fear random behavior and untraceable errors. If anything should go wrong, you can easily find out what the problem is, but these situations are rare.

CouchDB is also designed to handle varying traffic gracefully. For instance, if a website is experiencing a sudden spike in traffic, CouchDB will generally absorb a lot of concurrent requests without falling over. It may take a little more time for each request, but they all get answered. When the spike is over, CouchDB will work with regular speed again.

The third area of relaxation is growing and shrinking the underlying hardware of your application. This is commonly referred to as scaling. CouchDB enforces a set of limits on the programmer. On first look, CouchDB might seem inflexible, but some features are left out by design for the simple reason that if CouchDB supported them, it would allow a programmer to create applications that couldn’t deal with scaling up or down.

### 1.2.2. A Different Way to Model Your Data
We believe that CouchDB will drastically change the way you build document-based applications. CouchDB combines an intuitive document storage model with a powerful query engine in a way that’s so simple you’ll probably be tempted to ask, “Why has no one built something like this before?”

> Django may be built for the Web, but CouchDB is built of the Web. I’ve never seen software that so completely embraces the philosophies behind HTTP. CouchDB makes Django look old-school in the same way that Django makes ASP look outdated.
> —Jacob Kaplan-Moss, Django developer

CouchDB’s design borrows heavily from web architecture and the concepts of resources, methods, and representations. It augments this with powerful ways to query, map, combine, and filter your data. Add fault tolerance, extreme scalability, and incremental replication, and CouchDB defines a sweet spot for document databases.

### 1.2.5. CouchDB Replication
CouchDB replication is one of these building blocks. Its fundamental function is to synchronize two or more CouchDB databases. This may sound simple, but the simplicity is key to allowing replication to solve a number of problems: reliably synchronize databases between multiple machines for redundant data storage; distribute data to a cluster of CouchDB instances that share a subset of the total number of requests that hit the cluster (load balancing); and distribute data between physically distant locations, such as one office in New York and another in Tokyo.

CouchDB replication uses the same REST API all clients use. HTTP is ubiquitous and well understood. Replication works incrementally; that is, if during replication anything goes wrong, like dropping your network connection, it will pick up where it left off the next time it runs. It also only transfers data that is needed to synchronize databases.

A core assumption CouchDB makes is that things can go wrong, like network connection troubles, and it is designed for graceful error recovery instead of assuming all will be well. The replication system’s incremental design shows that best. The ideas behind “things that can go wrong” are embodied in the Fallacies of Distributed Computing:

* The network is reliable.
* Latency is zero.
* Bandwidth is infinite.
* The network is secure.
* Topology doesn’t change.
* There is one administrator.
* Transport cost is zero.
* The network is homogeneous.

Existing tools often try to hide the fact that there is a network and that any or all of the previous conditions don’t exist for a particular system. This usually results in fatal error scenarios when something finally goes wrong. In contrast, CouchDB doesn’t try to hide the network; it just handles errors gracefully and lets you know when actions on your end are required.

### 1.2.6. Local Data Is King
CouchDB takes quite a few lessons learned from the Web, but there is one thing that could be improved about the Web: latency. Whenever you have to wait for an application to respond or a website to render, you almost always wait for a network connection that isn’t as fast as you want it at that point. Waiting a few seconds instead of milliseconds greatly affects user experience and thus user satisfaction.

What do you do when you are offline? This happens all the time – your DSL or cable provider has issues, or your iPhone, G1, or Blackberry has no bars, and no connectivity means no way to get to your data.

CouchDB can solve this scenario as well, and this is where scaling is important again. This time it is scaling down. Imagine CouchDB installed on phones and other mobile devices that can synchronize data with centrally hosted CouchDBs when they are on a network. The synchronization is not bound by user interface constraints like sub-second response times. It is easier to tune for high bandwidth and higher latency than for low bandwidth and very low latency. Mobile applications can then use the local CouchDB to fetch data, and since no remote networking is required for that, latency is low by default.

Can you really use CouchDB on a phone? Erlang, CouchDB’s implementation language has been designed to run on embedded devices magnitudes smaller and less powerful than today’s phones.

## 1.3. Eventual Consistency

A distributed system is a system that operates robustly over a wide network. A particular feature of network computing is that network links can potentially disappear, and there are plenty of strategies for managing this type of network segmentation. CouchDB differs from others by accepting eventual consistency, as opposed to putting absolute consistency ahead of raw availability, like RDBMS or Paxos. What these systems have in common is an awareness that data acts differently when many people are accessing it simultaneously. Their approaches differ when it comes to which aspects of consistency, availability, or partition tolerance they prioritize.

Engineering distributed systems is tricky. Many of the caveats and “gotchas” you will face over time aren’t immediately obvious. We don’t have all the solutions, and CouchDB isn’t a panacea, but when you work with CouchDB’s grain rather than against it, the path of least resistance leads you to naturally scalable applications.

Of course, building a distributed system is only the beginning. A website with a database that is available only half the time is next to worthless. Unfortunately, the traditional relational database approach to consistency makes it very easy for application programmers to rely on global state, global clocks, and other high availability no-nos, without even realizing that they’re doing so. 

### 1.3.3. Local Consistency

Before we attempt to understand how CouchDB operates in a cluster, it’s important that we understand the inner workings of a single CouchDB node. The CouchDB API is designed to provide a convenient but thin wrapper around the database core. By taking a closer look at the structure of the database core, we’ll have a better understanding of the API that surrounds it.

#### The Key to Your Data
At the heart of CouchDB is a powerful B-tree storage engine. A B-tree is a sorted data structure that allows for searches, insertions, and deletions in logarithmic time. As Figure 2. Anatomy of a view request illustrates, CouchDB uses this B-tree storage engine for all internal data, documents, and views. If we understand one, we will understand them all.

<img src="http://docs.couchdb.org/en/2.1.1/_images/intro-consistency-02.png" width="500px;" height="400px;">


CouchDB uses MapReduce to compute the results of a view. MapReduce makes use of two functions, “map” and “reduce”, which are applied to each document in isolation. Being able to isolate these operations means that view computation lends itself to parallel and incremental computation. More important, because these functions produce key/value pairs, CouchDB is able to insert them into the B-tree storage engine, sorted by key. Lookups by key, or key range, are extremely efficient operations with a B-tree, described in big O notation as ```O(log N)``` and ```O(log N + K)```, respectively.

In CouchDB, we access documents and view results by key or key range. This is a direct mapping to the underlying operations performed on CouchDB’s B-tree storage engine. Along with document inserts and updates, this direct mapping is the reason we describe CouchDB’s API as being a thin wrapper around the database core.

Being able to access results by key alone is a very important restriction because it allows us to make huge performance gains. As well as the massive speed improvements, we can partition our data over multiple nodes, without affecting our ability to query each node in isolation. BigTable, Hadoop, SimpleDB, and memcached restrict object lookups by key for exactly these reasons.

#### No Locking

A table in a relational database is a single data structure. If you want to modify a table – say, update a row – the database system must ensure that nobody else is trying to update that row and that nobody can read from that row while it is being updated. The common way to handle this uses what’s known as a lock. If multiple clients want to access a table, the first client gets the lock, making everybody else wait. When the first client’s request is processed, the next client is given access while everybody else waits, and so on. This serial execution of requests, even when they arrived in parallel, wastes a significant amount of your server’s processing power. Under high load, a relational database can spend more time figuring out who is allowed to do what, and in which order, than it does doing any actual work.

Instead of locks, CouchDB uses Multi-Version Concurrency Control (MVCC) to manage concurrent access to the database. Figure 3. MVCC means no locking illustrates the differences between MVCC and traditional locking mechanisms. MVCC means that CouchDB can run at full speed, all the time, even under high load. Requests are run in parallel, making excellent use of every last drop of processing power your server has to offer.

<img src="http://docs.couchdb.org/en/2.1.1/_images/intro-consistency-03.png" width="300px;" height="300px;">

Documents in CouchDB are versioned, much like they would be in a regular version control system such as Subversion. If you want to change a value in a document, you create an entire new version of that document and save it over the old one. After doing this, you end up with two versions of the same document, one old and one new.

How does this offer an improvement over locks? Consider a set of requests wanting to access a document. The first request reads the document. While this is being processed, a second request changes the document. Since the second request includes a completely new version of the document, CouchDB can simply append it to the database without having to wait for the read request to finish.

When a third request wants to read the same document, CouchDB will point it to the new version that has just been written. During this whole process, the first request could still be reading the original version.

A read request will always see the most recent snapshot of your database at the time of the beginning of the request.

### 1.3.4. Validation

As application developers, we have to think about what sort of input we should accept and what we should reject. The expressive power to do this type of validation over complex data within a traditional relational database leaves a lot to be desired. Fortunately, CouchDB provides a powerful way to perform per-document validation from within the database.

CouchDB can validate documents using JavaScript functions similar to those used for MapReduce. Each time you try to modify a document, CouchDB will pass the validation function a copy of the existing document, a copy of the new document, and a collection of additional information, such as user authentication details. The validation function now has the opportunity to approve or deny the update.

By working with the grain and letting CouchDB do this for us, we save ourselves a tremendous amount of CPU cycles that would otherwise have been spent serializing object graphs from SQL, converting them into domain objects, and using those objects to do application-level validation.

### 1.3.5. Distributed Consistency

Maintaining consistency within a single database node is relatively easy for most databases. The real problems start to surface when you try to maintain consistency between multiple database servers. If a client makes a write operation on server A, how do we make sure that this is consistent with server B, or C, or D? For relational databases, this is a very complex problem with entire books devoted to its solution. You could use multi-master, single-master, partitioning, sharding, write-through caches, and all sorts of other complex techniques.

### 1.3.6. Incremental Replication

CouchDB’s operations take place within the context of a single document. As CouchDB achieves eventual consistency between multiple databases by using incremental replication you no longer have to worry about your database servers being able to stay in constant communication. Incremental replication is a process where document changes are periodically copied between servers. We are able to build what’s known as a shared nothing cluster of databases where each node is independent and self-sufficient, leaving no single point of contention across the system.

Need to scale out your CouchDB database cluster? Just throw in another server.

As illustrated in Figure 4. Incremental replication between CouchDB nodes, with CouchDB’s incremental replication, you can synchronize your data between any two databases however you like and whenever you like. After replication, each database is able to work independently.

You could use this feature to synchronize database servers within a cluster or between data centers using a job scheduler such as cron, or you could use it to synchronize data with your laptop for offline work as you travel. Each database can be used in the usual fashion, and changes between databases can be synchronized later in both directions.

![alt](http://docs.couchdb.org/en/2.1.1/_images/intro-consistency-04.png)

What happens when you change the same document in two different databases and want to synchronize these with each other? CouchDB’s replication system comes with automatic conflict detection and resolution. When CouchDB detects that a document has been changed in both databases, it flags this document as being in conflict, much like they would be in a regular version control system.

This isn’t as troublesome as it might first sound. When two versions of a document conflict during replication, the winning version is saved as the most recent version in the document’s history. Instead of throwing the losing version away, as you might expect, CouchDB saves this as a previous version in the document’s history, so that you can access it if you need to. This happens automatically and consistently, so both databases will make exactly the same choice.

It is up to you to handle conflicts in a way that makes sense for your application. You can leave the chosen document versions in place, revert to the older version, or try to merge the two versions and save the result.

