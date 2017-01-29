## Hash Table
Hash table is a data structure used to implement an associative array, by interpreting the key as an array index so that we can store the value associated with key in array entry. On average, its time complexity is constant(amortized).

### Hash collision
Hash table uses hash function to transform the search key into an array index. Ideally, different keys should map to different indices. However, in practical, we generally have to face the possibility that different keys may hash to the same array index. 

### Collision Resolution
* Separate Chaining : Each bucket is independent, and has some sort of list of entries with the same index. The time for hash table operations is the time to find the bucket (which is constant) plus the time for the list operation. It is called separate chaining because items that collide are chained together in separate linked lists.
* Open addressing :  When a new entry has to be inserted, the buckets are examined, starting with the hashed-to slot and proceeding in some probe sequence, until an unoccupied slot is found. When searching for an entry, the buckets are scanned in the same sequence, until either the target record is found, or an unused array slot is found, which indicates that there is no such key in the table. Unlike separate chaining, open addressing tells us that we never use other data structure to store the objects, all entry records are stored in the bucket array itself. 

### Probe sequences
* Linear probing, in which the interval between probes is fixed (usually 1)
* Quadratic probing,  is similar to Linear probing. The difference is that if you were to try to insert into a space that is filled you would first check 1^2 = 1 element away then 2^2 = 4 elements away, then  3^2 =9 elements away then 4^2=16 elements away and so on.
* Double hashing, in which the interval between probes is computed by a second hash function

## Linear probing
When the hash function causes a collision by mapping a new key to a cell of the hash table that is already occupied by another key, linear probing searches the table for the closest following free location and inserts the new key there. Lookups are performed in the same way, by searching the table sequentially starting at the position given by the hash function, until finding a cell with a matching key or an empty cell.

### Pros and Cons
* Linear probing provides good locality of reference, which causes it to require few uncached memory accesses per operation. Because of this, for low to moderate load factors, it can provide very high performance. However, compared to some other open addressing strategies, its performance degrades more quickly at high load factors because of primary clustering, a tendency for one collision to cause more nearby collisions. Primary Clustering is the tendency for a collision resolution scheme such as linear probing to create long runs of filled slots near the hash position of keys.If the primary hash index is x, subsequent probes go to x+1, x+2, x+3 and so on, this results in Primary Clustering. Once the primary cluster forms, the bigger the cluster gets, the faster it grows. And it reduces the performance.

* Additionally, achieving good performance with this method requires a higher-quality hash function than for some other collision resolution schemes. When used with low-quality hash functions that fail to eliminate nonuniformities in the input distribution, linear probing can be slower than other open-addressing strategies such as double hashing, which probes a sequence of cells whose separation is determined by a second hash function, or quadratic probing, where the size of each step varies depending on its position within the probe sequence.

#### Insertion

The insertion algorithm is as follows:

* use hash function to find index for a record
* If that spot is already occupied, use next available spot in a "higher" index. Treat the hash table as if it is round, if you hit the end of the hash table, go back to the front

#### Searching

The search algorithm is as follows:
* use hash function to find index of where an item should be.
* If it isn't there search records that records after that hash location (remember to treat table as cicular) until either it found, or until an empty record is found. If there is an empty spot in the table before record is found, it means that the the record is not there.

NOTE: 
* It is important not to search the whole array till you get back to the starting index. 
* As soon as you see an empty spot, your search needs to stop, which means that the record is not there.

#### Removal

1. The removal algorithm is a bit trickier because after an object is removed, records in same cluster with a higher index than the removed object has to be adjusted. Otherwise the empty spot left by the removal will cause valid searches to fail.

The algorithm is as follows:
when a cell i is emptied, it is necessary to search forward through the following cells of the table until finding either another empty cell or __a key that can be moved to cell i (that is, a key whose hash value is equal to or earlier than i)__. When an empty cell is found, then emptying cell i is safe and the deletion process terminates. But, when the search finds a key that can be moved to cell i, it performs this move. This has the effect of speeding up later searches for the moved key, but it also empties out another cell, later in the same block of occupied cells. The search for a movable key continues for the new emptied cell, in the same way, until it terminates by reaching a cell that was already empty. In this process of moving keys to earlier cells, each key is examined only once. Therefore, the time to complete the whole process is proportional to the length of the block of occupied cells containing the deleted key, matching the running time of the other hash table operations.

2. Alternatively, it is possible to use a lazy deletion strategy in which a key–value pair is removed by replacing the value by a special flag value indicating a deleted key. However, these flag values will contribute to the load factor of the hash table. With this strategy, it may become necessary to clean the flag values out of the array and rehash all the remaining key–value pairs once too large a fraction of the array becomes occupied by deleted keys.


