Elasticsearch is an open-source search engine built on top of Apache LuceneTM, a full- text search-engine library. Lucene is arguably the most advanced, high-performance, and fully featured search engine library in existence today—both open source and proprietary.

But Lucene is just a library. To leverage its power, you need to work in Java and to integrate Lucene directly with your application. Worse, you will likely require a degree in information retrieval to understand how it works. Lucene is very complex.

Elasticsearch is also written in Java and uses Lucene internally for all of its indexing and searching, but it aims to make full-text search easy by hiding the complexities of Lucene behind a simple, coherent, RESTful API.
However, Elasticsearch is much more than just Lucene and much more than “just” full-text search. It can also be described as follows:

* A distributed real-time document store where every field is indexed and searchable  
* A distributed search engine with real-time analytics  
* Capable of scaling to hundreds of servers and petabytes of structured and unstructured data  

And it packages up all this functionality into a standalone server that your application can talk to via a simple RESTful API, using a web client from your favorite program‐ ming language, or even from the command line.

