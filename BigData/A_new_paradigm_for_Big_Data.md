* Big Data Principles And Best Practices Of Scalable Realtime Data System

In the past decade the amount of data being created has skyrocketed. More than 30,000 gigabytes of data are generated every second, and the rate of data creation is only accelerating. The data we deal with is diverse. Users create content like blog posts, tweets, social network interactions, and photos. Servers continuously log messages about what they’re doing. Scientists create detailed measurements of the world around us. The internet, the ultimate source of data, is almost incomprehensibly large.

This astonishing growth in data has profoundly affected businesses. Traditional database systems, such as relational databases, have been pushed to the limit. In an increasing number of cases these systems are breaking under the pressures of “Big Data.” Traditional systems, and the data management techniques associated with them, have failed to scale to Big Data.

To tackle the challenges of Big Data, a new breed of technologies has emerged. Many of these new technologies have been grouped under the term NoSQL. In some ways, these new technologies are more complex than traditional databases, and in other ways they’re simpler. These systems can scale to vastly larger sets of data, but using these technologies effectively requires a fundamentally new set of techniques. They aren’t one-size-fits-all solutions.

Many of these Big Data systems were pioneered by Google, including distributed filesystems, the MapReduce computation framework, and distributed locking services. Another notable pioneer in the space was Amazon, which created an innovative distributed key/value store called Dynamo. The open source community responded in the years following with Hadoop, HBase, MongoDB, Cassandra, RabbitMQ, and countless other projects.



# A new paradigm for Big Data

### First principles

To figure out how to properly build data systems, you must go back to first principles. At the most fundamental level, what does a data system do? Let's start with an intuitive definition: A data system answers questions based on information that was acquired in the past up to the present.Data systems don’t just memorize and regurgitate information. They combine bits and pieces together to produce their answers.

Another crucial observation is that not all bits of information are equal. Some information is derived from other pieces of information. A bank account balance is derived from a transaction history. A friend count is derived from a friend list, and a friend list is derived from all the times a user added and removed friends from their profile. When you keep tracing back where information is derived from, you eventually end up at information that’s not derived from anything. This is the rawest information you have: information you hold to be true simply because it exists. Let’s call this information __data__.

If a data system answers questions by looking at past data, then the most generalpurpose data system answers questions by looking at the entire dataset. So the most general-purpose definition we can give for a data system is the following:

``` query = functionall data ```

Anything you could ever imagine doing with data can be expressed as a function that takes in all the data you have as input.


The Lambda Architecture provides a general-purpose approach to implementing an arbitrary function on an arbitrary dataset and having the function return its results with low latency. That doesn’t mean you’ll always use the exact same technologies every time you implement a data system. The specific technologies you use might change depending on your requirements. But the Lambda Architecture defines a consistent approach to choosing those technologies and to wiring them together to meet your requirements.


# Desired properties of a Big Data system

### Robustness and fault tolerance

Building systems that “do the right thing” is difficult in the face of the challenges of distributed systems. Systems need to behave correctly despite machines going down randomly, the complex semantics of consistency in distributed databases, duplicated data, concurrency, and more. These challenges make it difficult even to reason about what a system is doing. Part of making a Big Data system robust is avoiding these complexities so that you can easily reason about the system.

As discussed before, it’s imperative for systems to be __human-fault tolerant__. This is an oft-overlooked property of systems that we’re not going to ignore. In a production system, it’s inevitable that someone will make a mistake sometime, such as by deploying incorrect code that corrupts values in a database. If you build immutability and recomputation into the core of a Big Data system, the system will be innately resilient to human error by providing a clear and simple mechanism for recovery.

### Low latency reads and updates
The vast majority of applications require reads to be satisfied with very low latency, typically between a few milliseconds to a few hundred milliseconds. On the other hand, the update latency requirements vary a great deal between applications. Some applications require updates to propagate immediately, but in other applications a latency of a few hours is fine. Regardless, you need to be able to achieve low latency updates when you need them in your Big Data systems. More importantly, you need to be able to achieve low latency reads and updates without compromising the robustness of the system.

### Scalability

Scalability is the ability to maintain performance in the face of increasing data or load by adding resources to the system. The Lambda Architecture is horizontally scalable across all layers of the system stack: scaling is accomplished by adding more machines.

### Generalization
A general system can support a wide range of applications. Indeed, this book wouldn’t be very useful if it didn’t generalize to a wide range of applications! Because the Lambda Architecture is based on functions of all data, it generalizes to all applications, whether financial management systems, social media analytics, scientific applications, social networking, or anything else.

### Extensibility

