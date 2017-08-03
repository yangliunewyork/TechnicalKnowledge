## What is Proxy server ?
In computer networks, a __proxy server__ is a server (a computer system or an application) that acts as an intermediary for requests from clients seeking resources from other servers. A client connects to the proxy server, requesting some service, such as a file, connection, web page, or other resource available from a different server and the proxy server evaluates the request as a way to simplify and control its complexity. Proxies were invented to add structure and encapsulation to distributed systems.[2] Today, most proxies are web proxies, facilitating access to content on the World Wide Web, providing anonymity and may be used to bypass IP address blocking.

## Types
A proxy server may reside on the user's local computer, or at various points between the user's computer and destination servers on the Internet.
* A proxy server that passes requests and responses unmodified is usually called a gateway or sometimes a tunneling proxy.

![alt](http://kaazing.com/doc/legacy/4.0/images/f-html5-multi-client-web.jpg)

* A forward proxy is an Internet-facing proxy used to retrieve from a wide range of sources (in most cases anywhere on the Internet).

![alt](http://www.cisco.com/c/dam/en/us/td/i/300001-400000/340001-350000/348001-349000/348948.tif/_jcr_content/renditions/348948.jpg)

* A reverse proxy is usually an internal-facing proxy used as a front-end to control and protect access to a server on a private network. A reverse proxy commonly also performs tasks such as load-balancing, authentication, decryption or caching.

![alt](https://www.citrix.com/blogs/wp-content/uploads/2010/10/Citrix_ReverseProxy_101003.jpg)

## Reverse proxies
A reverse proxy (or surrogate) is a proxy server that appears to clients to be an ordinary server. Requests are forwarded to one or more proxy servers which handle the request. The response from the proxy server is returned as if it came directly from the original server, leaving the client no knowledge of the origin servers.[4] Reverse proxies are installed in the neighborhood of one or more web servers. All traffic coming from the Internet and with a destination of one of the neighborhood's web servers goes through the proxy server. The use of "reverse" originates in its counterpart "forward proxy" since the reverse proxy sits closer to the web server and serves only a restricted set of websites. There are several reasons for installing reverse proxy servers:

* Encryption / SSL acceleration: when secure web sites are created, the Secure Sockets Layer (SSL) encryption is often not done by the web server itself, but by a reverse proxy that is equipped with SSL acceleration hardware. Furthermore, a host can provide a single "SSL proxy" to provide SSL encryption for an arbitrary number of hosts; removing the need for a separate SSL Server Certificate for each host, with the downside that all hosts behind the SSL proxy have to share a common DNS name or IP address for SSL connections. This problem can partly be overcome by using the SubjectAltName feature of X.509 certificates.
* Load balancing: the reverse proxy can distribute the load to several web servers, each web server serving its own application area. In such a case, the reverse proxy may need to rewrite the URLs in each web page (translation from externally known URLs to the internal locations).
* Serve/cache static content: A reverse proxy can offload the web servers by caching static content like pictures and other static graphical content.
* Compression: the proxy server can optimize and compress the content to speed up the load time.
* Spoon feeding: reduces resource usage caused by slow clients on the web servers by caching the content the web server sent and slowly "spoon feeding" it to the client. This especially benefits dynamically generated pages.
* Security: the proxy server is an additional layer of defence and can protect against some OS and Web Server specific attacks. However, it does not provide any protection from attacks against the web application or service itself, which is generally considered the larger threat.
* Extranet Publishing: a reverse proxy server facing the Internet can be used to communicate to a firewall server internal to an organization, providing extranet access to some functions while keeping the servers behind the firewalls. If used in this way, security measures should be considered to protect the rest of your infrastructure in case this server is compromised, as its web application is exposed to attack from the Internet.


# Reverse proxy servers and load balancers

Reverse proxy servers and load balancers are components in a client-server computing architecture. Both act as intermediaries in the communication between the clients and servers, performing functions that improve efficiency. They can be implemented as dedicated, purpose-built devices, but increasingly in modern web architectures they are software applications that run on commodity hardware.

The basic definitions are simple:

* A reverse proxy accepts a request from a client, forwards it to a server that can fulfill it, and returns the server’s response to the client.
* A load balancer distributes incoming client requests among a group of servers, in each case returning the response from the selected server to the appropriate client.

##### Load Balancing

Load balancers are most commonly deployed when a site needs multiple servers because the volume of requests is too much for a single server to handle efficiently. Deploying multiple servers also eliminates a single point of failure, making the website more reliable. Most commonly, the servers all host the same content, and the load balancer’s job is to distribute the workload in a way that makes the best use of each server’s capacity, prevents overload on any server, and results in the fastest possible response to the client.

A load balancer can also enhance the user experience by reducing the number of error responses the client sees. It does this by detecting when servers go down, and diverting requests away from them to the other servers in the group. In the simplest implementation, the load balancer detects server health by intercepting error responses to regular requests. Application health checks are a more flexible and sophisticated method in which the load balancer sends separate health-check requests and requires a specified type of response to consider the server healthy.

Another useful function provided by some load balancers is session persistence, which means sending all requests from a particular client to the same server. Even though HTTP is stateless in theory, many applications must store state information just to provide their core functionality – think of the shopping basket on an e-commerce site. Such applications underperform or can even fail in a load-balanced environment, if the load balancer distributes requests in a user session to different servers instead of directing them all to the server that responded to the initial request.

Whereas deploying a load balancer makes sense only when you have multiple servers, it often makes sense to deploy a reverse proxy even with just one web server or application server. You can think of the reverse proxy as a website’s “public face.” Its address is the one advertised for the website, and it sits at the edge of the site’s network to accept requests from web browsers and mobile apps for the content hosted at the website. The benefits are two-fold:
* Increased security – No information about your backend servers is visible outside your internal network, so malicious clients cannot access them directly to exploit any vulnerabilities. Many reverse proxy servers include features that help protect backend servers from distributed denial-of-service (DDoS) attacks, for example by rejecting traffic from particular client IP addresses (blacklisting), or limiting the number of connections accepted from each client.
* Increased scalability and flexibility – Because clients see only the reverse proxy’s IP address, you are free to change the configuration of your backend infrastructure. This is particularly useful In a load-balanced environment, where you can scale the number of servers up and down to match fluctuations in traffic volume.

Another reason to deploy a reverse proxy is for web acceleration – reducing the time it takes to generate a response and return it to the client. Techniques for web acceleration include the following:

* Compression – Compressing server responses before returning them to the client (for instance, with gzip) reduces the amount of bandwidth they require, which speeds their transit over the network.
* SSL termination – Encrypting the traffic between clients and servers protects it as it crosses a public network like the Internet. But decryption and encryption can be computationally expensive. By decrypting incoming requests and encrypting server responses, the reverse proxy frees up resources on backend servers which they can then devote to their main purpose, serving content.
* Caching – Before returning the backend server’s response to the client, the reverse proxy stores a copy of it locally. When the client (or any client) makes the same request, the reverse proxy can provide the response itself from the cache instead of forwarding the request to the backend server. This both decreases response time to the client and reduces the load on the backend server.


