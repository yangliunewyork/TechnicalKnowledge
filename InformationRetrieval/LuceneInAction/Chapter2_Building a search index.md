Despite the great detail we’ll go into, don’t forget the big picture: indexing is simply a means to an end. What matters is the search experience your applications present to your users; indexing is “merely” the necessary evil you must go through in order to enable a strong user search experience. So although there are fun details here about indexing, your time is generally better spent working on how to improve the search experience. In nearly every application, the search features are far more important than the details of indexing. That being said, implementing search features requires important corresponding steps during indexing, as you’ll see here.

## 2.1 How Lucene models content

### 2.1.1 Documents and fields

A document is Lucene’s atomic unit of indexing and searching. It’s a container that holds one or more fields, which in turn contain the “real” content. Each field has a name to identify it, a text or binary value, and a series of detailed options that describe what Lucene should do with the field’s value when you add the document to the index. To index your raw content sources, you must first translate it into Lucene’s documents and fields. Then, at search time, it’s the field values that are searched; for example, users could search for “title:lucene” to find all documents whose title field value contains the term lucene.

At a high level, there are three things Lucene can do with each field:

* The value may be indexed (or not). __A field must be indexed if you intend to search on it.__ Only text fields may be indexed (binary valued fields may only be stored). When a field is indexed, tokens are first derived from its text value, using a process called __analysis__, and then those tokens are enrolled into the index.

* If it’s indexed, the field may also optionally store __term vectors__, which are collectively a miniature inverted index for that one field, allowing you to retrieve all of its tokens. This enables certain advanced use cases, like searching for documents similar to an existing one.

* Separately, the field’s value may be stored, meaning a verbatim copy of the unanalyzed value is written away in the index so that it can later be retrieved. This is useful for fields you’d like to present unchanged to the user, such as the document’s title or abstract.

How you factor your raw content sources into Lucene’s documents and fields is typically an iterative design process that’s application dependent. Lucene couldn’t care less which fields you use, what their names are, and so forth. Documents usually have quite a few fields, such as title, author, date, abstract, body text, URL, and keywords. Sometimes a catchall field is used, combining all text into a single field for searching. Once you’ve created your document, you add it to your index. Then, at search time, you can retrieve the documents that match each query and use their stored fields to present results to the end user.

Lucene is often compared to a database, because both can store content and retrieve it later. But there are important differences. The first one is Lucene’s flexible schema.

> NOTE : When you retrieve a document from the index, only the stored fields will be present. For example, fields that were indexed but not stored won’t be in the document. This behavior is frequently a source of confusion.

### 2.1.2 Flexible schema

Unlike a database, Lucene has no notion of a fixed global schema. In other words, each document you add to the index is a blank slate and can be completely different from the document before it: it can have whatever fields you want, with any indexing and storing and term vector options. It need not have the same fields as the previous document you added. It can even have the same fields, with different options, than in other documents.

This feature is quite powerful: it allows you to take an iterative approach to building your index. You can jump right in and index documents without having to predesign the schema. If you change your mind about your fields, start adding additional fields later on and then go back and reindex previously added documents, or rebuild the index.

Lucene’s flexible schema also means a single index can hold documents that represent different entities. For instance, you could have documents that represent retail products with fields such as name and price, and documents that represent people with fields such as name, age, and gender. You could also include unsearchable “meta” documents, which simply hold metadata about the index or your application (such as what time the index was last updated or which product catalog was indexed) but are never included in search results.

The second major difference between Lucene and databases is that Lucene requires you to flatten, or denormalize, your content when you index it.

### 2.1.3 Denormalization

One common challenge is resolving any “mismatch” between the structure of your documents versus what Lucene can represent. For example, XML can describe a recursive document structure by nesting tags within one another. A database can have an arbitrary number of joins, via primary and secondary keys, relating tables to one other. Microsoft’s Object Linking & Embedding (OLE) documents can reference other documents for embedding. Yet Lucene documents are flat. Such recursion and joins must be denormalized when creating your documents. Open source projects that build on Lucene, like Hibernate Search, Compass, LuSQL, DBSight, Browse Engine, and Oracle/Lucene integration, each has different and interesting approaches for handling this denormalization.

## 2.2 Understanding the indexing process

During indexing, the text is first extracted from the original content and used to create an instance of Document, containing Field instances to hold the content. The text in the fields is then analyzed to produce a stream of tokens. Finally, those tokens are added to the index in a segmented architecture. Let’s talk about text extraction first.

### 2.2.1 Extracting text and creating the document

