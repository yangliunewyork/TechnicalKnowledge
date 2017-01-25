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

### Meaning of Open hashing and Closed hashing
* Open Hashing (Separate Chaining): In open hashing, keys are stored in linked lists attached to cells of a hash table.
* Closed Hashing (Open Addressing): In closed hashing, all keys are stored in the hash table itself without the use of linked lists.
The use of "closed" vs. "open" reflects whether or not we are locked in to using a certain position or data structure (this is an extremely vague description, but hopefully the rest helps).
For instance, the "open" in "open addressing" tells us the index (aka. address) at which an object will be stored in the hash table is not completely determined by its hash code. Instead, the index may vary depending on what's already in the hash table.
The "closed" in "closed hashing" refers to the fact that we never leave the hash table; every object is stored directly at an index in the hash table's internal array. Note that this is only possible by using some sort of open addressing strategy. This explains why "closed hashing" and "open addressing" are synonyms.
Contrast this with open hashing - in this strategy, none of the objects are actually stored in the hash table's array; instead once an object is hashed, it is stored in a list which is separate from the hash table's internal array. "open" refers to the freedom we get by leaving the hash table, and using a separate list. By the way, "separate list" hints at why open hashing is also known as "separate chaining".
In short, "closed" always refers to some sort of strict guarantee, like when we guarantee that objects are always stored directly within the hash table (closed hashing). Then, the opposite of "closed" is "open", so if you don't have such guarantees, the strategy is considered "open".

## Linear probing
Linear probing is a scheme in computer programming for resolving collisions in hash tables, data structures for maintaining a collection of key–value pairs and looking up the value associated with a given key. 

Along with quadratic probing and double hashing, linear probing is a form of open addressing. In these schemes, each cell of a hash table stores a single key–value pair. When the hash function causes a collision by mapping a new key to a cell of the hash table that is already occupied by another key, linear probing searches the table for the closest following free location and inserts the new key there. Lookups are performed in the same way, by searching the table sequentially starting at the position given by the hash function, until finding a cell with a matching key or an empty cell.

As Thorup & Zhang (2012) write, "Hash tables are the most commonly used nontrivial data structures, and the most popular implementation on standard hardware uses linear probing, which is both fast and simple."[1] Linear probing can provide high performance because of its good locality of reference, but is more sensitive to the quality of its hash function than some other collision resolution schemes. 

### Operation
Linear probing is a component of open addressing schemes for using a hash table to solve the dictionary problem. In the dictionary problem, a data structure should maintain a collection of key–value pairs subject to operations that insert or delete pairs from the collection or that search for the value associated with a given key. In open addressing solutions to this problem, the data structure is an array T (the hash table) whose cells T[i] (when nonempty) each store a single key–value pair. A hash function is used to map each key into the cell of T where that key should be stored, typically scrambling the keys so that keys with similar values are not placed near each other in the table. A hash collision occurs when the hash function maps a key into a cell that is already occupied by a different key. Linear probing is a strategy for resolving collisions, by placing the new key into the closest following empty cell.

#### Search
To search for a given key x, the cells of T are examined, beginning with the cell at index h(x) (where h is the hash function) and continuing to the adjacent cells h(x) + 1, h(x) + 2, ..., until finding either an empty cell or a cell whose stored key is x. If a cell containing the key is found, the search returns the value from that cell. Otherwise, if an empty cell is found, the key cannot be in the table, because it would have been placed in that cell in preference to any later cell that has not yet been searched. In this case, the search returns as its result that the key is not present in the dictionary.

#### Insertion
To insert a key–value pair (x,v) into the table (possibly replacing any existing pair with the same key), the insertion algorithm follows the same sequence of cells that would be followed for a search, until finding either an empty cell or a cell whose stored key is x. The new key–value pair is then placed into that cell.
If the insertion would cause the load factor of the table (its fraction of occupied cells) to grow above some preset threshold, the whole table may be replaced by a new table, larger by a constant factor, with a new hash function, as in a dynamic array. Setting this threshold close to zero and using a high growth rate for the table size leads to faster hash table operations but greater memory usage than threshold values close to one and low growth rates. A common choice would be to double the table size when the load factor would exceed 1/2, causing the load factor to stay between 1/4 and 1/2.

#### Deletion

When a key–value pair is deleted, it may be necessary to move another pair backwards into its cell, to prevent searches for the moved key from finding an empty cell.

It is also possible to remove a key–value pair from the dictionary. However, it is not sufficient to do so by simply emptying its cell. This would affect searches for other keys that have a hash value earlier than the emptied cell, but that are stored in a position later than the emptied cell. The emptied cell would cause those searches to incorrectly report that the key is not present.

