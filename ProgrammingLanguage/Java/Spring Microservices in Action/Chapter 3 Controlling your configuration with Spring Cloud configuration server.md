At one point or another, a developer will be forced to separate configuration infor- mation from their code. After all, it has been drilled into their heads since school that they shouldn’t hard-code values into the application code. Many developers will use a constants class file in their application to help centralize all their configu- ration in one place. Application configuration data written directly into the code is often problematic because every time a change to the configuration has to be made the application has to be recompiled and/or redeployed. To avoid this, developers will separate the configuration information from the application code completely. This makes it easy to make changes to configuration without going through a recompile process, but also introduces complexity because you now have another artifact that needs to be managed and deployed with the application.

Many developers will turn to the lowly property file (or YAML, JSON, or XML) to store their configuration information. This property file will sit out on a server often containing database and middleware connection information and metadata about the application that will drive the application’s behavior. Segregating your application into a property file is easy and most developers never do any more operationalization of their application configuration then placing their configuration file under source control (if that) and deploying it as part of their application.

This approach might work with a small number of applications, but it quickly falls apart when dealing with cloud-based applications that may contain hundreds of microservices, where each microservice in turn might have multiple service instances running.

Suddenly configuration management becomes a big deal as application and opera- tions team in a cloud-based environment have to wrestle with a rat’s nest of which configuration files go where. Cloud-based microservices development emphasizes

* Completely separating the configuration of an application from the actual code being deployed.  
* Building the server and the application and an immutable image that never changes as it’s promoted through your environments.  
* Injecting any application configuration information at startup time of the server through either environment variables or through a centralized reposi- tory the application’s microservices read on startup.  

## 3.1 On managing configuration (and complexity)

Managing application configuration is critical for microservices running in the cloud because microservice instances need to be launched quickly with minimal human intervention. Every time a human being needs to manually configure or touch a ser- vice to get it deployed is an opportunity for configuration drift, an unexpected outage and a lag-time in responding to scalability challenges with the application.

Let’s begin our discussion about application configuration management by estab- lishing four principles we want to follow:

* __Segregate__ : We want to completely separate the services configuration information from the actual physical deployment of a service. Application configuration shouldn’t be deployed with the service instance. Instead, configuration information should either be passed to the starting service as environment variables or read from a centralized repository when the service starts.
* __Abstract__ : Abstract the access of the configuration data behind a service interface. Rather than writing code that directly accesses the service repository (that is, read the data out of a file or a database using JDBC), have the application use a REST-based JSON service to retrieve the configuration data. 
* __Centralize__ : Because a cloud-based application might literally have hundreds of services, it’s critical to minimize the number of different repositories used to hold configuration information. Centralize your application configuration into as few repositories as possible.
* __Harden__ : Because your application configuration information is going to be completely segregated from your deployed service and centralized, it’s critical that whatever solution you utilize can be implemented to be highly available and redundant.

One of the key things to remember is that when you separate your configuration information outside of your actual code, you’re creating an external dependency that will need to be managed and version controlled. I can’t emphasize enough that the application configuration data needs to be tracked and version-controlled because mismanaged application configuration is a fertile breeding ground for difficult-to- detect bugs and unplanned outages.

### 3.1.1 Your configuration management architecture

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%203.1.png">

In figure 3.2, you see several activities taking place:

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Figure%203.2.png">

1. When a microservice instance comes up, it’s going to call a service endpoint to read its configuration information that’s specific to the environment it’s operat- ing in. The connection information for the configuration management (con- nection credentials, service endpoint, and so on) will be passed into the microservice when it starts up.  
2. The actual configuration will reside in a repository. Based on the implementation of your configuration repository, you can choose to use different implementa- tions to hold your configuration data. The implementation choices can include files under source control, a relational database, or a key-value data store.  
3. The actual management of the application configuration data occurs independently of how the application is deployed. Changes to configuration manage- ment are typically handled through the build and deployment pipeline where changes of the configuration can be tagged with version information and deployed through the different environments.  
4. When a configuration management change is made, the services that use that application configuration data must be notified of the change and refresh their copy of the application data.  

### 3.1.2 Implementation choices

Fortunately, you can choose among a large number of battle-tested open source proj- ects to implement a configuration management solution.

<img src="https://github.com/Lelouch-Lamperouge-Code-Geass/TechnicalKnowledge/blob/master/ProgrammingLanguage/Java/Spring%20Microservices%20in%20Action/Photos/Table%203.1.png">

