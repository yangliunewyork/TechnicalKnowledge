__Amazon Elastic Compute Cloud (EC2)__ forms a central part of Amazon.com's cloud-computing platform, Amazon Web Services (AWS), by allowing users to rent virtual computers on which to run their own computer applications. EC2 encourages scalable deployment of applications by providing a web service through which a user can boot an Amazon Machine Image (AMI) to configure a virtual machine, which Amazon calls an "instance", containing any software desired. A user can create, launch, and terminate server-instances as needed, paying by the second for active servers – hence the term "elastic". EC2 provides users with control over the geographical location of instances that allows for latency optimization and high levels of redundancy.

In November 2010, Amazon switched its own retail website to use EC2 and AWS.  

# Features

#### Elastic IP addresses

Amazon's elastic IP address feature is similar to static IP address in traditional data centers, with one key difference. A user can programmatically map an elastic IP address to any virtual machine instance without a network administrator's help and without having to wait for DNS to propagate the binding. In this sense an Elastic IP Address belongs to the account and not to a virtual machine instance. It exists until it is explicitly removed, and remains associated with the account even while it is associated with no instance.

#### Automated scaling

Amazon's auto-scaling feature of EC2 allows it to automatically adapt computing capacity to site traffic. The schedule-based (e.g. time-of-the-day) and rule-based (e.g. CPU utilization thresholds) auto scaling mechanisms are easy to use and efficient for simple applications. However, one potential problem is that VMs may take up to several minutes to be ready to use, which are not suitable for time critical applications. The VM startup time are dependent on image size, VM type, data center locations, etc.

### Is Amazon EC2 IaaS or PaaS?

AWS Elastic Compute Service or EC2 is IaaS(Infrastructure as a Service). This is because Amazon takes the responsibility of networking, storage, server and virtualization and the user is responsible for managing the Operating System, middleware, runtime, data and application. In PaaS aka Platform as a Service the user only needs to take care of data and application, the management of rest of the layers lies in hands of the service provider. AWS Elastic BeanStalk is PaaS.


### Amazon Machine Image

An Amazon Machine Image (AMI) is a special type of virtual appliance that is used to create a virtual machine within the Amazon Elastic Compute Cloud ("EC2"). It serves as the basic unit of deployment for services delivered using EC2.

