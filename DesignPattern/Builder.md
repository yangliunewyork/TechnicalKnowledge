### What is Builder pattern?
Builder often builds a Composite. Often, designs start out using Factory Method (less complicated, more customizable, subclasses proliferate) and evolve toward Abstract Factory, Prototype, or Builder (more flexible, more complex) as the designer discovers where more flexibility is needed. Sometimes creational patterns are complementary: Builder can use one of the other patterns to implement which components are built. Builders are good candidates for a fluent interface.

### Intent
Separate the construction of a complex object from its representation so that the same construction process can create different representations. 

### Applicability
Use the Builder pattern when
* the algorithm for creating a complex object should be independent of the parts that make up the object and how they're assembled.
* the construction process must allow different representations for the object that's constructed. 

### Participants
1. Builder 
* specifies an abstract interface for creating parts of a Product object.
2. ConcreteBuilder
* constructs and assembles parts of the product by implementing the Builder interface.
* defines and keeps track of the representation it creates.
* provides an interface for retrieving the product.
3. Director
* constructs an object using the Builder interface.
4. Product
* represents the complex object under construction. ConcreteBuilder builds the product's internal representation and defines the process by which it's assembled.
* includes classes that define the constituent parts, including interfaces for assembling the parts into the final result. 

### Collaborations
* The client creates the Director object and configures it with the desired Builder object.
* Director notifies the builder whenever a part of the product should be built.
* Builder handles requests from the director and adds parts to the product.
* The client retrieves the product from the builder. 


### Builder pattern vs Factory method
http://stackoverflow.com/questions/757743/what-is-the-difference-between-builder-design-pattern-and-factory-design-pattern
* Builder focuses on constructing a complex object step by step. Abstract Factory emphasizes a family of product objects (either simple or complex). Builder returns the product as a final step, but as far as the Abstract Factory is concerned, the product gets returned immediately.
* Builder often builds a Composite.
* Often, designs start out using Factory Method (less complicated, more customizable, subclasses proliferate) and evolve toward Abstract Factory, Prototype, or Builder (more flexible, more complex) as the designer discovers where more flexibility is needed.
* Sometimes creational patterns are complementary: Builder can use one of the other patterns to implement which components get built. Abstract Factory, Builder, and Prototype can use Singleton in their implementations.
* The Factory pattern can almost be seen as a simplified version of the Builder pattern.In the Factory pattern, the factory is in charge of creating various subtypes of an object depending on the needs.The user of a factory method doesn't need to know the exact subtype of that object. An example of a factory method createCar might return a Ford or a Honda typed object.In the Builder pattern, different subtypes are also created by a builder method, but the composition of the objects might differ within the same subclass.To continue the car example you might have a createCar builder method which creates a Honda-typed object with a 4 cylinder engine, or a Honda-typed object with 6 cylinders. The builder pattern allows for this finer granularity.
*Constructing a complex object step by step : builder pattern. A simple object is created by using a single method : factory method pattern. Creating Object by using multiple factory method : Abstract factory pattern.
