It’s said that C is a low-level language. Part of what ismeant by this is that much of the memory management for an application pro- gram is left to the programmer to implement. Although this approach can be quite powerful, it also places a great responsibility on the programmer. It’s also said that C is a relatively small language and an easy one to learn. However, C is only small if you don’t consider a typical implementation of the standard C library, which is huge—and many programmers find C to be an easy language to use only up until they encounter pointers. In general, a program bug can cause one of two things to happen:

* It can cause the program to do something that the programmer doesn’t intend. Such bugs are often due to flaws in logic.
* It can cause the program to “bomb” or “crash.” These bugs are often associated with the mishandling or misuse of pointers.

## 4.1 Background Material: Memory Management

### 4.1.1 Why Does a Program Crash?

In the vernacular of the programming world, a program crashes when an error causes it to cease to execute, abruptly and abnormally. By far the most common cause of a crash is for a program to attempt to access a memory location without having the permission to do so. The hardware will sense this and execute a jump to the operating system (OS). On Unix-family platforms, which are our focus here and in most of this book, the OS will normally announce that the program has caused a __segmentation fault__, commonly referred to as a _seg fault_, and discontinue execution of the program.

### 4.1.2 Program Layout in Memory

![alt](http://static.duartes.org/img/blogPosts/linuxFlexibleAddressSpaceLayout.png)

Here virtual address 0 is at the bottom, and the arrows show the direc- tion of growth of two of the components, the heap and the stack, eating up the free area as they grow. The roles of the various pieces are as follows:

* The __text section__ consists of the machine instructions produced by the compiler from your program’s source code. Each line of C code, for instance, will typically translate into two or three machine instructions, and the collection of all the resulting instructions makes up the text section of the executable. The formal name for this section is ```.text```. This component includes statically linked code, including ```/usr/lib/crt0.o```, system code that does some initialization and then calls your main().

* The __data section__ contains all the program variables that are allocated at compile time—that is, your global variables. Actually, this section consists of various subsections. The first is called .data and consists of your initialized variables, that is, those given in declarations like ```int x = 5;```. There is also a .bss section for uninitialized data, given in declarations like ```int y;```.

* When your program requests additional memory from the operating system at run time—for example, when you call malloc() in C, or invoke the new construct in C++—the requested memory is allocated in an area called the __heap__. If you run out of heap space, a call to brk() can be used to expand the heap (which is precisely what malloc() and friends do).

* The __stack section__ is space for the data for function calls—including arguments, local variables, and return addresses—are stored on the stack. The stack grows each time a func- tion call is made and shrinks each time a function returns to its caller.

* Your program’s dynamically linked code is not shown in the picture above due to the platform dependence of its location, but it is somewhere in there.  

### 4.1.3 The Notion of Pages

The __virtual address space__  conceptually extends from 0 to 2 ^ w−1, where w is the word size of your machine in bits. Of course, your program will typically use only a tiny fraction of that space, and the OS may reserve part of the space for its own work. But your code, through pointers, could generate an address anywhere in that range. Often such addresses will be incorrect be due to “entomological conditions”—that is, because of bugs in your program!

This virtual address space is viewed as organized into chunks called __pages__. On Pentium hardware, the default page size is 4,096 bytes. Physical memory (both RAM and ROM) is also viewed as divided into pages. When a program is loaded into memory for execution, the OS arranges for some of the pages of the program to be stored in pages of physical memory. These pages are said to be __resident__, and the rest are stored on disk.

At various times during execution, some program page that is not currently resident will be needed. When this occurs, it will be sensed by the hardware, which transfers control to the OS. The latter brings the required page into memory, possibly replacing another program page that is currently resident (if there are no free pages of memory available), and then returns control to our program. The evicted program page, if any, becomes nonresident and will be stored on disk.

To manage all of this, the OS maintains a __page table__ for each process. (The Pentium’s page tables have a hierarchical structure, but here we assume just one level for simplicity, and most of this discussion will not be Pentium-specific.) Each of the process’s virtual pages has an entry in the table, which includes the following information:

* The current physical location of this page in memory or on disk. In the latter case, the entry will indicate that the page is nonresident and may consist of a pointer to a list which ultimately leads to a physical location on disk. It may show, for instance, that virtual page 12 of the program is resident and is located in physical page 200 of memory.  

* Permissions - read, write, execute - or this page.  

Note that the OS will not allocate partial pages to a program. For exam- ple, if the program to be run has a total size of about 10,000 bytes, it would occupy three pages of memory if fully loaded. It would not merely occupy about 2.5 pages, as pages are the smallest unit of memory manipulated by the VM system. This is an important point to understand when debugging, because it implies that some erroneous memory accesses by the program will not trigger seg faults, as you will see below. In other words, during your de- bugging session, you cannot say something like, “This line of source code must be okay, since it didn’t cause a seg fault.”

### 4.1.4 Details on the Role of the Page Table

Conceptually speaking, each page of the virtual address space of the pro- cess has an entry in the page table (in practice, various tricks can be used to compress the table). This page table entry stores various pieces of informa- tion related to the page. The data of interest in relation to seg faults are the access permissions for the page, which are similar to file access permissions: read, write, and execute. For example, the page table entry for page 3 will indicate whether your process has the right to read data from that page, the right to write data to it, and the right to execute instructions on it (if the page contains machine code). As the program executes, it will continually access its various sections, described above, which causes the page table to be consulted by the hard- ware as follows:

* Each time the program uses one of its global variables, read/write access to the data section is required.  
* Each time the program accesses a local variable, the program accesses the stack, requiring read/write access to the stack section.  
* Each time the program enters or leaves a function, it makes one or more accesses to the stack, requiring read/write access to the stack section.  
* Each time the program accesses storage that had been created by a call to malloc() or new, a heap access occurs, again requiring read/write access.  
* Each machine instruction that the program executes will be fetched from the text section (or from the area for dynamically linked code), thus requiring read and execute permission.  

During the execution of the program, the addresses it generates will be virtual. When the program attempts to access memory at a certain virtual address, say y, the hardware will convert that to a virtual page number v, which equals y divided by 4,096 (where the division uses integer arithmetic, discarding the remainder). The hardware will then check entry v in the page table to see whether the permissions for the page match the operation to be performed. If they do match, the hardware will get the desired location’s actual physical page number from this table entry and then carry out the requested memory operation. But if the table entry shows that the requested operation does not have the proper permission, the hardware will execute an internal interrupt. This will cause a jump to the OS’s error-handling routine. The OS will normally then announce a memory access violation and discontinue execution of the program (i.e., remove it from the process table and from memory).

### 4.1.5 A Slight Memory-Access Bug Might Not Cause a Seg Fault


