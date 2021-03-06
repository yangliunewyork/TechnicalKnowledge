## Introduction
In computer science, I/O bound refers to a condition in which the time it takes to complete a computation is determined principally by the period spent waiting for input/output operations to be completed. This is the opposite of a task being CPU bound. This circumstance arises when the rate at which data is requested is slower than the rate it is consumed or, in other words, more time is spent requesting data than processing it.

#### I/O bound as an inherent problem in computing
The I/O bound state has been identified as a problem in computing almost since its inception. The Von Neumann architecture, which is employed by many computing devices, is based on a logically separate central processor unit which requests data from main memory,[clarification needed] processes it and writes back the results. Since data must be moved between the CPU and memory along a bus which has a limited data transfer rate, there exists a condition that is known as the Von Neumann bottleneck. Put simply, this means that the data bandwidth between the CPU and memory tends to limit the overall speed of computation. In terms of the actual technology that makes up a computer, the Von Neumann Bottleneck predicts that it is easier to make the CPU perform calculations faster than it is to supply it with data at the necessary rate for this to be possible.

In recent history, the Von Neumann bottleneck has become more apparent. The design philosophy of modern computers is based upon a physically separate CPU and main memory. It is possible to make the CPU run at a high data transfer rate because data is moved between locations inside them across tiny distances. The physical separation between CPU and main memory, however, requires a data bus to move data across comparatively long distances of centimetres or more. The problem of making this part of the system operate sufficiently fast to keep up with the CPU has been a great challenge to designers.

#### I/O bound as a practical problem
The I/O bound state is considered undesirable because it means that the CPU must stall its operation while waiting for data to be loaded or unloaded from main memory or secondary storage. With faster computation speed being the primary goal of new computer designs and components such as the CPU and memory being expensive, there is a strong imperative to avoid I/O bound states and eliminating them can yield a more economic improvement in performance than upgrading the CPU or memory.

As CPU gets faster, processes tend to get more I/O-bound

Or in simpler terms:

As CPU gets faster, processes tend to not increase in speed in proportion to CPU speed because they get more I/O-bound.

This means that I/O bound processes are slower than non-I/O bound processes, not faster. This is due to increases in the rate of data processing in the core, while the rate at which data is transferred from storage to the processor does not increase with it. As CPU clock speed increases, allowing more instructions to be executed in a given time window, the limiting factor of effective execution is the rate at which instructions can be delivered to the processor from storage, and sent from the processor to their destination. In short, programs naturally shift to being more and more I/O bound.

### Comparison with CPU-bound
Many factors make up how a program performs. When something is X-bound, it means that it is the slowest/most important factor with regards to possible performance improvements. If something is CPU-bound, i.e. being limited by the speed of the CPU, adding more memory or I/O bandwidth won't help. If something is I/O bound, adding a faster CPU won't help.

In the lay expression, "you are only as strong as your weakest link", the bound factor is the weakest link.

When something is I/O bound, it means that the program is limited by the rate at which data can flow through the process, be it reading and/or writing, usually to a slow storage mechanism like disk (versus a high speed one like CPU cache or memory)



Assume we have one CPU-bound process and many I/O-bound processes. As the processes flow around the system, the following scenario may result. The CPU-bound process will get and hold the CPU. During this time, all the other processes will finish their I/O and will move into the ready queue, waiting for the CPU. While the processes wait in the ready queue, the I/O devices are idle. Eventually, the CPU-bound process finishes its CPU burst and moves to an I/O device. All the I/O-bound processes, which have short CPU bursts, execute quickly and move back to the I/O queues. At this point, the CPU sits idle. The CPU-bound process will then move back to the ready queue and be allocated the CPU. Again, all the I/O processes end up waiting in the ready queue until the CPU-bound process is done. There is a convoy effect as all the other processes wait for the one big process to get off the CPU. This effect results in lower CPU and device utilization than might be possible if the shorter processes were allowed to go first.

