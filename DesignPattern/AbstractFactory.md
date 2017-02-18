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
