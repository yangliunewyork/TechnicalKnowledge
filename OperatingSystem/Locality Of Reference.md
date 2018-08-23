## Locality of Reference
In computer science, locality of reference, also known as the principle of locality, is a term for the phenomenon in which the same values, or related storage locations, are frequently accessed, depending on the memory access pattern. There are two basic types of reference locality – temporal and spatial locality. Temporal locality refers to the reuse of specific data, and/or resources, within a relatively small time duration. Spatial locality refers to the use of data elements within relatively close storage locations. Sequential locality, a special case of spatial locality, occurs when data elements are arranged and accessed linearly, such as, traversing the elements in a one-dimensional array.

Locality is merely one type of predictable behavior that occurs in computer systems. Systems that exhibit strong locality of reference are great candidates for performance optimization through the use of techniques such as the caching, prefetching for memory and advanced branch predictors at the pipelining stage of processor core.

### Types of locality
* Temporal locality
  * If at one point a particular memory location is referenced, then it is likely that the same location will be referenced again in the near future. There is a temporal proximity between the adjacent references to the same memory location. In this case it is common to make efforts to store a copy of the referenced data in special memory storage, which can be accessed faster. Temporal locality is a special case of spatial locality, namely when the prospective location is identical to the present location.
  
* Spatial locality
  * If a particular storage location is referenced at a particular time, then it is likely that nearby memory locations will be referenced in the near future. In this case it is common to attempt to guess the size and shape of the area around the current reference for which it is worthwhile to prepare faster access.
* Memory locality
  * Spatial locality explicitly relating to memory.
* Branch locality
  * If there are only a few possible alternatives for the prospective part of the path in the spatial-temporal coordinate space. This is the case when an instruction loop has a simple structure, or the possible outcome of a small system of conditional branching instructions is restricted to a small set of possibilities. Branch locality is typically not a spatial locality since the few possibilities can be located far away from each other.
* Equidistant locality
  * It is halfway between the spatial locality and the branch locality. Consider a loop accessing locations in an equidistant pattern, i.e. the path in the spatial-temporal coordinate space is a dotted line. In this case, a simple linear function can predict which location will be accessed in the near future.
  
### Reasons for locality
There are several reasons for locality. These reasons are either goals to achieve or circumstances to accept, depending on the aspect. The reasons below are not disjoint; in fact, the list below goes from the most general case to special cases:

* Predictability	
  * In fact, locality is merely one type of predictable behavior in computer systems.
* Structure of the program
  * Locality occurs often because of the way in which computer programs are created, for handling decidable problems. Generally, related data is stored in nearby locations in storage. One common pattern in computing involves the processing of several items, one at a time. This means that if a lot of processing is done, the single item will be accessed more than once, thus leading to temporal locality of reference. Furthermore, moving to the next item implies that the next item will be read, hence spatial locality of reference, since memory locations are typically read in batches.
* Linear data structures
  * Locality often occurs because code contains loops that tend to reference arrays or other data structures by indices. Sequential locality, a special case of spatial locality, occurs when relevant data elements are arranged and accessed linearly. For example, the simple traversal of elements in a one-dimensional array, from the base address to the highest element would exploit the sequential locality of the array in memory.[1] The more general equidistant locality occurs when the linear traversal is over a longer area of adjacent data structures with identical structure and size, accessing mutually corresponding elements of each structure rather than each entire structure. This is the case when a matrix is represented as a sequential matrix of rows and the requirement is to access a single column of the matrix.
* Efficiency of memory hierarchy use	
  * Although random access memory presents the programmer with the ability to read or write anywhere at any time, in practice latency and throughput are affected by the efficiency of the cache, which is improved by increasing the locality of reference. Poor locality of reference results in cache thrashing and cache pollution and to avoid it, data-elements with poor locality can be bypassed from cache.
  
## Example
  
### Cache
In the context of computer architecture the most prominent exploiter of spatial locality is "Cache".  Caches are built upon the locality of references concept which tells us that :
  1. Recently referenced items are likely to be referenced in the near future.(which is known as temporal locality) 
  2. Items with nearby addresses tend to be referenced close together in time.(which is known as spatial locality) 

Thus, spatial locality suggests that whenever an address is accessed, in addition to cache the data of accessed address, it's reasonable to also cache data of nearby addresses.  In the caches spatial locality is exploited by using larger blocks that contains nearby addresses and cache them for future accesses.
