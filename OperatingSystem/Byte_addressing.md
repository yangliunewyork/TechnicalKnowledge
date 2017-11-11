__Byte addressing__ refers to hardware architectures which support accessing individual bytes of data rather than only larger units called _words_, which would be __word-addressable__. Such computers are sometimes called __byte machines__ (in contrast to __word machines__).

The basic unit of digital storage is called a bit, storing a single 0 or 1.

Many common architectures can address more than 8 bits of data at a time. For example, the Intel 386SX processor can handle 16-bit (two-byte) data, since data is transferred over a 16-bit bus. However, data in memory may be of various lengths.

A 64-bit architecture machine might still need to access 8-bit data over its 64-bit address line, and have the data returned in the bottom 8 bits of its longer data line.

Byte addressable memory refers to architectures where data can be accessed and addressed in units that are narrower than the bus. An eight bit processor like the Intel 8008 addresses eight bits, but as this is the full width of the bus, this is regarded as word addressable. The 386SX, which addresses memory in 8 bit units but can fetch and store it 16 bits at a time, is termed byte addressable.

Bytes have not always meant 8 bits, in fact, depending on the platform, byte sizes of 1 to 48 bits have been used in the past. Therefore, the term "octet" is used where the context makes byte-length ambiguous.

##### One memory location in a computer stores how much data?

Most commonly, modern systems are what you call "byte-accessible" This means:

* One memory location stores 1 Byte (8 bits).
* The basic storage unit for memory is 1 byte.
* If you need to store 4 bytes, and place the first byte at 0001, the last byte will be at 0004. That's one byte at each of 0001, 0002, 0003, and 0004.

Keep in mind while systems have different CPU WORD sizes (32-bit system has a 32-bit or 4-byte word), memory is usually addressed by byte. The CPU's registers used in arithmetic are 4 bytes, but the "memory" programmers use for data storage is addressed in bytes.

On x86 systems, many memory-accessing instructions require values in memory to be "aligned" to addresses evenly divisible by the world size. e.g. 0x???0, 0x???4, 0x???8, 0x???C. So, storing an int at 0001 won't happen on most systems. Non-numeric data types can usually be found at any address.


##### How many memory addresses can we get with a 32-bit processor and 1gb ram?

Short answer: The number of available addresses is equal to the smaller of those:

* Memory size in bytes
* Greatest unsigned integer that can be saved in CPU's machine word

