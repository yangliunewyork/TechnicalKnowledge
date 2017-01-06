#### Isolate the Column

If you don’t isolate the indexed columns in a query, MySQL generally can’t use indexes on columns unless the columns are isolated in the query. “Isolating” the column means it should not be part of an expression or be inside a function in the query.

#### Prefix Indexes and Index Selectivity

Sometimes you need to index very long character columns, which makes your indexes large and slow. One strategy is to simulate a hash index, as we showed earlier in this chapter. But sometimes that isn’t good enough. What can you do? You can often save space and get good performance by indexing the first few characters instead of the whole value. This makes your indexes use less space, but it also makes them less selective. 

Index selectivity is the ratio of the number of distinct indexed values (the cardinality) to the total number of rows in the table (#T), and ranges from 1/#T to 1. A highly selective index is good because it lets MySQL filter out more rows when it looks for matches. A unique index has a selectivity of 1, which is as good as it gets. A prefix of the column is often selective enough to give good performance. If you’re indexing BLOB or TEXT columns, or very long VARCHAR columns, you must define prefix indexes, because MySQL disallows indexing their full length. 

The trick is to choose a prefix that’s long enough to give good selectivity, but short enough to save space. The prefix should be long enough to make the index nearly as useful as it would be if you’d indexed the whole column. In other words, you’d like the prefix’s cardinality to be close to the full column’s cardinality. To determine a good prefix length, find the most frequent values and compare that list to a list of the most frequent prefixes.

#### Clustered Indexes

Clustered indexes* aren’t a separate type of index. Rather, they’re an approach to data storage. The exact details vary between implementations, but InnoDB’s clustered indexes actually store a B-Tree index and the rows together in the same structure.

When a table has a clustered index, its rows are actually stored in the index’s leaf pages. The term “clustered” refers to the fact that rows with adjacent key values are stored close to each other.† You can have only one clustered index per table, because you can’t store the rows in two places at once.Because storage engines are responsible for implementing indexes, not all storage engines support clustered indexes.

#### Covering Indexes 

Indexes are a way to find rows efficiently, but MySQL can also use an index to retrieve a column’s data, so it doesn’t have to read the row at all. After all, the index’s leaf nodes contain the values they index; why read the row when reading the index can give you the data you want? An index that contains (or “covers”) all the data needed to satisfy a query is called a covering index.

Covering indexes can be a very powerful tool and can dramatically improve performance. Consider the benefits of reading only the index instead of the data:
* Index entries are usually much smaller than the full row size, so MySQL can access significantly less data if it reads only the index. This is very important for cached workloads, where much of the response time comes from copying the data. It is also helpful for I/O-bound workloads, because the indexes are smaller than the data and fit in memory better.
* Indexes are sorted by their index values (at least within the page), so I/O-bound range accesses will need to do less I/O compared to fetching each row from a random disk location.
* Most storage engines cache indexes better than data.
* Covering indexes are especially helpful for InnoDB tables, because of InnoDB’s clustered indexes.

#### Using Index Scans for Sorts 

MySQL has two ways to produce ordered results: it can use a filesort, or it can scan an index in order. You can tell when MySQL plans to scan an index by looking for “index” in the type column in EXPLAIN.

Scanning the index itself is fast, because it simply requires moving from one index entry to the next. However, if MySQL isn’t using the index to cover the query, it will have to look up each row it finds in the index. This is basically random I/O, so reading data in index order is usually much slower than a sequential table scan, especially for I/O-bound workloads. MySQL can use the same index for both sorting and finding rows. If possible, it’s a good idea to design your indexes so that they’re useful for both tasks at once.

#### Packed (Prefix-Compressed) Indexes

#### Indexes and Locking

### Summary of Indexing Strategies 
Now that you’ve learned more about indexing, perhaps you’re wondering where to get started with your own tables. The most important thing to do is examine the queries you’re going to run most often, but you should also think about less-frequent operations, such as inserting and updating data. Try to avoid the common mistake of creating indexes without knowing which queries will use them, and consider whether all your indexes together will form an optimal configuration. Sometimes you can just look at your queries, and see which indexes they need, add them, and you’re done. But sometimes you’ll have enough different kinds of queries that you can’t add perfect indexes for them all, and you’ll need to compromise. 

To find the best balance, you should benchmark and profile. The first thing to look at is response time. Consider adding an index for any query that’s taking too long. Then examine the queries that cause the most load, and add indexes to support them. If your system is approaching a memory, CPU, or disk bottleneck, take that into account. For example, if you do a lot of long aggregate queries to generate summaries, your disks might benefit from covering indexes that support GROUP BY queries. Where possible, try to extend existing indexes rather than adding new ones. It is usually more efficient to maintain one multicolumn index than several single-column indexes. If you don’t yet know your query distribution, strive to make your indexes as selective as you can, because highly selective indexes are usually more beneficial.


