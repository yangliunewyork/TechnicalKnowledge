A microservice-based architecture takes a different approach to delivering functional- ity. Specifically, microservice-based architectures have these characteristics:

* Constrained—Microservices have a single set of responsibilities and are narrow in scope. Microservices embrace the UNIX philosophy that an application is nothing more than a collection of services where each service does one thing and does that one thing really well.
* Loosely coupled—A microservice-based application is a collection of small ser- vices that only interact with one another through a non–implementation spe- cific interface using a non-proprietary invocation protocol (for example, HTTP and REST). As long as the interface for the service doesn’t change, the owners of the microservice have more freedom to make modifications to the service than in a traditional application architecture.
* Abstracted—Microservices completely own their data structures and data sources. Data owned by a microservice can only be modified by that service. Access control to the database holding the microservice’s data can be locked down to only allow the service access to it.
* Independent—Each microservice in a microservice application can be compiled and deployed independently of the other services used in the application. This means changes can be isolated and tested much more easily than with a more heavily interdependent, monolithic application.

Why are these microservice architecture attributes important to cloud-based develop- ment? Cloud-based applications in general have the following:

* A large and diverse user base—Different customers want different features, and they don’t want to have to wait for a long application release cycle before they can start using these features. Microservices allow features to be delivered quickly, because each service is small in scope and accessed through a well- defined interface.
* Extremely high uptime requirements—Because of the decentralized nature of microservices, microservice-based applications can more easily isolate faults and problems to specific parts of an application without taking down the entire application. This reduces overall downtime for applications and makes them more resistent to problems.
* Uneven volume requirements—Traditional applications deployed within the four walls of a corporate data center usually have consistent usage patterns that emerge over time. This makes capacity planning for these types of applications simple. But in a cloud-based application, a simple tweet on Twitter or a post on Slashdot can drive demand for a cloud-based application through the roof.

Because microservice applications are broken down into small components that can be deployed independently of one another, it’s much easier to focus on the components that are under load and scale those components horizontally across multiple servers in a cloud.

Like a successful police detective trying to get to the truth, the journey to build a suc- cessful microservice architecture involves incorporating the perspectives of multiple individuals within your software development organization. Although it takes more than technical people to deliver an entire application, I believe that the foundation for successful microservice development starts with the perspectives of three critical roles:

* The architect—The architect’s job is to see the big picture and understand how an application can be decomposed into individual microservices and how the microservices will interact to deliver a solution.  
* The software developer—The software developer writes the code and understands in detail how the language and development frameworks for the language will be used to deliver a microservice.  
* The DevOps engineer—The DevOps engineer brings intelligence to how the services are deployed and managed throughout not only production, but also all the nonproduction environments. The watchwords for the DevOps engineer are consistency and repeatability in every environment.  

## 2.1 The architect’s story: designing the microservice architecture

When building a microservices architecture, a project’s architect focuses on three key tasks:

1. Decomposing the business problem  
2. Establishing service granularity  
3. Defining the service interfaces  

### 2.1.1 Decomposing the business problem

When you’re building a microservice architecture, the question of granularity is important, but you can use the following concepts to determine the correct solution:

1. It’s better to start broad with your microservice and refactor to smaller services—It’s easy to go overboard when you begin your microservice journey and make every- thing a microservice. But decomposing the problem domain into small services often leads to premature complexity because microservices devolve into noth- ing more than fine-grained data services.  
2. Focus first on how your services will interact with one another—This will help establish the coarse-grained interfaces of your problem domain. It’s easier to refactor from being too coarse-grained to being too fine-grained.  
3. Service responsibilities will change over time as your understanding of the problem domain grows—Often, a microservice gains responsibilities as new application functionality is requested. What starts as a single microservice might grow into multiple services, with the original microservice acting as an orchestration layer for these new services and encapsulating their functionality from other parts of the application.  

#### The smells of a bad microservice
How do you know whether your microservices are the right size? If a microservice is too coarse-grained, you’ll likely see the following:

A service with too many responsibilities—The general flow of the business logic in the service is complicated and seems to be enforcing an overly diverse array of business rules.

The service is managing data across a large number of tables—A microservice is the system of record for the data it manages. If you find yourself persisting data to mul- tiple tables or reaching out to tables outside of the immediate database, this is a clue the service is too big. I like to use the guideline that a microservice should own no more than three to five tables. Any more, and your service is likely to have too much responsibility.

