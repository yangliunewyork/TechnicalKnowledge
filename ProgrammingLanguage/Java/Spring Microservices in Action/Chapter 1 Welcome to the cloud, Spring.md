## 1.1 What’s a microservice?

Before the concept of microservices evolved, most web-based applications were built using a monolithic architectural style. In a monolithic architecture, an application is delivered as a single deployable software artifact. All the UI (user interface), business, and database access logic are packaged together into a single application artifact and deployed to an application server.

Remember, a microservice is a small, loosely coupled, distributed service.Microservices allow you to take a large application and decompose it into easy-to-manage components with narrowly defined responsibilities. Microservices help combat the traditional problems of complexity in a large code base by decomposing the large code base down into small, well-defined pieces. The key concept you need to embrace as you think about microservices is decomposing and unbundling the functionality of your applications so they’re completely independent of one another.

A microservice architecture has the following characteristics:

* Application logic is broken down into small-grained components with welldefined boundaries of responsibility that coordinate to deliver a solution.
* Each component has a small domain of responsibility and is deployed completely independently of one another. Microservices should have responsibility for a single part of a business domain. Also, a microservice should be reusable across multiple applications.
* Microservices communicate based on a few basic principles (notice I said principles, not standards) and employ lightweight communication protocols such as HTTP and JSON (JavaScript Object Notation) for exchanging data between the service consumer and service provider.
* The underlying technical implementation of the service is irrelevant because the applications always communicate with a technology-neutral protocol (JSON is the most common). This means an application built using a microservice application could be built with multiple languages and technologies.
* Microservices—by their small, independent, and distributed nature—allow organizations to have small development teams with well-defined areas of responsibility. These teams might work toward a single goal such as delivering an application, but each team is responsible only for the services on which they’re working.

## 1.2 What is Spring and why is it relevant to microservices?

Spring has become the de facto development framework for building Java-based applications. At its core, Spring is based on the concept of dependency injection. In a normal Java application, the application is decomposed into classes where each class often has explicit linkages to other classes in the application. The linkages are the invocation of a class constructor directly in the code. Once the code is compiled, these linkage points can’t be changed.

This is problematic in a large project because these external linkages are brittle and making a change can result in multiple downstream impacts to other code. A dependency injection framework, such as Spring, allows you to more easily manage large Java projects by externalizing the relationship between objects within your application through convention (and annotations) rather than those objects having hard-coded knowledge about each other. Spring sits as an intermediary between the different Java classes of your application and manages their dependencies. Spring essentially lets you assemble your code together like a set of Lego bricks that snap together.

What’s amazing about the Spring framework and a testament to its development community is its ability to stay relevant and reinvent itself. The Spring development team quickly saw that many development teams were moving away from monolithic applications where the application’s presentation, business, and data access logic were packaged together and deployed as a single artifact. Instead, teams were moving to highly distributed models where services were being built as small, distributed services that could be easily deployed to the cloud. In response to this shift, the Spring development team launched two projects: Spring Boot and Spring Cloud.

Spring Boot is a re-envisioning of the Spring framework. While it embraces core features of Spring, Spring Boot strips away many of the “enterprise” features found in Spring and instead delivers a framework geared toward Java-based, REST-oriented (Representational State Transfer)1 microservices. With a few simple annotations, a Java developer can quickly build a REST microservice that can be packaged and deployed without the need for an external application container.

## 1.5 Building a microservice with Spring Boot

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%201.3.png">


## 1.6 Why change the way we build applications?

We’re at an inflection point in history. Almost all aspects of modern society are now wired together via the internet. Companies that used to serve local markets are suddenly finding that they can reach out to a global customer base. However, with a larger global customer base also comes global competition. These competitive pressures mean the following forces are impacting the way developers have to think about building applications:

* __Complexity has gone way up__—Customers expect that all parts of an organization know who they are. “Siloed” applications that talk to a single database and don’t integrate with other applications are no longer the norm. Today’s applications need to talk to multiple services and databases residing not only inside a company’s data center, but also to external service providers over the internet.  
* __Customers want faster delivery__—Customers no longer want to wait for the next annual release or version of a software package. Instead, they expect the features in a software product to be unbundled so that new functionality can be released quickly in weeks (even days) without having to wait for an entire product release.  
* __Performance and scalability__—Global applications make it extremely difficult to predict how much transaction volume is going to be handled by an application and when that transaction volume is going to hit. Applications need to scale up across multiple servers quickly and then scale back down when the volume needs have passed.  
* __Customers expect their applications to be available__—Because customers are one click away from a competitor, a company’s applications must be highly resilient. Failures or problems in one part of the application shouldn’t bring down the entire application.  

To meet these expectations, we, as application developers, have to embrace the paradox that to build high-scalable and highly redundant applications we need to break our applications into small services that can be built and deployed independently of one another. If we “unbundle” our applications into small services and move them away from a single monolithic artifact, we can build systems that are:

