https://www.hardwaresecrets.com/how-the-cache-memory-works/  

# Introduction

The CPU fetches programs from the RAM memory. The problem with the RAM memory is that when it’s power is cut, it’s contents are lost – this classifies the RAM memory as a “volatile” medium. Thus programs and data must be stored on non-volatile media (i.e., where the contents aren’t lost after your turn your PC off) if you want to have them back after you turn off your PC, like hard disk drives and optical media like CDs and DVDs.

When you double click an icon on Windows to run a program, the program, which is usually stored on the computer’s hard disk drive, is loaded into the RAM memory, and then from the RAM memory the CPU loads the program through a circuit called memory controller, which is located inside the chipset (north bridge chip) on Intel processors or inside the CPU on AMD processors. In Figure 1 we summarize this (for AMD processors please ignore the chipset drawn).

<img src="https://s3.amazonaws.com/hs-wordpress/wp-content/uploads/2017/12/13140625/cpu_013.jpg">

The CPU can’t fetch data directly from hard disk drives because they are too slow for it, even if you consider the fastest hard disk drive available. 

By the way, transfer rates can be calculated using the following formula (on all examples so far “data per clock” is equal to “1”):

```
Transfer rate = width (number of bits) x clock rate x data per clock / 8
```

The problem is not only the transfer rate, i.e., the transfer speed, but also latency. Latency (a.k.a. “access time”) is how much time the memory delays in giving back the data that the CPU asked for – this isn’t instantaneous. When the CPU asks for an instruction (or data) that is stored at a given address, the memory delays a certain time to deliver this instruction (or data) back. On current memories, if it is labeled as having a CL (CAS Latency, which is the latency we are talking about) of 5, this means that the memory will deliver the asked data only after five memory clock cycles – meaning that the CPU will have to wait.

Waiting reduces the CPU performance. If the CPU has to wait five memory clock cycles to receive the instruction or data it asked for, its performance will be only 1/5 of the performance it would get if it were using a memory capable of delivering data immediately. 

# Dynamic RAM vs. Static RAM

There are two types of RAM memory: dynamic (DRAM) and static (SRAM). The RAM memory used on the PC is dynamic. On this kind of memory each bit of data is stored inside the memory chip in a tiny capacitor. Capacitors are very small components, meaning that millions of them can be manufactured on a small area – this is called “high density.” On the other hand capacitors lose their charge after some time, so dynamic memories need a recharge process called refresh, which occurs from time to time. During this period data cannot be read or written. Dynamic memory is also cheaper than static memory and also consumes far less power. But, as we saw, on dynamic RAM data is not readily available and it can’t work as fast as the CPU.

Static memory, on the other hand, can work as fast as the CPU, because each data bit is stored on a circuit called flip-flop, which can also deliver data with zero or very small latency, because flip-flops do not require refresh cycles. The problem is that flip-flops require several transistors to be made, i.e., they are far bigger than a single capacitor. This means that on the same area where on a static memory only one flip-flop exists, on a dynamic memory there are hundreds of capacitors. Thus static memories provide a lower density – chips have lower capacity. The other two problems with static memory: it is more expensive and it consumes more power – thus it heats more.

<img src="http://cssimplified.com/wp-content/uploads/2016/03/SRAMvsDRAM.jpg">

Even though static RAM is faster than dynamic RAM, its disadvantages prevent it from being used as the main RAM circuit.

The solution found to lower the impact of using a RAM memory that is slower than the CPU was using a small amount of static RAM between the CPU and the RAM memory. This technique is called memory cache and nowadays this small amount of static memory is located inside the CPU.

The memory cache copies most recently accessed data from the RAM memory to the static memory and tries to guess what data the CPU will ask next, loading them to the static memory before the CPU actually ask for it. The goal is to make the CPU to access the memory cache instead of accessing directly the RAM memory, since it can retrieve data from the memory cache immediately or almost immediately, while it has to wait when accessing data located on RAM. The more the CPU accesses the memory cache instead of the RAM, the fastest the system will be. We will explain exactly how the memory cache works in just a moment.

# Meet The Memory Cache

<img src="https://s3.amazonaws.com/hs-wordpress/wp-content/uploads/2017/12/13140610/cpu_063.gif">

The dotted line in Figure 2 represents the CPU body, as the RAM memory is located outside the CPU. The datapath between the RAM memory and the CPU is usually 64-bit wide (or 128-bit when dual channel memory configuration is used), running at the memory clock or the CPU external clock (or memory bus clock, in the case of AMD processors), which one is lower. We have already taught you how to calculate the memory transfer rate on the first page of this tutorial.

All the circuits inside the dotted box run at the CPU internal clock. Depending on the CPU some of its internal parts can even run at a higher clock rate. Also, the datapath between the CPU units can be wider, i.e., transfer more bits per clock cycle than 64 or 128. For example, the datapath between the L2 memory cache and the L1 instruction cache on modern processors is usually 256-bit wide. The datapath between the L1 instruction cache and the CPU fetch unit also varies depending on the CPU model – 128 bits is a typical value, but at the end of this tutorial we will present a table containing the main memory cache specs for the CPUs available on the market today. The higher the number the bits transferred per clock cycle, the fast the transfer will be done (in other words, the transfer rate will be higher).

In summary, all modern CPUs have three memory caches: L2, which is bigger and found between the RAM memory and the L1 instruction cache, which holds both instructions and data; the L1 instruction cache, which is used to store instructions to be executed by the CPU; and the L1 data cache, which is used to store data to be written back to the memory. L1 and L2 means “Level 1” and “Level 2,” respectively, and refers to the distance they are from the CPU core (execution unit). One common doubt is why having three separated cache memories (L1 data cache, L1 instruction cache and L2 cache).

Making zero latency static memory is a huge challenge, especially with CPUs running at very high clock rates. Since manufacturing near zero latency static RAM is very hard, the manufacturer uses this kind of memory only on the L1 memory cache. The L2 memory cache uses a static RAM that isn’t as fast as the memory used on the L1 cache, as it provides some latency, thus it is a little bit slower than L1 memory cache.

Pay attention to Figure 2 and you will see that L1 instruction cache works as an “input cache,” while L1 data cache works as an “output cache.” L1 instruction cache – which is usually smaller than L2 cache – is particularly efficient when the program starts to repeat a small part of it (loop), because the required instructions will be closer to the fetch unit.

This is rarely mentioned, but the L1 instruction cache is also used to store other data besides the instructions to be decoded. Depending on the CPU it can be also used to store some pre-decode data and branching information (in summary, control data that will speed up the decoding process) and sometimes the L1 instruction cache is bigger than announced, because the manufacturer didn’t add the extra space available for these extra pieces of information.

