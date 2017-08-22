* https://www.elastic.co/guide/en/elasticsearch/guide/current/inside-a-shard.html

# Making text searchable

The first challenge that had to be solved was how to make text searchable. Traditional databases store a single value per field, but this is insufficient for full-text search. Every word in a text field needs to be searchable, which means that the database needs to be able to index multiple values—words, in this case—in a single field.

The data structure that best supports the multiple-values-per-field requirement is the __inverted index__. The inverted index contains a sorted list of all of the unique values, or terms, that occur in any document and, for each term, a list of all the documents that contain it.

```
Term  | Doc 1 | Doc 2 | Doc 3 | ...
------------------------------------
brown |   X   |       |  X    | ...
fox   |   X   |   X   |  X    | ...
quick |   X   |   X   |       | ...
the   |   X   |       |  X    | ...
```

> When discussing inverted indices, we talk about indexing documents because, historically, an inverted index was used to index whole unstructured text documents. A document in Elasticsearch is a structured JSON document with fields and values. In reality, every indexed field in a JSON document has its own inverted index.


The inverted index may hold a lot more information than the list of documents that contain a particular term. It may store a count of the number of documents that contain each term, the number of times a term appears in a particular document, the order of terms in each document, the length of each document, the average length of all documents, and more. These statistics allow Elasticsearch to determine which terms are more important than others, and which documents are more important than others, as described in What Is Relevance?.

The important thing to realize is that the inverted index needs to know about all documents in the collection in order for it to function as intended.

In the early days of full-text search, one big inverted index was built for the entire document collection and written to disk. As soon as the new index was ready, it replaced the old index, and recent changes became searchable.

#### Immutabilityedit
The inverted index that is written to disk is immutable: it doesn’t change. Ever. This immutability has important benefits:

* There is no need for locking. If you never have to update the index, you never have to worry about multiple processes trying to make changes at the same time.
* Once the index has been read into the kernel’s filesystem cache, it stays there, because it never changes. As long as there is enough space in the filesystem cache, most reads will come from memory instead of having to hit disk. This provides a big performance boost.
* Any other caches (like the filter cache) remain valid for the life of the index. They don’t need to be rebuilt every time the data changes, because the data doesn’t change.
* Writing a single large inverted index allows the data to be compressed, reducing costly disk I/O and the amount of RAM needed to cache the index.

Of course, an immutable index has its downsides too, primarily the fact that it is immutable! You can’t change it. If you want to make new documents searchable, you have to rebuild the entire index. This places a significant limitation either on the amount of data that an index can contain, or the frequency with which the index can be updated.

# Dynamicall updatable indices

> To add to the confusion, a Lucene index is what we call a shard in Elasticsearch, while an index in Elasticsearch is a collection of shards. When Elasticsearch searches an index, it sends the query out to a copy of every shard (Lucene index) that belongs to the index, and then reduces the per-shards results to a global result set.

The next problem that needed to be solved was how to make an inverted index updatable without losing the benefits of immutability? The answer turned out to be: use more than one index.

Instead of rewriting the whole inverted index, add new supplementary indices to reflect more-recent changes. Each inverted index can be queried in turn—starting with the oldest—and the results combined.

Lucene, the Java libraries on which Elasticsearch is based, introduced the concept of per-segment search. A segment is an inverted index in its own right, but now the word index in Lucene came to mean a collection of segments plus a commit point—a file that lists all known segments. New documents are first added to an in-memory indexing buffer, before being written to an on-disk segment.

