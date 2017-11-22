In computing, a __context switch__ is the process of storing and restoring the state (more specifically, the execution context) of a process or thread so that execution can be resumed from the same point at a later time. This enables multiple processes to share a single CPU and is an essential feature of a multitasking operating system.

The precise meaning of "context switch" varies significantly in usage, most often to mean "thread switch or process switch" or "process switch only", either of which may be referred to as a "task switch". More finely, one can distinguish thread switch (switching between two threads within a given process), process switch (switching between two processes), mode switch (domain crossing: switching between user mode and kernel mode within a given thread), register switch, a stack frame switch, and address space switch (memory map switch: changing virtual memory to physical memory map). The computational cost of context switches varies significantly depending on what precisely it entails, from little more than a subroutine call for light-weight user processes, to very expensive, though typically much less than that of saving or restoring a process image.



#### Cost

Context switches are usually computationally intensive, and much of the design of operating systems is to optimize the use of context switches. Switching from one process to another requires a certain amount of time for doing the administration – saving and loading registers and memory maps, updating various tables and lists, etc. What is actually involved in a context switch varies between these senses and between processors and operating systems. _For example, in the Linux kernel, context switching involves switching registers, stack pointer, and program counter, but is independent of address space switching, though in a process switch an address space switch also happens._ Further still, analogous context switching happens between user threads, notably green threads, and is often very light-weight, saving and restoring minimal context. In extreme cases, such as switching between goroutines in Go, a context switch is equivalent to a coroutine yield, which is only marginally more expensive than a subroutine call.

#### thread context switch vs process context switch

__The main distinction between a thread switch and a process switch is that during a thread switch, the virtual memory space remains the same, while it does not during a process switch.__ Both types involve handing control over to the operating system kernel to perform the context switch. The process of switching in and out of the OS kernel along with the cost of switching out the registers is the largest fixed cost of performing a context switch.

A more fuzzy cost is that a context switch messes with the processors cacheing mechanisms. Basically, when you context switch, all of the memory addresses that the processor "remembers" in it's cache effectively become useless. The one big distinction here is that when you change virtual memory spaces, the processor's Translation Lookaside Buffer (TLB) or equivalent gets flushed making memory accesses much more expensive for a while. This does not happen during a thread switch.

Processes are the abstraction of running programs: A binary image, virtualized memory, various kernel resources, an associated security context, and so on. Threads are the unit of execution in a process: A virtualized processor and program state.

In single-threaded processes, the thread is the process. There's one thing going on. In multithreaded processes, there is more than one thread—more than one thing going on.

As virtualized memory is associated with the process and not threads, threads share the same memory address space. One instance of virtualized memory but many virtualized processors.

Process switching is context switching from one process to a different process. It involves switching out all of the process abstractions and resources in favor of those belonging to a new process. Most notably and expensively, this means switching the memory address space. This includes memory addresses, mappings, page tables, and kernel resources—a relatively expensive operation. On some architectures, it even means flushing various processor caches that aren't sharable across address spaces. For example, x86 has to flush the TLB and some ARM processors have to flush the entirety of the L1 cache!

Thread switching is context switching from one thread to another in the same process (switching from thread to thread across processes is just process switching). Thread switching is much, much cheaper, as it involves switching out only the abstraction unique to threads: The processor state. Switching processor state (such as the program counter and register contents) is generally very efficient. For the most part, the cost of thread-to-thread switching is about the same as the cost of entering and exiting the kernel. On systems such as Linux, that is very cheap.

Consequently, thread switching is significantly faster than process switching. How much faster depends on the operating system and architecture, but it can easily be a magnitude difference in CPU time. On an OS like Linux with cheap system calls, thread-to-thread switching is very quick.

# When to switch?

There are three potential triggers for a context switch:

##### Multitasking

Most commonly, within some scheduling scheme, one process must be switched out of the CPU so another process can run. This context switch can be triggered by the process making itself unrunnable, such as by waiting for an I/O or synchronization operation to complete. On a __pre-emptive multitasking system__, the scheduler may also switch out processes which are still runnable. To prevent other processes from being starved of CPU time, preemptive schedulers often configure a timer interrupt to fire when a process exceeds its time slice. This interrupt ensures that the scheduler will gain control to perform a context switch.

##### Interrupt handling

Modern architectures are interrupt driven. This means that if the CPU requests data from a disk, for example, it does not need to busy-wait until the read is over; it can issue the request and continue with some other execution. When the read is over, the CPU can be interrupted and presented with the read. For interrupts, a program called an interrupt handler is installed, and it is the interrupt handler that handles the interrupt from the disk.

When an interrupt occurs, the hardware automatically switches a part of the context (at least enough to allow the handler to return to the interrupted code). The handler may save additional context, depending on details of the particular hardware and software designs. Often only a minimal part of the context is changed in order to minimize the amount of time spent handling the interrupt. The kernel does not spawn or schedule a special process to handle interrupts, but instead the handler executes in the (often partial) context established at the beginning of interrupt handling. Once interrupt servicing is complete, the context in effect before the interrupt occurred is restored so that the interrupted process can resume execution in its proper state.

##### User and kernel mode switching

When a transition between user mode and kernel mode is required in an operating system, a context switch is not necessary; a mode transition is not by itself a context switch. However, depending on the operating system, a context switch may also take place at this time.

# Steps

In a switch, the state of process currently executing must be saved somehow, so that when it is rescheduled, this state can be restored.
The process state includes all the registers that the process may be using, especially the program counter, plus any other operating system specific data that may be necessary. This is usually stored in a data structure called a __process control block (PCB)__ or _switchframe_.

The PCB might be stored on a per-process stack in kernel memory (as opposed to the user-mode call stack), or there may be some specific operating system defined data structure for this information. A handle to the PCB is added to a queue of processes that are ready to run, often called the ready queue.

Since the operating system has effectively suspended the execution of one process, it can then switch context by choosing a process from the ready queue and restoring its PCB. In doing so, the program counter from the PCB is loaded, and thus execution can continue in the chosen process. Process and thread priority can influence which process is chosen from the ready queue (i.e., it may be a priority queue).

# Performance

Context switching itself has a cost in performance, due to running the task scheduler, TLB flushes, and indirectly due to sharing the CPU cache between multiple tasks. Switching between threads of a single process can be faster than between two separate processes, because threads share the same virtual memory maps, so a TLB flush is not necessary.










