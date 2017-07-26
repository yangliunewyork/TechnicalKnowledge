* https://www.quora.com/What-is-Facebooks-architecture-6

From various readings and conversations I had, my understanding of Facebook's current architecture is:

From various readings and conversations I had, my understanding of Facebook's current architecture is:

* Web front-end written in PHP. Facebook's HipHop Compiler [1] then converts it to C++ and compiles it using g++, thus providing a high performance templating and Web logic execution layer.  
* Because of the limitations of relying entirely on static compilation, Facebook's started to work on a HipHop Interpreter [2] as well as a HipHop Virtual Machine which translate PHP code to HipHop ByteCode [3].  
* Business logic is exposed as services using Thrift [4]. Some of these services are implemented in PHP, C++ or Java depending on service requirements (some other languages are probably used...)  
* Services implemented in Java don't use any usual enterprise application server but rather use Facebook's custom application server. At first this can look as wheel reinvented but as these services are exposed and consumed only (or mostly) using Thrift, the overhead of Tomcat, or even Jetty, was probably too high with no significant added value for their need.  
* Persistence is done using MySQL, Memcached [5], Hadoop's HBase [6]. Memcached is used as a cache for MySQL as well as a general purpose cache.  
* Offline processing is done using Hadoop and Hive.  
* Data such as logging, clicks and feeds transit using Scribe [7] and are aggregating and stored in HDFS using Scribe-HDFS [8], thus allowing extended analysis using MapReduce  
* BigPipe [9] is their custom technology to accelerate page rendering using a pipelining logic  
* Varnish Cache [10] is used for HTTP proxying. They've prefered it for its high performance and efficiency [11].  
* The storage of the billions of photos posted by the users is handled by Haystack, an ad-hoc storage solution developed by Facebook which brings low level optimizations and append-only writes [12].  
* Facebook Messages is using its own architecture which is notably based on infrastructure sharding and dynamic cluster management. Business logic and persistence is encapsulated in so-called 'Cell'. Each Cell handles a part of users ; new Cells can be added as popularity grows [13]. Persistence is achieved using HBase [14].  
* Facebook Messages' search engine is built with an inverted index stored in HBase [15]  
* Facebook Search Engine's implementation details are unknown as far as I know  
* The typeahead search uses a custom storage and retrieval logic [16]  
* Chat is based on an Epoll server developed in Erlang and accessed using Thrift [17]
They've built an automated system that responds to monitoring alerts by launching the appropriated repairing workflow, or escalating to humans if the outage couldn't be overcome [18].   

About the resources provisioned for each of these components, some information and numbers are known:    
* Facebook is estimated to own more than 60,000 servers [18]. Their recent datacenter in Prineville, Oregon is based on entirely self-designed hardware [19] that was recently unveiled as Open Compute Project [20].  
* 300 TB of data is stored in Memcached processes [21]  
* Their Hadoop and Hive cluster is made of 3000 servers with 8 cores, 32 GB RAM, 12 TB disks that is a total of 24k cores, 96 TB RAM and 36 PB disks [22]  
* 100 billion hits per day, 50 billion photos, 3 trillion objects cached, 130 TB of logs per day as of july 2010 [22]  


##### Reference

* [1] HipHop for PHP: http://developers.facebook.com/b...
* [2] Making HPHPi Faster: http://www.facebook.com/note.php...
* [3] The HipHop Virtual Machine: http://www.facebook.com/note.php...
* [4] Thrift: http://thrift.apache.org/
* [5] Memcached: http://memcached.org/
* [6] HBase: http://hbase.apache.org/
* [7] Scribe: https://github.com/facebook/scribe
* [8] Scribe-HDFS: http://hadoopblog.blogspot.com/2...
* [9] BigPipe: http://www.facebook.com/notes/fa...
* [10] Varnish Cache: http://www.varnish-cache.org/
* [11] Facebook goes for Varnish: http://www.varnish-software.com/...
* [12] Needle in a haystack: efficient storage of billions of photos: http://www.facebook.com/note.php...
* [13] Scaling the Messages Application Back End: http://www.facebook.com/note.php...
* [14] The Underlying Technology of Messages: https://www.facebook.com/note.ph...
* [15] The Underlying Technology of Messages Tech Talk: http://www.facebook.com/video/vi...
* [16] Facebook's typeahead search architecture: http://www.facebook.com/video/vi...
* [17] Facebook Chat: http://www.facebook.com/note.php...
* [18] Who has the most Web Servers?: http://www.datacenterknowledge.c...
* [19] Building Efficient Data Centers with the Open Compute Project: http://www.facebook.com/note.php...
* [20] Open Compute Project: http://opencompute.org/
* [21] Facebook's architecture presentation at Devoxx 2010: http://www.devoxx.com
* [22] Scaling Facebook to 500 millions users and beyond: http://www.facebook.com/note.php...
