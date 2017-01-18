## Hash Table
Hash table is a data structure used to implement an associative array, by interpreting the key as an array index so that we can store the value associated with key in array entry, ready for immediate access. On average, its time complexity is constant(amortized).
### Hash collision
Hash table uses hash function to transform the search key into an array index. Ideally, different keys should map to different indices. However, in practical, we generally have to face the possibility that different keys may hash to the same array index. 
### Collision Resolution
* Separate Chaining : build a linked-list of the key-value pairs whose keys hash to that index. It is called separate chaining because items that collide are chained together in separate linked lists.
* Open addressing : unlike separate chaining, open addressing tells us that we never use other data structure to store the objects, all entry records are stored in the bucket array itself.  When a new entry has to be inserted, the buckets are examined, starting with the hashed-to slot and proceeding in some probe sequence, until an unoccupied slot is found.
### Probe sequences
* Linear probing, in which the interval between probes is fixed (usually 1)
* Quadratic probing, in which the interval between probes is increased by adding the successive outputs of a quadratic polynomial to the starting value given by the original hash computation
* Double hashing, in which the interval between probes is computed by a second hash function

## Linear probing
Along with quadratic probing and double hashing, linear probing is a form of open addressing. In these schemes, each cell of a hash table stores a single key–value pair. When the hash function causes a collision by mapping a new key to a cell of the hash table that is already occupied by another key, linear probing searches the table for the closest following free location and inserts the new key there. Lookups are performed in the same way, by searching the table sequentially starting at the position given by the hash function, until finding a cell with a matching key or an empty cell.
### Pros and Cons
Linear probing provides good locality of reference, which causes it to require few uncached memory accesses per operation. Because of this, for low to moderate load factors, it can provide very high performance.d However, compared to some other open addressing strategies, its performance degrades more quickly at high load factors because of primary clustering, a tendency for one collision to cause more nearby collisions. Additionally, achieving good performance with this method requires a higher-quality hash function than for some other collision resolution schemes. When used with low-quality hash functions that fail to eliminate nonuniformities in the input distribution, linear probing can be slower than other open-addressing strategies such as double hashing, which probes a sequence of cells whose separation is determined by a second hash function, or quadratic probing, where the size of each step varies depending on its position within the probe sequence.
### Deletion
When a key–value pair is deleted, it may be necessary to move another pair backwards into its cell, to prevent searches for the moved key from finding an empty cell.

It is also possible to remove a key–value pair from the dictionary. However, it is not sufficient to do so by simply emptying its cell. This would affect searches for other keys that have a hash value earlier than the emptied cell, but that are stored in a position later than the emptied cell. The emptied cell would cause those searches to incorrectly report that the key is not present.

Instead, when a cell i is emptied, it is necessary to search forward through the following cells of the table until finding either another empty cell or a key that can be moved to cell i v. When an empty cell is found, then emptying cell i is safe and the deletion process terminates. But, when the search finds a key that can be moved to cell i, it performs this move.

This has the effect of speeding up later searches for the moved key, but it also empties out another cell, later in the same block of occupied cells. The search for a movable key continues for the new emptied cell, in the same way, until it terminates by reaching a cell that was already empty. In this process of moving keys to earlier cells, each key is examined only once. Therefore, the time to complete the whole process is proportional to the length of the block of occupied cells containing the deleted key, matching the running time of the other hash table operations.

Alternatively, it is possible to use a lazy deletion strategy in which a key–value pair is removed by replacing the value by a special flag value indicating a deleted key. However, these flag values will contribute to the load factor of the hash table. With this strategy, it may become necessary to clean the flag values out of the array and rehash all the remaining key–value pairs once too large a fraction of the array becomes occupied by deleted keys.

## Design Pattern
Software design pattern is a general reusable solution to a commonly occurring problem within a given context in software design. It is a description or template for how to solve a problem that can be used in many different situations. Design patterns are formalized best practices that the programmer can use to solve common problems when designing an application or system.

### Benefits of design pattern
(1)Design patterns can speed up the development process by providing tested, proven development paradigms. Effective software design requires considering issues that may not become visible until later in the implementation. Reusing design patterns helps to prevent subtle issues that can cause major problems and improves code readability for coders and architects familiar with the patterns.

