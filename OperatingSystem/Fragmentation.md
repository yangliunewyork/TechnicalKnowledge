In computer storage, __fragmentation__ is a phenomenon in which storage space is used inefficiently, reducing capacity or performance and often both. The exact consequences of fragmentation depend on the specific system of storage allocation in use and the particular form of fragmentation. In many cases, fragmentation leads to storage space being "wasted", and in that case the term also refers to the wasted space itself. For other systems (e.g. the FAT file system) the space used to store given data (e.g. files) is the same regardless of the degree of fragmentation (from none to extreme).

__There are three different but related forms of fragmentation: external fragmentation, internal fragmentation, and data fragmentation, which can be present in isolation or conjunction. Fragmentation is often accepted in return for improvements in speed or simplicity.__

# Basic principle

When a computer program requests blocks of memory from the computer system, the blocks are allocated in chunks. When the computer program is finished with a chunk, it can free the chunk back to the system, making it available to later be allocated again to another or the same program. The size and the amount of time a chunk is held by a program varies. During its lifespan, a computer program can request and free many chunks of memory.

When a program is started, the free memory areas are long and contiguous. Over time and with use, the long contiguous regions become fragmented into smaller and smaller contiguous areas. Eventually, it may become impossible for the program to obtain large contiguous chunks of memory.

# Types of fragmentation

### Internal fragmentation

Due to the rules governing memory allocation, more computer memory is sometimes allocated than is needed. For example, memory can only be provided to programs in chunks divisible by 4, 8 or 16, and as a result if a program requests perhaps 23 bytes, it will actually get a chunk of 32 bytes. When this happens, the excess memory goes to waste. In this scenario, the unusable memory is contained within an allocated region. This arrangement, termed fixed partitions, suffers from inefficient memory use - any process, no matter how small, occupies an entire partition. This waste is called __internal fragmentation__.

Unlike other types of fragmentation, internal fragmentation is difficult to reclaim; usually the best way to remove it is with a design change. For example, in dynamic memory allocation, __memory pools__ drastically cut internal fragmentation by spreading the space overhead over a larger number of objects.

##### Memory pool

__Memory pools__, also called __fixed-size blocks allocation__, is the use of pools for memory management that allows dynamic memory allocation comparable to malloc or C++'s operator new. As those implementations suffer from fragmentation because of variable block sizes, it is not recommendable to use them in a real time system due to performance. A more efficient solution is preallocating a number of memory blocks with the same size called the memory pool. The application can allocate, access, and free blocks represented by handles at run time.

### External fragmentation

External fragmentation arises when free memory is separated into small blocks and is interspersed by allocated memory. It is a weakness of certain storage allocation algorithms, when they fail to order memory used by programs efficiently. The result is that, although free storage is available, it is effectively unusable because it is divided into pieces that are too small individually to satisfy the demands of the application. The term "external" refers to the fact that the unusable storage is outside the allocated regions.

For example, consider a situation wherein a program allocates 3 continuous blocks of memory and then frees the middle block. The memory allocator can use this free block of memory for future allocations. However, it cannot use this block if the memory to be allocated is larger in size than this free block.

External fragmentation also occurs in file systems as many files of different sizes are created, change size, and are deleted. The effect is even worse if a file which is divided into many small pieces is deleted, because this leaves similarly small regions of free spaces.

### Data fragmentation

Data fragmentation occurs when a collection of data in memory is broken up into many pieces that are not close together. It is typically the result of attempting to insert a large object into storage that has already suffered external fragmentation.

For example, files in a file system are usually managed in units called blocks or clusters. When a file system is created, there is free space to store file blocks together contiguously. This allows for rapid sequential file reads and writes. However, as files are added, removed, and changed in size, the free space becomes externally fragmented, leaving only small holes in which to place new data. When a new file is written, or when an existing file is extended, the operating system puts the new data in new non-contiguous data blocks to fit into the available holes. The new data blocks are necessarily scattered, slowing access due to seek time and rotational latency of the read/write head, and incurring additional overhead to manage additional locations. This is called file system fragmentation.

When writing a new file of a known size, if there are any empty holes that are larger than that file, the operating system can avoid data fragmentation by putting the file into any one of those holes. There are a variety of algorithms for selecting which of those potential holes to put the file; each of them is a heuristic approximate solution to the bin packing problem. The "best fit" algorithm chooses the smallest hole that is big enough. The "worst fit" algorithm chooses the largest hole. The "first-fit algorithm" chooses the first hole that is big enough. The "next fit" algorithm keeps track of where each file was written. The "next fit" algorithm is faster than "first fit", which is in turn faster than "best fit", which is the same speed as "worst fit".

Just as compaction can eliminate external fragmentation, data fragmentation can be eliminated by rearranging data storage so that related pieces are close together. For example, the primary job of a defragmentation tool is to rearrange blocks on disk so that the blocks of each file are contiguous. Most defragmenting utilities also attempt to reduce or eliminate free space fragmentation. Some moving garbage collectors will also move related objects close together (this is called compacting) to improve cache performance.

