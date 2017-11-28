__Round Robin DNS__ is a technique of load distribution, load balancing, or fault-tolerance provisioning multiple, redundant Internet Protocol service hosts, e.g., Web server, FTP servers, _by managing the Domain Name System's (DNS) responses to address requests from client computers according to an appropriate statistical model_.

In its simplest implementation, Round-robin DNS works by responding to DNS requests not only with a single potential IP address, but with one out of a list of potential IP addresses corresponding to several servers that host identical services. The order in which IP addresses from the list are returned is the basis for the term round robin. With each DNS response, the IP address sequence in the list is permuted. Usually, basic IP clients attempt connections with the first address returned from a DNS query, so that on different connection attempts, clients would receive service from different providers, thus distributing the overall load among servers.

There is no standard procedure for deciding which address will be used by the requesting application, a few resolvers attempt to re-order the list to give priority to numerically "closer" networks. Some desktop clients do try alternate addresses after a connection timeout of 30–45 seconds.

Round robin DNS is often used to load balance requests between a number of Web servers. For example, a company has one domain name and three identical copies of the same web site residing on three servers with three different IP addresses. When one user accesses the home page it will be sent to the first IP address. The second user who accesses the home page will be sent to the next IP address, and the third user will be sent to the third IP address. In each case, once the IP address is given out, it goes to the end of the list. The fourth user, therefore, will be sent to the first IP address, and so forth.

A round-robin DNS name is, on rare occasions, referred to as a "rotor" due to the rotation between alternative A records.

### Drawbacks

Although easy to implement, round robin DNS has a number of drawbacks, such as those arising from record caching in the DNS hierarchy itself, as well as client-side address caching and reuse, the combination of which can be difficult to manage. Round robin DNS should not solely be relied upon for service availability. If a service at one of the addresses in the list fails, the DNS will continue to hand out that address and clients will still attempt to reach the inoperable service.

Also, it may not be the best choice for load balancing on its own, since it merely alternates the order of the address records each time a name server is queried. There is no consideration for transaction time, server load, network congestion, etc. Round robin DNS load balancing works best for services with a large number of uniformly distributed connections to servers of equivalent capacity. Otherwise it just does load distribution.

Methods exist to overcome such limitations. For example, modified DNS servers (such as lbnamed) can routinely poll mirrored servers for availability and load factor. If a server does not reply as required, the server can be temporarily removed from the DNS pool, until it reports that it is once again operating within specs.
