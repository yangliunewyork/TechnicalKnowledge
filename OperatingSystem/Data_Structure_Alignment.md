__Data structure alignment__ is the way data is arranged and accessed in computer memory. It consists of two separate but related issues: data alignment and data structure padding. When a modern computer reads from or writes to a memory address, it will do this in word sized chunks (e.g. 4 byte chunks on a 32-bit system) or larger. Data alignment means putting the data at a memory address equal to some multiple of the word size, which increases the system's performance due to the way the CPU handles memory. To align the data, it may be necessary to insert some meaningless bytes between the end of the last data structure and the start of the next, which is __data structure padding__.

For example, when the computer's word size is 4 bytes (a byte means 8 bits on most machines, but could be different on some systems), the data to be read should be at a memory address which is some multiple of 4. When this is not the case, e.g. the data starts at address 14 instead of 16, then the computer has to read two or more 4 byte chunks and do some calculation before the requested data has been read, or it may generate an alignment fault. Even though the previous data structure end is at address 13, the next data structure should start at address 16. Two padding bytes are inserted between the two data structures at addresses 14 and 15 to align the next data structure at address 16.

Although data structure alignment is a fundamental issue for all modern computers, many computer languages and computer language implementations handle data alignment automatically.

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

### Typical alignment of C structs on x86
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