(2)Often, people only understand how to apply certain software design techniques to certain problems. These techniques are difficult to apply to a broader range of problems. Design patterns provide general solutions, documented in a format that doesn't require specifics tied to a particular problem.

(3)In addition, patterns allow developers to communicate using well-known, well understood names for software interactions. Common design patterns can be improved over time, making them more robust than ad-hoc designs.

### Familiar design patterns:
Singleton: A class of which only a single instance can exist. Ensure a class only has one instance, and provide a global point of access to it.This is useful when exactly one object is needed to coordinate actions across the system. Examples: Singleton pattern is used for logging, drivers objects, caching and thread pool.

Observer: A way of notifying change to a number of classes. Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.Example: Following a question on quora which notifies any new answers. 

Interpreter: A way to include language elements in a program. Given a language, define a representation for its grammar along with an interpreter that uses the representation to interpret sentences in the language.Examples: Any mechanism for interpreting formal languages suites this pattern perfectly, it can be anything: from a simple calculator to a C# parser.

Template: Defer the exact steps of an algorithm to a subclass. Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm’s structure. Example: LoadData(csv,word)=>ParseAndFormatInto(XML,JSON)=>SaveToDatabase(Sql,Mongo,ES)

Adapter: Match interfaces of different classes.Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn’t otherwise because of incompatible interfaces. Examples: C++ Stack(deque),Queue(deque),PriorityQueue(vector).

Builder : Separate the construction of a complex object from its representation so that the same construction process can create different representations.Use the Builder pattern when 
* the algorithm for creating a complex object should be independent of the parts that make up the object and how they're assembled.
* the construction process must allow different representations for the object that's constructed.

Iterator Pattern: provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.It also places the task of traversal on the iterator object, not on the aggregate, which simplifies the aggregate interface and implementation, and places the responsibility where it should be. Example: STL iterators.

Factory Method: Creates an instance of several derived classes. Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

## Quick sort vs merge sort
Both are sorting algorithms based on the divide and conquer strategy. Top-down Merge-sort needs an extra array for merge operations, so its space complexity is O(n), while bottom-up merge-sort can have constant space complexity. Merge-sort has O(nlog(n)) time complexity no matter in best/average/worst scenarios. Quick-sort has O(nlog(n)) time complexity in best/average scenario but O(n^2) in worst scenario. Regarding space complexity, the space complexity of quicksort is O(log n), taking into account the stack space used for recursion. Also, quicksort cannot be implemented iteratively, unlike mergesort, where an iterative implementation, sometimes called bottom-up mergesort, is possible. 

## Throughput vs Latency
Latency is the time required to perform some action or to produce some result. Latency is measured in units of time.
Throughput is the number of such actions executed or results produced per unit of time. This is measured in units of whatever is being produced per unit of time.
Example:
Latency and throughput can be used together to describe the performance of a network. Latency refers to the time delay between when one machine sends a packet of data and the second machine receives the data (for example, if the second machine receives the data 10 ms later than the first machine sent it, the latency is 10 ms). Throughput refers to the amount of data that can be transferred in a given time (for example, if a one machine sends 1000 KB of data, and it takes 5 seconds for all of it to be received by the second machine, the throughput is 200 KB/s).

Network Latency
In data network, latency means time when a particular packet takes to reach the destination from source. The term delay is similar to latency. The latency or delay can be low if there is high congestion in the traffic or can be because of errors and distance as well.

Network Throughput
Network throughput is the amount of data that can traverse through a given medium. The network throughput is measured in bits per second (bps). Throughput can be high or low depending on your network infrastructure. Devices such as routers, switches, firewalls, cables, network cards can have significant impact on the network throughput. High speed devices and cables will definitely increase your network throughput.


## Process vs Thread

Processes are the abstraction of running programs: A binary image, virtualized memory, various kernel resources, an associated security context, and so on. Threads are the unit of execution in a process: A virtualized processor, a stack, and program state. Put another way, processes are running binaries and threads are the smallest unit of execution schedulable by an operating system's process scheduler.

Each process provides the resources needed to execute a program. A process has a virtual address space, executable code, open handles to system objects, a security context, a unique process identifier, environment variables, a priority class, minimum and maximum working set sizes, and at least one thread of execution. Each process is started with a single thread, often called the primary thread, but can create additional threads from any of its threads. 

