Regerence : https://github.com/lamerman/cpp-lru-cache/blob/master/include/lrucache.hpp
## What is LRU (Least Recently Used)
Discards the least recently used items first. This algorithm requires keeping track of what was used when, which is expensive if one wants to make sure the algorithm always discards the least recently used item. General implementations of this technique require keeping "age bits" for cache-lines and track the "Least Recently Used" cache-line based on age-bits. In such an implementation, every time a cache-line is used, the age of all other cache-lines changes.

