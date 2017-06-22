An Elasticsearch index is a logical namespace to organize your data (like a database). An Elasticsearch index has one or more shards (default is 5). A shard is a Lucene index which actually stores the data and is a search engine in itself. Each shard can have zero or more replicas (default is 1). An Elasticsearch index also has “types” (like tables in a database) which allow you to logically partition your data in an index. All documents in a given “type” in an Elasticsearch index have the same properties (like schema for a table).

![alt](https://cdn-images-1.medium.com/max/1600/0*SL6EqBeNIyoDufE8.jpeg)

# Types of nodes
An instance of Elasticsearch is a node and a group of nodes form a cluster. Nodes in an Elasticsearch cluster can be configured in three different ways:

#### Master Node
* It controls the Elasticsearch cluster and is responsible for all clusterwide operations like creating/deleting an index, keeping track of which nodes are part of the cluster and assigning shards to nodes. The master node processes one cluster state at a time and broadcasts the state to all the other nodes which respond with confirmation to the master node.
* A node can be configured to be eligible to become a master node by setting the node.master property to be true (default) in elasticsearch.yml.
* __For large production clusters, it’s recommended to have a dedicated master node to just control the cluster and not serve any user requests.__

#### Data Node
It holds the data and the inverted index. By default, every node is configured to be a data node and the property node.data is set to true in elasticsearch.yml. If you would like to have a dedicated master node, then change the node.data property to false.

#### Client Node
If you set both node.master and node.data to false, then the node gets configured as a client node and acts as a load balancer routing incoming requests to different nodes in the cluster.


The node in the Elasticsearch cluster that you connect with as a client is called the __coordinating node__. The coordinating node routes the client requests to the appropriate shard in the cluster. For read requests, the coordinating node selects a different shard every time to serve the request in order to balance the load.

Before we start reviewing how a CRUD request sent to the coordinting node propagates through the cluster and is executed by the engine, let’s see how Elasticsearch stores data internally to serve results for full-text search at low latency.

# Storage Model
Elasticsearch uses Apache Lucene, a full-text search library written in Java and developed by Doug Cutting (creator of Apache Hadoop), internally which uses a data structure called an inverted index designed to serve low latency search results. A document is the unit of data in Elasticsearch and an inverted index is created by tokenizing the terms in the document, creating a sorted list of all unique terms and associating a list of documents with where the word can be found.

It is very similar to an index at the back of a book which contains all the unique words in the book and a list of pages where we can find that word. When we say a document is indexed, we refer to the inverted index.

To improve searchability (e.g., serving same results for both lowercase and uppercase words), the documents are first analyzed and then indexed. Analyzing consists of two parts:

* Tokenizing sentences into individual words
* Normalizing words to a standard form

By default, Elasticsearch uses Standard Analyzer, which uses

* Standard tokenizer to split words on word boundaries
* Lowercase token filter to convert words to lowercase

There are many other analyzers available and you can read about them in the docs.
In order to serve relevant search results, every query made on the documents is also analyzed using the same analyzer used for indexing.

# Anatomy of a Write

#### (C)reate
When you send a request to the coordinating node to index a new document, the following set of operations take place:

* All the nodes in the Elasticsearch cluster contain metadata about which shard lives on which node. The coordinating node routes the document to the appropriate shard using the document ID (default). Elasticsearch hashes the document ID with murmur3 as the hash function and mods by the number of primary shards in the index to determine which shard the document should be indexed in.

``` shard = hash(document_id) % (num_of_primary_shards) ```

* As the node receives the request from the coordinating node, the request is written to the __translog__ and the document is added to memory buffer. If the request is successful on the primary shard, the request is sent in parallel to the replica shards. The client receives acknowledgement that the request was successful only after the translog is fsync’ed on all primary and replica shards.

* The memory buffer is refreshed at a regular interval (defaults to 1 sec) and the contents are written to a new segment in filesystem cache. This segment is not yet fsync’ed, however, the segment is open and the contents are available for search.

* The translog is emptied and filesystem cache is fsync’ed every 30 minutes or when the translog gets too big. This process is called flush in Elasticsearch. During the flush process, the in-memory buffer is cleared and the contents are written to a new segment. A new commit point is created with the segments fsync’ed and flushed to disk. The old translog is deleted and a fresh one begins.

The figure below shows how the write request and data flows.
![alt](https://cdn-images-1.medium.com/max/1600/0*SFtJWPp4A0lLY1k6.jpeg)

#### (U)pdate and (D)elete
Delete and Update operations are also write operations. However, documents in Elasticsearch are immutable and hence, cannot be deleted or modified to represent any changes. Then, how can a document be deleted/updated?

Every segment on disk has a .del file associated with it. When a delete request is sent, the document is not really deleted, but marked as deleted in the .del file. This document may still match a search query but is filtered out of the results. When segments are merged (we’ll cover segment merging in a follow up post), the documents marked as deleted in the .del file are not included in the new merged segment.

Now, let’s see how updates work. When a new document is created, Elasticsearch assigns a version number to that document. Every change to the document results in a new version number. When an update is performed, the old version is marked as deleted in the .del file and the new version is indexed in a new segment. The older version may still match a search query, however, it is filtered out from the results.

After the documents are indexed/updated, we would like to perform search requests. Let’s see how search requests are executed in Elasticsearch.


#### Anatomy of a (R)ead
Read operations consist of two parts:
* Query Phase
* Fetch Phase
Let’s see how each phase works.

##### Query Phase

In this phase, the coordinating node routes the search request to all the shards (primary or replica) in the index. The shards perform search independently and create a priority queue of the results sorted by relevance score (we’ll cover relevance score later in the post). All the shards return the __document IDs__ of the matched documents and relevant scores to the coordinating node. The coordinating node creates a new priority queue and sorts the results globally. There can be a lot of documents which match the results, however, by default, each shard sends the top 10 results to the coordinating node and the coordinating creates a priority queue sorting results from all the shards and returns the top 10 hits.


##### Fetch Phase
After the coordinating node sorts all the results to generate a globally sorted list of documents, it then requests the original documents from all the shards. All the shards enrich the documents and return them to the coordinating node.
The figure below shows how the read request and the data flows.

![alt](https://cdn-images-1.medium.com/max/1600/0*2DAJ28Q4tnGmOLu4.jpeg)

##### Search Relevance
The relevance is determined by a score that Elasticsearch gives to each document returned in the search result. The default algorithm used for scoring is tf/idf (term frequency/inverse document frequency). The term frequency measures how many times a term appears in a document (higher frequency == higher relevance) and inverse document frequency measures how often the term appears in the entire index as a percentage of the total number of documents in the index (higher frequency == less relevance). The final score is a combination of the tf-idf score with other factors like term proximity (for phrase queries), term similarity (for fuzzy queries), etc.

# Consensus- Split-brain problem and importance of quorum
Consensus is one of the fundamental challenges of a distributed system. It requires all the processes/nodes in the system to agree on a given data value/status. There are a lot of consensus algorithms like [Raft](https://raft.github.io/), [Paxos](https://en.wikipedia.org/wiki/Paxos_%28computer_science%29), etc. which are mathematically proven to work, however, Elasticsearch has implemented its own consensus system (zen discovery) because of reasons described [here](https://www.elastic.co/blog/resiliency-elasticsearch) by Shay Banon (Elasticsearch creator). The zen discovery module has two parts:

* Ping: The process nodes use to discover each other
* Unicast: The module that contains a list of hostnames to control which nodes to ping

Elasticsearch is a peer-to-peer system where all nodes communicate with each other and there is one active master which updates and controls the cluster wide state and operations. A new Elasticsearch cluster undergoes an election as part of the ping process where a node, out of all master eligible nodes, is elected as the master and other nodes join the master. The default ping_interval is 1 sec and ping_timeout is 3 sec. As nodes join, they send a join request to the master with a default join_timeout which is 20 times the ping_timeout. If the master fails, the nodes in the cluster start pinging again to start another election. This ping process also helps if a node accidentally thinks that the master has failed and discovers the master through other nodes.

> NOTE: By default, client and data nodes don’t contribute to the election process. This can be changed by setting discovery.zen.master_election.filter_client and discovery.zen.master_election.filter_data property to False in elasticsearch.yml config file.

For fault detection, the master node pings all the other nodes to check if they are alive and all the nodes ping the master back to report that they are alive.

If used with the default settings, Elasticsearch suffers from the problem of __split-brain__ where in case of a network partition, a node can think that the master is dead and elect itself as a master resulting in a cluster with multiple masters. This may result in data loss and it may not be possible to merge the data correctly. This can be avoided by setting the following property to a quorum of master eligible nodes.

> discovery.zen.minimum_master_nodes = int(# of master eligible nodes/2)+1

![alt](https://cdn-images-1.medium.com/max/800/0*6V8RZaIaiPo-ugT9.jpeg)

This property needs the quorum of active master eligible nodes to join a newly elected master for the election process to complete and have the new master accept its mastership. This is an extremely important property to ensure cluster stability and can be dynamically updated if the cluster size changes. Figure a and b show what would happen in case of a network partition when the minimum_master_nodes property is set and not set respectively.

> NOTE: For a production cluster, it is recommended to have 3 dedicated master nodes, which do not serve any client requests, out of which 1 is active at any given time.

# Concurrency
Elasticsearch is a distributed system and supports concurrent requests. When a create/update/delete request hits the primary shard, it is sent in parallel to the replica shard(s) as well, however, it is possible that these requests arrive out of order. In such cases, Elasticsearch uses optimistic concurrency control to make sure that the newer versions of the document are not overwritten by the older versions.
Every document indexed has a version number which is incremented with every change applied to that document. These version numbers are used to make sure that the changes are applied in order. To make sure that updates in our application don’t result in data loss, Elasticsearch’s API allows you to specify the current version number of a document to which the changes should be applied. If the version specified in the request is older than the one present in the shard, the request fails, which means that the document has been updated by another process. How failed requests are handled can be controlled at the application level. There are also other locking options available and you can read about them [here](https://www.elastic.co/guide/en/elasticsearch/guide/2.x/concurrency-solutions.html).

As we send concurrent requests to Elasticsearch, the next concern is — how can we make these requests consistent? Now, it is unclear to answer which side of the CAP triangle Elasticsearch falls on and this has been a debate which we are not going to settle in this post.

![alt](https://cdn-images-1.medium.com/max/800/0*xmG0SmUWB3poSXr7.jpeg)

However, we’ll review how to achieve consistent writes and reads with Elasticsearch.

# Consistency — Ensuring consistent writes and reads
For writes, Elasticsearch supports consistency levels, different from most other databases, to allow a preliminary check to see how many shards are available for the write to be permissible. The available options are __quorum__, __one__ and __all__. __By default it is set to quorum and that means that a write operation will be permitted only if a majority of the shards are available.__ With a majority of the shards available, it may still happen that the writes to a replica fail for some reason and in that case, the replica is said to be faulty and the shard would be rebuilt on a different node.

For reads, new documents are not available for search until after the refresh interval. To make sure that the search request returns results from the latest version of the document, replication can be set to sync (default) which returns the write request after the operation has been completed on both primary and replica shards. In this case, search request from any shard will return results from the latest version of the document. Even if your application requires replication=async for higher indexing rate, there is a _preference parameter which can be set to primary for search requests. That way, the primary shard is queried for search requests and it ensures that the results will be from the latest version of the document.

As we understand how Elasticsearch deals with consensus, concurrency and consistency, let’s review some of the important concepts internal to a shard that result in certain characteristics of Elasticsearch as a distributed search engine.

# Translog
The concept of a __write ahead log (WAL)__ or a __transaction log (translog)__ has been around in the database world since the development of relational databases. A translog ensures data integrity in the event of failure with the underlying principle that the intended changes must be logged and committed before the actual changes to the data are committed to the disk.

When new documents are indexed or old ones are updated, the Lucene index changes and these changes will be committed to the disk for persistence. It is a very expensive operation to be performed after every write request and hence, it is performed in a way to persist multiple changes to the disk at once. As we described in a previous blog, flush operation (Lucene commit) is performed by default every 30 min or when the translog gets too big (default is 512MB). In such a scenario, there is a possibility to lose all the changes between two Lucene commits. To avoid this issue, Elasticsearch uses a translog. All the index/delete/update operations are written to the translog and the translog is fsync’ed after every index/delete/update operation (or every 5 sec by default) to make sure the changes are persistent. The client receives acknowledgement for writes after the translog is fsync’ed on both primary and replica shards.

In case of a hardware failure between two Lucene commits or a restart, the translog is replayed to recover from any lost changes before the last Lucene commit and all the changes are applied to the index.

> NOTE: It is recommended to explicitly flush the translog before restarting Elasticsearch instances, as the startup will be faster because the translog to be replayed will be empty. POST /_all/_flush command can be used to flush all indices in the cluster.

With the translog flush operation, the segments in the filesystem cache are committed to the disk to make changes in the index persistent. Let’s now see what Lucene segments are.

# Lucene Segments
A Lucene index is made up of multiple segments and a segment is a fully functional inverted index in itself. Segments are immutable which allows Lucene to add new documents to the index incrementally without rebuilding the index from scratch. For every search request, all the segments in an index are searched, and each segment consumes CPU cycles, file handles and memory. This means that the higher the number of segments, the lower the search performance will be.

To get around this problem, Elasticsearch merges small segments together into a bigger segment (as shown in the figure below), commits the new merged segment to the disk and deletes the old smaller segments.

![alt](https://cdn-images-1.medium.com/max/800/0*ubmOoIQwtK0RouaB.jpeg)

This automatically happens in the background without interrupting indexing or searching. Since segment merging can use up resources and affect search performance, Elasticsearch throttles the merging process to have enough resources available for search.




































