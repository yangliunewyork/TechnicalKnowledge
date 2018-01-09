A JavaBean is just a [standard](http://www.oracle.com/technetwork/java/javase/documentation/spec-136004.html).

* All properties private (use [getters/setters](https://en.wikipedia.org/wiki/Mutator_method))
* A public [no-argument constructor](https://en.wikipedia.org/wiki/Nullary_constructor).
* Implements [Serializable](https://docs.oracle.com/javase/8/docs/api/java/io/Serializable.html).

That's it. It's just a convention.



In computing based on the Java Platform, JavaBeans are classes that encapsulate many objects into a single object (the bean). They are __serializable__, have __a zero-argument constructor__, and __allow access to properties using getter and setter methods__. The name "Bean" was given to encompass this standard, which aims to create reusable software components for Java.

#### Advantages

* The properties, events, and methods of a bean can be exposed to another application.
* A bean may register to receive events from other objects and can generate events that are sent to those other objects.
* Auxiliary software can be provided to help configure a bean.
* The configuration settings of a bean can be saved to persistent storage and restored.

#### Disadvantages

* A class with a nullary constructor is subject to being instantiated in an invalid state. If such a class is instantiated manually by a developer (rather than automatically by some kind of framework), the developer might not realize that the class has been improperly instantiated. The compiler cannot detect such a problem, and even if it is documented, there is no guarantee that the developer will see the documentation.
* JavaBeans are inherently mutable and so lack the advantages offered by immutable objects.
* Having to create getters for every property and setters for many, most, or all of them can lead to an immense quantity of boilerplate code.
