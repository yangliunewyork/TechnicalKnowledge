* http://www.ijcaonline.org/volume15/number7/pxc3872629.pdf

# ABSTRACT

The Web is a context in which traditional Information Retrieval methods are challenged. Given the volume of the Web and its speed of change, the coverage of modern web search engines is relatively small. Search engines attempt to crawl the web exhaustively with crawler for new pages, and to keep track of changes made to pages visited earlier. The centralized design of crawlers introduces limitations in the design of search engines. It has been recognized that as the size of the web grows, it is imperative to parallelize the crawling process. Contents other then standard documents (Multimedia content and Databases etc) also makes searching harder since these contents are not visible to the traditional crawlers. Most of the sites stores and retrieves data from backend databases which are not accessible to the crawlers. This results in the problem of hidden web. This paper proposes and implements DCrawler, a scalable, fully distributed web crawler. The main features of this crawler are platform independence, decentralization of tasks, a very effective assignment function for partitioning the domain to crawl, and the ability to cooperate with web servers. By improving the cooperation between web server and crawler, the most recent and updates results can be obtained from the search engine. A new model and architecture for a Web crawler that tightly integrates the crawler with the rest of the search engine is designed first. The development and implementation are discussed in detail. Simple tests with distributed web crawlers successfully show that the Dcrawler performs better then traditional centralized crawlers. The mutual performance gain increases as more crawlers are added.

# INTRODUCTION

### Web search engines and crawlers

##### Information Retrieval (IR) 

Information Retrieval is the area of computer science concerned with retrieving information about a subject from a collection of data objects. This is not the same as Data Retrieval, which in the context of documents consists mainly in determining which documents of a collection contain the keywords of a user query. Information Retrieval deals with satisfying a user need. Although there was an important body of Information Retrieval techniques published before the invention of the World Wide Web, here are unique characteristics of the Web that made them unsuitable or insufficient. 

The low cost of publishing in the "open Web" is a key part of its success, but implies that searching information on the Web will always be inherently more difficult then searching information in traditional, closed repositories.

##### Web search and Web crawling

The typical design of search engines is a "cascade", in which a Web crawler creates a collection which is indexed and searched. Most of the designs of search engines consider the Web crawler as just a first stage in Web search, with little feedback from the ranking algorithms to the crawling process. This is a cascade model, in which operations are executed in strict order: first crawling, then indexing, and then searching.

