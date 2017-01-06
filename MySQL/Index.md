### Indexing Basics 

Indexes are data structures that help MySQL retrieve data efficiently. They are critical for good performance, but people often forget about them or misunderstand them, so indexing is a leading cause of real-world performance problems.

The easiest way to understand how an index works in MySQL is to think about the index in a book. To find out where a particular topic is discussed in a book, you look in the index, and it tells you the page number(s) where that term appears.

MySQL uses indexes in a similar way. It searches the index’s data structure for a value. When it finds a match, it can find the row that contains the match.In other words, it performs a lookup on the values in the index and returns any rows containing the specified value.

An index contains values from a specified column or columns in a table. If you index more than one column, the column order is very important, because MySQL can only search efficiently on a leftmost prefix of the index. Creating an index on two columns is not the same as creating two separate single-column indexes.

#### Types of Indexes

There are many types of indexes, each designed to perform well for different purposes. Indexes are implemented in the storage engine layer, not the server layer. Thus, they are not standardized: indexing works slightly differently in each engine, and not all engines support all types of indexes. Even when multiple engines support the same index type, they may implement it differently under the hood.

##### B-Tree indexes 

![alt](https://upload.wikimedia.org/wikipedia/en/0/03/Btree_index.PNG)

When people talk about an index without mentioning a type, they’re probably referring to a B-Tree index, which typically uses a B-Tree data structure to store its data.

A B-Tree index speeds up data access because the storage engine doesn’t have to scan the whole table to find the desired data. Instead, it starts at the root node.The slots in the root node hold pointers to child nodes, and the storage engine follows these pointers. It finds the right pointer by looking at the values in the node pages, which define the upper and lower bounds of the values in the child nodes. Eventually, the storage engine either determines that the desired value doesn’t exist or successfully reaches a leaf page.Leaf pages are special, because they have pointers to the indexed data instead of pointers to other pages.The tree’s depth depends on how big the table is. Because B-Trees store the indexed columns in order, they’re useful for searching for ranges of data.Because the tree’s nodes are sorted, they can be used for both lookups (finding values) and ORDER BY queries (finding values in sorted order). In general, if a B-Tree can help you find a row in a particular way, it can help you sort rows by the same criteria.

##### Hash indexes 

A hash index is built on a hash table and is useful only for exact lookups that use every column in the index. For each row, the storage engine computes a hash code of the indexed columns, which is a small value that will probably differ from the hash codes computed for other rows with different key values. It stores the hash codes in the index and stores a pointer to each row in a hash table. 

In MySQL, only the Memory storage engine supports explicit hash indexes. They are the default index type for Memory tables, though Memory tables can have B-Tree indexes too. The Memory engine supports nonunique hash indexes, which is unusual in the database world. If multiple values have the same hash code, the index will store their row pointers in the same hash table entry, using a linked list.

