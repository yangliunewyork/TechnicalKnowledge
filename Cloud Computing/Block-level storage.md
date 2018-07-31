__Block-level storage__ is a concept in cloud-hosted data persistence where cloud services emulate the behaviour of a traditional block device, such as a physical hard drive.[1] It is a form of Network Attached Storage (NAS).

Storage in such is organised as blocks. This emulates the type of behaviour seen in traditional disk or tape storage. Blocks are identified by an arbitrary and assigned identifier by which they may be stored and retrieved, but this has no obvious meaning in terms of files or documents. A filesystem must be applied on top of the block-level storage to map 'files' onto a sequence of blocks.

Amazon EBS (Elastic Block Store) is an example of a cloud block store. Cloud block-level storage will usually offer facilities such as replication for reliability, or backup services.

Block-level storage is in contrast to an object store or 'bucket store', such as Amazon S3 (Simple Storage Service), or to a database. These operate at a higher level of abstraction and are able to work with entities such as files, documents, images, videos or database records.[5]

Instance stores are another form of cloud-hosted block-level storage. These are provided as part of an 'instance', such as an Amazon EC2 (Elastic Compute Cloud) service.[6] As EC2 instances are primarily provided as compute resources, rather than storage resources, their storage is less robust. Their contents will be lost if the cloud instance is stopped. As these stores are part of the instance's virtual server they offer higher performance and bandwidth to the instance. They are best used for temporary storage such as caching or temporary files, with persistent storage held on a different type of server.

At one time, block-level storage was provided by Storage Area Networks (SAN) and NAS provided file-level storage. [8] With the shift from on-premises hosting to cloud services, this distinction has shifted.[2] Even block-storage is now seen as distinct servers (thus NAS), rather than the previous array of bare discs. 

### Amazon Elastic Block Store

Amazon Elastic Block Store (EBS) provides raw block-level storage that can be attached to Amazon EC2 instances. These block devices can then be used like any raw block device. In a typical use case, this would include formatting the device with a filesystem and mounting said filesystem. In addition EBS supports a number of advanced storage features, including snapshotting and cloning. As of June 2014, EBS volumes can be up to 1TB in size. EBS volumes are built on replicated back end storage, so that the failure of a single component will not cause data loss.

The EBS product was introduced to the general public by Amazon in August 2008 and as of March 2018 30 GB of free space is included in the free tier of Amazon Web Services at least since 2017.

Amazon EBS provides a range of options for storage performance and cost for workload. These options are divided into two major categories: SSD-backed storage for transactional workloads, such as databases and boot volumes (performance depends primarily on IOPS), and HDD-backed storage for throughput intensive workloads, such as MapReduce and log processing (performance depends primarily on MB/s). 