![alt](http://images.slideplayer.com/18/6104280/slides/slide_1.jpg)

An aim of this approach is to provide the crawler with access to all the information about the collection to guide the crawling process effectively. This can be taken one step further, as there are tools available for dealing with all the possible interactions between the modules of a search engine. 

##### 1.2 Working of a crawler

A web crawler is an automatic web object retrieval system that exploits the web's dense link structure. It has two primary goals, to seek out new web objects, and to observe changes in previously-discovered web objects (web- event detection).The basic web crawler algorithm has not changed since the World Wide Web Wanderer (the first reported web crawler) was designed in 1993. Almost all crawlers follow some variant of the basic web-traversal algorithm. Crawlers must continue to deal with issues of scalability as the World-Wide Web expands. How does one efficiently and effectively crawl the current set of almost 2.5 billion publicly index-able web pages if crawlers are limited by crawling speed and difficulty in predicting web-events? The speed at which a crawler can traverse the web is limited by a number of factors, including the bandwidth of the crawler and the latency of the network.

Predicting when a web object is going to change, helps to limit the amount of useless polling done by a crawler to determine if it has been updated since the last visit. The fewer resources wasted by a crawler doing useless polls, the more that can be delegated to the task of locating new information. In the end, crawlers are going to be relying upon communicating with others and being instances of themselves (in the parallel sense), This arises the need for autonomously cooperative sharing web crawlers - crawlers that can make decisions on their own, and communicate with others when the need arises. 

### 2.REQUIRMENTS AND ASSUMPTIONS

It has been recognized that as the size of the web grows, it becomes imperative to parallelize the crawling process, in order to finish downloading pages in a reasonable amount of time (Junghoo 2002). Nonetheless, little published work actually investigates the fundamental issues underlying the parallelization of the different tasks involved with the crawling process (Sergey 1998, Alan 2001). For example, some features of Google have been presented in (Sergey 1998), where the crawling mechanism is described as a two stage process: a URL server distributes individual URLs to multiple crawlers, which download web pages in parallel; the crawlers then send the downloaded pages to a central indexer, on which links are extracted and sent via the URL server to the crawlers. 

In contrast, when designing DCrawler, all the tasks of web crawlers were decentralized, with obvious advantages in terms of scalability and fault tolerance. Essential features of DCrawler are

* Platform independence;
* Full distribution of every task
* Tolerance to failures:
* Scalability. 

Following sections describes the design goals and assumptions which have guided the architectural choices of DCrawler. These features are the offspring of a well defined design goal: fault tolerance and full distribution (lack of any centralized control). For instance, while there are several reasonable ways to partition the domain to be crawled if one assume the presence of a central server, it becomes harder to find an assignment of URLs to different agents which is fully distributed, does not require too much coordination, and allow to cope with failures. 

#### 2.1 Design Goals

##### 2.1.1 Full Distribution

In order to achieve significant advantages in terms of programming, deployment, and debugging, a parallel and distributed crawler should be composed by identically programmed agents, distinguished by a unique identifier only. This has a fundamental consequence: each task must be performed in a fully distributed fashion, that is, no central coordinator can exist. Also no assumption concerning the location of the agents is made, and this implies that latency can become and issue, so that communication should be minimized to reduce it. 

##### 2.1.2 Balanced locally computable assignment.

The distribution of URLs to agents is an important issue, crucially related to the efficiency of the distributed crawling process. Following goals three goals are identified as important: 

* At any time, each URL should be assigned to a specific agent, which is solely responsible for it. 
* For any given URL, the knowledge of its responsible agent should be locally available. In other words, every agent should have the capability to compute the identifier of the agent responsible for a URL, without communicating. 
* The distribution of URLs should be balanced, that is, each agent should be responsible for approximately the same number of URLs. 

##### 2.1.3 Scalability

The number of pages crawled per second per agent should be (almost) independent of the number of agents. In other words, the throughput should grow linearly with the number of agents. 

##### 2.1.4 Platform independence

The crawler should be able to work among different platforms and in heterogeneous networks with different architecture. This is the reason for choosing java for implementation of Drawler.

##### 2.1.5 Cooperation with web server

The crawler should have the ability to cooperate with the web server during the crawling process. The network traffic generated by the crawlers can be considerably reduced using this mechanism.

##### 2.1.6 Politeness

A parallel crawler should never try to fetch more than one page at a time from a given host. Congestion that could arise because of multiple threads crawling single host could be avoided with this technique.

##### 2.1.7 Fault tolerance

A distributed crawler should continue to work under crash faults, that is, when some agents abruptly die. No behavior can be assumed in the presence of this kind of crash, except that the faulty agent stops communicating; in particular, one cannot prescribe any action to a crashing agent, or recover its state afterwards (note that this is different from milder assumptions, as for instance saying that the state of a faulty agent can be recovered. In the latter case, one can try to "mend" the crawler's global state by analyzing the state of the crashed agent). When an agent crashes, the remaining agents should continue to satisfy the "Balanced locally computable assignment" requirement: this means, in particular, that URLs will have to be redistributed. 

This has two important consequences: 
* It is not possible to assume that URLs are statically distributed. 
* ince the "Balanced locally computable assignment" requirement must be satisfied at any time, it is not reasonable to rely on a distributed reassignment protocol after a crash. Indeed, during the protocol the requirement would be violated

# 3. THE BASIC DESIGN

### 3.1.1 Multithread architecture

DCrawler is composed of several agents that autonomously coordinate their behavior in such a way that each of them scans its share of the web. An agent performs its task by running several threads, each dedicated to the visit of a single host. More precisely, each thread scans a single host using a breadth-first visit. 

Several mechanisms are used to make sure that different threads visit different hosts at the same time, so that each host is not overloaded by too many requests. The out links that are not local to the given host are dispatched to the right agent, which puts them in the queue of pages to be visited. Thus, the overall visit of the web is breadth first, but as soon as a new host is met, it is entirely visited (possibly with bounds on the depth reached or on the overall number of pages), again in a breadth-first fashion.

### 3.1.2 Quality of Pages

More sophisticated approaches (which can take into account suitable priorities related to URLs, such as, for instance, their rank) can be easily implemented. However it is worth noting that several authors have argued that breadth-first visits tend to find high quality pages early on in the crawl. 

An important advantage of per-host breadthfirst visits is that DNS requests are infrequent. Web crawlers that use a global breadth-first strategy must work around the high latency of DNS servers: this is usually obtained by buffering requests through a multithreaded cache. Similarly, no caching is needed for the robots . txt file required by the "Robot Exclusion Standard" indeed such file can be downloaded any time an host breadth-first visit begins.

### 3.1.3 Assignment of URLs