You don’t want to have to reinvent the wheel each time you add a related feature or make a change to how your system works. Extensible systems allow functionality to be added with a minimal development cost. Oftentimes a new feature or a change to an existing feature requires a migration of old data into a new format. Part of making a system extensible is making it easy to do large-scale migrations. Being able to do big migrations quickly and easily is core to the approach you’ll learn.

### Ad hoc queries

Being able to do ad hoc queries on your data is extremely important. Nearly every large dataset has unanticipated value within it. Being able to mine a dataset arbitrarily gives opportunities for business optimization and new applications. Ultimately, you can’t discover interesting things to do with your data unless you can ask arbitrary questions of it.

### Minimal maintenance

Maintenance is a tax on developers. Maintenance is the work required to keep a system running smoothly. This includes anticipating when to add machines to scale, keeping processes up and running, and debugging anything that goes wrong in production. An important part of minimizing maintenance is choosing components that have as little implementation complexity as possible. You want to rely on components that have simple mechanisms underlying them. In particular, distributed databases tend to have very complicated internals. The more complex a system, the more likely something will go wrong, and the more you need to understand about the system to debug and tune it. You combat implementation complexity by relying on simple algorithms and simple components. A trick employed in the Lambda Architecture is to push complexity out of the core components and into pieces of the system whose outputs are discardable after a few hours. The most complex components used, like read/write distributed databases, are in this layer where outputs are eventually discardable.

### Debuggability
A Big Data system must provide the information necessary to debug the system when things go wrong. The key is to be able to trace, for each value in the system, exactly what caused it to have that value. “Debuggability” is accomplished in the Lambda Architecture through the functional nature of the batch layer and by preferring to use recomputation algorithms when possible. Achieving all these properties together in one system may seem like a daunting challenge. But by starting from first principles, as the Lambda Architecture does, these properties emerge naturally from the resulting system design.

# The problems with fully incremental architectures

### Operational complexity
There are many complexities inherent in fully incremental architectures that create difficulties in operating production infrastructure. Here we’ll focus on one: the need for read/write databases to perform online compaction, and what you have to do operationally to keep things running smoothly.

In a read/write database, as a disk index is incrementally added to and modified, parts of the index become unused. These unused parts take up space and eventually need to be reclaimed to prevent the disk from filling up. Reclaiming space as soon as it becomes unused is too expensive, so the space is occasionally reclaimed in bulk in a process called __compaction__.

Compaction is an intensive operation. The server places substantially higher demand on the CPU and disks during compaction, which dramatically lowers the performance of that machine during that time period. Databases such as HBase and Cassandra are well-known for requiring careful configuration and management to avoid problems or server lockups during compaction. The performance loss during compaction is a complexity that can even cause cascading failure—if too many machines compact at the same time, the load they were supporting will have to be handled by other machines in the cluster. This can potentially overload the rest of your cluster, causing total failure. We have seen this failure mode happen many times.

To manage compaction correctly, you have to schedule compactions on each node so that not too many nodes are affected at once. You have to be aware of how long a compaction takes—as well as the variance—to avoid having more nodes undergoing compaction than you intended. You have to make sure you have enough disk capacity on your nodes to last them between compactions. In addition, you have to make sure you have enough capacity on your cluster so that it doesn’t become overloaded when resources are lost during compactions.

All of this can be managed by a competent operational staff, but it’s our contention that the best way to deal with any sort of complexity is to get rid of that complexity Licensed to altogether. The fewer failure modes you have in your system, the less likely it is that you’ll suffer unexpected downtime. Dealing with online compaction is a complexity inherent to fully incremental architectures, but in a Lambda Architecture the primary databases don’t require any online compaction.

### Extreme complexity of achieving eventual consistency

Another complexity of incremental architectures results when trying to make systems highly available. A highly available system allows for queries and updates even in the presence of machine or partial network failure.

It turns out that achieving high availability competes directly with another important property called consistency. A consistent system returns results that take into account all previous writes. A theorem called the CAP theorem has shown that it’s impossible to achieve both high availability and consistency in the same system in the presence of network partitions. So a highly available system sometimes returns stale results during a network partition.

In order for a highly available system to return to consistency once a network partition ends (known as eventual consistency), a lot of help is required from your application. Take, for example, the basic use case of maintaining a count in a database. The obvious way to go about this is to store a number in the database and increment that number whenever an event is received that requires the count to go up. You may be surprised that if you were to take this approach, you抎 suffer massive data loss during network partitions.

The reason for this is due to the way distributed databases achieve high availability by keeping multiple replicas of all information stored. When you keep many copies of the same information, that information is still available even if a machine goes down or the network gets partitioned.During a network partition, a system that chooses to be highly available has clients update whatever replicas are reachable to them. This causes replicas to diverge and receive different sets of updates. Only when the partition goes away can the replicas be merged together into a common value.

