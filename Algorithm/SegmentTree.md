## Reference

https://kartikkukreja.wordpress.com/2014/11/09/a-simple-approach-to-segment-trees/  
http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/  
http://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/  



# Problem : Sum of given range

Let us consider the following problem to understand Segment Trees.

We have an array arr[0 . . . n-1]. We should be able to:

```
1. Find the sum of elements from index l to r where 0 <= l <= r <= n-1
2. Change value of a specified element of the array to a new value x. 
  We need to do arr[i] = x where 0 <= i <= n-1.
```

A simple solution is to run a loop from l to r and calculate sum of elements in given range. To update a value, simply do arr[i] = x. The first operation takes O(n) time and second operation takes O(1) time.

Another solution is to create another array and store sum from start to i at the ith index in this array. Sum of a given range can now be calculated in O(1) time, but update operation takes O(n) time now. This works well if the number of query operations are large and very few updates.

What if the number of query and updates are equal? Can we perform both the operations in O(log n) time once given the array? We can use a Segment Tree to do both operations in O(Logn) time.

Representation of Segment trees :
1. Leaf Nodes are the elements of the input array.  
2. Each internal node represents some merging of the leaf nodes. The merging may be different for different problems. For this problem, merging is sum of leaves under a node.  

![alt](http://www.geeksforgeeks.org/wp-content/uploads/segment-tree1.png)


#### Construction of Segment Tree from given array

We start with a segment arr[0 . . . n-1]. and every time we divide the current segment into two halves(if it has not yet become a segment of length 1), and then call the same procedure on both halves, and for each such segment we store the sum in corresponding node.

All levels of the constructed segment tree will be completely filled except the last level. Also, the tree will be a Full Binary Tree because we always divide segments in two halves at every level. Since the constructed tree is always full binary tree with n leaves, there will be n-1 internal nodes. So total number of nodes will be ```2*n – 1```.

#### Query for Sum of given range

Once the tree is constructed, how to get the sum using the constructed segment tree. Following is algorithm to get the sum of elements.

```
int getSum(node, l, r) 
{
   if range of node is within l and r
        return value in node
   else if range of node is completely outside l and r
        return 0
   else
    return getSum(node's left child, l, r) + 
           getSum(node's right child, l, r)
}
```

#### Update a value

Like tree construction and query operations, update can also be done recursively. We are given an index which needs to updated. Let _diff_ be the value to be added. We start from root of the segment tree, and add _diff_ to all nodes which have given index in their range. If a node doesn’t have given index in its range, we don’t make any changes to that node.


#### Time Complexity

Time Complexity for tree construction is O(n). There are total 2n-1 nodes, and value of every node is calculated only once in tree construction.

Time complexity to query is O(Logn). To query a sum, we process at most four nodes at every level and number of levels is O(Logn).

The time complexity of update is also O(Logn). To update a leaf value, we process one node at every level and number of levels is O(Logn).


```cpp
class NumArray {
public:
  NumArray(vector<int> &nums) {
    m_root = BuildSegmentTree(nums,0,nums.size()-1);
  }

  void update(int i, int val) {
    Update(m_root,i,val);
  }

  int sumRange(int i, int j) {
    return SumRange(m_root,i,j);
  }
private:
  class SegmentTreeNode {
  public:
    SegmentTreeNode(int start, int end)
      : m_start(start),m_end(end),m_left(nullptr),m_right(nullptr),m_sum(0) {
    }
    int m_start, m_end;
    SegmentTreeNode *m_left, *m_right;
    int m_sum;
  };
  SegmentTreeNode* BuildSegmentTree(const vector<int> & input,int start, int end) {
    if (start>end) {
      return nullptr;
    } else {
      SegmentTreeNode* root = new SegmentTreeNode(start,end);
      if (start==end) {
        root->m_sum = input[start];
      } else {
        int mid = start + (end-start) / 2;
        root->m_left = BuildSegmentTree(input,start,mid);
        root->m_right = BuildSegmentTree(input,mid+1,end);
        root->m_sum = root->m_left->m_sum + root->m_right->m_sum;
      }
      return root;
    }

  }
  int SumRange(SegmentTreeNode* root, int start, int end) {
    if (root->m_start==start && root->m_end==end) {
      return root->m_sum;
    } else {
      int mid = root->m_start + (root->m_end-root->m_start) / 2;
      if (end<=mid) {
        return SumRange(root->m_left,start,end);
      } else if (start>=mid+1) {
        return SumRange(root->m_right,start,end);
      } else {
        return SumRange(root->m_left,start,mid) + SumRange(root->m_right,mid+1,end);
      }
    }
  }
  void Update(SegmentTreeNode* root,int pos,int val) {
    if (root->m_start==root->m_end) {
      root->m_sum = val;
    } else {
      int mid = root->m_start + (root->m_end-root->m_start) / 2;
      if (pos<=mid) {
        Update(root->m_left,pos,val);
      } else {
        Update(root->m_right,pos,val);
      }
      root->m_sum = root->m_left->m_sum + root->m_right->m_sum;
    }
  }
  SegmentTreeNode* m_root;
};
```
