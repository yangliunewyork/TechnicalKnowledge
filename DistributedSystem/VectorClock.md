A very good tutorial : https://www.youtube.com/watch?v=jD4ECsieFbE

Firstly, as others have pointed out, using the physical timestamp of a record is no good because you can't guarantee that time will move forward in a uniform manner across all nodes in the cluster, which means a 'later' record might have an earlier timestamp than some record produced before it.

You could instead use a logical timestamp, otherwise known as a Lamport Clock. A Lamport Clock is a single integer value that is passed around the cluster with every message sent between nodes. Each node keeps a record of what it thinks the latest (i.e. highest) Lamport Clock value is, and if it hears a larger value from some other node, it updates its own value.

Every time a database record is produced, the producing node can attach the current Lamport Clock value + 1 to it as a timestamp. This sets up a total ordering on all records with the valuable property that if record A may causally precede record B, then A's timestamp < B's timestamp. 

By 'causally precede', I mean that the node that produced A may have sent some messages which caused another node to send messages which caused another node to... etc. until the node that produced B receives a message, before it actually creates B, which may have originated at A. The idea being that we want to capture whether the production of A may have influenced B at all, and we do that by tagging this timestamp on to all messages we send, which are the only mechanisms we have for affecting the behaviour of other nodes in the system.

So Lamport Clocks are great for making sure we know when there's a causal dependency between records. But there is a problem. Because Lamport Clocks induce a total ordering over all records, they actually imply more dependencies than truly exist. If two records are not causally related at all, and were produced completely independently by separate nodes that did not communicate, they will still have Lamport Clock timestamps which imply that one is ordered before the other, which is a false positive. For some applications this is fine, but not for Dynamo.

The reason is that Dynamo wants to know if two messages cannot possibly be causally related. This situation, which Lamport Clocks can not detect, arises in Dynamo when there is the possibility of a conflict between two record versions, arising perhaps due to a partition. So instead we need a timestamp type that admits only a partial ordering, so we can detect when two timestamps are not ordered with respect to each other. 

Vector clocks allow us to do that. Roughly speaking, a VC timestamp A is less than a VC timestamp B if all members of A are less than or equal to their counterpart in B. So we can detect causal dependency. But if some but not all of the individual timestamps in A are less-than-or-equal-to, and some are greater than their counterparts in B, A and B cannot be causally related.

Of course, it's the way that the individual timestamps get incremented in Vector Clocks that give rise to this property; you can't just pick a datatype and a partial ordering and assume that this will work. But VCs can be viewed simply as an array of Lamport Clocks, one per node, and so simply and elegantly generalise Lamport Clocks at the cost of space to store them.

## Vector clock

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/5/55/Vector_Clock.svg/500px-Vector_Clock.svg.png)

A vector clock is an algorithm for generating a partial ordering of events in a distributed system and detecting causality violations. Just as in __Lamport timestamps__, interprocess messages contain the state of the sending process's logical clock. A vector clock of a system of N processes is an array/vector of N logical clocks, one clock per process; a local "smallest possible values" copy of the global clock-array is kept in each process, with the following rules for clock updates:

Initially all clocks are zero.
* Each time a process experiences an internal event, it increments its own logical clock in the vector by one.
* Each time a process prepares to send a message, it sends its entire vector along with the message being sent.
* Each time a process receives a message, it increments its own logical clock in the vector by one and updates each element in its vector by taking the maximum of the value in its own vector clock and the value in the vector in the received message (for every element).
