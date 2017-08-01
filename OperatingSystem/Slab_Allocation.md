Slab allocation is a memory management mechanism intended for the efficient memory allocation of kernel objects. It eliminates fragmentation caused by allocations and deallocations. The technique is used to retain allocated memory that contains a data object of a certain type for reuse upon subsequent allocations of objects of the same type. It is analogous to an object pool, but only applies to memory, not other resources.

# Basis

The primary motivation for slab allocation is that the initialization and destruction of kernel data objects can actually outweigh the cost of allocating memory for them. As object creation and deletion are widely employed by the kernel, overhead costs of initialization can result in significant performance drops. The notion of object caching was therefore introduced in order to avoid the invocation of functions used to initialize object state.

With slab allocation, memory chunks suitable to fit data objects of certain type or size are preallocated. The slab allocator keeps track of these chunks, known as caches, so that when a request to allocate memory for a data object of a certain type is received, it can instantly satisfy the request with an already allocated slot. Destruction of the object does not free up the memory, but only opens a slot which is put in the list of free slots by the slab allocator. The next call to allocate memory of the same size will return the now unused memory slot. This process eliminates the need to search for suitable memory space and greatly alleviates memory fragmentation. In this context, a slab is one or more contiguous pages in the memory containing pre-allocated memory chunks.

# Implementation

Understanding the slab allocation algorithm requires defining and explaining some terms:

* Cache: cache represents a small amount of very fast memory. A cache is a storage for a specific type of object, such as semaphores, process descriptors, file objects, etc. A cache is stored in one or more slabs.
* Slab: slab represents a contiguous piece of memory, usually made of several physically contiguous pages. The slab is the actual container of data associated with objects of the specific kind of the containing cache.

When a program sets up a cache, it allocates a number of objects to the slabs associated with that cache. This number depends on the size of the associated slabs.

Slabs may exist in one of the following states :

* empty – all objects on a slab marked as free
* partial – slab consists of both used and free objects
* full – all objects on a slab marked as used

Initially, the system marks each slab as "empty". When the process calls for a new kernel object, the system tries to find a free location for that object on a partial slab in a cache for that type of object. If no such location exists, the system allocates a new slab from contiguous physical pages and assigns it to a cache. The new object gets allocated from this slab, and its location becomes marked as "partial".

The allocation takes place quickly, because the system builds the objects in advance and readily allocates them from a slab.

# Slabs

A slab is the amount by which a cache can grow or shrink. It represents one memory allocation to the cache from the machine, and whose size is customarily a multiple of the page size. A slab must contain a list of free buffers (or bufctls), as well as a list of the bufctls that have been allocated (in the case of a large slab size).

##### Large slabs
These are for caches that store objects that are at least 1/8 of the page size for a given machine. The reason for the large slabs having a different layout from the small slabs is that it allows large slabs to pack better into page-size units, which helps with fragmentation. The slab contains a list of bufctls, which are simply controllers for each buffer that can be allocated (a buffer is the memory that the user of a slab allocator would use).

##### Small slabs
The small slabs contain objects that are less than 1/8 of the page size for a given machine. These small slabs need to be optimized further from the logical layout, by avoiding using bufctls (which would be just as large as the data itself and cause memory usage to be much greater). A small slab is exactly one page, and has a defined structure that allows bufctls to be avoided. The last part of the page contains the 'slab header', which is the information needed to retain the slab. Starting at the first address of that page, there are as many buffers as can be allocated without running into the slab header at the end of the page.
Instead of using bufctls, we use the buffers themselves to retain the free list links. This allows the small slab's bufctl to be bypassed.



















