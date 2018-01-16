Concurrency is the ability of multiple users to access data at the same time. When the number of simultaneous operations that the database engine can support is large, the database concurrency is increased. In Microsoft SQL Server, concurrency control is achieved by using locks to help protect data. The locks control how multiple users can access and change shared data at the same time without conflicting with each other.

### Concurrency Problems

If you do not manage the modification and reading of data by multiple users, concurrency problems can occur. For example, if several users access a database at the same time, their transactions could try to perform operations on the same data at the same time. Some of the concurrency problems :

* __Lost updates__ : Lost updates occur when two or more transactions select the same row, and then update the row based on the value originally selected. The last update overwrites updates made by the other transactions, resulting in lost data.

* __Inconsistent analysis (nonrepeatable reads)__ : Nonrepeatable reads occur when a second transaction accesses the same row several times and reads different data every time. This involves multiple reads of the same row. Every time, the information is changed by another transaction.

* __Phantom reads__ : Phantom reads occur when an insert or a delete action is performed against a row that belongs to a range of rows being read by a transaction. The transaction's first read of the range of rows shows a row that no longer exists in the subsequent read, because of a deletion by a different transaction. Similarly, as the result of an insert by a different transaction, the subsequent read of the transaction shows a row that did not exist in the original read.

### Concurrency control

In a database scenario, there are two types of concurrency control mechanisms:

* Optimistic concurrency control : Optimistic concurrency control works on the assumption that resource conflicts between multiple users are unlikely, and it permits transactions to execute without locking any resources. The resources are checked only when transactions are trying to change data. This determines whether any conflict has occurred (for example, by checking a version number). If a conflict occurs, the application must read the data and try the change again. Optimistic concurrency control is not provided with the product, but you can build it into your application manually by tracking database access.

* Pessimistic concurrency control : Pessimistic concurrency control locks resources as needed, for the duration of a transaction
