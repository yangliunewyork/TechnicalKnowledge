Processes and threads are related to each other but are fundamentally different.

A process can be thought of as an instance of a running program. Each process is an independent entity to which system resources such as CPU time, memory, etc. are allocated and each process is executed in a separate address space. If we want to access another process' resources, inter-process communications have to be used such as pipes, files, sockets etc. See more on Linux process.

Process provides each program with two key abstractions:

1. Logical control flow
Each process seems to have exclusive use of the CPU
2. Private virtual address space
Each process seems to have exclusive use of main memory

A thread uses the same address space of a process. A process can have multiple threads. A key difference between processes and threads is that multiple threads share parts of their state. Typically, multiple threads can read from and write to the same memory (no process can directly access the memory of another process). However, each thread still has its own stack of activation records and its own copy of CPU registers, including the stack pointer and the program counter, which together describe the state of the thread's execution.

A thread is a particular execution path of a process. When one thread modifies a process resource, the change is immediately visible to sibling threads.

* Processes are independent while thread is within a process.
* Processes have separate address spaces while threads share their address spaces.
* Processes communicate each other through inter-process communication.
* Processes carry considerable state (e.g., ready, running, waiting, or stopped) information, whereas multiple threads within a process share state as well as memory and other resources.
* Context switching between threads in the same process is typically faster than context switching between processes.
* Multithreading has some advantages over multiple processes. Threads require less overhead to manage than processes, and intraprocess thread communication is less expensive than interprocess communication.
* Multiple process concurrent programs do have one advantage: Each process can execute on a different machine (distribute program). Examples of distributed programs are file servers (NFS), file transfer clients and servers (FTP), remote log-in clients and servers (Telnet), groupware programs, and Web browsers and servers.
