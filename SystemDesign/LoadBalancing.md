## Reference

https://msdn.microsoft.com/en-us/library/bb742455.aspx
http://www.thegeekstuff.com/2016/01/load-balancer-intro/?utm_source=tuicool&utm_medium=referral

# Load Balancing

In computing, load balancing improves the distribution of workloads across multiple computing resources, such as computers, a computer cluster, network links, central processing units, or disk drives. Load balancing aims to optimize resource use, maximize throughput, minimize response time, and avoid overload of any single resource. Using multiple components with load balancing instead of a single component may increase reliability and availability through redundancy. Load balancing usually involves dedicated software or hardware, such as a multilayer switch or a Domain Name System server process.



## What is Load Balancer ?
A load balancer is a device that acts as a reverse proxy and distributes network or application traffic across a number of servers. Load balancers are used to increase capacity (concurrent users) and reliability of applications. They improve the overall performance of applications by decreasing the burden on servers associated with managing and maintaining application and network sessions, as well as by performing application-specific tasks.

![alt](https://qph.ec.quoracdn.net/main-qimg-2f90af6447b52481eb6bd06a382dce44-c)

Load balancers are generally grouped into two categories: Layer 4 and Layer 7. Layer 4 load balancers act upon data found in network and transport layer protocols (IP, TCP, FTP, UDP). Layer 7 load balancers distribute requests based upon data found in application layer protocols such as HTTP.

Requests are received by both types of load balancers and they are distributed to a particular server based on a configured algorithm. Some industry standard algorithms are:

* Round robin
* Weighted round robin
* Least connections
* Least response time

Layer 7 load balancers can further distribute requests based on application specific data such as HTTP headers, cookies, or data within the application message itself, such as the value of a specific parameter.

Load balancers ensure reliability and availability by monitoring the "health" of applications and only sending requests to servers and applications that can respond in a timely manner.

## Active-Active vs Active-Passive High Availability Cluster
The two most commonly used high availability (HA) cluster configurations are active-active and active-passive. What's the difference between the two? 

### Active-Active high availability cluster

![alt](http://www.jscape.com/hubfs/images/active_active_high_availability_cluster_load_balancer.png?t=1485219504542)

An active-active cluster is typically made up of at least two nodes, both actively running the same kind of service simultaneously. The main purpose of an active-active cluster is to achieve load balancing. Load balancing distributes workloads across all nodes in order to prevent any single node from getting overloaded. Because there are more nodes available to serve, there will also be a marked improvement in throughput and response times.

The set up below, which consists of a load balancer and two (2) HTTP servers (i.e. 2 nodes), is an example of this type of HA cluster configuration. Instead of connecting directly to an HTTP server, web clients go through the load balancer, which in turn connects each client to any of the HTTP servers behind it. 

Assigning of clients to the nodes in the cluster isn't an arbitrary process. Rather, it's based on what ever load balancing algorithm is set on the load balancer. So, for example in a "Round Robin" algorithm, the first client to connect is sent to the 1st server, the second client to the 2nd server, the 3rd client back to the 1st server, the 4th client back to the 2nd server, and so on.

In order for the high availability cluster to operate seamlessly, it's recommended that the two nodes be configured for redundancy. In other words, their individual configurations/settings must be virtually identical.

### Active-Passive high availability cluster

![alt](http://www.jscape.com/hubfs/images/active_passive_high_availability_cluster.png?t=1485219504542)

Like the active-active configuration, active-passive also consists of at least two nodes. However, as the name "active-passive" implies, not all nodes are going to be active. In the case of two nodes, for example, if the first node is already active, the second node must be passive or on standby.

When clients connect to a 2-node cluster in active-passive configuration, they only connect to one server. In other words, all clients will connect to the same server. Like in the active-active configuration, it's important that the two servers have exactly the same settings (i.e., redundant).

If changes are made on the settings of the primary server, those changes must be cascaded to the failover server. So when the failover does take over, the clients won't be able to tell the difference. 

### How does Software and Hardware Load Balancer Work

http://www.thegeekstuff.com/2016/01/load-balancer-intro/?utm_source=tuicool&utm_medium=referral


# Load balancing in distributed system

oad balancer (LB) is another critical piece of any distributed system. It helps to distribute load across multiple resources according to some metric (random, round-robin, random with weighting for memory or CPU utilization, etc.). LB also keeps track of the status of all the resources while distributing requests. If a server is not available to take new requests or is not responding or has elevated error rate, LB will stop sending traffic to such a server.

To utilize full scalability and redundancy, we can try to balance the load at each layer of the system. We can add LBs at three places:

* Between the user and the web server.  
* Between web servers and an internal platform layer, like application servers or cache servers.  
* Between internal platform layer and database.  

There are many ways to implement load balancing.

##### 1. Smart Clients

A smart client will take a pool of service hosts and balances load across them. It also detects hosts that are not responding to avoid sending requests their way. Smart clients also have to detect recovered hosts, deal with adding new hosts, etc.

Adding load-balancing functionality into the database (cache, service, etc.) client is usually an attractive solution for the developer. It looks easy to implement and manage especially when the system is not large. But as the system grows, LBs need to be evolved into standalone servers.

##### 2. Hardware Load Balancers

The most expensive–but very high performance–solution to load balancing is to buy a dedicated hardware load balancer (something like a Citrix NetScaler). While they can solve a remarkable range of problems, hardware solutions are very expensive, and they are not trivial to configure.

As such, even large companies with large budgets will often avoid using dedicated hardware for all their load-balancing needs. Instead, they use them only as the first point of contact for user requests to their infrastructure and use other mechanisms (smart clients or the hybrid approach discussed in the next section) for load-balancing for traffic within their network.

##### 3. Software Load Balancers
If we want to avoid the pain of creating a smart client, and since purchasing dedicated hardware is excessive, we can adopt a hybrid approach, called software load-balancers.

HAProxy is a one of the popular open source software LB. Load balancer can be placed between client and server or between two server side layers. If we can control the machine where the client is running, HAProxy could be running on the same machine. Each service we want to load balance can have a locally bound port (e.g., localhost:9000) on that machine, and the client will use this port to connect to the server. This port is, actually, managed by HAProxy; every client request on this port will be received by the proxy and then passed to the backend service in an efficient way (distributing load). If we can’t manage client’s machine, HAProxy can run on an intermediate server. Similarly, we can have proxies running between different server side components. HAProxy manages health checks and will remove or add machines to those pools. It also balances requests across all the machines in those pools.

For most systems, we should start with a software load balancer and move to smart clients or hardware load balancing as need arises.
