__Data structure alignment__ is the way data is arranged and accessed in computer memory. It consists of two separate but related issues: data alignment and data structure padding. When a modern computer reads from or writes to a memory address, it will do this in __word sized chunks__ (e.g. 4 byte chunks on a 32-bit system) or larger. Data alignment means putting the data at a memory address equal to some multiple of the word size, which increases the system's performance due to the way the CPU handles memory. To align the data, it may be necessary to insert some meaningless bytes between the end of the last data structure and the start of the next, which is __data structure padding__.

For example, when the computer's word size is 4 bytes (a byte means 8 bits on most machines, but could be different on some systems), the data to be read should be at a memory address which is some multiple of 4. When this is not the case, e.g. the data starts at address 14 instead of 16, then the computer has to read two or more 4 byte chunks and do some calculation before the requested data has been read, or it may generate an alignment fault. Even though the previous data structure end is at address 13, the next data structure should start at address 16. Two padding bytes are inserted between the two data structures at addresses 14 and 15 to align the next data structure at address 16.

Although data structure alignment is a fundamental issue for all modern computers, many computer languages and computer language implementations handle data alignment automatically.

* __Data alignment__: Data alignment means putting the data in memory at address equal to some multiple of the word size. This increases the performance of system due to the way the CPU handles memory.
* __Data Structure Padding__: Now, to align the data, it may be necessary to insert some extra bytes between the end of the last data structure and the start of the next data structure as the data is placed in memory as multiples of fixed word size. This insertion of extra bytes of memory to align the data is called data structure padding.

Consider the structure as shown below:
```
struct 
{
    char a;
    short int b;
    int c;
    char d;
}
```

Now we may think that the processor will allocate memory to this structure as shown below:

