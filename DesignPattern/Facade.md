### What is Facade pattern?

![alt](https://powerdream5.files.wordpress.com/2007/10/10_21_1_2007.jpg)

__The Facade Pattern provides a unified interface to a set of interfaces in a subsytem. Facade defines a higher-level interface that makes the subsystem easier to use.__

The facade pattern (or façade pattern) is a software design pattern commonly used with object-oriented programming. The name is by analogy to an architectural facade.
A facade is an object that provides a simplified interface to a larger body of code, such as a class library. A facade can

* make a software library easier to use, understand and test, since the facade has convenient methods for common tasks,
* make the library more readable, for the same reason, 
* reduce dependencies of outside code on the inner workings of a library, since most code uses the facade, thus allowing more flexibility in developing the system,
* wrap a poorly designed collection of APIs with a single well-designed API.

The Facade design pattern is often used when a system is very complex or difficult to understand because the system has a large number of interdependent classes or its source code is unavailable. This pattern hides the complexities of the larger system and provides a simpler interface to the client. It typically involves a single wrapper class that contains a set of members required by client. These members access the system on behalf of the facade client and hide the implementation details.

Facades don’t “encapsulate” the subsystem classes; they merely provide a simplified interface to their functionality. The subsystem classes still remain available for direct use by clients that need to use more specific interfaces. This is a nice property of the Facade Pattern: it provides a simplified interface while still exposing the full functionality of the system to those who may need it.The Facade Pattern also allows you to decouple your client implementation from any one subsystem. 

Remember, the Adapter Pattern changes the interface of one or more classes into one interface that a client is expecting. While most textbook examples show the adapter adapting one class, you may need to adapt many classes to provide the interface a client is coded to. Likewise, a Facade may provide a simplified interface to a single class with a very complex interface.
The difference between the two is not in terms of how many classes they “wrap,” it is in their __intent__. __The intent of the Adapter Pattern is to alter an interface so that it matches one a client is expecting. The intent of the Facade Pattern is to provide a simplified interface to a subsystem.__

#### Keypoint
* __A facade not only simplifies an interface, it decouples a client from a subsystem of components.__
* __Facades and adapters may wrap multiple classes, but a facade’s intent is to simplify, while an adapter’s is to convert the interface to something different.__

### The Principle of Least Knowledge
__Principle of Least Knowledge - talk only to your immediate friends.__

But what does this mean in real terms? It means when you are designing a system, for any object, be careful of the number of classes it interacts with and also how it comes to interact with those classes.

This principle prevents us from creating designs that have a large number of classes coupled together so that changes in one part of the system cascade to other parts. When you build a lot of dependencies between many classes, you are building a fragile system that will be costly to maintain and complex for others to understand.

#### Bullet Points
* When you need to use an existing class and its interface is not the one you need, use an adapter.
* When you need to simplify and unify a large interface or complex set of interfaces, use a facade.
* An adapter changes an interface into one a client expects.
* A facade decouples a client from a complex subsystem.
* Implementing an adapter may require little work or a great deal of work depending on the size and complexity of the target interface.
* Implementing a facade requires that we compose the facade with its subsystem and use delegation to perform the work of the facade.
* There are two forms of the Adapter Pattern: object and class adapters. Class adapters require multiple inheritance.
* You can implement more than one facade for a subsystem.
* An adapter wraps an object to change its interface, a decorator wraps an object to add new behaviors and responsibilities, and a facade “wraps” a set of objects to simplify.
