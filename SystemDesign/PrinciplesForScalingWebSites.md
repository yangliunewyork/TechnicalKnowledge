## Rule 1 - Don’t Overengineer the Solution
Overengineering (or over-engineering) is the designing of a product to be more robust or complicated than is necessary for its application, either (charitably) to ensure sufficient factor of safety, sufficient functionality, or because of design errors. Overengineering can be desirable when safety or performance on a particular criterion is critical, or when extremely broad functionality is required, but it is generally criticized from the point of view of value engineering as wasteful. As a design philosophy, such overcomplexity is the opposite of the less is more school of thought.

AsWikipedia explains, overengineering falls into two broad categories.1 The first category covers products designed and implemented to exceed the useful requirements of the product.The second category of overengineering covers products that are made to be overly complex.

## Rule 2—Design Scale into theSolution (D-I-D Process)


## Rule 3—Simplify the Solution 3 Times Over

## Rule 4—Reduce DNS Lookups
The Domain Name System (DNS) is one of the most important parts of the infrastructure of the Internet or any other network that utilizes the Internet Protocol Suite (TCP/IP). It allows the translation from domain name (www.akfpartners.com) to an IP address (184.72.236.173) and is often analogized to a phone book. DNS is maintained by a distributed database system, the nodes of which are the name servers.The top of the hierarchy consists of the root name servers. Each domain has at least one authoritative DNS server that publishes information about that domain.

This process of translating domains into IP addresses is made quicker by caching on many levels, including the browser, computer operating system, Internet service provider, and so on. However, in our world where pages can have hundreds or thousands of objects, many from different domains, small milliseconds of time can add up to something noticeable to the customer.

Browsers take advantage of the fact that almost all Web pages are comprised of many different objects (images, JavaScript files, css files, and so on) by having the ability to download multiple objects through simultaneous connections. Browsers limit the maximum number of simultaneous persistent connections per server or proxy.

Every distinct domain that serves one or more objects for a Web page requires a DNS lookup either from cache or out to a DNS name server. For example, let’s assume we have a simple Web page that has four objects: 1) the HTML page itself that contains text and directives for other objects, 2) a CSS file for the layout, 3) a JavaScript file for a menu item, and 4) a JPG image.The HTML comes from our domain (akfpartners.com), but the CSS and JPG are served from a subdomain (static.akfpartners. com), and the JavaScript we’ve linked to from Google (ajax.googleapis.com). In this scenario our browser first receives the request to go to page www.akfpartners.com, which requires a DNS lookup of the akfpartners.com domain. Once the HTML is downloaded the browser parses it and finds that it needs to download the CSS and JPG both from static.akfpartners. com, which requires another DNS lookup. Finally, the parsing reveals the need for an external JavaScript file from yet another domain. Depending on the freshness of DNS cache in our browser, operating system, and so on, this lookup can take essentially no time up to hundreds of milliseconds.As a general rule, the fewer DNS lookups on your pages the better your page download performance will be.

## Rule 5—Reduce Objects Where Possible
Web pages consist of many different objects (HTML, CSS, images, JavaScript, and so on), which allows our browsers to download them somewhat independently and often in parallel. One of the easiest ways to improve Web page performance and thus increase your scalability (fewer objects to serve per page means your servers can serve more pages) is to reduce the number of objects on a page.The biggest offenders on most pages are graphical objects such as pictures and images.

Reducing the number of objects on the page is a great way to improve performance and scalability, but before you rush off to remove all your images there are a few other things to consider.

In summary, the fewer the number of objects on a page the better for performance, but this must be balanced with many other factors. Included in these factors are the amount of content that must be displayed, how many objects can be combined, how to maximize the use of simultaneous connections by adding domains, the total page weight and whether penalization can help, and so on.While this rule touches on many Web site performance improvement techniques the real focus is how to improve performance and thus increase the scalability of your site through the reduction of objects on the page. Many other techniques for optimizing performance should be considered, including loading CSS at the top of the page and JavaScript files at the bottom, minifying files, and making use of caches, lazy loading, and so on.

## Rule 6—Use Homogenous Networks