Too many test cases—Services can grow in size and responsibility over time. If you have a service that started with a small number of test cases and ends up with hun- dreds of unit and integration test cases, you might need to refactor.
What about a microservice that’s too fine-grained?

The microservices in one part of the problem domain breed like rabbits—If everything becomes a microservice, composing business logic out of the services becomes complex and difficult because the number of services needed to get a piece of work done grows tremendously. A common smell is when you have dozens of microser- vices in an application and each service interacts with only a single database table.

Your microservices are heavily interdependent on one another—You find that the microservices in one part of the problem domain keep calling back and forth between each other to complete a single user request.

Your microservices become a collection of simple CRUD (Create, Replace, Update, Delete) services—Microservices are an expression of business logic and not an abstraction layer over your data sources. If your microservices do nothing but CRUD- related logic, they’re probably too fine-grained.

A microservices architecture should be developed with an evolutionary thought pro- cess where you know that you aren’t going to get the design right the first time. That’s why __it’s better to start with your first set of services being more coarse-grained than fine-grained__. It’s also important not to be dogmatic with your design. You may run into physical constraints on your services where you’ll need to make an aggregation service that joins data together because two separate services will be too chatty, or where no clear boundaries exist between the domain lines of a service.

In the end, take a pragmatic approach and deliver, rather than waste time trying to get the design perfect and then have nothing to show for your effort.

### 2.1.3 Talking to one another: service interfaces

In general, the following guidelines can be used for thinking about service inter- face design:

1. Embrace the REST philosophy—The REST approach to services is at heart the embracing of HTTP as the invocation protocol for the services and the use of standard HTTP verbs (GET, PUT, POST, and DELETE). Model your basic behaviors around these HTTP verbs.  
2. Use URI’s to communicate intent—The URI you use as endpoints for the service should describe the different resources in your problem domain and provide a basic mechanism for relationships of resources within your problem domain.  
3. Use JSON for your requests and responses—JavaScript Object Notation (in other words, JSON) is an extremely lightweight data-serialization protocol and is much easier to consume then XML.  
4. Use HTTP status codes to communicate results—The HTTP protocol has a rich body of standard response codes to indicate the success or failure of a service. Learn these status codes and most importantly use them consistently across all your services.  

## 2.2 When not to use microservices

### 2.2.1 Complexity of building distributed systems

Because microservices are distributed and fine-grained (small), they introduce a level of complexity into your application that wouldn’t be there in more monolithic appli- cations. Microservice architectures require a high degree of operational maturity. Don’t consider using microservices unless your organization is willing to invest in the automation and operational work (monitoring, scaling) that a highly distributed application needs to be successful.

### 2.2.2 Server sprawl

One of the most common deployment models for microservices is to have one microservice instance deployed on one server. In a large microservices-based applica- tion, you might end up with 50 to 100 servers or containers (usually virtual) that have to be built and maintained in production alone. Even with the lower cost of running these services in the cloud, the operational complexity of having to manage and mon- itor these servers can be tremendous.

NOTE The flexibility of microservices has to be weighed against the cost of running all of these servers.

### 2.2.3 Type of application

Microservices are geared toward reusability and are extremely useful for building large applications that need to be highly resilient and scalable. This is one of the rea- sons why so many cloud-based companies have adopted microservices. If you’re build- ing small, departmental-level applications or applications with a small user base, the complexity associated with building on a distributed model such as microservices might be more expense then it’s worth.

### 2.2.4 Data transformations and consistency

As you begin looking at microservices, you need to think through the data usage patterns of your services and how service consumers are going to use them. A microservice wraps around and abstracts away a small number of tables and works well as a mechanism for performing “operational” tasks such as creating, adding, and performing simple (non-complex) queries against a store.

If your applications need to do complex data aggregation or transformation across multiple sources of data, the distributed nature of microservices will make this work difficult. Your microservices will invariably take on too much responsibility and can also become vulnerable to performance problems.

Also keep in mind that no standard exists for performing transactions across microservices. If you need transaction management, you will need to build that logic yourself. In addition, microservices can communicate amongst themselves by using messages. Messaging introduces latency in data updates. Your applications need to handle eventual consistency where updates that are applied to your data might not immediately appear.

## 2.4 The DevOps story: building for the rigors of runtime

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%202.6.png">

