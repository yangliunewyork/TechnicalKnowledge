In computing, a hash table (hash map) is a data structure used to implement an associative array, a structure that can map keys to values. A hash table uses a hash function to compute an index into an array of buckets or slots, from which the desired value can be found.
Ideally, the hash function will assign each key to a unique bucket, but most hash table designs employ an imperfect hash function, which might cause hash collisions where the hash function generates the same index for more than one key. Such collisions must be accommodated in some way.
In a well-dimensioned hash table, the average cost (number of instructions) for each lookup is independent of the number of elements stored in the table. Many hash table designs also allow arbitrary insertions and deletions of key-value pairs, at (amortized) constant average cost per operation.
## Collision resolution
### Separate chaining
In the method known as separate chaining, each bucket is independent, and has some sort of list of entries with the same index. The time for hash table operations is the time to find the bucket (which is constant) plus the time for the list operation.
In a good hash table, each bucket has zero or one entries, and sometimes two or three, but rarely more than that. Therefore, structures that are efficient in time and space for these cases are preferred. Structures that are efficient for a fairly large number of entries per bucket are not needed or desirable. If these cases happen often, the hashing function needs to be fixed.
* Separate chaining with linked lists
Chained hash tables with linked lists are popular because they require only basic data structures with simple algorithms, and can use simple hash functions that are unsuitable for other methods.
The cost of a table operation is that of scanning the entries of the selected bucket for the desired key. If the distribution of keys is sufficiently uniform, the average cost of a lookup depends only on the average number of keys per bucket—that is, it is roughly proportional to the load factor.
* Separate chaining with list head cells
* Separate chaining with other structures

### Open addressing
In another strategy, called open addressing, all entry records are stored in the bucket array itself. When a new entry has to be inserted, the buckets are examined, starting with the hashed-to slot and proceeding in some probe sequence, until an unoccupied slot is found. When searching for an entry, the buckets are scanned in the same sequence, until either the target record is found, or an unused array slot is found, which indicates that there is no such key in the table. The name "open addressing" refers to the fact that the location ("address") of the item is not determined by its hash value. (This method is also called closed hashing; it should not be confused with "open hashing" or "closed addressing" that usually mean separate chaining.)
Well-known probe sequences include:
* Linear probing, in which the interval between probes is fixed (usually 1)
* Quadratic probing, in which the interval between probes is increased by adding the successive outputs of a quadratic polynomial to the starting value given by the original hash computation
* Double hashing, in which the interval between probes is computed by a second hash function
* Open Hashing (Separate Chaining): In open hashing, keys are stored in linked lists attached to cells of a hash table.
* Closed Hashing (Open Addressing): In closed hashing, all keys are stored in the hash table itself without the use of linked lists.

### Meaning of Open hashing and Closed hashing
The use of "closed" vs. "open" reflects whether or not we are locked in to using a certain position or data structure (this is an extremely vague description, but hopefully the rest helps).
For instance, the "open" in "open addressing" tells us the index (aka. address) at which an object will be stored in the hash table is not completely determined by its hash code. Instead, the index may vary depending on what's already in the hash table.
The "closed" in "closed hashing" refers to the fact that we never leave the hash table; every object is stored directly at an index in the hash table's internal array. Note that this is only possible by using some sort of open addressing strategy. This explains why "closed hashing" and "open addressing" are synonyms.
Contrast this with open hashing - in this strategy, none of the objects are actually stored in the hash table's array; instead once an object is hashed, it is stored in a list which is separate from the hash table's internal array. "open" refers to the freedom we get by leaving the hash table, and using a separate list. By the way, "separate list" hints at why open hashing is also known as "separate chaining".
In short, "closed" always refers to some sort of strict guarantee, like when we guarantee that objects are always stored directly within the hash table (closed hashing). Then, the opposite of "closed" is "open", so if you don't have such guarantees, the strategy is considered "open".