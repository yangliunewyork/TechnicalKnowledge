Chapter 11. Fundamental Cloud Architectures

IT resources can be horizontally scaled via the addition of one or more identical IT resources, and a load balancer that provides runtime logic capable of evenly distributing the workload among the available IT resources. The resulting workload distribution architecture reduces both IT resource over-utilization and under-utilization to an extent dependent upon the sophistication of the load balancing algorithms and runtime logic.

This fundamental architectural model can be applied to any IT resource, with workload distribution commonly carried out in support of distributed virtual servers, cloud storage devices, and cloud services. Load balancing systems applied to specific IT resources usually produce specialized variations of this architecture that incorporate aspects of load balancing, such as:

* the service load balancing architecture 
* the load balanced virtual server architecture 
* the load balanced virtual switches architecture

In addition to the base load balancer mechanism, and the virtual server and cloud storage device mechanisms to which load balancing can be applied, the following mechanisms can also be part of this cloud architecture:

* Audit Monitor – When distributing runtime workloads, the type and geographical location of the IT resources that process the data can determine whether monitoring is necessary to fulfill legal and regulatory requirements.  
* Cloud Usage Monitor – Various monitors can be involved to carry out runtime workload tracking and data processing.  
* Hypervisor – Workloads between hypervisors and the virtual servers that they host may require distribution.  
* Logical Network Perimeter – The logical network perimeter isolates cloud consumer network boundaries in relation to how and where workloads are distributed.  
* Resource Cluster – Clustered IT resources in active/active mode are commonly used to support workload balancing between different cluster nodes.  
* Resource Replication – This mechanism can generate new instances of virtualized IT resources in response to runtime workload distribution demands.  

## 11.2. Resource Pooling Architecture

A resource pooling architecture is based on the use of one or more resource pools, in which identical IT resources are grouped and maintained by a system that automatically ensures that they remain synchronized.

Provided here are common examples of resource pools:

<img src="http://www.informit.com/content/images/chap4_9780133858563/elementLinks/04-01a.jpg">

Physical server pools are composed of networked servers that have been installed with operating systems and other necessary programs and/or applications and are ready for immediate use.  

<img src="http://www.informit.com/content/images/chap4_9780133858563/elementLinks/04-01b.jpg">

Virtual server pools are usually configured using one of several available templates chosen by the cloud consumer during provisioning. For example, a cloud consumer can set up a pool of mid-tier Windows servers with 4 GB of RAM or a pool of low-tier Ubuntu servers with 2 GB of RAM.  

<img src="https://docs.microsoft.com/en-us/windows-server/storage/storage-spaces/media/storage-spaces-states/storage-spaces-object-model.png">

Storage pools, or cloud storage device pools, consist of file-based or block-based storage structures that contain empty and/or filled cloud storage devices.

<img src="http://docs.hol.vmware.com/HOL-2017/hol-1787-use-1_html_en/images/9cac5471-583d-4b5b-b071-13238b8deaef.png">

Network pools (or interconnect pools) are composed of different preconfigured network connectivity devices. For example, a pool of virtual firewall devices or physical network switches can be created for redundant connectivity, load balancing, or link aggregation.

<img src="https://slideplayer.com/2775732/10/images/10/Resource+Pooling+Architecture.jpg">

CPU pools are ready to be allocated to virtual servers, and are typically broken down into individual processing cores.

Pools of physical RAM can be used in newly provisioned physical servers or to vertically scale physical servers.

<img src="https://slideplayer.com/2775732/10/images/11/Resource+Pooling+Architecture.jpg">


Dedicated pools can be created for each type of IT resource and individual pools can be grouped into a larger pool, in which case each individual pool becomes a sub-pool.

<img src="https://slideplayer.com/2775732/10/images/12/Resource+Pooling+Architecture.jpg">

Resource pools can become highly complex, with multiple pools created for specific cloud consumers or applications. A hierarchical structure can be established to form parent, sibling, and nested pools in order to facilitate the organization of diverse resource pooling requirements.

Sibling resource pools are usually drawn from physically grouped IT resources, as opposed to IT resources that are spread out over different data centers. Sibling pools are isolated from one another so that each cloud consumer is only provided access to its respective pool.

In the nested pool model, larger pools are divided into smaller pools that individually group the same type of IT resources together. Nested pools can be used to assign resource pools to different departments or groups in the same cloud consumer organization.

<img src="https://slideplayer.com/2775732/10/images/14/Fundamental+Cloud+Architectures.jpg">

After resources pools have been defined, multiple instances of IT resources from each pool can be created to provide an in-memory pool of “live” IT resources.

In addition to cloud storage devices and virtual servers, which are commonly pooled mechanisms, the following mechanisms can also be part of this cloud architecture:

* Audit Monitor – This mechanism monitors resource pool usage to ensure compliance with privacy and regulation requirements, especially when pools contain cloud storage devices or data loaded into memory.
* Cloud Usage Monitor – Various cloud usage monitors are involved in the runtime tracking and synchronization that are required by the pooled IT resources and any underlying management systems.
* Hypervisor – The hypervisor mechanism is responsible for providing virtual servers with access to resource pools, in addition to hosting the virtual servers and sometimes the resource pools themselves.
* Logical Network Perimeter – The logical network perimeter is used to logically organize and isolate resource pools.
* Pay-Per-Use Monitor – The pay-per-use monitor collects usage and billing information on how individual cloud consumers are allocated and use IT resources from various pools.
* Remote Administration System – This mechanism is commonly used to interface with backend systems and programs in order to provide resource pool administration features via a front-end portal.
* Resource Management System – The resource management system mechanism supplies cloud consumers with the tools and permission management options for administering resource pools.
* Resource Replication – This mechanism is used to generate new instances of IT resources for resource pools.  

## 11.3. Dynamic Scalability Architecture

Excerpt From: Erl, Thomas. “Cloud Computing: Concepts, Technology & Architecture (The Prentice Hall Service Technology Series from Thomas Erl).” iBooks. 
