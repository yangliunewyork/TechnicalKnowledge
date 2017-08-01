Redis is an open source, BSD licensed, advanced key-value store. It is often referred to as a data structure server, since the keys can contain strings, hashes, lists, sets and sorted sets. Redis is written in C. This tutorial provides good understanding on Redis concepts, needed to create and deploy a highly scalable and performance-oriented system.

# Overview

Redis is an open source, advanced key-value store and an apt solution for building highperformance, scalable web applications.

Redis has three main peculiarities that sets it apart.

* Redis holds its database entirely in the memory, using the disk only for persistence.  
* Redis has a relatively rich set of data types when compared to many key-value data stores.  
* Redis can replicate data to any number of slaves.  

### Redis Advantages

* Exceptionally fast − Redis is very fast and can perform about 110000 SETs per second, about 81000 GETs per second.

* Supports rich data types − Redis natively supports most of the datatypes that developers already know such as list, set, sorted set, and hashes. This makes it easy to solve a variety of problems as we know which problem can be handled better by which data type.

* Operations are atomic − All Redis operations are atomic, which ensures that if two clients concurrently access, Redis server will receive the updated value.

* Multi-utility tool − Redis is a multi-utility tool and can be used in a number of use cases such as caching, messaging-queues (Redis natively supports Publish/Subscribe), any short-lived data in your application, such as web application sessions, web page hit counts, etc.

### Redis Versus Other Key-value Stores

* Redis is a different evolution path in the key-value DBs, where values can contain more complex data types, with atomic operations defined on those data types.

* Redis is an in-memory database but persistent on disk database, hence it represents a different trade off where very high write and read speed is achieved with the limitation of data sets that can't be larger than the memory.

* Another advantage of in-memory databases is that the memory representation of complex data structures is much simpler to manipulate compared to the same data structure on disk. Thus, Redis can do a lot with little internal complexity.

# Data types

##### Strings
Redis string is a sequence of bytes. Strings in Redis are binary safe, meaning they have a known length not determined by any special terminating characters. Thus, you can store anything up to 512 megabytes in one string.

Example

```
redis 127.0.0.1:6379> SET name "tutorialspoint" 
OK 
redis 127.0.0.1:6379> GET name 
"tutorialspoint"
```

##### Hashes
A Redis hash is a collection of key value pairs. Redis Hashes are maps between string fields and string values. Hence, they are used to represent objects.

##### Lists
Redis Lists are simply lists of strings, sorted by insertion order. You can add elements to a Redis List on the head or on the tail.

##### Sets
Redis Sets are an unordered collection of strings. In Redis, you can add, remove, and test for the existence of members in O(1) time complexity.

##### Sorted Sets
Redis Sorted Sets are similar to Redis Sets, non-repeating collections of Strings. The difference is, every member of a Sorted Set is associated with a score, that is used in order to take the sorted set ordered, from the smallest to the greatest score. While members are unique, the scores may be repeated.

# Commands

