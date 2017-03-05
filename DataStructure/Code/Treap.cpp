// http://www.geeksforgeeks.org/treap-a-randomized-binary-search-tree/
// https://threads-iiith.quora.com/Treaps-One-Tree-to-Rule-em-all-Part-1

#include <memory>
#include <iostream>
#include <sstream>



class Treap {

private:
  struct TreapNode;
  typedef std::shared_ptr<TreapNode> TreapNodePtr;
  // A Treap Node
  struct TreapNode {
    int m_key;
    int m_priority;

    TreapNodePtr m_left;
    TreapNodePtr m_right;
  };


public:
  Treap() : m_root(nullptr) {}
  void Insert(int key) {
    m_root = Insert(m_root, key);
  }

  void Delete(int key) {
    Delete(m_root, key);
  }

  TreapNodePtr Search(int key) {
    return Search(m_root, key);
  }

  std::string InorderPrint() {
    std::ostringstream oss;
    InorderPrint(m_root, oss);
    return oss.str();
  }

private:
  TreapNodePtr m_root;

  /* T1, T2 and T3 are subtrees of the tree rooted with y
     (on left side) or x (on right side)
     y                               x
     / \     Right Rotation          /  \
     x   T3   – – – – – – – >        T1   y
     / \       < - - - - - - -            / \
     T1  T2     Left Rotation            T2  T3 */


  // A utility function to right rotate subtree rooted with y
  // See the diagram given above.
  static TreapNodePtr RightRotate(TreapNodePtr & node_ptr) {
    if (!node_ptr || !node_ptr->m_left) return node_ptr;
    TreapNodePtr node_left = node_ptr->m_left;
    TreapNodePtr right_child_of_left = node_left->m_right;

    node_ptr->m_left = right_child_of_left;
    node_left->m_right = node_ptr;

    return node_left;
  }


  // A utility function to left rotate subtree rooted with x
  // See the diagram given above.
  static TreapNodePtr LeftRotate(TreapNodePtr & node_ptr) {
    if (!node_ptr || !node_ptr->m_right) return node_ptr;
    TreapNodePtr node_right = node_ptr->m_right;
    TreapNodePtr left_child_of_right = node_right->m_left;

    node_ptr->m_right = left_child_of_right;
    node_right->m_left = node_ptr;

    return node_right;
  }
  static TreapNodePtr GetNewNode(int key) {
    TreapNodePtr reval = std::make_shared<TreapNode>();
    reval->m_key = key;
    reval->m_priority = rand() % 100;
    reval->m_left = reval->m_right = nullptr;
    return reval;
  }

  static TreapNodePtr Search(TreapNodePtr & root_ptr, int key) {
    if (!root_ptr || root_ptr->m_key == key) return root_ptr;

    if (root_ptr->m_key < key) {
      return Search(root_ptr->m_right, key);
    } else {
      return Search(root_ptr->m_left, key);
    }
  }

  static TreapNodePtr Insert(TreapNodePtr & root_ptr, int key) {
    if (!root_ptr) {
      return GetNewNode(key);
    }

    if (key <= root_ptr->m_key) {
      // Insert in left subtree
      root_ptr->m_left = Insert(root_ptr->m_left, key);

      // Fix Heap property if it is violated
      if (root_ptr->m_left->m_priority > root_ptr->m_priority)
        root_ptr = RightRotate(root_ptr);
    } else {
      // Insert in right subtree
      root_ptr->m_right = Insert(root_ptr->m_right, key);

      // Fix Heap property if it is violated
      if (root_ptr->m_right->m_priority > root_ptr->m_priority)
        root_ptr = LeftRotate(root_ptr);
    }

    return root_ptr;
  }

 TreapNodePtr Delete(TreapNodePtr & root_ptr, int key) {
    if (!root_ptr) return root_ptr;

    if (key < root_ptr->m_key) {
      root_ptr->m_left = Delete(root_ptr->m_left, key);
    } else if (key > root_ptr->m_key) {
      root_ptr->m_right = Delete(root_ptr->m_right, key);
    } else {
      if (!root_ptr->m_left) {
        TreapNodePtr cur_right = root_ptr->m_right;
        root_ptr = cur_right; // make right node as root
      } else if (!root_ptr->m_right) {
        TreapNodePtr cur_left = root_ptr->m_left;
        root_ptr = cur_left; // make left node as root
      } else {
        // If ksy is at root and both left and right are not NULL
        if (root_ptr->m_left->m_priority < root_ptr->m_right->m_priority) {
          root_ptr = LeftRotate(root_ptr);
          root_ptr->m_left = Delete(root_ptr->m_left, key);
        } else {
          root_ptr = RightRotate(root_ptr);
          root_ptr = Delete(root_ptr->m_right, key);
        }
      }
    }
    return root_ptr;
  }

  void InorderPrint(TreapNodePtr & root_ptr, std::ostringstream & oss) {
    if (!root_ptr) return;
    InorderPrint(root_ptr->m_left, oss);
    oss << "["<<root_ptr->m_key<< " : "<<root_ptr->m_priority <<"],";
    InorderPrint(root_ptr->m_right, oss);
  }
};

void UnitTest() {
  Treap treap;
  treap.Insert(50);
  treap.Insert(30);
  treap.Insert(20);
  treap.Insert(40);
  treap.Insert(70);
  treap.Insert(60);
  treap.Insert(80);
  std::cout << treap.InorderPrint() << std::endl;

  std::cout << "Delete 20 " << std::endl;
  treap.Delete(20);
  std::cout << treap.InorderPrint() << std::endl;

  std::cout << "Delete 30 " << std::endl;
  treap.Delete(30);
  std::cout << treap.InorderPrint() << std::endl;


  std::cout << "Find 50 " << std::endl;
  std::cout << (treap.Search(50) ? "Found" : "Not Found") << std::endl;

  std::cout << "Delete 50 " << std::endl;
  treap.Delete(50);
  std::cout << treap.InorderPrint() << std::endl;

}

int main() {
  UnitTest();
  return 0;
}
