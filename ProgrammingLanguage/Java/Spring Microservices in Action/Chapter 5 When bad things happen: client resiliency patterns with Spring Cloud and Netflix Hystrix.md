What’s insidious about problems caused by poorly performing remote services is that they’re not only difficult to detect, but can trigger a cascading effect that can ripple throughout an entire application ecosystem. Without safeguards in place, a single poorly performing service can quickly take down multiple applications. Cloud-based, microservice-based applications are particularly vulnerable to these types of outages because these applications are composed of a large number of fine-grained, distrib- uted services with different pieces of infrastructure involved in completing a user’s transaction.

## 5.1 What are client-side resiliency patterns?

Client resiliency software patterns are focused on protecting a remote resource’s (another microservice call or database lookup) client from crashing when the remote resource is failing because that remote service is throwing errors or performing poorly. The goal of these patterns is to allow the client to “fail fast,” not consume valu- able resources such as database connections and thread pools, and prevent the prob- lem of the remote service from spreading “upstream” to consumers of the client.

There are four client resiliency patterns:

1. Client-side load balancing  
2. Circuit breakers  
3. Fallbacks  
4. Bulkheads  

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%205.1.png">

Figure 5.1 demonstrates how these patterns sit between the microservice service con- sumer and the microservice.

These patterns are implemented in the client calling the remote resource. The implementation of these patterns logically sit between the client consuming the remote resources and the resource itself.

### 5.1.1 Client-side load balancing

Client-side load balancing involves having the client look up all of a service’s individual instances from a service discovery agent (like Netflix Eureka) and then caching the physical location of said service instances.Whenever a service consumer needs to call that service instance, the client-side load balancer will return a location from the pool of service locations it’s maintaining.

Because the client-side load balancer sits between the service client and the service consumer, the load balancer can detect if a service instance is throwing errors or behaving poorly. If the client-side load balancer detects a problem, it can remove that service instance from the pool of available service locations and prevent any future service calls from hitting that service instance.

This is exactly the behavior that Netflix’s Ribbon libraries provide out of the box with no extra configuration.

### 5.1.2 Circuit breaker

The circuit breaker pattern is a client resiliency pattern that’s modeled after an elec- trical circuit breaker. In an electrical system, a circuit breaker will detect if too much current is flowing through the wire. If the circuit breaker detects a problem, it will break the connection with the rest of the electrical system and keep the downstream components from the being fried.

With a software circuit breaker, when a remote service is called, the circuit breaker will monitor the call. If the calls take too long, the circuit breaker will intercede and kill the call. In addition, the circuit breaker will monitor all calls to a remote resource and if enough calls fail, the circuit break implementation will pop, failing fast and pre- venting future calls to the failing remote resource.

### 5.1.3 Fallback processing

With the fallback pattern, when a remote service call fails, rather than generating an exception, the service consumer will execute an alternative code path and try to carry out an action through another means. This usually involves looking for data from another data source or queueing the user’s request for future processing. The user’s call will not be shown an exception indicating a problem, but they may be notified that their request will have to be fulfilled at a later date.

For instance, suppose you have an e-commerce site that monitors your user’s behavior and tries to give them recommendations of other items they could buy. Typi- cally, you might call a microservice to run an analysis of the user’s past behavior and return a list of recommendations tailored to that specific user. However, if the prefer- ence service fails, your fallback might be to retrieve a more general list of preferences that’s based off all user purchases and is much more generalized. This data might come from a completely different service and data source.

### 5.1.4 Bulkheads

The bulkhead pattern is based on a concept from building ships. With a bulkhead design, a ship is divided into completely segregated and watertight compartments called bulkheads. Even if the ship’s hull is punctured, because the ship is divided into watertight compartments (bulkheads), the bulkhead will keep the water confined to the area of the ship where the puncture occurred and prevent the entire ship from filling with water and sinking.

