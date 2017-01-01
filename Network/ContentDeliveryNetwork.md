https://www.incapsula.com/cdn-guide/what-is-cdn-how-it-works.html
## What is a CDN?
A content delivery network or content distribution network (CDN) is a globally distributed network of proxy servers deployed in multiple data centers. The goal of a CDN is to serve content to end-users with high availability and high performance. CDNs serve a large fraction of the Internet content today, including web objects (text, graphics and scripts), downloadable objects (media files, software, documents), applications (e-commerce, portals), live streaming media, on-demand streaming media, and social networks.
CDN nodes are usually deployed in multiple locations, often over multiple backbones. Benefits include reducing bandwidth costs, improving page load times, or increasing global availability of content. The number of nodes and servers making up a CDN varies, depending on the architecture, some reaching thousands of nodes with tens of thousands of servers on many remote points of presence (PoPs). Others build a global network and have a small number of geographical PoPs.

## Overview
Performance, reliability and bandwidth are major factors for online service providers that directly impact profitability and customer satisfaction.
A CDN is a distributed group of servers that can withstand high amounts of traffic, provide inexpensive data transfer costs, and provide reliability. Many websites and online services rely on CDNs as a cost-effective way to improve uptime and performance.

### What performance problem does a CDN solve?

While content delivery networks also solve ancillary problems such as improving global availability and reducing bandwidth, the main problem they address is latency: the amount of time it takes for the host server to receive, process, and deliver on a request for a page resource (images, CSS files, etc.). Latency depends largely on how far away the user is from the server, and it’s compounded by the number of resources a web page contains.

For example, if all your resources are hosted in San Francisco, and a user is visiting your page in London, then each request has to make a long round trip from London to SF and back to London. If your web page contains 100 objects (which is at the low end of normal), then your user’s browser has to make 100 individual requests to your server in order to retrieve those objects.

Typically, latency is in the 75-140ms range, but it can be significantly higher, especially for mobile users accessing a site over a 3G network. This can easily add up to 2 or 3 seconds of load time, which is a big deal when you consider that this is just one factor among many that can slow down your pages.

A CDN caches static resources in distributed servers (AKA edge caches, points of presence, or PoPs) across a region or worldwide, thereby bringing resources closer to users and reducing round trip time.

## How a CDN works?
Typically, when a user visits a website, their browser downloads every referenced asset (images, videos, CSS/Javascript) from a single origin server. If the origin is in New York and the user is in Japan, each asset must be downloaded from across the world. In a case like this, users experience longer page load times due to higher latency.
A CDN distributes files to servers around the globe, reducing the time needed to access a file. For example, users in Japan could download files from a nearby server in Asia instead of one in North America.

## CDN Building Blocks
* __PoPs__ : CDN PoPs (Points of Presence) are strategically located data centers responsible for communicating with users in their geographic vicinity. Their main function is to reduce round trip time by bringing the content closer to the website’s visitor. Each CDN PoP typically contains numerous caching servers.
* __Caching servers__ : Caching servers are responsible for the storage and delivery of cached files. Their main function is to accelerate website load times and reduce bandwidth consumption. Each CDN caching server typically holds multiple storage drives and high amounts of RAM resources. 
* __SSD/HDD + RAM__ : Inside CDN caching servers, cached files are stored on solid-state and hard-disk drives (SSD and HDD) or in random-access memory (RAM), with the more commonly-used files hosted on the more speedy mediums. Being the fastest of the three, RAM is typically used to store the most frequently-accessed items. 

Here’s a step-by-step description of how a CDN works:
1. The website administrator for example.com (the origin server) signs up with a CDN provider. The CDN provider gives the administrator a url for the CDN such as example.some-cdn.com.
2. The website administrator configures the site to load assets (images, videos, CSS/Javascript files) from the CDN url instead of the origin server. With software like WordPress, this change can be made using a plugin.
3. A user opens example.com in their browser. The browser requests assets that are referenced inside the page using a CDN url such as http://example.some-cdn.com/image.png.
4. The CDN automatically distributes incoming requests to the nearest CDN server, using technologies like DNS load balancing and Anycast routing. Files not already on the CDN are downloaded from the origin server and stored.
5 .The browser downloads assets from a nearby CDN server, thereby improving performance and reducing traffic for the origin server.

CDN providers use additional techniques to optimize the delivery of files, such as compression, caching and special HTTP headers.


## BENEFITS OF A CDN
A CDN offers numerous benefits for a website or online service:
* Users experience faster load times because assets are downloaded from local servers instead of faraway ones.
* Enterprises save on bandwidth costs since CDNs can purchase bandwidth in bulk and pass this discounted rate to their customers.
* Enterprises reduce server load because asset requests are routed away from the origin server.
* Enterprises improve server reliability as CDNs are part of failover plans to route traffic to new locations should a server be taken offline.

## Examples of CDN

Many websites use third-party libraries like Twitter Bootstrap to improve their layout or functionality. However, the administrator may not want to host the libraries directly, which costs bandwidth and may involve maintenance and updates.

Services like Bootstrap CDN let users load the CSS and Javascript files for Twitter Bootstrap from a CDN. This reduces server load and speeds up access for users. Additionally, users can avoid re-downloading the files if they’ve already visited a site that uses the same files on Bootstrap CDN.

