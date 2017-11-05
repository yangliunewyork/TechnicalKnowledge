## What is Cache
In computing, a cache, is a hardware or software component that stores data so future requests for that data can be served faster; the data stored in a cache might be the result of an earlier computation, or the duplicate of data stored elsewhere. A cache hit occurs when the requested data can be found in a cache, while a cache miss occurs when it cannot. Cache hits are served by reading data from the cache, which is faster than recomputing a result or reading from a slower data store; thus, the more requests can be served from the cache, the faster the system performs.

To be cost-effective and to enable efficient use of data, caches are relatively small. Nevertheless, caches have proven themselves in many areas of computing because access patterns in typical computer applications exhibit the __locality of reference__. Moreover, access patterns exhibit temporal locality if data is requested again that has been recently requested already, while spatial locality refers to requests for data physically stored close to data that has been already requested.

## Motivation
There is an inherent trade-off between size and speed (given that a larger resource implies greater physical distances) but also a tradeoff between expensive, premium technologies (such as SRAM) vs cheaper, easily mass-produced commodities (such as DRAM or hard disks).

The buffering provided by a cache benefits both throughput and latency:


* Latency 
  * A larger resource incurs a significant latency for access – e.g. it can take 100s of clock cycles for a modern 4 GHz processor to reach DRAM. This is mitigated by reading in large chunks, in the hope that subsequent reads will be from nearby locations. Prediction or explicit prefetching might also guess where future reads will come from and make requests ahead of time; if done correctly the latency is bypassed altogether.

* Throughput and granularity
  * The use of a cache also allows for higher throughput from the underlying resource, by assembling multiple fine grain transfers into larger, more efficient requests. In the case of DRAM, this might be served by a wider bus. Imagine a program scanning bytes in a 32bit address space, but being served by a 128bit off chip data bus; individual uncached byte accesses would only allow 1/16th of the total bandwidth to be used, and 80% of the data movement would be addresses. Reading larger chunks reduces the fraction of bandwidth required for transmitting address information.
  
## Operation
Hardware implements cache as a block of memory for temporary storage of data likely to be used again. Central processing units (CPUs) and hard disk drives (HDDs) frequently use a cache, as do web browsers and web servers.
A cache is made up of a pool of entries. Each entry has associated data, which is a copy of the same data in some backing store. Each entry also has a tag, which specifies the identity of the data in the backing store of which the entry is a copy.

When the cache client (a CPU, web browser, operating system) needs to access data presumed to exist in the backing store, it first checks the cache. If an entry can be found with a tag matching that of the desired data, the data in the entry is used instead. This situation is known as a __cache hit__. So, for example, a web browser program might check its local cache on disk to see if it has a local copy of the contents of a web page at a particular URL. In this example, the URL is the tag, and the contents of the web page is the data. The percentage of accesses that result in cache hits is known as the hit rate or hit ratio of the cache.

The alternative situation, when the cache is consulted and found not to contain data with the desired tag, has become known as a cache miss. The previously uncached data fetched from the backing store during miss handling is usually copied into the cache, ready for the next access.

During a cache miss, the CPU usually ejects some other entry in order to make room for the previously uncached data. The heuristic used to select the entry to eject is known as the replacement policy. One popular replacement policy, "least recently used" (LRU), replaces the least recently used entry (see cache algorithm). More efficient caches compute use frequency against the size of the stored contents, as well as the latencies and throughputs for both the cache and the backing store. This works well for larger amounts of data, longer latencies and slower throughputs, such as experienced with a hard drive and the Internet, but is not efficient for use with a CPU cache.

## Buffer vs. cache
The semantics of a "buffer" and a "cache" are not necessarily mutually exclusive; even so, there are fundamental differences in intent between the process of caching and the process of buffering.

Fundamentally, caching realizes a performance increase for transfers of data that is being repeatedly transferred. While a caching system may realize a performance increase upon the initial (typically write) transfer of a data item, this performance increase is due to buffering occurring within the caching system.

