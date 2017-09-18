In computer science, __thrashing__ occurs when a computer's virtual memory subsystem is in a constant state of paging, rapidly exchanging data in memory for data on disk, to the exclusion of most application-level processing. This causes the performance of the computer to degrade or collapse. The situation may continue indefinitely until the underlying cause is addressed.

# Overview

If a process does not have access to a sufficient number of memory pages, a futile, repetitive swapping condition known as "thrashing" often arises, and the page fault rate typically becomes high. This frequently leads to high, runaway CPU utilization that can grind the system to a halt. In modern computers, thrashing may occur in the paging system (if there is not sufficient physical memory or the disk access time is overly long), or in the I/O communications subsystem (especially in conflicts over internal bus access), etc.

Depending on the configuration and algorithms involved, the throughput and latency of a system may degrade by multiple orders of magnitude. Thrashing is a state in which the CPU performs 'productive' work less, and 'swapping' more. The CPU is busy in swapping pages so much that it can not respond to users' programs and interrupts as much as required. Thrashing occurs when there are too many pages in memory, and each page refers to another page. The real memory shortens in capacity to have all the pages in it, so it uses 'virtual memory'. When each page in execution demands that page that is not currently in real memory (RAM) it places some pages on virtual memory and adjusts the required page on RAM. If the CPU is too busy in doing this task, thrashing occurs.

### Causes

In virtual memory systems, thrashing may be caused by programs or workloads that present insufficient locality of reference: if the working set of a program or a workload cannot be effectively held within physical memory, then constant data swapping, i.e., thrashing, may occur.
















