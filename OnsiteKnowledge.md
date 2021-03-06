## CDN
A content delivery network or content distribution network (CDN) is a globally distributed network of proxy servers deployed in multiple data centers. The goal of a CDN is to serve content to end-users with high availability and high performance.
Benefits include reducing bandwidth costs, improving page load times, or increasing global availability of content. The number of nodes and servers making up a CDN varies, depending on the architecture, some reaching thousands of nodes with tens of thousands of servers on many remote points of presence (PoPs). Others build a global network and have a small number of geographical PoPs.

Performance, reliability and bandwidth are major factors for online service providers that directly impact profitability and customer satisfaction. A CDN is a distributed group of servers that can withstand high amounts of traffic, provide inexpensive data transfer costs, and provide reliability. Many websites and online services rely on CDNs as a cost-effective way to improve uptime and performance.

Typically, when a user visits a website, their browser downloads every referenced asset (images, videos, CSS/Javascript) from a single origin server. If the origin is in New York and the user is in Japan, each asset must be downloaded from across the world. In a case like this, users experience longer page load times due to higher latency. A CDN distributes files to servers around the globe, reducing the time needed to access a file. For example, users in Japan could download files from a nearby server in Asia instead of one in North America.

Here’s a step-by-step description of how a CDN works: 1. The website administrator for example.com (the origin server) signs up with a CDN provider. The CDN provider gives the administrator a url for the CDN such as example.some-cdn.com. 2. The website administrator configures the site to load assets (images, videos, CSS/Javascript files) from the CDN url instead of the origin server. With software like WordPress, this change can be made using a plugin. 3. A user opens example.com in their browser. The browser requests assets that are referenced inside the page using a CDN url such as http://example.some-cdn.com/image.png. 4. The CDN automatically distributes incoming requests to the nearest CDN server, using technologies like DNS load balancing and Anycast routing. Files not already on the CDN are downloaded from the origin server and stored. 5 .The browser downloads assets from a nearby CDN server, thereby improving performance and reducing traffic for the origin server.

### BENEFITS OF A CDN

A CDN offers numerous benefits for a website or online service:

* Users experience faster load times because assets are downloaded from local servers instead of faraway ones.
* Enterprises save on bandwidth costs since CDNs can purchase bandwidth in bulk and pass this discounted rate to their customers.
* Enterprises reduce server load because asset requests are routed away from the origin server.
* Enterprises improve server reliability as CDNs are part of failover plans to route traffic to new locations should a server be taken offline.

