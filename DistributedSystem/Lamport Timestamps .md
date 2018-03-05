A very good tutorial is here: https://www.youtube.com/watch?v=CMBjvCzDVkY

The algorithm of __Lamport timestamps__ is a simple algorithm used to determine the order of events in a distributed computer system. As different nodes or processes will typically not be perfectly synchronized, this algorithm is used to provide a __partial ordering__ of events with minimal overhead, and conceptually provide a starting point for the more advanced vector clock method. They are named after their creator, Leslie Lamport.

Distributed algorithms such as resource synchronization often depend on some method of ordering events to function. For example, consider a system with two processes and a disk. The processes send messages to each other, and also send messages to the disk requesting access. The disk grants access in the order the messages were sent. For example process {\displaystyle A} A sends a message to the disk requesting write access, and then sends a read instruction message to process {\displaystyle B} B. Process {\displaystyle B} B receives the message, and as a result sends its own read request message to the disk. If there is a timing delay causing the disk to receive both messages at the same time, it can determine which message happened-before the other: {\displaystyle A} A happens-before {\displaystyle B} B if one can get from {\displaystyle A} A to {\displaystyle B} B by a sequence of moves of two types: moving forward while remaining in the same process, and following a message from its sending to its reception. A logical clock algorithm provides a mechanism to determine facts about the order of such events.

Lamport invented a simple mechanism by which the happened-before ordering can be captured numerically. A Lamport logical clock is an incrementing software counter maintained in each process.

Conceptually, this logical clock can be thought of as a clock that only has meaning in relation to messages moving between processes. When a process receives a message, it resynchronizes its logical clock with that sender. The abovementioned vector clock is a generalization of the idea into the context of an arbitrary number of parallel, independent processes.

> Causal ordering : For any two events,  ```a``` and ```b```, if there’s any way that  ```a``` could have influenced ```b```, then the Lamport timestamp of ```a``` will be less than the Lamport timestamp of ```b```. It’s also possible to have two events where we can’t say which came first; when that happens, it means that they couldn’t have affected each other. If ```a``` and ```b``` can’t have any affect on each other, then it doesn’t matter which one came first.

### Algorithm

The algorithm follows some simple rules:

* A process increments its counter before each event in that process;
* When a process sends a message, it includes its counter value with the message;
* On receiving a message, the counter of the recipient is updated, if necessary, to the greater of its current counter and the timestamp in the received message. The counter is then incremented by 1 before the message is considered received.

In pseudocode, the algorithm for sending is:

```
time = time + 1;
time_stamp = time;
send(message, time_stamp);
```

The algorithm for receiving a message is:

```
(message, time_stamp) = receive();
time = max(time_stamp, time) + 1;
```

