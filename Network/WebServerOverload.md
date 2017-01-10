A web server (program) has defined load limits, because it can handle only a limited number of concurrent client connections (usually between 2 and 80,000, by default between 500 and 1,000) per IP address (and TCP port) and it can serve only a certain maximum number of requests per second (RPS, also known as queries per second or QPS) depending on:

* its own settings,
* the HTTP request type,
* whether the content is static or dynamic,
* whether the content is cached, and
* the hardware and software limitations of the OS of the computer on which the web server runs.

### Causes of overload
At any time web servers can be overloaded due to:
* Excess legitimate web traffic. Thousands or even millions of clients connecting to the web site in a short interval, e.g., Slashdot effect;
* __Distributed Denial of Service__ attacks. A denial-of-service attack (DoS attack) or distributed denial-of-service attack (DDoS attack) is an attempt to make a computer or network resource unavailable to its intended users;
* Computer worms that sometimes cause abnormal traffic because of millions of infected computers (not coordinated among them)
* __XSS viruses__ can cause high traffic because of millions of infected browsers and/or web servers;
* __Internet bots__ Traffic not filtered/limited on large web sites with very few resources (bandwidth, etc.);
Internet (network) slowdowns, so that client requests are served more slowly and the number of connections increases so much that server limits are reached;
* Web servers (computers) partial unavailability. This can happen because of required or urgent maintenance or upgrade, hardware or software failures, back-end (e.g., database) failures, etc.; in these cases the remaining web servers get too much traffic and become overloaded.

### Symptoms of overload
The symptoms of an overloaded web server are:

* Requests are served with (possibly long) delays (from 1 second to a few hundred seconds).
* The web server returns an HTTP error code, such as 500, 502, 503, 504, 408, or even 404, which is inappropriate for an overload condition.
* The web server refuses or resets (interrupts) TCP connections before it returns any content.
* In very rare cases, the web server returns only a part of the requested content. This behavior can be considered a bug, even if it usually arises as a symptom of overload.

### Anti-overload techniques

To partially overcome above average load limits and to prevent overload, most popular web sites use common techniques like:

* Managing network traffic, by using:
  * Firewalls to block unwanted traffic coming from bad IP sources or having bad patterns
  * HTTP traffic managers to drop, redirect or rewrite requests having bad HTTP patterns
  * Bandwidth management and traffic shaping, in order to smooth down peaks in network usage
* Deploying web cache techniques
* Using different domain names to serve different (static and dynamic) content by separate web servers, i.e.:
  * http://images.example.com
  * http://www.example.com
* Using different domain names and/or computers to separate big files from small and medium-sized files; the idea is to be able to fully cache small and medium-sized files and to efficiently serve big or huge (over 10 - 1000 MB) files by using different settings
* Using many internet servers (programs) per computer, each one bound to its own network card and IP address
* Using many internet servers (computers) that are grouped together behind a load balancer so that they act or are seen as one big web server
* Adding more hardware resources (i.e. RAM, disks) to each computer
* Tuning OS parameters for hardware capabilities and usage
* Using more efficient computer programs for web servers, etc.
* Using other workarounds, especially if dynamic content is involved