Suppose you have two replicas with a count of 10 when a network partition begins. Suppose the first replica gets two increments and the second gets one increment. When it comes time to merge these replicas together, with values of 12 and 11, what should the merged value be? Although the correct answer is 13, there’s no way to know just by looking at the numbers 12 and 11. They could have diverged at 11 (in which case the answer would be 12), or they could have diverged at 0 (in which case the answer would be 23).

To do highly available counting correctly, it’s not enough to just store a count. You need a data structure that’s amenable to merging when values diverge, and you need to implement the code that will repair values once partitions end. This is an amazing amount of complexity you have to deal with just to maintain a simple count.

In general, handling eventual consistency in incremental, highly available systems is unintuitive and prone to error. This complexity is innate to highly available, fully incremental systems. You’ll see later how the Lambda Architecture structures itself in a different way that greatly lessens the burdens of achieving highly available, eventually consistent systems.

### Lack of human-fault tolerance
The last problem with fully incremental architectures we wish to point out is their inherent lack of human-fault tolerance. An incremental system is constantly modifying the state it keeps in the database, which means a mistake can also modify the state in the database. Because mistakes are inevitable, the database in a fully incremental architecture is guaranteed to be corrupted.

It's important to note that this is one of the few complexities of fully incremental architectures that can be resolved without a complete rethinking of the architecture. Consider the two architectures shown in figure 1.5: a synchronous architecture, where the application makes updates directly to the database, and an asynchronous architecture, where events go to a queue before updating the database in the background. In both cases, every event is permanently logged to an events datastore. By keeping every event, if a human mistake causes database corruption, you can go back to the events store and reconstruct the proper state for the database. Because the events store is immutable and constantly growing, redundant checks, like permissions, can be put in to make it highly unlikely for a mistake to trample over the events store. This technique is also core to the Lambda Architecture.

