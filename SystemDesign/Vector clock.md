<img src = "https://upload.wikimedia.org/wikipedia/commons/5/55/Vector_Clock.svg">

A vector clock is an algorithm for generating a __partial ordering__ of events in a distributed system and detecting causality violations. Just as in __Lamport timestamps__, interprocess messages contain the state of the sending process's __logical clock__. __A vector clock of a system of N processes is an array/vector of N logical clocks, one clock per process__; a local "smallest possible values" copy of the global clock-array is kept in each process, with the following rules for clock updates:

* Initially all clocks are zero.  
* Each time a process experiences an internal event, it increments its own logical clock in the vector by one.  
* Each time a process sends a message, it increments its own logical clock in the vector by one (as in the bullet above) and then sends a copy of its own vector.  
* Each time a process receives a message, it increments its own logical clock in the vector by one and updates each element in its vector by taking the maximum of the value in its own vector clock and the value in the vector in the received message (for every element).  

The vector clocks algorithm was independently developed by Colin Fidge and Friedemann Mattern in 1988.

> Causality (also referred to as causation, or cause and effect) is the natural or worldly agency or efficacy that connects one process (the cause) with another process or state (the effect), where the first is partly responsible for the second, and the second is partly dependent on the first.



##### Why do distributed databases, such as Dynamo and Voldemort, choose the Vector Clock to control the ordering of multi-version records? What’s the advantage? Why not choose the direct timestamp of each record?

Timestamps are not reliable given the clock skew, timezone interpretation risks and granularity.

Using the physical timestamp of a record is no good because you can't guarantee that time will move forward in a uniform manner across all nodes in the cluster, which means a 'later' record might have an earlier timestamp than some record produced before it.

You could instead use a logical timestamp, otherwise known as a Lamport Clock. A Lamport Clock is a single integer value that is passed around the cluster with every message sent between nodes. Each node keeps a record of what it thinks the latest (i.e. highest) Lamport Clock value is, and if it hears a larger value from some other node, it updates its own value.

Every time a database record is produced, the producing node can attach the current Lamport Clock value + 1 to it as a timestamp. This sets up a total ordering on all records with the valuable property that if record A may causally precede record B, then A's timestamp < B's timestamp. 

By 'causally precede', I mean that the node that produced A may have sent some messages which caused another node to send messages which caused another node to... etc. until the node that produced B receives a message, before it actually creates B, which may have originated at A. The idea being that we want to capture whether the production of A may have influenced B at all, and we do that by tagging this timestamp on to all messages we send, which are the only mechanisms we have for affecting the behaviour of other nodes in the system.

So Lamport Clocks are great for making sure we know when there's a causal dependency between records. But there is a problem. Because Lamport Clocks induce a total ordering over all records, they actually imply more dependencies than truly exist. If two records are not causally related at all, and were produced completely independently by separate nodes that did not communicate, they will still have Lamport Clock timestamps which imply that one is ordered before the other, which is a false positive. For some applications this is fine, but not for Dynamo.

The reason is that Dynamo wants to know if two messages cannot possibly be causally related. This situation, which Lamport Clocks can not detect, arises in Dynamo when there is the possibility of a conflict between two record versions, arising perhaps due to a partition. So instead we need a timestamp type that admits only a partial ordering, so we can detect when two timestamps are not ordered with respect to each other. 

Vector clocks allow us to do that. Roughly speaking, a VC timestamp A is less than a VC timestamp B if all members of A are less than or equal to their counterpart in B. So we can detect causal dependency. But if some but not all of the individual timestamps in A are less-than-or-equal-to, and some are greater than their counterparts in B, A and B cannot be causally related.

Of course, it's the way that the individual timestamps get incremented in Vector Clocks that give rise to this property; you can't just pick a datatype and a partial ordering and assume that this will work. But VCs can be viewed simply as an array of Lamport Clocks, one per node, and so simply and elegantly generalise Lamport Clocks at the cost of space to store them.



### Version Vectors are not Vector Clocks

Most people still confuse __Version Vectors__ and __Vector Clocks__. Well, I did confuse them for several years. In fact they look the same and the update rules are almost the same.

Both of these mechanisms are practical ways of capturing causality in distributed systems. Causality (in distributed systems) is an abstract concept, can was formalized in 1978 by Leslie Lamport in one of the most cited  articles in computer science. In 1983 Version Vectors are developed to track the causal relations among data items that can be concurrently updated. Some years later, around 1988, Vector Clocks are developed to track the causality between events in a distributed computation. In both cases a vector of integers, one per source of concurrency, is used. There is, however, a fundamental difference.

First, in order to simplify a little bit, lets consider that we have a fixed number of processes and a fixed number of replicas. 

* __Vector Clocks need to establish a partial order among a, potentially ever growing, set of events occurring in the processes.__ The set of events that are generated in the distributed computation. Naturally since the set can grow unbounded, the tracking mechanism also needs to grow unbounded. Vectors of integers are fine since, at least in theory we don’t run out of integers. In 1991, Charron-Bost showed in this article that Vector Clocks are the smaller mechanism that can track causality among distributed events.

* __Version Vectors need to establish a partial order (more precisely a pre-order) among the replicas in the distributed system.__ Notice that although the state in these replicas changes as consequence of ever growing sets of update events, here we want to relate the replica states and not the update events. Using vectors of integers is over-expressive in this setting. In 2004, we noticed this and constructed Bounded Version Vectors, where integers are substituted by a limited set of symbols, depending on the number of replicas. Naturally, Charron-Bost result does not apply to Version Vectors.

Lets consider a simple example, thats shows that vectors of integers are over-expressive . One has two recently synchronized replicas A and B with identical state and vectors A[2,3] and B[2,3]. Now, replica A suffers an update and its new vector is A[3,3]. We now see that A is more updated than B, since [3,3] > [2,3] (here each integer in the left is greater or equal than its counterpart in the same position). Now replica A suffers 7 more updates, A[10,3]. Still we have [10,3] > [2,3], and this increase in the integer does not convey more information to the task of tracking the causal order among the two replicas. The number of individual updates is typically not important, specially in systems where you can change either a lot or a little in a single update. What is important is how they change the causal order relation among the replicas.

In the example, at this point, we can compare A[10,3] and B[2,3] and notice that they are easy to synchronize since A has the most updated state and it can be simply copied into B. However, if B issues an update and we now have a system with A[10,3] and B[2,4]. Now the replicas are divergent and a synchronization will typically have to look at the state (often with user assistance)  to figure the correct synchronized state that can be tagged with [10,4].

The message is, use the right tools and know the differences. Vector Clocks are great to implement causal delivery middleware, consistent snapshots, and the like. But for replicated data, Version Vectors are the right concept, and several mechanisms can make use of the subtle differences.


