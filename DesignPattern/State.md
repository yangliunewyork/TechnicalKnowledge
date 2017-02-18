## What is State pattern?
![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e8/State_Design_Pattern_UML_Class_Diagram.svg/600px-State_Design_Pattern_UML_Class_Diagram.svg.png)
￼
The State Pattern allows an object to alter its behavior when its internal state changes. The object will appear to change its class. 

The first part of this description makes a lot of sense, right? Because the pattern encapsulates state into separate classes and delegates to the object representing the current state, we know that behavior changes along with the internal state.

What about the second part of the definition? What does it mean for an object to “appear to change its class?” Think about it from the perspective of a client: if an object you’re using can completely change its behavior, then it appears to you that the object is actually instantiated from another class. In reality, however, you know that we are using composition to give the appearance of a class change by simply referencing different state objects.

Compare its diagram with Strategy Pattern, they are EXACTLY the same,but the two patterns differ in their __intent__.With the State Pattern, we have a set of behaviors encapsulated in state objects; at any time the context is delegating to one of those states. Over time, the current state changes across the set of state objects to reflect the internal state of the context, so the context’s behavior changes over time as well. The client usually knows very little, if anything, about the state objects.With Strategy, the client usually specifies the strategy object that the context is composed with. Now, while the pattern provides the flexibility to change the strategy object at runtime, often there is a strategy object that is most appropriate for a context object. In general, think of the Strategy Pattern as a flexible alternative to subclassing; if you use inheritance to define the behavior of a class, then you’re stuck with that behavior even if you need to change it. With Strategy you can change the behavior by composing with a different object.Think of the State Pattern as an alternative to putting lots of conditionals in your context; by encapsulating the behaviors within state objects, you can simply change the state object in context to change its behavior.

#### Do clients ever interact directly with the states?
No. The states are used by the Context to represent its internal state and behavior, so all requests to the states come from the Context. Clients don’t directly change the state of the Context. It is the Context’s job
to oversee its state, and you don’t usually want a client changing the state of a Context without that Context’s knowledge.



### Intent
Allow an object to alter its behavior when its internal state changes.The object will appear to change its class. 

###### Also Known As Objects for States 

#### Applicability
Use the State pattern in either of the following cases:
* An object's behavior depends on its state, and it must change its behavior at run-time depending on that state.
* Operations have large, multipart conditional statements that depend onthe object's state. This state is usually represented by one or moreenumerated constants. Often, several operations will contain this same conditional structure. The State pattern puts each branch of theconditional in a separate class. This lets you treat the object'sstate as an object in its own right that can vary independently fromother objects. 


### BULLET POINTS
The State Pattern allows an object to have many different behaviors that are based on its internal state.
* Unlike a procedural state machine, the State Pattern represents state as a full-blown class.
* The Context gets its behavior by delegating to the current state object it is composed with.
* By encapsulating each state into a class, we localize any changes that will need to be made.
* The State and Strategy Patterns have the same class diagram, but they differ in intent.
* Strategy Pattern typically configures Context classes with a behavior or algorithm. State Pattern allows a Context to change its behavior as the state of the Context changes.
* State transitions can be controlled by the State classes or by the Context classes.
* Using the State Pattern will typically result in a greater number of classes in your design.
* State classes may be shared among Context instances.

### State Pattern vs Strategy Pattern
* The strategy pattern decides on 'how' to perform some action and state pattern decides on 'when' to perform them.
  * By using the State pattern the state-holding (context) class is relieved from knowledge of what state or type it is and what states or types that are available. This means that the class adheres to the open-closed design principle (OCP): the class is closed for changes in what states/types there are, but the states/types are open to extensions.
  * By using the Strategy pattern the algorithm-using (context) class is relieved from knowledge of how to perform a certain task (-- the "algorithm"). This case also creates an adherence to the OCP; the class is closed for changes regarding how to perform this task, but the design is very open to additions of other algorithms for solving this task.
* The state and strategy patterns are similar in the sense that both of them encapsulate behavior in separate objects and use composition to delegate to the composed object to implement the behavior and both of them provide the flexibility to change the behavior dynamically by changing the composed object at run-time. But there are some key differences :
  * In the state pattern, the client knows nothing about the state objects. State changes happen transparently to the client. The client just calls methods on the context, the context oversees its own state. Because the client is not aware of the state changes, it appears to the client as though the context is instantiated from a different class each time there is a change in behavior due to a state change. The object will appear to change its class as the official definition of the pattern states. The pattern is built around a well-defined series of state transitions. Changing state is key to the pattern's existence.
  * Even though the strategy pattern provides the flexibility to change behavior by changing the composed strategy object dynamically, mostly there is an appropriate strategy object already set for each context. ie even though the pattern provides a way to change the composed strategy object dynamically, there won't be much of a need for it. Even if it has to be done, it is the client that does the change. The client will call the setter method on the context and pass the new strategy object. Thus behavior changes are NOT transparent to the client and are initiated and controlled by the client. The pattern does not encourage a series of well-defined behavior changes like the state pattern. The client knows about the strategy objects and will usually set the appropriate strategy object in the context while creating it. The client controls what strategy object the context uses, but in the state pattern, the client knows nothing about the state object(s) that the context uses.
* The difference simply lies in that they solve different problems:
 * The State pattern deals with what (state or type) an object is (in) -- it encapsulates state-dependent behavior, whereas
the Strategy pattern deals with how an object performs a certain task -- it encapsulates an algorithm.The constructs for achieving these different goals are however very similar; both patterns are examples of composition with delegation.
