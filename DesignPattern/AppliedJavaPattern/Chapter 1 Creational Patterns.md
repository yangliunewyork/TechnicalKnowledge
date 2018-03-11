These patterns support one of the most common tasks in object-oriented programming—the creation of objects in a system. Most OO systems of any complexity require many objects to be instantiated over time, and these patterns support the creation process by helping to provide the following capabilities: 

* Generic instantiation – This allows objects to be created in a system without having to identify a specific class type in code. 
* Simplicity – Some of the patterns make object creation easier, so callers will not have to write large, complex code to instantiate an object. 
* Creation constraints – Some patterns enforce constraints on the type or number of objects that can be created within a system. 

The following patterns are discussed in this chapter: 

* Abstract Factory – To provide a contract for creating families of related or dependent objects without having to specify their concrete classes.   
* Builder – To simplify complex object creation by defining a class whose purpose is to build instances of another class. The Builder produces one main product, such that there might be more than one class in the product, but there is always one main class.   
* Factory Method – To define a standard method to create an object, apart from a constructor, but the decision of what kind of an object to create is left to subclasses.   
* Prototype – To make dynamic creation easier by defining classes whose objects can create duplicates of themselves.  
* Singleton – To have only one instance of this class in the system, while allowing other classes to get access to this instance.  

Of these patterns, the Abstract Factory and Factory Method are explicitly based on the concept of defining flexible object creation; they assume that the classes or interfaces to be created will be extended in an implementing system. As a result, these two patterns are frequently combined with other creational patterns.

# Abstract Factory

Also known as Kit, Toolkit

##### Pattern Properties  

* Type: Creational, Object
* Level: Component

##### Purpose  

To provide a contract for creating families of related or dependent objects without having to specify their concrete classes.

### Introduction

Suppose you plan to manage address and telephone information as part of a personal information manager (PIM) application. The PIM will act as a combination address book, personal planner, and appointment and contact manager, and will use the address and phone number data extensively.

You can initially produce classes to represent your address and telephone number data. Code these classes so that they store the relevant information and enforce business rules about their format. For example, all phone numbers in North America are limited to ten digits and the postal code must be in a particular format.

Shortly after coding your classes, you realize that you have to manage address and phone information for another country, such as the Netherlands. The Netherlands has different rules governing what constitutes a valid phone number and address, so you modify your logic in the Address and PhoneNumber classes to take the new country into account.

Now, as your personal network expands, you need to manage information from another foreign country... and another... and another. With each additional set of business rules, the base Address and PhoneNumber classes become even more bloated with code and even more difficult to manage. What's more, this code is brittle—with every new country added, you need to modify and recompile the classes to manage contact information.

It’s better to flexibly add these paired classes to the system; to take the general rules that apply to address and phone number data, and allow any number of possible foreign variations to be “loaded” into a system.

The Abstract Factory solves this problem. Using this pattern, you define an AddressFactory—a generic framework for producing objects that follow the general pattern for an Address and PhoneNumber. At runtime, this factory is paired with any number of concrete factories for different countries, and each country has its own version of Address and PhoneNumber classes.

Instead of going through the nightmare of adding functional logic to the classes, extend the Address to a DutchAddress and the PhoneNumber to a DutchPhoneNumber. Instances of both classes are created by a DutchAddressFactory. This gives greater freedom to extend your code without having to make major structural modifications in the rest of the system.  

### Applicability

Use the Abstract Factory pattern when:

* The client should be independent of how the products are created.  
* The application should be configured with one of multiple families of products.  
* Objects need to be created as a set, in order to be compatible.  
* You want to provide a collection of classes and you want to reveal just their contracts and their relationships, not their implementations.   

### Implementation