#### Building the Twelve-Factor microservice service application
One of my biggest hopes with this book is that you realize that a successful microser- vice architecture requires strong application development and DevOps practices. One of the most succinct summaries of these practices can be found in Heroku’s Twelve- Factor Application manifesto (https://12factor.net/). This document provides 12 best practices you should always keep in the back of your mind when building microser- vices. As you read this book, you’ll see these practices intertwined into the examples. I’ve summarized them as follows:

* Codebase—All application code and server provisioning information should be in ver- sion control. Each microservice should have its own independent code repository within the source control systems.
* Dependencies—Explicitly declare the dependencies your application uses through build tools such as Maven (Java). Third-party JAR dependence should be declared using their specific version numbers. This allows your microservice to always be built using the same version of libraries.
* Config—Store your application configuration (especially your environment-specific configuration) independently from your code. Your application configuration should never be in the same repository as your source code.
* Backing services—Your microservice will often communicate over a network to a data- base or messaging system. When it does, you should ensure that at any time, you can swap out your implementation of the database from an in-house managed service to a third-party service. 
* Build, release, run—Keep your build, release, and run pieces of deploying your appli- cation completely separate. Once code is built, the developer should never make changes to the code at runtime. Any changes need to go back to the build process and be redeployed. A built service is immutable and cannot be changed.
* Processes—Your microservices should always be stateless. They can be killed and replaced at any timeout without the fear that a loss-of-a-service instance will result in data loss.
* Port binding—A microservice is completely self-contained with the runtime engine for the service packaged in the service executable. You should run the service without the need for a separated web or application server. The service should start by itself on the command line and be accessed immediately through an exposed HTTP port.
* Concurrency—When you need to scale, don’t rely on a threading model within a single service. Instead, launch more microservice instances and scale out horizontally. This doesn’t preclude using threading within your microservice, but don’t rely on it as your sole mechanism for scaling. Scale out, not up.
* Disposability—Microservices are disposable and can be started and stopped on demand. Startup time should be minimized and processes should shut down grace- fully when they receive a kill signal from the operating system.
* Dev/prod parity—Minimize the gaps that exist between all of the environments in which the service runs (including the developer’s desktop). A developer should use the same infrastructure locally for the service development in which the actual ser- vice will run. It also means that the amount of time that a service is deployed between environments should be hours, not weeks. As soon as code is committed, it should be tested and then promoted as quickly as possible from Dev all the way to Prod.
* Logs—Logs are a stream of events. As logs are written out, they should be stream- able to tools, such as Splunk (http://splunk.com) or Fluentd (http://fluentd.org), that will collate the logs and write them to a central location. The microservice should never be concerned about the mechanics of how this happens and the developer should visually look at the logs via STDOUT as they’re being written out.
* Admin processes—Developers will often have to do administrative tasks against their services (data migration or conversion). These tasks should never be ad hoc and instead should be done via scripts that are managed and maintained through the source code repository. These scripts should be repeatable and non-changing (the script code isn’t modified for each environment) across each environment they’re run against.

### 2.4.1 Service assembly: packaging and deploying your microservices

From a DevOps perspective, one of the key concepts behind a microservice architec- ture is that multiple instances of a microservice can be deployed quickly in response to a change application environment (for example, a sudden influx of user requests, problems within the infrastructure, and so on).

To accomplish this, a microservice needs to be packaged and installable as a single artifact with all of its dependencies defined within it. This artifact can then be deployed to any server with a Java JDK installed on it. These dependencies will also include the runtime engine (for example, an HTTP server or application container) that will host the microservice.

### 2.4.2 Service bootstrapping: managing configuration of your microservices

Service bootstrapping occurs when the microservice is first start- ing up and needs to load its application configuration information.

As any application developer knows, there will be times when you need to make the runtime behavior of the application configurable. Usually this involves reading your application configuration data from a property file deployed with the application or reading the data out of a data store such as a relational database.

Microservices often run into the same type of configuration requirements. The difference is that in microservice application running in the cloud, you might have hundreds or even thousands of microservice instances running. Further complicating this is that the services might be spread across the globe. With a high number of geographically dispersed services, it becomes unfeasible to redeploy your services to pick up new configuration data.

### 2.4.3 Service registration and discovery: how clients communicate with your microservices

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%202.9.png">

From a microservice consumer perspective, a microservice should be location-transparent, because in a cloud-based environment, servers are ephemeral. Ephemeral means the servers that a service is hosted on usually have shorter lives then a service running in a corporate data center. Cloud-based services can be started and torn down quickly with an entirely new IP address assigned to the server on which the ser- vices are running.

By insisting that services are treated as short-lived disposable objects, microservice architectures can achieve a high-degree of scalability and availability by having multi- ple instances of a service running. Service demand and resiliency can be managed as quickly as the situation warrants. Each service has a unique and non-permanent IP address assigned to it. The downside to ephemeral services is that with services constantly coming up and down, managing a large pool of ephemeral services manually or by hand is an invitation to an outage.

A microservice instance needs to register itself with the third-party agent. This registration process is called service discovery. When a microservice instance registers with a service discovery agent, it will tell the discovery agent two things: the physical IP address or domain address of the service instance, and a logical name that an application can use to look up in a service. Certain service discovery agents will also require a URL back to the registering service that can be used by the service discovery agent to perform health checks.

The service client then communicates with the discovery agent to look up the service’s location.

### 2.4 Communicating a microservice’s health


<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%202.10.png">

A service discovery agent doesn’t act only as a traffic cop that guides the client to the location of the service. In a cloud-based microservice application, you’ll often have multiple instances of a service running. Sooner or later, one of those service instances will fail. The service discovery agent monitors the health of each service instance regis- tered with it and removes any service instances from its routing tables to ensure that clients aren’t sent a service instance that has failed.

After a microservice has come up, the service discovery agent will continue to monitor and ping the health check interface to ensure that that service is available. 

By building a consistent health check interface, you can use cloud-based monitor- ing tools to detect problems and respond to them appropriately.

If the service discovery agent discovers a problem with a service instance, it can take corrective action such as shutting down the ailing instance or bringing additional service instances up.

In a microservices environment that uses REST, the simplest way to build a health check interface is to expose an HTTP end-point that can return a JSON payload and HTTP status code. In a non-Spring-Boot-based microservice, it’s often the developer’s responsibility to write an endpoint that will return the health of the service.

In Spring Boot, exposing an endpoint is trivial and involves nothing more than modifying your Maven build file to include the Spring Actuator module.

## 2.5 Pulling the perspectives together

Microservices in the cloud seem deceptively simple. But to be successful with them, you need to have an integrated view that pulls the perspective of the architect, the developer, and DevOps engineer together into a cohesive vision. The key takeaways for each of these perspectives are

* Architect—Focus on the natural contours of your business problem. Describe your business problem domain and listen to the story you’re telling. Target microservice candidates will emerge. Remember, too, that it’s better to start with a “coarse-grained” microservice and refactor back to smaller services than to start with a large group of small services. Microservice architectures, like most good architectures, are emergent and not preplanned to-the-minute.
* Software engineer—The fact that the service is small doesn’t mean good design principles get thrown out the window. Focus on building a layered service where each layer in the service has discrete responsibilities. Avoid the tempta- tion to build frameworks in your code and try to make each microservice com- pletely independent. Premature framework design and adoption can have massive maintenance costs later in the lifecycle of the application.
* DevOps engineer—Services don’t exist in a vacuum. Establish the lifecycle of your services early. The DevOps perspective needs to focus not only on how to auto- mate the building and deployment of a service, but also on how to monitor the health of the service and react when something goes wrong. Operationalizing a service often takes more work and forethought than writing business logic.

## 2.6 Summary

* To be successful with microservices, you need to integrate in the architect’s, software developer’s, and DevOps’ perspectives.
* Microservices, while a powerful architectural paradigm, have their benefits and tradeoffs. Not all applications should be microservice applications.
* From an architect’s perspective, microservices are small, self-contained, and distributed. Microservices should have narrow boundaries and manage a small set of data.
* From a developer’s perspective, microservices are typically built using a REST- style of design, with JSON as the payload for sending and receiving data from the service.
* Spring Boot is the ideal framework for building microservices because it lets you build a REST-based JSON service with a few simple annotations.
* From a DevOp’s perspective, how a microservice is packaged, deployed, and monitored are of critical importance.
* Out of the box, Spring Boot allows you to deliver a service as a single executable JAR file. An embedded Tomcat server in the producer JAR file hosts the service.
* Spring Actuator, which is included with the Spring Boot framework, exposes information about the operational health of the service along with information about the services runtime.

