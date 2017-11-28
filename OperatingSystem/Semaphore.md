In computer science, a __semaphore__ is a variable or abstract data type used to control access to a common resource by multiple processes in a concurrent system such as a multiprogramming operating system.

A trivial semaphore is a plain variable that is changed (for example, incremented or decremented, or toggled) depending on programmer-defined conditions. The variable is then used as a condition to control access to some system resource.

A useful way to think of a semaphore as used in the real-world systems is as a record of how many units of a particular resource are available, coupled with operations to adjust that record safely (i.e. to avoid race conditions) as units are required or become free, and, if necessary, wait until a unit of the resource becomes available.

Semaphores are a useful tool in the prevention of race conditions; however, their use is by no means a guarantee that a program is free from these problems. Semaphores which allow an arbitrary resource count are called __counting semaphores__, while semaphores which are restricted to the values 0 and 1 (or locked/unlocked, unavailable/available) are called __binary semaphores__ and are used to implement locks.

The semaphore concept was invented by Dutch computer scientist Edsger Dijkstra in 1962 or 1963, and has found widespread use in a variety of operating systems. 

# Important observations

When used to control access to a pool of resources, a semaphore tracks only how many resources are free; it does not keep track of which of the resources are free. Some other mechanism (possibly involving more semaphores) may be required to select a particular free resource.

The paradigm is especially powerful because the semaphore count may serve as a useful trigger for a number of different actions. The librarian above may turn the lights off in the study hall when there are no students remaining, or may place a sign that says the rooms are very busy when most of the rooms are occupied.

The success of the protocol requires applications follow it correctly. Fairness and safety are likely to be compromised (which practically means a program may behave slowly, act erratically, hang or crash) if even a single process acts incorrectly. This includes:

* requesting a resource and forgetting to release it;
* releasing a resource that was never requested;
* holding a resource for a long time without needing it;
* using a resource without requesting it first (or after releasing it).

Even if all processes follow these rules, multi-resource deadlock may still occur when there are different resources managed by different semaphores and when processes need to use more than one resource at a time, as illustrated by the dining philosophers problem.

# Semaphores vs. mutexes

A mutex is essentially the same thing as a binary semaphore and sometimes uses the same basic implementation. The differences between them are in how they are used. While a binary semaphore may be used as a mutex, a mutex is a more specific use-case, in that only the thread that locked the mutex is supposed to unlock it. This constraint makes it possible to implement some additional features in mutexes:

* Since only the thread that locked the mutex is supposed to unlock it, a mutex may store the id of thread that locked it and verify the same thread unlocks it.  
* Mutexes may provide priority inversion safety. If the mutex knows who locked it and is supposed to unlock it, it is possible to promote the priority of that thread whenever a higher-priority task starts waiting on the mutex.  
* Mutexes may also provide deletion safety, where the thread holding the mutex cannot be accidentally deleted.  
* Alternately, if the thread holding the mutex is deleted (perhaps due to an unrecoverable error), the mutex can be automatically released.  
* A mutex may be recursive: a thread is allowed to lock it multiple times without causing a deadlock.  

# “mutex” and “atomic operation”

An __atomic operation__ is one that cannot be subdivided into smaller parts. As such, it will never be halfway done, so you can guarantee that it will always be observed in a consistent state. For example, modern hardware implements atomic compare-and-swap operations.

A __mutex__ (short for mutual exclusion) excludes other processes or threads from executing the same section of code (the __critical section__). Basically, it ensures that at most one thread is executing a given section of code. A mutex is also called a lock.

_Underneath the hood, locks must be implemented using hardware somehow, and the implementation must make use of the atomicity guarantees of the underlying hardware._

Most nontrivial operations cannot be made atomic, so you must either use a lock to block other threads from operating while the critical section executes, or else you must carefully design a lock-free algorithm that ensures that all the critical state-changing operations can be safely implemented using atomic operations.








