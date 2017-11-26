In computer science, an algorithm is called non-blocking if failure or suspension of any thread cannot cause failure or suspension of another thread; for some operations, these algorithms provide a useful alternative to traditional blocking implementations. A non-blocking algorithm is lock-free if there is guaranteed system-wide progress, and wait-free if there is also guaranteed per-thread progress.

### Motivation

The traditional approach to multi-threaded programming is to use locks to synchronize access to shared resources. Synchronization primitives such as mutexes, semaphores, and critical sections are all mechanisms by which a programmer can ensure that certain sections of code do not execute concurrently, if doing so would corrupt shared memory structures. If one thread attempts to acquire a lock that is already held by another thread, the thread will block until the lock is free.

Blocking a thread can be undesirable for many reasons. An obvious reason is that while the thread is blocked, it cannot accomplish anything: if the blocked thread had been performing a high-priority or real-time task, it would be highly undesirable to halt its progress.
Other problems are less obvious. For example, certain interactions between locks can lead to error conditions such as deadlock, livelock, and priority inversion. Using locks also involves a trade-off between coarse-grained locking, which can significantly reduce opportunities for parallelism, and fine-grained locking, which requires more careful design, increases locking overhead and is more prone to bugs.

Unlike blocking algorithms, non-blocking algorithms do not suffer from these downsides, and in addition are safe for use in interrupt handlers: even though the preempted thread cannot be resumed, progress is still possible without it. In contrast, global data structures protected by mutual exclusion cannot safely be accessed in an interrupt handler, as the preempted thread may be the one holding the lock.

A lock-free data structure can be used to improve performance. A lock-free data structure increases the amount of time spent in parallel execution rather than serial execution, improving performance on a multi-core processor, because access to the shared data structure does not need to be serialized to stay coherent.

# Implementation

With few exceptions, non-blocking algorithms use __atomic__ __read-modify-write__ primitives that the hardware must provide, the most notable of which is __compare and swap (CAS)__. Critical sections are almost always implemented using standard interfaces over these primitives (in the general case, critical sections will be blocking, even when implemented with these primitives). Until recently, all non-blocking algorithms had to be written "natively" with the underlying primitives to achieve acceptable performance. However, the emerging field of software transactional memory promises standard abstractions for writing efficient non-blocking code.

In computer science, non-blocking synchronization ensures that threads competing for a shared resource do not have their execution indefinitely postponed by mutual exclusion. A non-blocking algorithm is lock-free if there is guaranteed system-wide progress; wait-free if there is also guaranteed per-thread progress. 

Much research has also been done in providing basic data structures such as stacks, queues, sets, and hash tables. These allow programs to easily exchange data between threads asynchronously.

Additionally, some non-blocking data structures are weak enough to be implemented without special atomic primitives. These exceptions include:

* A single-reader single-writer ring buffer FIFO, with a size which evenly divides the overflow of one of the available unsigned integer types, can unconditionally be implemented safely using only a memory barrier.  
* Read-copy-update with a single writer and any number of readers. (The readers are wait-free; the writer is usually lock-free, until it needs to reclaim memory).  
* Read-copy-update with multiple writers and any number of readers. (The readers are wait-free; multiple writers generally serialize with a lock and are not obstruction-free).  

Several libraries internally use lock-free techniques, but it is difficult to write lock-free code that is correct.
