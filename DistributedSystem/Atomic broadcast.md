In fault-tolerant distributed computing, an __atomic broadcast__ or __total order broadcast__ is a broadcast where all correct processes in a system of multiple processes deliver the same set of messages in the same order; that is, the same sequence of messages. The broadcast is termed "atomic" because it either eventually completes correctly at all participants, or all participants abort without side effects. Atomic broadcasts are an important distributed computing primitive.

### Properties

The following properties are usually required from an atomic broadcast protocol:

* Validity: if a correct participant broadcasts a message, then all correct participants will eventually deliver it.
* Uniform Agreement: if one correct participant delivers a message, then all correct participants will eventually deliver that message.
* Uniform Integrity: a message is delivered by each participant at most once, and only if it was previously broadcast.
* Uniform Total Order: the messages are totally ordered in the mathematical sense; that is, if any correct participant delivers message 1 first and message 2 second, then every other correct participant must deliver message 1 before message 2.

Note that total order is not equivalent to FIFO order, which requires that if a process sent message 1 before it sent message 2, then all participants must deliver message 1 before delivering message 2. It is also not equivalent to "causal order", where message 2 "depends on" or "occurs after" message 1 then all participants must deliver message 2 after delivering message 1. While a strong and useful condition, total order requires only that all participants deliver the messages in the same order, but does not place other constraints on that order.

### Fault Tolerance

Designing an algorithm for atomic broadcasts is relatively easy if it can be assumed that computers will not fail. For example, if there are no failures, atomic broadcast can be achieved simply by having all participants communicate with one "leader" which determines the order of the messages, with the other participants following the leader.

However, real computers are faulty; they fail and recover from failure at unpredictable, possibly inopportune, times. For example, in the follow-the-leader algorithm, what if the leader fails at the wrong time? In such an environment achieving atomic broadcasts is difficult. A number of protocols have been proposed for performing atomic broadcast, under various assumptions about the network, failure models, availability of hardware support for multicast, and so forth.

### Equivalent to Consensus

In order for the conditions for atomic broadcast to be satisfied, the participants must effectively "agree" on the order of delivery of the messages. Participants recovering from failure, after the other participants have "agreed" an order and started to deliver the messages, must be able to learn and comply with the agreed order. Such considerations indicate that in systems with crash failures, atomic broadcast and consensus are equivalent problems.


A value can be proposed by a process for consensus by atomically broadcasting it, and a process can decide a value by selecting the value of the first message which it atomically delivers. Thus, consensus can be reduced to atomic broadcast.

Conversely, a group of participants can atomically broadcast messages by achieving consensus regarding the first message to be delivered, followed by achieving consensus on the next message, and so forth until all the messages have been delivered. Thus, atomic broadcast reduces to consensus. 
