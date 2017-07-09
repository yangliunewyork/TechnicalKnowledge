# Maximum subarray problem

In computer science, the maximum subarray problem is the task of finding the contiguous subarray within a one-dimensional array of numbers which has the largest sum. For example, for the sequence of values −2, 1, −3, 4, −1, 2, 1, −5, 4; the contiguous subarray with the largest sum is 4, −1, 2, 1, with sum 6.

### Kadane's algorithm

Kadane's algorithm begins with a simple inductive question: if we know the maximum subarray sum ending at position i, what is the maximum subarray sum ending at position i+1? The answer turns out to be relatively straightforward: either the maximum subarray sum ending at position i+1 includes the maximum subarray sum ending at position i as a prefix, or it doesn't. Thus, we can compute the maximum subarray sum ending at position  i for all positions i by iterating once over the array. As we go, we simply keep track of the maximum sum we've ever seen. Thus, the problem can be solved with the following code, expressed here in Python:

```
def max_subarray(A):
    max_ending_here = max_so_far = A[0]
    for x in A[1:]:
        max_ending_here = max(x, max_ending_here + x)
        max_so_far = max(max_so_far, max_ending_here)
    return max_so_far
```

The algorithm can also be easily modified to keep track of the starting and ending indices of the maximum subarray (when max_so_far changes) as well as the case where we want to allow zero-length subarrays (with implicit sum 0) if all elements are negative.
Because of the way this algorithm uses optimal substructures (the maximum subarray ending at each position is calculated in a simple way from a related but smaller and overlapping subproblem: the maximum subarray ending at the previous position) this algorithm can be viewed as a simple/trivial example of dynamic programming.

The runtime complexity of Kadane's algorithm is O(n).

