In any distributed architecture, we need to find the physical address of where a machine is located. This concept has been around since the beginning of distrib- uted computing and is known formally as service discovery. Service discovery can be something as simple as maintaining a property file with the addresses of all the remote services used by an application, or something as formalized (and compli- cated) as a UDDI (Universal Description, Discovery, and Integration) repository.

Service discovery is critical to microservice, cloud-based applications for two key reasons. First, it offers the application team the ability to quickly horizontally scale up and down the number of service instances running in an environment. The service consumers are abstracted away from the physical location of the service via service dis- covery. Because the service consumers don’t know the physical location of the actual service instances, new service instances can be added or removed from the pool of available services.

This ability to quickly scale services without disrupting the service consumers is an extremely powerful concept, because it moves a development team used to building monolithic, single-tenant (for example, one customer) applications away from think- ing about scaling only in terms of adding bigger, better hardware (vertical scaling) to the more powerful approach to scaling by adding more servers (horizontal scaling).

A monolithic approach usually drives development teams down the path of over- buying their capacity needs. Capacity increases come in clumps and spikes and are rarely a smooth steady path. Microservices allow us to scale up/down new service instances. Service discovery helps abstract that these deployments are occurring away from the service consumer.

The second benefit of service discovery is that it helps increase application resil- iency. When a microservice instance becomes unhealthy or unavailable, most service discovery engines will remove that instance from its internal list of available services. The damage caused by a down service will be minimized because the service discovery engine will route services around the unavailable service.

## 4.1 Where’s my service?

Whenever you have an application calling resources spread across multiple servers, it needs to locate the physical location of those resource. In the non-cloud world, this service location resolution was often solved through a combination of DNS and a net- work load balancer. Figure 4.1 illustrates this model.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%204.1.png">

