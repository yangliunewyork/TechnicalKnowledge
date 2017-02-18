### What is Adapter pattern?

![alt](http://www.bogotobogo.com/DesignPatterns/images/adapter/class_adapter.gif)

￼The Adapter Pattern converts the interface of a class into another interface the clients expect. Adapter lets classes work together that couldn’t otherwise because of incompatible interfaces.

Now, we know this pattern allows us to use a client with an incompatible interface by creating an Adapter that does the conversion. This acts to decouple the client from the implemented interface, and if we expect the interface to change over time, the adapter encapsulates that change so that the client doesn’t have to be modified each time it needs to operate against a different interface.

The Adapter Pattern is full of good OO design principles: check out the use of object composition to wrap the adaptee with an altered interface. This approach has the added advantage that we can use an adapter with any subclass of the adaptee.

Also check out how the pattern binds the client to an interface, not an implementation; we could use several adapters, each converting a different backend set of classes. Or, we could add new implementations after the fact, as long as they adhere to the Target interface.

### Here’s how the Client uses the Adapter
1. The client makes a request to the adapter by calling a method on it using the target interface.
2. The adapter translates the request into one or more calls on the adaptee using the adaptee interface.
3. The client receives the results of the call and never knows there is an adapter doing the translation.

### Examples

#### Container adapters in C++
Container adapters, are interfaces created by limiting functionality in a pre-existing container and providing a different set of functionality. When you declare the container adapters, you have an option of specifying which sequence containers form the underlying container. These are:
* A stack is a container providing Last-In, First-Out (LIFO) access. Basically, you remove elements in the reverse order you insert them. It's difficult to get to any elements in the middle. __Usually this goes on top of a deque__.
* A queue is a container providing First-In, First-Out (FIFO) access. You remove elements in the same order you insert them. It's difficult to get to any elements in the middle. __Usually this goes on top of a deque__.
* A priority_queue is a container providing sorted-order access to elements. You can insert elements in any order, and then retrieve the "lowest" of these values at any time. __Priority queues in C++ STL use a heap structure internally, which in turn is basically array-backed; thus, usually this goes on top of a vector__.