To index data with Lucene, you must extract plain text from it, the format that Lucene can digest, and then create a Lucene document.

Suppose you need to index a set of manuals in PDF format. To prepare these manuals for indexing, you must first find a way to extract the textual information from the PDF documents and use that extracted text to create Lucene documents and their fields. No methods would accept a PDF Java type, even if such a type existed. You face the same situation if you want to index Microsoft Word documents or any document format other than plain text. Even when you’re dealing with XML or HTML documents, which use plain-text characters, you still need to be smart about preparing the data for indexing, to avoid indexing the XML elements or HTML tags and index only the real text.

### 2.2.2 Analysis

Once you’ve created Lucene documents populated with fields, you can call ```IndexWriter```’s _addDocument_ method and hand your data off to Lucene to index. When you do that, Lucene first analyzes the text, a process that splits the textual data into a stream of tokens, and performs a number of optional operations on them. For instance, the tokens could be lowercased before indexing, to make searches case insensitive, using Lucene’s ```LowerCaseFilter```. Typically it’s also desirable to remove all stop words, which are frequent but meaningless tokens, from the input (for example a, an, the, in, on, and so on, in English text) using ```StopFilter```. Similarly, it’s common to process input tokens to reduce them to their roots, for example by using ```PorterStemFilter``` for English text (similar classes exist in Lucene’s contrib analysis module, for other languages). The combination of an original source of tokens, followed by the series of filters that modify the tokens produced by that source, make up the analyzer. You are also free to build your own analyzer by chaining together Lucene’s token sources and filters, or your own, in customized ways.

This important step, covered under the Analyze Document step in figure 1.4, is called __analysis__. The input to Lucene can be analyzed in so many interesting and useful ways that we cover this process in detail in chapter 4. __The analysis process produces a stream of tokens that are then written into the files in the index.__

### 2.2.3 Adding to the index

After the input has been analyzed, it’s ready to be added to the index. Lucene stores the input in a data structure known as an __inverted index__. This data structure makes efficient use of disk space while allowing quick keyword lookups. What makes this structure inverted is that it uses tokens extracted from input documents as lookup keys instead of treating documents as the central entities, much like the index of this book references the page number(s) where a concept occurs. In other words, rather than trying to answer the question “What words are contained in this document?” this structure is optimized for providing quick answers to “Which documents contain word X?”

