## 8.1. Automated Scaling Listener

The automated scaling listener mechanism is a service agent that monitors and tracks communications between cloud service consumers and cloud services for dynamic scaling purposes. Automated scaling listeners are deployed within the cloud, typically near the firewall, from where they automatically track workload status information. Workloads can be determined by the volume of cloud consumer-generated requests or via back-end processing demands triggered by certain types of requests. For example, a small amount of incoming data can result in a large amount of processing.

Automated scaling listeners can provide different types of responses to workload fluctuation conditions, such as:

* Automatically scaling IT resources out or in based on parameters previously defined by the cloud consumer (commonly referred to as auto-scaling).
* Automatic notification of the cloud consumer when workloads exceed current thresholds or fall below allocated resources . This way, the cloud consumer can choose to adjust its current IT resource allocation.

## 8.2. Load Balancer

A common approach to horizontal scaling is to balance a workload across two or more IT resources to increase performance and capacity beyond what a single IT resource can provide. The load balancer mechanism is a runtime agent with logic fundamentally based on this premise.

Beyond simple division of labor algorithms (Figure 8.5), load balancers can perform a range of specialized runtime workload distribution functions that include:

* Asymmetric Distribution – larger workloads are issued to IT resources with higher processing capacities
* Workload Prioritization – workloads are scheduled, queued, discarded, and distributed workloads according to their priority levels
* Content-Aware Distribution – requests are distributed to different IT resources as dictated by the request content

A load balancer is programmed or configured with a set of performance and QoS rules and parameters with the general objectives of optimizing IT resource usage, avoiding overloads, and maximizing throughput.

The load balancer mechanisms can exist as a:

* multi-layer network switch
* dedicated hardware appliance
* dedicated software-based system (common in server operating systems)
* service agent (usually controlled by cloud management software)

The load balancer is typically located on the communication path between the IT resources generating the workload and the IT resources performing the workload processing. This mechanism can be designed as a transparent agent that remains hidden from the cloud service consumers, or as a proxy component that abstracts the IT resources performing their workload.

## 8.3. SLA Monitor

The SLA monitor mechanism is used to specifically observe the runtime performance of cloud services to ensure that they are fulfilling the contractual QoS requirements that are published in SLAs . The data collected by the SLA monitor is processed by an SLA management system to be aggregated into SLA reporting metrics. The system can proactively repair or failover cloud services when exception conditions occur, such as when the SLA monitor reports a cloud service as “down.”

## 8.4. Pay-Per-Use Monitor

The pay-per-use monitor mechanism measures cloud-based IT resource usage in accordance with predefined pricing parameters and generates usage logs for fee calculations and billing purposes.

Some typical monitoring variables are:

* request/response message quantity
* transmitted data volume
* bandwidth consumption

The data collected by the pay-per-use monitor is processed by a billing management system that calculates the payment fees.

## 8.5. Audit Monitor

The audit monitor mechanism is used to collect audit tracking data for networks and IT resources in support of (or dictated by) regulatory and contractual obligations. Figure 8.15 depicts an audit monitor implemented as a monitoring agent that intercepts “login” requests and stores the requestor’s security credentials, as well as both failed and successful login attempts, in a log database for future audit reporting purposes.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Cloud%20Computing/cloud%20computing%20concepts%20technology%20and%20architecture/Pictures/Figure%208.15.png">

## 8.6. Failover System

The failover system mechanism is used to increase the reliability and availability of IT resources by using established clustering technology to provide redundant implementations. A failover system is configured to automatically switch over to a redundant or standby IT resource instance whenever the currently active IT resource becomes unavailable.

Failover systems are commonly used for mission-critical programs and reusable services that can introduce a single point of failure for multiple applications. A failover system can span more than one geographical region so that each location hosts one or more redundant implementations of the same IT resource.

The resource replication mechanism is sometimes utilized by the failover system to provide redundant IT resource instances, which are actively monitored for the detection of errors and unavailability conditions.

Failover systems come in two basic configurations:

#### Active-Active

In an active-active configuration, redundant implementations of the IT resource actively serve the workload synchronously. Load balancing among active instances is required. When a failure is detected, the failed instance is removed from the load balancing scheduler. Whichever IT resource remains operational when a failure is detected takes over the processing.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Cloud%20Computing/cloud%20computing%20concepts%20technology%20and%20architecture/Pictures/Figure%208.17-8.18.png">

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Cloud%20Computing/cloud%20computing%20concepts%20technology%20and%20architecture/Pictures/Figure%208.19.png">

#### Active-Passive

In an active-passive configuration, a standby or inactive implementation is activated to take over the processing from the IT resource that becomes unavailable, and the corresponding workload is redirected to the instance taking over the operation.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Cloud%20Computing/cloud%20computing%20concepts%20technology%20and%20architecture/Pictures/Figure%208.20%20-%208.21.png">

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Cloud%20Computing/cloud%20computing%20concepts%20technology%20and%20architecture/Pictures/Figure%208.22.png">

