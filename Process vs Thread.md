## Process vs Thread
Processes are the abstraction of running programs.Threads are the unit of execution in a process.Put another way, processes are running binaries and threads are the smallest unit of execution schedulable by an operating system's process scheduler.
### Process
* A process has a self-contained execution environment. An instance of program called Process.
* Each Process has its own address space.
* Process have to use Inter Process Communication (IPC) resource like pipes and sockets to communicate with other process.
* New processes require duplication of the parent process.
* Processes have considerable overhead.
* Process have their own copy of data segment of the parent process.
* Process have control over its child processes.
* Any change in the parent process does not affect child processes.
* Process is controlled by the operating system.
* Processes are independent.

### Thread
* Threads are sometimes called lightweight processes. It runs within the Process.
* Thread(s) shares the address space of Process that created it.
* Threads can directly communicate with other Threads of its process.
* New threads can be created easily.
* Threads have almost no overhead.
* Threads have direct access to data segment of its Process.
* Threads have considerable control over threads of the same process.
* Any change in main thread (cancellation, priority change, etc...) may affect the behavior of the other threads of the process.
* Threads are controlled by programmer in a program.
* Threads are dependent.
