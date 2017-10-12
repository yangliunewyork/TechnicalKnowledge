* https://prakhar.me/articles/bloom-filters-for-dummies/

Before we talk about what a Bloom Filter is and how it actually works let me make an attempt to sell you on why you would need a bloom filter. Let’s assume you have an idea to build your own search engine. You are fed up of Google’s monopoly and decide to write your own version of a search engine (much like DuckDuckGo). Now the first step in building a search engine is to build a crawler. How does a crawler work? Quite simply the work of crawler can be reduced down to the following steps (without the implementation details, of course).

1. Start with a URL (webpage) and scrape its content.
2. Extract a list of all URLs on that page.
3. For each URL on that page check if this URL has not been crawled already.
4. Take the new URL that you encounter and go to Step 1.

As you can see, a crawler’s work in theory is quite simple - just keep scraping content for any previously unseen URLs (webpages). The step we are going to focus on is step 3 in the above algorithm. If you’ve taken your data structures class you know that to maintain a list of all URLs to check for membership is a bad idea (O(n) lookup time). So what you instead do is a use a set (or a hash-table) in memory that allows you do quick lookups and test for membership of a URL. Now this works fine as long as your hash-table can reside in the memory. Consider the case for Google for example - clearly there is no way a hash table for a billion plus URLs can reside in main memory. You can surely use the disk for storing and querying but since that is significantly slower compared to accessing the main memory we are not going to consider that case for now.

# BLOOM FILTERS

How do you tackle the above situation? Is there a data structure that can be stored in main memory and still hold vast amount of data? This is where bloom filters come in. Bloom filters use much lesser space and constant time to answer the queries for set membership. More precisely "A Bloom filter is a data structure that is used to check for membership of an element x in a set of m elements".

Bloom filters have a strong space advantage over other data structures like sets, hash tables or binary search trees. Bloom filters also have the property that the time taken to add an item or to check for membership is a constant O(k) and is independent of the number of items in the filter.

What’s the catch you might ask? Well, the catch is that bloom filters trade exactness for this efficiency meaning that there are false-positives - i.e. elements that are not a part of set but are claimed to be part of the set. However, as we shall soon see, the rate of false positives depends upon the application and can be lowered at the expense of amount of memory required. Like everything else in computer science, there is a trade-off and in this case, between exactness and amount of memory.

### ALGORITHM

At the heart of every bloom filter lies two key elements

1. An array of n bits, initially all set to 0.  
2. A collection of k independent hash functions h(x). Each hash function takes a value v and generates a number i where i < n which effectively maps to a position in the bit array.  

The underlying idea of a bloom filter is quite simple and can be explained in the following steps :

1. Initialize a bit array of n bits with zeros. Generally n is chosen to be much greater than the number of elements in the set.  
2. Whenever the filter sees a new element apply each of the hash functions h(x) on the element. With the value generated, which is an index in the bit array, set the bit to 1 in the array. For example, if there are k hash functions there will be k indices generated. For each of these k positions in the bit array set array[i] = 1.  
3. To check if an element exists in the set, simply carry out the exact same procedure with a slight twist. Generate k values by applying the k hash-functions on the input. If at least one of these k indices in the bit array is set to zero then the element is a new element else this is an existing element in the set.  














