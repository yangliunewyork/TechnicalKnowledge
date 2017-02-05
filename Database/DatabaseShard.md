## What is Shard ?
A database shard is a horizontal partition of data in a database or search engine. Each individual partition is referred to as a shard or database shard. Each shard is held on a separate database server instance, to spread load.
Some data within a database remains present in all shards, but some appears only in a single shard. Each shard (or server) acts as the single source for this subset of data.

## Database architecture
Horizontal partitioning is a database design principle whereby rows of a database table are held separately, rather than being split into columns (which is what normalization and vertical partitioning do, to differing extents). Each partition forms part of a shard, which may in turn be located on a separate database server or physical location.

There are numerous advantages to the horizontal partitioning approach. Since the tables are divided and distributed into multiple servers, the total number of rows in each table in each database is reduced. This reduces index size, which generally improves search performance. A database shard can be placed on separate hardware, and multiple shards can be placed on multiple machines. This enables a distribution of the database over a large number of machines, greatly improving performance. In addition, if the database shard is based on some real-world segmentation of the data (e.g., European customers v. American customers) then it may be possible to infer the appropriate shard membership easily and automatically, and query only the relevant shard.

Disadvantages include :
* A heavier reliance on the interconnect between servers
* Increased latency when querying, especially where more than one shard must be searched.
* Data or indexes are often only sharded one way, so that some searches are optimal, and others are slow or impossible.
* Issues of consistency and durability due to the more complex failure modes of a set of servers, which often result in systems making no guarantees about cross-shard consistency or durability.

In practice, sharding is complex. Although it has been done for a long time by hand-coding (especially where rows have an obvious grouping, as per the example above), this is often inflexible. There is a desire to support sharding automatically, both in terms of adding code support for it, and for identifying candidates to be sharded separately. __Consistent hashing__ is one form of automatic sharding to spread large loads across multiple smaller services and servers.

Where __distributed computing__ is used to separate load between multiple servers (either for performance or reliability reasons), a shard approach may also be useful.

## Shards compared to horizontal partitioning
Horizontal partitioning splits one or more tables by row, usually within a single instance of a schema and a database server. It may offer an advantage by reducing index size (and thus search effort) provided that there is some obvious, robust, implicit way to identify in which partition a particular row will be found, without first needing to search the index, e.g., the classic example of the 'CustomersEast' and 'CustomersWest' tables, where their zip code already indicates where they will be found.

Sharding goes beyond this: it partitions the problematic table(s) in the same way, but it does this across potentially multiple instances of the schema. The obvious advantage would be that search load for the large partitioned table can now be split across multiple servers (logical or physical), not just multiple indexes on the same logical server.
Splitting shards across multiple isolated instances requires more than simple horizontal partitioning. The hoped-for gains in efficiency would be lost, if querying the database required both instances to be queried, just to retrieve a simple dimension table. Beyond partitioning, sharding thus splits large partitionable tables across the servers, while smaller tables are replicated as complete units.

This is also why sharding is related to a shared nothing architecture—once sharded, each shard can live in a totally separate logical schema instance / physical database server / data center / continent. There is no ongoing need to retain shared access (from between shards) to the other unpartitioned tables in other shards.

This makes replication across multiple servers easy (simple horizontal partitioning does not). It is also useful for worldwide distribution of applications, where communications links between data centers would otherwise be a bottleneck.
There is also a requirement for some notification and replication mechanism between schema instances, so that the unpartitioned tables remain as closely synchronized as the application demands. This is a complex choice in the architecture of sharded systems: approaches range from making these effectively read-only (updates are rare and batched), to dynamically replicated tables (at the cost of reducing some of the distribution benefits of sharding) and many options in between.

## Disadvantages of sharding
Sharding a database table before it has been optimized locally causes premature complexity. Sharding should be used only when all other options for optimization are inadequate. The introduced complexity of database sharding causes the following potential problems:
* Increased complexity of SQL - Increased bugs because the developers have to write more complicated SQL to handle sharding logic.
* Sharding introduces complexity - The sharding software that partitions, balances, coordinates, and ensures integrity can fail.
* Single point of failure - Corruption of one shard due to network/hardware/systems problems causes failure of the entire table.
* Failover servers more complex - Failover servers must themselves have copies of the fleets of database shards.
* Backups more complex - Database backups of the individual shards must be coordinated with the backups of the other shards.
* Operational complexity added - Adding/removing indexes, adding/deleting columns, modifying the schema becomes much more difficult.

## What's the difference between sharding DB tables and partitioning them?
__Partitioning is a general term used to describe the act of breaking up your logical data elements into multiple entities for the purpose of performance, availability, or maintainability.__  

__Sharding is the equivalent of "horizontal partitioning".__  When you shard a database, you create replica's of the schema, and then divide what data is stored in each shard based on a shard key.  For example, I might shard my customer database using CustomerId as a shard key - I'd store ranges 0-10000 in one shard and 10001-20000 in a different shard.  When choosing a shard key, the DBA will typically look at data-access patterns and space issues to ensure that they are distributing load and space across shards evenly.  
__"Vertical partitioning" is the act of splitting up the data stored in one entity into multiple entities - again for space and performance reasons.__  For example, a customer might only have one billing address, yet I might choose to put the billing address information into a separate table with a CustomerId reference so that I have the flexibility to move that information into a separate database, or different security context, etc.    

To summarize - partitioning is a generic term that just means dividing your logical entities into different physical entities for performance, availability, or some other purpose.  "Horizontal partitioning", or sharding, is replicating the schema, and then dividing the data based on a shard key.  "Vertical partitioning" involves dividing up the schema (and the data goes along for the ride).  

__Final note: you can combine both horizontal and vertical partitioning techniques - sometimes required in big data, high traffic environments.__

SOSP paper on DynamoDB mentions:
> “Data is distributed across multiple servers using partitioning, and each partition is further replicated to provide availability. The technique for distributing (aka partitioning) is consistent hashing”.

MongoDB’s online manual:
> “Sharding is a method to distribute data across multiple different servers. We achieve horizontal scalability through sharding”.


