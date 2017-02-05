## Reference

* http://ksat.me/a-plain-english-introduction-to-cap-theorem/
* http://robertgreiner.com/2014/08/cap-theorem-revisited/
* https://martin.kleppmann.com/2015/05/11/please-stop-calling-databases-cp-or-ap.html

## What Is CAP Theorem ?
In theoretical computer science, the CAP theorem states that it is impossible for a __distributed computer system__ to simultaneously provide more than two out of three of the following guarantees:
* Consistency	 
  * Every read receives the most recent write or an error. All the servers in the system will have the same data so anyone using the system will get the same copy regardless of which server answers their request.
* Availability
  * Every request receives a (non-error) response – without guarantee that it contains the most recent write. The system will always respond to a request (even if it's not the latest data or consistent across the system or just a message saying the system isn't working).
* Partition tolerance 
  * The system continues to operate despite an arbitrary number of messages being dropped (or delayed) by the network between nodes

  
__In other words, the CAP Theorem states that in the presence of a network partition, one has to choose between consistency and availability.__ Note that consistency as defined in the CAP Theorem is quite different from the consistency guaranteed in ACID database transactions.


## Explanation
No distributed system is safe from network failures, thus __network partitioning__ generally has to be tolerated. In the presence of a partition, one is then left with two options: consistency or availability. When choosing consistency over availability, the system will return an error or a time out if particular information cannot be guaranteed to be up to date due to network partitioning. When choosing availability over consistency, the system will always process the query and try to return the most recent available version of the information, even if it cannot guarantee it is up to date due to network partitioning.

In the absence of network failure – that is, when the distributed system is running normally – both availability and consistency can be satisfied.

CAP is frequently misunderstood as if one had to choose to abandon one of the three guarantees at all times. In fact, the choice is really between consistency and availability for when a partition happens only; at all other times, no trade-off has to be made.

Database systems designed with traditional __ACID__ guarantees in mind such as RDBMS choose consistency over availability, whereas systems designed around the __BASE__ philosophy, common in the NoSQL movement for example, choose availability over consistency.

The PACELC theorem builds on CAP by stating that even in the absence of partitioning, another trade-off between latency and consistency occurs.

