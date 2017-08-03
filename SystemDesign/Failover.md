In computing and related technologies such as networking, failover is switching to a redundant or standby computer server, system, hardware component or network upon the failure or abnormal termination of the previously active application, server, system, hardware component, or network. Failover and switchover are essentially the same operation, except that __failover is automatic and usually operates without warning, while switchover requires human intervention.__

Systems designers usually provide failover capability in servers, systems or networks requiring near-continuous availability and a high degree of reliability.

At the server level, failover automation usually uses a "heartbeat" system that connects two servers, either through using a separate cable (for example, RS-232 serial ports/cable) or a network connection. As long as a regular "pulse" or "heartbeat" continues between the main server and the second server, the second server will not bring its systems online. There may also be a third "spare parts" server that has running spare components for "hot" switching to prevent downtime. The second server takes over the work of the first as soon as it detects an alteration in the "heartbeat" of the first machine. Some systems have the ability to send a notification of failover.

Certain systems, intentionally, do not failover entirely automatically, but require human intervention. This "automated with manual approval" configuration runs automatically once a human has approved the failover.

Failback is the process of restoring a system, component, or service previously in a state of failure back to its original, working state, and having the standby system go from functioning back to standby.

The use of virtualization software has allowed failover practices to become less reliant on physical hardware through the process referred to as migration in which a running virtual machine is moved from one physical host to another, with little or no disruption in service.

# Active-passive

With active-passive fail-over, heartbeats are sent between the active and the passive server on standby. If the heartbeat is interrupted, the passive server takes over the active's IP address and resumes service.

The length of downtime is determined by whether the passive server is already running in 'hot' standby or whether it needs to start up from 'cold' standby. Only the active server handles traffic.

Active-passive failover can also be referred to as master-slave failover.

![alt](http://www.jscape.com/hubfs/images/active_passive_high_availability_cluster.png?t=1501482101175)

* Setup: A single Adaptive Server runs either on the primary node or on the secondary node. The Adaptive Server runs on the primary node before a fail over and the secondary node after fail over.

* Failover: When a system fails over, the Adaptive Server and its associated resources are relocated to, and restarted on, the secondary node.

* Failback: Failback is a planned fail over or relocation of the Adaptive Server and its resources to the primary node. Failback is not required, but can be done for administrative purposes.

* Client connection failover: During failover and failback, clients connect to the same Adaptive Server to resubmit uncommitted transactions. Clients with the failover property reestablish their connections automatically.


# Active-active

In active-active, both servers are managing traffic, spreading the load between them.

If the servers are public-facing, the DNS would need to know about the public IPs of both servers. If the servers are internal-facing, application logic would need to know about both servers.

Active-active failover can also be referred to as master-master failover.

![alt](http://www.jscape.com/hubfs/images/active_active_high_availability_cluster_load_balancer.png?t=1501482101175)

* Setup: Two Adaptive Servers are configured as companion servers, each with independent workloads. These companions run on the primary and secondary nodes, respectively, as individual servers until one fails over.

* Failover: When fail over occurs, the secondary companion takes over the devices, client connections, and so on from the primary companion. The secondary companion services the failed-over clients, as well as any new clients, until the primary companion fails back and resumes its activities.

* Failback: Failback is a planned event during which the primary companion takes back its devices and client connections from the secondary companion to resume its services.

* Client connection failover: During failover, clients connect to the secondary companion to resubmit their uncommitted transactions. During failback, clients connect to the primary companion to resubmit their transactions. Clients with the failover property reestablish their connections automatically.
