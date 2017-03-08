## Full-text searching
Back in the days when full-text searching was a term known to a small percentage of engineers, most of us used SQL databases to perform search operations. Of course, it is ok, at least to some extent. However, as you go deeper and deeper, you start to see the limits of such an approach. Just to mention some of them—lack of scalability, not enough flexibility, and lack of language analysis (of course there were additions that introduced full-text searching to SQL databases). These were the reasons why Apache Lucene (http://lucene.apache.org) was created—to provide a library of full text search capabilities. It is very fast, scalable, and provides analysis capabilities for different languages.

### The Lucene glossary and architecture
Before going into the details of the analysis process, we would like to introduce you to the glossary for Apache Lucene and the overall architecture of Apache Lucene. The basic concepts of the mentioned library are as follows:

*  Document: This is the main data carrier used during indexing and searching, comprising one or more fields that contain the data we put in and get from Lucene.
* Field: This a section of the document, which is built of two parts: the name and the value.
* Term: This is a unit of search representing a word from the text.
* Token: This is an occurrence of a term in the text of the field. It consists of the term text, start and end offsets, and a type.

Apache Lucene writes all the information to a structure called the inverted index. It is a data structure that maps the terms in the index to the documents and not the other way around as a relational database does in its tables. You can think of an inverted index as a data structure where data is term-oriented rather than document-oriented.

![alt](http://karthikkumar.me/images/intro-to-lucene/inverted_index.jpg)

Each index is divided into multiple write-once and read-many-time structures called segments. Each segment is a miniature Apache Lucene index on its own. When indexing, after a single segment is written to the disk it can't be updated, or we should rather say it can't be fully updated; documents can't be removed from it, they can only be marked as deleted in a separate file. The reason that Lucene doesn't allow segments to be updated is the nature of the inverted index. After the fields are analyzed and put into the inverted index, there is no easy way of building the original document structure. When deleting, Lucene would have to delete the information from the segment, which translates to updating all the information within the inverted index itself. 

Because of the fact that segments are write-once structures Lucene is able to merge segments together in a process called segment merging. During indexing, if Lucene thinks that there are too many segments falling into the same criterion, a new and bigger segment will be created—one that will have data from the other segments. During that process, Lucene will try to remove deleted data and get back the space needed to hold information about those documents. Segment merging is a demanding operation both in terms of the I/O and CPU. What we have to remember for now is that searching with one large segment is faster than searching with multiple smaller ones holding the same data. That's because, in general, searching translates to just matching the query terms to the ones that are indexed. You can imagine how searching through multiple small segments and merging those results will be slower than having a single segment preparing the results.


### Input data analysis
The transformation of a document that comes to Lucene and is processed and put into the inverted index format is called __indexation__. One of the things Lucene has to do during this is data analysis. You may want some of your fields to be processed by a __language analyzer__ so that words such as car and cars are treated as the same be your index. On the other hand, you may want other fields to be divided only on the white space character or be only lowercased.

__Analysis is done by the analyzer, which is built of a tokenizer and zero or more token filters, and it can also have zero or more character mappers.__ A tokenizer in Lucene is used to split the text into tokens, which are basically the terms with additional information such as its position in the original text and its length. The results of the tokenizer's work is called a __token stream__, where the tokens are put one by one and are ready to be processed by the filters.

Apart from the tokenizer, the Lucene analyzer is built of zero or more token filters that are used to process tokens in the token stream. Some examples of filters are as follows: 
* Lowercase filter: Makes all the tokens lowercased 
* Synonyms filter: Changes one token to another on the basis of synonym rules 
* Language stemming filters: Responsible for reducing tokens (actually, the text part that they provide) into their root or base forms called the stem (https://en.wikipedia.org/wiki/Word_stem).

Filters are processed one after another, so we have almost unlimited analytical possibilities with the addition of multiple filters, one after another.

Finally, the __character mappers__ operate on non-analyzed text—they are used before the tokenizer. Therefore, we can easily remove HTML tags from whole parts of text without worrying about tokenization.

### Indexing and querying
You may wonder how all the information we've described so far affects indexing and querying when using Lucene and all the software that is built on top of it. During indexing, Lucene will use an analyzer of your choice to process the contents of your document; of course, different analyzers can be used for different fields, so the name field of your document can be analyzed differently compared to the summary field. For example, the name field may only be tokenized on whitespaces and lowercased, so that exact matches are done and the summary field is stemmed in addition to that. We can also decide to not analyze the fields at all—we have full control over the analysis process.

During a query, your query text can be analyzed as well. However, you can also choose not to analyze your queries. This is crucial to remember because some Elasticsearch queries are analyzed and some are not. For example, prefix and term queries are not analyzed, and match queries are analyzed. Having queries that are analyzed and not analyzed is very useful; sometimes, you may want to query a field that is not analyzed, while sometimes you may want to have a full text search analysis. For example, if we search for the LightRed term and the query is being analyzed by the standard analyzer, then the terms that would be searched are light and red. If we use a query type that has not been analyzed, then we will explicitly search for the LightRed term. We may not want to analyze the content of the query if we are only interested in exact matches.

What you should remember about indexing and querying analysis is that the index should match the query term. If they don't match, Lucene won't return the desired documents. For example, if you use stemming and lowercasing during indexing, you need to ensure that the terms in the query are also lowercased and stemmed, or your queries won't return any results at all. For example, let's get back to our LightRed term that we analyzed during indexing; we have it as two terms in the index: light and red. If we run a LightRed query against that data and don't analyze it, we won't get the document in the results—the query term does not match the indexed terms. It is important to keep the token filters in the same order during indexing and query time analysis so that the terms resulting from such an analysis are the same.

### Scoring and query relevance
There is one additional thing that we only mentioned once till now—scoring. What is the score of a document? The score is a result of a scoring formula that describes how well the document matches the query. By default, Apache Lucene uses the __TF/IDF (term frequency/inverse document frequency)__ scoring mechanism, which is an algorithm that calculates how relevant the document is in the context of our query. Of course, it is not the only algorithm available.

## The basics of Elasticsearch
Elasticsearch is an open source search server project started by Shay Banon and published in February 2010. During this time, the project grew into a major player in the field of search and data analysis solutions and is widely used in many common or lesser-known search and data analysis platforms. In addition, due to its distributed nature and real-time search and analytics capabilities, many organizations use it as a document store.

### Key concepts of Elasticsearch

#### Index
An index is the logical place where Elasticsearch stores the data. Each index can be spread onto multiple Elasticsearch nodes and is divided into one or more smaller pieces called shards that are physically placed on the hard drives. If you are coming from the relational database world, you can think of an index like a table. However, the index structure is prepared for fast and efficient full text searching and, in particular, does not store original values. That structure is called an inverted index (https://en.wikipedia.org/wiki/Inverted_index).

Elasticsearch can hold many indices located on one machine or spread them over multiple servers. As we have already said, every index is built of one or more shards, and each shard can have many replicas.

#### Document
The main entity stored in Elasticsearch is a document. A document can have multiple fields, each having its own type and treated differently. Using the analogy to relational databases, a document is a row of data in a database table. When you compare an Elasticsearch document to a MongoDB document, you will see that both can have different structures. The thing to keep in mind when it comes to Elasticsearch is that fields that are common to multiple types in the same index need to have the same type. This means that all the documents with a field called title need to have the same data type for it, for example, string.

Documents consist of fields, and each field may occur several times in a single document (such a field is called multivalued). Each field has a type (text, number, date, and so on). The field types can also be complex—a field can contain other subdocuments or arrays. The field type is important to Elasticsearch because type determines how various operations such as analysis or sorting are performed. Fortunately, this can be determined automatically (however, we still suggest using mappings; take a look at what follows).

Unlike the relational databases, documents don't need to have a fixed structure— every document may have a different set of fields, and in addition to this, fields don't have to be known during application development. Of course, one can force a document structure with the use of schema. From the client's point of view, a document is a JSON object (see more about the JSON format at https:// en.wikipedia.org/wiki/JSON). Each document is stored in one index and has its own unique identifier, which can be generated automatically by Elasticsearch, and document type. The thing to remember is that the document identifier needs to be unique inside an index and should be for a given type. This means that, in a single index, two documents can have the same unique identifier if they are not of the same type.

#### Document Type
In Elasticsearch, one index can store many objects serving different purposes. For example, a blog application can store articles and comments. The document type lets us easily differentiate between the objects in a single index. Every document can have a different structure, but in real-world deployments, dividing documents into types significantly helps in data manipulation. Of course, one needs to keep the limitations in mind. That is, different document types can't set different types for the same property. For example, a field called title must have the same type across all document types in a given index.

#### Mapping
Every field of the document must be properly analyzed depending on its type. For example, a different analysis chain is required for the numeric fields (numbers shouldn't be sorted alphabetically) and for the text fetched from web pages (for example, the first step would require you to omit the HTML tags as it is useless information). To be able to properly analyze at indexing and querying time, Elasticsearch stores the information about the fields of the documents in so-called mappings. Every document type has its own mapping, even if we don't explicitly define it.



### Key concepts of the Elasticsearch infrastructure
Now, we already know that Elasticsearch stores its data in one or more indices and every index can contain documents of various types. We also know that each document has many fields and how Elasticsearch treats these fields is defined by the mappings. But there is more. From the beginning, Elasticsearch was created as a distributed solution that can handle billions of documents and hundreds of search requests per second. This is due to several important key features and concepts that we are going to describe in more detail now.

#### Nodes and clusters
Elasticsearch can work as a standalone, single-search server. Nevertheless, to be able to process large sets of data and to achieve fault tolerance and high availability, Elasticsearch can be run on many cooperating servers. Collectively, these servers connected together are called a cluster and each server forming a cluster is called a node.

#### Shards
When we have a large number of documents, we may come to a point where a single node may not be enough—for example, because of RAM limitations, hard disk capacity, insufficient processing power, and an inability to respond to client requests fast enough. In such cases, an index (and the data in it) can be divided into smaller parts called shards (where each shard is a separate Apache Lucene index). Each shard can be placed on a different server, and thus your data can be spread among the cluster nodes. When you query an index that is built from multiple shards, Elasticsearch sends the query to each relevant shard and merges the result in such a way that your application doesn't know about the shards. In addition to this, having multiple shards can speed up indexing, because documents end up in different shards and thus the indexing operation is parallelized.

#### Replicas
In order to increase query throughput or achieve high availability, shard replicas can be used. A replica is just an exact copy of the shard, and each shard can have zero or more replicas. In other words, Elasticsearch can have many identical shards and __one of them is automatically chosen as a place where the operations that change the index are directed. This special shard is called a primary shard, and the others are called replica shards.__ When the primary shard is lost (for example, a server holding the shard data is unavailable), the cluster will promote the replica to be the new primary shard.

#### Gateway
The cluster state is held by the gateway, which stores the cluster state and indexed data across full cluster restarts. By default, every node has this information stored locally; it is synchronized among nodes.

### Indexing and searching

When you send a new document to the cluster, you specify a target index and send it to any of the nodes. The node knows how many shards the target index has and is able to determine which shard should be used to store your document. The important information that you have to remember for now is that Elasticsearch calculates the shard in which the document should be placed using the unique identifier of the document—this is one of the reasons each document needs a unique identifier. After the indexing request is sent to a node, that node forwards the document to the target node, which hosts the relevant shard.

When you try to fetch a document by its identifier, the node you send the query to uses the same routing algorithm to determine the shard and the node holding the document and again forwards the request, fetches the result, and sends the result to you. On the other hand, the querying process is a more complicated one. The node receiving the query forwards it to all the nodes holding the shards that belong to a given index and asks for minimum information about the documents that match the query (the identifier and score are matched by default), unless routing is used, when the query will go directly to a single shard only. This is called the scatter phase. After receiving this information, the aggregator node (the node that receives the client request) sorts the results and sends a second request to get the documents that are needed to build the results list (all the other information apart from the document identifier and score). This is called the gather phase. After this phase is executed, the results are returned to the client.

Now the question arises: what is the replica's role in the previously described process? While indexing, replicas are only used as an additional place to store the data. When executing a query, by default, Elasticsearch will try to balance the load among the shard and its replicas so that they are evenly stressed.














