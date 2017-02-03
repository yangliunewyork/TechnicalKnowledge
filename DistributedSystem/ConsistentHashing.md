## Reference:
http://www.tom-e-white.com/2007/11/consistent-hashing.html

## What is Consistent Hashing ?
Consistent hashing is a special kind of hashing such that when a hash table is resized, only __K/n__ keys need to be remapped on average, where __K__ is the number of keys, and __n__ is the number of slots. In contrast, in most traditional hash tables, a change in the number of array slots causes nearly all keys to be remapped because the mapping between the keys and the slots is defined by a modular operation.

Consistent hashing has also been used to reduce the impact of partial system failures in large Web applications as to allow for robust caches without incurring the system wide fallout of a failure.

The consistent hashing concept also applies to the design of __distributed hash tables (DHTs)__. DHTs use consistent hashing to partition a keyspace among a distributed set of nodes, and additionally provide an overlay network that connects nodes such that the node responsible for any key can be efficiently located.

__Rendezvous hashing__, designed at the same time as consistent hashing, achieves the same goals using the very different Highest Random Weight (HRW) algorithm.

## Overview
The need for consistent hashing arose from limitations experienced while running collections of caching machines - web caches, for example. If you have a collection of n cache machines then a common way of load balancing across them is to put object o in cache machine number hash(o) mod n. This works well until you add or remove cache machines (for whatever reason), for then n changes and every object is hashed to a new location. This can be catastrophic since the originating content servers are swamped with requests from the cache machines. It's as if the cache suddenly disappeared. Which it has, in a sense. (This is why you should care - consistent hashing is needed to avoid swamping your servers!)

It would be nice if, when a cache machine was added, it took its fair share of objects from all the other cache machines. Equally, when a cache machine was removed, it would be nice if its objects were shared between the remaining machines. This is exactly what consistent hashing does - consistently maps objects to the same cache machine, as far as is possible, at least.

The basic idea behind the consistent hashing algorithm is to hash both objects and caches using the same hash function. The reason to do this is to map the cache to an interval, which will contain a number of object hashes. If the cache is removed then its interval is taken over by a cache with an adjacent interval. All the other caches remain unchanged.

## Demonstration
Let's look at this in more detail. The hash function actually maps objects and caches to a number range. This should be familiar to every Java programmer - the hashCode method on Object returns an int, which lies in the range -231 to 231-1. Imagine mapping this range into a circle so the values wrap around. Here's a picture of the circle with a number of objects (1, 2, 3, 4) and caches (A, B, C) marked at the points that they hash to (based on a diagram from Web Caching with Consistent Hashing by David Karger et al):

![alt](http://2.bp.blogspot.com/_IhqEHw4_Ick/Rz9cjSPnAEI/AAAAAAAAAA4/hc2tot8SWVw/s1600-h/consistent_hashing_1.png)

To find which cache an object goes in, we move clockwise round the circle until we find a cache point. So in the diagram above, we see object 1 and 4 belong in cache A, object 2 belongs in cache B and object 3 belongs in cache C. Consider what happens if cache C is removed: object 3 now belongs in cache A, and all the other object mappings are unchanged. If then another cache D is added in the position marked it will take objects 3 and 4, leaving only object 1 belonging to A.

![alt](http://4.bp.blogspot.com/_IhqEHw4_Ick/Rz9cwyPnAFI/AAAAAAAAABA/aW5zxmOIIN0/s1600-h/consistent_hashing_2.png)

This works well, except the size of the intervals assigned to each cache is pretty hit and miss. Since it is essentially random it is possible to have a very non-uniform distribution of objects between caches. The solution to this problem is to introduce the idea of "virtual nodes", which are replicas of cache points in the circle. So whenever we add a cache we create a number of points in the circle for it.