Instead, when a cell i is emptied, it is necessary to search forward through the following cells of the table until finding either another empty cell or a key that can be moved to cell i (that is, a key whose hash value is equal to or earlier than i). When an empty cell is found, then emptying cell i is safe and the deletion process terminates. But, when the search finds a key that can be moved to cell i, it performs this move. This has the effect of speeding up later searches for the moved key, but it also empties out another cell, later in the same block of occupied cells. The search for a movable key continues for the new emptied cell, in the same way, until it terminates by reaching a cell that was already empty. In this process of moving keys to earlier cells, each key is examined only once. __Therefore, the time to complete the whole process is proportional to the length of the block of occupied cells containing the deleted key, matching the running time of the other hash table operations.__

__Alternatively, it is possible to use a lazy deletion strategy in which a key–value pair is removed by replacing the value by a special flag value indicating a deleted key. However, these flag values will contribute to the load factor of the hash table. With this strategy, it may become necessary to clean the flag values out of the array and rehash all the remaining key–value pairs once too large a fraction of the array becomes occupied by deleted keys.__

In practice, linear probing is typically significantly faster than chaining. This is primarily due to locality of reference, since the accesses performed in linear probing tend to be closer in memory than the accesses performed in chained hashing.

There are other wins in linear probing. For example, insertions into a linear probing hash table don't require any new allocations (unless you're rehashing the table), so in applications like network routers where memory is scarce, it's nice to know that once the table is set up, the elements can be placed into it with no risk of a malloc fail.

One weakness of linear probing is that, with a bad choice of hash function, primary clustering can cause the performance of the table to degrade significantly. While chained hashing can still suffer from bad hash functions, it's less sensitive to elements with nearby hash codes, which don't adversely impact the runtime. Theoretically, linear probing only gives expected O(1) lookups if the hash functions are 5-independent or if there's sufficient entropy in the keys. There are many ways to address this, since as using the Robin Hood hashing technique or hopscotch hashing, both of which have significantly better worst-cases than vanilla linear probing.

The other weakness of linear probing is that its performance significantly degrades as the load factor approaches 1. You can address this either by rehashing periodically or by using the Robin Hood hashing technique described above.

#### Properties
__Linear probing provides good locality of reference, which causes it to require few uncached memory accesses per operation. Because of this, for low to moderate load factors, it can provide very high performance.__ However, compared to some other open addressing strategies, its performance degrades more quickly at high load factors because of primary clustering, a tendency for one collision to cause more nearby collisions. Additionally, achieving good performance with this method requires a higher-quality hash function than for some other collision resolution schemes. When used with low-quality hash functions that fail to eliminate nonuniformities in the input distribution, linear probing can be slower than other open-addressing strategies such as double hashing, which probes a sequence of cells whose separation is determined by a second hash function, or quadratic probing, where the size of each step varies depending on its position within the probe sequence.

## Quadratic probing
Quadratic probing is an open addressing scheme in computer programming for resolving collisions in hash tables—when an incoming data's hash value indicates it should be stored in an already-occupied slot or bucket. Quadratic probing operates by taking the original hash index and adding successive values of an arbitrary quadratic polynomial until an open slot is found.

* __Quadratic probing can be a more efficient algorithm in a closed hash table, since it better avoids the clustering problem that can occur with linear probing, although it is not immune. It also provides good memory caching because it preserves some locality of reference; however, linear probing has greater locality and, thus, better cache performance.__

* __For linear probing it is a bad idea to let the hash table get neraly full, because performance degrades. For quadratic probing, the situation is even more drastic: There is no guarentee of finding an empty cell once the table gets more than half full, or ven before the table gets half full if the table size is not prime. This is because at most half of the table can be used as alternative locations to resolve collisions.__

* __If quadratic probing is used, and the table size is prime, then a new elment can always be insteredi if the table is at least half empty.__

* __Although quadratic probing eliminates primary clustering, elements that hash to the same position will probe the same alternative cells. This is known as secondary clustering. Secondary clustering is a slight theoretical blemish. Simulation results suggest that it generally causes less than an extra half probe per search.__

## Double hashing
Double hashing is a computer programming technique used in hash tables to resolve hash collisions, in cases when two different values to be searched for produce the same hash key. It is a popular collision-resolution technique in open-addressed hash tables. Double hashing is implemented in many popular libraries.

Like linear probing, it uses one hash value as a starting point and then repeatedly steps forward an interval until the desired value is located, an empty location is reached, or the entire table has been searched; but this interval is decided using a second, independent hash function (hence the name double hashing). Unlike linear probing and quadratic probing, __the interval depends on the data__, so that even values mapping to the same location have different bucket sequences; this minimizes repeated collisions and the effects of clustering.

