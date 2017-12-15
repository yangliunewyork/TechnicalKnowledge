* https://www.cs.umb.edu/~poneil/lsmtree.pdf

* http://www.benstopford.com/2015/02/14/log-structured-merge-trees/



In computer science, the log-structured merge-tree (or LSM tree) is a data structure with performance characteristics that make it attractive for providing indexed access to files with high insert volume, such as transactional log data. LSM trees, like other search trees, maintain key-value pairs. LSM trees maintain data in two or more separate structures, each of which is optimized for its respective underlying storage medium; data is synchronized between the two structures efficiently, in batches.

One simple version of the LSM tree is a two-level LSM tree. As described by Patrick O'Neil, a two-level LSM tree comprises two tree-like structures, called C0 and C1. C0 is smaller and entirely resident in memory, whereas C1 is resident on disk. New records are inserted into the memory-resident C0 component. If the insertion causes the C0 component to exceed a certain size threshold, a contiguous segment of entries is removed from C0 and merged into C1 on disk. The performance characteristics of LSM trees stem from the fact that each component is tuned to the characteristics of its underlying storage medium, and that data is efficiently migrated across media in rolling batches, using an algorithm reminiscent of merge sort.

Most LSM trees used in practice employ multiple levels. Level 0 is kept in main memory, and might be represented using a tree. The on-disk data is organized into sorted runs of data. Each run contains data sorted by the index key. A run can be represented on disk as a single file, or alternatively as a collection of files with non-overlapping key ranges. To perform a query on a particular key to get its associated value, one must search in the Level 0 tree and each run.

A particular key may appear in several runs, and what that means for a query depends on the application. Some applications simply want the newest key-value pair with a given key. Some applications must combine the values in some way to get the proper aggregate value to return. For example, in Apache Cassandra, each value represents a row in a database, and different versions of the row may have different sets of columns.

