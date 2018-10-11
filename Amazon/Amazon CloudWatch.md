Amazon CloudWatch allows developers, system architects, and administrators to monitor their AWS applications in the cloud, in near-real-time. CloudWatch is automatically configured to provide metrics on request counts, latency, and CPU usage. Users also can send their own logs and custom metrics to CloudWatch for monitoring.

The data and reports CloudWatch provides lets users keep track of application performance, resource use, operational issues, and constraints. This helps organizations resolve technical issues and streamline operations.

CloudWatch is most commonly used with Elastic Compute Cloud (EC2) instances, and can also monitor Amazon Elastic Block Store (EBS) volumes, Elastic Load Balancers (ELBs), and instances of Amazon Relational Database Service (RDS). It also can extend beyond these core services to intake custom data from external sources.

Users choose CloudWatch for its automatic integration with AWS services, its flexibility, and its ability to scale quickly.

### Monitoring AWS Resources With CloudWatch

Amazon CloudWatch is configured out-of-the-box to integrate with EC2, offering two levels of monitoring capabilities:

* Basic monitoring, which requires no additional fee, includes seven pre-selected metrics and three status-check metrics, produced at five-minute and one-minute intervals, respectively.  
* Detailed monitoring, which comes at an additional charge, increases the frequency of all metrics to one-minute intervals.  

Additional AWS services that CloudWatch can monitor automatically include the following:

* EBS: Monitors read/write latency and similar measurements.  
* RDS database instances: Monitors metrics such as storage space and freeable memory.  
* SQS Queues: Monitors messages sent, messages received, and other key metrics.  
* SNS Topics: Monitors common metrics like number of published and delivered messages.  