![alt](https://www.elastic.co/guide/en/elasticsearch/guide/current/images/elas_1101.png)

A per-segment search works as follows:

![alt](https://www.elastic.co/guide/en/elasticsearch/guide/current/images/elas_1102.png)

1. New documents are collected in an in-memory indexing buffer. See Figure 17, “A Lucene index with new documents in the in-memory buffer, ready to commit”.
2. Every so often, the buffer is commited:
  * A new segment—a supplementary inverted index—is written to disk.
  * A new commit point is written to disk, which includes the name of the new segment.
  * The disk is fsync’ed—all writes waiting in the filesystem cache are flushed to disk, to ensure that they have been physically written.
3. The new segment is opened, making the documents it contains visible to search.
4. The in-memory buffer is cleared, and is ready to accept new documents.

![alt](https://www.elastic.co/guide/en/elasticsearch/guide/current/images/elas_1103.png)

When a query is issued, all known segments are queried in turn. Term statistics are aggregated across all segments to ensure that the relevance of each term and each document is calculated accurately. In this way, new documents can be added to the index relatively cheaply.

##### Deletes and Updates
Segments are immutable, so documents cannot be removed from older segments, nor can older segments be updated to reflect a newer version of a document. Instead, every commit point includes a .del file that lists which documents in which segments have been deleted.

When a document is “deleted,” it is actually just marked as deleted in the .del file. A document that has been marked as deleted can still match a query, but it is removed from the results list before the final query results are returned.

Document updates work in a similar way: when a document is updated, the old version of the document is marked as deleted, and the new version of the document is indexed in a new segment. Perhaps both versions of the document will match a query, but the older deleted version is removed before the query results are returned.

# Near Real-Time Search

With the development of per-segment search, the delay between indexing a document and making it visible to search dropped dramatically. New documents could be made searchable within minutes, but that still isn’t fast enough.

The bottleneck is the disk. Commiting a new segment to disk requires an ```fsync``` to ensure that the segment is physically written to disk and that data will not be lost if there is a power failure. But an fsync is costly; it cannot be performed every time a document is indexed without a big performance hit.

What was needed was a more lightweight way to make new documents visible to search, which meant removing fsync from the equation.

Sitting between Elasticsearch and the disk is the filesystem cache. As before, documents in the in-memory indexing buffer (Figure 19, “A Lucene index with new documents in the in-memory buffer”) are written to a new segment (Figure 20, “The buffer contents have been written to a segment, which is searchable, but is not yet commited”). But the new segment is written to the filesystem cache first—which is cheap—and only later is it flushed to disk—which is expensive. But once a file is in the cache, it can be opened and read, just like any other file.

Lucene allows new segments to be written and opened—making the documents they contain visible to search—without performing a full commit. This is a much lighter process than a commit, and can be done frequently without ruining performance.

# Making Changes Persistentedit

Without an fsync to flush data in the filesystem cache to disk, we cannot be sure that the data will still be there after a power failure, or even after exiting the application normally. For Elasticsearch to be reliable, it needs to ensure that changes are persisted to disk.

In Dynamically Updatable Indices, we said that a full commit flushes segments to disk and writes a commit point, which lists all known segments. Elasticsearch uses this commit point during startup or when reopening an index to decide which segments belong to the current shard.

While we refresh once every second to achieve near real-time search, we still need to do full commits regularly to make sure that we can recover from failure. But what about the document changes that happen between commits? We don’t want to lose those either.

Elasticsearch added a translog, or transaction log, which records every operation in Elasticsearch as it happens. With the translog, the process now looks like this:

1. When a document is indexed, it is added to the in-memory buffer and appended to the translog, as shown in Figure 21, “New documents are added to the in-memory buffer and appended to the transaction log”.

![alt](https://www.elastic.co/guide/en/elasticsearch/guide/current/images/elas_1106.png)

2. The refresh leaves the shard in the state depicted in Figure 22, “After a refresh, the buffer is cleared but the transaction log is not”. Once every second, the shard is refreshed:
  * The docs in the in-memory buffer are written to a new segment, without an fsync.
  * The segment is opened to make it visible to search.
  * The in-memory buffer is cleared.

![alt](https://www.elastic.co/guide/en/elasticsearch/guide/current/images/elas_1107.png)

3. This process continues with more documents being added to the in-memory buffer and appended to the transaction log (see Figure 23, “The transaction log keeps accumulating documents”).

![alt](https://www.elastic.co/guide/en/elasticsearch/guide/current/images/elas_1108.png)

4. Every so often—such as when the translog is getting too big—the index is flushed; a new translog is created, and a full commit is performed (see Figure 24, “After a flush, the segments are fully commited and the transaction log is cleared”):
  * Any docs in the in-memory buffer are written to a new segment.
  * The buffer is cleared.
  * A commit point is written to disk.
  * The filesystem cache is flushed with an fsync.
  * The old translog is deleted.

The translog provides a persistent record of all operations that have not yet been flushed to disk. When starting up, Elasticsearch will use the last commit point to recover known segments from disk, and will then replay all operations in the translog to add the changes that happened after the last commit.

The translog is also used to provide real-time CRUD. When you try to retrieve, update, or delete a document by ID, it first checks the translog for any recent changes before trying to retrieve the document from the relevant segment. This means that it always has access to the latest known version of the document, in real-time.

![alt](https://www.elastic.co/guide/en/elasticsearch/guide/current/images/elas_1109.png)


### How Safe Is the Translog?

The purpose of the translog is to ensure that operations are not lost. This begs the question: how safe is the translog?

Writes to a file will not survive a reboot until the file has been fsync'ed to disk. By default, the translog is fsync'ed every 5 seconds and after a write request completes (e.g. index, delete, update, bulk). This process occurs on both the primary and replica shards. Ultimately, that means your client won’t receive a 200 OK response until the entire request has been fsync'ed in the translog of the primary and all replicas.

Executing an fsync after every request does come with some performance cost, although in practice it is relatively small (especially for bulk ingestion, which amortizes the cost over many documents in the single request).

But for some high-volume clusters where losing a few seconds of data is not critical, it can be advantageous to fsync asynchronously. E.g. writes are buffered in memory and fsync'ed together every 5s.

This behavior can be enabled by setting the durability parameter to async:

```
PUT /my_index/_settings
{
    "index.translog.durability": "async",
    "index.translog.sync_interval": "5s"
}
```

This setting can be configured per-index and is dynamically updatable. If you decide to enable async translog behavior, you are guaranteed to lose sync_interval's worth of data if a crash happens. Please be aware of this characteristic before deciding!

If you are unsure the ramifications of this action, it is best to use the default ("index.translog.durability": "request") to avoid data-loss.

# Segment Merging
With the automatic refresh process creating a new segment every second, it doesn’t take long for the number of segments to explode. Having too many segments is a problem. Each segment consumes file handles, memory, and CPU cycles. More important, every search request has to check every segment in turn; the more segments there are, the slower the search will be.

Elasticsearch solves this problem by merging segments in the background. Small segments are merged into bigger segments, which, in turn, are merged into even bigger segments.

This is the moment when those old deleted documents are purged from the filesystem. Deleted documents (or old versions of updated documents) are not copied over to the new bigger segment.

1. There is nothing you need to do to enable merging. It happens automatically while you are indexing and searching. The process works like as depicted in Figure 25, “Two commited segments and one uncommited segment in the process of being merged into a bigger segment”:

2. While indexing, the refresh process creates new segments and opens them for search.
The merge process selects a few segments of similar size and merges them into a new bigger segment in the background. This does not interrupt indexing and searching.

![alt](https://www.elastic.co/guide/en/elasticsearch/guide/current/images/elas_1110.png)

3. Figure 26, “Once merging has finished, the old segments are deleted” illustrates activity as the merge completes:

![alt](https://www.elastic.co/guide/en/elasticsearch/guide/current/images/elas_1111.png)

* The new segment is flushed to disk.
* A new commit point is written that includes the new segment and excludes the old, smaller segments.
* The new segment is opened for search.
* The old segments are deleted.

The merging of big segments can use a lot of I/O and CPU, which can hurt search performance if left unchecked. By default, Elasticsearch throttles the merge process so that search still has enough resources available to perform well.