With read caches, a data item must have been fetched from its residing location at least once in order for subsequent reads of the data item to realize a performance increase by virtue of being able to be fetched from the cache's (faster) intermediate storage rather than the data's residing location. With write caches, a performance increase of writing a data item may be realized upon the first write of the data item by virtue of the data item immediately being stored in the cache's intermediate storage, deferring the transfer of the data item to its residing storage at a later stage or else occurring as a background process. Contrary to strict buffering, a caching process must adhere to a (potentially distributed) cache coherency protocol in order to maintain consistency between the cache's intermediate storage and the location where the data resides. Buffering, on the other hand,
reduces the number of transfers for otherwise novel data amongst communicating processes, which amortizes overhead involved for several small transfers over fewer, larger transfers,
provides an intermediary for communicating processes which are incapable of direct transfers amongst each other, or
ensures a minimum data size or representation required by at least one of the communicating processes involved in a transfer.

With typical caching implementations, a data item that is read or written for the first time is effectively being buffered; and in the case of a write, mostly realizing a performance increase for the application from where the write originated. Additionally, the portion of a caching protocol where individual writes are deferred to a batch of writes is a form of buffering. The portion of a caching protocol where individual reads are deferred to a batch of reads is also a form of buffering, although this form may negatively impact the performance of at least the initial reads (even though it may positively impact the performance of the sum of the individual reads). In practice, caching almost always involves some form of buffering, while strict buffering does not involve caching.

A buffer is a temporary memory location that is traditionally used because CPU instructions cannot directly address data stored in peripheral devices. Thus, addressable memory is used as an intermediate stage. Additionally, such a buffer may be feasible when a large block of data is assembled or disassembled (as required by a storage device), or when data may be delivered in a different order than that in which it is produced. Also, a whole buffer of data is usually transferred sequentially (for example to hard disk), so buffering itself sometimes increases transfer performance or reduces the variation or jitter of the transfer's latency as opposed to caching where the intent is to reduce the latency. These benefits are present even if the buffered data are written to the buffer once and read from the buffer once.
A cache also increases transfer performance. A part of the increase similarly comes from the possibility that multiple small transfers will combine into one large block. But the main performance-gain occurs because there is a good chance that the same data will be read from cache multiple times, or that written data will soon be read. A cache's sole purpose is to reduce accesses to the underlying slower storage. Cache is also usually an abstraction layer that is designed to be invisible from the perspective of neighboring layers.
  
# How The Cache Memory Works

