# Sort 1TB file on machine with 1GB RAM
Keyword: External sorting
External sorting is a class of sorting algorithms that can handle massive amounts of data. External sorting is required when the data being sorted do not fit into the main memory of a computing device (usually RAM) and instead they must reside in the slower external memory (usually a hard drive). External sorting typically uses a hybrid sort-merge strategy. In the sorting phase, chunks of data small enough to fit in main memory are read, sorted, and written out to a temporary file. In the merge phase, the sorted subfiles are combined into a single larger file.
In this example, we are going to use external merge sort algorithm, which sorts chunks that each fit in RAM, then merges the sorted chunks together.
1.Read 1GB of the data in main memory and sort by some conventional method, like quicksort.
2.Write the sorted data to disk.
3.Repeat steps 1 and 2 until all of the data is in sorted 1GB chunks(there are 1TB/1GB=1024 chunks, some manufacture use 1TB=1000GB, we are using 1024 here), which now need to be merged into one single output file.
4.Read the first (0.5GB RAM)/(1024 chunk files) = 0.5MB of each sorted chunk into input buffers in main memory and allocate the remaining 0.5GB for an output buffer. Right now we have 1024 input buffers whose total RAM cost is 0.5GB, and one output buffer whose total RAM cost is 0.5GB.Then we begin merge on the 1024 input buffers, whenever any input buffer empties, fill it with the next 0.5MB with its associated chunk until no more data from that chunk is avaialble, whenever the output buffer fills, write it to the final sorted file and empty it.
Please note that IO R/W is expensive operation, and that's why we want to minimize it. 
