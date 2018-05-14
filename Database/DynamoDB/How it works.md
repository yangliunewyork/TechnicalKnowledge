# DynamoDB Core Components

In DynamoDB, tables, items, and attributes are the core components that you work with. A table is a collection of items, and each item is a collection of attributes. DynamoDB uses primary keys to uniquely identify each item in a table and secondary indexes to provide more querying flexibility. You can use DynamoDB Streams to capture data modification events in DynamoDB tables.

### Tables, Items, and Attributes

* Tables – Similar to other database systems, DynamoDB stores data in tables. A table is a collection of data. For example, see the example table called People that you could use to store personal contact information about friends, family, or anyone else of interest. You could also have a Cars table to store information about vehicles that people drive.  
* Items – Each table contains zero or more items. An item is a group of attributes that is uniquely identifiable among all of the other items. In a People table, each item represents a person. For a Cars table, each item represents one vehicle. Items in DynamoDB are similar in many ways to rows, records, or tuples in other database systems. In DynamoDB, there is no limit to the number of items you can store in a table.  
* Attributes – Each item is composed of one or more attributes. An attribute is a fundamental data element, something that does not need to be broken down any further. For example, an item in a People table contains attributes called PersonID, LastName, FirstName, and so on. For a Department table, an item might have attributes such as DepartmentID, Name,Manager, and so on. Attributes in DynamoDB are similar in many ways to fields or columns in other database systems.  

The following diagram shows a table named People with some example items and attributes.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Database/DynamoDB/Photos/People%20Table.PNG">

Note the following about the People table:

* __Each item in the table has a unique identifier, or primary key, that distinguishes the item from all of the others in the table.__ In the People table, the primary key consists of one attribute (PersonID).  
* Other than the primary key, the People table is schemaless, which means that neither the attributes nor their data types need to be defined beforehand. Each item can have its own distinct attributes.  
* Most of the attributes are scalar, which means that they can have only one value. Strings and numbers are common examples of scalars.  
* Some of the items have a nested attribute (Address). DynamoDB supports nested attributes up to 32 levels deep.  

The following is another example table named Music that you could use to keep track of your music collection.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Database/DynamoDB/Photos/Music%20Table.PNG">

Note the following about the Music table:

* The primary key for Music consists of two attributes (Artist and SongTitle). Each item in the table must have these two attributes. The combination of Artist and SongTitle distinguishes each item in the table from all of the others.
* Other than the primary key, the Music table is schemaless, which means that neither the attributes nor their data types need to be defined beforehand. Each item can have its own distinct attributes.
* One of the items has a nested attribute (PromotionInfo), which contains other nested attributes. DynamoDB supports nested attributes up to 32 levels deep.

### Primary Key

When you create a table, in addition to the table name, you must specify the primary key of the table. The primary key uniquely identifies each item in the table, so that no two items can have the same key. DynamoDB supports two different kinds of primary keys:

* __Partition key – A simple primary key, composed of one attribute known as the partition key.__ DynamoDB uses the partition key's value as input to an internal hash function. The output from the hash function determines the partition (physical storage internal to DynamoDB) in which the item will be stored. In a table that has only a partition key, no two items can have the same partition key value. The People table described in Tables, Items, and Attributes (p. 2) is an example of a table with a simple primary key (PersonID). You can access any item in the People table directly by providing the PersonId value for that item.  
* __Partition key and sort key – Referred to as a composite primary key, this type of key is composed of two attributes.__ __The first attribute is the partition key, and the second attribute is the sort key__. DynamoDB uses the partition key value as input to an internal hash function. The output from the hash function determines the partition (physical storage internal to DynamoDB) in which the item will be stored. All items with the same partition key are stored together, in sorted order by sort key value. In a table that has a partition key and a sort key, it's possible for two items to have the same partition key value. However, those two items must have different sort key values. The Music table described in Tables, Items, and Attributes (p. 2) is an example of a table with a composite primary key (Artist and SongTitle). You can access any item in the Music table directly, if you provide the Artist and SongTitle values for that item. A composite primary key gives you additional flexibility when querying data. For example, if you provide only the value for Artist, DynamoDB retrieves all of the songs by that artist. To retrieve only a subset of songs by a particular artist, you can provide a value for Artist along with a range of values for SongTitle.  

