The choice of data structure to use for a programming problem can be a key part of the overall solution, and parallel programming problems are no exception. If a data structure is to be accessed from multiple threads then either it must be completely immutable so the data never changes and no synchronization is necessary, or the program must be designed to ensure that changes are correctly synchronized between threads. One option is to use a separate mutex and external locking to protect the data, and another is to design the data structure itself for concurrent access.

## What does it mean for a Data Structure to be designed for concurrency?
At the basic level, designing a data structure for concurrency means that multiple threads can access the data structure concurrently, either performing the same or distinct operations, and each thread will see a consistent view of the data structure. No data will be lost or corrupted, all invariants will be upheld and there will be no problematic race conditions. Such a data structure is said to be thread-safe.

Truly designing for concurrency means more than that though: it means providing the opportunity for concurrency to threads accessing the data structure. By it's very nature, a mutex provides mutual exclusion: only one thread can acquire a lock on the mutex at a time. The use of a mutex to protect a data structure does so by explicitly preventing true concurrent access to the data it protects.

This is called __serialization__: threads take turns to access the data protected by the mutex; they must access it serially rather than concurrently. Consequently, careful thought must go into the design of the data structure to enable true concurrent access. Some data structures have more scope for true concurrency than others, but in all cases the idea is the same: the smaller the protected region, the fewer operations are serialized, the greater the potential for concurrency.

### Guidelines for Designing Data Structures for Concurrency
As I just mentioned, there are two aspects to consider when designing data structures for concurrent access: ensuring that the accesses are safe and enabling genuine concurrent access. The basics of how to make the data structure thread-safe are: 
* Ensure that no thread can see a state where the invariants of the data structure have been broken by the actions of another thread.
* Take care to avoid race conditions inherent in the interface to the data structure by providing functions for complete operations rather than for operation steps. 
* Pay attention to how the data structure behaves in the presence of exceptions to ensure that the invariants are not broken. 
* Minimize the opportunities for deadlock when using the data structure by restricting the scope of locks and avoiding nested locks where possible.

However, before you think about that, it's also important to think about what constraints you wish to put on the users of the data structure:
* If one thread is accessing the data structure through a particular function, which functions are safe to call from other threads? 

This is actually quite a crucial question to think about. Generally constructors and destructors require exclusive access to the data structure, but it is up to the user to ensure that they are not accessed before construction is complete or after destruction has started. If the data structure supports assignment, swap() or copy-construction then as the designer of the data structure you need to decide whether these operations are safe to call concurrently with other operations, or whether they require the user to ensure exclusive access even though the majority of functions for manipulating the data structure may be called from multiple threads concurrently without problem. 

The second aspect to consider is that of enabling genuine concurrent access. I can't offer much in the way of guidelines here; instead here's a list of questions to ask yourself as the data structure designer: 

* Can the scope of locks be restricted to allow some parts of an operation to be performed outside the lock? 
* Can different parts of the data structure be protected with different mutexes? 
* Do all operations require the same level of protection? 
* Can a simple change to the data structure improve the opportunities for concurrency without affecting the operational semantics?

__All these questions are guided by a single idea: how can we minimize the amount of serialization that must occur and enable the greatest amount of true concurrency?__ It is not uncommon for data structures to allow concurrent access from multiple threads that merely read the data structure, whilst a thread that can modify the data structure must have exclusive access. This is supported by using constructs like boost::shared_mutex. Likewise, as we shall see shortly, it is quite common for a data structure to support concurrent access from threads performing different operations, whilst serializing threads that try to perform the same operation.

The simplest thread-safe data structures typically use mutexes and locks to protect the data — though there are issues with this, it is relatively easy to ensure that only one thread is accessing the data structure at a time.

## Lock-based Concurrent Data Structures
__The design of lock-based concurrent data structures is all about ensuring that the right mutex is locked when accessing the data, and ensuring that the lock is held for the minimum amount of time.__ This is hard enough when there is just one mutex protecting a data structure — we need to ensure that data cannot be accessed outside the protection of the mutex lock, and that there are no race conditions inherent in the interface.If we use separate mutexes to protect separate parts of the data structure then these issues are compounded, and there is now also the possibility of deadlock if the operations on the data structure require more than one mutex to be locked. We therefore need to consider the design of a data structure with multiple mutexes even more carefully than the design of a data structure with a single mutex.

