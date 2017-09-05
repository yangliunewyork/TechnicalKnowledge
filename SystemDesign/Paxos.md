* https://www.quora.com/In-distributed-systems-what-is-a-simple-explanation-of-the-Paxos-algorithm

I think it is easier to understand Paxos in context of other solutions that try to solve the consensus problem but have shortcomings, so let’s talk about that.

An intuitive way of reaching consensus is to take marriage vows:
```
“Do you …?” “I do!” “I do!”
“I now pronounce you …”
```

Assume now that the marriage is not between two people, but is a bit like what happens among the Aiel folk in Robert Jordan’s Wheel of Time Series – one or more Aiel women can be first-sisters and either the man has to marry them all, or none at all. Among the Aiel, the marriage vows would perhaps work as follows:

```
“Do you …?” “I do!” “I do!” “I do!” …
“I now pronounce you …”
```

If any of the Aiel would-be-spouses does not respond with an “I do!” the wedding cannot proceed.

Computer scientists call this the two-phase commit.

##### Two Phase Commit (2PC)

* Voting Phase – A coordinator suggests a value to all nodes and gathers their responses (whether they agree to the value or not). For our scenario, a transaction coordinator asks whether all resource managers (database server instances) can commit to a transaction or not. The RMs reply with a yes or no.  
* Commit Phase - If everyone agrees, the coordinator contacts all nodes to let them know the value is final. If even one node does not agree, inform all nodes that the value is not final. In our scenario, the coordinator asks the RMs to commit the transaction or abort it.  

Note that the vote is only on the proposed value – a node can only say yes or no. It cannot suggest an alternative. If a node wants to suggest a value, it should start its own 2PC. Clearly the algorithm works – the nodes decide on a value proposed by one of the nodes. It is also not very inefficient – for N nodes, 3N messages are exchanged.

But what happens if a node crashes? For example, assume that the coordinator crashes in phase 1 after the proposal has been sent to some of the N nodes, but not all.

* Now some nodes have started a 2PC round, while some nodes are unaware of a 2PC round happening. The ones who have started the 2PC round are blocked waiting for the next phase.
* In our scenario, a RM that has voted may also have had to lock some resources so it cannot even time out since the coordinator may recover and start phase 2.

Similar problems exist if the coordinator crashes in phase 2 after it has sent commit message to some nodes but not to all nodes. Some of these problems can be solved by having another node take over coordination duties on observing a timeout. This node can get in touch with all the other nodes to discover their votes (requires nodes to persist votes) and take the transaction to completion, but further participant failures can happen during this process and the transaction may never recover. __Bottomline – 2PC cannot operate reliably in the event of node failure.__

##### Three Phase Commit (3PC)

__The key issue with 2PC is that in case the coordinator crashes, there is no one else who has the knowledge to complete the protocol. This can be solved by the addition of an extra step:

1. Phase 1 – same as before – a coordinator suggests a value to all nodes.  
2. Phase 2 – new step – on receiving a yes from all nodes in previous step, the coordinator sends a “prepare to commit” message. The expectation is that nodes can perform work that they can undo, but nothing which cannot be undone. Each node acknowledges to the coordinator that it has received a “prepare to commit” message.  
3. Phase 3 – similar to second phase in 2PC – If the coordinator receives an acknowledgement from all nodes on the “prepare to commit,” it can go ahead and communicate the result of the vote to all nodes asking them to commit. However, if all nodes do not acknowledge, the coordinator aborts the transaction.  

Now if the coordinator crashes at any point, any participant can take over the role and query the state from other nodes.

* If any RM reports to the recovery node that it has not received the “prepare to commit” message, the recovery node knows that the transaction has not been committed at any RM. Now either the transaction can be pessimistically aborted, or the protocol instance can be re-run.
* If a RM that has committed the transaction crashes, we know that every other RM would have received and acknowledged the “prepare to commit” message since otherwise the coordinator would not have moved to the commit phase. So the coordinator can proceed with the last phase.

So 3PC works well despite node failures. This is at the cost of adding one more step across N nodes which results in higher latencies.

Where 3PC falls short is in the event of a network partition. Assume that all RMs that received “prepared to commit” are on one side of the partition, and the rest are on the other side. Now this will result in each partition electing a recovery node that would either commit or abort the transaction. Once the network partition gets removed, the system gets in an inconsistent state.

Paxos - Why Bother?

First things first – given 3PC do we even need something better? The only problem is network partition, right? To begin with, let’s assume that network partition is the only problem (it is not, as we shall soon see). Is correctness in the event of network partition a problem worth solving? Today, with cloud computing and internet-scale services where nodes may be on different sides of a continent or across oceans, we certainly need a partition tolerant algorithm.

The second point is that network partition is not the only problem. While we tackled the case of a node failing permanently, the more general case is that the node crashes, then recovers and resumes from where it left. This fail-recover model can also describe an asynchronous network model where there is no upper bound on amount of time a node can take to respond to a message, since you can never assume a node to be dead – they may just be slow or the network may be slow. You cannot timeout in this model.

3PC is fail-stop resilient, but not fail-recover resilient. Unfortunately real life requires fail-recover and hence we need a more general solution. This is where Paxos comes in.





