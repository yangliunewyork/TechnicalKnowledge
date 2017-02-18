### What is Template design pattern?
￼The Template Method Pattern defines the skeleton of an algorithm in a method, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm’s structure.

This pattern is all about creating a template for an algorithm. What’s a template? As you’ve seen it’s just a method; more specifically, it’s a method that defines an
algorithm as a set of steps. One or more of these steps is defined to be abstract and implemented by a subclass. This ensures the algorithm’s structure stays unchanged, while subclasses provide some part of the implementation.

Use abstract methods when your subclass MUST provide an implementation of the method or step in the algorithm. Use hooks when that part of the algorithm is optional. With hooks, a subclass may choose to implement that hook, but it doesn’t have to.


### The Hollywood Principle
__ Don’t call us, we’ll call you.__
The Hollywood principle gives us a way to prevent “dependency rot.” Dependency rot happens when you have high-level components depending on low-level components depending on high-level components depending on sideways components depending on low-level components, and so on. When rot sets in, no one can easily understand the way a system is designed.

With the Hollywood Principle, we allow low-level components to hook themselves into a system, but the high-level components determine when they are needed, and how. In other words, the high-level components give the low-level components a “don’t call us, we’ll call you” treatment.

The Dependency Inversion Principle teaches us to avoid the use of concrete classes and instead work as much as possible with abstractions. The Hollywood Principle is a technique for building frameworks or components so that lower-level components can be hooked into the computation, but without creating dependencies between the lower-level components and the higher-level layers. So, they both have the goal of decoupling, but the Dependency Inversion Principle makes a much stronger and general statement about how to avoid dependencies in design. The Hollywood Principle gives us a technique for creating designs that allow low-level structures to interoperate while preventing other classes from becoming too dependent on them. 


### BULLET POINTS
A “template method” defines the steps of an algorithm, deferring to subclasses for the implementation of those steps.
* The Template Method Pattern gives us an important technique for code reuse.
* The template method’s abstract class may define concrete methods, abstract methods and hooks.
* Abstract methods are implemented by subclasses.
* Hooks are methods that do nothing or default behavior in the abstract class, but may be overridden in the subclass.
* To prevent subclasses from changing the algorithm in the template method, declare the template method as final.
* The Hollywood Principle guides us to put decision-making in high-level modules that can decide how and when to call low level modules.
* You’ll see lots of uses of the Template Method Pattern in real world code, but don’t expect it all (like any pattern) to be designed “by the book.”
* The Strategy and Template Method Patterns both encapsulate algorithms, one by inheritance and one by composition.
* The Factory Method is a specialization of Template Method.
