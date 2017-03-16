## Basic key-value storage
How would you design a simple key-value storage system in a single machine?

The most straightforward thing is to use a hash table to store key-value pairs, which is how most this kind of systems work nowadays. A hash table allows you to read/write a key-value pair in constant time and it’s extremely easy to use. Most languages have built-in support for this.

However, the downside is also obvious. Using a hash table usually means you need to store everything in memory, which may not be possible when the data set is big. There are two common solutions:

* Compress your data. This should be the first thing to think about and often there are a bunch of stuff you can compress. For example, you can store reference instead of the actual data. You can also use float32 rather than float64. In addition, using different data representations like bit array (integer) or vectors can be effective as well.
* Storing in a disk. When it’s impossible to fit everything in memory, you may store part of the data into disk. To further optimize this, you can think of the system as a cache system. Frequently visited data is kept in memory and the rest is on a disk.

## Distributed key-value storage
The most interesting topic is definitely scaling the key-value storage into multiple machines. If you want to support big data, you will implement distributed system for sure. Let’s see how we can design a distributed key-value storage system.

Since a single machine doesn’t have enough storage for all the data, the general idea here is to split the data into multiple machines by some rules and a coordinator machine can direct clients to the machine with requested resource. The question is how to split the data into multiple machines and more importantly, what is a good strategy to partition data?

## Sharding
Suppose all the keys are URLs like http://gainlo.co and we have 26 machines. One approach is to divide all keys (URLs) based on the first character of the URL (after “www”) to these 26 machines. For example, http://gainlo.co will be stored at machine G and http://blog.gainlo.co will be stored at machine B. So what are disadvantages of this design?

Let’s ignore cases where URL contains ASCII characters. A good sharding algorithm should be able to balance traffic equally to all machines. In other words, each machine should receive equal requests ideally. Apparently, the above design doesn’t work well. First of all, the storage is not distributed equally. Probably there are much more URLs starting with “a” than “z”. Secondly, some URLs are much more popular like Facebook and Google.

In order to balance the traffic, you’d better make sure that keys are distributed randomly. Another solution is to use the hash of URL, which usually have much better performance. To design a good sharding algorithm, you should fully understand the application and can estimate the bottleneck of the system.

## System availability
To evaluate a distributed system, one key metric is system availability. For instance, suppose one of our machines crashes for some reason (maybe hardware issue or program bugs), how does this affect our key-value storage system?

Apparently, if someone requests resources from this machine, we won’t be able to return the correct response. You may not consider this issue when building a side project. However, if you are serving millions of users with tons of servers, this happens quite often and you can’t afford to manually restart the server every time. This is why availability is essential in every distributed system nowadays. So how would you address this issue?

Of course you can write more robust code with test cases. However, your program will always have bugs. In addition, hardware issues are even harder to protect. The most common solution is replica. By setting machines with duplicate resources, we can significantly reduce the system downtime. If a single machine has 10% of chance to crash every month, then with a single backup machine, we reduce the probability to 1% when both are down.

## Replica VS sharding
At first glance, replica is quite similar to sharding. So what’s the relation of these two? And how would you choose between replica and sharding when designing a distributed key-value store?

First of all, we need to be clear about the purpose of these two techniques. Sharding is basically used to splitting data to multiple machines since a single machine cannot store too much data. Replica is a way to protect the system from downtime. With that in mind, if a single machine can’t store all the data, replica won’t help.

## Consistency
By introducing replicas, we can make the system more robust. However, one issue is about consistency. Let’s say for machine A1, we have replica A2. How do you make sure that A1 and A2 have the same data? For instance, when inserting a new entry, we need to update both machines. But it’s possible that the write operation fails in one of them. So over time, A1 and A2 might have quite a lot inconsistent data, which is a big problem.

There are a couple of solutions here. First approach is to keep a local copy in coordinator. Whenever updating a resource, the coordinator will keep the copy of updated version. So in case the update fails, the coordinator is able to re-do the operation.

Another approach is commit log. If you have been using Git, the concept of commit log should be quite familiar to you. Basically, for each node machine, it’ll keep the commit log for each operation, which is like the history of all updates. So when we want to update an entry in machine A, it will first store this request in commit log. And then a separate program will process all the commit logs in order (in a queue). Whenever an operation fails, we can easily recover as we can lookup the commit log.

The last approach I’d like to introduce is to resolve conflict in read. Suppose when the requested resource locates in A1, A2 and A3, the coordinator can ask from all three machines. If by any chance the data is different, the system can resolve the conflict on the fly.

It’s worth to note that all of these approaches are not mutually exclusive. You can definitely use multiple ones based on the application.