__Note:The partition key of an item is also known as its hash attribute. The term hash attribute derives from the use of an internal hash function in DynamoDB that evenly distributes data items across partitions, based on their partition key values. The sort key of an item is also known as its range attribute. The term range attribute derives from the way DynamoDB stores items with the same partition key physically close together, in sorted order by the sort key value.__

Each primary key attribute must be a scalar (meaning that it can hold only a single value). The only data types allowed for primary key attributes are string, number, or binary. There are no such restrictions for other, non-key attributes.  

### Secondary Indexes

You can create one or more secondary indexes on a table. A secondary index lets you query the data in the table using an alternate key, in addition to queries against the primary key. DynamoDB doesn't require that you use indexes, but they give your applications more flexibility when querying your data. After you create a secondary index on a table, you can read data from the index in much the same way as you do from the table. DynamoDB supports two kinds of indexes:

* Global secondary index – An index with a partition key and sort key that can be different from those on the table.   
* Local secondary index – An index that has the same partition key as the table, but a different sort key.  

### DynamoDB Streams

DynamoDB Streams is an optional feature that captures data modification events in DynamoDB tables.
The data about these events appear in the stream in near real time, and in the order that the events occurred. Each event is represented by a stream record. If you enable a stream on a table, DynamoDB Streams writes a stream record whenever one of the following events occurs:

* A new item is added to the table: The stream captures an image of the entire item, including all of its attributes.
* An item is updated: The stream captures the "before" and "after" image of any attributes that were modified in the item.
* An item is deleted from the table: The stream captures an image of the entire item before it was deleted.

Each stream record also contains the name of the table, the event timestamp, and other metadata. Stream records have a lifetime of 24 hours; after that, they are automatically removed from the stream.

<img src="https://docs.aws.amazon.com/amazondynamodb/latest/developerguide/images/HowItWorksStreams.png">  

# Read Consistency

Amazon DynamoDB is available in multiple AWS regions around the world. Each region is independent and isolated from other AWS regions. For example, if you have a table called People in the us-east-2 region and another table named People in the us-west-2 region, these are considered two entirely separate tables. 

Every AWS region consists of multiple distinct locations called Availability Zones. Each Availability Zone is isolated from failures in other Availability Zones, and provides inexpensive, low-latency network connectivity to other Availability Zones in the same region. This allows rapid replication of your data among multiple Availability Zones in a region.

When your application writes data to a DynamoDB table and receives an HTTP 200 response (OK), all copies of the data are updated. The data is eventually consistent across all storage locations, usually within one second or less.

DynamoDB supports __eventually consistent__ and __strongly consistent reads__.

* Eventually Consistent Reads : When you read data from a DynamoDB table, the response might not reflect the results of a recently completed write operation. The response might include some stale data. If you repeat your read request after a short time, the response should return the latest data.  
* Strongly Consistent Reads : When you request a strongly consistent read, DynamoDB returns a response with the most up-to-date data, reflecting the updates from all prior write operations that were successful. A strongly consistent read might not be available if there is a network delay or outage.  

# Throughput Capacity for Reads and Writes

When you create a table or index in Amazon DynamoDB, you must specify your capacity requirements for read and write activity. By defining your throughput capacity in advance, DynamoDB can reserve the necessary resources to meet the read and write activity your application requires, while ensuring consistent, low-latency performance.

You specify throughput capacity in terms of read capacity units and write capacity units:

* One read capacity unit represents one strongly consistent read per second, or two eventually consistent reads per second, for an item up to 4 KB in size. If you need to read an item that is larger than 4 KB, DynamoDB will need to consume additional read capacity units. The total number of read capacity units required depends on the item size, and whether you want an eventually consistent or strongly consistent read.  
* One write capacity unit represents one write per second for an item up to 1 KB in size. If you need to write an item that is larger than 1 KB, DynamoDB will need to consume additional write capacity units. The total number of write capacity units required depends on the item size.  

For example, suppose that you create a table with 5 read capacity units and 5 write capacity units. With these settings, your application could:

* Perform strongly consistent reads of up to 20 KB per second (4 KB × 5 read capacity units).
* Perform eventually consistent reads of up to 40 KB per second (twice as much read throughput).
* Write up to 5 KB per second (1 KB × 5 write capacity units).

