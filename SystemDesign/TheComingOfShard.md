#### Source
* http://highscalability.com/blog/2009/8/6/an-unorthodox-approach-to-database-design-the-coming-of-the.html

## What Is Sharding?

Sharding is taking a single logical data model and partitioning it into disjoint subsets, ideally so that relationships between records in the data model do not span a single "shard". In practice, a shard is often an independent database instance. A simple example would be sharding a database of people by last name such that names that start with "a" are on shard 1, "b" are on shard 2, etc. Distributed hash tables are a special case of sharding; all records can be sharded but there will be no common relationship between records on a particular shard.

The importance of sharding is that it can be a simple way to build a scalable distributed database because each shard can be on a different machine. If relationships between records do not span shards then record insert/update operations only go to one database server and queries can often be distributed over the shards as well since the query can be partitioned into independent sub-queries over the shards. In a well designed sharding scheme, you can continue to add new shards and new database servers as your database grows.


Conventional sharding has significant limits. If a data model cannot be partitioned into disjoint sets then it often scales poorly. One example is data models where queries operate on complex relationships between records, such as a social graph database, because sub-queries between shards are not independent. Applications that require ad hoc join operations often scale very poorly when sharded. Another example is data models based on interval data types, such as geospatial polygons or temporal intervals. Intervals are not trivially reducible to a shard key that supports simple queries based on intersection or containment relationships, the most common query operations for interval data types. These are all issues to be aware of when designing a sharded data model.

The advantages are:

* __High availability__. If one box goes down the others still operate.
* __Faster queries__. Smaller amounts of data in each user group mean faster querying.
* __More write bandwidth__. With no master database serializing writes you can write in parallel which increases your write throughput. Writing is major bottleneck for many websites.
* __You can do more work__. A parallel backend means you can do more work simultaneously. You can handle higher user loads, especially when writing data, because there are parallel paths through your system. You can load balance web servers, which access shards over different network paths, which are processed by separate CPUs, which use separate caches of RAM and separate disk IO paths to process work. Very few bottlenecks limit your work.

## How Is Sharding Different Than Traditional Architectures?
* __Data are denormalized__. Traditionally we normalize data. Data are splayed out into anomaly-less tables and then joined back together again when they need to be used. In sharding the data are denormalized. You store together data that are used together. This doesn't mean you don't also segregate data by type. You can keep a user's profile data separate from their comments, blogs, email, media, etc, but the user profile data would be stored and retrieved as a whole. This is a very fast approach. You just get a blob and store a blob. No joins are needed and it can be written with one disk write.

* __Data are parallelized across many physical instances__. Historically database servers are scaled up. You buy bigger machines to get more power. With sharding the data are parallelized and you scale by scaling out. Using this approach you can get massively more work done because it can be done in parallel.

* __Data are kept small__. The larger a set of data a server handles the harder it is to cash intelligently because you have such a wide diversity of data being accessed. You need huge gobs of RAM that may not even be enough to cache the data when you need it. By isolating data into smaller shards the data you are accessing is more likely to stay in cache. Smaller sets of data are also easier to backup, restore, and manage.

* __Data are more highly available__. Since the shards are independent a failure in one doesn't cause a failure in another. And if you make each shard operate at 50% capacity it's much easier to upgrade a shard in place. Keeping multiple data copies within a shard also helps with redundancy and making the data more parallelized so more work can be done on the data. You can also setup a shard to have a master-slave or dual master relationship within the shard to avoid a single point of failure within the shard. If one server goes down the other can take over.
* __It doesn't use replication__. Replicating data from a master server to slave servers is a traditional approach to scaling. Data is written to a master server and then replicated to one or more slave servers. At that point read operations can be handled by the slaves, but all writes happen on the master. Obviously the master becomes the write bottleneck and a single point of failure. And as load increases the cost of replication increases. Replication costs in CPU, network bandwidth, and disk IO. The slaves fall behind and have stale data. Sharding cleanly and elegantly solves the problems with replication.

## Some Problems With Sharding
* __Rebalancing data__. What happens when a shard outgrows your storage and needs to be split? Let's say some user has a particularly large friends list that blows your storage capacity for the shard. You need to move the user to a different shard.On some platforms I've worked on this is a killer problem. You had to build out the data center correctly from the start because moving data from shard to shard required a lot of downtime.Rebalancing has to be built in from the start. Google's shards automatically rebalance. For this to work data references must go through some sort of naming service so they can be relocated. This is what Flickr does. And your references must be invalidateable so the underlying data can be moved while you are using it.
* __Joining data from multiple shards__. To create a complex friends page, or a user profile page, or a thread discussion page, you usually must pull together lots of different data from many different sources. With sharding you can't just issue a query and get back all the data. You have to make individual requests to your data sources, get all the responses, and the build the page. Thankfully, because of caching and fast networks this process is usually fast enough that your page load times can be excellent.
* __How do you partition your data in shards__? What data do you put in which shard? Where do comments go? Should all user data really go together, or just their profile data? Should a user's media, IMs, friends lists, etc go somewhere else? Unfortunately there are no easy answer to these questions.
* __Less leverage__. People have experience with traditional RDBMS tools so there is a lot of help out there. You have books, experts, tool chains, and discussion forums when something goes wrong or you are wondering how to implement a new feature. Eclipse won't have a shard view and you won't find any automated backup and restore programs for your shard. With sharding you are on your own. 
* __Implementing shards is not well supported__. Sharding is currently mostly a roll your own approach. LiveJournal makes their tool chain available. Hibernate has a library under development. MySQL has added support for partioning. But in general it's still something you must implement yourself.

## Examples
* http://highscalability.com/flickr-architecture
* http://highscalability.com/google-architecture
* http://highscalability.com/livejournal-architecture
