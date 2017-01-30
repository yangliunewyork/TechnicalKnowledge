
### Short answer:



| Algorithm | Average	Time | Best Time | Worst Time | Space | Stability |
| ------------- |:-------------:| -----:|  -----:|  -----:|  -----:| 
| Merge Sort | O(n*log(n)) | O(n*log(n)) |	O(n*log(n))	| Bottom-up O(1), Top-down O(n)	| Stable |
| Quicksort	| O(n*log(n)) |	O(n*log(n)) |	O(n^2)	| O(log n) taking into account the stack space used for recursion	| Unstable	|

Both are sorting algorithms based on the divide and conquer strategy.
Top-down Merge-sort needs an extra array for merge operations, so its space complexity is O(n), while bottom-up merge-sort can have constant space complexity. Merge-sort has O(n*log(n)) time complexity no matter in best/average/worst scenarioes.
Quick-sort has O(n*log(n)) time complexity in best/average scenario but O(n^2) in worst scenario. Regarding space complexity, the space complexity of quicksort is O(log n), taking into account the stack space used for recursion. Also, quicksort cannot be implemented iteratively, unlike mergesort, where an iterative implementation, sometimes called bottom-up mergesort, is possible.

### Long answer:

Mergesort
The real work of mergesort is done by the merge operation. Given two sorted sub-arrays, together having a total of n elements,  the merge operation uses an auxiliary array of size n to merge them together into a single sorted array in linear time i.e. O(n) in Big Oh notation.

Having this merge operation, mergesort works as follows. Given an array of elements A, it sorts the left and right sub-arrays using mergesort itself, and then merges them together into one single sorted array. The base case is a sub-array of size 1, which is implicitly sorted by definition.

If we analyze the time complexity of mergesort, we will see it is O(n log n) in all cases. That is, the time taken to sort n elements grows proportionally to n log n. Merge sort also needs an extra array of size n for the merge operation. So its space complexity is O(n).

Quicksort
Quicksort is another divide and conquer sorting algorithm, proposed by C. A. R. Hoare. Here, the workhorse is the partition operation. Given an array of n elements, partition takes one element (known as the pivot) and places it in the correct position. That is, the array will not be sorted, but all the elements less than the pivot will be to the left of the pivot, and all the elements greater than the pivot will be to the right. The partition operation can be performed in linear time.

Quicksort then works as follows. First, it performs the partition operation on the input array. Assume the pivot is placed in position p. Now, quicksort sorts the sub-arrays A[0 : p - 1] and A[p + 1 : n - 1], using quicksort itself. Here again, the base case is an array of size 1.

There are various ways of selecting the pivot. The simplest is to just take the left-most element every time as the pivot. But, this leads to a fatal weakness. In this case, if the array is already sorted, the pivot will get placed in the left most position always, and quicksort will be sorting sub-lists of size 0 and n - 1. This leads to a time complexity of O(n2)O(n2), which is no better than bubble sort.
This can be mitigated by choosing a random element as the pivot, or using the median of three elements. In this case, the worst case time of O(n2)O(n2) is extremely unlikely (borderline impossible).

In the best case, when the pivot is always placed in the middle, the time complexity will be O(n log n). Also, if the pivot always gets placed somewhere in the middle 50% (25% - 75%) part of the array, quick sort will take time proportional to O(n log n), even as in the best case.

The biggest advantage of quick sort is that, even though the asymptotic complexities are O(n log n), the constant muliplier (hidden by the Big Oh notation) is much smaller for quicksort, which subsequently is appreciably faster than mergesort in almost all cases.

Regarding space complexity, the space complexity of quicksort is O(log n), taking into account the stack space used for recursion.

Also, quicksort cannot be implemented iteratively, unlike mergesort, where an iterative implementation, sometimes called bottom-up mergesort, is possible.

### Why Quick Sort preferred for Arrays and Merge Sort for Linked Lists?

#### Why is Quick Sort preferred for arrays?
Quick Sort in its general form is an in-place sort (i.e. it doesn’t require any extra storage) whereas merge sort requires O(N) extra storage, N denoting the array size which may be quite expensive. Allocating and de-allocating the extra space used for merge sort increases the running time of the algorithm. Comparing average complexity we find that both type of sorts have O(NlogN) average complexity but the constants differ. For arrays, merge sort loses due to the use of extra O(N) storage space.
Most practical implementations of Quick Sort use randomized version. The randomized version has expected time complexity of O(nLogn). The worst case is possible in randomized version also, but worst case doesn’t occur for a particular pattern (like sorted array) and randomized Quick Sort works well in practice.
Quick Sort is also a cache friendly sorting algorithm as it has good locality of reference when used for arrays.
Quick Sort is also tail recursive, therefore tail call optimizations is done.

#### Why is Merge Sort preferred for Linked Lists?
In case of linked lists the case is different mainly due to difference in memory allocation of arrays and linked lists. Unlike arrays, linked list nodes may not be adjacent in memory. Unlike array, in linked list, we can insert items in the middle in O(1) extra space and O(1) time. Therefore merge operation of merge sort can be implemented without extra space for linked lists.
In arrays, we can do random access as elements are continuous in memory. Let us say we have an integer (4-byte) array A and let the address of A[0] be x then to access A[i], we can directly access the memory at (x + i*4). Unlike arrays, we can not do random access in linked list. Quick Sort requires a lot of this kind of access. In linked list to access i’th index, we have to travel each and every node from the head to i’th node as we don’t have continuous block of memory. Therefore, the overhead increases for quick sort. Merge sort accesses data sequentially and the need of random access is low.


## Most people use QuickSort than MergeSort, why is that?

Its cache performance is higher than other sorting algorithms. This is because of its in-place characteristic.
If Quick sort is implemented well, it will be around 2-3 times faster than merge sort and heap sort. This is mainly because that the operations in the innermost loop are simpler. ( I read this from Algorithm Design Manual Book).
No extra memory.
In practice, many modern implementations of quicksort (in particular libstdc++’s std::sort) are actually introsort, whose theoretical worst-case is O(nlogn), same as merge sort. It achieves this by limiting the recursion depth, and switching to a different algorithm (heapsort) once it exceeds logn.

## why is merge sort preferred over quick sort for sorting linked lists?

Mergesort is a stable sort, unlike quicksort and heapsort, and can be easily adapted to operate on linked lists and very large lists stored on slow-to-access media such as disk storage or network attached storage. Although quicksort can be written to operate on linked lists, it will often suffer from poor pivot choices without random access.

In external sorting it will on disks, outside main memory. It can be because the data is huge and cannot be stored in main memory. While sorting the data will pulled over in chunks from disk to main memory. Later all the sorted data will be merged and stored back to disk, where it can fit. External merge sort can be used here.
