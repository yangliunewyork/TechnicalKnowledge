A column-oriented DBMS (or columnar database management system) is a database management system (DBMS) that stores data tables by column rather than by row. Practical use of a column store versus a row store differs little in the relational DBMS world. Both columnar and row databases can use traditional database query languages like SQL to load data and perform queries. Both row and columnar databases can become the backbone in a system to serve data for common extract, transform, load (ETL) and data visualization tools. However, by storing data in columns rather than rows, the database can more precisely access the data it needs to answer a query rather than scanning and discarding unwanted data in rows. Query performance is often increased as a result, particularly in very large data sets.

# Description

A relational database management system provides data that represents a two-dimensional table, of columns and rows. For example, a database might have this table:

```
RowId	EmpId	Lastname	Firstname	Salary
001	10	Smith	Joe	40000
002	12	Jones	Mary	50000
003	11	Johnson	Cathy	44000
004	22	Jones	Bob	55000
```

dimensional format is an abstraction. In an actual implementation, storage hardware requires the data to be serialized into one form or another.

__The most expensive operations involving hard disks are seeks.__ In order to improve overall performance, related data should be stored in a fashion to minimize the number of seeks. This is known as __locality of reference__, and the basic concept appears in a number of different contexts. __Hard disks are organized into a series of blocks of a fixed size,__ typically enough to store several rows of the table. __By organizing the table's data so rows fit within these blocks, and grouping related rows onto sequential blocks, the number of blocks that need to be read or sought is minimized in many cases, along with the number of seeks.__

### Row-oriented systems

A common method of storing a table is to serialize each row of data, like this;

```
001:10,Smith,Joe,40000;
002:12,Jones,Mary,50000;
003:11,Johnson,Cathy,44000;
004:22,Jones,Bob,55000;
```

Row-based systems are designed to efficiently return data for an entire row, or record, in as few operations as possible. This matches the common use-case where the system is attempting to retrieve information about a particular object, say the contact information for a user in a rolodex system, or product information for an online shopping system. By storing the record's data in a single block on the disk, along with related records, the system can quickly retrieve records with a minimum of disk operations.

__Row-based systems are not efficient at performing set-wide operations on the whole table__, as opposed to a small number of specific records. For instance, in order to find all records in the example table with salaries between 40,000 and 50,000, the DBMS would have to fully scan through the entire table looking for matching records. While the example table shown above will likely fit in a single disk block, a table with even a few hundred rows would not, and multiple disk operations would be needed to retrieve the data and examine it.

To improve the performance of these sorts of operations (which are very common, and generally the point of using a DBMS), most DBMSs support the use of database indexes, which store all the values from a set of columns along with rowid pointers back into the original table. An index on the salary column would look something like this:
```
001:40000;
003:44000;
002:50000;
004:55000;
```

As they store only single pieces of data, rather than entire rows, indexes are generally much smaller than the main table stores. Scanning this smaller set of data reduces the number of disk operations. If the index is heavily used, it can dramatically reduce the time for common operations. However, maintaining indexes adds overhead to the system, especially when new data is written to the database. Records not only need to be stored in the main table, but any attached indexes have to be updated as well.

