## Introduction
Simply put, virtual memory is a combination of RAM and disk space that running processes can use.

Swap space is the portion of virtual memory that is on the hard disk, used when RAM is full.

Every program is normally loaded in the RAM. But what if the RAM is completely filled and you want to run another program? Then two techniques come into play Paging and Swapping.
* In Paging, instead of the whole address space only specific pages are copied to or from the secondary storage.
* In Swapping, the whole process's address space is copied from RAM to a Secondary Storage. And when OS wants to continue running that process, then it's address space will be copied back to RAM from Secondary Storage. The space in the secondary storage is called the Swap Space or Swap Memory. In Linux, although still the name Swap is used but Linux also use Paging + Segmentation for Memory Management. Hence, Swap Space in Linux is used similarly like Virtual Memory or Paging File on Windows.
