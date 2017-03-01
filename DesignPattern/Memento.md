## Intent

* Without violating encapsulation, capture and externalize an object's internal state so that the object can be returned to this state later.
* A magic cookie that encapsulates a "check point" capability.
* Promote undo or rollback to full object status.

## Discussion
The client requests a Memento from the source object when it needs to checkpoint the source object's state. The source object initializes the Memento with a characterization of its state. The client is the "care-taker" of the Memento, but only the source object can store and retrieve information from the Memento (the Memento is "opaque" to the client and all other objects). If the client subsequently needs to "rollback" the source object's state, it hands the Memento back to the source object for reinstatement.

An unlimited "undo" and "redo" capability can be readily implemented with a stack of Command objects and a stack of Memento objects.

The Memento design pattern defines three distinct roles:

* Originator - the object that knows how to save itself.
* Caretaker - the object that knows why and when the Originator needs to save and restore itself.
* Memento - the lock box that is written and read by the Originator, and shepherded by the Caretaker.

![alt](http://www.dofactory.com/images/diagrams/net/memento.gif)


## Rules of thumb
* Command and Memento act as magic tokens to be passed around and invoked at a later time. In Command, the token represents a request; in Memento, it represents the internal state of an object at a particular time. Polymorphism is important to Command, but not to Memento because its interface is so narrow that a memento can only be passed as a value.
* Command can use Memento to maintain the state required for an undo operation.
* Memento is often used in conjunction with Iterator. An Iterator can use a Memento to capture the state of an iteration. The Iterator stores the Memento internally.


## Memento vs Command
The command pattern doesn't necessarily have anything to do with an undo facility (though they like using them). A command is basically a single method wrapped up in an object together with its invocation parameters. Once the command is set up that method can be executed by anyone with access to the execute interface.

The memento on the other hand simply stores information which reflects the current state of the originating class and it does so without revealing any of the state details to the caretaker which stores the memento.

Undo facilities which can simply undo by restoring the originator's previous state use mementos. In some systems however it isn't possible or feasible to store the entire state of the originator (which could be a complex composite). In that case the undo facility can use commands - whenever an action is received a compensating action is set up and stored in the undo facility. To undo you simply execute the commands in LIFO order until you undo all the necessary actions.

* Undo with memento - undo by restoring a snapshot of the originator's state.
* Undo with commands - undo by executing compensating actions.
