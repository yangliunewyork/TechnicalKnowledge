
## What is Rope ?

Ropes are a scalable string implementation: they are designed for efficient operation that involve the string as a whole. Operations such as assignment, concatenation, and substring take time that is nearly independent of the length of the string. Unlike C strings, ropes are a reasonable representation for very long strings such as edit buffers or mail messages.

Advantages:

* Much faster concatenation and substring operations involving long strings. Inserting a character in the middle of a 10 megabyte rope should take on the order of 10s of microseconds, even if a copy of the original is kept, e.g. as part of an edit history. In contrast, this would take on the order of a second for conventional "flat" string representation. The time required for concatenation can be viewed as constant for most applications. It is perfectly reasonable to use a rope as the representation of a file inside a text editor.
* Potentially much better space performance. Minor modifications of a rope can share memory with the original. Ropes are allocated in small chunks, significantly reducing memory fragmentation problems introduced by large blocks
* Assignment is simply a (possibly reference counted) pointer assignment. Unlike reference-counted copy-on-write implementations, this remains largely true even if one of the copies is subsequently slightly modified. It is very inexpensive to checkpoint old versions of a string, e.g. in an edit history.
* It is possible to view a function producing characters as a rope. Thus a piece of a rope may be a 100MByte file, which is read only when that section of the string is examined. Concatenating a string to the end of such a file does not involve reading the file. (Currently the implementation of this facility is incomplete.)