![alt](http://contribute.geeksforgeeks.org/wp-content/uploads/struct.png)

The total memory allocated in this case is 8 bytes. But this never happens as the processor can access memory as fixed word size of 4 bytes. So, the integer variable c can not be allocated memory as shown above. An integer variable requires 4 bytes. The correct way of allocation of memory is shown below for this structure using padding bytes.

![alt](http://contribute.geeksforgeeks.org/wp-content/uploads/struct2.png)

The processor will require a total of 12 bytes for the above structure to maintain the data alignment.




# Definitions

A memory address a, is said to be n-byte aligned when a is a multiple of n bytes (where n is a power of 2). In this context a byte is the smallest unit of memory access, i.e. each memory address specifies a different byte. An n-byte aligned address would have a minimum of log2(n) least-significant zeros when expressed in binary.

The alternate wording b-bit aligned designates a b/8 byte aligned address (ex. 64-bit aligned is 8 bytes aligned).

A memory access is said to be aligned when the datum being accessed is n bytes long and the datum address is n-byte aligned. When a memory access is not aligned, it is said to be misaligned. Note that by definition byte memory accesses are always aligned.

A memory pointer that refers to primitive data that is n bytes long is said to be aligned if it is only allowed to contain addresses that are n-byte aligned, otherwise it is said to be unaligned. A memory pointer that refers to a data aggregate (a data structure or array) is aligned if (and only if) each primitive datum in the aggregate is aligned.

Note that the definitions above assume that each primitive datum is a power of two bytes long. When this is not the case (as with 80-bit floating-point on x86) the context influences the conditions where the datum is considered aligned or not.

Data structures can be stored in memory on the stack with a static size known as __bounded__ or on the heap with a dynamic size known as __unbounded__.

# Problems

A computer accesses memory by a single memory word at a time. As long as the memory word size is at least as large as the largest primitive data type supported by the computer, aligned accesses will always access a single memory word. This may not be true for misaligned data accesses.

If the highest and lowest bytes in a datum are not within the same memory word the computer must split the datum access into multiple memory accesses. This requires a lot of complex circuitry to generate the memory accesses and coordinate them. To handle the case where the memory words are in different memory pages the processor must either verify that both pages are present before executing the instruction or be able to handle a TLB miss or a page fault on any memory access during the instruction execution.

When a single memory word is accessed the operation is atomic, i.e. the whole memory word is read or written at once and other devices must wait until the read or write operation completes before they can access it. This may not be true for unaligned accesses to multiple memory words, e.g. the first word might be read by one device, both words written by another device and then the second word read by the first device so that the value read is neither the original value nor the updated value. Although such failures are rare, they can be very difficult to identify.

# Data structure padding

Although the compiler (or interpreter) normally allocates individual data items on aligned boundaries, data structures often have members with different alignment requirements. To maintain proper alignment the translator normally inserts additional unnamed data members so that each member is properly aligned. In addition the data structure as a whole may be padded with a final unnamed member. This allows each member of an array of structures to be properly aligned.

Padding is only inserted when a structure member is followed by a member with a larger alignment requirement or at the end of the structure. By changing the ordering of members in a structure, it is possible to change the amount of padding required to maintain alignment. For example, if members are sorted by descending alignment requirements a minimal amount of padding is required. The minimal amount of padding required is always less than the largest alignment in the structure. Computing the maximum amount of padding required is more complicated, but is always less than the sum of the alignment requirements for all members minus twice the sum of the alignment requirements for the least aligned half of the structure members.

```cpp
// structure C
typedef struct structc_tag
{
   char        c;
   double      d;
   int         s;
} structc_t;
```
Applying same analysis, structc_t needs sizeof(char) + 7 byte padding + sizeof(double) + sizeof(int) = 1 + 7 + 8 + 4 = 20 bytes. However, the sizeof(structc_t) will be 24 bytes. It is because, along with structure members, structure type variables will also have natural alignment. Let us understand it by an example. Say, we declared an array of structc_t as shown below

```
structc_t structc_array[3];
```

Assume, the base address of structc_array is 0x0000 for easy calculations. If the structc_t occupies 20 (0x14) bytes as we calculated, the second structc_t array element (indexed at 1) will be at 0x0000 + 0x0014 = 0x0014. It is the start address of index 1 element of array. The double member of this structc_t will be allocated on 0x0014 + 0x1 + 0x7 = 0x001C (decimal 28) which is not multiple of 8 and conflicting with the alignment requirements of double. As we mentioned on the top, the alignment requirement of double is 8 bytes.

Inorder to avoid such misalignment, compiler will introduce alignment requirement to every structure. It will be as that of the largest member of the structure. In our case alignment of structa_t is 2, structb_t is 4 and structc_t is 8. If we need nested structures, the size of largest inner structure will be the alignment of immediate larger structure.

In structc_t of the above program, there will be padding of 4 bytes after int member to make the structure size multiple of its alignment. Thus the sizeof (structc_t) is 24 bytes. It guarantees correct alignment even in arrays. You can cross check.

### How to Reduce Padding?

By now, it may be clear that padding is unavoidable. There is a way to minimize padding. The programmer should declare the structure members in their increasing/decreasing order of size. An example is structd_t given in our code, whose size is 16 bytes in lieu of 24 bytes of structc_t.


# Data Alignment

Every data type in C/C++ will have alignment requirement (infact it is mandated by processor architecture, not by language). A processor will have processing word length as that of data bus size. On a 32 bit machine, the processing word size will be 4 bytes.

![alt](http://www.geeksforgeeks.org/wp-content/uploads/MemoryAlignment1.gif)

Historically memory is byte addressable and arranged sequentially. If the memory is arranged as single bank of one byte width, the processor needs to issue 4 memory read cycles to fetch an integer. It is more economical to read all 4 bytes of integer in one memory cycle. To take such advantage, the memory will be arranged as group of 4 banks as shown in the above figure.

The memory addressing still be sequential. If bank 0 occupies an address X, bank 1, bank 2 and bank 3 will be at (X + 1), (X + 2) and (X + 3) addresses. If an integer of 4 bytes is allocated on X address (X is multiple of 4), the processor needs only one memory cycle to read entire integer.

Where as, if the integer is allocated at an address other than multiple of 4, it spans across two rows of the banks as shown in the below figure. Such an integer requires two memory read cycle to fetch the data.

![alt](http://www.geeksforgeeks.org/wp-content/uploads/MemoryAlignment2.gif)

 variable’s data alignment deals with the way the data stored in these banks. For example, the natural alignment of int on 32-bit machine is 4 bytes. When a data type is naturally aligned, the CPU fetches it in minimum read cycles.

Similarly, the natural alignment of short int is 2 bytes. It means, a short int can be stored in bank 0 – bank 1 pair or bank 2 – bank 3 pair. A double requires 8 bytes, and occupies two rows in the memory banks. Any misalignment of double will force more than two read cycles to fetch double data.

__Note that a double variable will be allocated on 8 byte boundary on 32 bit machine and requires two memory read cycles. On a 64 bit machine, based on number of banks, double variable will be allocated on 8 byte boundary and requires only one memory read cycle.__



### Typical alignment of C structs on x86

The following typical alignments are valid for compilers from Microsoft (Visual C++), Borland/CodeGear (C++Builder), Digital Mars (DMC), and GNU (GCC) when compiling for 32-bit x86:

```
A char (one byte) will be 1-byte aligned.
A short (two bytes) will be 2-byte aligned.
An int (four bytes) will be 4-byte aligned.
A long (four bytes) will be 4-byte aligned.
A float (four bytes) will be 4-byte aligned.
A double (eight bytes) will be 8-byte aligned on Windows and 4-byte aligned on Linux (8-byte with -malign-double compile time option).
A long long (eight bytes) will be 4-byte aligned.
```

Data structure members are stored sequentially in memory so that, in the structure below, the member Data1 will always precede Data2; and Data2 will always precede Data3:

```cpp
struct MyData
{
    short Data1;
    short Data2;
    short Data3;
};
```

If the type "short" is stored in two bytes of memory then each member of the data structure depicted above would be 2-byte aligned. Data1 would be at offset 0, Data2 at offset 2, and Data3 at offset 4. The size of this structure would be 6 bytes.

##### Example one
Here is a structure with members of various types, totaling 8 bytes before compilation:
```
struct MixedData
{
    char Data1;
    short Data2;
    int Data3;
    char Data4;
};
```

After compilation the data structure will be supplemented with padding bytes to ensure a proper alignment for each of its members:

```cpp
struct MixedData  /* After compilation in 32-bit x86 machine */
{
    char Data1; /* 1 byte */
    char Padding1[1]; /* 1 byte for the following 'short' to be aligned on a 2 byte boundary
assuming that the address where structure begins is an even number */
    short Data2; /* 2 bytes */
    int Data3;  /* 4 bytes - largest structure member */
    char Data4; /* 1 byte */
    char Padding2[3]; /* 3 bytes to make total size of the structure 12 bytes */
};
```

The compiled size of the structure is now 12 bytes. __It is important to note that the last member is padded with the number of bytes required so that the total size of the structure should be a multiple of the largest alignment of any structure member (alignment(int) in this case, which = 4 on linux-32bit/gcc).__

In this case 3 bytes are added to the last member to pad the structure to the size of a 12 bytes (alignment(int) × 3).

##### Example two
```
struct FinalPad {
  float x;  // 4 bytes
  char n[1]; // 1 byte
};
```

In this example the total size of the structure sizeof(FinalPad) == 8, not 5 (so that the size is a multiple of 4 (alignment of float)).

It is possible to change the alignment of structures to reduce the memory they require (or to conform to an existing format) by reordering structure members or changing the compiler’s alignment (or “packing”) of structure members.

##### Example three

```
struct MixedData  /* after reordering */
{
    char Data1;
    char Data4;   /* reordered */
    short Data2;
    int Data3;
};
```

The compiled size of the structure now matches the pre-compiled size of 8 bytes. Note that Padding1[1] has been replaced (and thus eliminated) by Data4 and Padding2[3] is no longer necessary as the structure is already aligned to the size of a long word.










