## Reference

https://msdn.microsoft.com/en-us/library/bb742455.aspx


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

