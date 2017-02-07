## Vector clock

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/5/55/Vector_Clock.svg/500px-Vector_Clock.svg.png)

A vector clock is an algorithm for generating a partial ordering of events in a distributed system and detecting causality violations. Just as in __Lamport timestamps__, interprocess messages contain the state of the sending process's logical clock. A vector clock of a system of N processes is an array/vector of N logical clocks, one clock per process; a local "smallest possible values" copy of the global clock-array is kept in each process, with the following rules for clock updates:

Initially all clocks are zero.
* Each time a process experiences an internal event, it increments its own logical clock in the vector by one.
* Each time a process prepares to send a message, it sends its entire vector along with the message being sent.
* Each time a process receives a message, it increments its own logical clock in the vector by one and updates each element in its vector by taking the maximum of the value in its own vector clock and the value in the vector in the received message (for every element).
