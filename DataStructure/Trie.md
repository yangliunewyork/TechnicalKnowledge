In computer science, a __trie__, also called __digital tree__ and sometimes __radix tree__ or __prefix tree__ (as they can be searched by prefixes), is a kind of search tree—an ordered tree data structure that is used to store a dynamic set or associative array where the keys are usually strings. Unlike a binary search tree, no node in the tree stores the key associated with that node; instead, its position in the tree defines the key with which it is associated. All the descendants of a node have a common prefix of the string associated with that node, and the root is associated with the empty string. Values are not necessarily associated with every node. Rather, values tend only to be associated with leaves, and with some inner nodes that correspond to keys of interest.


Trie is an efficient information re_Trie_val data structure. Using Trie, search complexities can be brought to optimal limit (key length). If we store keys in binary search tree, a well balanced BST will need time proportional to M * log N, where M is maximum string length and N is number of keys in tree. Using Trie, we can search the key in O(M) time. However the penalty is on Trie storage requirements.

Every node of Trie consists of multiple branches. Each branch represents a possible character of keys. We need to mark the last node of every key as end of word node.

Inserting a key into Trie is simple approach. Every character of input key is inserted as an individual Trie node. Note that the children is an array of pointers (or references) to next level trie nodes. The key character acts as an index into the array children. If the input key is new or an extension of existing key, we need to construct non-existing nodes of the key, and mark end of word for last node. If the input key is prefix of existing key in Trie, we simply mark the last node of key as end of word. The key length determines Trie depth.

__Insert and search costs O(key_length)__, however the memory requirements of Trie is __O(ALPHABET_SIZE * key_length * N)__ where N is number of keys in Trie. There are efficient representation of trie nodes (e.g. compressed trie, ternary search tree, etc.) to minimize memory requirements of trie.

### What are TRIE data structure usage or applications?

1. Dictionary Suggestions OR Autocomplete dictionary  
  Retrieving data stored in Trie data structure is very fast, so it is most suited for application where retrieval are more frequently performed like Phone directory where contact searching operation is used frequently.

2. Searching Contact from Mobile Contact list OR Phone Directory  
  Auto suggestion of words while searching for anything in dictionary is very common.  
  If we search for word "tiny", then it auto suggest words starting with same characters like "tine", "tin", "tinny" etc.
Auto suggestion is very useful and Trie plays a nice role there, Lets see real time use.
If say, Person doesn't know the complete spelling of the some word but know few, then rest of words starting with few characters can be auto suggested using TRIE data structure.
