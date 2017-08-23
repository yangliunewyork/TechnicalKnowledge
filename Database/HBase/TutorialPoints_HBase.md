# Introduction

Since 1970, RDBMS is the solution for data storage and maintenance related problems. After the advent of big data, companies realized the benefit of processing big data and started opting for solutions like Hadoop.

Hadoop uses distributed file system for storing big data, and MapReduce to process it. Hadoop excels in storing and processing of huge data of various formats such as arbitrary, semi-, or even unstructured.

##### Limitations of Hadoop
Hadoop can perform only batch processing, and data will be accessed only in a sequential manner. That means one has to search the entire dataset even for the simplest of jobs.

A huge dataset when processed results in another huge data set, which should also be processed sequentially. At this point, a new solution is needed to access any point of data in a single unit of time (random access).

Applications such as HBase, Cassandra, couchDB, Dynamo, and MongoDB are some of the databases that store huge amounts of data and access the data in a random manner.

##### What is HBase?

HBase is a distributed column-oriented database built on top of the Hadoop file system. It is an open-source project and is horizontally scalable.

HBase is a data model that is similar to Google’s big table designed to provide quick random access to huge amounts of structured data. It leverages the fault tolerance provided by the Hadoop File System (HDFS).

It is a part of the Hadoop ecosystem that provides random real-time read/write access to data in the Hadoop File System.

One can store the data in HDFS either directly or through HBase. Data consumer reads/accesses the data in HDFS randomly using HBase. HBase sits on top of the Hadoop File System and provides read and write access.

![alt](https://www.tutorialspoint.com/hbase/images/hbase_flow.jpg)

##### HBase and HDFS

HDFS is a distributed file system and has the following properties:
1. It is optimized for streaming access of large files. You would typically store files that are in the 100s of MB upwards on HDFS and access them through MapReduce to process them in batch mode. 
2. HDFS files are write once files. You can append to files in some of the recent versions but that is not a feature that is very commonly used. Consider HDFS files as write-once and read-many files. There is no concept of random writes.
3. HDFS doesn't do random reads very well.

HBase on the other hand is a database that stores it's data in a distributed filesystem. The filesystem of choice typically is HDFS owing to the tight integration between HBase and HDFS. Having said that, it doesn't mean that HBase can't work on any other filesystem. It's just not proven in production and at scale to work with anything except HDFS.
HBase provides you with the following:
1. Low latency access to small amounts of data from within a large data set. You can access single rows quickly from a billion row table.
2. Flexible data model to work with and data is indexed by the row key.
3. Fast scans across tables.
4. Scale in terms of writes as well as total volume of data.

An analogous comparison would be between MySQL and Ext4.

| HDFS        | HBase           |
| ------------- |:-------------:| 
| HDFS is a distributed file system suitable for storing large files.      | HBase is a database built on top of the HDFS. | 
| HDFS does not support fast individual record lookups.      | HBase provides fast lookups for larger tables.      |  
| It provides high latency batch processing; no concept of batch processing. | It provides low latency access to single rows from billions of records (Random access).      | 
| It provides only sequential access of data. | HBase internally uses Hash tables and provides random access, and it stores the data in indexed HDFS files for faster lookups.      | 

##### torage Mechanism in HBase
HBase is a column-oriented database and the tables in it are sorted by row. The table schema defines only column families, which are the key value pairs. A table have multiple column families and each column family can have any number of columns. Subsequent column values are stored contiguously on the disk. Each cell value of the table has a timestamp. In short, in an HBase:

* Table is a collection of rows.
* Row is a collection of column families.
* Column family is a collection of columns.
* Column is a collection of key value pairs.

##### Column Oriented and Row Oriented
Column-oriented databases are those that store data tables as sections of columns of data, rather than as rows of data. Shortly, they will have column families.

| Row-Oriented Database       | Column-Oriented Database           |
| ------------- |:-------------:| 
| It is suitable for Online Transaction Process (OLTP).      | An RDBMS is governed by its schema, which describes the whole structure of tables.| 
| Such databases are designed for small number of rows and columns.     | Column-oriented databases are designed for huge tables.      | 

##### HBase and RDBMS

| HBase       | RDBMS           |
| ------------- |:-------------:| 
| HBase is schema-less, it doesn't have the concept of fixed columns schema; defines only column families.   | It is suitable for Online Analytical Processing (OLAP). | 
| It is built for wide tables. HBase is horizontally scalable.  | It is thin and built for small tables. Hard to scale. |  
| No transactions are there in HBase.  | 	RDBMS is transactional. |  
| It has de-normalized data.  | It will have normalized data. |  
| It is good for semi-structured as well as structured data.  | It is good for structured data. |  

##### Features of HBase

* HBase is linearly scalable.
* It has automatic failure support.
* It provides consistent read and writes.
* It integrates with Hadoop, both as a source and a destination.
* It has easy java API for client.
* It provides data replication across clusters.

##### Where to Use HBase

* Apache HBase is used to have random, real-time read/write access to Big Data.
* It hosts very large tables on top of clusters of commodity hardware.
* Apache HBase is a non-relational database modeled after Google's Bigtable. Bigtable acts up on Google File System, likewise Apache HBase works on top of Hadoop and HDFS.

##### Applications of HBase

* It is used whenever there is a need to write heavy applications.
* HBase is used whenever we need to provide fast random access to available data.
* Companies such as Facebook, Twitter, Yahoo, and Adobe use HBase internally.

# Architecture

![alt](https://www.tutorialspoint.com/hbase/images/architecture.jpg)

In HBase, tables are split into regions and are served by the region servers. Regions are vertically divided by column families into “Stores”. Stores are saved as files in HDFS. Shown below is the architecture of HBase.

HBase has three major components: the client library, a master server, and region servers. Region servers can be added or removed as per requirement.

##### MasterServer

The master server -

* Assigns regions to the region servers and takes the help of Apache ZooKeeper for this task.
* Handles load balancing of the regions across region servers. It unloads the busy servers and shifts the regions to less occupied servers.
* Maintains the state of the cluster by negotiating the load balancing.
* Is responsible for schema changes and other metadata operations such as creation of tables and column families.

##### Regions

Regions are nothing but tables that are split up and spread across the region servers.

The region servers have regions that -

* Communicate with the client and handle data-related operations.
* Handle read and write requests for all the regions under it.
* Decide the size of the region by following the region size thresholds.

When we take a deeper look into the region server, it contain regions and stores as shown below:

![alt](https://www.tutorialspoint.com/hbase/images/regional_server.jpg)

The store contains memory store and HFiles. Memstore is just like a cache memory. Anything that is entered into the HBase is stored here initially. Later, the data is transferred and saved in Hfiles as blocks and the memstore is flushed.

##### Zookeeper

* Zookeeper is an open-source project that provides services like maintaining configuration information, naming, providing distributed synchronization, etc.
* Zookeeper has ephemeral nodes representing different region servers. Master servers use these nodes to discover available servers.
* In addition to availability, the nodes are also used to track server failures or network partitions.
* Clients communicate with region servers via zookeeper.
* In pseudo and standalone modes, HBase itself will take care of zookeeper.

