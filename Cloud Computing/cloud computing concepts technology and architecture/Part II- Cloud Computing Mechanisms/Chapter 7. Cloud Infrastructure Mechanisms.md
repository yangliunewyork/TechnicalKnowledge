## 7.1. Logical Network Perimeter

Defined as the isolation of a network environment from the rest of a communications network, the logical network perimeter establishes a virtual network boundary that can encompass and isolate a group of related cloud-based IT resources that may be physically distributed.

Logical network perimeters are typically established via network devices that supply and control the connectivity of a data center and are commonly deployed as virtualized IT environments that include:

* Virtual Firewall – An IT resource that actively filters network traffic to and from the isolated network while controlling its interactions with the Internet.
* Virtual Network – Usually acquired through VLANs, this IT resource isolates the network environment within the data center infrastructure.

## 7.2. Virtual Server

A virtual server is a form of virtualization software that emulates a physical server. Virtual servers are used by cloud providers to share the same physical server with multiple cloud consumers by providing cloud consumers with individual virtual server instances.

<img src="https://devcentral.f5.com/weblogs/images/devcentral_f5_com/weblogs/macvittie/Windows-Live-Writer/Back-to-Basics-Load-balancing-Virtualize_3AB8/phys%20virt%20consolidation_2.png">

As a commodity mechanism, the virtual server represents the most foundational building block of cloud environments. Each virtual server can host numerous IT resources, cloud-based solutions, and various other cloud computing mechanisms. The instantiation of virtual servers from image files is a resource allocation process that can be completed rapidly and on-demand.

Cloud consumers that install or lease virtual servers can customize their environments independently from other cloud consumers that may be using virtual servers hosted by the same underlying physical server.

In order to enable the on-demand creation of virtual servers, cloud providers offer cloud consumers with a set of template virtual servers that are made available through pre-made VM images. VM images are files that represent the virtual disk images used by the hypervisor to boot the virtual server.

## 7.3. Cloud Storage Device

The cloud storage device mechanism represents storage devices that are designed specifically for cloud-based provisioning. Instances of these devices can be virtualized, similar to how physical servers can spawn virtual server images. Cloud storage devices are commonly able to provide fixed-increment capacity allocation in support of the pay-per-use mechanism. Cloud storage devices can be exposed for remote access via cloud storage services.

A primary concern related to cloud storage is the security, integrity, and confidentiality of data, which becomes more prone to being compromised when entrusted to external cloud providers and other third parties. There can also be legal and regulatory implications that result from relocating data across geographical or national boundaries. Another issue applies specifically to the performance of large databases. LANs provide locally stored data with network reliability and latency levels that are superior to those of WANs.

### Cloud Storage Levels

Cloud storage device mechanisms provide common logical units of data storage, such as:
* Files – Collections of data are grouped into files that are located in folders.
* Blocks – The lowest level of storage and the closest to the hardware, a block is the smallest unit of data that is still individually accessible.
* Datasets – Sets of data are organized into a table-based, delimited, or record format.
* Objects – Data and its associated metadata are organized as Web-based resources.

Each of these data storage levels is commonly associated with a certain type of technical interface which corresponds to a particular type of cloud storage device and cloud storage service used to expose its API.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Cloud%20Computing/cloud%20computing%20concepts%20technology%20and%20architecture/Part%20I-%20Fundamental%20Cloud%20Computing/Pictures/Figure%207.9.png">

### 7.4. Cloud Usage Monitor

The cloud usage monitor mechanism is a lightweight and autonomous software program responsible for collecting and processing IT resource usage data.

Depending on the type of usage metrics they are designed to collect and the manner in which usage data needs to be collected, cloud usage monitors can exist in different formats. 

#### Monitoring Agent

A monitoring agent is an intermediary, event-driven program that exists as a service agent and resides along existing communication paths to transparently monitor and analyze dataflows. This type of cloud usage monitor is commonly used to measure network traffic and message metrics.

#### Resource Agent

A resource agent is a processing module that collects usage data by having event-driven interactions with specialized resource software. This module is used to monitor usage metrics based on pre-defined, observable events at the resource software level, such as initiating, suspending, resuming, and vertical scaling.

#### Polling Agent

A polling agent is a processing module that collects cloud service usage data by polling IT resources. This type of cloud service monitor is commonly used to periodically monitor IT resource status, such as uptime and downtime.




