## What is CPU ?

![alt](http://www.ict4u.net/components/components-images/cpu-overview.jpg)


The brain of the computer is the CPU. It fetches instructions from memory and executes them. The basic cycle of every CPU is to fetch the first instruction from memory, decode it to determine its type and operands, execute it, and then fetch, decode, and execute subsequent instructions. In this way, programs are carried out.

Because accessing memory to get an instruction or data word takes much longer than executing an instruction, all CPUs contain some registers inside to hold key variables and temporary results. Thus the instruction set generally contains instructions to load a word from memory into a register, and store a word from a register into memory. Other instructions combine two operands from registers, memory, or both into a result, such as adding two words and storing the result in a register or in memory.

In addition to the general registers used to hold variables and temporary results, most computers have several special registers that are visible to the programmer. One of these is the program counter, which contains the memory address of the next instruction to be fetched. After that instruction has been fetched, the program counter is updated to point to its successor.

Another register is the stack pointer, which points to the top of the current stack in memory. The stack contains one frame for each procedure that has been entered but not yet exited. A procedure's stack frame holds those input parameters, local variables, and temporary variables that are not kept in registers.

Yet another register is the PSW (Program Status Word). This register contains the condition code bits, which are set by comparison instructions, the CPU priority, the mode (user or kernel), and various other control bits.Â  User programs may normally read the entire PSW but typically may write only some of its fields. The PSW plays an important role in system calls and I/O.

The operating system must be aware of all the registers. When time multiplexing the CPU, the operating system will often stop the running program to (re)start another one. Every time it stops a running program, the operating system must save all the registers so they can be restored when the program runs later.

Most CPUs, except very simple ones used in embedded systems, have two modes, kernel mode and user mode, as mentioned earlier. Usually a bit in the PSW controls the mode. When running in kernel mode, the CPU can execute every instruction in its instruction set and use every feature of the hardware. The operating system runs in kernel mode, giving it access to the complete hardware.

In contrast, user programs run in user mode, which permits only a subset of the instructions to be executed and a subset of the features to be accessed. Generally, all instructions involving I/O and memory protection are disallowed in user mode. Setting the PSW mode bit to kernel mode-is also forbidden, of course.

To obtain services from the operating system, a user program must make a system call, which traps into the kernel and invokes the operating system. The TRAP instruction switches from user mode to kernel mode and starts the operating system. When the work has been completed, control is returned to the user program at the instruction following the system call.

It is worth noting that computers have traps other than the instruction for executing a system call. Most of the other traps are caused by the hardware to warn of an exceptional situation such as an attempt to divide by 0 or a floating-point underflow.




## Wiki definition

A common property of computer programs is locality of reference, which refers to accessing the same values repeatedly and holding frequently used values in registers to improve performance; this makes fast registers and caches meaningful.[1] Allocating frequently used variables to registers can be critical to a program's performance; this register allocation is performed either by a compiler in the code generation phase, or manually by an assembly language programmer.Traditionally, the term "CPU" refers to a processor, more specifically to its processing unit and control unit (CU), distinguishing these core elements of a computer from external components such as main memory and I/O circuitry.

The form, design and implementation of CPUs have changed over the course of their history, but their fundamental operation remains almost unchanged. Principal components of a CPU include the arithmetic logic unit (ALU) that performs arithmetic and logic operations, processor registers that supply operands to the ALU and store the results of ALU operations, and a control unit that orchestrates the fetching (from memory) and execution of instructions by directing the coordinated operations of the ALU, registers and other components.

Most modern CPUs are microprocessors, meaning they are contained on a single integrated circuit (IC) chip. An IC that contains a CPU may also contain memory, peripheral interfaces, and other components of a computer; such integrated devices are variously called microcontrollers or systems on a chip (SoC). Some computers employ a multi-core processor, which is a single chip containing two or more CPUs called "cores"; in that context, one can speak of such single chips as "sockets". Array processors or vector processors have multiple processors that operate in parallel, with no unit considered central. There also exists the concept of virtual CPUs which are an abstraction of dynamical aggregated computational resources.

# CPU vs core vs processor

![alt](https://i.stack.imgur.com/RaFrm.png)

__A core is usually the basic computation unit of the CPU - it can run a single program context (or multiple ones if it supports hardware threads such as hyperthreading on Intel CPUs), maintaining the correct program state, registers, and correct execution order, and performing the operations through ALUs.__ For optimization purposes, a core can also hold on-core caches with copies of frequently used memory chunks.

A CPU may have one or more cores to perform tasks at a given time. These tasks are usually software processes and threads that the OS schedules. Note that the OS may have many threads to run, but the CPU can only run X such tasks at a given time, where ```X = number cores * number of hardware threads per core```. The rest would have to wait for the OS to schedule them whether by preempting currently running tasks or any other means.

In addition to the one or many cores, the CPU will include some interconnect that connects the cores to the outside world, and usually also a large "last-level" shared cache. There are multiple other key elements required to make a CPU work, but their exact locations may differ according to design. You'll need a memory controller to talk to the memory, I/O controllers (display, PCIe, USB, etc..). In the past these elements were outside the CPU, in the complementary "chipset", but most modern design have integrated them into the CPU.

In addition the CPU may have an integrated GPU, and pretty much everything else the designer wanted to keep close for performance, power and manufacturing considerations. CPU design is mostly trending in to what's called system on chip (SoC).

This is a "classic" design, used by most modern general-purpose devices (client PC, servers, and also tablet and smartphones). You can find more elaborate designs, usually in the academy, where the computations is not done in basic "core-like" units.

```
alvas@server:~$ lscpu
Architecture:          x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                96
On-line CPU(s) list:   0-95
Thread(s) per core:    2
Core(s) per socket:    12
Socket(s):             4
NUMA node(s):          4
Vendor ID:             GenuineIntel
CPU family:            6
Model:                 62
Model name:            Intel(R) Xeon(R) CPU E5-4657L v2 @ 2.40GHz
Stepping:              4
CPU MHz:               2700.000
CPU max MHz:           2900.0000
CPU min MHz:           1200.0000
BogoMIPS:              4801.91
Virtualization:        VT-x
L1d cache:             32K
L1i cache:             32K
L2 cache:              256K
L3 cache:              30720K
NUMA node0 CPU(s):     0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92
NUMA node1 CPU(s):     1,5,9,13,17,21,25,29,33,37,41,45,49,53,57,61,65,69,73,77,81,85,89,93
NUMA node2 CPU(s):     2,6,10,14,18,22,26,30,34,38,42,46,50,54,58,62,66,70,74,78,82,86,90,94
NUMA node3 CPU(s):     3,7,11,15,19,23,27,31,35,39,43,47,51,55,59,63,67,71,75,79,83,87,91,95
```