![alt](https://notes.shichao.io/bd/figure_1.5.png)

Although fully incremental architectures with logging can overcome the humanfault tolerance deficiencies of fully incremental architectures without logging, the logging does nothing to handle the other complexities that have been discussed.

# Lambda Architecture

The main idea of the Lambda Architecture is to build Big Data systems as a series of layers. Each layer satisfies a subset of the properties and builds upon the functionality provided by the layers beneath it.

Everything starts from the query = function(all data) equation. Ideally, you could run the functions on the fly to get the results. Unfortunately, even if this were possible, it would take a huge amount of resources to do and would be unreasonably expensive. Imagine having to read a petabyte dataset every time you wanted to answer the query of someone’s current location.

The most obvious alternative approach is to precompute the query function. Let抯 call the precomputed query function the batch view. Instead of computing the query on the fly, you read the results from the precomputed view. The precomputed view is indexed so that it can be accessed with random reads. This system looks like this:


```batch view = function(all data)```

```query = function(batch view) ```

In this system, you run a function on all the data to get the batch view. Then, when you want to know the value for a query, you run a function on that batch view. The batch view makes it possible to get the values you need from it very quickly, without having to scan everything in it.

![alt](http://blogs.quovantis.com/wp-content/uploads/2015/12/lambda4.jpg)

### Batch layer
The portion of the Lambda Architecture that implements the batch view = function(all data) equation is called the batch layer. The batch layer stores the master copy of the dataset and precomputes batch views on that master dataset. The master dataset can be thought of as a very large list of records.

The batch layer needs to be able to do two things: store an immutable, constantly growing master dataset, and compute arbitrary functions on that dataset. This type of processing is best done using batch-processing systems. Hadoop is the canonical example of a batch-processing system.

The simplest form of the batch layer can be represented in pseudo-code like this:

```
function runBatchLayer():
  while(true):
    recomputeBatchViews()
```

The batch layer runs in a while(true) loop and continuously recomputes the batch views from scratch.

The nice thing about the batch layer is that it’s so simple to use. Batch computations are written like single-threaded programs, and you get parallelism for free. It’s easy to write robust, highly scalable computations on the batch layer. The batch layer scales by adding new machines.

### Serving layer

The batch layer emits batch views as the result of its functions. The next step is to load the views somewhere so that they can be queried. This is where the serving layer comes in. The serving layer is a specialized distributed database that loads in a batch view and makes it possible to do random reads on it. When new batch views are available, the serving layer automatically swaps those in so that more up-to-date results are available.

A serving layer database supports batch updates and random reads. Most notably, it doesn’t need to support random writes. This is a very important point, as random writes cause most of the complexity in databases. By not supporting random writes, these databases are extremely simple. That simplicity makes them robust, predictable, easy to configure, and easy to operate. ElephantDB, the serving layer database you’ll learn to use in this book, is only a few thousand lines of code.

### Batch and serving layers satisfy almost all properties
The batch and serving layers support arbitrary queries on an arbitrary dataset with the trade-off that queries will be out of date by a few hours. It takes a new piece of data a few hours to propagate through the batch layer into the serving layer where it can be queried. The important thing to notice is that other than low latency updates, the batch and serving layers satisfy every property desired in a Big Data system,

* Robustness and fault tolerance—Hadoop handles failover when machines go down. The serving layer uses replication under the hood to ensure availability when servers go down. The batch and serving layers are also human-fault tolerant, because when a mistake is made, you can fix your algorithm or remove the bad data and recompute the views from scratch.

* Scalability—Both the batch and serving layers are easily scalable. They’re both fully distributed systems, and scaling them is as easy as adding new machines.

* Generalization—The architecture described is as general as it gets. You can compute and update arbitrary views of an arbitrary dataset.

* Extensibility—Adding a new view is as easy as adding a new function of the master dataset. Because the master dataset can contain arbitrary data, new types of data can be easily added. If you want to tweak a view, you don’t have to worry about supporting multiple versions of the view in the application. You can simply recompute the entire view from scratch.

* Ad hoc queries—The batch layer supports ad hoc queries innately. All the data is conveniently available in one location. 

* Minimal maintenance—The main component to maintain in this system is Hadoop. Hadoop requires some administration knowledge, but it’s fairly straightforward to operate. As explained before, the serving layer databases are simple because they don’t do random writes. Because a serving layer database has so few moving parts, there’s lots less that can go wrong. As a consequence, it’s much less likely that anything will go wrong with a serving layer database, so they’re easier to maintain. 

* Debuggability—You’ll always have the inputs and outputs of computations run on the batch layer. In a traditional database, an output can replace the original input—such as when incrementing a value. In the batch and serving layers, the input is the master dataset and the output is the views. Likewise, you have the inputs and outputs for all the intermediate steps. Having the inputs and outputs gives you all the information you need to debug when something goes wrong.

The beauty of the batch and serving layers is that they satisfy almost all the properties you want with a simple and easy-to-understand approach. There are no concurrency issues to deal with, and it scales trivially. The only property missing is low latency updates. The final layer, the speed layer, fixes this problem.

### Speed layer

The serving layer updates whenever the batch layer finishes precomputing a batch view. This means that the only data not represented in the batch view is the data that came in while the precomputation was running. All that’s left to do to have a fully realtime data system—that is, to have arbitrary functions computed on arbitrary data in real time—is to compensate for those last few hours of data. This is the purpose of the speed layer. As its name suggests, its goal is to ensure new data is represented in query functions as quickly as needed for the application requirements.

You can think of the speed layer as being similar to the batch layer in that it produces views based on data it receives. One big difference is that the speed layer only looks at recent data, whereas the batch layer looks at all the data at once. Another big difference is that in order to achieve the smallest latencies possible, the speed layer doesn’t look at all the new data at once. Instead, it updates the realtime views as it receives new data instead of recomputing the views from scratch like the batch layer does. The speed layer does incremental computation instead of the recomputation done in the batch layer.

We can formalize the data flow on the speed layer with the following equation:

``` realtime view = function(realtime view, new data)```

A realtime view is updated based on new data and the existing realtime view. The Lambda Architecture in full is summarized by these three equations:

``` batch view = function(all data) ```

``` realtime view = function(realtime view, new data) ```

``` query = function(batch view. realtime view) ```

Instead of resolving queries by just doing a function of the batch view, you resolve queries by looking at both the batch and realtime views and merging the results together.

![alt](https://notes.shichao.io/bd/figure_1.11.png)

A pictorial representation of these ideas is shown in figure here. Instead of resolving queries by just doing a function of the batch view, you resolve queries by looking at both the batch and realtime views and merging the results together.

The speed layer uses databases that support random reads and random writes. Because these databases support random writes, they’re orders of magnitude more complex than the databases you use in the serving layer, both in terms of implementation and operation.

The beauty of the Lambda Architecture is that once data makes it through the batch layer into the serving layer, the corresponding results in the realtime views are no longer needed. This means you can discard pieces of the realtime view as they’re no longer needed. This is a wonderful result, because the speed layer is far more complex than the batch and serving layers. This property of the Lambda Architecture is called complexity isolation, meaning that complexity is pushed into a layer whose results are only temporary. If anything ever goes wrong, you can discard the state for the entire speed layer, and everything will be back to normal within a few hours.














































































