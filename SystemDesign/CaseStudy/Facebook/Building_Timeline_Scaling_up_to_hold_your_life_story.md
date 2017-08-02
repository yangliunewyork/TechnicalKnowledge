* https://www.facebook.com/note.php?note_id=10150468255628920
* http://highscalability.com/blog/2012/1/23/facebook-timeline-brought-to-you-by-the-power-of-denormaliza.html

Timeline isn’t just a bold new look for Facebook­—it’s also the product of a remarkably ambitious engineering effort. While our earlier profile pages surfaced a few days or weeks of activity, from the onset we knew that with Timeline we had to think in terms of years and even decades. At a high level we needed to scan, aggregate, and rank posts, shares, photos and check-ins to surface the most significant events over years of Facebook activity.
 
The schedule for Timeline was very aggressive. When we sat down to build the system, one of our key priorities was eliminating technical risk by keeping the system as simple as possible and relying on internally-proven technologies. After a few discussions we decided to build on four of our core technologies: MySQL/InnoDB  for storage and replication, Multifeed (the technology that powers News Feed) for ranking, Thrift for communications, and memcached for caching. We chose well-understood technologies so we could better predict capacity needs and rely on our existing monitoring and operational tool kits.

# Denormalizing the data

Before we began Timeline, our existing data was highly normalized, which required many round trips to the databases. Because of this, we relied on caching to keep everything fast. When data wasn’t found in cache, it was unlikely to be clustered together on disk, which led to lots of potentially slow, random disk IO. To support our ranking model for Timeline, we would have had to keep the entire data set in cache, including low-value data that wasn’t displayed.
 
A massive denormalization process was required to ensure all the data necessary for ranking was available in a small number of IO-efficient database requests
 
Once denormalized, each row in the database contained both information about the action and enough ranking metadata so it could be selected or discarded without additional data fetches. Data is now sorted by (user, time) on disk and InnoDB does a great job of streaming data from disk with a primary key range query.
 
Some of our specific challenges of the denormalization process were:

1. Dozens of legacy data formats that evolved over years. Peter Ondruška, a Facebook summer intern, defined a custom language to concisely express our data format conversion rules and wrote a compiler to turn this into runnable PHP. Three “data archeologists” wrote the conversion rules.
2. Non-recent activity data had been moved to slow network storage. We hacked a read-only build of MySQL and deployed hundreds of servers to exert maximum IO pressure and copy this data out in weeks instead of months.
3. Massive join queries that did tons of random IO. We consolidated join tables into a tier of flash-only databases. Traditionally PHP can perform database queries on only one server at a time, so we wrote a parallelizing query proxy that allowed us to query the entire join tier in parallel.
4. Future-proofing the data schema. We adopted a data model that’s compatible with Multifeed. It’s more flexible and provides more semantic context around data with the added benefit of allowing more code reuse.

# Timeline aggregator 

We built the Timeline aggregator on top of the database. It started its life as a modified version of the Multifeed Aggregator that powers News Feed, but now it runs locally on each database box, allowing us to max out the disks without sending any data over the network that won’t be displayed on the page.
 
The aggregator provides a set of story generators that handle everything from geographically clustering nearby check-ins to ranking status updates. These generators are implemented in C++ and can run all these analyses in a few milliseconds, much faster than PHP could. Much of the generator logic is decomposed into a sequence of simple operations that can be reused to write new generators with minimal effort.
 
Caching is an important part of any Facebook project. One of the nice properties of Timeline is that the results of big queries, such as ranking all your activity in 2010, are small and can be cached for a long period without cache invalidations. A query result cache is of huge benefit and memcached is an excellent solution.
 
Recent Activity changes frequently so a query cache is frequently invalidated, but regenerating the summary of Recent Activity is quite fast. Here a row cache helps further boost query performance. We rely on the InnoDB buffer pool in RAM and our own Flashcache kernel driver to expand the OS cache onto a flash device.

![alt](https://tctechcrunch2011.files.wordpress.com/2012/01/timeline-architecture-diagram.jpg)

# Developing in parallel

Timeline started as a Hackathon project in late 2010 with two full-time engineers, an engineering intern, and a designer building a working demo in a single night. The full team ramped up in early 2011, and the development team was split into design, front-end engineering, infrastructure engineering, and data migrations. By doing staged and layered prototyping, we achieved an amazing amount of development parallelism and rarely was any part of the team blocked by another. Early on in the project we were simultaneously:
 
1. Designing UI prototypes with our pre-existing but non-scalable backend,
2. Building production frontend code on a simulation of the scalable backend,
3. Building the scalable backend using samples of de-normalized data from a prototype of denormalization migration,
4. Building the framework to run the full-scale denormalization process,
5. Collecting and copying the data necessary for the denormalization,
6. Performing simulated load testing to validate our capacity planning estimates.

# Five big takeaways from the article 

##### Leverage infrastructure rather than build something new. 

You might expect that they would pioneer a new infrastructure for Timeline, but given the short schedule, they decided to go with proven technologies inside Facebook: MySQL, Multifeed (a custom distributed system which takes the tens of thousands of updates from friends and picks the most relevant), Thrift, Memcached, Operations. The last point about the operations infrastructure is a huge win for any team. All that just works. They can concentrate on solving the problem and skip the whole tooling dance, which is why new products can be generated amazingly fast inside a "big company", if the infrastructure is done right.

##### Denormalize. Format data in the way you need to use it. 

Denormalzation, creating special purpose objects instead of distributed rows that must be joined, minimizes random IO by reducing the number of trips to the database. Caching can often get around the need for denormalization, but given the amount of timeline data and how much of it is cold, that is it will rarely be viewed, caching everything isn't a good design.

Timeline decides the order to display data by calculating a rank based on metadata. The denormalization process brought all that metadata together in a format that meant ranking could be done in a few IOs and streamed efficiently from the database using a primary key range query.

Timeline is like a datamart in a data warehouse. Data must be slurped up from dozens of different systems, cleaned, merged, and reformatted into a new canonical format. Facebook of course did this in a Facebook-like way. They created a custom data conversion language, they deployed hundreds of MySQL servers to extract the data out of "legacy" systems as fast as possible, they deployed flash storage to speed up joins, they created a parallelizing query proxy, and they standardized on the Multifeed data format for future flexibility.


##### Keep different types of caches. 

Short term cache.  A timeline of recent activity is frequently invalidated because it is changing all the time as you perform actions through your life. This cache is an in RAM row cache inside InnoDB that uses the Flashcache kernel driver to expand the OS cache onto a flash device.

Long term cache. A query cache is kept in memcached. The results of large queries, like the ranking of all your activities in 2010, can be efficiently cached since they will rarely be invalidated.

##### Run operations locally. 
The Timeline Aggregator (geographically clustering nearby check-ins, ranking status updates, etc) runs on each database so it can max out the disks. Only data that needs to be displayed is sent over the network.

##### Parallelize development. 
The short 6 month development time was partly a product of the quality infrastructure, but of also running significant development activities in parallel. The development team was split into design, front-end engineering, infrastructure engineering, and data migrations. In parallel they built: UI prototypes on a test backend, production UI on a simulated backend, the scalable backend, the denormalization framework, the data warehouse, and simulated load testing. 