# Overview

Compared to external fragmentation, overhead and internal fragmentation account for little loss in terms of wasted memory and reduced performance. It is defined as:

![alt](https://wikimedia.org/api/rest_v1/media/math/render/svg/718dd9727b3c8db3a8b733a9558608e16fcf5434)

Fragmentation of 0% means that all the free memory is in a single large block; fragmentation is 90% (for example) when 100 MB free memory is present but largest free block of memory for allocation is just 10 MB.

External fragmentation tends to be less of a problem in file systems than in primary memory (RAM) allocation systems, because programs usually require their RAM allocation requests to be fulfilled with contiguous blocks, but file systems typically are designed to be able use any collection of available blocks (fragments) to assemble a file which logically appears contiguous. Therefore, if a highly fragmented file or many small files are deleted from a full volume and then a new file with size equal to the newly freed space is created, the new file will simply reuse the same fragments that were freed by the deletion. If what was deleted was one file, the new file and will be just as fragmented as that old file was, but in any case there will be no barrier to using all the (highly fragmented) free space to create the new file. In RAM, on the other hand, the allocation systems used often cannot assemble a large block to meet a request from small noncontiguous free blocks, and so the request cannot be fulfilled and the program cannot proceed to do whatever it needed that memory for (unless it can reissue the request as a number of smaller separate requests).

# Problems

### Allocation failure

The most severe problem caused by fragmentation is causing a process or system to fail, due to premature resource exhaustion: if a contiguous allocation is needed and cannot be satisfied, failure occurs. Fragmentation causes this to occur even if there is enough of the resource, but not a contiguous amount. For example, if a computer has 4 GiB of memory and 2 GiB are free, but the memory is fragmented in an alternating sequence of 1 MiB used, 1 MiB free, then a request for 1 contiguous GiB of memory cannot be satisfied even though 2 GiB total are free.

In order to avoid this, the allocator may, instead of failing, trigger a defragmentation (or memory compaction cycle) or other resource reclamation, such as a major garbage collection cycle, in the hope that it will then be able to satisfy the request. This allows the process to proceed, but can severely impact performance.

### Performance degradation

Fragmentation causes performance degradation for a number of reasons. Most basically, fragmentation increases the work required to allocate and access a resource. For example, on a hard drive or tape drive, sequential data reads are very fast, but seeking to a different address is slow, so reading or writing a fragmented file requires numerous seeks and is thus much slower, in addition to causes greater wear on the device. Further, if a resource is not fragmented, allocation requests can simply be satisfied by returning a single block from the start of the free area. However it is fragmented, the request requires either searching for a large enough free block, which may take a long time, or fulfilling the request by several smaller blocks (if this is possible), which results in this allocation being fragmented, and requiring additional overhead to manage the several pieces.

A subtler problem is that fragmentation may prematurely exhaust a cache, causing thrashing, due to caches holding blocks, not individual data. For example, suppose a program has a working set of 256 KiB, and is running on a computer with a 256 KiB cache (say L2 instruction+data cache), so the entire working set fits in cache and thus executes quickly, at least in terms of cache hits. Suppose further that it has 64 translation lookaside buffer (TLB) entries, each for a 4 KiB page: each memory access requires a virtual-to-physical translation, which is fast if the page is in cache (here TLB). If the working set is unfragmented, then it will fit onto exactly 64 pages (the page working set will be 64 pages), and all memory lookups can be served from cache. However, if the working set is fragmented, then it will not fit into 64 pages, and execution will slow due to thrashing: pages will be repeatedly added and removed from the TLB during operation. Thus cache sizing in system design must include margin to account for fragmentation.

Memory fragmentation is one of the most severe problems faced by system managers.[citation needed] Over time, it leads to degradation of system performance. Eventually, memory fragmentation may lead to complete loss of (application-usable) free memory.

Memory fragmentation is a kernel programming level problem. During real-time computing of applications, fragmentation levels can reach as high as 99%, and may lead to system crashes or other instabilities.[citation needed] This type of system crash can be difficult to avoid, as it is impossible to anticipate the critical rise in levels of memory fragmentation. However, while it may not be possible for a system to continue running all programs in the case of excessive memory fragmentation, a well-designed system should be able to recover from the critical fragmentation condition by moving in memory some memory blocks used by the system itself in order to enable consolidation of free memory into fewer, larger blocks, or, in the worst case, by terminating some programs to free their memory and then defragmenting the resulting sum total of free memory. This will at least avoid a true crash in the sense of system failure and allow the system to continue running some programs, save program data, etc. It is also important to note that fragmentation is a phenomenon of system software design; different software will be susceptible to fragmentation to different degrees, and it is possible to design a system that will never be forced to shut down or kill processes as a result of memory fragmentation.








































