## What is Command pattern?

The command pattern is a behavioral design pattern in which an object is used to encapsulate all information needed to perform an action or trigger an event at a later time. This information includes the method name, the object that owns the method and values for the method parameters.
Four terms always associated with the command pattern are command, receiver, invoker and client. 
* A command object knows about receiver and invokes a method of the receiver. Values for parameters of the receiver method are stored in the command. 
* The receiver then does the work. 
* An invoker object knows how to execute a command, and optionally does bookkeeping about the command execution. The invoker does not know anything about a concrete command, it knows only about command interface. Both an invoker object and several command objects are held by a client object. 
* The client decides which commands to execute at which points. To execute a command, it passes the command object to the invoker object.

Let’s step through this. We know that a command object encapsulates a request by binding together a set of actions on a specific receiver. To achieve this, it packages the actions and the receiver up into an object that exposes just one method, execute(). When called, execute() causes the actions to be invoked on the receiver. From the outside, no other objects really know what actions get performed on what receiver; they just know that if they call the execute() method, their request will be serviced.
__The design of the Command Pattern support the decoupling of the invoker of a request and the receiver of the request.__

![alt](http://www.dofactory.com/images/diagrams/net/command.gif)

* The Client is responsible for creating a ConcreteCommand and setting its Receiver.
* The Invoker holds a command and at some point asks the command to carry out a request by calling its execute() method.
* Command declares an interface for all commands. As you already know, a command is invoked through its execute() method, which asks a receiver to perform an action.
* The Receiver knows how to perform the work needed to carry out the request. Any class can act as a Receiver.
* The ConcreteCommand defines a binding between an action and a Receiver. The Invoker makes a request by calling execute() and the ConcreteCommand carries it out by calling one or more actions on the Receiver.

#### BULLET POINTS
* The Command Pattern decouples an object, making a request from the one that knows how to perform it.
* A Command object is at the center of this decoupling and encapsulates a receiver with an action (or set of actions) .
* An invoker makes a request of a Command object by calling its execute() method, which invokes those actions on the receiver.
* Invokers can be parameterized with Commands, even dynamically at runtime.
* Commands may support undo by implementing an undo method that restores the object to its previous state before the execute() method was last called.
* Macro Commands are a simple extension of Command that allow multiple commands to be invoked. Likewise, Macro Commands can easily support undo().
* In practice, it is not uncommon for “smart” Command objects to implement the request themselves rather than delegating to a receiver.
* Commands may also be used to implement logging and transactional systems.

### Intent
Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undoable operations. 

### Participants
1.Command
* declares an interface for executing an operation.

2.ConcreteCommand
* defines a binding between a Receiver object and an action.
* implements Execute by invoking the corresponding operation(s) on Receiver.

3.Client 
* creates a ConcreteCommand object and sets its receiver.

4.Invoker
* asks the command to carry out the request.

5.Receiver
* knows how to perform the operations associated with carrying out a request. Any class may serve as a Receiver. 

**The key to this pattern is an abstract Command class, which declares an interface for executing operations, usually an Execute virtual function. You also need to notice that how the concrete command subclass specify a receiver-action pair by storing the receiver information(usually pointer or reference) and by implementing Execute virtual function to invoke the request through the receiver.**

### Collaborations
* The client creates a ConcreteCommand object and specifies its receiver.
* An Invoker object stores the ConcreteCommand object.
* The invoker issues a request by calling Execute on the command. When commands are undoable, ConcreteCommand stores state for undoing thecommand prior to invoking Execute.
* The ConcreteCommand object invokes operations on its receiver to carryout the request. 

### Pros and cons
Using command objects makes it easier to construct general components that need to delegate, sequence or execute method calls at a time of their choosing without the need to know the class of the method or the method parameters. Using an invoker object allows bookkeeping about command executions to be conveniently performed, as well as implementing different modes for commands, which are managed by the invoker object, without the need for the client to be aware of the existence of bookkeeping or modes.

