### What is Iterator Pattern?

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/1/13/Iterator_UML_class_diagram.svg/750px-Iterator_UML_class_diagram.svg.png)

￼The Iterator Pattern provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.It also places the task of traversal on the iterator object, not on the aggregate, which simplifies the aggregate interface and implementation, and places the responsibility where it should be.
Having a common interface for your aggregates is handy for your client; it decouples your client from the implementation of your collection of objects.

### Single Responsibility
__Design Principle : A class should have only one reason to change.__
Every responsibility of a class is an area of potential change. More than one responsibility means more than one area of change. This principle guides us to keep each class to a single responsibility.


### Bullet Points
* An Iterator allows access to an aggregate’s elements without exposing its internal structure.
* An Iterator takes the job of iterating over an aggregate and encapsulates it in another object.
* When using an Iterator, we relieve the aggregate of the responsibility of supporting operations for traversing its data.
* An Iterator provides a common interface for traversing the items of an aggregate, allowing you to use polymorphism when writing code that makes use of the items of the aggregate.
* We should strive to assign only one responsibility to each class.
