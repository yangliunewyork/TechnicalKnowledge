Amazon S3 (Simple Storage Service) is a cloud computing web service offered by Amazon Web Services (AWS). Amazon S3 provides object storage through web services interfaces (REST, SOAP, and BitTorrent). Amazon launched S3 as its fifth publicly-available web service in March 2006, then in Europe in November 2007.

Amazon says that S3 uses the same scalable storage infrastructure that Amazon.com uses to run its own global e-commerce network.

Amazon S3 is reported to store more than 2 trillion objects as of April 2013. S3 uses include web hosting, image hosting, and storage for backup systems. S3 guarantees 99.9% monthly up-time service-level agreement (SLA); that is, not more than 43 minutes of downtime per month.

Amazon S3 is one of the earliest and key drivers (along with EC2) of AWS, the most profitable division under the entire Amazon company.

### Design

Amazon does not make details of S3's design public, though it manages data with an object-storage architecture.According to Amazon, S3's design aims to provide scalability, high availability, and low latency at commodity costs.

S3 is designed to provide 99.9% durability and between 99.99%–99.95% availability of objects over a given year depending on which Amazon S3 Storage classes are used,[12] though there is no service-level agreement for durability.

The basic storage units of Amazon S3 are objects which are organized into buckets (each owned by an Amazon Web Services account) and identified within each bucket by a unique, user-assigned key. Amazon Machine Images (AMIs) which are used in the Elastic Compute Cloud (EC2) can be exported to S3 as bundles.[13]

Buckets and objects can be created, listed, and retrieved using either a REST-style HTTP interface or a SOAP interface, but new Amazon S3 features will not be supported for SOAP, Amazon recommends using either the REST API or the AWS SDKs.

```
https://docs.aws.amazon.com/AmazonS3/latest/API/ErrorResponses.html
```

Additionally, objects can be downloaded using the HTTP GET interface and the BitTorrent protocol.

S3 stores arbitrary objects, for example computer files, up to 5 terabytes in size since 2011, each accompanied by up to 2 kilobytes of metadata.

Requests are authorized using an access control list associated with each bucket and object and support versioning, disabled by default, and lifecycle management of objects.

Bucket names and keys are chosen so that objects are addressable using HTTP URLs:

```
http://s3.amazonaws.com/bucket/key 
http://bucket.s3.amazonaws.com/key
http://bucket/key (where bucket is a DNS CNAME record pointing to bucket.s3.amazonaws.com)
```

Because objects are accessible by unmodified HTTP clients, S3 can be used to replace significant existing (static) web-hosting infrastructure.The Amazon AWS Authentication mechanism allows the bucket owner to create an authenticated URL with time-bounded validity. That is, someone can construct a URL that can be handed off to a third-party for access for a period such as 30 minutes, or 24 hours.

Every item in a bucket can also be served as a BitTorrent feed. The S3 store can act as a seed host for a torrent and any BitTorrent client can retrieve the file. This drastically reduces the bandwidth costs for the download of popular objects. While the use of BitTorrent does reduce bandwidth, AWS does not provide native bandwidth limiting and, as such, users have no access to automated cost control. This can lead to users on the "free-tier" S3 or small hobby users amassing dramatic bills. AWS representatives have previously stated that such a feature was on the design table from 2006 to 2010,[18] but in 2011 stated the feature is no longer in development.

A bucket can be configured to save HTTP log information to a sibling bucket; this can be used in later data mining operations.

### Amazon S3 Storage Classes

Amazon S3 offers four different storage classes designed for different use case depending on durability, availability and performance requirements.[21] Amazon S3 Standard and Reduced Redundancy Storage (RRS),[22] Amazon S3 Standard Infrequent Access (IA), Amazon S3 One Zone Infrequent Access and Amazon Glacier which is designed for data archiving.

* Amazon S3 Standard is the default class.  
* Amazon S3 Standard Infrequent Access (IA) is used for less frequently accessed data. Typical use cases are backups and disaster recovery solutions. Costs are lower than the Amazon S3 Standard, but applies additional fees per gigabyte of data retrieved.  
* Amazon S3 Reduced Redundancy Storage (RRS) is designed for noncritical, reproducible data at lower levels of redundancy. It reduces the costs of storing data in a less fault-tolerance manner. It supports one facility fault instead of two, unlike the Amazon S3 Standard.[23] Typical use cases can be data that could be recreated in the case of data loss. Durability is claimed to be 99.99% in comparison with 99.999999999% of standard class.  
* Amazon Glacier is designed for long-term storage of data that is infrequently accessed and for which retrieval latency of minutes or hours are acceptable. Use cases for this may be as a status service, where other servers may not need to be checked so frequently.  

