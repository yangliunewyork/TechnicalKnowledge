In databases and transaction processing, __two-phase locking (2PL)__ is a concurrency control method that guarantees serializability. It is also the name of the resulting set of database transaction schedules (histories). The protocol utilizes locks, applied by a transaction to data, which may block (interpreted as signals to stop) other transactions from accessing the same data during the transaction's life.

By the 2PL protocol, locks are applied and removed in two phases:

1. Expanding phase: locks are acquired and no locks are released.  
2. Shrinking phase: locks are released and no locks are acquired.  

Two types of locks are utilized by the basic protocol: Shared and Exclusive locks. Refinements of the basic protocol may utilize more lock types. Using locks that block processes, 2PL may be subject to deadlocks that result from the mutual blocking of two or more transactions.

# Data-access locks

A lock is a system object associated with a shared resource such as a data item of an elementary type, a row in a database, or a page of memory. In a database, a lock on a database object (a data-access lock) may need to be acquired by a transaction before accessing the object. Correct use of locks prevents undesired, incorrect or inconsistent operations on shared resources by other concurrent transactions. When a database object with an existing lock acquired by one transaction needs to be accessed by another transaction, the existing lock for the object and the type of the intended access are checked by the system. If the existing lock type does not allow this specific attempted concurrent access type, the transaction attempting access is blocked (according to a predefined agreement/scheme). In practice, a lock on an object does not directly block a transaction's operation upon the object, but rather blocks that transaction from acquiring another lock on the same object, needed to be held/owned by the transaction before performing this operation. Thus, with a locking mechanism, needed operation blocking is controlled by a proper lock blocking scheme, which indicates which lock type blocks which lock type.

Two major types of locks are utilized:

* __Write-lock (exclusive lock)__ is associated with a database object by a transaction (Terminology: "the transaction locks the object," or "acquires lock for it") before writing (inserting/modifying/deleting) this object.  
* __Read-lock (shared lock)__ is associated with a database object by a transaction before reading (retrieving the state of) this object.  

The common interactions between these lock types are defined by blocking behavior as follows:

* An existing write-lock on a database object blocks an intended write upon the same object (already requested/issued) by another transaction by blocking a respective write-lock from being acquired by the other transaction. The second write-lock will be acquired and the requested write of the object will take place (materialize) after the existing write-lock is released.  
* A write-lock blocks an intended (already requested/issued) read by another transaction by blocking the respective read-lock .  
* A read-lock blocks an intended write by another transaction by blocking the respective write-lock.  
* A read-lock does not block an intended read by another transaction. The respective read-lock for the intended read is acquired (shared with the previous read) immediately after the intended read is requested, and then the intended read itself takes place.  

Several variations and refinements of these major lock types exist, with respective variations of blocking behavior. If a first lock blocks another lock, the two locks are called incompatible; otherwise the locks are compatible. Often, lock types blocking interactions are presented in the technical literature by a Lock compatibility table. The following is an example with the common, major lock types:

```
##### Lock compatibility table

Lock type	    read-lock	      write-lock
read-lock		                     X
write-lock	     X	             X
```

X indicates incompatibility, i.e, a case when a lock of the first type (in left column) on an object blocks a lock of the second type (in top row) from being acquired on the same object (by another transaction). An object typically has a queue of waiting requested (by transactions) operations with respective locks. The first blocked lock for operation in the queue is acquired as soon as the existing blocking lock is removed from the object, and then its respective operation is executed. If a lock for operation in the queue is not blocked by any existing lock (existence of multiple compatible locks on a same object is possible concurrently), it is acquired immediately.

# Two-phase locking and its special cases

According to the two-phase locking protocol, a transaction handles its locks in two distinct, consecutive phases during the transaction's execution:

* Expanding phase (aka Growing phase): locks are acquired and no locks are released (the number of locks can only increase).  
* Shrinking phase: locks are released and no locks are acquired.   

The two phase locking rule can be summarized as: never acquire a lock after a lock has been released. The serializability property is guaranteed for a schedule with transactions that obey this rule.
Typically, without explicit knowledge in a transaction on end of phase-1, it is safely determined only when a transaction has completed processing and requested commit. In this case, all the locks can be released at once (phase-2).






