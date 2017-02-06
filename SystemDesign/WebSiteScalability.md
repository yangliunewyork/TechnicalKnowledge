## Source

* http://horicky.blogspot.com/2008/03/web-site-scalability.html

## 
A classical large scale web site typically have multiple data centers in geographically distributed locations. Each data center will typically have the following tiers in its architecture
* Web tier : Serving static contents (static pages, photos, videos)
* App tier : Serving dynamic contents and execute the application logic (dynamic pages, order processing, transaction processing)
* Data tier: Storing persistent states (Databases, Filesystems)

![alt](http://2.bp.blogspot.com/_j6mB7TMmJJY/R9F3_4qXpgI/AAAAAAAAAAs/-qYU9ZKhEpo/s1600-h/scalable.png)

## Content Delivery

### Dynamic Content

Most of the content display is dynamic content. Some application logic will be executed at the web server which generate an HTML for the client browser. The efficiency of application logic will have a huge impact on the overall site's scalability. This is our main topic here.
Sometimes it is possible to pre-generate dynamic content and store it as static content. When the real request comes in, instead of re-running the application logic to generate the page, we just need to lookup the pre-generated page, which can be much faster.

### Static Content

Static content are typically the images, videos embedded inside the dynamic pages.

A typical HTML pages typically contains many static contents where the browser will make additional HTTP network round trips to fetch. So fetching static content efficiency also has a big impact to the overall response of dynamic page
Content Delivery Network is an effective solution for delivering static contents. CDN provider will cache the static content in their network and will return the cached copy for subsequent HTTP fetch request. This reduce the overall hits to your web site as well as improving the user's response time (because their cache is in closer proximity to the user).

## Request dispatching and Load balancing

There are 2 layers of dispatching for a Client who is making an HTTP request to reach the application server

### DNS Resolution based on user proximity

* Depends on the location of the client (derived from the IP address), the DNS server can return an ordered list of sites according to the proximity measurement. Therefore client request will be routed to the data center closest to him/her
* After that, the client browser will cache the server IP

### Load balancer

* Load balancer (hardware-based or software-based) will be sitting in front of a pool of homogeneous servers which provide same application services. The load balancer's job is to decide which member of the pool should handle the request
* The decision can be based on various strategy, simple one include round robin or random, more sophisticated one involves tracking the workload of each member (e.g. by measuring their response time) and dispatch request to the least busy one
* Members of the pool can also monitor its own workload and mark itself down (by not responding to the ping request of the load balancer).

## Client communication

This is concerned about designing an effective mechanism to communicate with the client, which is typically the browser making some HTTP call (maybe AJAX as well)

### Designing the granularity of service call
* Reduce the number of round trips by using a coarse grain API model so your client is making one call rather than many small calls
* Don't send back more data than your client need
* Consider using an incremental processing model. Just send back sufficient result for the first page. Use a cursor model to compute more result for subsequent pages in case the client needs it. But it is good to calculate an estimation of the total matched result to return to the client.

### Designing message format
* If you have control on the client side (e.g. I provide the JavaScript library which is making the request), then you can choose a more compact encoding scheme and not worry about compatibility.
* If not, you have to use a standard encoding mechanism such as XML. You also need to publish the XML schema of the message (the contract is the message format)
### Consider data compression
* If the message size is big, then we can apply compression technique (e.g. gzip) to the message before sending it.
* You are trading off CPU for bandwidth savings, better to measure whether this is a gain first
### Asynchronous communication
* AJAX fits very well here. User can proceed to do other things while the server is working on the request
* Consider not sending the result at all. Rather than sending the final order status to the client who is sending an order placement request, consider sending an email acknowledgment.

## Session state handling
Typical web transaction involves multiple steps. Session state need to be maintained across multiple interactions

### Memory-based session state with Load balancer affinity
* One way is to store the state in the App Server's local memory. But we need to make sure subsequent request land on the same App Server instance otherwise it cannot access the previous stored session state
* Load balancer affinity need to be turned on. Typically request with the same cookie will be routed to the same app server
### Memory replication session state across App servers
* Another way to have the App server sharing a global session state by replicating its changes to each other
* Double check the latency of replication so we can make sure there is enough time for the replication to complete before subsequent request is made
### Persist session state to a DB
* Store the session state into a DB which can be accessed by any App Server inside the pool
### On-demand session state migration
* Under this model, the cookie will be used to store the IP address of the last app server who process the client request
* When the next request comes in, the dispatcher is free to forward to any members of the pool. The app server which receive this request will examine the IP address of the last server and pull over the session state from there.
### Embed session state inside cookies
* If the session state is small, you don't need to store at the server side at all. You can just embed all information inside a cookie and send back to the client.
* You need to digitally sign the cookie so that modification cannot happen

## Caching
Remember the previous result can reuse them for future request can drastically reduce the workload of the system. But don't cache request which modifies the backend state
