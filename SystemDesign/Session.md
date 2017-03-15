

## Sticky Session
A method used with Application Load Balancing, to achieve server-affinity.

A router or load balancer with sticky-session support can assign a single server to a particular user, based on their HTTP session or IP address. The assigned server is remembered by the router for a certain amount of time, ensuring that all future requests for the same session are sent to the same server.

To be effective, the router must remember the server selection for a time that is longer than the session timeout.

#### Advantages
* Reasonably simple to implement for experienced network administrators.
* Reduces the need to implement session-failover, as users are only sent to other servers if one goes offline.
* Load balancer/router is often responsible for detecting offline servers, providing faster request-failover than round robin DNS-based load balancing.

#### Disadvantages
* Difficult to set up for network administrators who are new to sticky sessions.
* Problems can be difficult to diagnose. See the sections below for the main issues.
* The load-balancer/router must be load-balanced itself, or it becomes a point of failure that will take down an entire cluster.
* Cannot provide global load-balancing (whereas round-robin DNS can).
* Session-failover is often not implemented, as there is reduced need. If a server goes offline, all users lose their session.

#### Sticky Sessions and HTTPS
Sticky sessions will not work with HTTPS (SSL) if the server ID is based on the HTTP session. This is because the contents of the requests cannot be investigated due to the encryption. In this case, there are 3 options:
* Web server proxies. An initial web server decodes the SSL requests, and forwards the request onto one of the servers in the cluster. Fairly simple to set up, but causes increased load on the proxy. Also the proxy is a single point of failure, which is more likely to fail considering the amount of work it has to perform.
* Hardware SSL decoders. Hardware in the router or load balancer that is capable of decoding the HTTPS requests, and determining the session information stored in them. These are fast and less likely to fail than a web server proxy, but often more difficult to set up and with pricing based on their power.
* IP address-based server allocation. All requests from a given IP address or range are sent to the same server. This is by far the easiest and cheapest method, and allows the router or load-balancer to do all the work. However, their may be more chance of an unevenly distributed load with this method if most of the load comes from a single IP/range. For example, all requests are coming from the same university, will all be sent to the same server.


## What are the most efficient ways to handle user sessions in a scalable environment?

The first is: how do you make sure that all requests issued by a particular user are served by the same web server -- typically this is called __user stickiness, session affinity, session stickiness, or IP stickiness__. You may want to enable this if a given web server machine caches user-specific state that you want to avoid duplicating across machines. For example, if each web server maintains a set of incoming requests for 30 seconds, then flushes the set to a backend data store, you may want to direct all of a user's requests to a single machine to avoid clobbering updates.

The Amazon ELB (Elastic Load Balacing) service supports session stickiness -- you can configure your ELB to attach a special cookie value to HTTP responses that will direct the same user's future requests back to the same EC2 machine.

Session stickiness can be tricky to get right. For example, if your web servers are running on multi-core machines, and you have several processes handling web traffic, you'll need a way to be sticky to both a specific machine and a single process on that machine. So make sure your system degrades well in cases where stickiness doesn't work correctly.

The second part is: how do you reliably store user state. You have several options here, depending on how much state you want to store and how you want to access it:

* First-party cookies. If there's a fairly small amount of data, you can always store it in a first-party browser cookie under your site's domain. (If the data sensitive, you can encrypt it before storing it in the cookie.) The advantage of this approach is that it's simple, widely supported, and frees you from having to maintain user state in your own server-side store.
* A server-side data store. If you want to store user data persistently, you'll need to write it into a server-side data store (e.g., a relational database, a NoSQL key-value store, etc.). The lookup key will typically be either a cookie ID or a login ID. To speed up lookups, you can put a caching layer in front of it (e.g., Memcache, Redis). The advantage is that you can store an arbitrarily large / complex set of per-user data.
* The web server machines (not recommended). If you have session stickiness enabled, and your session data does not need to be long-lived, you can probably get by with storing it in memory on the web server machines themselves. Of course, session stickiness isn't perfect, so it's not especially common to do this in practice.

If you rely solely on first-party cookies, you don't have to worry about a single point of failure because the user passes the full session data on each request. If you rely on a server-side data store, you'll typically want to use something like replication (e.g., read-only slaves for a relational database).