![alt](http://karthikkumar.me/images/intro-to-lucene/inverted_index.jpg)

If you think about your favorite web search engine and the format of your typical query, you’ll see that this is exactly the query that you want to be as quick as possible. The core of today’s web search engines are inverted indexes.

Lucene’s index directory has a unique segmented architecture, which we describe next.

##### INDEX SEGMENTS

Every Lucene index consists of one or more segments. Each __segment__ is a standalone index, holding a subset of all indexed documents. A new segment is created whenever the writer flushes buffered added documents and pending deletions into the directory. __At search time, each segment is visited separately and the results are combined.__

Each segment, in turn, consists of multiple files, of the form _X.<ext>, where X is the segment’s name and <ext> is the extension that identifies which part of the index that file corresponds to. There are separate files to hold the different parts of the index (term vectors, stored fields, inverted index, and so on). If you’re using the compound file format (which is enabled by default but you can change using Index- Writer.setUseCompoundFile), then most of these index files are collapsed into a single compound file: _X.cfs. This reduces the number of open file descriptors during searching, at a small cost of searching and indexing performance.

There’s one special file, referred to as the segments file and named segments_<N>, that references all live segments. This file is important! Lucene first opens this file, and then opens each segment referenced by it. The value <N>, called “the generation,” is an integer that increases by one every time a change is committed to the index.

Naturally, over time the index will accumulate many segments, especially if you open and close your writer frequently. This is fine. Periodically, __IndexWriter__ will select segments and coalesce them by merging them into a single new segment and then removing the old segments. The selection of segments to be merged is governed by a separate __MergePolicy__. Once merges are selected, their execution is done by the __MergeScheduler__.

## 2.3 Basic index operations

### 2.3.1 Adding documents to an index

Let's look at how to create a new index and add documents to it. There are two methods for adding documents: 

* addDocument(Document) - adds the document using the default analyzer, which you specified when creating the IndexWriter, for tokenization. 

* addDocument(Document, Analyzer) - adds the document using the provided analyzer for tokenization. But be careful! In order for searches to work correctly, you need the analyzer used at search time to "match" the tokens produced by the analyzers at indexing time. 

```java

import junit.framework.TestCase;
import org.apache.lucene.analysis.WhitespaceAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.TermQuery;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.RAMDirectory;

public class IndexingTest extends TestCase {

    protected String[] ids = {"1", "2"};
    protected String[] unindexed = {"Netherlands", "Italy"};
    protected String[] unstored = {"Amsterdam has lots of bridges",
            "Venice has lots of canals"};
    protected String[] text = {"Amsterdam", "Venice"};
    private Directory directory;
    protected void setUp() throws Exception {
        // First creates a new RAMDirectory, to hold the index.
        directory = new RAMDirectory();
        // Freates an IndexWriter on this Directory. We created the getWriter convenience
        //method because we need to get the IndexWriter in many places.
        IndexWriter writer = getWriter();
        // Iterates over our content, creating a Document and Fields, and then
        // adds the Document to the index.
        for (int i = 0; i < ids.length; i++)
        {
            Document doc = new Document();
            doc.add(new Field("id", ids[i],
                    Field.Store.YES,
                    Field.Index.NOT_ANALYZED));
            doc.add(new Field("country", unindexed[i],
                    Field.Store.YES,
                    Field.Index.NO));
            doc.add(new Field("contents", unstored[i],
                    Field.Store.NO,
                    Field.Index.ANALYZED));
            doc.add(new Field("city", text[i],
                    Field.Store.YES,
                    Field.Index.ANALYZED));
            writer.addDocument(doc);
        }
        writer.close();
    }
    private IndexWriter getWriter() throws IOException {
        return new IndexWriter(directory, new WhitespaceAnalyzer(),
                IndexWriter.MaxFieldLength.UNLIMITED);
    }

    // We create the IndexSearcher and execute a basic single-term query with the specified
    //string, returning the number of documents that matched.
    protected int getHitCount(String fieldName, String searchString)
            throws IOException {
        IndexSearcher searcher = new IndexSearcher(directory);
        Term t = new Term(fieldName, searchString);
        Query query = new TermQuery(t);
        int hitCount = TestUtil.hitCount(searcher, query);
        searcher.close();
        return hitCount;
    }

    // We verify the documents counts according to IndexReader and IndexWriter matches
    //how many documents we added.
    public void testIndexWriter() throws IOException {
        IndexWriter writer = getWriter();
        assertEquals(ids.length, writer.numDocs());
        writer.close();
    }
    public void testIndexReader() throws IOException {
        IndexReader reader = IndexReader.open(directory);
        assertEquals(ids.length, reader.maxDoc());
        assertEquals(ids.length, reader.numDocs());
        reader.close();
    }
}
```

### 2.3.2 Deleting documents from an index

Although most applications are more concerned with getting documents into a Lucene index, some also need to remove them. For instance, a newspaper publisher may want to keep only the last week’s worth of news in its searchable indexes. Other applications may want to remove all documents that contain a certain term or replace an old version of a document with a newer one whenever the original source of the document has changed. IndexWriter provides various methods to remove documents from an index:

* deleteDocuments(Term) deletes all documents containing the provided term.
* deleteDocuments(Term[])deletes all documents containing any of the terms in the provided array.
* deleteDocuments(Query) deletes all documents matching the provided query.
* deleteDocuments(Query[])deletes all documents matching any of the queries in the provided array.
* deleteAll() deletes all documents in the index. This is exactly the same as closing the writer and opening a new writer with create=true, without having to close your writer.

In each case, the deletes aren't done immediately. Instead, they're buffered in memory, just like the added documents, and periodically flushed to the directory. As with added documents, you must call commit() or close() on your writer to commit the changes to the index. Even once the deletes are flushed to the directory, the disk space consumed by that document isn't immediately freed. Rather, the documents are simply marked as deleted.

### 2.3.3 Updating documents in the index

In many applications, after initially indexing a document you may still want to make further changes to it, requiring you to reindex it. For example, if your documents are crawled from a web server, one way to detect that the content has changed is to look for a changed ETag HTTP header. If it’s different from when you last indexed the document, that means changes have been made to the content and you should update the document in the index.

__In some cases you may want to update only certain fields of the document. Perhaps the title changed but the body was unchanged. Unfortunately, although this is a frequently requested feature, Lucene can’t do that: instead, it deletes the entire previous document and then adds a new document to the index.__ This requires that the new document contains all fields, even unchanged ones, from the original document. IndexWriter provides two convenience methods to replace a document in the index:

* updateDocument(Term, Document) first deletes all documents containing the provided term and then adds the new document using the writer’s default analyzer.  
* updateDocument(Term, Document, Analyzer) does the same but uses the provided analyzer instead of the writer’s default analyzer.  

## 2.4 Field options