![alt](http://www.hardwaresecrets.com/wp-content/uploads/cpu_063.gif)

In summary, all modern CPUs have three memory caches: L2, which is bigger and found between the RAM memory and the L1 instruction cache, which holds both instructions and data; the L1 instruction cache, which is used to store instructions to be executed by the CPU; and the L1 data cache, which is used to store data to be written back to the memory. L1 and L2 means “Level 1” and “Level 2,” respectively, and refers to the distance they are from the CPU core (execution unit). One common doubt is why having three separated cache memories (L1 data cache, L1 instruction cache and L2 cache).

Here is how the memory cache works. The CPU fetch unit looks for the next instruction to be executed in the L1 instruction cache. If it isn’t there, it will look for it on the L2 cache. Then, if it is not there, it will have to go to the RAM memory to fetch the instruction.

We call a “hit” when the CPU loads a required instruction or data from the cache, and we call a “miss” if the required instruction or data isn’t there and the CPU needs to access the system RAM memory directly.

When the CPU loads an instruction from a certain memory position, a circuit called memory cache controller loads into the memory cache a small block of data below the current position that the CPU has just loaded. Since usually programs flow in a sequential way, the next memory position the CPU will request will probably be the position immediately below the memory position that it has just loaded. Since the memory cache controller already loaded some data below the first memory position read by the CPU, the next data will probably be inside the memory cache, so the CPU doesn’t need to go outside to grab the data: it is already loaded inside in the memory cache embedded in the CPU, which it can access at its internal clock rate.

This amount of data is called line and it is usually 64 bytes long (more on that in the next page).

Besides loading this small amount of data, the memory controller is always trying to guess what the CPU will ask next. A circuit called prefetcher, for example, loads more data located after these first 64 bytes from RAM into the memory cache. If the program continues to load instructions and data from memory positions in a sequential way, the instructions and data that the CPU will ask next will be already loaded into the memory cache.

So we can summarize how the memory cache works as:

1. The CPU asks for instruction/data stored in address “a.”  

2. Since the contents from address “a” aren’t inside the memory cache, the CPU has to fetch it directly from RAM.  

3. The cache controller loads a line (typically 64 bytes) starting at address “a” into the memory cache. This is more data than the CPU requested, so if the program continues to run sequentially (i.e., asks for address a+1) the next instruction/data the CPU will ask will be already loaded in the memory cache.  

4. A circuit called prefetcher loads more data located after this line, i.e., starts loading the contents from address a+64 on into the cache. To give you a real example, Pentium 4 CPUs have a 256-byte prefetcher, so it loads the next 256 bytes after the line already loaded into the cache.  

If programs always run sequentially the CPU would never need to fetch data directly from the RAM memory – except to load the very first instruction – as the instructions and data required by the CPU would always be inside the memory cache before the CPU would ask for them.

However programs do not run like this, from time to time they jump from one memory position to another. The main challenge of the cache controller is trying to guess what address the CPU will jump, loading the content of this address into the memory cache before the CPU asks for it in order to avoid the CPU having to go to the RAM memory, what slows the system down. This task is called branch predicting and all modern CPUs have this feature.

Modern CPUs have a hit rate of at least 80%, meaning that at least 80% of the time the CPU isn’t accessing the RAM memory directly, but the memory cache instead.

### Memory Cache Organization

The memory cache is divided internally into lines, each one holding from 16 to 128 bytes, depending on the CPU. On the majority of current CPUs the memory cache is organized in 64-byte lines (512 bits), so we will be considering a memory cache using 64-byte lines in our examples throughout this tutorial. On the last page we will present the main memory cache specs for all CPUs currently found on the market.

So a 512 KB L2 memory cache is divided into 8,192 lines. Keep in mind that 1 KB is 2^10 or 1,024 bytes and not 1,000 bytes, so the math is 524,288 / 64 = 8,192. We will be considering a single-core CPU with 512 KB L2 memory cache in our examples. In Figure 5 we illustrate this memory cache internal organization.

![alt](http://www.hardwaresecrets.com/wp-content/uploads/481_051.gif)

__The memory cache can work under three different configurations: direct mapping, fully associative and set associative (a.k.a. n-way set associative).__ The later is the most used configuration nowadays, but let’s take a look at how these three configurations work.

##### Direct Mapping

Direct mapping is the simplest way of creating a memory cache. In this configuration the main RAM memory is divided into the same number of lines there are inside the memory cache. If we have a system with 1 GB of RAM, this 1 GB will be divided into 8,192 blocks (assuming the memory cache uses the configuration we describe above), each one with 128 KB (1,073,741,824 / 8,192 = 131,072 – keep in mind that 1 GB is 2^30 bytes, 1 MB is 2^20 bytes and 1 KB is 2^10 bytes). If our system had 512 MB the memory would be also divided into 8,192 blocks, but this time each one would have 64 KB. And so on. We illustrate this organization in Figure 6.

![alt](http://www.hardwaresecrets.com/wp-content/uploads/481_061.gif)

The main advantage of direct mapping is that it is the easiest configuration to implement.

When the CPU asks for a given address from the RAM memory (e.g., address 1,000), the cache controller will load a line (64 bytes) from the RAM memory and store this line on the memory cache (i.e., addresses 1,000 through 1,063, assuming we are using 8-bit addressing scheme just to help our examples). So if the CPU asks again the contents of this address or of the next few addresses right after this address (i.e., any address from 1,000 to 1,063) they will be already inside the cache.

The problem is that if the CPU needs two addresses that are mapped to the same cache line, a cache miss will occur (this problem is called collision or conflict). Continuing our example, if the CPU asks address 1,000 and then asks address 2,000, a cache miss will occur because these two addresses are inside the same block (the first 128 KB), and what was inside the cache was a line starting from address 1,000. So the cache controller will load the line from address 2,000 and store it on the first line of the memory cache, cleaning the previous contents, in our case the line from address 1,000.

The problem goes on. If the program has a loop that is more than 64 bytes long, there will be a cache miss for the entire duration of the loop.

For example, if the loop goes from address 1,000 to address 1,100, the CPU will have to load all instructions directly from the RAM memory through the duration of the loop. This will happen because the cache will have the contents from addresses 1,000 through 1,063 and when the CPU asks for the contents from address 1,100 it will have to go the RAM memory, and the cache controller will load addresses 1,100 through 1,163. When the CPU asks address 1,000 back it will have to go back to the RAM memory, as the cache doesn’t have the contents from address 1,000 anymore. If this loop is executed 1,000 times, the CPU will have to go to the RAM memory 1,000 times.

That is why direct mapping cache is the least efficient cache configuration and not used anymore – at least on PCs.

##### Fully associative

On __fully associative__ configuration, on the other hand, there is no hard linking between the lines of the memory cache and the RAM memory locations. The cache controller can store any address. Thus the problems described above don’t happen. This configuration is the most efficient one (i.e., the one with the highest hit rate).

On the other hand, the control circuit is far more complex, as it needs to keep track of what memory locations are loaded inside the memory cache. That is why a hybrid solution – called __set associative__ – is the most used one nowadays.

##### n-Way Set Associative Cache

On this configuration the memory cache is divided in several blocks (sets) containing “n” lines each.

So on a 4-way set associative cache the memory cache will have 2,048 blocks containing four lines each (8,192 lines / 4), on a 2-way set associative cache the memory cache will have 4,096 blocks containing 2 lines each and on a 16-way set associative cache the memory cache will have 512 blocks containing 16 lines each. Here we are continuing our example of a 512 KB L2 memory cache divided into 8,192 64-byte lines. Depending on the CPU the number of blocks will be different, of course.

![alt](http://www.hardwaresecrets.com/wp-content/uploads/481_071.gif)

Then the main RAM memory is divided in the same number of blocks available in the memory cache. Keeping the 512 KB 4-way set associative example, the main RAM would be divided into 2,048 blocks, the same number of blocks available inside the memory cache. Each memory block is linked to a set of lines inside the cache, just like in the direct mapped cache. With 1 GB RAM, the memory would be divided into 2,048 blocks with 512 KB each, see Figure 8.

![alt](http://www.hardwaresecrets.com/wp-content/uploads/481_081.gif)

As you see the mapping is very similar to what happens with the direct mapped cache, the difference is that for each memory block there is now more than one line available on the memory cache. Each line can hold the contents from any address inside the mapped block. On a 4-way set associative cache each set on the memory cache can hold up to four lines from the same memory block.

With this approach the problems presented by the direct mapped cache are gone (both the collision problem and the loop problem we describe in the previous page). At the same time, the set associative cache is easier to implement than the full associative cache, since its control logic is simpler. Because of that this is nowadays the most common cache configuration, even though it provides a lower performance compared to the full associative one.

Of course we still have a limited number of available slots inside each memory cache set for each memory block – four on a 4-way configuration. After these four slots are taken, the cache controller will have to free one of them to store the next instruction loaded from the same memory block.

When we increase the number of ways a set associative memory cache has – for example, from 4-way to 8-way configuration –, we have more slots available on each set, but if we keep the same amount of cache memory the size of each memory block is also increased. Continuing our example, moving from 4-way to 8-way would make our 1 GB RAM memory to be divided into 1,024 1 MB blocks. So this move would increase the number of available slots on each set, but now each set would be in charge of a bigger memory block.

There is a lot of academic discussion regarding what is the perfect balance between the number of sets and the memory block size and there is no definitive answer – Intel and AMD use different configurations, as you will see in the next page.

So what happens if we have a bigger memory cache? Keeping the above example, if we increased the L2 memory cache from 512 KB to 1 MB (the only way to do that would be by replacing the CPU), what would happen is that we would have 16,384 64-byte lines in our memory cache, what would give us 4,096 sets with four lines each. Our 1 GB RAM memory would be divided into 4,096 256 KB blocks. So basically what happens is that the size of each memory block is lowered, increasing the chance of the requested data to be inside the memory cache – in other words, increasing the cache size lowers the cache miss rate.

However, increasing the memory cache isn’t something that guarantees increase in performance. Increasing the size of the memory cache assures that more data will be cached, but the question is whether the CPU is using this extra data or not. For example, suppose a single-core CPU with 4 MB L2 cache. If the CPU is using heavily 1 MB but not so heavily the other 3 MB (i.e., the most accessed instructions are taking up 1 MB and on the other 3 MB the CPU cached instructions are not being called so much), chance is that this CPU will have a similar performance of an identical CPU but with 2 MB or even 1 MB L2 cache.










