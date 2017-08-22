* https://www.elastic.co/blog/lucenes-handling-of-deleted-documents

When a document is deleted or updated (= delete + add), Apache Lucene simply marks a bit in a per-segment bitset to record that the document is deleted. All subsequent searches simply skip any deleted documents.

It is not until segments are merged that the bytes consumed by deleted documents are reclaimed. Likewise, any terms that occur only in deleted documents (ghost terms) are not removed until merge. This approach is necessary because it would otherwise be far too costly to update Lucene's write-once index data structures and aggregate statistics for every document deletion, but it has some implications:

* Deleted documents tie up disk space in the index.
* In-memory per-document data structures, such as norms or field data, will still consume RAM for deleted documents.
* Search throughput is lower, since each search must check the deleted bitset for every potential hit. More on this below.
* Aggregate term statistics, used for query scoring, will still reflect deleted terms and documents. When a merge completes, the term statistics will suddenly jump closer to their true values, changing hit scores. In practice this impact is minor, unless the deleted documents had divergent statistics from the rest of the index.
* A deleted document ties up a document ID from the maximum 2.1 B documents for a single shard. If your shard is riding close to that limit (not recommended!) this could matter.
* Fuzzy queries can have slightly different results, because they may match ghost terms.

