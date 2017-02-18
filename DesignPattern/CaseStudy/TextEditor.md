## Problem
Design a text editor. It should support insert(p), delete(p1, p2), highlight(p1, p2)，redo/undo, save/load update, search.
And the operations should be saved as well to disk so that I can even undo operation after one week.

### Data Structure : Rope
In computer programming, a rope, or cord, is a data structure composed of smaller strings that is used for efficiently storing and manipulating a very long string. For example, a text editing program may use a rope to represent the text being edited, so that operations such as insertion, deletion, and random access can be done efficiently.

### How to save to disk : JSON
Tree structure can be easily serialized and deserialized, the only questions is : in what format? Generally JSON is the most common choice here comparing to XML. However, you need to outline the requirements of the whole project in order to make that decision. For simplicity, JSON is good enough here.
We can use any tree traversal algorithm, for example pre order traversal which has a very simple implementation here, to serialize/deserialize the text to disk format.   


### Data Structure for Operations Saving : Stack
One stack for Redo, one stack for Undo. 
The operations should be saved to disk as well.
 


