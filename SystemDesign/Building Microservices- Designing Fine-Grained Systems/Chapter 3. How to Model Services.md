### What Makes a Good Service?

What makes a good service? If you’ve survived a failed SOA implementation, you may have some idea where I’m going next. But just in case you aren’t that (un)fortunate, I want you to focus on two key concepts: loose coupling and high cohesion. 

##### Loose Coupling

When services are loosely coupled, a change to one service should not require a change to another. The whole point of a microservice is being able to make a change to one service and deploy it, without needing to change any other part of the system. This is really quite important.

What sort of things cause tight coupling? A classic mistake is to pick an integration style that tightly binds one service to another, causing changes inside the service to require a change to consumers. 

A loosely coupled service knows as little as it needs to about the services with which it collaborates. This also means we probably want to limit the number of different types of calls from one service to another, because beyond the potential performance problem, chatty communication can lead to tight coupling.

##### High Cohesion

We want related behavior to sit together, and unrelated behavior to sit elsewhere. Why? Well, if we want to change behavior, we want to be able to change it in one place, and release that change as soon as possible. If we have to change that behavior in lots of different places, we’ll have to release lots of different services (perhaps at the same time) to deliver that change. Making changes in lots of different places is slower, and deploying lots of services at once is risky—both of which we want to avoid.

So we want to find boundaries within our problem domain that help ensure that related behavior is in one place, and that communicate with other boundaries as loosely as possible.

### The Bounded Context

Eric Evans’s book Domain-Driven Design (Addison-Wesley) focuses on how to create systems that model real-world domains. The book is full of great ideas like using ubiquitous language, repository abstractions, and the like, but there is one very important concept Evans introduces that completely passed me by at first: bounded context. The idea is that any given domain consists of multiple bounded contexts, and residing within each are things (Eric uses the word model a lot, which is probably better than things) that do not need to be communicated outside as well as things that are shared externally with other bounded contexts. Each bounded context has an explicit interface, where it decides what models to share with other contexts.

Another definition of bounded contexts I like is “a specific responsibility enforced by explicit boundaries.”1 If you want information from a bounded context, or want to make requests of functionality within a bounded context, you communicate with its explicit boundary using models. “In his book, Evans uses the analogy of cells, where “[c]ells can exist because their membranes define what is in and out and determine what can pass.”



Excerpt From: Sam Newman. “Building Microservices.” iBooks. 