Database indexes on one or more columns are typically sorted by value, which makes range queries operations (like the above "find all records with salaries between 40,000 and 50,000 example) very fast.

A number of row-oriented databases are designed to fit entirely in RAM, an in-memory database. These systems do not depend on disk operations, and have equal-time access to the entire dataset. This reduces the need for indexes, as it requires the same amount of operations to full scan the original data as a complete index for typical aggregation purposes. Such systems may be therefore simpler and smaller, but can only manage databases that will fit in memory.

### Column-oriented systems
A column-oriented database serializes all of the values of a column together, then the values of the next column, and so on. For our example table, the data would be stored in this fashion:

```
10:001,12:002,11:003,22:004;
Smith:001,Jones:002,Johnson:003,Jones:004;
Joe:001,Mary:002,Cathy:003,Bob:004;
40000:001,50000:002,44000:003,55000:004;
```

In this layout, any one of the columns more closely matches the structure of an index in a row-based system. This may cause confusion that can lead to the mistaken belief a column-oriented store "is really just" a row-store with an index on every column. However, it is the mapping of the data that differs dramatically. In a row-oriented indexed system, the primary key is the rowid that is mapped from indexed data. In the column-oriented system, the primary key is the data, which is mapped from rowids. This may seem subtle, but the difference can be seen in this common modification to the same store:

```
…;Smith:001;Jones:002,004;Johnson:003;…
```

As two of the records store the same value, "Jones", it is possible to store this only once in the column store, along with pointers to all of the rows that match it. For many common searches, like "find all the people with the last name Jones", the answer is retrieved in a single operation. Other operations, like counting the number of matching records or performing math over a set of data, can be greatly improved through this organization.

![alt](http://www.timestored.com/time-series-data/images/column-vs-row-oriented-database.png)

Look at the above image, now imagine which areas need read when you perform a query like "average price" for all dates. In row-oriented databases we have to read over large areas, in column-oriented databases the prices are stored as one sequential region and we can read just that region. Column-oriented databases are therefore extremely quick at aggregate queries (sum, average, min, max, etc.).


Whether or not a column-oriented system will be more efficient in operation depends heavily on the workload being automated. Operations that retrieve all the data for a given object (the entire row) are slower. A row-based system can retrieve the row in a single disk read, whereas numerous disk operations to collect data from multiple columns are required from a columnar database. However, these whole-row operations are generally rare. In the majority of cases, only a limited subset of data is retrieved. In a rolodex application, for instance, collecting the first and last names from many rows to build a list of contacts is far more common than reading all data for any single address. This is even more true for writing data into the database, especially if the data tends to be "sparse" with many optional columns. For this reason, column stores have demonstrated excellent real-world performance in spite of many theoretical disadvantages.

Partitioning, indexing, caching, views, OLAP cubes, and transactional systems such as write-ahead logging or multiversion concurrency control all dramatically affect the physical organization of either system. That said, online transaction processing (OLTP)-focused RDBMS systems are more row-oriented, while online analytical processing (OLAP)-focused systems are a balance of row-oriented and column-oriented.

# Benefits
__Comparisons between row-oriented and column-oriented databases are typically concerned with the efficiency of hard-disk access for a given workload, as seek time is incredibly long compared to the other bottlenecks in computers.__ For example, a Serial ATA (SATA) hard drive has a maximum transfer rate of 600 MB/second (Megabytes per second)  while DDR3 SDRAM Memory can reach transfer rates of 17 GB/s (Gigabytes per second), nearly 30 times as fast. Clearly, a major bottleneck in handling big data is disk access. Columnar databases boost performance by reducing the amount of data that needs to be read from disk, both by efficiently compressing the similar columnar data and by reading only the data necessary to answer the query.

__In practice, columnar databases are well-suited for OLAP-like workloads (e.g., data warehouses) which typically involve highly complex queries over all data (possibly petabytes).__ However, some work must be done to write data into a columnar database. Transactions (INSERTs) must be separated into columns and compressed as they are stored, making it less suited for OLTP workloads. Row-oriented databases are well-suited for OLTP-like workloads which are more heavily loaded with interactive transactions. For example, retrieving all data from a single row is more efficient when that data is located in a single location (minimising disk seeks), as in row-oriented architectures. However, column-oriented systems have been developed as hybrids capable of both OLTP and OLAP operations, with some of the OLTP constraints column-oriented systems face mediated using (amongst other qualities) in-memory data storage. Column-oriented systems suitable for both OLAP and OLTP roles effectively reduce the total data footprint by removing the need for separate systems.

# Compression

Column data is of uniform type; therefore, there are some opportunities for storage size optimizations available in column-oriented data that are not available in row-oriented data. For example, many popular modern compression schemes, such as LZW or run-length encoding, make use of the similarity of adjacent data to compress. Missing values and repeated values, common in clinical data, can be represented by a two-bit marker. While the same techniques may be used on row-oriented data, a typical implementation will achieve less effective results.

To improve compression, sorting rows can also help. For example, using bitmap indexes, sorting can improve compression by an order of magnitude. To maximize the compression benefits of the lexicographical order with respect to run-length encoding, it is best to use low-cardinality columns as the first sort keys.[13] For example, given a table with columns sex, age, name, it would be best to sort first on the value sex (cardinality of two), then age (cardinality of <150), then name.

Columnar compression achieves a reduction in disk space at the expense of efficiency of retrieval. The greater adjacent compression achieved, the more difficult random-access may become, as data might need to be uncompressed to be read. Therefore, column-oriented architectures are sometimes enriched by additional mechanisms aimed at minimizing the need for access to compressed data.


