https://kukuruku.co/post/ropes-fast-strings/


## What is Rope ?

Ropes are a scalable string implementation: they are designed for efficient operation that involve the string as a whole. Operations such as assignment, concatenation, and substring take time that is nearly independent of the length of the string. Unlike C strings, ropes are a reasonable representation for very long strings such as edit buffers or mail messages.

Advantages:

* Much faster concatenation and substring operations involving long strings. Inserting a character in the middle of a 10 megabyte rope should take on the order of 10s of microseconds, even if a copy of the original is kept, e.g. as part of an edit history. In contrast, this would take on the order of a second for conventional "flat" string representation. The time required for concatenation can be viewed as constant for most applications. It is perfectly reasonable to use a rope as the representation of a file inside a text editor.
* Potentially much better space performance. Minor modifications of a rope can share memory with the original. Ropes are allocated in small chunks, significantly reducing memory fragmentation problems introduced by large blocks
* Assignment is simply a (possibly reference counted) pointer assignment. Unlike reference-counted copy-on-write implementations, this remains largely true even if one of the copies is subsequently slightly modified. It is very inexpensive to checkpoint old versions of a string, e.g. in an edit history.
* It is possible to view a function producing characters as a rope. Thus a piece of a rope may be a 100MByte file, which is read only when that section of the string is examined. Concatenating a string to the end of such a file does not involve reading the file. (Currently the implementation of this facility is incomplete.)


# Text Editor and Rope


Design a text editor which should support

* insert(p)  
* delete(p1, p2)  
* highlight(p1, p2)  
* redo/undo  
* save/load update  
* search  


text editor需要insert，remove，highlight，需要想办法去index每次插入的object，原po说的interval tree应该就是index的方式吧。

关键点在于text打算怎么存

store highlight?

他要求三天后再load这个text,需要可以undo三天前的操作. save的时候 保存成json/xml类型之类的 把之前的操作也一起存下来

# Knowledge

# Rope

In computer programming, a rope, or cord, is a data structure composed of smaller strings that is used to efficiently store and manipulate a very long string. For example, a text editing program may use a rope to represent the text being edited, so that operations such as insertion, deletion, and random access can be done efficiently.

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/8/8a/Vector_Rope_example.svg/427px-Vector_Rope_example.svg.png)

### Description

A rope is a binary tree where __each leaf node contains a short string__. _Each node has a weight value equal to the length of its string plus the sum of all leaf nodes' weight in its left subtree, namely the weight of a node is the total string length in its left subtree for a non-leaf node, or the string length of itself for a leaf node. Thus a node with two children divides the whole string into two parts: the left subtree stores the first part of the string. The right subtree stores the second part and its weight is the sum of the left child's weight and the length of its contained string._

The binary tree can be seen as several levels of nodes. The bottom level contains all the nodes that contain a string. Higher levels have fewer and fewer nodes. The top level consists of a single "root" node. The rope is built by putting the nodes with short strings in the bottom level, then attaching a random half of the nodes to parent nodes in the next level.

### Operations

In the following definitions, N is the length of the rope.

##### Index

* Index(i) : return the character at position i. Time complexity O(log N).

```
function Index(RopeNode node, integer i)
     if node.weight <= i then
         return index(node.right, i - node.weight)
     else
         if exists(node.left) then
             return index(node.left, i)
         else
             return node.string[i]
         end
     end
 end
 ```

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/2/20/Vector_Rope_index.svg/452px-Vector_Rope_index.svg.png)

##### Concat

* Concat(S1, S2) : concatenate two ropes, S1 and S2, into a single rope. Time complexity: O(1) (or  O(log N) time to compute the root weight).

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a0/Vector_Rope_concat.svg/254px-Vector_Rope_concat.svg.png)

A concatenation can be performed simply by creating a new root node with left = S1 and right = S2, which is constant time. The weight of the parent node is set to the length of the left child S1, which would take  O(log N) time, if the tree is balanced.

As most rope operations require balanced trees, the tree may need to be re-balanced after concatenation.

##### Split

Definition: Split (i, S): split the string S into two new strings S1 and S2, S1 = C1, …, Ci and S2 = Ci + 1, …, Cm.
__Time complexity:O(log N).__

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/f/fd/Vector_Rope_split.svg/418px-Vector_Rope_split.svg.png)

There are two cases that must be dealt with:

1. The split point is at the end of a string (i.e. after the last character of a leaf node)  
2. The split point is in the middle of a string.  

The second case reduces to the first by splitting the string at the split point to create two new leaf nodes, then creating a new node that is the parent of the two component strings.

##### Insert

Definition: Insert(i, S’): insert the string S’ beginning at position i in the string s, to form a new string.

__Time complexity:O(log N).__

This operation can be done by a Split() and two Concat() operations. The cost is the sum of the three.

##### Delete

Definition: Delete(i, j): delete the substring Ci, …, Ci + j − 1, from s to form a new string C1, …, Ci − 1, Ci + j, …, Cm.

__Time complexity:O(log N).__

This operation can be done by two Split() and one Concat() operation. First, split the rope in three, divided by i-th and i+j-th character respectively, which extracts the string to delete in a separate node. Then concatenate the other two nodes.




# Sample solution

