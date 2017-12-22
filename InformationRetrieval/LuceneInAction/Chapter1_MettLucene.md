## 1.2 What is Lucene?

Lucene is a high-performance, scalable information retrieval (IR) library. IR refers to the process of searching for documents, information within documents, or metadata about documents. Lucene lets you add searching capabilities to your applications. It抯 a mature, free, open source project implemented in Java, and a project in the Apache Software Foundation, licensed under the liberal Apache Software License. As such, Lucene is currently, and has been for quite a few years, the most popular free IR library.

> Throughout the book, we’ll use the term information retrieval (or its acronym IR) to describe search tools like Lucene. People often refer to IR libraries as search engines, but you shouldn’t confuse IR libraries with web search engines.

Lucene’s website, at http://lucene.apache.org/java, is a great place to learn more about the current status of Lucene. There you’ll find the tutorial, Javadocs for Lucene’s API for all recent releases, an issue-tracking system, links for downloading releases, and Lucene’s wiki (http://wiki.apache.org/lucene-java), which contains many community-created and -maintained pages.

### 1.2.1 What Lucene can do

People new to Lucene often mistake it for a ready-to-use application like a file-search program, a web crawler, or a website search engine. That isn抰 what Lucene is: Lucene is a software library, a toolkit if you will, not a full-featured search application. It concerns itself with text indexing and searching, and it does those things very well. Lucene lets your application deal with business rules specific to its problem domain while hiding the complexity of indexing and searching behind a simple-to-use API. Lucene is the core that the application wraps around.

Lucene allows you to add search capabilities to your application. Lucene can index and make searchable any data that you can extract text from. Lucene doesn’t care about the source of the data, its format, or even its language, as long as you can derive text from it. This means you can index and search data stored in files: web pages on remote web servers, documents stored in local file systems, simple text files, Microsoft Word documents, XML or HTML or PDF files, or any other format from which you can extract textual information.

## 1.3 Lucene and the components of a search application

It’s important to grasp the big picture so that you have a clear understanding of which parts Lucene can handle and which parts your application must separately handle. A common misconception is that Lucene is an entire search application, when in fact it’s simply the core indexing and searching component.

We’ll see that a search application starts with an indexing chain, which in turn requires separate steps to retrieve the raw content; create documents from the content, possibly extracting text from binary documents; and index the documents. Once the index is built, the components required for searching are equally diverse, including a user interface, a means for building up a programmatic query, query execution (to retrieve matching documents), and results rendering.

Modern search applications have wonderful diversity. Some run quietly, as a small component deeply embedded inside an existing tool, searching a specific set of content (local files, email messages, calendar entries, etc.). Others run on a remote website, on a dedicated server infrastructure, interacting with many users via a web browser or mobile device, perhaps searching a product catalog or a known and clearly scoped set of documents. Some run inside a company’s intranet and search a massive collection of documents visible inside the company. Still others index a large subset of the entire web and must deal with unbelievable scale both in content and in simultaneous search traffic. Yet despite all this variety, search engines generally share a common overall architecture.

