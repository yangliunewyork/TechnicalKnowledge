In this chapter, we look at how to construct an inverted index. We call this process __index construction__ or __indexing__ ; the process or machine that performs it the indexer . The design of indexing algorithms is governed by hardware constraints. 

# Hardware basics

When building an information retrieval (IR) system, many decisions are based on the characteristics of the computer hardware on which the system runs.A list of hardware basics that we need in this book to motivate IR system design follows.

* Access to data in memory is much faster than access to data on disk. It takes a few clock cycles (perhaps  $5 \times 10^{-9}$ seconds) to access a byte in memory, but much longer to transfer it from disk (about  $2 \times 10^{-8}$ seconds). Consequently, we want to keep as much data as possible in memory, especially those data that we need to access frequently. We call the technique of keeping frequently used disk data in main memory __caching__ .  
* When doing a disk read or write, it takes a while for the disk head to move to the part of the disk where the data are located. This time is called the seek time and it averages 5 ms for typical disks. No data are being transferred during the seek. To maximize data transfer rates, chunks of data that will be read together should therefore be stored contiguously on disk. For example, it may take as little as 0.2 seconds to transfer 10 megabytes (MB) from disk to memory if it is stored as one chunk, but up to  ```0.2+100
x(5 x 10^-3)=0.7``` seconds if it is stored in 100 noncontiguous chunks because we need to move the disk head up to 100 times.  
* Operating systems generally read and write entire blocks. Thus, reading a single byte from disk can take as much time as reading the entire block. Block sizes of 8, 16, 32, and 64 kilobytes (KB) are common. We call the part of main memory where a block being read or written is stored a buffer .  
* Data transfers from disk to memory are handled by the system bus, not by the processor. This means that the processor is available to process data during disk I/O. We can exploit this fact to speed up data transfers by storing compressed data on disk. Assuming an efficient decompression algorithm, the total time of reading and then decompressing compressed data is usually less than reading uncompressed data.  
* Servers used in IR systems typically have several gigabytes (GB) of main memory, sometimes tens of GB. Available disk space is several orders of magnitude larger.


