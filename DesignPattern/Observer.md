## What is Observer Pattern ?

![alt](http://www.bogotobogo.com/DesignPatterns/images/observer/observer_pattern.gif)

__Publishers + Subscribers = Observer Pattern__

If you understand newspaper subscriptions, you pretty much understand the Observer Pattern, only we call the publisher the SUBJECT and the subscribers the OBSERVERS.When you’re trying to picture the Observer Pattern, a newspaper subscription service with its publisher and subscribers is a good way to visualize the pattern. In the real world however, you’ll typically see the Observer Pattern defined like this:

> The Observer Pattern defines a one-to-many dependency between objects so that when one object changes state, all of its dependents are notified and updated automatically.

#### The power of Loose Coupling
__When two objects are loosely coupled, they can interact, but have very little knowledge of each other.The Observer Pattern provides an object design where subjects and observers are loosely coupled.__

__The only thing the subject knows about an observer is that it implements a certain interface (the Observer interface).__ It doesn’t need to know the concrete class of the observer, what it does, or anything else about it.

__We can add new observers at any time.__ Because the only thing the subject depends on is a list of objects that implement the Observer interface, we can add new observers whenever we want. In fact, we can replace any observer at runtime with another observer and the subject will keep purring along. Likewise, we can remove observers at any time.

__We never need to modify the subject to add new types of observers.__ Let’s say we have a new concrete class come along that needs to be an observer. We don’t need to make any changes to the subject to accommodate the new class type, all
we have to do is implement the Observer interface in the new class and register as an observer. The subject doesn’t care; it will deliver notifications to any object that implements the Observer interface.

__We can reuse subjects or observers independently of each other.__ If we have another use for a subject or an observer, we can easily reuse them because the two aren’t tightly coupled.

__Changes to either the subject or an observer will not affect the other.__ Because the two are loosely coupled, we are free to make changes to either, as long as the objects still meet their obligations to implement the subject or observer interfaces.

__Loosely coupled designs allow us to build flexible OO systems that can handle change because they minimize the interdependency between objects.__




## Summary
### Intent
Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically. 

### Applicability
Use the Observer pattern in any of the following situations:
  * When an abstraction has two aspects, one dependent on the other.Encapsulating these aspects in separate objects lets you vary and reuse them independently.
  * When a change to one object requires changing others, and you don't know how many objects need to be changed.
  * When an object should be able to notify other objects without making assumptions about who these objects are. In other words, you don'twant these objects tightly coupled. 

### Participants
1. Subject
  * knows its observers. Any number of Observer objects may observe a subject.
  * provides an interface for attaching and detaching Observer objects.
2. Observer
  * defines an updating interface for objects that should be notified of changes in a subject.
3.ConcreteSubject
  * stores state of interest to ConcreteObserver objects.
  * sends a notification to its observers when its state changes.
4.ConcreteObserver
  * maintains a reference to a ConcreteSubject object.
  * stores state that should stay consistent with the subject's.
  * implements the Observer updating interface to keep its state consistent with the subject's. 
  
### Collaborations
* ConcreteSubject notifies its observers whenever a change occurs that could make its observers' state inconsistent with its own.
* After being informed of a change in the concrete subject, a ConcreteObserver object may query the subject for information.ConcreteObserver uses this information to reconcile its state with thatof the subject. 
