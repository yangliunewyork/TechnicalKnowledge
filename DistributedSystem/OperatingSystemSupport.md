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