* Flexible—Decoupled services can be composed and rearranged to quickly deliver new functionality. The smaller the unit of code that one is working with, the less complicated it is to change the code and the less time it takes to test deploy the code.  
* Resilient—Decoupled services mean an application is no longer a single “ball of mud” where a degradation in one part of the application causes the whole appli- cation to fail. Failures can be localized to a small part of the application and contained before the entire application experiences an outage. This also enables the applications to degrade gracefully in case of an unrecoverable error.  
* Scalable—Decoupled services can easily be distributed horizontally across multi- ple servers, making it possible to scale the features/services appropriately. With a monolithic application where all the logic for the application is intertwined, the entire application needs to scale even if only a small part of the application is the bottleneck. Scaling on small services is localized and much more cost- effective.  

To this end, as we begin our discussion of microservices keep the following in mind:

__Small, Simple, and Decoupled Services = Scalable, Resilient, and Flexible Applications__

## 1.7 What exactly is the cloud?

The term “cloud” has become overused. Every software vendor has a cloud and every- one’s platform is cloud-enabled, but if you cut through the hype, three basic models exist in cloud-based computing. These are

* Infrastructure as a Service (IaaS)   
* Platform as a Service (PaaS)
* Software as a Service (SaaS)

To better understand these concepts, let’s map the everyday task of making a meal to the different models of cloud computing. When you want to eat a meal, you have four choices:

1. You can make the meal at home.
2. You can go to the grocery store and buy a meal pre-made that you heat up and serve.
3. You can get a meal delivered to your house.
4. You can get in the car and eat at restaurant.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%201.6.png">

The difference between these options is about who’s responsible for cooking these meals and where the meal is going to be cooked. In the on-premise model, eating a meal at home requires you to do all the work, using your own oven and ingredients already in the home. A store-bought meal is like using the Infrastructure as a Service (IaaS) model of computing. You’re using the store’s chef and oven to pre-bake the meal, but you’re still responsible for heating the meal and eating it at the house (and cleaning up the dishes afterward).

In a Platform as a Service (PaaS) model you still have responsibility for the meal, but you further rely on a vendor to take care of the core tasks associated with making a meal. For example, in a PaaS model, you supply the plates and furniture, but the res- taurant owner provides the oven, ingredients, and the chef to cook them. In the Soft- ware as a Service (SaaS) model, you go to a restaurant where all the food is prepared for you. You eat at the restaurant and then you pay for the meal when you’re done. you also have no dishes to prepare or wash.

The key items at play in each of these models are ones of control: who’s responsi- ble for maintaining the infrastructure and what are the technology choices available for building the application? In a IaaS model, the cloud vendor provides the basic infrastructure, but you’re accountable for selecting the technology and building the final solution. On the other end of the spectrum, with a SaaS model, you’re a passive consumer of the service provided by the vendor and have no input on the technology selection or any accountability to maintain the infrastructure for the application.

## 1.8 Why the cloud and microservices?

One of the core concepts of a microservice-based architecture is that each service is packaged and deployed as its own discrete and independent artifact. Service instances should be brought up quickly and each instance of the service should be indistin- guishable from another.

As a developer writing a microservice, sooner or later you’re going to have to decide whether your service is going to be deployed to one of the following:

* __Physical server__—While you can build and deploy your microservices to a physical machine(s), few organizations do this because physical servers are constrained. You can’t quickly ramp up the capacity of a physical server and it can become extremely costly to scale your microservice horizontally across multiple physical servers.
* __Virtual machine images__—One of the key benefits of microservices is their ability to quickly start up and shut down microservice instances in response to scalabil- ity and service failure events. Virtual machines are the heart and soul of the major cloud providers. A microservice can be packaged up in a virtual machine image and multiple instances of the service can then be quickly deployed and started in either a IaaS private or public cloud.
* __Virtual container__—Virtual containers are a natural extension of deploying your microservices on a virtual machine image. Rather than deploying a service to a full virtual machine, many developers deploy their services as Docker contain- ers (or equivalent container technology) to the cloud. Virtual containers run inside a virtual machine; using a virtual container, you can segregate a single vir- tual machine into a series of self-contained processes that share the same virtual machine image.

The advantage of cloud-based microservices centers around the concept of elasticity. Cloud service providers allow you to quickly spin up new virtual machines and contain- ers in a matter of minutes. If your capacity needs for your services drop, you can spin down virtual servers without incurring any additional costs. Using a cloud provider to deploy your microservices gives you significantly more horizontal scalability (adding more servers and service instances) for your applications. Server elasticity also means that your applications can be more resilient. If one of your microservices is having prob- lems and is falling over, spinning up new service instances can you keep your applica- tion alive long enough for your development team to gracefully resolve the issue.

## 1.9 Microservices are more than writing the code

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%201.7.png">