Given two randomly, uniformly, and independently selected hash functions {\displaystyle h_{1}} h_{1} and {\displaystyle h_{2}} h_{2}, the ith location in the bucket sequence for value k in a hash table {\displaystyle T} T is: {\displaystyle h(i,k)=(h_{1}(k)+i\cdot h_{2}(k))\mod |T|.} h(i,k)=(h_1(k) + i \cdot h_2(k))\mod |T|. Generally, {\displaystyle h_{1}} h_{1} and {\displaystyle h_{2}} h_{2} are selected from a set of universal hash functions.

## What's recommended ? Separated chaining or open addressing?

Wikipedia's article on hash tables gives a distinctly better explanation and overview of different hash table schemes that people have used than I'm able to off the top of my head. In fact you're probably better off reading that article than asking the question here. :)

That said...

A chained hash table indexes into an array of pointers to the heads of linked lists. Each linked list cell has the key for which it was allocated and the value which was inserted for that key. When you want to look up a particular element from its key, the key's hash is used to work out which linked list to follow, and then that particular list is traversed to find the element that you're after. If more than one key in the hash table has the same hash, then you'll have linked lists with more than one element.

The downside of chained hashing is having to follow pointers in order to search linked lists. The upside is that chained hash tables only get linearly slower as the load factor (the ratio of elements in the hash table to the length of the bucket array) increases, even if it rises above 1.

An open-addressing hash table indexes into an array of pointers to pairs of (key, value). You use the key's hash value to work out which slot in the array to look at first. If more than one key in the hash table has the same hash, then you use some scheme to decide on another slot to look in instead. For example, linear probing is where you look at the next slot after the one chosen, and then the next slot after that, and so on until you either find a slot that matches the key you're looking for, or you hit an empty slot (in which case the key must not be there).

__Open-addressing is usually faster than chained hashing when the load factor is low because you don't have to follow pointers between list nodes. It gets very, very slow if the load factor approaches 1, because you end up usually having to search through many of the slots in the bucket array before you find either the key that you were looking for or an empty slot. Also, you can never have more elements in the hash table than there are entries in the bucket array.__

To deal with the fact that all hash tables at least get slower (and in some cases actually break completely) when their load factor approaches 1, practical hash table implementations make the bucket array larger (by allocating a new bucket array, and copying elements from the old one into the new one, then freeing the old one) when the load factor gets above a certain value (typically about 0.7).

## Rehashing
Extendible hashing is a type of hash system which treats a hash as a bit string, and uses a trie for bucket lookup. Because of the hierarchical nature of the system, re-hashing is an incremental operation (done one bucket at a time, as needed). This means that time-sensitive applications are less affected by table growth than by standard full-table rehashes.Practically all modern filesystems use either extendible hashing or B-trees.

If the table gets too full, the running time for the operations will start taking too long and inserts might fail for closed hashing with quadratic resolution. This can happen if there are too many deletions intermixed with insertions. A solution, then, is to build another table that is about twice as big (with associated new hash function) and scan down the entire original hash table, computing the new hash value for each (non-deleted) element and inserting it in the new table.

This entire operation is called rehashing. This is obviously a very expensive operation -- the running time is O(n), since there are n elements to rehash and the table size is roughly 2n, but it is actually not all that bad, because it happens very infrequently. In particular, there must have been n/2 inserts prior to the last rehash, so it essentially adds a constant cost to each insertion. If this data structure is part of the program, the effect is not noticeable. On the other hand, if the hashing is performed as part of an interactive system, then the unfortunate user whose insertion caused a rehash could see a slowdown.

Rehashing can be implemented in several ways with quadratic probing. One alternative is to rehash as soon as the table is half full. The other extreme is to rehash only when an insertion fails. A third, middle of the road, strategy is to rehash when the table reaches a certain load factor. Since performance does degrade as the load factor increases, the third strategy, implemented with a good cutoff, could be best.Rehashing frees the programmer from worrying about the table size and is important because hash tables cannot be made arbitrarily large in complex programs.

## Extendible Hashing
Our last topic deals with the case where the amount of data is too large to fit in main memory.

As before, we assume that at any point we have n records to store; the value of n changes over time. Furthermore, at most m records fit in one disk block. We will use m = 4 in this section.

If either open hashing or closed hashing is used, the major problem is that collisions could cause several blocks to be examined during a find, even for a well-distributed hash table. Furthermore, when the table gets too full, an extremely expensive rehashing step must be performed, which requires O(n) disk accesses.

A clever alternative, known as extendible hashing, allows a find to be performed in two disk accesses. Insertions also require few disk accesses.

We recall that a B-tree has depth O(logm/2n). As m increases, the depth of a B-tree decreases. We could in theory choose m to be so large that the depth of the B-tree would be 1. Then any find after the first would take one disk access, since, presumably, the root node could be stored in main memory. The problem with this strategy is that the branching factor is so high that it would take considerable processing to determine which leaf the data was in. If the time to perform this step could be reduced, then we would have a practical scheme. This is exactly the strategy used by extendible hashing.



