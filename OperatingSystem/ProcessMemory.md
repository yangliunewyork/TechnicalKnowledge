## Resident set size
In computing, resident set size (RSS) is the portion of memory occupied by a process that is held in main memory (RAM). The rest of the occupied memory exists in the swap space or file system, either because some parts of the occupied memory were paged out, or because some parts of the executable were never loaded.

## Virtual Memory Size
Virtual memory isn't even necessarily memory. For example, if a process memory-maps a large file, the file is actually stored on disk, but it still takes up "address space" in the process.

Address space (ie. virtual memory in the process list) doesn't cost anything; it's not real. What's real is the RSS (RES) column, which is resident memory. That's how much of your actual memory a process is occupying.

But even that isn't the whole answer. If a process calls fork(), it splits into two parts, and both of them initially share all their RSS. So even if RSS was initially 1 GB, the result after forking would be two processes, each with an RSS of 1 GB, but you'd still only be using 1 GB of memory.

```
o: VIRT  --  Virtual Image (kb)
      The  total  amount  of  virtual  memory  used  by the task.  It
      includes all code, data and shared libraries  plus  pages  that
      have been swapped out.

      VIRT = SWAP + RES.
```

Where RES means RESident memory (physical memory used).

Actually that's not correct (anymore). When it says "swap," that also includes files that the program has mapped into its address space, which may or may not actually be consuming real RAM yet. This memory is file-backed but isn't really swap.

VIRT also includes pages that have been allocated but not used for anything yet. Any page in this state is mapped to the kernel Zero Page (brilliant concept--you should look it up) so it shows up in VIRT but doesn't actually consume any memory.