Some failover systems are designed to redirect workloads to active IT resources that rely on specialized load balancers that detect failure conditions and exclude failed IT resource instances from the workload distribution. This type of failover system is suitable for IT resources that do not require execution state management and provide stateless processing capabilities. In technology architectures that are typically based on clustering and virtualization technologies, the redundant or standby IT resource implementations are also required to share their state and execution context. A complex task that was executed on a failed IT resource can remain operational in one of its redundant implementations.

## 8.7. Hypervisor

__The hypervisor mechanism is a fundamental part of virtualization infrastructure that is primarily used to generate virtual server instances of a physical server. A hypervisor is generally limited to one physical server and can therefore only create virtual images of that server.__ Similarly, a hypervisor can only assign virtual servers it generates to resource pools that reside on the same underlying physical server. A hypervisor has limited virtual server management features, such as increasing the virtual server’s capacity or shutting it down. The VIM provides a range of features for administering multiple hypervisors across physical servers.

Hypervisor software can be installed directly in bare-metal servers and provides features for controlling, sharing and scheduling the usage of hardware resources, such as processor power, memory, and I/O. These can appear to each virtual server’s operating system as dedicated resources.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Cloud%20Computing/cloud%20computing%20concepts%20technology%20and%20architecture/Pictures/Figure%208.27.png">

## 8.8. Resource Cluster

Cloud-based IT resources that are geographically diverse can be logically combined into groups to improve their allocation and use. The resource cluster mechanism is used to group multiple IT resource instances so that they can be operated as a single IT resource. This increases the combined computing capacity, load balancing, and availability of the clustered IT resources.

Resource cluster architectures rely on high-speed dedicated network connections, or cluster nodes, between IT resource instances to communicate about workload distribution, task scheduling, data sharing, and system synchronization. A cluster management platform that is running as distributed middleware in all of the cluster nodes is usually responsible for these activities. This platform implements a coordination function that allows distributed IT resources to appear as one IT resource, and also executes IT resources inside the cluster.

Common resource cluster types include:

* Server Cluster – Physical or virtual servers are clustered to increase performance and availability. Hypervisors running on different physical servers can be configured to share virtual server execution state (such as memory pages and processor register state) in order to establish clustered virtual servers. In such configurations, which usually require physical servers to have access to shared storage, virtual servers are able to live-migrate from one to another. In this process, the virtualization platform suspends the execution of a given virtual server at one physical server and resumes it on another physical server. The process is transparent to the virtual server operating system and can be used to increase scalability by live-migrating a virtual server that is running at an overloaded physical server to another physical server that has suitable capacity.
* Database Cluster – Designed to improve data availability, this high-availability resource cluster has a synchronization feature that maintains the consistency of data being stored at different storage devices used in the cluster.The redundant capacity is usually based on an active-active or active-passive failover system committed to maintaining the synchronization conditions.  
* Large Dataset Cluster – Data partitioning and distribution is implemented so that the target datasets can be efficiently partitioned without compromising data integrity or computing accuracy. Each cluster node processes workloads without communicating with other nodes as much as in other cluster types.  

Many resource clusters require cluster nodes to have almost identical computing capacity and characteristics in order to simplify the design of and maintain consistency within the resource cluster architecture. The cluster nodes in high-availability cluster architectures need to access and share common storage IT resources. This can require two layers of communication between the nodes—one for accessing the storage device and another to execute IT resource orchestration . Some resource clusters are designed with more loosely coupled IT resources that only require the network layer.

There are two basic types of resource clusters:

* Load Balanced Cluster – This resource cluster specializes in distributing workloads among cluster nodes to increase IT resource capacity while preserving the centralization of IT resource management. It usually implements a load balancer mechanism that is either embedded within the cluster management platform or set up as a separate IT resource.
* HA Cluster – A high-availability cluster maintains system availability in the event of multiple node failures, and has redundant implementations of most or all of the clustered IT resources. It implements a failover system mechanism that monitors failure conditions and automatically redirects the workload away from any failed nodes.  




Excerpt From: Erl, Thomas. “Cloud Computing: Concepts, Technology & Architecture (The Prentice Hall Service Technology Series from Thomas Erl).” iBooks. 

Excerpt From: Erl, Thomas. “Cloud Computing: Concepts, Technology & Architecture (The Prentice Hall Service Technology Series from Thomas Erl).” iBooks. 

Excerpt From: Erl, Thomas. “Cloud Computing: Concepts, Technology & Architecture (The Prentice Hall Service Technology Series from Thomas Erl).” iBooks. 

Excerpt From: Erl, Thomas. “Cloud Computing: Concepts, Technology & Architecture (The Prentice Hall Service Technology Series from Thomas Erl).” iBooks. 

Excerpt From: Erl, Thomas. “Cloud Computing: Concepts, Technology & Architecture (The Prentice Hall Service Technology Series from Thomas Erl).” iBooks. 

Excerpt From: Erl, Thomas. “Cloud Computing: Concepts, Technology & Architecture (The Prentice Hall Service Technology Series from Thomas Erl).” iBooks. 
