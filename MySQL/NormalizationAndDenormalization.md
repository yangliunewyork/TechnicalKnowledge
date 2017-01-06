There are usually many ways to represent any given data, ranging from fully normalized to fully denormalized and anything in between. In a normalized database, each fact is represented once and only once. Conversely, in a denormalized database, information is duplicated, or stored in multiple places.

### Pros and Cons of a Normalized Schema 

People who ask for help with performance issues are frequently advised to normalize their schemas, especially if the workload is write-heavy. This is often good advice. It works well for the following reasons:

* Normalized updates are usually faster than denormalized updates. 
* When the data is well normalized, there’s little or no duplicated data, so there’s less data to change. 
* Normalized tables are usually smaller, so they fit better in memory and perform better. 
* The lack of redundant data means there’s less need for DISTINCT or GROUP BY queries when retrieving lists of values. Consider the preceding example: it’s impossible to get a distinct list of departments from the denormalized schema without DISTINCT or GROUP BY, but if DEPARTMENT is a separate table, it’s a trivial query.

The drawbacks of a normalized schema usually have to do with retrieval. Any nontrivial query on a well-normalized schema will probably require at least one join, and perhaps several. This is not only expensive, but it can make some indexing strategies impossible. For example, normalizing may place columns in different tables that would benefit from belonging to the same index.

### Pros and Cons of a Denormalized Schema

A denormalized schema works well because everything is in the same table, which avoids joins. If you don’t need to join tables, the worst case for most queries—even the ones that don’t use indexes—is a full table scan. This can be much faster than a join when the data doesn’t fit in memory, because it avoids random I/O. A single table can also allow more efficient indexing strategies.

### A Mixture of Normalized and Denormalized

Given that both normalized and denormalized schemas have benefits and drawbacks, how can you choose the best design? The truth is, fully normalized and fully denormalized schemas are like laboratory rats: they usually have little to do with the real world. In the real world, you often need to mix the approaches, possibly using a partially normalized schema, cache tables, and other techniques. The most common way to denormalize data is to duplicate, or cache, selected columns from one table in another table. In MySQL 5.0 and newer, you can use triggers to update the cached values, which makes the implementation easier.
