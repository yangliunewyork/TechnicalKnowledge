In software development, functions that span multiple points of an application are called __cross-cutting concerns__. Typically, these cross-cutting concerns are conceptually separate from (but often embedded directly within) the application’s business logic. Separating these cross-cutting concerns from the business logic is where __aspectoriented programming (AOP)__ goes to work.

## 4.1 What is aspect-oriented programming?

As stated earlier, aspects help to modularize cross-cutting concerns. In short, a crosscutting concern can be described as any functionality that affects multiple points of an application. Security, for example, is a cross-cutting concern, in that many methods in an application can have security rules applied to them.

This figure represents a typical application that’s broken down into modules. Each module’s main concern is to provide services for its particular domain. But each module also requires similar ancillary functionality, such as security and transaction management.

![alt](http://apprize.info/javascript/spring_1/spring_1.files/image037.jpg)

A common object-oriented technique for reusing common functionality is to apply inheritance or delegation. But inheritance can lead to a brittle object hierarchy if the same base class is used throughout an application, and delegation can be cumbersome because complicated calls to the delegate object may be required.

Aspects offer an alternative to inheritance and delegation that can be cleaner in many circumstances. With AOP, you still define the common functionality in one place, but you can declaratively define how and where this functionality is applied without having to modify the class to which you’re applying the new feature. Crosscutting concerns can now be modularized into special classes called __aspects__. This has two benefits. First, the logic for each concern is in one place, as opposed to being scattered all over the code base. Second, your service modules are cleaner because they only contain code for their primary concern (or core functionality), and secondary concerns have been moved to aspects.

### 4.1.1 Defining AOP terminology

##### ADVICE

Advice defines both the what and the when of an aspect. In addition to describing the job that an aspect will perform, advice addresses the question of when to perform the job. Should it be applied before a method is invoked? After the method is invoked? Both before and after method invocation? Or should it be applied only if a method throws an exception?

Spring aspects can work with five kinds of advice:

Spring aspects can work with five kinds of advice: 

* Before : The advice functionality takes place before the advised method is invoked. 
* After : The advice functionality takes place after the advised method completes, regardless of the outcome. 
* After-returning : The advice functionality takes place after the advised method successfully completes. 
* After-throwing : The advice functionality takes place after the advised method throws an exception. 
* Around : The advice wraps the advised method, providing some functionality before and after the advised method is invoked.

##### JOIN POINTS

An electric company services several houses, perhaps even an entire city. Each house has an electric meter that needs to be read, so each house is a potential target for the meter reader. The meter reader could potentially read all kinds of devices, but to do her job, she needs to target electric meters that are attached to houses.

In the same way, your application may have thousands of opportunities for advice to be applied. These opportunities are known as join points. A __join point__ is a point in the execution of the application where an aspect can be plugged in. This point could be a method being called, an exception being thrown, or even a field being modified. These are the points where your aspect's code can be inserted into the normal flow of your application to add new behavior.

##### POINTCUTS

It’s not possible for any one meter reader to visit all houses serviced by the electric company. Instead, each one is assigned a subset of all the houses to visit. Likewise, an aspect doesn’t necessarily advise all join points in an application. __Pointcuts__ help narrow down the join points advised by an aspect.

If advice defines the what and when of aspects, then pointcuts define the where. A pointcut definition matches one or more join points at which advice should be woven. Often you specify these pointcuts using explicit class and method names or through regular expressions that define matching class and method name patterns. Some AOP frameworks allow you to create dynamic pointcuts that determine whether to apply advice based on runtime decisions, such as the value of method parameters.

##### ASPECTS

When a meter reader starts his day, he knows both what he’s supposed to do (report electricity usage) and which houses to collect that information from. Thus he knows everything he needs to know to get his job done.

An __aspect__ is the merger of advice and pointcuts. Taken together, advice and pointcuts define everything there is to know about an aspect—what it does and where and when it does it.

##### INTRODUCTIONS

An __introduction__ allows you to add new methods or attributes to existing classes. For example, you could create an Auditable advice class that keeps the state of when an object was last modified. This could be as simple as having one method, setLast- Modified(Date), and an instance variable to hold this state. The new method and instance variable can then be introduced to existing classes without having to change them, giving them new behavior and state.

##### WEAVING

__Weaving__ is the process of applying aspects to a target object to create a new proxied object. The aspects are woven into the target object at the specified join points. The weaving can take place at several points in the target object’s lifetime:

* Compile time : Aspects are woven in when the target class is compiled. This requires a special compiler. AspectJˇs weaving compiler weaves aspects this way.   
* Class load time : Aspects are woven in when the target class is loaded into the JVM. This requires a special ClassLoader that enhances the target classˇs bytecode before the class is introduced into the application. AspectJ 5ˇs load-time weaving (LTW) support weaves aspects this way.   
* Runtime : Aspects are woven in sometime during the execution of the application. Typically, an AOP container dynamically generates a proxy object that delegates to the target object while weaving in the aspects. This is how Spring AOP aspects are woven.  







