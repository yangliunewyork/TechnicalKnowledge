The notes comes from this book : https://www.amazon.com/Designing-Data-Intensive-Applications-Reliable-Maintainable/dp/1449373321 , one of the best in this field.

Replication means keeping a copy of the same data on multiple machines that are connected via a network. There are several reasons why you might want to replicate data:

* To keep data geographically close to your users (and thus reduce latency)
* To allow the system to continue working even if some of its parts have failed (and thus increase availability)
* To scale out the number of machines that can serve read queries (and thus increase read throughput)

If the data that you’re replicating does not change over time, then replication is easy: you just need to copy the data to every node once, and you’re done. All of the difficulty in replication lies in handling changes to replicated data, and that’s what this chapter is about. We will discuss three popular algorithms for replicating changes between nodes: __single-leader__, __multi-leader__, and __leaderless__ replication. Almost all distributed databases use one of these three approaches. They all have various pros and cons, which we will examine in detail.

There are many trade-offs to consider with replication: for example, whether to use synchronous or asynchronous replication, and how to handle failed replicas. Those are often configuration options in databases, and although the details vary by data‐ base, the general principles are similar across many different implementations. 

## Leaders and Followers