## Quadratic Probing
Quadratic probing,  is similar to Linear probing. The difference is that quadratic probing operates by taking the original hash index and adding successive values of an arbitrary quadratic polynomial until an open slot is found. 

For a given hash value, the indices generated by quadratic probing are as follows:
H+1,H+4,H+9,H+16,...,H+k

With linear probing we know that we will always find an open spot if one exists (It might be a long search but we will find it). However, this is not the case with quadratic probing unless you take care in the choosing of the table size. 

For example consider what would happen in the following situation:
Table size is 16. First 5 pieces of data that all hash to index 2
* First piece goes to index 2.
* Second piece goes to 3 ((2 + 1)%16
* Third piece goes to 6 ((2+4)%16
* Fourth piece goes to 11((2+9)%16
* Fifth piece dosen't get inserted because (2+16)%16==2 which is full so we end up back where we started and we haven't searched all empty spots.

In order to guarantee that your quadratic probes will hit every single available spots eventually, your table size must meet these requirements:
* Be a prime number
* never be more than half full (even by one element)

## Double hashing
Like linear probing, it uses one hash value as a starting point and then repeatedly steps forward an interval until the desired value is located, an empty location is reached, or the entire table has been searched; but this interval is decided using a second, independent hash function (hence the name double hashing). Unlike linear probing and quadratic probing, the interval depends on the data, so that even values mapping to the same location have different bucket sequences; this minimizes repeated collisions and the effects of clustering.

## Design Pattern
Software design pattern is a general reusable solution to a commonly occurring problem within a given context in software design. It is a description or template for how to solve a problem that can be used in many different situations. Design patterns are formalized best practices that the programmer can use to solve common problems when designing an application or system.

### Benefits of design pattern
(1)Design patterns can speed up the development process by providing tested, proven development paradigms. Effective software design requires considering issues that may not become visible until later in the implementation. Reusing design patterns helps to prevent subtle issues that can cause major problems and improves code readability for coders and architects familiar with the patterns.

(2)Often, people only understand how to apply certain software design techniques to certain problems. These techniques are difficult to apply to a broader range of problems. Design patterns provide general solutions, documented in a format that doesn't require specifics tied to a particular problem.

(3)In addition, patterns allow developers to communicate using well-known, well understood names for software interactions. Common design patterns can be improved over time, making them more robust than ad-hoc designs.

### Familiar design patterns:
__Singleton__: A class of which only a single instance can exist. Ensure a class only has one instance, and provide a global point of access to it.This is useful when exactly one object is needed to coordinate actions across the system. Examples: Singleton pattern is used for logging, caching and thread pool.

__Observer__: A way of notifying change to a number of classes. Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.Example: Following a question on quora which notifies any new answers. 

Benefits of Observer Pattern
* The Observer Pattern provides an object design where subjects and observers are loosely coupled.Which means they can interact, but have very little knowledge of each other.The only thing the subject knows about an observer is that it implements a certain interface (the Observer interface). It doesn’t need to know the concrete class of the observer, what it does, or anything else about it.
* We can add new observers at any time. 
* We never need to modify the subject to add new types of observers.
* We can reuse subjects or observers independently of each other.



__Interpreter__: Interpreter pattern provides a way to evaluate language grammar or expression. This pattern involves implementing an expression interface which tells to interpret a particular context. This pattern is used in calculator, SQL parsing, symbol processing engine etc. Any mechanism for interpreting formal languages suites this pattern perfectly.
Benefits of Interpreter
* Representing each grammar rule in a class makes the language easy to implement.
* Because the grammar is represented by classes, you can easily change or extend the language.
* By adding additional methods to the class structure, you can add new behaviors beyond interpretation, like pretty printing and more sophisticated program validation.

__Template Method__: Defer the exact steps of an algorithm to a subclass. Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm’s structure. Example: LoadData(csv,word)=>ParseAndFormatInto(XML,JSON)=>SaveToDatabase(Sql,Mongo,ES)

Benefits of Template Method pattern:
* defines the steps of an algorithm, deferring to subclasses for the implementation of those steps.
* put decision-making in high-level modules that can decide how and when to call low level modules

__Adapter__: Adapter pattern is used when you want to adapt an existing class's interface to another interface that a client expects to work with.  Adapter lets classes work together that couldn’t otherwise because of incompatible interfaces. Examples: C++ Stack(deque),Queue(deque),PriorityQueue(vector).


__Builder__ : Separate the construction of a complex object from its representation so that the same construction process can create different representations.Use the Builder pattern when 
* the algorithm for creating a complex object should be independent of the parts that make up the object and how they're assembled.
* the construction process must allow different representations for the object that's constructed.

Benefits of Builder Pattern

* Encapsulates the way a complex object is constructed.
* Allows objects to be constructed in a multistep and varying process (as opposed to one step factories).
* Hides the internal representation of the product from the client.
* Product implementations can be swapped in and out because the client only sees an abstract interface.

e.g. SqlQueryBuilder, ElasticSearchQueryBuilder

__Iterator Pattern__: provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.It also places the task of traversal on the iterator object, not on the aggregate, which simplifies the aggregate interface and implementation, and places the responsibility where it should be. Example: STL iterators.

__Factory Method__: Creates an instance of several derived classes. Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

Benefits of Factory Method
* encapsulate object creation,decouple your clients from concrete classes
* a powerful technique for coding to abstractions, not concrete classes
* The places that need an implementation of the product do not need to know how to construct one. The factory holds that information.

## Quick sort &  merge sort
### QuickSort (Unstable in general, in-place in general)
Quicksort first divides a large array into two smaller sub-arrays: the low elements and the high elements. Quicksort can then recursively sort the sub-arrays.
The steps are:
* Pick an element, called a pivot, from the array.
* Partitioning: reorder the array so that all elements with values less than the pivot come before the pivot, while all elements with values greater than the pivot come after it (equal values can go either way). After this partitioning, the pivot is in its final position. This is called the partition operation.
* Recursively apply the above steps to the sub-array of elements with smaller values and separately to the sub-array of elements with greater values.

### MergeSort (Stable in general, NOT in-place in general)
Conceptually, a merge sort works as follows:
* Divide the unsorted list into n sublists, each containing 1 element (a list of 1 element is considered sorted).
* Repeatedly merge sublists to produce new sorted sublists until there is only 1 sublist remaining. This will be the sorted list.

### Quick sort vs  Merge sort
Both are sorting algorithms based on the divide and conquer strategy. Top-down Merge-sort needs an extra array for merge operations, so its space complexity is O(n), while bottom-up merge-sort can have constant space complexity. Merge-sort has O(nlog(n)) time complexity no matter in best/average/worst scenarios. Quick-sort has O(nlog(n)) time complexity in best/average scenario but O(n^2) in worst scenario. Regarding space complexity, the space complexity of quicksort is O(log n), taking into account the stack space used for recursion. Also, quicksort cannot be implemented iteratively, unlike mergesort, where an iterative implementation, sometimes called bottom-up mergesort, is possible. 

## Throughput vs Latency
Latency is the time required to perform some action or to produce some result. Latency is measured in units of time.
Throughput is the number of such actions executed or results produced per unit of time. This is measured in units of whatever is being produced per unit of time.
Example:
Latency and throughput can be used together to describe the performance of a network. Latency refers to the time delay between when one machine sends a packet of data and the second machine receives the data (for example, if the second machine receives the data 10 ms later than the first machine sent it, the latency is 10 ms). Throughput refers to the amount of data that can be transferred in a given time for a given medium (for example, if a one cable can pass 1000 bits per second, then throughput is 1000 bit/s).

### Network Latency
In data network, latency means time when a particular packet takes to reach the destination from source. The term delay is similar to latency. The latency or delay can be low if there is high congestion in the traffic or can be because of errors and distance as well.

### Network Throughput
Network throughput is the amount of data that can traverse through a given medium. The network throughput is measured in bits per second (bps). Throughput can be high or low depending on your network infrastructure. Devices such as routers, switches, firewalls, cables, network cards can have significant impact on the network throughput. High speed devices and cables will definitely increase your network throughput.


### Relation between Latency and Throughput
High latency does not have to mean low throughput and vice versa.

For instance, in an internet connection, latency is generally measured by how long it takes for a request to get from your computer to a given server. Cable or DSL tends to have low latency, while Satellite tends to have high latency. 

However,the throughput  for these different connections are generally similar, even when the latency are not. Satellite internet, for instance, tends to have quite a bit of bandwidth. They are able to transmit a very large amount of information from the satellite to you over a short period of time. It just takes a long time to make the round trip from your computer to the server, to the satellite, and back to you again.

The reason that latency and throughput are not necessarily correlated is because of __data density__. It's not so much a matter of how quickly information can make the trip. It's more a matter of how much information can make the trip each time.

## Process vs Thread

### Process
When an executable program is read into system memory by the kernel and executed, it becomes a process. A process is an instance of a computer program that is being executed. It contains the program code and its current activity. 

### Thread
A thread of execution is the smallest sequence of programmed instructions that can be managed independently by a schedulerA thread is the entity within a process that can be scheduled for execution. All threads of a process share its virtual address space and system resources. In addition, each thread maintains exception handlers, a scheduling priority, thread local storage, a unique thread identifier, and a set of structures the system will use to save the thread context until it is scheduled. 

### Process vs Thread
Typical difference is, 
* processes run in separated memory while threads run in shared memory. 
* processes are typically independent, while threads exist as subsets of a process 
* processes carry considerably more state information than threads, whereas multiple threads within a process share process state as well as memory and other resources 
* processes have separate address spaces, whereas threads share their address space ，processes interact only through system-provided inter-process communication mechanisms 
* context switching between threads in the same process is typically faster than context switching between processes.

### Process memory layout

A process is logically divided into the following parts, known as segments:

* Text: the instructions of the program.
* Data: the static variables used by the program.
* Heap: an area from which programs can dynamically allocate extra memory.
* Stack: a piece of memory that grows and shrinks as functions are called and return and that is used to allocate storage for local variables and function call linkage information.

## IPC vs ITC (Inter-Process Communication vs Inter-Thread Communications) 
### IPC
Many processes operate independently of each other. Some processes, however, cooperate to achieve their intended purposes, and these processes need methods of communicating with one another and synchronizing their actions. 
* __Pipes__ : permit sequential communication from one process to a related process.It is a unidirectional data channel. Data written to the write end of the pipe is buffered by the operating system until it is read from the read end of the pipe. Pipes areserial devices; the data is always read from the pipe in the same order it was written.Typically, a pipe is used to communicate between two threads in a single process or between parent and child processes. A pipe’s data capacity is limited. If the writer process writes faster than the reader process consumes the data, and if the pipe cannot store more data, the writer process blocks until more capacity becomes available. If the reader tries to read but no data is available, it blocks until data becomes available.Thus, the pipe automatically synchronizes the two processes.
  * In a shell, the symbol | creates a pipe. For example, this shell command causes the shell to produce two child processes, one for ls and one for less: ```% ls | less``` .The shell also creates a pipe connecting the standard output of the ```ls``` subprocess with the standard input of the ```less``` process.The filenames listed by ```ls``` are sent to ```less``` in exactly the same order as if they were sent directly to the terminal.
* __Shared memory__ : permits processes to communicate by simply reading and writing to a specified memory location. Shared memory allows two or more processes to access the same memory as if they all called malloc and were returned pointers to the same actual memory.When one process changes the memory, all the other processes see the modification.Shared memory is the fastest form of interprocess communication because all processes share the same piece of memory.Access to this shared memory is as fast as accessing a process’s nonshared memory, and it does not require a system call or entry to the kernel. It also avoids copying data unnecessarily.
* __Mapped memory__ : is similar to shared memory, except that it is associated with a file in the filesystem.Mapped memory forms an association between a file and a process’s memory. Linux splits the file into page-sized chunks and then copies them into virtual memory pages so that they can be made available in a process’s address space.Thus, the process can read the file’s contents with ordinary memory access. It can also modify the file’s contents by writing to memory.This permits fast access to files. You can think of mapped memory as allocating a buffer to hold a file’s entire contents, and then reading the file into the buffer and (if the buffer is modified) writing the buffer back out to the file afterward. Linux handles the file reading and writing operations for you.
* __FIFOs__ : are similar to pipes, except that unrelated processes can communicate because the pipe is given a name in the filesystem.A first-in, first-out (FIFO) file is a pipe that has a name in the filesystem.Any process can open or close the FIFO; the processes on either end of the pipe need not be related to each other. FIFOs are also called named pipes.
* __Sockets__ : support communication between unrelated processes even on different computers. A socket is a bidirectional communication device that can be used to communicate with another process on the same machine or with a process running on other machines.
* __Message Queue__ : A message queue provide an asynchronous communications protocol, a system that puts a message onto a message queue does not require an immediate response to continue processing. Email is probably the best example of asynchronous messaging. When an email is sent can the sender continue processing other things without an immediate response from the receiver. This way of handling messages decouple the producer from the consumer. The producer and the consumer of the message do not need to interact with the message queue at the same time.  



### ITC: 
* Synchronization primitives
 * Mutex, event, conditional variables and semaphores are all synchronization primitives.
 * Shared and exclusive locks. 
* Shared memory*
 * Cause typically threads of the same process all live in the same process. Each thread has a private stack, which it can quickly add and remove items from. T\ All threads share a common heap. Since all threads share the same heap, access to the allocator/deallocator must be synchronized. There are various methods and libraries for avoiding allocator contention. Some languages allow you to create private pools of memory, or individual heaps, which you can assign to a single thread. every thread would be allocated its own memory space in stack while typically there is only one heap within one process. This means heap space is shared among all threads. Since it is global, it is faster in speed. But also, this causes synchronization issues, which could possibly slow the whole system down. Some languages or OS my support allocating heaps for each thread.
