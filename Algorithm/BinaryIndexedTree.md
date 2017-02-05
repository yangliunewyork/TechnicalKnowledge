##

http://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/


## Code

~~~
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

~~~

