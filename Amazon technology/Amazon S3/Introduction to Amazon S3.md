### Object storage

__Object storage (also known as object-based storage)__ is a computer data storage architecture that manages data as objects, as opposed to other storage architectures like file systems which manage data as a file hierarchy, and block storage which manages data as blocks within sectors and tracks.[2] Each object typically includes the data itself, a variable amount of metadata, and a globally unique identifier. Object storage can be implemented at multiple levels, including the device level (object-storage device), the system level, and the interface level. In each case, object storage seeks to enable capabilities not addressed by other storage architectures, like interfaces that can be directly programmable by the application, a namespace that can span multiple instances of physical hardware, and data-management functions like data replication and data distribution at object-level granularity.

Object-storage systems allow retention of massive amounts of unstructured data. Object storage is used for purposes such as storing photos on Facebook, songs on Spotify, or files in online collaboration services, such as Dropbox.

# Introduction to Amazon S3

__Amazon S3 (Simple Storage Service)__ is a cloud computing web service offered by Amazon Web Services (AWS). Amazon S3 provides __object storage__ through web services interfaces (REST, SOAP, and BitTorrent).

Amazon says that S3 uses the same scalable storage infrastructure that Amazon.com uses to run its own global e-commerce network.

### Design

Amazon does not make details of S3's design public, though it clearly manages data with an object-storage architecture. According to Amazon, S3's design aims to provide scalability, high availability, and low latency at commodity costs.

S3 is designed to provide between 99.999999999% durability and 99.99%-99,95% availability of objects over a given depending on which Amazon S3 Storage classes is used,[15] though there is no service-level agreement for durability.

Amazon S3 basic storage unit is an objects which are organized into buckets (each owned by an Amazon Web Services account), and identified within each bucket by a unique, user-assigned key. Amazon Machine Images (AMIs) which are used in the Elastic Compute Cloud (EC2) can be exported to S3 as bundles.

Buckets and objects can be created, listed, and retrieved using either a REST-style HTTP interface or a SOAP interface. Additionally, objects can be downloaded using the HTTP GET interface and the BitTorrent protocol.

S3 stores arbitrary objects, for example computer files, up to 5 terabytes in size since 2011[17], each accompanied by up to 2 kilobytes of metadata.

Requests are authorized using an access control list associated with each bucket and object and support versioning, disabled by default, and lifecycle management of objects.

#### Advantages to Amazon S3

Amazon S3 is intentionally built with a minimal feature set that focuses on simplicity and robustness. Following are some of advantages of the Amazon S3 service:

* Create Buckets – Create and name a bucket that stores data. Buckets are the fundamental container in Amazon S3 for data storage.  
* Store data in Buckets – Store an infinite amount of data in a bucket. Upload as many objects as you like into an Amazon S3 bucket.  Each object can contain up to 5 TB of data. Each object is stored and retrieved using a unique developer-assigned key.  
* Download data – Download your data or enable others to do so. Download your data any time you like or allow others to do the same.  
* Permissions – Grant or deny access to others who want to upload or download data into your Amazon S3 bucket. Grant upload and download permissions to three types of users. Authentication mechanisms can help keep data secure from unauthorized access.  
* Standard interfaces – Use standards-based REST and SOAP interfaces designed to work with any Internet-development toolkit.  

#  Amazon S3 Concepts

