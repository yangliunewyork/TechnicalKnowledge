## Introduction
We have learned that an important aspect of distributed systems is resource sharing. Client applications invoke operations on resources that are often on another node or at least in another process. Applications (in the form of clients) and services (in the form of resource managers) use the middleware layer for their interactions. Middleware enables remote communication between objects or processes at the nodes of a distributed system.

The task of any operating system is to provide problem-oriented abstractions of the underlying physical resources – the processors, memory, networks, and storage media. An operating system such as UNIX (and its variants, such as Linux and Mac OS X) or Windows (and its variants, such as XP, Vista and Windows 7) provides the programmer with, for example, files rather than disk blocks, and with sockets rather than raw network access. It takes over the physical resources on a single node and manages them to present these resource abstractions through the system-call interface.

Before we begin our detailed coverage of the operating system’s middleware support role, it is useful to gain some historical perspective by examining two operating system concepts that have come about during the development of distributed systems: __network operating systems__ and __distributed operating systems__. Definitions vary, but the concepts behind them are something like the following.

Both UNIX and Windows are examples of network operating systems. They have a networking capability built into them and so can be used to access remote resources. Access is network-transparent for some – not all – types of resource. For example, through a distributed file system such as NFS, users have network-transparent access to files. That is, many of the files that users access are stored remotely, on a server, and this is largely transparent to their applications. 

But the defining characteristic is that the nodes running a network operating system retain autonomy in managing their own processing resources. In other words, there are multiple system images, one per node. With a network operating system, a user can remotely log into another computer, using ssh, for example, and run processes there. However, while the operating system manages the processes running at its own node, it does not manage processes across the nodes. 

By contrast, one could envisage an operating system in which users are never concerned with where their programs run, or the location of any resources. There is a single system image. The operating system has control over all the nodes in the system, and it transparently locates new processes at whatever node suits its scheduling policies.

An operating system that produces a single system image like this for all the resources in a distributed system is called a distributed operating system.

##### Middleware and network operating systems
In fact, there are no distributed operating systems in general use, only network operating systems such as UNIX, Mac OS and Windows. This is likely to remain the case, for two main reasons. The first is that users have much invested in their application software, which often meets their current problem-solving needs; they will not adopt a new operating system that will not run their applications, whatever efficiency advantages it offers. Attempts have been made to emulate UNIX and other operating system kernels on top of new kernels, but the emulations’ performance has not been satisfactory. Anyway, keeping emulations of all the major operating systems up-to-date as they evolve would be a huge undertaking. 

The second reason against the adoption of distributed operating systems is that users tend to prefer to have a degree of autonomy for their machines, even in a closely knit organization. This is particularly so because of performance. For example, Jones needs good interactive responsiveness while she writes her documents and would resent it if Smith’s programs were slowing her down. The combination of middleware and network operating systems provides an acceptable balance between the requirement for autonomy on the one hand and networktransparent resource access on the other. The network operating system enables users to run their favourite word processors and other standalone applications. Middleware enables them to take advantage of services that become available in their distributed system.

## The operating system layer
Users will only be satisfied if their middleware–OS combination has good performance. Middleware runs on a variety of OS–hardware combinations (platforms) at the nodes of a distributed system. The OS running at a node – a kernel and associated user-level services such as communication libraries – provides its own flavour of abstractions of local hardware resources for processing, storage and communication. Middleware utilizes a combination of these local resources to implement its mechanisms for remote invocations between objects or processes at the nodes.

Our goal in this chapter is to examine the impact of particular OS mechanisms on middleware’s ability to deliver distributed resource sharing to users. Kernels and the client and server processes that execute upon them are the chief architectural components that concern us. Kernels and server processes are the components that manage resources and present clients with an interface to the resources. As such, we require at least the following of them:

* Encapsulation: They should provide a useful service interface to their resources – that is, a set of operations that meet their clients’ needs. Details such as management of memory and devices used to implement resources should be hidden from clients. 
* Protection: Resources require protection from illegitimate accesses – for example, files are protected from being read by users without read permissions, and device registers are protected from application processes. 
* Concurrent processing: Clients may share resources and access them concurrently. Resource managers are responsible for achieving concurrency transparency.

Clients access resources by making, for example, remote method invocations to a server object, or system calls to a kernel. We call a means of accessing an encapsulated resource an invocation mechanism, however it is implemented. A combination of libraries, kernels and servers may be called upon to perform the following invocationrelated tasks:

* Communication: Operation parameters and results have to be passed to and from resource managers, over a network or within a computer. * Scheduling: When an operation is invoked, its processing must be scheduled within the kernel or server.

The core OS components and their responsibilities are:
* Process manager: Creation of and operations upon processes. A process is a unit of resource management, including an address space and one or more threads. 
* Thread manager: Thread creation, synchronization and scheduling. 
* Communication manager: Communication between threads attached to different processes on the same computer. Some kernels also support communication between threads in remote processes. Other kernels have no notion of other computers built into them, and an additional service is required for external communication. 
* Memory manager: Management of physical and virtual memory. 
* Supervisor: Dispatching of interrupts, system call traps and other exceptions; control of memory management unit and hardware caches; processor and floating-point unit register manipulations. This is known as the Hardware Abstraction Layer in Windows.

## Protection

#### Kernels and protection
The kernel is a program that is distinguished by the facts that it remains loaded from system initialization and its code is executed with complete access privileges for the physical resources on its host computer. In particular, it can control the memory management unit and set the processor registers so that no other code may access the machine’s physical resources except in acceptable ways.

Most processors have a hardware mode register whose setting determines whether privileged instructions can be executed, such as those used to determine which protection tables are currently employed by the memory management unit. __A kernel process executes with the processor in supervisor (privileged) mode; the kernel arranges that other processes execute in user (unprivileged) mode.__ 

