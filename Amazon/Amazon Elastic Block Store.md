https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/AmazonEBS.html. 

__Amazon Elastic Block Store (EBS)__ provides raw block-level storage that can be attached to Amazon EC2 instances and is used in Amazon Relational Database Service (RDS). These block devices can then be used like any raw block device. In a typical use case, this would include formatting the device with a filesystem and mounting said filesystem. In addition EBS supports a number of advanced storage features, including snapshotting and cloning. As of June 2014, EBS volumes can be up to 1TB in size. EBS volumes are built on replicated back end storage, so that the failure of a single component will not cause data loss.

The EBS product was introduced to the general public by Amazon in August 2008 and as of March 2018 30 GB of free space is included in the free tier of Amazon Web Services at least since 2017.

Amazon EBS provides a range of options for storage performance and cost for workload. These options are divided into two major categories: SSD-backed storage for transactional workloads, such as databases and boot volumes (performance depends primarily on IOPS), and HDD-backed storage for throughput intensive workloads, such as MapReduce and log processing (performance depends primarily on MB/s). 

