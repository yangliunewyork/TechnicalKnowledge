Load Balancing and Round-robin DNS are used to distribute loads to different hosts or networks to achieve load distribution, high availability, and geographical distribution for fast delivery. Mostly, it is being used in web based internet applications for the above mentioned reasons. These days, new methodology called CDN (Content Delivery Network) is introduced, but it is mainly targeting the static content delivery only. CDN will not give instant updates, unless its host sync frequency is increased.

# Load Balancing (Load Balancer)

Load balancers are software application or hardware devices placed in the network architecture to face user side, obviously behind the firewall. Basically, a load balancer will be assigned with an IP address for user interactions with service port numbers. For example, when you get a web load balancer you will get an IP address from the provider, with that only you map with DNS records. If you are going to use that for web server, you need to create port 80 in the load balancer. Behind load balancers, you can have sever farm for same services with same content and configurations. A percentage of http requests coming to load balancer IP will be distributed to hosts behind the load balancer as defined by you. One thing you need to make sure is that, all host servers are synchronised with same content and configuration, then only users will get the same content.

This kind of architecture will help us to increase high availability via redundant hosts. There are two types of load balancers; one is local or data centre load balancer and the other one is global load balancer. Read the difference between global load balancers and local or data centre load balancers.

# Round-robin DNS

DNS is the Domain Name Systems distributed in multiple databases to provide human readable and usable identification for hosts. Hosts are identified by their IP, and a name is assigned to that IP in the DNS server to avoid remembering the IP address to reach that host.  For example, when you request for differencebetween.com your local DNS server will provide the host details to communicate. Generally, it’s a single IP address of the differencebetween.com host. In Round-robin DNS, you can configure multiple IP addresses against a single domain name, and those IP addresses will be issued to user requests in a round robin manner. Here, the host computer or server can be anywhere in the world, which is equivalent to Global Load balancer.

DNS responds for queries, which could be defined depending on the applications. Generally it is in round robin manner; that is, if IP 1 is given to the first query, then the second query will receive IP 2, and so on. But, you can define this depending on your needs and application capabilities. If your DNS is intelligent enough to identify the geographical locations by respond time or any other mechanism, you can provide the closest IP to clients in that area.

# What is the difference between Load Balancer and Round-robin DNS?

(1)	We can achieve IP address and port number hiding in load balancer, but we can’t do that in DNS method.

(2)	DNS method, sometimes, will not work because some service providers use DNS caching, which stops getting the new IP for the client’s requests and directs to same IP, but in load balancers this will not be a problem.

(3)	DOS, DDOS attacks will not directly affect the host servers, instead it will affect load balancer IP, whereas in DNS method it will directly hit the host server.

(4)	In load balancer method , load balancer uses single TCP connection for multiple HTTP request, which will reduce the network congestion and server over head to keep track of TCP sessions, whereas in DNS method this is not applicable.

(5)	In HTTPS, SSL encryption and decryption consume more CPU usage, and this load can be eased by load balancer and let the host servers to perform their designated tasks; this also is not achievable in DNS method.

(6)	Some load balancers can have caching facility, and provide the clients with cached content without troubling host servers. This will increase the fast delivery via fast response time.

(7)	In Load balancers, load balancer polls host server’s health conditions, and if server is dead, it will remove the serving poll and distribute the load among others, which is also not available in DNS method.

(8)	Load balancer is a single point of failure, whereas in DNS method, generally, DNS records will be updated across the word in hierarchical manner and cached in local DNS, which will help to resolve the IP faster.
