Cloud-based IT resources need to be set up, configured, maintained, and monitored. The systems covered in this chapter are mechanisms that encompass and enable these types of management tasks. They form key parts of cloud technology architectures by facilitating the control and evolution of the IT resources that form cloud platforms and solutions.
The following management-related mechanisms are described in this chapter:

* Remote Administration System
* Resource Management System
* SLA Management System
* Billing Management System

These systems typically provide integrated APIs and can be offered as individual products, custom applications, or combined into various product suites or multi-function applications.

## 9.1. Remote Administration System

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/Cloud%20Computing/cloud%20computing%20concepts%20technology%20and%20architecture/Pictures/Figure%209.2.png">

The remote administration system mechanism  provides tools and user-interfaces for external cloud resource administrators to configure and administer cloud-based IT resources.

The tools and APIs provided by a remote administration system are generally used by the cloud provider to develop and customize online portals that provide cloud consumers with a variety of administrative controls.

The following are the two primary types of portals that are created with the remote administration system:

* Usage and Administration Portal – A general purpose portal that centralizes management controls to different cloud-based IT resources and can further provide IT resource usage reports.
* Self-Service Portal – This is essentially a shopping portal that allows cloud consumers to search an up-to-date list of cloud services and IT resources that are available from a cloud provider (usually for lease). The cloud consumer submits its chosen items to the cloud provider for provisioning. This portal is primarily associated with the rapid provisioning.

Tasks that can commonly be performed by cloud consumers via a remote administration console include:

* configuring and setting up cloud services
* provisioning and releasing IT resource for on-demand cloud services
* monitoring cloud service status, usage, and performance
* monitoring QoS and SLA fulfillment
* managing leasing costs and usage fees
* managing user accounts, security credentials, authorization, and access control
* tracking internal and external access to leased services
* planning and assessing IT resource provisioning
* capacity planning

While the user-interface provided by the remote administration system will tend to be proprietary to the cloud provider, there is a preference among cloud consumers to work with remote administration systems that offer standardized APIs. This allows a cloud consumer to invest in the creation of its own front-end with the fore-knowledge that it can reuse this console if it decides to move to another cloud provider that supports the same standardized API. Additionally, the cloud consumer would be able to further leverage standardized APIs if it is interested in leasing and centrally administering IT resources from multiple cloud providers and/or IT resources residing in cloud and on-premise environments.

## 9.2. Resource Management System

The resource management system mechanism helps coordinate IT resources in response to management actions performed by both cloud consumers and cloud providers. Core to this system is the __virtual infrastructure manager (VIM)__ that coordinates the server hardware so that virtual server instances can be created from the most expedient underlying physical server. A VIM is a commercial product that can be used to manage a range of virtual IT resources across multiple physical servers. For example, a VIM can create and manage multiple instances of a hypervisor across different physical servers or allocate a virtual server on one physical server to another (or to a resource pool).

Tasks that are typically automated and implemented through the resource management system include:

* managing virtual IT resource templates that are used to create pre-built instances, such as virtual server images  
* allocating and releasing virtual IT resources into the available physical infrastructure in response to the starting, pausing, resuming, and termination of virtual IT resource instances  
* coordinating IT resources in relation to the involvement of other mechanisms, such as resource replication, load balancer, and failover system  
* enforcing usage and security policies throughout the lifecycle of cloud service instances  
* monitoring operational conditions of IT resources  

Resource management system functions can be accessed by cloud resource administrators employed by the cloud provider or cloud consumer. Those working on behalf of a cloud provider will often be able to directly access the resource management system’s native console.

Resource management systems typically expose APIs that allow cloud providers to build remote administration system portals that can be customized to selectively offer resource management controls to external cloud resource administrators acting on behalf of cloud consumer organizations via usage and administration portals.

## 9.3. SLA Management System

The SLA management system mechanism represents a range of commercially available cloud management products that provide features pertaining to the administration, collection, storage, reporting, and runtime notification of SLA data.

An SLA management system deployment will generally include a repository used to store and retrieve collected SLA data based on pre-defined metrics and reporting parameters. It will further rely on one or more SLA monitor mechanisms to collect the SLA data that can then be made available in near-real time to usage and administration portals to provide on-going feedback regarding active cloud services. The metrics monitored for individual cloud services are aligned with the SLA guarantees in corresponding cloud provisioning contracts.

<img src="https://image.slidesharecdn.com/chapter9-141009042024-conversion-gate01/95/cloud-management-mechanisms-17-638.jpg?cb=1412828533">

## 9.4. Billing Management System

The billing management system mechanism is dedicated to the collection and processing of usage data as it pertains to cloud provider accounting and cloud consumer billing. Specifically, the billing management system relies on pay-per-use monitors to gather runtime usage data that is stored in a repository that the system components then draw from for billing, reporting, and invoicing purposes.

<img src="https://image.slidesharecdn.com/chapter9-141009042024-conversion-gate01/95/cloud-management-mechanisms-19-638.jpg">

The billing management system allows for the definition of different pricing policies, as well as custom pricing models on a per cloud consumer and/or per IT resource basis. Pricing models can vary from the traditional pay-per-use models, to flat-rate or pay-per-allocation modes, or combinations thereof.

Billing arrangements be based on pre-usage and post-usage payments. The latter type can include pre-defined limits or it can be set up (with the mutual agreement of the cloud consumer) to allow for unlimited usage (and, consequently, no limit on subsequent billing). When limits are established, they are usually in the form of usage quotas. When quotas are exceeded, the billing management system can block further usage requests by cloud consumers.

