Function as a service (FaaS) is a category of cloud computing services that provides a platform allowing customers to develop, run, and manage application functionalities without the complexity of building and maintaining the infrastructure typically associated with developing and launching an app. Building an application following this model is one way of achieving a "serverless" architecture, and is typically used when building microservices applications.

FaaS is an extremely recent development in cloud computing, first made available to the world by hook.io in October 2014,[2] followed by AWS Lambda, Google Cloud Functions, Microsoft Azure Functions, IBM/Apache's OpenWhisk (open source) in 2016 and Oracle Cloud Fn (open source) in 2017 which are available for public use. FaaS capabilities also exist in private platforms, as demonstrated by Uber's Schemaless triggers.

### Comparison with PaaS application hosting services

Serverless computing architectures in which the customer has no direct need to manage resources can also be achieved using Platform as a Service services. These services are, however, typically very different in their implementation architecture, which has some implications for scaling. In most PaaS systems, the system continually runs at least one server process and, even with auto scaling, a number of longer running processes are simply added or removed on the same machine. This means that scalability is a more visible problem to the developer.

In a FaaS system, the functions are expected to start within milliseconds in order to allow handling of individual requests. In a PaaS system, by contrast, there is typically an application thread which keeps running for a long period of time and handles multiple requests. This difference is primarily visible in the pricing, where FaaS services charge per execution time of the function whereas PaaS services charge per running time of the thread in which the server application is running. 

### Use Cases

Use cases for FaaS are associated with "on-demand" functionality that enables the supporting infrastructure to be powered down and not incurring charges when not in use. Examples include data processing (e.g., batch processing, stream processing, ETL), IoT services for Internet-connected devices, mobile applications, and web applications.[
