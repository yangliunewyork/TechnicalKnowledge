
* https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
* http://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
* https://www.hackerearth.com/practice/notes/binary-indexed-tree-or-fenwick-tree/

Let us consider the following problem to understand Binary Indexed Tree.

We have an array arr[0 . . . n-1]. We should be able to

1. Find the sum of first i elements.
2. Change value of a specified element of the array arr[i] = x where 0 <= i <= n-1.

A simple solution is to run a loop from 0 to i-1 and calculate sum of elements. To update a value, simply do arr[i] = x. The first operation takes O(n) time and second operation takes O(1) time. Another simple solution is to create another array and store sum from start to i at the i’th index in this array. Sum of a given range can now be calculated in O(1) time, but update operation takes O(n) time now. This works well if the number of query operations are large and very few updates.

##### Can we perform both the operations in O(log n) time once given the array? 

One Efficient Solution is to use Segment Tree that does both operations in O(Logn) time.

__Using Binary Indexed Tree, we can do both tasks in O(Logn) time. The advantages of Binary Indexed Tree over Segment are, requires less space and very easy to implement.__

##### Representation

Binary Indexed Tree is represented as an array. Let the array be BITree[]. Each node of Binary Indexed Tree stores sum of some elements of given array. Size of Binary Indexed Tree is equal to n where n is size of input array. In the below code, we have used size as n+1 for ease of implementation.

##### Construction
We construct the Binary Indexed Tree by first initializing all values in BITree[] as 0. Then we call update() operation for all indexes to store actual sums, update is discussed below.

```
getSum(index): Returns sum of arr[0..index]
// Returns sum of arr[0..index] using BITree[0..n].  It assumes that
// BITree[] is constructed for given array arr[0..n-1]
1) Initialize sum as 0 and index as index+1.
2) Do following while index is greater than 0.
...a) Add BITree[index] to sum
...b) Go to parent of BITree[index].  Parent can be obtained by removing
     the last set bit from index, i.e., index = index - (index & (-index))
3) Return sum.
```

