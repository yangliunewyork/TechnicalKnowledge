__Signals__ are a limited form of inter-process communication (IPC), typically used in Unix, Unix-like, and other POSIX-compliant operating systems. A signal is an asynchronous notification sent to a process or to a specific thread within the same process in order to notify it of an event that occurred. Signals originated in 1970s Bell Labs Unix and have been more recently specified in the POSIX standard.

When a signal is sent, the operating system interrupts the target process' normal flow of execution to deliver the signal. Execution can be interrupted during any non-atomic instruction. If the process has previously registered a signal handler, that routine is executed. Otherwise, the default signal handler is executed.

Embedded programs may find signals useful for interprocess communications, as the computational and memory footprint for signals is small.

Signals are similar to interrupts, the difference being that interrupts are mediated by the processor and handled by the kernel—thus, they are not a form of IPC—while signals are mediated by the kernel (possibly via system calls) and handled by processes. The kernel may pass an interrupt as a signal to the process that caused it (typical examples are SIGSEGV, SIGBUS, SIGILL and SIGFPE).

### Sending signals

The kill(2) system call sends a specified signal to a specified process, if permissions allow. Similarly, the kill(1) command allows a user to send signals to processes. The raise(3) library function sends the specified signal to the current process.

Exceptions such as division by zero or a segmentation violation will generate signals (here, SIGFPE "floating point exception" and SIGSEGV "segmentation violation" respectively, which both by default cause a core dump and a program exit).

The kernel can generate signals to notify processes of events. For example, SIGPIPE will be generated when a process writes to a pipe which has been closed by the reader; by default, this causes the process to terminate, which is convenient when constructing shell pipelines.

Typing certain key combinations at the controlling terminal of a running process causes the system to send it certain signals:

* Ctrl-C (in older Unixes, DEL) sends an INT signal ("interrupt", SIGINT); by default, this causes the process to terminate.
* Ctrl-Z sends a TSTP signal ("terminal stop", SIGTSTP); by default, this causes the process to suspend execution.
* Ctrl-\ sends a QUIT signal (SIGQUIT); by default, this causes the process to terminate and dump core.
* Ctrl-T (not supported on all UNIXes) sends an INFO signal (SIGINFO); by default, and if supported by the command, this causes the operating system to show information about the running command.

These default key combinations with modern operating systems can be changed with the stty command.

### Relationship with hardware exceptions

A process's execution may result in the generation of a hardware exception, for instance, if the process attempts to divide by zero or incurs a TLB miss.

In Unix-like operating systems, this event automatically changes the processor context to start executing a kernel exception handler. In case of some exceptions, such as a page fault, the kernel has sufficient information to fully handle the event itself and resume the process's execution.

Other exceptions, however, the kernel cannot process intelligently and it must instead defer the exception handling operation to the faulting process. This deferral is achieved via the signal mechanism, wherein the kernel sends to the process a signal corresponding to the current exception. For example, if a process attempted integer divide by zero on an x86 CPU, a divide error exception would be generated and cause the kernel to send the SIGFPE signal to the process.

Similarly, if the process attempted to access a memory address outside of its virtual address space, the kernel would notify the process of this violation via a SIGSEGV signal. The exact mapping between signal names and exceptions is obviously dependent upon the CPU, since exception types differ between architectures.


