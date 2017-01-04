### Locks
A lock is an abstract concept. The basic premise is that a lock protects access to some kind of shared resource. If you own a lock then you can access the protected shared resource. If you do not own the lock then you cannot access the shared resource.To own a lock, you first need some kind of lockable object. You then acquire the lock from that object. </br>
The concept of a lock also implies some kind of exclusion: sometimes you might be unable to take ownership of a lock, and the operation to do so will either fail, or block. In the former case, the operation will return some error code or exception to indicate that the attempt to take ownership failed. In the latter case, the operation will not return until it has taken ownership, which typically requires that another thread in the system does something to permit that to happen.</br>
### Ownership
What it means to "own" a lock depends on the precise type of the lockable object. For some lockable objects there is a very tight definition of ownership: this specific thread owns the lock, through the use of that specific object, within this particular scope.</br>
In other cases, the definition is more fluid, and the ownership of the lock is more conceptual. In these cases, ownership can be relinquished by a different thread or object than the thread or object that acquired the lock.
### Mutexes
Mutex is short for MUTual EXclusion. Unless the word is qualified with additional terms such as shared mutex, recursive mutex or read/write mutex then it refers to a type of lockable object that can be owned by exactly one thread at a time. Only the thread that acquired the lock can release the lock on a mutex. When the mutex is locked, any attempt to acquire the lock will fail or block, even if that attempt is done by the same thread.
##### Recursive Mutexes
A recursive mutex is similar to a plain mutex, but one thread may own multiple locks on it at the same time. If a lock on a recursive mutex has been acquired by thread A, then thread A can acquire further locks on the recursive mutex without releasing the locks already held. However, thread B cannot acquire any locks on the recursive mutex until all the locks held by thread A have been released.</br>
In most cases, a recursive mutex is undesirable, since the it makes it harder to reason correctly about the code. With a plain mutex, if you ensure that the invariants on the protected resource are valid before you release ownership then you know that when you acquire ownership those invariants will be valid.</br>
With a recursive mutex this is not the case, since being able to acquire the lock does not mean that the lock was not already held, by the current thread, and therefore does not imply that the invariants are valid.
#### Reader/Writer Mutexes
Sometimes called shared mutexes, multiple-reader/single-writer mutexes or just read/write mutexes, these offer two distinct types of ownership:
* shared ownership, also called read ownership, or a read lock, and
* exclusive ownership, also called write ownership, or a write lock.

Exclusive ownership works just like ownership of a plain mutex: only one thread may hold an exclusive lock on the mutex, only that thread can release the lock. No other thread may hold any type of lock on the mutex whilst that thread holds its lock.

Shared ownership is more lax. Any number of threads may take shared ownership of a mutex at the same time. No thread may take an exclusive lock on the mutex while any thread holds a shared lock.

These mutexes are typically used for protecting shared data that is seldom updated, but cannot be safely updated if any thread is reading it. The reading threads thus take shared ownership while they are reading the data. When the data needs to be modified, the modifying thread first takes exclusive ownership of the mutex, thus ensuring that no other thread is reading it, then releases the exclusive lock after the modification has been done.

#### Spinlocks
A spinlock is a special type of mutex that does not use OS synchronization functions when a lock operation has to wait. Instead, it just keeps trying to update the mutex data structure to take the lock in a loop.

If the lock is not held very often, and/or is only held for very short periods, then this can be more efficient than calling heavyweight thread synchronization functions. However, if the processor has to loop too many times then it is just wasting time doing nothing, and the system would do better if the OS scheduled another thread with active work to do instead of the thread failing to acquire the spinlock.

### Semaphores
A semaphore is a very relaxed type of lockable object. A given semaphore has a predefined maximum count, and a current count. You take ownership of a semaphore with a wait operation, also referred to as decrementing the semaphore, or even just abstractly called P. You release ownership with a signal operation, also referred to as incrementing the semaphore, a post operation, or abstractly called V. The single-letter operation names are from Dijkstra's original paper on semaphores.

Every time you wait on a semaphore, you decrease the current count. If the count was greater than zero then the decrement just happens, and the wait call returns. If the count was already zero then it cannot be decremented, so the wait call will block until another thread increases the count by signalling the semaphore.

Every time you signal a semaphore, you increase the current count. If the count was zero before you called signal, and there was a thread blocked in wait then that thread will be woken. If multiple threads were waiting, only one will be woken. If the count was already at its maximum value then the signal is typically ignored, although some semaphores may report an error.

Whereas mutex ownership is tied very tightly to a thread, and only the thread that acquired the lock on a mutex can release it, semaphore ownership is far more relaxed and ephemeral. Any thread can signal a semaphore, at any time, whether or not that thread has previously waited for the semaphore.

##### An analogy
A semaphore is like a public lending library with no late fees. They might have 5 copies of C++ Concurrency in Action available to borrow. The first five people that come to the library looking for a copy will get one, but the sixth person will either have to wait, or go away and come back later.

The library doesn't care who returns the books, since there are no late fees, but when they do get a copy returned, then it will be given to one of the people waiting for it. If no-one is waiting, the book will go on the shelf until someone does want a copy.

##### Binary semaphores and Mutexes
A binary semaphore is a semaphore with a maximum count of 1. You can use a binary semaphore as a mutex by requiring that a thread only signals the semaphore (to unlock the mutex) if it was the thread that last successfully waited on it (when it locked the mutex). However, this is only a convention; the semaphore itself doesn't care, and won't complain if the "wrong" thread signals the semaphore.

### Critical Sections
In synchronization terms, a critical section is that block of code during which a lock is owned. It starts at the point that the lock is acquired, and ends at the point that the lock is released.








