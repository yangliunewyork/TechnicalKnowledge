## What Limits MySQL’s Performance ?

Many different hardware components can affect MySQL’s performance, but the two most frequent bottlenecks we see are CPU saturation and I/O saturation. CPU saturation happens when MySQL works with data that either fits in memory or can be read from disk as fast as needed. Examples are intensive cryptographic operations and joins without indexes that end up being cross-products. 

I/O saturation, on the other hand, generally happens when you need to work with much more data than you can fit in memory. If your application is distributed across a network, or if you have a huge number of queries and/or low latency requirements, the bottleneck may shift to the network instead.

Look beyond the obvious when you think you’ve found a bottleneck. A weakness in one area often puts pressure on another subsystem, which then appears to be the problem. For example, if you don’t have enough memory, MySQL might have to flush caches to make room for data it needs—and then, an instant later, read back the data it just flushed (this is true for both read and write operations). The memory scarcity can thus appear to be a lack of I/O capacity. Similarly, a saturated memory bus can appear to be a CPU problem. In fact, when we say that an application has a “CPU bottleneck” or is “CPU-bound,” what we really mean is that there is a computational bottleneck.

## How to Select CPUs for MySQL

You should consider whether your workload is CPU-bound when upgrading current hardware or purchasing new hardware. You can identify a CPU-bound workload by checking the CPU utilization, but instead of looking only at how heavily your CPUs are loaded overall, try to look at the balance of CPU usage and I/O for your most important queries, and notice whether the CPUs are loaded evenly. You can use tools such as mpstat, iostat, and vmstat (see the end of this chapter for examples) to figure out what limits your server’s performance.

#### Which Is Better: Fast CPUs or Many CPUs?

When you have a CPU-bound workload, MySQL generally benefits most from faster CPUs (as opposed to more CPUs). This isn’t always true, because it depends on the workload and the number of CPUs. However, MySQL’s current architecture has scaling issues with multiple CPUs, and MySQL cannot run a single query in parallel across many CPUs. As a result, the CPU speed limits the response time for each individual CPU-bound query.

Broadly speaking, there are two types of performance you might desire:
* Low latency (fast response time)  - To achieve this you need fast CPUs, because each query will use only a single CPU.
* High throughput     -  If you can run many queries at the same time, you may benefit from multiple CPUs to service the queries. However, whether this works in practice depends on many factors. Because MySQL scales poorly on multiple CPUs, it’s often better to use fewer fast CPUs instead.

MySQL replication also works best with fast CPUs, not many CPUs. If your workload is CPU-bound, a parallel workload on the master can easily serialize into a workload the slave can’t keep up with, even if the slave is more powerful than the master. That said, the I/O subsystem, not the CPU, is usually the bottleneck on a slave.

If you have a CPU-bound workload, another way to approach the question of whether you need fast CPUs or many CPUs is to consider what your queries are really doing. At the hardware level, a query can either be executing or waiting. The most common causes of waiting are waiting in the run queue (when the process is runnable, but all the CPUs are busy), waiting for latches or locks, and waiting for the disk or network. What do you expect your queries to be waiting for? If they’ll be waiting in the run queue or waiting for latches or locks, you generally need faster CPUs.

#### Scaling to Many CPUs and Cores
One place where multiple CPUs can be quite helpful is an online transaction processing system. These systems generally do many small operations, which can run on multiple CPUs because they’re coming from multiple connections. In this environment, concurrency can become a bottleneck. Most web applications fall into this category.

There are actually two types of concurrency problems in databases, and you need different approaches to solve them: 
1. Logical concurrency issues 

Contention for resources that are visible to the application, such as table or row locks. These problems usually require tactics such as changing your application, using a different storage engine, changing the server configuration, or using different locking hints or transaction isolation levels.

2. Internal concurrency issues 

Contention for resources such as semaphores, access to pages in the InnoDB buffer pool, and so on. You can try to work around these problems by changing server settings, changing your operating system, or using different hardware, but you might just have to live with them. In some cases, using a different storage engine or a patch to a storage engine can help ease these problems.

## Balancing Memory and Disk Resources

