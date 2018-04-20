At one point or another, a developer will be forced to separate configuration infor- mation from their code. After all, it has been drilled into their heads since school that they shouldn’t hard-code values into the application code. Many developers will use a constants class file in their application to help centralize all their configu- ration in one place. Application configuration data written directly into the code is often problematic because every time a change to the configuration has to be made the application has to be recompiled and/or redeployed. To avoid this, developers will separate the configuration information from the application code completely. This makes it easy to make changes to configuration without going through a recompile process, but also introduces complexity because you now have another artifact that needs to be managed and deployed with the application.

Many developers will turn to the lowly property file (or YAML, JSON, or XML) to store their configuration information. This property file will sit out on a server often containing database and middleware connection information and metadata about the application that will drive the application’s behavior. Segregating your application into a property file is easy and most developers never do any more operationalization of their application configuration then placing their configuration file under source control (if that) and deploying it as part of their application.

This approach might work with a small number of applications, but it quickly falls apart when dealing with cloud-based applications that may contain hundreds of microservices, where each microservice in turn might have multiple service instances running.

Suddenly configuration management becomes a big deal as application and opera- tions team in a cloud-based environment have to wrestle with a rat’s nest of which configuration files go where. Cloud-based microservices development emphasizes

* Completely separating the configuration of an application from the actual code being deployed.  
* Building the server and the application and an immutable image that never changes as it’s promoted through your environments.  
* Injecting any application configuration information at startup time of the server through either environment variables or through a centralized reposi- tory the application’s microservices read on startup.  

## 3.1 On managing configuration (and complexity)
