A transaction is a unit of work that is performed against a database. Transactions are units or sequences of work accomplished in a logical order, whether in a manual fashion by a user or automatically by some sort of a database program.

A transaction is the propagation of one or more changes to the database. For example, if you are creating a record or updating a record or deleting a record from the table, then you are performing a transaction on that table. It is important to control these transactions to ensure the data integrity and to handle database errors.

Practically, you will club many SQL queries into a group and you will execute all of them together as a part of a transaction.

### Properties of Transactions

Transactions have the following four standard properties, usually referred to by the acronym ACID.

* Atomicity : A transaction must be an atomic unit of work; either all of its data modifications are performed, or none of them are performed.
* Consistency : When completed, a transaction must leave all data in a consistent state. In a relational database, all rules must be applied to the transaction's modifications to maintain all data integrity. All internal data structures, such as B-tree indexes or doubly-linked lists, must be correct at the end of the transaction.
* Isolation : Modifications made by concurrent transactions must be isolated from the modifications made by any other concurrent transactions. A transaction either recognizes data in the state it was in before another concurrent transaction modified it, or it recognizes the data after the second transaction has completed, but it does not recognize an intermediate state. This is referred to as serializability because it results in the ability to reload the starting data and replay a series of transactions to end up with the data in the same state it was in after the original transactions were performed.
* Durability : After a transaction has completed, its effects are permanently in place in the system. The modifications persist even in the event of a system failure.

SQL programmers are responsible for starting and ending transactions at points that enforce the logical consistency of the data. The programmer must define the sequence of data modifications that leave the data in a consistent state relative to the organization's business rules. The programmer includes these modification statements in a single transaction so that the SQL Server Database Engine can enforce the physical integrity of the transaction.

It is the responsibility of an enterprise database system, such as an instance of the Database Engine, to provide mechanisms ensuring the physical integrity of each transaction. The Database Engine provides:
* Locking facilities that preserve transaction isolation.  
* Logging facilities that ensure transaction durability. Even if the server hardware, operating system, or the instance of the Database Engine itself fails, the instance uses the transaction logs upon restart to automatically roll back any uncompleted transactions to the point of the system failure.  
* Transaction management features that enforce transaction atomicity and consistency. After a transaction has started, it must be successfully completed (committed), or the Database Engine undoes all of the data modifications made since the transaction started. This operation is referred to as rolling back a transaction because it returns the data to the state it was prior to those changes.  

##### Transaction Control

The following commands are used to control transactions.

* COMMIT − to save the changes.

* ROLLBACK − to roll back the changes.

* SAVEPOINT − creates points within the groups of transactions in which to ROLLBACK.

* SET TRANSACTION − Places a name on a transaction.

