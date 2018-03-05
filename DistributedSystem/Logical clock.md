A __logical clock__ is a mechanism for capturing chronological and causal relationships in a distributed system. Distributed systems may have no physically synchronous global clock, so a logical clock allows global ordering on events from different processes in such systems. The first implementation, the Lamport timestamps, was proposed by Leslie Lamport in 1978.

In logical clock systems each process has two data structures: logical local time and logical global time. Logical local time is used by the process to mark its own events, and logical global time is the local information about global time. A special protocol is used to update logical local time after each local event, and logical global time when processes exchange data.[1]

Logical clocks are useful in computation analysis, distributed algorithm design, individual event tracking, and exploring computational progress.

Some noteworthy logical clock algorithms are:

* __Lamport timestamps__, which are monotonically increasing software counters.
* __Vector clocks__, that allow for partial ordering of events in a distributed system.
* __Version vectors__, order replicas, according to updates, in an optimistic replicated system.
* __Matrix clocks__, an extension of vector clocks that also contains information about other processes' views of the system.