The same concept can be applied to a service that must interact with multiple remote resources. By using the bulkhead pattern, you can break the calls to remote resources into their own thread pools and reduce the risk that a problem with one slow remote resource call will take down the entire application. The thread pools act as the bulkheads for your service. Each remote resource is segregated and assigned to the thread pool. If one service is responding slowly, the thread pool for that one type of service call will become saturated and stop processing requests. Service calls to other services won’t become saturated because they’re assigned to other thread pools.

## 5.2 Why client resiliency matters

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%205.2.png">

Over the weekend, a network administrator made what they thought was a small tweak to the configuration on the NAS, as shown in bold in figure 5.2. This change appears to work fine, but on Monday morning, any reads to a particular disk subsys- tem start performing extremely slowly.

The developer who wrote Service B never anticipated slowdowns occurring with calls to Service C. They wrote their code so that the writes to their database and the reads from the service occur within the same transaction. When Service C starts run- ning slowly, not only does the thread pool for requests to Service C start backing up, the number of database connections in the service container’s connection pools become exhausted because these connections are being held open because the calls out to Service C never complete.

Finally, Service A starts running out of resources because it’s calling Service B, which is running slow because of Service C. Eventually, all three applications stop responding because they run out of resources while waiting for requests to complete.

A circuit breaker acts as a middle man between the application and the remote ser- vice. In the previous scenario, a circuit breaker implementation could have protected Applications A, B, and C from completely crashing.

In figure 5.3, the Service B (the client) is never going to directly invoke Service C. Instead, when the call is made, Service B is going to delegate the actual invocation of the service to the circuit breaker, which will take the call and wrap it in a thread (usu- ally managed by a thread pool) that’s independent of the originating caller. By wrap- ping the call in a thread, the client is no longer directly waiting for the call to complete. Instead, the circuit breaker is monitoring the thread and can kill the call if the thread runs too long.

Three scenarios are shown in figure 5.3. In the first scenario, the happy path, the circuit breaker will maintain a timer and if the call to the remote service completes before the timer runs out, everything is good and Service B can continue its work. In the partial degradation scenario, Service B will call Service C through the circuit breaker. This time, though, Service C is running slow and the circuit breaker will kill the connection out to the remote service if it doesn’t complete before the timer on the thread maintained by the circuit breaker times out.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%205.3.png">

Service B will then get an error from making the call, but Service B won’t have resources (that is, its own thread or connection pools) tied up waiting for Service C to complete. If the call to Service C is timed-out by the circuit breaker, the circuit breaker will start tracking the number of failures that have occurred.

If enough errors on the service have occurred within a certain time period, the circuit breaker will now “trip” the circuit and all calls to Service C will fail without calling Service C.

This tripping of the circuit allows three things to occur:

1. Service B now immediately knows there’s a problem without having to wait for a timeout from the circuit breaker.  
2. Service B can now choose to either completely fail or take action using an alter- native set of code (a fallback).  
3. Service C will be given an opportunity to recover because Service B isn’t calling it while the circuit breaker has been tripped. This allows Service C to have breathing room and helps prevent the cascading death that occurs when a service degradation occurs.  

Finally, the circuit breaker will occasionally let calls through to a degraded service, and if those calls succeed enough times in a row, the circuit breaker will reset itself.

The key thing a circuit break patterns offers is the ability for remote calls to:

1. Fail fast—When a remote service is experiencing a degradation, the application will fail fast and prevent resource exhaustion issues that normally shut down the entire application. In most outage situations, it’s better to be partially down rather than completely down.  
2. Fail gracefully—By timing out and failing fast, the circuit breaker pattern gives the application developer the ability to fail gracefully or seek alternative mecha- nisms to carry out the user’s intent. For instance, if a user is trying to retrieve data from one data source, and that data source is experiencing a service degra- dation, then the application developer could try to retrieve that data from another location.  
3. Recover seamlessly—With the circuit-breaker pattern acting as an intermediary, the circuit breaker can periodically check to see if the resource being requested is back on line and re-enable access to it without human intervention.  

In a large cloud-based application with hundreds of services, this graceful recovery is critical because it can significantly cut down on the amount of time needed to restore service and significantly lessen the risk of a tired operator or application engineer causing greater problems by having them intervene directly (restarting a failed ser- vice) in the restoration of the service.  