A thread is the entity within a process that can be scheduled for execution. All threads of a process share its virtual address space and system resources. In addition, each thread maintains exception handlers, a scheduling priority, thread local storage, a unique thread identifier, and a set of structures the system will use to save the thread context until it is scheduled. 

Typical difference is, 
* processes run in separated memory while threads run in shared memory. 
* processes are typically independent, while threads exist as subsets of a process 
* processes carry considerably more state information than threads, whereas multiple threads within a process share process state as well as memory and other resources 
* processes have separate address spaces, whereas threads share their address space processes interact only through system-provided inter-process communication mechanisms 
* context switching between threads in the same process is typically faster than context switching between processes.

## IPC vs ITC (Inter-Process Communication vs Inter-Thread Communications) 
### IPC
Many processes operate independently of each other. Some processes, however, cooperate to achieve their intended purposes, and these processes need methods of communicating with one another and synchronizing their actions. One way for processes to communicate is by reading and writing information in disk files. However, for many applications, this is too slow and inflexible.Therefore, Operating System usually provides a rich set of mechanisms for interprocess communication (IPC), including the following

IPC: 
* Signals 
  * Basically, one process can "raise" a signal and have it delivered to another process. The destination process's signal handler (just a function) is invoked and the process can handle it. For example, one process might want to stop another one, and this can be done by sending the signal SIGSTOP to that process. To continue, the process has to receive signal SIGCONT. Many signals are predefined and the process has a default signal handler to deal with it.Take the ever popular SIGKILL, signal #9. Have you ever typed "kill -9 nnnn" to kill a runaway process? You were sending it SIGKILL. Now you might also remember that no process can get out of a "kill -9", and you would be correct. SIGKILL is one of the signals you can't add your own signal handler for. The aforementioned SIGSTOP is also in this category.

* Pipe
  * A unidirectional data channel. Data written to the write end of the pipe is buffered by the operating system until it is read from the read end of the pipe. Two-way data streams between processes can be achieved by creating two pipes utilizing standard input and output. Like when we are using arrow symbol in command line.
* File Locking
  * There are two types of (advisory!) locks: read locks and write locks (also referred to as shared locks and exclusive locks, respectively.) The way read locks work is that they don't interfere with other read locks. For instance, multiple processes can have a file locked for reading at the same. However, when a process has an write lock on a file, no other process can activate either a read or write lock until it is relinquished. One easy way to think of this is that there can be multiple readers simultaneously, but there can only be one writer at a time.
* Message Queue 
  * A data stream similar to a socket, but which usually preserves message boundaries. Typically implemented by the operating system, they allow multiple processes to read and write to the message queue without being directly connected to each other.  
* Socket 
  * A data stream sent over a network interface, either to a different process on the same computer or to another computer on the network. Typically byte-oriented, sockets rarely preserve message boundaries. Data written through a socket requires formatting to preserve message boundaries.  
* Shared memory 
  * Multiple processes are given access to the same block of memory which creates a shared buffer for the processes to communicate with each other. 
* Semaphore 
  * A simple structure that synchronizes multiple processes acting on shared resources. 

### ITC: 
* Synchronization 
 * primitives, like locks and semaphores 
* contidional variable/(Through Events)
 * notify_one : Unblocks one of the threads currently waiting for this condition.
 * notify_all: Unblocks all threads currently waiting for this condition.
 * wait: The execution of the current thread (which shall have locked lck's mutex) is blocked until notified.
* Shared memory*
 * Cause typically threads of the same process all live in the same process. Each thread has a private stack, which it can quickly add and remove items from. T\ All threads share a common heap. Since all threads share the same heap, access to the allocator/deallocator must be synchronized. There are various methods and libraries for avoiding allocator contention. Some languages allow you to create private pools of memory, or individual heaps, which you can assign to a single thread. every thread would be allocated its own memory space in stack while typically there is only one heap within one process. This means heap space is shared among all threads. Since it is global, it is faster in speed. But also, this causes synchronization issues, which could possibly slow the whole system down. Some languages or OS my support allocating heaps for each thread.