![alt](http://www.geeksforgeeks.org/wp-content/uploads/BITSum.png)

The above diagram demonstrates working of getSum(). Following are some important observations.

* Node at index 0 is a dummy node.
* A node at index y is parent of a node at index x, iff y can be obtained by removing last set bit from binary representation of x.
* A child x of a node y stores sum of elements from of y(exclusive y) and of x(inclusive x).

```
update(index, val): Updates BIT for operation arr[index] += val
// Note that arr[] is not changed here.  It changes
// only BI Tree for the already made change in arr[].
1) Initialize index as index+1.
2) Do following while index is smaller than or equal to n.
...a) Add value to BITree[index]
...b) Go to parent of BITree[index].  Parent can be obtained by removing
     the last set bit from index, i.e., index = index + (index & (-index))
```

![alt](http://www.geeksforgeeks.org/wp-content/uploads/BITUpdate12.png)

The update process needs to make sure that all BITree nodes that have arr[i] as part of the section they cover must be updated. We get all such nodes of BITree by repeatedly adding the decimal number corresponding to the last set bit.

##### How does Binary Indexed Tree work?

__The idea is based on the fact that all positive integers can be represented as sum of powers of 2.__ For example 19 can be represented as 16 + 2 + 1. Every node of BI Tree stores sum of n elements where n is a power of 2. For example, in the above first diagram for getSum(), sum of first 12 elements can be obtained by sum of last 4 elements (from 9 to 12) plus sum of 8 elements (from 1 to 8). The number of set bits in binary representation of a number n is O(Logn). Therefore, we traverse at-most O(Logn) nodes in both getSum() and update() operations. Time complexity of construction is O(nLogn) as it calls update() for all n elements.

![alt](https://he-s3.s3.amazonaws.com/media/uploads/68f2369.jpg)

Notice  
```
               {           a[x],                  if x is odd
BIT[x] =                    a[1] + ... + a[x],     if x is power of 2
               }
```

Suppose we are looking for cumulative frequency of index 13 (for the first 13 elements). In binary notation, 13 is equal to 1101. Accordingly, we will calculate c[1101] = tree[1101] + tree[1100] + tree[1000] (more about this later).

Let’s see how to construct this tree and then we will come back to querying the tree for prefix sums. BIT[] is an array of size = 1 + the size of the given array a[] on which we need to perform operations. Initially all values in BIT[] are equal to 0. Then we call update() operation for each element of given array to construct the Binary Indexed Tree. The update() operation is discussed below.

```
void update(int x, int delta)       //add "delta" at index "x"
{
    for(; x <= n; x += x&-x)
          BIT[x] += delta;
}
```

Its okay if you are unable to understand how the above update() function works. Let’s take an example and try to understand it.

Suppose we call update(13, 2).

Here we see from the above figure that indices 13, 14, 16 cover index 13 and thus we need to add 2 to them also.

Initially x is 13, we update BIT[13], ```  BIT[13] += 2;```.

Now isolate the last set bit of x = 13(1101) and add that to x , i.e. x += x&(-x)

Last bit is of x = 13(1101) is 1 which we add to x, then x = 13+1 = 14, we update BIT[14]

``` BIT[14] += 2;```

Now 14 is 1110, isolate last bit and add to 14, x becomes 14+2 = 16(10000), we update BIT[16]

```    BIT[16] += 2;```

In this way, when an update() operation is performed on index x we update all the indices of BIT[] which cover index x and maintain the BIT[].

If we look at the for loop in update() operation, we can see that the loop runs at most the number of bits in index x which is restricted to be less or equal to n (the size of the given array), so we can say that the update operation takes at most __O(log2(n))__ time.

How to query such structure for prefix sums? Let’s look at the query operation.

```
int query(int x)      //returns the sum of first x elements in given array a[]
{
     int sum = 0;
     for(; x > 0; x -= x&-x)
         sum += BIT[x];
     return sum;
}
```

The above function query() returns the sum of first x elements in given array. Let’s see how it works.

Suppose we call query(14), initially sum = 0

x is 14(1110) we add BIT[14] to our sum variable, thus sum = BIT[14] = (a[14] + a[13])

now we isolate the last set bit from x = 14(1110) and subtract it from x

last set bit in 14(1110) is 2(10), thus x = 14 – 2 = 12

we add BIT[12] to our sum variable, thus sum = BIT[14] + BIT[12] = (a[14] + a[13]) + (a[12] + … + a[9])

again we isolate last set bit from x = 12(1100) and subtract it from x

last set bit in 12(1100) is 4(100), thus x = 12 – 4 = 8

we add BIT[8] to our sum variable, thus

sum = BIT[14] + BIT[2] + BIT[8] = (a[14] + a[13]) + (a[12] + … + a[9]) + (a[8] + … + a[1])

once again we isolate last set bit from x = 8(1000) and subtract it from x

last set bit in 8(1000) is 8(1000), thus x = 8 – 8 = 0

since x = 0, the for loop breaks and we return the prefix sum.

Talking about complexity, again we can see that the loop iterates at most the number of bits in x which will be at most n(the size of the given array). Thus the *query operation takes O(log2(n)) time *.

## Code

```cpp
#include <vector>
#include <iostream>
#include <cassert>

class NumArray {
public:
  NumArray(std::vector<int> nums) : m_nums(nums.size(),0), m_tree(nums.size() + 1,0) {
    const std::size_t nums_size(nums.size());
    for (std::size_t i = 0;i < nums_size; ++ i) {
      Update(i,nums[i]);
    }
  }

  void Update(int i, int val) {
    int diff = val - m_nums[i];
    m_nums[i] = val;

    ++ i;
    while (i < m_tree.size()) {
      m_tree[i] += diff;
      int last_set_bit = i & (-i);
      i += last_set_bit;
    }
  }

  int GetSum(int i) {
 
    int sum(0);
    ++ i;
    while (i>0) {
      sum += m_tree[i];
      int last_set_bit = i & (-i);
      i -= last_set_bit;
    }
    return sum;
  }

  int SumRange(int i, int j) {
    return GetSum(j) - GetSum(i-1);
  }
private:
  std::vector<int> m_nums;
  std::vector<int> m_tree; // binary indexed tree

};

void UnitTest() {
  std::vector<int> input = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  NumArray num_array(input);
  assert(num_array.SumRange(3,6) == 12);
  assert(num_array.SumRange(6,10) == 30);
  num_array.Update(3,-1);
  assert(num_array.SumRange(3,6) == 8);
}

int main() {
  UnitTest();
  return 0;
}

```

