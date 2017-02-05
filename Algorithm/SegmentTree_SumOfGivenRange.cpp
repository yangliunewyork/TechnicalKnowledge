#include <memory>
#include <vector>
#include <iostream>
#include <cassert>

class SegmentTreeNode;
typedef std::shared_ptr<SegmentTreeNode> SegmentTreeNodePtr;

class SegmentTreeNode {
public:
  SegmentTreeNode(std::size_t start, std::size_t end,int sum)
    : m_start(start), m_end(end), m_sum(sum),m_left(nullptr), m_right(nullptr) {
    
  }
  std::size_t m_start, m_end;
  SegmentTreeNodePtr m_left, m_right;
  int m_sum;
};

SegmentTreeNodePtr BuildSegmentTree(const std::vector<int> & vec, std::size_t start, std::size_t end) {
  if (start > end) {
    return nullptr;
  } else {
    SegmentTreeNodePtr root = std::make_shared<SegmentTreeNode>(start,end,0);
    if (start == end) {
      root->m_sum = vec[start];
    } else {
      int mid = start + (end-start) / 2;
      root->m_left = BuildSegmentTree(vec,start,mid);
      root->m_right = BuildSegmentTree(vec,mid+1,end);
      root->m_sum = root->m_left->m_sum + root->m_right->m_sum;
    }
    return root;
  }
}

void Update(SegmentTreeNodePtr & root, std::size_t pos, int val) {
  if (root->m_start == root->m_end) {
    root->m_sum = val;
  } else {
    std::size_t mid = root->m_start + (root->m_end - root->m_start) / 2;
    if (pos <= mid) {
      Update(root->m_left, pos, val);
    } else {
      Update(root->m_right, pos, val);
    }

    // update internal nodes' sum
    root->m_sum = root->m_left->m_sum + root->m_right->m_sum;
  }
}

int SumRange (SegmentTreeNodePtr & root, std::size_t start, std::size_t end) {
  if (root->m_start == start && root->m_end == end) {
    return root->m_sum;
  } else {
    //  get the interval mid of current node
    std::size_t interval_mid = root->m_start + (root->m_end - root->m_start) / 2;
    
    if (end <= interval_mid) {
      return SumRange(root->m_left, start, end);
    } else if (start > interval_mid) {
      return SumRange(root->m_right, start, end);
    } else {
      return SumRange(root->m_left,start,interval_mid) + SumRange(root->m_right,interval_mid + 1,end);
    }
  }
}

void UnitTest() {
  std::vector<int> vec = {1,3,5,7,9,10};
  SegmentTreeNodePtr root = BuildSegmentTree(vec,0,vec.size());

  assert(SumRange(root,2,3) == 12);
  assert(SumRange(root,2,4) == 21);

  Update(root,3,4);

  assert(SumRange(root,2,3) == 9);
  assert(SumRange(root,2,4) == 18);
}

int main() {
  UnitTest();
  return 0;
}
