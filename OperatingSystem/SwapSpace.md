https://askubuntu.com/questions/157793/why-is-swap-being-used-even-though-i-have-plenty-of-free-ram?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa

## Introduction

Simply put, virtual memory is a combination of RAM and disk space that running processes can use.

Swap space is the portion of virtual memory that is on the hard disk, used when RAM is full.

Every program is normally loaded in the RAM. But what if the RAM is completely filled and you want to run another program? Then two techniques come into play Paging and Swapping.
* In Paging, instead of the whole address space only specific pages are copied to or from the secondary storage.
* In Swapping, the whole process's address space is copied from RAM to a Secondary Storage. And when OS wants to continue running that process, then it's address space will be copied back to RAM from Secondary Storage. The space in the secondary storage is called the Swap Space or Swap Memory. In Linux, although still the name Swap is used but Linux also use Paging + Segmentation for Memory Management. Hence, Swap Space in Linux is used similarly like Virtual Memory or Paging File on Windows.


## What is Swap Space?

Swap space in Linux is used when the amount of physical memory (RAM) is full. If the system needs more memory resources and the RAM is full, inactive pages in memory are moved to the swap space. While swap space can help machines with a small amount of RAM, it should not be considered a replacement for more RAM. Swap space is located on hard drives, which have a slower access time than physical memory.

Swap space can be a dedicated swap partition (recommended), a swap file, or a combination of swap partitions and swap files.

In general, swap should equal 2x physical RAM for up to 2 GB of physical RAM, and then an additional 1x physical RAM for any amount above 2 GB, but never less than 32 MB.

#### Why use swap when there is more than enough free space in RAM?

It is normal for Linux systems to use some swap even if there is still RAM free. The Linux kernel will move to swap memory pages that are very seldom used (e.g., the getty instances when you only use X11, and some other inactive daemon).

Swap space usage becomes an issue only when there is not enough RAM available, and the kernel is forced to continuously move memory pages to swap and back to RAM, just to keep applications running. In this case, system monitor applications would show a lot of disk I/O activity.

#### What is the right swap space size?

https://askubuntu.com/questions/49109/the-swap-needs-to-be-the-double-of-the-amount-of-ram?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa

Here's a very good recommendation from RedHat: [Recommended System Swap Space](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/installation_guide/sect-disk-partitioning-setup-x86#sect-recommended-partitioning-scheme-x86)

An excerpt from the same link:

In years past, the recommended amount of swap space increased linearly with the amount of RAM in the system. But because the amount of memory in modern systems has increased into the hundreds of gigabytes, __it is now recognized that the amount of swap space that a system needs is a function of the memory workload running on that system. However, given that swap space is usually designated at install time, and that it can be difficult to determine beforehand the memory workload of a system,__ we recommend determining system swap using the following table.

Current table (as of December 2017):

```
Amount of RAM in the system   Recommended swap space         Recommended swap space 
                                                             if allowing for hibernation
---------------------------   ----------------------------   ---------------------------
2GB of RAM or less            2 times the amount of RAM      3 times the amount of RAM
2GB to 8GB of RAM             Equal to the amount of RAM     2 times the amount of RAM
8GB to 64GB of RAM            At least 4 GB                  1.5 times the amount of RAM
64GB of RAM or more           At least 4 GB                  Hibernation not recommended
```

Original table:

```
Amount of RAM in the System     Recommended Amount of Swap Space
4GB of RAM or less              a minimum of 2GB of swap space
4GB to 16GB of RAM              a minimum of 4GB of swap space
16GB to 64GB of RAM             a minimum of 8GB of swap space
64GB to 256GB of RAM            a minimum of 16GB of swap space
256GB to 512GB of RAM           a minimum of 32GB of swap space 
```
