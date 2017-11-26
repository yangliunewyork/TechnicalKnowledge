In computing, particularly in the context of the Unix operating system and its workalikes, __fork__ is an operation whereby a process creates a copy of itself. It is usually a system call, implemented in the kernel. Fork is the primary (and historically, only) method of process creation on Unix-like operating systems.

### Overview

In multitasking operating systems, processes (running programs) need a way to create new processes, e.g. to run other programs. Fork and its variants are typically the only way of doing so in Unix-like systems. For a process to start the execution of a different program, it first forks to create a copy of itself. Then, the copy, called the "child process", calls the exec system call to overlay itself with the other program: it ceases execution of its former program in favor of the other.

The fork operation creates a separate address space for the child. The child process has an exact copy of all the memory segments of the parent process. In modern UNIX variants that follow the virtual memory model from SunOS-4.0, copy-on-write semantics are implemented and the physical memory need not be actually copied. Instead, virtual memory pages in both processes may refer to the same pages of physical memory until one of them writes to such a page: then it is copied. This optimization is important in the common case where fork is used in conjunction with exec to execute a new program: typically, the child process performs only a small set of actions before it ceases execution of its program in favour of the program to be started, and it requires very few, if any, of its parent's data structures.

When a process calls fork, it is deemed the parent process and the newly created process is its child. After the fork, both processes not only run the same program, but they resume execution as though both had called the system call. They can then inspect the call's return value to determine their status, child or parent, and act accordingly.

### Example

##### What happens when we type a simple command on shell?

The shell is just a program, although it plays an important role in the system. Bash, and I would assume most other common shells, are implemented in C. The two most important native C system calls that are used in the creation of subprocesses are fork() and exec(). These functions are usually implemented in higher level languages too, including shell.

```fork()```  

"Fork" creates a duplicate copy of the calling process as its child. This is how virtually all processes on the system except for the first one (init) begin: as copies of the process which started them. Shell language doesn't actually have a fork function, but it does include syntax to generate subshells, which are the same thing.

```exec()```  

There isn't actually an exec() call in C, but it colloquially refers to a group of related functions; you can see the list with man 3 exec, which usually begins:

The exec() family of functions replace the current process image with a new process image...
And that is exactly what it does: replaces defining parts of the current process's memory stack with new stuff loaded from an executable file (e.g., /usr/bin/ls). This is why fork() is necessary first in the creation of a new process -- otherwise, the calling process ceases to be what it was and becomes something else instead; no new process would actually be created.

That may sound at first like an absurd and inefficient way to do things: why not just have a command that creates a new process from scratch? In fact, that would probably not be as efficient for a few reasons:

* The "copy" produced by fork() is a bit of an abstraction, since the kernel uses a __copy-on-write system__; all that really has to be created is a virtual memory map. If the copy then immediately calls exec(), most of the data that would have been copied if it had been modified by the process's activity never actually has to be copied/created because the process doesn't do anything requiring its use.

* Various significant aspects of the child process (e.g., its environment) do not have to be individually duplicated or set based on a complex analysis of the context, etc. They're just assumed to be the same as that of the calling process, and this is the fairly intuitive system we are familiar with.

