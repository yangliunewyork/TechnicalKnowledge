## MySQL Architecture

![alt](http://books.gigatux.nl/mirror/highperfmysql/0596003064/images/0596003064/figs/hpsql_0201.gif)

The topmost layer is composed of the services that aren't unique to MySQL. They're services most network-based client/server tools or servers need: connection handling, authentication, security, etc.

The second layer is where things get interesting. Much of the brains inside MySQL live here, including query parsing, analysis, optimization, caching, and all the built-in functions (dates, times, math, encryption, etc.). Any functionality provided across storage engines lives at this level. Stored procedures, which will arrive in MySQL 5.0, also reside in this layer.

The third layer is made up of storage engines. They're responsible for the storage and retrieval of all data stored "in" MySQL. Like the various filesystems available for Linux, each storage engine has its own benefits and drawbacks. The good news is that many of the differences are transparent at the query layer.

The interface between the second and third layers is a single API not specific to any given storage engine. This API is made up of roughly 20 low-level functions that perform operations such as "begin a transaction" or "fetch the row that has this primary key" and so on. The storage engines don't deal with SQL or communicate with each other; they simply respond to requests from the higher levels within MySQL.

## Locking and Concurrency
The first of those problems is how to deal with concurrency and locking. In any data repository you have to be careful when more than one person, process, or client needs to change data at the same time. 

### Read/Write Locks
Systems that deal with concurrent read/write access typically implement a locking system that consists of two lock types. These locks are usually known as __shared locks__ and __exclusive locks__, or __read locks__ and __write locks__.

Without worrying about the actual locking technology, we can describe the concept as follows. Read locks on a resource are shared: many clients may read from the resource at the same time and not interfere with each other. Write locks, on the other hand, are exclusive, because it is safe to have only one client writing to the resource at given time and to prevent all reads when a client is writing. Why? Because the single writer is free to make any changes to the resource—even deleting it entirely.

In the database world, locking happens all the time. MySQL has to prevent one client from reading a piece of data while another is changing it. It performs this lock management internally in a way that is transparent much of the time.

### Lock Granularity
One way to improve the concurrency of a shared resource is to be more selective about what is locked. Rather than locking the entire resource, lock only the part that contains the data you need to change. Better yet, lock only the exact piece of data you plan to change. By decreasing the amount of data that is locked at any one time, more changes can occur simultaneously—as long as they don't conflict with each other.

The downside of this is that locks aren't free. There is overhead involved in obtaining a lock, checking to see whether a lock is free, releasing a lock, and so on. All this business of lock management can really start to eat away at performance because the system is spending its time performing lock management instead of actually storing and retrieving data. 

To achieve the best performance overall, some sort of balance is needed. Most commercial database servers don't give you much choice: you get what is known as row-level locking in your tables. MySQL, on the other hand, offers a choice in the matter. Among the storage engines you can choose from in MySQL, you'll find three different granularities of locking. Let's have a look at them.

#### Table locks
The most basic and low-overhead locking strategy available is a table lock, which is analogous to the mailbox locks described earlier. The table as a whole is locked on an all-or-nothing basis. When a client wishes to write to a table (insert, delete, or update, etc.), it obtains a write lock that keeps all other read or write operations at bay for the duration of the operation. Once the write has completed, the table is unlocked to allow those waiting operations to continue. When nobody is writing, readers obtain read locks that allow other readers to do the same.

#### Page locks
A slightly more expensive form of locking that offers greater concurrency than table locking, a page lock is a lock applied to a portion of a table known as a page. All the records that reside on the same page in the table are affected by the lock. Using this scheme, the main factor influencing concurrency is the page size; if the pages in the table are large, concurrency will be worse than with smaller pages. MySQL's BDB (Berkeley DB) tables use page-level locking on 8-KB pages.

The only hot spot in page locking is the last page in the table. If records are inserted there at regular intervals, the last page will be locked frequently.

#### Row locks
The locking style that offers the greatest concurrency (and carries the greatest overhead) is the row lock. In most applications, it's relatively rare for several clients to need to update the exact same row at the same time. Row-level locking, as it's commonly known, is available in MySQL's InnoDB tables. InnoDB doesn't use a simple row locking mechanism, however. Instead it uses row-level locking in conjunction with a multiversioning scheme.

### Multi-Version Concurrency Control

There is a final technique for increasing concurrency: Multi-Version Concurrency Control (MVCC). Often referred to simply as versioning, __MVCC is used by Oracle, by PostgreSQL, and by MySQL's InnoDB storage engine__. MVCC can be thought of as a new twist on row-level locking. It has the added benefit of allowing nonlocking reads while still locking the necessary records only during write operations. Some of MVCC's other properties will be of particular interest when we look at transactions in the next section.

So how does this scheme work? Conceptually, any query against a table will actually see a snapshot of the data as it existed at the time the query began—no matter how long it takes to execute. 

__In a versioning system, each row has two additional, hidden values associated with it. These values represent when the row was created and when it was expired (or deleted). Rather than storing the actual time at which these events occur, the database stores the version number at the time each event occurred. The database version (or system version) is a number that increments each time a query begins. We'll call these two values the creation id and the deletion id.__

> That's not quite true. As you'll see when we start talking about transactions later, the version number is incremented for each transaction rather than each query.

Under MVCC, a final duty of the database server is to keep track of all the running queries (with their associated version numbers). Let's see how this applies to particular operations:


* SELECT
 When records are selected from a table, the server must examine each row to ensure that it meets several criteria:

  * Its creation id must be less than or equal to the system version number. This ensures that the row was created before the current query began.
  * Its deletion id, if not null, must be greater than the current system version. This ensures that the row wasn't deleted before the current query began.
  * Its creation id can't be in the list of running queries. This ensures that the row wasn't added or changed by a query that is still running.
  * Rows that pass all of these tests may be returned as the result of the query.


* INSERT
  * When a row is added to a table, the database server records the current version number along with the new row, using it as the row's creation id.


* DELETE
  * To delete a row, the database server records the current version number as the row's deletion id.


* UPDATE
  * When a row is modified, the database server writes a new copy of the row, using the version number as the new row's creation id. It also writes the version number as the old row's deletion id.

The result of all this extra record keeping is that read queries never lock tables, pages, or rows. They simply read data as fast as they can, making sure to select only rows that meet the criteria laid out earlier. The drawbacks are that the server has to store a bit more data with each row and do a bit more work when examining rows.

| Locking strategy        | Concurrency           | Overhead  | Engines  |
| ------------- |:-------------:| -----:| -----:|
| Table socks      | Lowest | Lowest | MyISAM, Heap, Merge |
| Page locks      | Modest      |   Modest | BDB |
| Multiversioning | Highest      |    High | InnoDB |


## Transactions
Simply having transactions isn't sufficient unless the database server passes what is known as the ACID test. ACID is an acronym for Atomicity, Consistency, Isolation, and Durability—four tightly related criteria that are required in a well-behaved transaction processing system. Transactions that meet those four criteria are often referred to as ACID transactions.

* __Atomicity__ : Transactions must function as a single indivisible unit of work. The entire transaction is either applied or rolled back. When transactions are atomic, there is no such thing as a partially completed transaction: it's all or nothing.
* __Consistency__ : The database should always move from one consistent state to the next.
* __Isolation__ : The results of a transaction are usually invisible to other transactions until the transaction is complete. 
* __Durability__ : Once committed, the results of a transaction are permanent. This means that the changes must be recorded in such a way that system crashes won't lose the data. Of course, if the database server's disks fail, all bets are off. That's a hardware problem. 

### Benefits and Drawbacks
ACID transactions ensure that banks don't lose your money. By wrapping arbitrarily complex logic into single units of work, the database server takes some of the burden off application developers. The database server's ACID properties offer guarantees that reduce the need for code guarding against race conditions and handling crash recovery.

The downside of this extra security is that the database server has to do more work. It also means that a database server with ACID transactions will generally require more CPU power, memory, and disk space than one without them. As mentioned earlier, this is where MySQL's modularity comes into play. Because you can decide on a per-table basis if you need ACID transactions or not, you don't need to pay the performance penalty on a table that really won't benefit from transactions.

#### Isolation Levels

The previous description of isolation was a bit simplistic. Isolation is more complex than it might first appear because of some peculiar cases that can occur. The SQL standard defines four isolation levels with specific rules for which changes are and aren't visible inside and outside a transaction. 

#####  Read uncommitted

In the read uncommitted isolation level, transactions can view the results of uncommitted transactions. At this level, many problems can occur unless you really, really know what you are doing and have a good reason for doing it. Read uncommitted is rarely used in practice. Reading uncommitted data is also known as a dirty read.

##### Read committed

The default isolation level for most database systems is read committed. It satisfies the simple definition of isolation used earlier. A transaction will see the results only of transactions that were already committed when it began, and its changes won't be visible to others until it's committed.

##### Repeatable read
At the repeatable read isolation level, any rows that are read during a transaction are locked so that they can't be changed until the transaction finishes. This provides the perfect solution to the problem mentioned in the previous section, in which Amazon's id can change or vanish entirely. However, this isolation level still leaves the door open to another tricky problem: __phantom reads__.

Phantom rows are such a common problem that InnoDB's locking (known as next-key locking) prevents this from happening. Rather than locking only the rows you've touched in a query, InnoDB actually locks the slot following them in the index structure as well.

##### Serializable
The highest level of isolation, serializable, solves the phantom read problem by ordering transactions so that they can't conflict. At this level, a lot of timeouts and lock contention may occur, but the needs of your application may bring you to accept the decreased performance in favor of the data stability that results.

![alt](https://juliandontcheff.files.wordpress.com/2011/02/isolation_levels_types.png)

## Deadlocks
Whenever multiple transactions obtain locks, there is the danger of encountering a deadlock condition. Deadlocks occur when two transactions attempt to obtain conflicting locks in a different order.

To combat this problem, database systems implement various forms of deadlock detection and timeouts. The more sophisticated systems, such as InnoDB, will notice circular dependencies like the previous example and return an error. Others will give up after the query exceeds a timeout while waiting for a lock. InnoDB's default timeout is 50 seconds. In either case, applications that use transactions need to be able to handle deadlocks and possibly retry transactions.

### Transaction Logging
Some of the overhead involved with transactions can be mitigated through the use of a transaction log. Rather than directly updating the tables on disk each time a change occurs, the system can update the in-memory copy of the data (which is very fast) and write a record of the change to a transaction log on disk. Then, at some later time, a process (or thread) can actually apply the changes that the transaction log recorded. The serial disk I/O required to append events to the log is much faster than the random seeks required to update data in various places on disk.

As long as events are written to the transaction log before a transaction is considered committed, having the changes in a log will not affect the durability of the system. If the database server crashes before all changes have been applied from the transaction log, the database will continue applying changes from the transaction log when it is restarted and before it accepts new connections.

#### Transactions in MySQL
MySQL provides two transaction-safe storage engines: Berkeley DB (BDB) and InnoDB. Their specific properties are discussed in next section. Each one offers the basic BEGIN/COMMIT/ROLLBACK functionality. They differ in their supported isolation levels, locking characteristics, deadlock detection, and other features.

##### Implicit commits

Certain commands, when issued during an open transaction, cause MySQL to commit the transaction before they execute. Typically these are commands that make significant changes, such as removing or renaming a table.

Here is the list of commands for which MySQL implicitly commits a transaction:

* ALTER TABLE
* BEGIN
* CREATE INDEX
* DROP DATABASE
* DROP TABLE
* RENAME TABLE
* TRUNCATE
* LOCK TABLES
* UNLOCK TABLES

##### Isolation levels
MySQL allows you to set the isolation level using the SET TRANSACTION ISOLATION LEVEL command. Unless otherwise specified, the isolation level is changed beginning with the next transaction.

To set the level for the whole session (connection), use:
```
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED
```
Here's how to set the global level:
```
SET GLOBAL TRANSACTION ISOLATION LEVEL SERIALIZABLE
```
MySQL recognizes all four ANSI standard isolation levels, and as of Version 4.0.5 of MySQL, InnoDB supports all of them:


* READ UNCOMMITTED
* READ COMMITTED
* REPEATABLE READ
* SERIALIZABLE

#### Mixing storage engines in transactions

Transaction management in MySQL is currently handled by the underlying storage engines, not at a higher level. Thus, you can't reliably mix tables stored in transactional engines (such as InnoDB and BDB) in a single transaction. A higher-level transaction management service may someday be added to MySQL, making it safe to mix and match transaction-safe tables in a transaction. Until then, don't expect it to work.

If you mix transaction-safe and non-transaction-safe tables (such as InnoDB and MyISAM) in a transaction, the transaction will work properly if all goes well. However, if a rollback is required, the changes to the non-transaction-safe table won't be undone. This leaves the database in an inconsistent state that may be difficult to recover from (and renders the entire point of transactions moot).

#### Simulating transactions

At times you may need the behavior of transactions when you aren't using a transaction-safe table. You can achieve something like transactions using MySQL's LOCK TABLES and UNLOCK TABLES commands. If you lock the tables that will be involved in the transaction and keep track of any changes that you make (in case you need to simulate a rollback), you'll have something equivalent to running at the serializable isolation level. But the process is kludgy and error prone, so if you really need transactions, we recommend using a transactional storage engine.

## Selecting the Right Engine
When designing MySQL-based applications, you should decide which engine to use for storing your data. If you don't think about it during the design phase, you will likely face complications later in the process. You might find that the default engine doesn't provide a feature you need, such as transactions. Or maybe the mix of read and write queries your application generates will require more granular locking than MyISAM's table locks.

Because you can make the choice on a table-by-table basis, you'll need a clear idea of how each table is used and the data it stores. Of course, it also helps to have a good understanding of the application as a whole and its potential for growth. Armed with this information, you can begin to make good choices about which table engines can do the job.

### Considerations
While there are many factors that can affect your decision, it usually boils down to just a few considerations: transactions and concurrency, backups, and special features.

#### Transactions and concurrency
When it comes to transactions and concurrency, consider the following guidelines:
* If your application requires transactions and high read/write concurrency, InnoDB is probably your best bet.
* If your application requires transactions but only moderate read/write concurrency, either BDB or InnoDB tables should work fine.
* If your application doesn't require transactions and issues primarily SELECT or primarily INSERT/UPDATE queries, MyISAM is a good choice. Many web applications fall into this category.

#### Backups

The need to perform regular backups may also influence your table choices. If your server can be shut down at regular intervals for backups, the storage engines are equally easy to deal with. However, if you need to perform online backups in one form or another, the choices become less clear. Chapter 9 deals with this topic in more detail.

Another way of looking at this is simplicity. Using multiple storage engines increases the complexity of backups and server tuning. You may decide that it's just easier to use a single storage engine rather than those that are theoretically best.

Finally, you sometimes find that an application relies on particular features or optimizations that are provided by only some of MySQL's storage engines. For example, not all tables provide a quick answer to queries like the following:
```
SELECT COUNT(*) FROM mytable
```
If your application depends on accurate and fast row counts, MyISAM is the answer. InnoDB must actually count up all the rows, but the MyISAM storage engine always knows the exact row count of a table without the need to do any work.

If your application requires referential integrity with foreign keys, you're limited to just InnoDB tables. Do you need full-text search capabilities? Only MyISAM tables provide it.

Keep this in mind as you read the more detailed information about each table's features. There will come a time when you find that the feature you really, really need is available only in one table engine. When that happens, you need to either compromise or break a table into multiple tables of different types.

## Storage Engines
* InnoDB: The default storage engine in MySQL 5.7. InnoDB is a transaction-safe (ACID compliant) storage engine for MySQL that has commit, rollback, and crash-recovery capabilities to protect user data. InnoDB row-level locking (without escalation to coarser granularity locks) and Oracle-style consistent nonlocking reads increase multi-user concurrency and performance. InnoDB stores user data in clustered indexes to reduce I/O for common queries based on primary keys. To maintain data integrity, InnoDB also supports FOREIGN KEY referential-integrity constraints. For more information about InnoDB, see Chapter 15, The InnoDB Storage Engine.

* MyISAM: These tables have a small footprint. Table-level locking limits the performance in read/write workloads, so it is often used in read-only or read-mostly workloads in Web and data warehousing configurations.

* Memory: Stores all data in RAM, for fast access in environments that require quick lookups of non-critical data. This engine was formerly known as the HEAP engine. Its use cases are decreasing; InnoDB with its buffer pool memory area provides a general-purpose and durable way to keep most or all data in memory, and NDBCLUSTER provides fast key-value lookups for huge distributed data sets.



And many others......