![alt](https://image.slidesharecdn.com/basicsofsearchenginesandalgorithms-140719133624-phpapp02/95/basics-of-search-engines-and-algorithms-9-638.jpg)

### 1.3.1 Components for indexing

Suppose you need to search a large number of files, and you want to find files that contain a certain word or a phrase. How would you go about writing a program to do this? A naïve approach would be to sequentially scan each file for the given word or phrase. Although this approach would work, it has a number of flaws, the most obvious of which is that it doesn’t scale to larger file sets or cases where files are very large. Here’s where indexing comes in: to search large amounts of text quickly, you must first index that text and convert it into a format that will let you search it rapidly, eliminating the slow sequential scanning process. This conversion process is called __indexing__, and its output is called an __index__.

##### ACQUIRE CONTENT

The first step, is to acquire content. This process, which involves using a crawler or spider, gathers and scopes the content that needs to be indexed. That may be trivial, for example, if you’re indexing a set of XML files that resides in a specific directory in the file system or if all your content resides in a wellorganized database. Alternatively, it may be horribly complex and messy if the content is scattered in all sorts of places (file systems, content management systems, Microsoft Exchange, Lotus Domino, various websites, databases, local XML files, CGI scripts running on intranet servers, and so forth).

Using entitlements (which means allowing only specific authenticated users to see certain documents) can complicate content acquisition, because it may require “superuser” access when acquiring the content. Furthermore, the access rights or access control lists (ACLs) must be acquired along with the document’s content, and added to the document as additional fields used during searching to properly enforce the entitlements.

For large content sets, it’s important that this component be efficiently incremental, so that it can visit only changed documents since it was last run. It may also be “live,” meaning it’s a continuously running service, waiting for new or changed content to arrive and loading that content the moment it becomes available.

Lucene, as a core search library, doesn’t provide any functionality to support acquiring content. This is entirely up to your application, or a separate piece of software. 

If your application has scattered content, it might make sense to use a preexisting crawling tool. Such tools are typically designed to make it easy to load content stored in various systems, and sometimes provide prebuilt connectors to common content stores, such as websites, databases, popular content management systems, and file systems. If your content source doesn’t have a preexisting connector for the crawler, it’s likely easy enough to build your own.

The next step is to create bite-sized pieces, called documents, out of your content.

##### BUILD DOCUMENT

Once you have the raw content that needs to be indexed, you must translate the content into the __units__ (usually called __documents__) used by the search engine. The document typically consists of several separately named fields with values, such as title, body, abstract, author, and url. You’ll have to carefully design how to divide the raw content into documents and fields as well as how to compute the value for each of those fields. Often the approach is obvious: one email message becomes one document, or one PDF file or web page is one document. But sometimes it’s less clear: how should you handle attachments on an email message? Should you glom together all text extracted from the attachments into a single document, or make separate documents, somehow linked back to the original email message, for each attachment?

Once you’ve worked out this design, you’ll need to extract text from the original raw content for each document. If your content is already textual in nature, with a known standard encoding, your job is simple. But more often these days documents are binary in nature (PDF, Microsoft Office, Open Office, Adobe Flash, streaming video and audio multimedia files) or contain substantial markups that you must remove before indexing (RDF, XML, HTML). You’ll need to run document filters to extract text from such content before creating the search engine document.

Interesting business logic may also apply during this step to create additional fields. For example, if you have a large “body text” field, you might run semantic analyzers to pull out proper names, places, dates, times, locations, and so forth into separate fields in the document. Or perhaps you tie in content available in a separate store (such as a database) and merge this for a single document to the search engine.

Another common part of building the document is to inject __boosts__ to individual documents and fields that are deemed more or less important. Perhaps you’d like your press releases to come out ahead of all other documents, all things being equal? Perhaps recently modified documents are more important than older documents? __Boosting may be done statically (per document and field) at indexing time,  or dynamically during searching.__ Nearly all search engines, including Lucene, automatically statically boost fields that are shorter over fields that are longer. Intuitively this makes sense: if you match a word or two in a very long document, it’s quite a bit less relevant than matching the same words in a document that’s, say, three or four words long.

##### ANALYZE DOCUMENT

No search engine indexes text directly: rather, the text must be broken into a series of individual atomic elements called tokens. This is what happens during the Analyze Document step. Each token corresponds roughly to a “word” in the language, and this step determines how the textual fields in the document are divided into a series of tokens. There are all sorts of interesting questions here: how do you handle compound words? Should you apply spell correction (if your content itself has typos)? Should you inject synonyms inlined with your original tokens, so that a search for “laptop” also returns products mentioning “notebook”? Should you collapse singular and plural forms to the same token? Often a stemmer, such as Dr. Martin Porter’s Snowball stemmer is used to derive roots from words (for example, runs, running, and run, all map to the base form run). Should you preserve or destroy differences in case? For non-Latin languages, how can you even determine what a “word” is?

Lucene provides an array of built-in analyzers that give you fine control over this process. It’s also straightforward to build your own analyzer, or create arbitrary analyzer chains combining Lucene’s tokenizers and token filters, to customize how tokens are created. The final step is to index the document.

##### INDEX DOCUMENT

During the indexing step, the document is added to the index. Lucene provides everything necessary for this step, and works quite a bit of magic under a surprisingly simple API.

### 1.3.2 Components for searching

Searching is the process of looking up words in an index to find documents where they appear. The quality of a search is typically described using precision and recall metrics. Recall measures how well the search system finds relevant documents; precision measures how well the system filters out the irrelevant documents.

You must consider a number of other factors when thinking about searching. We already mentioned speed and the ability to quickly search large quantities of text. Support for single and multiterm queries, phrase queries, wildcards, fuzzy queries, result ranking, and sorting are also important, as is a friendly syntax for entering those queries.

##### SEARCH USER INTERFACE

The user interface is what users actually see, in the web browser, desktop application, or mobile device, when they interact with your search application. The UI is the most important part of your search application! You could have the greatest search engine in the world under the hood, tuned with fabulous state-of-the-art functionality, but with one silly mistake, the UI will lack consumability, thus confusing your precious and fickle users who will then quietly move on to your competitors. 

Keep the interface simple: don’t present a lot of advanced options on the first page. Provide a ubiquitous, prominent search box, visible everywhere, rather than requiring a two-step process of first clicking a search link and then entering the search text (this is a common mistake).

Don’t underestimate the importance of result presentation. Simple details, like failing to highlight matches in the titles and excerpts, or using a small font and cramming too much text into the results, can quickly kill a user’s search experience. Be sure the sort order is clearly called out and defaults to an appropriate starting point (usually relevance). Be fully transparent: if your search application is doing something “interesting,” such as expanding the search to include synonyms, using boosts to influence sort order, or automatically correcting spelling, say so clearly at the top of the search results and make it easy for the user to turn it off.

> The worst thing that can happen, and it happens quite easily, is to erode the user’s trust in the search results. Once this happens, your users will quietly move on and you may never again have the chance to earn back that trust.

Most of all, eat your own dog food: use your own search application extensively. Enjoy what’s good about it, but aggressively correct what’s bad. Almost certainly your search interface should offer spell correction. Lucene has a contrib module, spellchecker,that you can use. Likewise, providing dynamic excerpts (sometimes called summaries) with hit highlighting under each search result is important, and Lucene’s contrib directory offers two such modules, highlighter and fast vector highlighter, to handle this.

Lucene doesn’t provide any default search UI; it’s entirely up to your application to build one. Once a user interacts with your search interface, she or he submits a search request, which first must be translated into an appropriate Query object for the search engine.

##### BUILD QUERY

When you manage to entice a user to use your search application, she or he issues a search request, often as the result of an HTML form or Ajax request submitted by a browser to your server. You must then translate the request into the search engine’s Query object. We call this the Build Query step.

Query objects can be simple or complex. Lucene provides a powerful package, called QueryParser, to process the user’s text into a query object according to a common search syntax. We’ll cover QueryParser and its syntax in chapter 3, but it’s also fully described at http://lucene.apache.org/java/3_0_0/queryparsersyntax.html. The query may contain Boolean operations, phrase queries (in double quotes), or wildcard terms. If your application has further controls on the search UI, or further interesting constraints, you must implement logic to translate this into the equivalent query. For example, if there are entitlement constraints that restrict which set of documents each user is allowed to search, you’ll need to set up filters on the query.

Many applications will at this point also modify the search query so as to boost or filter for important things, if the boosting wasn抰 done during indexing. Often an e-commerce site will boost categories of products that are more profitable, or filter out products presently out of stock (so you don抰 see that they抮e out of stock and then go elsewhere to buy them). Resist the temptation to heavily boost and filter the search results: users will catch on and lose trust.

Lucene’s default QueryParser is often sufficient for an application. Sometimes, you’ll want to use the output of QueryParser but then add your own logic afterward to further refine the query object. Still other times you want to customize the QueryParser’s syntax, or customize which Query instances it actually creates, which, thanks to Lucene’s open source nature, is straightforward.

##### SEARCH QUERY

Search Query is the process of consulting the search index and retrieving the documents matching the Query, sorted in the requested sort order. This component covers the complex inner workings of the search engine, and Lucene handles all of it for you. Lucene is also wonderfully extensible at this point, so if you’d like to customize how results are gathered, filtered, sorted, and so forth, it’s straightforward.

There are three common theoretical models of search: 

* __Pure Boolean model__—Documents either match or don’t match the provided query, and no scoring is done. In this model there are no relevance scores associated with matching documents, and the matching documents are unordered; a query simply identifies a subset of the overall corpus as matching the query. 

* __Vector space model__—Both queries and documents are modeled as vectors in a high dimensional space, where each unique term is a dimension. Relevance, or similarity, between a query and a document is computed by a vector distance measure between these vectors.  

* __Probabilistic model__—In this model, you compute the probability that a document is a good match to a query using a full probabilistic approach.

Lucene’s approach combines the vector space and pure Boolean models, and offers you controls to decide which model you’d like to use on a search-by-search basis. Finally, Lucene returns documents that you next must render in a consumable way for your users.

##### RENDER RESULTS

Once you have the raw set of documents that match the query, sorted in the right order, you then render them to the user in an intuitive, consumable manner. The UI should also offer a clear path for follow-on searches or actions, such as clicking to the next page, refining the search, or finding documents similar to one of the matches, so that the user never hits a dead end. 

We’ve finished reviewing the components of both the indexing and searching paths in a search application, but we aren’t done. Search applications also often require ongoing administration.

### 1.3.3 The rest of the search application

There’s still quite a bit more to a typical fully functional search engine, especially a search engine running on a website. You must include administration, in order to keep track of the application’s health, configure the different components, and start and stop servers. You must also include analytics, allowing you to use different views to see how your users are searching, thus giving you the necessary guidance on what’s working and what’s not. Finally, for large search applications, scaling—so that your application can handle larger and larger content sizes as well as higher and higher numbers of simultaneous search queries—is a very important feature.

##### ADMINISTRATION INTERFACE

A modern search engine is a complex piece of software and has numerous controls that need configuration. If you’re using a crawler to discover your content, the administration interface should let you set the starting URLs, create rules to scope which sites the crawler should visit or which document types it should load, set how quickly it’s allowed to read documents, and so forth. Starting and stopping servers, managing replication (if it’s a high-scale search, or if high availability failover is required), culling search logs, checking overall system health, and creating and restoring from backups are all examples of what an administration interface might offer.

Lucene has a number of configuration options that an administration interface would expose. During indexing you may need to tune the size of the RAM buffer, how many segments to merge at once, how often to commit changes, or when to optimize and purge deletes from the index. Searching also has important administration options, such as how often to reopen the reader. You’ll probably also want to expose some basic summary information of the index, such as segment and pending deletion counts. If some documents failed to be indexed properly, or queries hit exceptions while searching, your administration API would detail them.

##### ANALYTICS INTERFACE

Spanning the right side is the analytics interface, which is often a web-based UI, perhaps running under a separate server hosting a reporting engine. Analytics is important: you can gain a lot of intelligence about your users and why they do or do not buy your widgets through your website, by looking for patterns in the search logs. Some would say this is the most important reason to deploy a good search engine! If you run an e-commerce website, incredibly powerful tools—that let you see how your users run searches, which searches failed to produce satisfactory results, which results users clicked on, and how often a purchase followed or did not follow a search—enable you to optimize the buying experience of your users.

Lucene-specific metrics that could feed the analytics interface include:

* How often which kinds of queries (single term, phrase, Boolean queries, etc.) are run   
* Queries that hit low relevance   
* Queries where the user didn't click on any results (if your application tracks click-throughs)   
* How often users are sorting by specified fields instead of relevance   
* The breakdown of Lucene's search time  

You may also want to see indexing metrics, such as documents indexed per second or byte size of documents being indexed.

Lucene, since it’s a search library, doesn’t provide any analytics tools. If your search application is web based, Google Analytics is a fast way to create an analytics interface. If that doesn’t fit your needs, you can also build your own custom charts based on Google’s visualization API. The final topic we visit is scaling.

##### SCALING

One particularly tricky area is scaling of your search application. The vast majority of search applications don’t have enough content or simultaneous search traffic to require scaling beyond a single computer. Lucene indexing and searching throughput allows for a sizable amount of content on a single modern computer. Still, such applications may want to run two identical computers to ensure there’s no single point of failure (no downtime) in the event of hardware failure. This approach also enables you to pull one computer out of production to perform maintenance and upgrades without affecting ongoing searches.

There are two dimensions to scaling: net amount of content, and net query throughput. If you have a tremendous amount of content, you must divide it into shards, so that a separate computer searches each shard. A front-end server sends a single incoming query to all shards, and then coalesces the results into a single result set. If instead you have high search throughput during your peak traffic, you’ll have to take the same index and replicate it across multiple computers. A front-end load balancer sends each incoming query to the least loaded back-end computer. If you require both dimensions of scaling, as a web scale search engine will, you combine both of these practices.

A number of complexities are involved in building such an architecture. You’ll need a reliable way of replicating the search index across computers. If a computer has some downtime, planned or not, you need a way to bring it up-to-date before putting it back into production. If there are transactional requirements, so that all searchers must “go live” on a new index commit simultaneously, that adds complexity. Error recovery in a distributed setting can be complex. Finally, important functionality like spell correction and highlighting, and even how term weights are computed for scoring, are impacted by such a distributed architecture.

Lucene provides no facilities for scaling. However, both Solr and Nutch, projects under the Apache Lucene umbrella, provide support for index sharding and replication. The Katta open source project, hosted at http://katta.sourceforge.net and based on Lucene, also provides this functionality. Elastic search, at http://www.elasticsearch. com, is another option that’s also open source and based on Lucene. Before you build your own approach, it’s best to have a solid look at these existing solutions.


## 1.4 Lucene in action: a sample application

### 1.4.1 Creating an index

```java
package com.company;

import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;

import java.io.File;
import java.io.FileFilter;
import java.io.FileReader;
import java.io.IOException;

public class Indexer {
    public static void main(String[] args) throws Exception {
        if (args.length != 2) {
            throw new IllegalArgumentException("Usage: java " +
                    Indexer.class.getName()
                    + " <index dir> <data dir>");
        }
        String indexDir = args[0]; // Create index in this directory
        String dataDir = args[1]; // Index all *.txt files within this directory
        long start = System.currentTimeMillis();
        Indexer indexer = new Indexer(indexDir);
        int numIndexed;
        try {
            numIndexed = indexer.index(dataDir, new TextFilesFilter());
        } finally {
            indexer.close();
        }
        long end = System.currentTimeMillis();
        System.out.println("Indexing " + numIndexed + " files took "
                + (end - start) + " milliseconds");
    }
    private IndexWriter writer;
    public Indexer(String indexDir) throws IOException {
        Directory dir = FSDirectory.open(new File(indexDir));
        // Create Lucene IndexWriter
        writer = new IndexWriter(dir,
                new StandardAnalyzer(
                        Version.LUCENE_30),
                true,
                IndexWriter.MaxFieldLength.UNLIMITED);
    }

    public void close() throws IOException {
        writer.close(); // Close IndexWriter
    }

    public int index(String dataDir, FileFilter filter)
            throws Exception {
        File[] files = new File(dataDir).listFiles();
        for (File f: files) {
            if (!f.isDirectory() &&
                    !f.isHidden() &&
                    f.exists() &&
                    f.canRead() &&
                    (filter == null || filter.accept(f))) {
                indexFile(f);
            }
        }
        return writer.numDocs(); // Return number of documents indexed
    }

    private static class TextFilesFilter implements FileFilter {
        public boolean accept(File path) {
            // Index .txt files only, by using Filefilter
            return path.getName().toLowerCase()
                    .endsWith(".txt");
        }
    }
    protected Document getDocument(File f) throws Exception {
        Document doc = new Document();
        // Index file content
        doc.add(new Field("contents", new FileReader(f)));
        // Index filename
        doc.add(new Field("filename", f.getName(),
                Field.Store.YES, Field.Index.NOT_ANALYZED));
        // Index file full path
        doc.add(new Field("fullpath", f.getCanonicalPath(),
                Field.Store.YES, Field.Index.NOT_ANALYZED));
        return doc;
    }

    // Add document to Lucene index
    private void indexFile(File f) throws Exception {
        System.out.println("Indexing " + f.getCanonicalPath());
        Document doc = getDocument(f);
        writer.addDocument(doc);
    }
}
```

Indexer is simple. The static main method parses  the incoming arguments, creates an Indexer instance, locates G \*.txt in the provided data directory, and prints how many documents were indexed and how much time was required. The code involving the Lucene APIs includes creating  and closing  the IndexWriter, creating the document, adding the document to the index, and returning the number of documents indexed.

##### RUNNING INDEXER

The simplest way to run Indexer is to use Apache Ant. You’ll first have to unpack the zip file containing source code with this book, which you can download from Manning’s site at http://www.manning.com/hatcher3, and change to the directory lia2e. If you don’t see the file build.xml in your working directory, you’re not in the right directory. If this is the first time you’ve run any targets, Ant will compile all the example sources, build the test index, and finally run Indexer, first prompting you for the index and document directory, in case you’d like to change the defaults. It’s also fine to run Indexer using Java from the command line; just ensure your classpath includes the JARs under the lib subdirectory as well as the build/classes directory.

By default the index will be placed under the subdirectory indexes/MeetLucene, and the sample documents under the directory src/lia/meetlucene/data will be indexed. This directory contains a sampling of modern open source licenses. Go ahead and type ant Indexer, and you should see output like this:

### 1.4.2 Searching an index

In the previous section, we indexed a directory of text files. The index in this example resides in a directory of its own on the file system. We instructed Indexer to create a Lucene index in the indexes/MeetLucene directory, relative to the directory from which we invoked Indexer. As you saw in listing 1.1, this index contains the indexed contents of each file, along with the absolute path. Now we need to use Lucene to search that index in order to find files that contain a specific piece of text. For instance, we may want to find all files that contain the keyword patent or redistribute, or we may want to find files that include the phrase modified version. Let’s do some searching now.

```java
package com.company;

import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;

import java.io.File;
import java.io.IOException;

public class Searcher {
    public static void main(String[] args) throws IllegalArgumentException,
            IOException, ParseException {
        if (args.length != 2) {
            throw new IllegalArgumentException("Usage: java " +
                    Searcher.class.getName()
                    + " <index dir> <query>");
        }
        // We parse command-line arguments (index directory, query string).
        String indexDir = args[0];
        String q = args[1];
        search(indexDir, q);
    }
    public static void search(String indexDir, String q)
            throws IOException, ParseException {
        // We use Lucene’s Directory and IndexSearcher classes to open our index for searching.
        Directory dir = FSDirectory.open(new File(indexDir));
        IndexSearcher is = new IndexSearcher(dir);
        // We use QueryParser to parse a human-readable search text into Lucene’s Query class.
        QueryParser parser = new QueryParser(Version.LUCENE_30,
                "contents",
                new StandardAnalyzer(
                        Version.LUCENE_30));
        Query query = parser.parse(q);
        long start = System.currentTimeMillis();
        // Searching returns hits in the form of a TopDocs object.
        TopDocs hits = is.search(query, 10);
        long end = System.currentTimeMillis();
        // Print details on the search (how many hits were found and time taken)
        System.err.println("Found " + hits.totalHits +
                " document(s) (in " + (end - start) +
                " milliseconds) that matched query '" +
                q + "':");
        //Note that the TopDocs object contains only references to the underlying documents.
        //In other words, instead of being loaded immediately upon search, matches are loaded
        //from the index in a lazy fashion—only when requested with the Index-
        //Searcher.doc(int) call. That call returns a Document object from which we can then
        //retrieve individual field values.
        for(ScoreDoc scoreDoc : hits.scoreDocs) {
            Document doc = is.doc(scoreDoc.doc);
            System.out.println(doc.get("fullpath"));
        }
        // Close the IndexSearcher when we’re done.
        is.close();
    }
}
```

## 1.5 Understanding the core indexing classes

### 1.5.1 IndexWriter

IndexWriter is the central component of the indexing process. This class creates a new index or opens an existing one, and adds, removes, or updates documents in the index. Think of IndexWriter as an object that gives you write access to the index but doesn't let you read or search it. IndexWriter needs somewhere to store its index, and that's what Directory is for.

### 1.5.2 Directory 

The Directory class represents the location of a Lucene index. It’s an abstract class that allows its subclasses to store the index as they see fit. In our Indexer example, we used FSDirectory.open to get a suitable concrete FSDirectory implementation that stores real files in a directory on the file system, and passed that in turn to Index- Writer’s constructor. 

### 1.5.3 Analyzer

Before text is indexed, it’s passed through an analyzer. The analyzer, specified in the IndexWriter constructor, is in charge of extracting those tokens out of text that should be indexed and eliminating the rest. If the content to be indexed isn’t plain text, you should first extract plain text from it before indexing.

Analyzer is an abstract class, but Lucene comes with several implementations of it. Some of them deal with skipping stop words (frequently used words that don’t help distinguish one document from the other, such as a, an, the, in, and on); some deal with conversion of tokens to lowercase letters, so that searches aren’t case sensitive; and so on. Analyzers are an important part of Lucene and can be used for much more than simple input filtering. For a developer integrating Lucene into an application, the choice of analyzer(s) is a critical element of application design.

### 1.5.4 Document



