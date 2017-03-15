## Basic key-value storage
How would you design a simple key-value storage system in a single machine?

The most straightforward thing is to use a hash table to store key-value pairs, which is how most this kind of systems work nowadays. A hash table allows you to read/write a key-value pair in constant time and it’s extremely easy to use. Most languages have built-in support for this.

However, the downside is also obvious. Using a hash table usually means you need to store everything in memory, which may not be possible when the data set is big. There are two common solutions:

Compress your data. This should be the first thing to think about and often there are a bunch of stuff you can compress. For example, you can store reference instead of the actual data. You can also use float32 rather than float64. In addition, using different data representations like bit array (integer) or vectors can be effective as well.
Storing in a disk. When it’s impossible to fit everything in memory, you may store part of the data into disk. To further optimize this, you can think of the system as a cache system. Frequently visited data is kept in memory and the rest is on a disk.