An application needs to invoke a service located in another part of the organiza- tion. It attempts to invoke the service by using a generic DNS name along with a path that uniquely represents the service that the application was trying to invoke. The DNS name would resolve to a commercial load balancer, such as the popular F5 load balancer (http://f5.com) or an open source load balancer such as HAProxy (http:// haproxy.org).

The load balancer, upon receiving the request from the service consumer, locates the physical address entry in a routing table based on the path the user was trying to access. This routing table entry contains a list of one or more servers hosting the service. The load balancer then picks one of the servers in the list and forwards the request onto that server.

Each instance of a service is deployed to one or more application servers. The number of these application servers was often static (for example, the number of application servers hosting a service didn’t go up and down) and persistent (for exam- ple, if a server running an application server crashed, it would be restored to the same state it was at the time of the crash, and would have the same IP and configuration that it had previously.)

To achieve a form of high availability, a secondary load balancer is sitting idle and pinging the primary load balancer to see if it’s alive. If it isn’t alive, the secondary load balancer becomes active, taking over the IP address of the primary load balancer and beginning serving requests.

While this type of model works well with applications running inside of the four walls of a corporate data center and with a relatively small number of services running on a group of static servers, it doesn’t work well for cloud-based microservice applications. Reasons for this include:

* Single point of failure—While the load balancer can be made highly available, it’s a single point of failure for your entire infrastructure. If the load balancer goes down, every application relying on it goes down too. While you can make a load balancer highly available, load balancers tend to be centralized chokepoints within your application infrastructure.  
* Limited horizontal scalability—By centralizing your services into a single cluster of load balancers, you have limited ability to horizontally scale your load-balancing infrastructure across multiple servers. Many commercial load balancers are con- strained by two things: their redundancy model and licensing costs. Most com- mercial load balancers use a hot-swap model for redundancy so you only have a single server to handle the load, while the secondary load balancer is there only for fail-over in the case of an outage of the primary load balancer. You are, in essence, constrained by your hardware. Second, commercial load balancers also have restrictive licensing models geared toward a fixed capacity rather than a more variable model.  
* Statically managed—Most traditional load balancers aren’t designed for rapid registration and de-registration of services. They use a centralized database to store the routes for rules and the only way to add new routes is often through the vendor’s proprietary API (Application Programming Interface).  
* Complex—Because a load balancer acts as a proxy to the services, service con- sumer requests have to have their requests mapped to the physical services. This translation layer often added a layer of complexity to your service infra- structure because the mapping rules for the service have to be defined and deployed by hand. In a traditional load balancer scenario, this registration of new service instances was done by hand and not at startup time of a new ser- vice instance.  

These four reasons aren’t a general indictment of load balancers. They work well in a corporate environment where the size and scale of most applications can be handled through a centralized network infrastructure. In addition, load balancers still have a role to play in terms of centralizing SSL termination and managing service port secu- rity. A load balancer can lock down inbound (ingress) and outbound (egress) port access to all the servers sitting behind it. This concept of least network access is often a critical component when trying to meet industry-standard certification requirements such as PCI (Payment Card Industry) compliance.

However, in the cloud where you have to deal with massive amounts of transac- tions and redundancy, a centralized piece of network infrastructure doesn’t ulti- mately work as well because it doesn’t scale effectively and isn’t cost-efficient. Let’s now look at how you can implement a robust-service discovery mechanism for cloud- based applications.

## 4.2 On service discovery in the cloud

The solution for a cloud-based microservice environment is to use a service-discovery mechanism that’s

* Highly available—Service discovery needs to be able to support a “hot” cluster- ing environment where service lookups can be shared across multiple nodes in a service discovery cluster. If a node becomes unavailable, other nodes in the cluster should be able to take over.  
* Peer-to-peer—Each node in the service discovery cluster shares the state of a ser- vice instance.  
* Load balanced—Service discovery needs to dynamically load balance requests across all service instances to ensure that the service invocations are spread across all the service instances managed by it. In many ways, service discovery replaces the more static, manually managed load balancers used in many early web application implementations.  
* Resilient—The service discovery’s client should “cache” service information locally. Local caching allows for gradual degradation of the service discovery feature so that if service discovery service does become unavailable, applica- tions can still function and locate the services based on the information main- tained in its local cache.  
* Fault-tolerant—Service discovery needs to detect when a service instance isn’t healthy and remove the instance from the list of available services that can take client requests. It should detect these faults with services and take action with- out human intervention.  

### 4.2.1 The architecture of service discovery

To begin our discussion around service discovery architecture, we need to understand four concepts. These general concepts are shared across all service discovery imple- mentations:

* Service registration—How does a service register with the service discovery agent?  
* Client lookup of service address—What’s the means by which a service client looks up service information?  
* Information sharing—How is service information shared across nodes?  
* Health monitoring—How do services communicate their health back to the service discovery agent?  

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%204.2.png">

As service instances start up, they’ll register their physical location, path, and port that they can be accessed by with one or more service discovery instances. While each instance of a service will have a unique IP address and port, each service instance that comes up will register under the same service ID. A service ID is nothing more than a key that uniquely identifies a group of the same service instances.

A service will usually only register with one service discovery service instance. Most service discovery implementations use a peer-to-peer model of data propagation where the data around each service instance is communicated to all the other nodes in the cluster.

Depending on the service discovery implementation, the propagation mechanism might use a hard-coded list of services to propagate to or use a multi-casting protocol like the “gossip”2 or “infection-style”3 protocol to allow other nodes to “discover” changes in the cluster.

Finally, each service instance will push to or have pulled from its status by the ser- vice discovery service. Any services failing to return a good health check will be removed from the pool of available service instances.

Once a service has registered with a service discovery service, it’s ready to be used by an application or service that needs to use its capabilities. Different models exist for a client to “discover” a service. A client can rely solely on the service discovery engine to resolve service locations each time a service is called. With this approach, the ser- vice discovery engine will be invoked every time a call to a registered microservice instance is made. Unfortunately, this approach is brittle because the service client is completely dependent on the service discovery engine to be running to find and invoke a service.

A more robust approach is to use what’s called client-side load balancing.4 Figure 4.3 illustrates this approach.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%204.3.png">

In this model, when a consuming actor needs to invoke a service:

1. It will contact the service discovery service for all the service instances a service consumer is asking for and then cache data locally on the service consumer’s machine.  
2. Each time a client wants to call the service, the service consumer will look up the location information for the service from the cache. Usually client-side caching will use a simple load balancing algorithm like the “round-robin” load balancing algorithm to ensure that service calls are spread across multiple ser- vice instances.  
3. The client will then periodically contact the service discovery service and refresh its cache of service instances. The client cache is eventually consistent, but there’s always a risk that between when the client contacts the service dis- covery instance for a refresh and calls are made, calls might be directed to a ser- vice instance that isn’t healthy.
If, during the course of calling a service, the service call fails, the local service discovery cache is invalidated and the service discovery client will attempt to refresh its entries from the service discovery agent.  

## 4.6 Summary

* The service discovery pattern is used to abstract away the physical location of services.
* A service discovery engine such as Eureka can seamlessly add and remove ser- vice instances from an environment without the service clients being impacted.
* Client-side load balancing can provide an extra level of performance and resil-
iency by caching the physical location of a service on the client making the ser-
vice call.
* Eureka is a Netflix project that when used with Spring Cloud, is easy to set up
and configure.
* You used three different mechanisms in Spring Cloud, Netflix Eureka, and Netflix Ribbon to invoke a service. These mechanisms included:  
* Using a Spring Cloud service DiscoveryClient  
* Using Spring Cloud and Ribbon-backed RestTemplate   
* Using Spring Cloud and Netflix’s Feign client  


