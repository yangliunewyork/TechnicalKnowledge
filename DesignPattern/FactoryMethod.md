## What is Factory Method pattern?

![alt](https://upload.wikimedia.org/wikipedia/commons/e/ed/Factory_Method_UML_class_diagram.png)

Factory Design Pattern is one of the creational design patterns. It is to help you with the creation of an object at runtime without the client needing to know the internal implementation details (not even the name of the class). For this, the factory needs to have one additional but mandatory input - which indicates what type of object you want to create.


It should be pretty clear that reducing dependencies to concrete classes in our code is a “good thing.” In fact, we’ve got an OO design principle that formalizes this notion; it even has a big, formal name: __Dependency Inversion Principle__. 
__Design Principle : Depend upon abstractions. Do not depend upon concrete classes.__
At first, this principle sounds a lot like “Program to an interface, not an implementation,” right? It is similar; however, the Dependency Inversion Principle makes an even stronger statement about abstraction. It suggests that our high-level components should not depend on our low-level components; rather, they should both depend on abstractions.
The following guidelines can help you avoid OO designs that violate the Dependency Inversion Principle:
* No variable should hold a reference to a concrete class.
  * If you use new, you’ll be holding a reference to a concrete class. Use a factory to get around that!
* No class should derive from a concrete class.
  * If you derive from a concrete class, you’re depending on a concrete class. Derive from an abstraction, like an interface or an abstract class.
* No method should override an implemented method of any of its base classes.
  * If you override an implemented method, then your base class wasn’t really an abstraction to start with. Those methods implemented in the base class are meant to be shared by all your subclasses.


### Definition
"Define an interface for creating an object, but let subclasses decide which class to instantiate. The Factory method lets a class defer instantiation it uses to subclasses." (Gang Of Four)
Creating an object often requires complex processes not appropriate to include within a composing object. The object's creation may lead to a significant duplication of code, may require information not accessible to the composing object, may not provide a sufficient level of abstraction, or may otherwise not be part of the composing object's concerns. The factory method design pattern handles these problems by defining a separate method for creating the objects, which subclasses can then override to specify the derived type of product that will be created.
The factory method pattern relies on inheritance, as object creation is delegated to subclasses that implement the factory method to create objects.

## Applicability

Use the Factory Method pattern when
* a class can't anticipate the class of objects it must create.
* a class wants its subclasses to specify the objects it creates.
* classes delegate responsibility to one of several helper subclasses, and you want to localize the knowledge of which helper subclass is the delegate. 
