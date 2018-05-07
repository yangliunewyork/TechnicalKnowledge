# Intent

Provide an interface for creating families of related or dependent objects without specifying their concrete classes.

# Applicability

Use the Abstract Factory pattern when:  

* a system should be independent of how its products are created, composed, and represented.    
* a system should be configured with one of multiple families of products.    
* a family of related product objects is designed to be used together, and you need to enforce this constraint.  
* you want to provide a class library of products, and you want to reveal just their interfaces, not their implementations. 

# Structure

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/DesignPattern/Photos/Abstract%20Fatory.png">

# Participants

* AbstractFactory (WidgetFactory) 
  * declares an interface for operations that create abstract product objects.
* ConcreteFactory (MotifWidgetFactory, PMWidgetFactory)
  * implements the operations to create concrete product objects.
* AbstractProduct (Window, ScrollBar)
  * declares an interface for a type of product object.
* ConcreteProduct (MotifWindow, MotifScrollBar)
  * defines a product object to be created by the corresponding concrete factory.
  * implements the AbstractProduct interface.
* Client
  * uses only interfaces declared by AbstractFactory and AbstractProduct classes.

# Collaborations

* Normally a single instance of a ConcreteFactory class is created at run-time. This concrete factory creates product objects having a particular implementation. To create different product objects, clients should use a different concrete factory.  
* AbstractFactory defers creation of product objects to its ConcreteFactory subclass. 

# Consequences

The Abstract Factory pattern has the following benefits and liabilities:

1. It isolates concrete classes.The AbstractFactory pattern helps you control the classes of objects that an application creates. Because a factory encapsulates the responsibility and the process of creating product objects, it isolates clients from implementation classes. __Clients manipulate instances through their abstract interfaces. Product class names are isolated in the implementation of the concrete factory; they do not appear in client code.__  
2. It makes exchanging product families easy. The class of a concrete factory appears only once in an application—that is, where it's instantiated. This makes it easy to change the concrete factory an application uses. It can use different product configurations simply by changing the concrete factory. __Because an abstract factory creates a complete family of products, the whole product family changes at once.__ In our user interface example, we can switch from Motif widgets to Presentation Manager widgets simply by switching the corresponding factory objects and recreating the interface.  
3. It promotes consistency among products. When product objects in a family are designed to work together, it's important that an application use objects from only one family at a time. AbstractFactory makes this easy to enforce.  
4. Supporting new kinds of products is difficult.Extending abstract factories to produce new kinds of Products isn't easy. That's because the AbstractFactory interface fixes the set of products that can be created. Supporting new kinds of products requires extending the factory interface, which involves changing the AbstractFactory class and all of its subclasses. We discuss one solution to this problem in the Implementation section.

# Implementation

Here are some useful techniques for implementing the Abstract Factory pattern:  

1. Factories as singletons. An application typically needs only one instance of a ConcreteFactory per product family. So it's usually best implemented as a Singleton.  
2. Creating the products. AbstractFactory only declares an interface for creating products. It's up to ConcreteProduct subclasses to actually create them. The most common way to do this is to define a factory method (see Factory Method (121)) for each product. A concrete factory will specify its products by overriding the factory method for each. While this implementation is simple, it requires a new concrete factory subclass for each product family, even if the product families differ only slightly. If many product families are possible, the concrete factory can be implemented using the Prototype  pattern. The concrete factory is initialized with a prototypical instance of each product in the family, and it creates a new product by cloning its prototype. The Prototype-based approach eliminates the need for a new concrete factory class for each new product family.

# Related Patterns

* AbstractFactory classes are often implemented with factory methods (Factory Method (121)), but they can also be implemented using Prototype.  
* A concrete factory is often a singleton.  


# Appendix

### What is Abstract factory pattern ?

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a7/Abstract_factory.svg/517px-Abstract_factory.svg.png)

The abstract factory pattern provides a way to encapsulate a group of individual factories that have a common theme without specifying their concrete classes. In normal usage, the client software creates a concrete implementation of the abstract factory and then uses the generic interface of the factory to create the concrete objects that are part of the theme. The client doesn't know (or care) which concrete objects it gets from each of these internal factories, since it uses only the generic interfaces of their products. This pattern separates the details of implementation of a set of objects from their general usage and relies on object composition, as object creation is implemented in methods exposed in the factory interface.

An Abstract Factory gives us an interface for creating a family of products. By writing code that uses this interface, we decouple our code from the actual factory that creates the products. That allows us to implement a variety of factories that produce products meant for different contexts – such as different regions, different operating systems, or different look and feels.
Because our code is decoupled from the actual products, we can substitute different factories to get different behaviors.

#### BULLET POINTS
* All factories encapsulate object creation.
* Simple Factory, while not a bona fide design pattern, is a simple way to decouple your clients from concrete classes.
* Factory Method relies on inheritance: object creation is delegated to subclasses which implement the factory method to create objects.
* Abstract Factory relies on object composition: object creation is implemented in methods exposed in the factory interface.
* All factory patterns promote loose coupling by reducing the dependency of your application on concrete classes.
* The intent of Factory Method is to allow a class to defer instantiation to its subclasses.
* The intent of Abstract Factory is to create families of related objects without having to depend on their concrete classes.
* The Dependency Inversion Principle guides us to avoid dependencies on concrete types and to strive for abstractions.
* Factories are a powerful technique for coding to abstractions, not concrete classes

### Difference between Abstract Factory and Factory Method design patterns:
* Factory Method is used to create one product only but Abstract Factory is about creating families of related or dependent products.
* Factory Method pattern exposes a method to the client for creating the object whereas in case of Abstract Factory they expose a family of related objects which may consist of these Factory methods.
* Factory Method pattern hides the construction of single object where as Abstract factory method hides the construction of a family of related objects. Abstract factories are usually implemented using (a set of) factory methods.
* __AbstractFactory pattern uses composition to delegate responsibility of creating object to another class while Factory design pattern uses inheritance and relies on derived class or sub class to create object.__
* The idea behind the Factory Method pattern is that it allows for the case where a client doesn't know what concrete classes it will be required to create at runtime, but just wants to get a class that will do the job while AbstractFactory pattern is best utilised when your system has to create multiple families of products or you want to provide a library of products without exposing the implementation details.!
