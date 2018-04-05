https://stackoverflow.com/questions/19225859/difference-between-core-and-processor?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa

### Difference between core and processor?


<img src="https://software.intel.com/sites/default/files/m/8/8/c/9/c/31098-multicoresystem.png">

A core is usually the basic computation unit of the CPU - it can run a single program context (or multiple ones if it supports hardware threads such as hyperthreading on Intel CPUs), maintaining the correct program state, registers, and correct execution order, and performing the operations through ALUs. For optimization purposes, a core can also hold on-core caches with copies of frequently used memory chunks.

A CPU may have one or more cores to perform tasks at a given time. These tasks are usually software processes and threads that the OS schedules. Note that the OS may have many threads to run, but the CPU can only run X such tasks at a given time, where X = number cores * number of hardware threads per core. The rest would have to wait for the OS to schedule them whether by preempting currently running tasks or any other means.

In addition to the one or many cores, the CPU will include some interconnect that connects the cores to the outside world, and usually also a large "last-level" shared cache. There are multiple other key elements required to make a CPU work, but their exact locations may differ according to design. You'll need a memory controller to talk to the memory, I/O controllers (display, PCIe, USB, etc..). In the past these elements were outside the CPU, in the complementary "chipset", but most modern design have integrated them into the CPU.

In addition the CPU may have an integrated GPU, and pretty much everything else the designer wanted to keep close for performance, power and manufacturing considerations. CPU design is mostly trending in to what's called system on chip (SoC).

This is a "classic" design, used by most modern general-purpose devices (client PC, servers, and also tablet and smartphones). You can find more elaborate designs, usually in the academy, where the computations is not done in basic "core-like" units.