If your application reads or writes larger items (up to the DynamoDB maximum item size of 400 KB), it will consume more capacity units.

If your read or write requests exceed the throughput settings for a table, DynamoDB can throttle that request. DynamoDB can also throttle read requests exceeds for an index. Throttling prevents your application from consuming too many capacity units. When a request is throttled, it fails with an HTTP 400 code (Bad Request) and a ProvisionedThroughputExceededException. The AWS SDKs have built-in support for retrying throttled requests (see Error Retries and Exponential Backoff), so you do not need to write this logic yourself.

You can use the AWS Management Console to monitor your provisioned and actual throughput, and to modify your throughput settings if necessary.

DynamoDB provides the following mechanisms for managing throughput:

* DynamoDB auto scaling  
* Provisioned throughput  
* Reserved capacity  

#### DynamoDB Auto Scaling  

DynamoDB auto scaling actively manages throughput capacity for tables and global secondary indexes. With auto scaling, you define a range (upper and lower limits) for read and write capacity units. You also define a target utilization percentage within that range. DynamoDB auto scaling seeks to maintain your target utilization, even as your application workload increases or decreases.

With DynamoDB auto scaling, a table or a global secondary index can increase its provisioned read and write capacity to handle sudden increases in traffic, without request throttling. When the workload decreases, DynamoDB auto scaling can decrease the throughput so that you don't pay for unused provisioned capacity.  

#### Provisioned Throughput

If you aren't using DynamoDB auto scaling, you have to manually define your throughput requirements. Provisioned throughput is the maximum amount of capacity that an application can consume from a table or index. If your application exceeds your provisioned throughput settings, it is subject to request throttling.

#### Reserved Capacity

As a DynamoDB customer, you can purchase reserved capacity in advance, as described at Amazon DynamoDB Pricing. With reserved capacity, you pay a one-time upfront fee and commit to a minimum usage level over a period of time. By reserving your read and write capacity units ahead of time, you realize significant cost savings compared to on-demand provisioned throughput settings.  

# Partitions and Data Distribution

DynamoDB stores data in partitions. A partition is an allocation of storage for a table, backed by solid-state drives (SSDs) and automatically replicated across multiple Availability Zones within an AWS Region. Partition management is handled entirely by DynamoDB—you never have to manage partitions yourself.

When you create a table, the initial status of the table is CREATING. During this phase, DynamoDB allocates sufficient partitions to the table so that it can handle your provisioned throughput requirements. You can begin writing and reading table data after the table status changes to ACTIVE.

DynamoDB allocates additional partitions to a table in the following situations:

* If you increase the table's provisioned throughput settings beyond what the existing partitions can support.  
* If an existing partition fills to capacity and more storage space is required.  

Partition management occurs automatically in the background and is transparent to your applications. Your table remains available throughout and fully supports your provisioned throughput requirements.  

Global secondary indexes in DynamoDB are also composed of partitions. The data in a GSI is stored separately from the data in its base table, but index partitions behave in much the same way as table partitions.

### Data Distribution: Partition Key

If your table has a simple primary key (partition key only), DynamoDB stores and retrieves each item based on its partition key value.

To write an item to the table, DynamoDB uses the value of the partition key as input to an internal hash function. The output value from the hash function determines the partition in which the item will be stored.

To read an item from the table, you must specify the partition key value for the item. DynamoDB uses this value as input to its hash function, yielding the partition in which the item can be found.

### Data Distribution: Partition Key and Sort Key

If the table has a composite primary key (partition key and sort key), DynamoDB calculates the hash value of the partition key in the same way as described in Data Distribution: Partition Key—but it stores all of the items with the same partition key value physically close together, ordered by sort key value.

To write an item to the table, DynamoDB calculates the hash value of the partition key to determine which partition should contain the item. In that partition, there could be several items with the same partition key value, so DynamoDB stores the item among the others with the same partition key, in ascending order by sort key.

To read an item from the table, you must specify its partition key value and sort key value. DynamoDB calculates the partition key's hash value, yielding the partition in which the item can be found.

You can read multiple items from the table in a single operation (Query), provided that the items you want have the same partition key value. DynamoDB returns all of the items with that partition key value. Optionally, you can apply a condition to the sort key so that it returns only the items within a certain range of values.