![alt](https://www.uml-diagrams.org/examples/class-example-abstract-factory.png)  

You typically use the following to implement the Abstract Factory pattern:  

* AbstractFactory – An abstract class or interface that defines the create methods for abstract products.   
* AbstractProduct – An abstract class or interface describing the general behavior of the resource that will be used by the application.
* ConcreteFactory – A class derived from the abstract factory . It implements create methods for one or more concrete products.
* ConcreteProduct – A class derived from the abstract product, providing an implementation for a specific resource or operating environment.

### Benefits and Drawbacks

An Abstract Factory helps to increase the overall flexibility of an application. This flexibility manifests itself both during design time and runtime. During design, you do not have to predict all future uses for an application. Instead, you create the generic framework and then develop implementations independently from the rest of the application. At runtime, the application can easily integrate new features and resources.  

A further benefit of this pattern is that it can simplify testing the rest of the application. Implementing a TestConcreteFactory and TestConcreteProduct is simple ; it can simulate the expected resource behavior.

To realize the benefits of this pattern, carefully consider how to define a suitably generic interface for the abstract product. If the abstract product is improperly defined, producing some of the desired concrete products can be difficult or impossible.


# Builder

#### Purpose

To simplify complex object creation by defining a class whose purpose is to build instances of another class. The Builder produces one main product, such that there might be more than one class in the product, but there is always one main class.

#### Applicability

Use the Builder pattern when a class:

* Has complex internal structure (especially one with a variable set of related objects).
* Has attributes that depend on each other. One of the things a Builder can do is enforce staged construction of a complex object. This would be required when the Product attributes depend on one another. For instance, suppose you’re building an order. You might need to ensure that you have a state set before you move on to "building" the shipping method, because the state would impact the sales tax applied to the Order itself.
* Uses other objects in the system that might be difficult or inconvenient to obtain during creation.

#### Description

Because this pattern is concerned with building a complex object from possibly multiple different sources, it is called the Builder. As object creation increases in complexity, managing object creation from within the constructor method can become difficult. This is especially true if the object does not depend exclusively on resources that are under its own control.

Business objects often fall into this category. They frequently require data from a database for initialization and might need to associate with a number of other business objects to accurately represent the business model.

Another example is that of composite objects in a system, such as an object representing a drawing in a visual editing program. Such an object might need to be related to an arbitrary number of other objects as soon as it’s created.

In cases like this, it is convenient to define another class (the Builder) that is responsible for the construction. The Builder coordinates the assembly of the product object: creating resources, storing intermediate results, and providing functional structure for the creation. Additionally, the Builder can acquire system resources required for construction of the product object.

#### Implementation

<img src="https://i.ytimg.com/vi/EHS4h2noiMQ/maxresdefault.jpg" height="400" width="800">

To implement the Builder pattern, you need:

* __Director__ – Has a reference to an AbstractBuilder instance. The Director calls the creational methods on its builder instance to have the different parts and the Builder build.  
* __AbstractBuilder__ – The interface that defines the available methods to create the separate parts of the product.  
* __ConcreteBuilder__ – Implements the AbstractBuilder interface. The ConcreteBuilder implements all the methods required to create a real Product. The implementation of the methods knows how to process information from the Director and build the respective parts of a Product. The ConcreteBuilder also has either a getProduct method or a creational method to return the Product instance.  
* __Product__ – The resulting object. You can define the product as either an interface (preferable) or class.  

#### Benefits and Drawbacks

The Builder pattern makes it easier to manage the overall flow during the creation of complex objects. This
manifests itself in two ways:

For objects that require phased creation (a sequence of steps to make the object fully active), the Builder acts as a higher-level object to oversee the process. It can coordinate and validate the creation of all resources and if necessary provide a fallback strategy if errors occur.

For objects that need existing system resources during creation, such as database connections or existing business objects, the Builder provides a convenient central point to manage these resources. The Builder also provides a single point of creational control for its product, which other objects within the system can use. Like other creational patterns, this makes things easier for clients in the software system, since they need only access the Builder object to produce a resource.

The main drawback of this pattern is that there is tight coupling among the Builder, its product, and any other creational delegates used during object construction. Changes that occur for the product created by the Builder often result in modifications for both the Builder and its delegates.

#### Pattern Variants

At the most fundamental level, it is possible to implement a bare-bones Builder pattern around a single Builder class with a creational method and its product. For greater flexibility, designers often extend this base pattern with one or more of the following approaches:

* Create an abstract Builder. By defining an abstract class or interface that specifies the creational methods, you can produce a more generic system that can potentially host many different kinds of builders.
* Define multiple create methods for the Builder. Some Builders define multiple methods (essentially, they overload their creational method) to provide a variety of ways to initialize the constructed resource.
* Develop creational delegates. With this variant, a Director object holds the overall Product create method and calls a series of more granular create methods on the Builder object. In this case, the Director acts as the manager for the Builder’s creation process.

# Factory Method

Factory Method is also known as Virtual Constructor.

#### Pattern Properties

Type: Creational
Level: Class

#### Purpose

To define a standard method to create an object, apart from a constructor, but the decision of what kind of an object to create is left to subclasses.

#### Applicability

Use Factory Method pattern when:

* You want to create an extensible framework. This means allowing flexibility by leaving some decisions, like the specific kind of object to create, until later.  
* You want a subclass, rather than its superclass, to decide what kind of an object to create.  
* You know when to create an object, but not what kind of an object. 
* You need several overloaded constructors with the same parameter list, which is not allowed in Java. Instead, use several Factory Methods with different names.  

#### Description

This pattern is called Factory Method because it creates (manufactures) objects when you want it to.  

When you start writing an application, it’s often not clear yet what kind of components you will be using. Normally you will have a general idea of the operations certain components should have, but the implementation is done at some other time and will not be of consequence at that moment.  

This flexibility can be achieved by using interfaces for these components. But the problem with programming to interfaces is that you cannot create an object from an interface. You need an implementing class to get an object. Instead of coding a specific implementing class in your application, you extract the functionality of the constructor and put it in a method. That method is the factory method.

To create these objects, instead of coding a specific implementing class in your application, you extract the functionality of the constructor and put it in a method. This produces a ```ConcreteCreator``` whose responsibility it is to create the proper objects. That ConcreteCreator creates instances of an implementation (```ConcreteProduct```) of an interface (```Product```).

#### Implementation

<img src="https://upload.wikimedia.org/wikipedia/commons/8/8e/Factory_Method_UML_class_diagram.svg" height="300" width="600">

To implement the Factory Method you need:

* __Product__ – The interface of objects created by the factory.   
* __ConcreteProduct__ – The implementing class of Product. Objects of this class are created by the ConcreteCreator.    
* __Creator__ – The interface that defines the factory method(s) (factoryMethod).    
* __ConcreteCreator__ – The class that extends Creator and that provides an implementation for the factoryMethod. This can return any object that implements the Product interface.   

#### Benefits and Drawbacks

The drawback to this pattern is the fact that to add a new type of product, you must add another new implementing class, and you must either change an existing ConcreteCreator or create a new class that implements Product.


# Prototype



