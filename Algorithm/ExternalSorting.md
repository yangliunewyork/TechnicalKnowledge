## What is External Sorting
External sorting is a class of sorting algorithms that can handle massive amounts of data. External sorting is required when the data being sorted do not fit into the main memory of a computing device (usually RAM) and instead they must reside in the slower external memory (usually a hard drive). External sorting typically uses a hybrid sort-merge strategy. In the sorting phase, chunks of data small enough to fit in main memory are read, sorted, and written out to a temporary file. In the merge phase, the sorted subfiles are combined into a single larger file.

### External merge sort
One example of external sorting is the external merge sort algorithm, which sorts chunks that each fit in RAM, then merges the sorted chunks together. For example, for sorting 900 megabytes of data using only 100 megabytes of RAM:

1. Read 100 MB of the data in main memory and sort by some conventional method, like quicksort.
2. Write the sorted data to disk.
3. Repeat steps 1 and 2 until all of the data is in sorted 100 MB chunks (there are 900MB / 100MB = 9 chunks), which now need to be merged into one single output file.
4. Read the first 10 MB (= 100MB / (9 chunks + 1)) of each sorted chunk into input buffers in main memory and allocate the remaining 10 MB for an output buffer. (In practice, it might provide better performance to make the output buffer larger and the input buffers slightly smaller.)
5. Perform a 9-way merge and store the result in the output buffer. Whenever the output buffer fills, write it to the final sorted file and empty it. Whenever any of the 9 input buffers empties, fill it with the next 10 MB of its associated 100 MB sorted chunk until no more data from the chunk is available. This is the key step that makes external merge sort work externally -- because the merge algorithm only makes one pass sequentially through each of the chunks, each chunk does not have to be loaded completely; rather, sequential parts of the chunk can be loaded as needed.

Historically, instead of a sort, sometimes a replacement-selection algorithm was used to perform the initial distribution, to produce on average half as many output chunks of double the length.

### Additional passes
The above example is a two-pass sort: first sort, then merge. Note that there was a single k-way merge, rather than, say, a series of 2-way merge passes as in a typical in-memory merge sort. This is because each merge pass reads and writes every value from and to disk.

However, there is a limitation to single-pass merging. As the number of chunks increases, we divide memory into more buffers, so each buffer is smaller, so we have to make many smaller reads rather than fewer larger ones. Thus, for sorting, say, 50 GB in 100 MB of RAM, using a single merge pass isn't efficient: the disk seeks required to fill the input buffers with data from each of the 500 chunks (we read 100MB / 501 ~ 200KB from each chunk at a time) take up most of the sort time. Using two merge passes solves the problem. Then the sorting process might look like this:

1. Run the initial chunk-sorting pass as before.
2. Run a first merge pass combining 25 chunks at a time, resulting in 20 larger sorted chunks.
3. Run a second merge pass to merge the 20 larger sorted chunks.

Like in-memory sorts, efficient external sorts require O(n log n) time: exponential increases in data size require linear increases in the number of passes. If one makes liberal use of the gigabytes of RAM provided by modern computers, the logarithmic factor grows very slowly: under reasonable assumptions, one could sort at least 500 GB of data on a hard disk using 1 GB of main memory before a third pass became advantageous, and could sort many times that before a fourth pass became useful.[4] Low-seek-time media like SSDs also increase the amount that can be sorted before additional passes help.

RAM size is important here: doubling memory dedicated to sorting halves the number of chunks and the number of reads per chunk, reducing the number of seeks required by about three-quarters. The ratio of RAM to disk storage on servers often makes it convenient to do huge sorts on a cluster of machines[5] rather than on one machine with multiple passes.
