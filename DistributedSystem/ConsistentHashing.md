## What is Consistent Hashing ?
Consistent hashing is a special kind of hashing such that when a hash table is resized, only __K/n__ keys need to be remapped on average, where __K__ is the number of keys, and __n__ is the number of slots. In contrast, in most traditional hash tables, a change in the number of array slots causes nearly all keys to be remapped because the mapping between the keys and the slots is defined by a modular operation.

Consistent hashing has also been used to reduce the impact of partial system failures in large Web applications as to allow for robust caches without incurring the system wide fallout of a failure.

The consistent hashing concept also applies to the design of __distributed hash tables (DHTs)__. DHTs use consistent hashing to partition a keyspace among a distributed set of nodes, and additionally provide an overlay network that connects nodes such that the node responsible for any key can be efficiently located.

__Rendezvous hashing__, designed at the same time as consistent hashing, achieves the same goals using the very different Highest Random Weight (HRW) algorithm.