The biggest reason to have a lot of memory isn’t so you can hold a lot of data in memory: it’s ultimately so you can avoid disk I/O, which is orders of magnitude slower than accessing data in memory. The trick is to balance the memory and disk size, speed, cost, and other qualities so you get good performance for your workload.

This is especially true of database servers, whose behavior often goes against the predictions made by the heuristics we just mentioned. A well-designed database cache (such as the InnoDB buffer pool) is usually more efficient than an operating system’s cache, which is tuned for general-purpose tasks. The database cache has much more knowledge about its data needs, and it has special-purpose logic that helps meet those needs. Also, a system call is not required to access the data in the database cache. These special-purpose cache requirements are why you’ll have to balance your cache hierarchy to suit the particular access patterns of a database server. Because the registers and on-chip caches are not user-configurable, memory and the hard disk are the only things you can change.

#### Random Versus Sequential I/O
Database servers use both sequential and random I/O, and random I/O benefits the most from caching. You can convince yourself of this by thinking about a typical mixed workload, with some balance of single-row lookups and multirow range scans. The typical pattern is for the “hot” data to be randomly distributed; caching this data will therefore help avoid expensive disk seeks. In contrast, sequential reads generally go through the data only once, so it’s useless to cache it unless it fits completely in memory.
Another reason sequential reads don’t benefit much from caching is because they are faster than random reads. There are two reasons for this:

* __Sequential I/O is faster than random I/O.__ Sequential operations are performed faster than random operations, both in memory and on disk. Suppose your disks can do 100 random I/O operations per second and can read 50 MB per second sequentially (that’s roughly what a consumer-grade disk can achieve today). If you have 100-byte rows, that’s 100 rows per second randomly, versus 500,000 rows per second sequentially—a difference of 5,000 times, or several orders of magnitude. Thus, the random I/O benefits more from caching in this scenario. Accessing in-memory rows sequentially is also faster than accessing in-memory rows randomly. Today’s memory chips can typically access about 250,000 100- byte rows per second randomly, and 5 million per second sequentially. Note that random accesses are some 2,500 times faster in memory than on disk, while sequential accesses are only 10 times faster in memory.

* __Storage engines can perform sequential reads faster than random reads.__ A random read generally means that the storage engine must perform index operations. (There are exceptions to this rule, but it’s true for InnoDB and MyISAM.) That usually requires navigating a B-Tree data structure and comparing values to other values. In contrast, sequential reads generally require traversing a simpler data structure, such as a linked list. That’s a lot less work, so again, sequential reads are faster.

You can save work by caching sequential reads, but you can save much more work by caching random reads instead. In other words, adding memory is the best solution for random-read I/O problems if you can afford it.

#### Caching, Reads, and Writes
If you have enough memory, you can insulate the disk from read requests completely. If all your data fits in memory, every read will be a cache hit once the server’s caches are warmed up. There will still be logical reads, but no physical reads. Writes are a different matter, though. A write can be performed in memory just as a read can, but sooner or later it has to be written to the disk so it’s permanent. In other words, a cache can delay writes, but caching cannot eliminate writes as it can reads.
In fact, in addition to allowing writes to be delayed, caching can permit them to be grouped together in two important ways: 

* __Many writes, one flush__ A single piece of data can be changed many times in memory without all of the new values being written to disk. When the data is eventually flushed to disk, all the modifications that happened since the last physical write are made permanent. For example, many statements could update an in-memory counter. If the counter is incremented 100 times and then written to disk, 100 modifications have been grouped into one write. 
* __I/O merging__ Many different pieces of data can be modified in memory, and the modifications can be collected together, so the physical writes can be performed as a single disk operation.

This is why many transactional systems use a write-ahead logging strategy. Writeahead logging lets them make changes to the pages in memory without flushing the changes to disk, which usually involves random I/O and is very slow. Instead, they write a record of the changes to a sequential log file, which is much faster. A background thread can flush the modified pages to disk later; when it does, it can optimize the writes. 

Writes benefit greatly from buffering, because it converts random I/O into more sequential I/O. Asynchronous (buffered) writes are typically handled by the operating system and are batched so they can be flushed to disk more optimally. Synchronous (unbuffered) writes have to be written to disk before they finish. That’s why they benefit from buffering in a RAID controller’s battery-backed write-back cache.

#### What’s Your Working Set?















