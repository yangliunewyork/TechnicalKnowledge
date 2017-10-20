
* http://lampwww.epfl.ch/~odersky/papers/jmlc06.pdf

# Introduction

Concurrent programming is indispensable. On the one hand, distributed and mobile environments naturally involve concurrency. On the other hand, there is a general trend towards multi-core processors that are capable of running multiple threads in parallel.

With actors there exists a computation model which is especially suited for concurrent and distributed computations. Actors are basically concurrent processes which communicate through asynchronous message passing. When combined with pattern matching for messages, actor-based process models have been proven to be very efective, as the success of Erlang documents.

Erlang is a dynamically typed functional programming language designed for programming real-time control systems. Examples of such systems are telephone exchanges, network simulators and distributed resource controllers. In these systems, large numbers of concurrent processes can be active simultaneously.

Moreover, it is generally difficult to predict the number of processes and their memory requirements as they vary with time.
For the implementation of these processes, operating system threads and threads of virtual machines, such as the Java Virtual Machine, are usually too heavyweight.

The main reasons are: (1) Over-provisioning of stacks leads to quick exhaustion of virtual address space and (2) locking mechanisms often lack suitable contention managers. Therefore, Erlang implements concurrent processes by its own runtime system and not by the underlying operating system.

Actor abstractions as lightweight as Erlang's processes have been unavailable on popular virtual machines so far. At the same time, standard virtual machines are becoming an increasingly important platform for exactly the same domain of applications in which Erlang{because of its process model{has been so successful: Real-time control systems.

Another domain where virtual machines are expected to become ubiquitous are applications running on mobile devices, such as cellular phones or personal digital assistants. Usually, these devices are exposed to severe resource constraints. On such devices, only a few hundred kilobytes of memory is available to a virtual machine and applications.

This has important consequences: (1) A virtual machine for mobile devices usually offers only a restricted subset of the services of a common virtual machine for desktop or server computers. For example, the KVM1 has no support for reection (introspection) and serialization. (2) Programming abstractions used by applications have to be very lightweight to be useful. Again, thread-based concurrency abstractions are too heavyweight. Furthermore, programming models have to cope with the restricted set of services a mobile virtual machine provides.

A common alternative to programming with threads are __event-driven programming models__. Programming in explicitly event-driven models is very diffcult.

Most programming models support event-driven programming only through __inversion of control__. Instead of calling blocking operations (e.g. for obtaining user input), a program merely registers its interest to be resumed on certain events (e.g. an event signaling a pressed button, or changed contents of a text field).

In the process, event handlers are installed in the execution environment which are called when certain events occur. The program never calls these event handlers itself. Instead, the execution environment dispatches events to the installed
handlers. Thus, control over the execution of program logic is "inverted".

Virtually all approaches based on inversion of control suffer from the following two problems: First, the interactive logic of a program is fragmented across multiple event handlers (or classes, as in the state design pattern). Second, control flow among handlers is expressed implicitly through manipulation of shared state.

To obtain very lightweight abstractions without inversion of control, we make actors thread-less. We introduce event-based actors as an implementation technique for lightweight actor abstractions on non-cooperative virtual machines such as the JVM. Non-cooperative means that the virtual machine provides no means to explicitly manage the execution state of a program.

__The central idea is as follows: An actor that waits in a receive statement is not represented by a blocked thread but by a closure that captures the rest of the actor's computation. The closure is executed once a message is sent to the actor
that matches one of the message patterns specified in the receive. The execution of the closure is "piggy-backed" on the thread of the sender. If the receiving closure terminates, control is returned to the sender as if a procedure returns. If
the receiving closure blocks in a second receive, control is returned to the sender by throwing a special exception that unwinds the receiver's call stack.__

To the best of our knowledge, event-based actors are the first to (1) allow reactive behavior to be expressed without inversion of control, and (2) support arbitrary blocking operations in reactions, at the same time. Our actor library outperforms other state-of-the-art actor languages with respect to message passing speed and memory consumption by several orders of magnitude. Our implementation is able to make use of multi-processors and multi-core processors because reactions can be executed simultaneously on multiple processors. 

