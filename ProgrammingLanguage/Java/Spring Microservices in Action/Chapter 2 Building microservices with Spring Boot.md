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