![alt] (http://ptgmedia.pearsoncmg.com/images/chap2_9780134431604/elementLinks/02fig01_alt.jpg)


## Rule 7—Design to Clone Things (X Axis)
One technique for scaling databases is to take advantage of the fact that most applications and databases perform significantly more reads than writes. A client of ours that handles booking reservations for customers has on average 400 searches for a single booking. Each booking is a write and each search a read,resulting in a 400:1 read to write ratio.This type of system can be easily scaled by creating read-only copies (or replicas) of the data.

There are a couple ways that you can distribute the readcopy of your data depending on the time sensitivity of the data. Time sensitivity is how fresh or completely correct the readcopy has to be relative to the write copy. Before you scream out that the data has to be instantly, real time, in sync, and completely correct across the entire system, take a breath and appreciate the costs of such a system.While perfectly in sync data is ideal, it costs…a lot. Furthermore, it doesn’t always give you the return that you might expect or desire for that cost.

To distribute the data,one way is to use a caching tier in front of the database. An object cache can be used to read from instead of going back to the application for each query. Only when the data has been marked expired would the application have to query the primary transactional database to retrieve the data and refresh the cache. Given the availability of numerous excellent, open source key-value stores that can be used as object caches, this is a highly recommended first step.

The next step beyond an object cache between the application tier and the database tier, is replicating the database. Most major relational database systems allow for some type of replication “out of the box.” MySQL implements replication through the master-slave concept—the master database being the primary transactional database that gets written to and the slave databases are read-only copies of the master databases.The master database keeps track of updates, inserts, deletes, and so on in a binary log. Each slave requests the binary log from the master and replays these commands on its database.While this is asynchronous, the latency between data being updated in the master and then in the slave can be very low. Often this implementation consists of several slave databases or read replicas that are configured behind a load balancer.The application makes a read request to the load balancer, which passes the request in either a round robin or least connections manner to a read replica.

We call this type of split an X axis split, and it is represented on the AKF Scale Cube in Figure 2.1 as the X axis – Horizontal Duplication. An example that many developers familiar with hosting Web applications will recognize is on the Web or application tier of a system, running multiple servers behind a load balancer all with the same code.A request comes in to the load balancer that distributes it to any one of the many Web or application servers to fulfill.The great thing about this distributed model on the application tier is that you can put dozens, hundreds, or even thousands of servers behind load balancers all running the same code and handling similar requests.

The X axis can be applied to more than just the database. Web servers and application servers typically can be easily cloned.This cloning allows the distribution of transactions across systems evenly for horizontal scale.This cloning of application or Web services tends to be relatively easy to perform, and allows us to scale the number of transactions processed. Unfortunately, it doesn’t really help us when trying to scale the data we must manipulate to perform these transactions. In memory, caching of data unique to several customers or unique to disparate functions might create a bottleneck that keeps us from scaling these services without significant impact to customer response time.

## Rule 8—Design to Split Different Things (Y Axis)
When you put aside the religious debate around the concepts of services (SOA) and resources (ROA) oriented architectures and look deep into their underlying premises, they have at least one thing in common. Both concepts force architects and engineers to think in terms of separation of responsibilities within their architectures. At a high and simple level, they do this through the concepts of verbs (services) and nouns (resources). Rule 8, and our second axis of scale, takes the same approach. Put simply,Rule 8 is about scaling through the separation of distinct and different functions and data within your site.The simple approach to Rule 8 tells us to split up our product by either nouns or verbs or a combination of both nouns and verbs.

While Y axis splits are most useful in scaling data sets, they are also useful in scaling code bases. Because services or resources are now split, the actions we perform and the code necessary to perform them are split up as well.This means that very large engineering teams developing complex systems can become experts in subsets of those systems and don’t need to worry about or become experts on every other part of the system.And of course because we have split up our services, we can also scale transactions fairly easily.

## Rule 9—Design to Split Similar Things (Z Axis)

Often referred to as sharding and podding, Rule 9 is about taking one data set or service and partitioning it into several pieces. These pieces are often equal sized but may be of different sizes if there is value in having several unequal sized chunks or shards. One reason to have unequal sized shards is to enable application rollouts that limit your risk by affecting first a small customer segment, and then increasingly large segments of customers as you feel you have identified and resolved major problems.

Why would we ever decide to partition similar things? For hyper growth companies, the answer is easy.The speed with which we can answer any request is at least partially determined by the cache hit ratio of near and distant caches.This speed in turn indicates how many transactions we can process on any given system, which in turn determines how many systems we need to process a number of requests. In the extreme case, without partitioning of data, our transactions might become agonizingly slow as we attempt to traverse huge amounts of monolithic data to come to a single answer for a single user.Where speed is paramount and the data to answer any request is large, designing to split different things (Rule 8) and similar things (Rule 9) become necessities.

## Summary 
We maintain that three simple rules can help you scale nearly everything.There are undoubtedly more ways to scale systems and platforms, but armed with these three rules, few if any scale related problems will stand in your way: 
* __Scale by cloning__ —Cloning or duplicating data and services allows you to scale transactions easily. 
* __Scale by splitting different things__ —Use nouns or verbs to identify data and services to separate. If done properly, both transactions and data sets can be scaled efficiently. 
* __Scale by splitting similar things__ —Typically these are customer data sets. Set customers up into unique and separated shards or swimlanes to enable transaction and data scaling.

## Rule 10: Design Your Solution to Scale Out—Not Just Up
Scaling out is the duplication of services or databases to spread transaction load and is the alternative to buying larger hardware, known as scaling up. Any system, service, or database expected to grow rapidly. Plan for success and design your systems to scale out. Don’t get caught in the trap of expecting to scale up only to find out that you’ve run out of faster and larger systems to purchase.

## Rule 11—Use Commodity Systems (Goldfish Not Thoroughbreds)
Use small, inexpensive systems where possible. Use this approach in your production environment when going through hyper growth. Stay away from very large systems in your production environment. Build your systems to be capable of relying on commodity hardware and don’t get caught in the trap of using high-margin, high-end servers.

## Rule 12—Scale Out Your Data Centers
Design your systems to have three or more live data centers to reduce overall cost, increase availability, and implement disaster recovery. Any rapidly growing business that is considering adding a disaster recovery (cold site) data center.Split up your data to spread across data centers and spread transaction load across those data centers in a “multiple live” configuration. Use spare capacity for peak periods of the year. The cost of data center failure can be disastrous to your business. Design to have three or more as the cost is often less than having two data centers. Make use of idle capacity for peak periods rather than slowing down your transactions. When implementing disaster recovery, lower your cost of disaster recovery by designing your systems to leverage three or more live data centers. Use the spare capacity for spiky demand when necessary.