```cpp
class RopeNode {
public:
  RopeNode(const std::stirng & text = "") : m_text(text), m_weight(text.size()){}
  std::string m_text;
  std::size_t m_weight;
  RopeNodePtr m_left;
  RopeNodePtr m_right;
};

class Rope {
public:
  Rope(){}
  char GetChar(std::size_t pos) { return GetChar(m_root, pos); }
  void Insert(std::size_t pos, const std::string & text) { return Insert(m_root, pos, text); }
  void Delete(std::size_t from, std::size_t to) { Delete(m_root, from, to); }
private:


  static char GetChar(const RopeNodePtr & root, std::size_t pos) {
    if (!root) return '';

    if (root->m_weight < pos) {
      return GetChar(root->right, pos - root->m_weight);
    } else {
      if (root->m_left) {
        return GetChar(root->left, pos);
      } else { // leaf node
        return root->m_text[pos];
      }
    }
  }

  // Return a Rope tree based on input
  static NodePtr Build(const std::string & input) {
    const std::size_t input_size(input.size());
    if (input_size <= 0) {
      return nullptr;
    } else if( input_size == 1) {
      return std::make_shared<Node>(input);
    } else {
      NodePtr root = std::make_shared<Node>();
      root->m_left = Build(input.substr(0,input_size/2));
      root->m_right = Build(input.substr(input_size/2));
      root->m_wieght  = root->m_left->m_weight + root->m_right->m_weight;
      return root;
    }
  }

  static RopeNodePtr GetNewNode(const std::string & text) {
    return std::make_shared<RopeNode>(text);
  }
 /***
    A concatenation can be performed simply by creating a new root node with left = S1 and right = S2,
    which is constant time. The weight of the parent node is set to the length of the left child S1, which would take O(log N) time, if the tree is balanced.
    As most rope operations require balanced trees, the tree may need to be re-balanced after concatenation.
  ***/
  static RopeNodePtr Concat(RopeNodePtr & left, RopeNodePtr & right) {
    RopeNodePtr reval = std::make_shared<RopeNode>();
    reval->m_weight = left->m_weight + right->m_weight;
    // balancing....
    return reval;
  }

  /***
      Split the Rope into two ropes, the other rope will be stored at `other`.
   ***/
  static void Split(RopeNodePtr & root, std::size_t pos, RopeNodePtr & other);

  /***
    This operation can be done by two Split() and one Concat() operation. First, split the rope in three,
    divided by i-th and i+j-th character respectively, which extracts the string to delete in a separate node.
    Then concatenate the other two nodes.
   ***/
  static void Delete(RopeNodePtr & root, std::size_t from, std::size_t to) {
    RopeNodePtr left_part,  right_part, other;

    Split(root, from, other);
    left_part = root;


    Split(other, to - from, right_part);

    root = Concat(left_part, right_part);

    // Call balance function
  }

  static void Insert(RopeNodePtr & root, std::size_t pos, const std::string & input) {
    RopeNodePtr other;
    Split(root, pos, other);
    RopeNodePtr new_node = GetNewNode(input);

    root = Concat(root, new_node);
    root = concat(root, other);
    // Call balance function
  }
};

// Here TextEditor is the receivor
class TextEditor{
public:
  TextEditor();
  void Insert(std::size_t pos, const std::string & text) { m_rope.Insert(pos, text); }
  void Delete(std::size_t from, std::size_t to) { m_rope.Delete(from, to); }
  void Highlight(std::size_t from, std::size_t to) {}
  void DeleteHighlight(std::size_t from, std::size_t to);
  std::size_t Search(const std::string);
  void Save(const std::string & file_path);
  void Load(const std::string & file_path);
private:
  Rope m_rope;
};
typedef std::shared_ptr<TextEditor> TextEditorPtr;

// The command interface
class ICommand {
public:
  ICommand(){}
  ~ICommand(){}
  virtual void Execute() = 0;
  virtual void Undo() = 0;
  virtual void Redo() = 0;
};
typedef std::shared_ptr<ICommand> ICommandPtr;

// The concrete command
class HighlightCommand : public ICommand {
public:
  HighlightCommand(const TextEditorPtr & editor,std::size_t from, std::size_t to)
    : m_text_editor(editor),m_from(from),m_to(to){}
  void Execute() {m_text_editor->Highlight(m_from,m_to);}
  void Redo() {m_text_editor->Highlight(m_from,m_to);}
  void Undo() {m_text_editor->DeleteHighlight(m_from,m_to);}
private:
  TextEditorPtr m_text_editor;
  std::size_t m_from;
  std::size_t m_to;
};


class CommandManager {
public:
  CommandManager(){}
  void ExecuteCommand(const ICommandPtr & command) {
    m_redo_stack.clear();// don't forget to clear redo stack
    command->Execute();
    m_undo_stack.push(command);
  }
  void Undo() {
    if (m_undo_stack.empty()) return;
    m_undo_stack.top()->Undo();
    m_redo_stack.push(m_undo_stack.top());
    m_undo_stack.pop();
  }
  void Redo() {
    if (m_redo_stack.empty()) return;
    m_redo_stack.top()->Redo();
    m_undo_stack.push(m_redo_stack.top());
    m_redo_stack.pop();
  }
private:
  std::stack<ICommandPtr> m_undo_stack;
  std::stack<ICommandPtr> m_redo_stack;
};
```