* Right-sized—How do you ensure that your microservices are properly sized so that you don’t have a microservice take on too much responsibility? Remember, properly sized, a service allows you to quickly make changes to an application and reduces the overall risk of an outage to the entire application.
* Location transparent—How you we manage the physical details of service invoca- tion when in a microservice application, multiple service instances can quickly start and shut down?
* Resilient—How do you protect your microservice consumers and the overall integrity of your application by routing around failing services and ensuring that you take a “fail-fast” approach?
* Repeatable—How do you ensure that every new instance of your service brought up is guaranteed to have the same configuration and code base as all the other service instances in production?
* Scalable—How do you use asynchronous processing and events to minimize the direct dependencies between your services and ensure that you can gracefully scale your microservices?

### 1.9.1 Core microservice development pattern

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%201.8.png">

### 1.9.2 Microservice routing patterns

The microservice routing patterns deal with how a client application that wants to consume a microservice discovers the location of the service and is routed over to it. In a cloud-based application, you might have hundreds of microservice instances run- ning. You’ll need to abstract away the physical IP address of these services and have a single point of entry for service calls so that you can consistently enforce security and content policies for all service calls.

Service discovery and routing answer the question, “How do I get my client’s request for a service to a specific instance of a service?”

* Service discovery : How do you make your microservice discoverable so client applications can find them without having the location of the service hard- coded into the application? How do you ensure that misbehaving microservice instances are removed from the pool of available service instances?
* Service routing—How do you provide a single entry point for all of your services so that security policies and routing rules are applied uniformly to multiple services and service instances in your microservice applications? How do you ensure that each developer in your team doesn’t have to come up with their own solutions for providing routing to their services? 

### 1.9.3 Microservice client resiliency patterns

* Client-side load balancing : How do you cache the location of your service instances on the service client so that calls to multiple instances of a microser- vice are load balanced to all the health instances of that microservice?
* Circuit breakers pattern : How do you prevent a client from continuing to call a service that’s failing or suffering performance problems? When a service is run- ning slowly, it consumes resources on the client calling it. You want failing microservice calls to fail fast so that the calling client can quickly respond and take an appropriate action.
* Fallback pattern : When a service call fails, how do you provide a “plug-in” mech- anism that will allow the service client to try to carry out its work through alter- native means other than the microservice being called?
* Bulkhead pattern : Microservice applications use multiple distributed resources to carry out their work. How do you compartmentalize these calls so that the mis- behavior of one service call doesn’t negatively impact the rest of the application?

### 1.9.4 Microservice security patterns

* Authentication—How do you determine the service client calling the service is who they say they are?
* Authorization—How do you determine whether the service client calling a microservice is allowed to undertake the action they’re trying to undertake?
* Credential management and propagation—How do you prevent a service client from constantly having to present their credentials for service calls involved in a trans- action? Specifically, we’ll look at how token-based security standards such as OAuth2 and JavaScript Web Tokens (JWT) can be used to obtain a token that can be passed from service call to service call to authenticate and authorize the user.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%201.9.png">

### 1.9.5 Microservice logging and tracing patterns

The beauty of the microservice architecture is that a monolithic application is broken down into small pieces of functionality that can be deployed independently of one another. The downside of a microservice architecture is that it’s much more difficult to debug and trace what the heck is going on within your application and services.

* Log correlation—How do you tie together all the logs produced between services for a single user transaction? With this pattern, we’ll look at how to implement a correlation ID, which is a unique identifier that will be carried across all service calls in a transaction and can be used to tie together log entries produced from each service.  
* Log aggregation—With this pattern we’ll look at how to pull together all of the logs produced by your microservices (and their individual instances) into a sin- gle queryable database. We’ll also look at how to use correlation IDs to assist in searching your aggregated logs.  
* Microservice tracing—Finally, we’ll explore how to visualize the flow of a client transaction across all the services involved and understand the performance characteristics of services involved in the transaction.  

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%201.12.png">

### 1.9.6 Microservice build/deployment patterns

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%201.13.png">

## 1.10 Using Spring Cloud in building your microservices

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%201.14.png">

## 1.13 Summary

* Microservices are extremely small pieces of functionality that are responsible for one specific area of scope.   
* No industry standards exist for microservices. Unlike other early web service protocols, microservices take a principle-based approach and align with the concepts of REST and JSON.   
* Writing microservices is easy, but fully operationalizing them for production requires additional forethought. We introduced several categories of microser- vice development patterns, including core development, routing patterns, cli- ent resiliency, security, logging, and build/deployment patterns.    
* While microservices are language-agnostic, we introduced two Spring frame- works that significantly help in building microservices: Spring Boot and Spring Cloud.  
* Spring Boot is used to simplify the building of REST-based/JSON microservices. Its goal is to make it possible for you to build microservices quickly with nothing more than a few annotations.  
* Spring Cloud is a collection of open source technologies from companies such as Netflix and HashiCorp that have been “wrapped” with Spring annotations to significantly simplify the setup and configuration of these services.  

