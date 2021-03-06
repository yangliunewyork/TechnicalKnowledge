## IPC vs ITC (Inter-Process Communication vs Inter-Thread Communications) 

### IPC

* File : A record stored on disk, or a record synthesized on demand by a file server, which can be accessed by multiple processes. 
* Socket : A data stream sent over a network interface, either to a different process on the same computer or to another computer on the network. Typically byte-oriented, sockets rarely preserve message boundaries. Data written through a socket requires formatting to preserve message boundaries. 
* Message Queue : A data stream similar to a socket, but which usually preserves message boundaries. Typically implemented by the operating system, they allow multiple processes to read and write to the message queue without being directly connected to each other. 
Example: Publish/Subscribe, Observer 
* Pipe : A unidirectional data channel. Data written to the write end of the pipe is buffered by the operating system until it is read from the read end of the pipe. Two-way data streams between processes can be achieved by creating two pipes utilizing standard input and output. Like when we are using arrow symbol in command line. 
* Shared memory : Multiple processes are given access to the same block of memory which creates a shared buffer for the processes to communicate with each other. 
* Semaphore : A simple structure that synchronizes multiple processes acting on shared resources.

### ITC 

* Synchronization primitives, like locks and semaphores 
* Through Events: wait, notify 
* Shared memory, cause typically they all live in the same process 

Each thread has a private stack, which it can quickly add and remove items from. This makes stack based memory fast, but if you use too much stack memory, as occurs in infinite recursion, you will get a stack overflow. All threads share a common heap. Since all threads share the same heap, access to the allocator/deallocator must be synchronized. There are various methods and libraries for avoiding allocator contention. Some languages allow you to create private pools of memory, or individual heaps, which you can assign to a single thread. 

Every thread would be allocated its own memory space in stack while typically there is only one heap within one process. This means heap space is shared among all threads. Since it is global, it is faster in speed. But also, this causes synchronization issues, which could possibly slow the whole system down. Some languages or OS my support allocating heaps for each thread.


