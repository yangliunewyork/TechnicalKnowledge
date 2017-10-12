An SSTable (Sorted-String Table) is a frequently-used storage format at Google that has several advantages .

An SSTable is a sorted list of <key,value> string pairs, where the keys do not have to be unique and any string or protocol buffer ( another nice thing ) can be used for both keys and values. Once written, an SSTable cannot be modified or updated, i.e., an SSTable is immutable. SSTables also support sharding and compression, and are very easy to use as input and output to MapReduce jobs. With serialized protocol buffers, an SSTable can be used to store a huge variety of data structures and types.