The kernel also sets up address spaces to protect itself and other processes from the accesses of an aberrant process, and to provide processes with their required virtual memory layout. An address space is a collection of ranges of virtual memory locations, in each of which a specified combination of memory access rights applies, such as readonly or read-write. A process cannot access memory outside its address space. The terms user process or user-level process are normally used to describe one that executes in user mode and has a user-level address space (that is, one with restricted memory access rights compared with the kernel’s address space). 

When a process executes application code, it executes in a distinct user-level address space for that application; when the same process executes kernel code, it executes in the kernel’s address space. The process can safely transfer from a user-level address space to the kernel’s address space via an exception such as an interrupt or a system call trap – the invocation mechanism for resources managed by the kernel. __A system call trap is implemented by a machine-level TRAP instruction, which puts the processor into supervisor mode and switches to the kernel address space.__ When the TRAP instruction is executed, as with any type of exception, the hardware forces the processor to execute a kernel-supplied handler function, in order that no process may gain illicit control of the hardware.

__Programs pay a price for protection. Switching between address spaces may take many processor cycles, and a system call trap is a more expensive operation than a simple procedure or method call.__

## Processes and threads
The solution reached was to enhance the notion of a process so that it could be associated with multiple activities. Nowadays, a process consists of an execution environment together with one or more threads. A thread is the operating system abstraction of an activity (the term derives from the phrase ‘thread of execution’). An execution environment is the unit of resource management: a collection of local kernelmanaged resources to which its threads have access. An execution environment primarily consists of: 

* an address space; 
* thread synchronization and communication resources such as semaphores and communication interfaces (for example, sockets); 
* higher-level resources such as open files and windows.

Execution environments are normally expensive to create and manage, but several threads can share them – that is, they can share all resources accessible within them. In other words, an execution environment represents the protection domain in which its threads execute.

Threads can be created and destroyed dynamically, as needed. The central aim of having multiple threads of execution is to maximize the degree of concurrent execution between operations, thus enabling the overlap of computation with input and output, and enabling concurrent processing on multiprocessors. This can be particularly helpful within servers, where concurrent processing of clients’ requests can reduce the tendency for servers to become bottlenecks. For example, one thread can process a client’s request while a second thread servicing another request waits for a disk access to complete.

An execution environment provides protection from threads outside it, so that the data and other resources contained in it are by default inaccessible to threads residing in other execution environments. But certain kernels allow the controlled sharing of resources such as physical memory between execution environments residing at the same computer.

### Address spaces
An address space, introduced in the previous section, is a unit of management of a process’s virtual memory. It is large (typically up to 232 bytes, and sometimes up to 264 bytes) and consists of one or more regions, separated by inaccessible areas of virtual memory. A region (Figure 7.3) is an area of contiguous virtual memory that is accessible by the threads of the owning process. Regions do not overlap. Note that we distinguish between the regions and their contents. Each region is specified by the following properties:
* its extent (lowest virtual address and size); 
* read/write/execute permissions for the process’s threads; 
* whether it can be grown upwards or downwards.

Note that this model is page-oriented rather than segment-oriented. Regions, unlike segments, would eventually overlap if they were extended in size. Gaps are left between regions to allow for growth. This representation of an address space as a sparse set of disjoint regions is a generalization of the UNIX address space, which has three regions: a fixed, unmodifiable text region containing program code; a heap, part of which is initialized by values stored in the program’s binary file, and which is extensible towards higher virtual addresses; and a stack, which is extensible towards lower virtual addresses.

The provision of an indefinite number of regions is motivated by several factors. One of these is the need to support a separate stack for each thread. Allocating a separate stack region to each thread makes it possible to detect attempts to exceed the stack limits and to control each stack’s growth. Unallocated virtual memory lies beyond each stack region, and attempts to access this will cause an exception (a page fault). The alternative is to allocate stacks for threads on the heap, but then it is difficult to detect when a thread has exceeded its stack limit.

Another motivation is to enable files in general – not just the text and data sections of binary files – to be mapped into the address space. A mapped file is one that is accessed as an array of bytes in memory. The virtual memory system ensures that accesses made in memory are reflected in the underlying file storage.

The need to share memory between processes, or between processes and the kernel, is another factor leading to extra regions in the address space. A shared memory region (or shared region for short) is one that is backed by the same physical memory as one or more regions belonging to other address spaces. Processes therefore access identical memory contents in the regions that are shared, while their non-shared regions remain protected. The uses of shared regions include the following:

* Libraries: Library code can be very large and would waste considerable memory if it was loaded separately into every process that used it. Instead, a single copy of the library code can be shared by being mapped as a region in the address spaces of processes that require it. 
* Kernel: Often the kernel code and data are mapped into every address space at the same location. When a process makes a system call or an exception occurs, there is no need to switch to a new set of address mappings. 
* Data sharing and communication: Two processes, or a process and the kernel, might need to share data in order to cooperate on some task. It can be considerably more efficient for the data to be shared by being mapped as regions in both address spaces than by being passed in messages between them.

### Creation of a new process
The creation of a new process has traditionally been an indivisible operation provided by the operating system. For example, the UNIX fork system call creates a process with an execution environment copied from the caller (except for the return value from fork). The UNIX exec system call transforms the calling process into one executing the code of a named program.

For a distributed system, the design of the process-creation mechanism has to take into account the utilization of multiple computers; consequently, the process-support infrastructure is divided into separate system services.

The creation of a new process can be separated into two independent aspects:

* the choice of a target host, for example, the host may be chosen from among the nodes in a cluster of computers acting as a compute server
* the creation of an execution environment







