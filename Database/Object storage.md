
# History

The most common enterprise data storage models are ‘block storage’ and ‘file storage’. Block storage became increasingly popular in the mid-1990s, as computers in the data center moved from each using its own directly-attached storage device, to sharing a single large storage device or ‘array’. This more flexible and efficient approach creates a ‘storage area network’ or SAN.

File storage, utilizes a metaphor from the traditional paper-based office—representing data as files (such as documents, presentations and spreadsheets), arranged in a series of nested folders.

##### The 3 Pillars of Modern Enterprise Data Storage  

<img src="https://www.emc.com/content/dam/uwaem/production-design-assets/en/sdsaemmodule/images/ecs-object-storage-the-3-pillars-of-modern-enterprise-data-storage.gif">

##### The Need For a New Storage Alternative

While both block and file storage have many advantages, they both face challenges with the changing nature and explosive growth of data. More and more data created today is ‘unstructured’—individual items of information. This kind of data is not organized in a ‘structured’ database, so block storage is not suited for it.

Some of the unstructured data growth is in terms of files and documents—so file storage can be used. However, the sheer volume of data is beyond what most file systems were designed to handle. The hierarchical nature of file storage becomes ever more complex to sustain and manage as the amount of data grows.

In the late 1990s, a new kind of storage was developed to address these emerging challenges—‘object storage’. In this storage architecture, data items are not stored in blocks, files or folders, but rather in flexibly sized containers called ‘objects’. Placing data items in object storage is quick and easy—like putting items in a bucket. This analogy has led to 'bucket' becoming the generic term for a volume of object storage.

##### The Competitive Advantage—Why You Should Care About Object Storage

Large enterprises have been early adopters of object architectures and have used it to gain a competitive advantage in their industries. With the latest generation of object storage solutions, companies of all sizes can now realize these advantages. Many organizations initially deploy object architecture because of the huge cost savings realized by tiering warm and cold file data to object storage for long-term retention. At the same time, object storage supports new workloads like modern application development. Ultimately customers are leveraging object storage to analyze their data and gain insights about customers. A good example is how Uber disrupted the taxi industry with cloud technology and analytics. The bottom line is that object storage enables cloud technologies that businesses will leverage to gain real competitive advantage.

##### Object Storage—Valet Parking For Your Data

To illustrate how object storage works, computer experts often use a car parking analogy. Imagine your car is an item of unstructured data. You want to 'store' or park it in a parking lot. You have three options.

__‘Parking Your Data’—Storage Models Compared__

<img src="https://www.emc.com/content/dam/uwaem/production-design-assets/en/sdsaemmodule/images/ecs-object-storage-parking-your-data-storage-models-compared.gif">

#### The Advantages of Object Storage

In object storage technology, the ‘expert valet’ role is played by smart software that controls the system. Starting from a name that is meaningful to the application or user (e.g. ‘my-sales-records-2015’), the data is quickly identified via a highly optimized internal mechanism designed for fast lookups and reliability. If the physical location of an object is changed ‘behind the scenes’, this is simply updated in the internal lookup mechanism—the object’s ID (‘my-sales-records-2015’) stays the same, enabling users and applications to always easily access it at any later point in time.

In a storage system, the location of each item of data is identified and managed within a ‘namespace’. As discussed in our analogy, the namespaces for block storage (the available block 'grid references') and file storage (the possible file paths) can become a limitation as the amount of data grows. Object storage, however, is perfect for scaling with a massive growth of unstructured data, because the namespace is virtually limitless—there is an unending series of possible user-chosen names available.

The additional ‘abstraction’ of object storage away from the underlying hardware—letting smart software look after any complexities—makes it very simple to use, manage and maintain. Object storage also makes possible the use of multiple, simpler, lower-cost commodity storage devices of various types—with the smart software linking everything together into a single high-performance ‘cloud’ of storage.

Object storage is very robust and resilient, as each data object is typically ‘mirrored’ with at least three copies in geographically distributed locations. Each object also carries a ‘checksum’ value that allows any data corruption to be easily detected—in which case a new ‘good’ copy of the object can quickly be generated to replace it.

#### Object Metadata Powers Big Data, Analytics and Data Science

Another powerful feature of object storage is its use of ‘metadata’—or ‘data about data’. Each object when stored is labeled not only with its unique ID, but also with information about the data within the object. For example, a digitized song placed in object storage might be stored with additional metadata about the song title, artist, album, duration, year, and so on. It’s important to note that this metadata about each object is fixed to and stored with that object. It does not need to be held in a separate centralized database, which might quickly become unmanageably large.

This attached metadata enables much more sophisticated searching of data in object storage than in file storage—where the filename is often the only clue to a file’s contents. In a supermarket analogy, file storage is like the ‘value’ or ‘white label’ shelf, where items are identified only by a short (and often misleading) name on otherwise blank packaging. Object storage is more like a supermarket shelf where every item is clearly and comprehensively labeled with name, manufacturer, images, ingredients, serving instructions, nutritional information, and so on—enabling you to easily find exactly what you want, without having to open the packaging.

Another powerful aspect of object storage is that the nature of this metadata can be customized to suit the needs of the storage users and applications. The metadata can also be analyzed to gain new insights into the preferences of users and customers.

#### Object Storage Comes Home To The Data Center

The world really started to take more notice of object storage as it was embraced by the biggest and best-known web businesses over the past decade. Facebook, Instagram and Twitter use object storage to store millions of user photos every day. Spotify uses it to store millions of music tracks. Dropbox and other consumer online storage services store millions of uploaded documents in object storage—although usually hidden behind a familiar ‘files and folders’ interface.

Organizations can use the latest on-premise systems like EMC Elastic Cloud Storage (ECS) to implement a ‘private cloud’ of object storage—securely within their own enterprise data centers. EMC ECS also works perfectly as a complementary option to public cloud storage, creating a smart 'hybrid cloud' approach.

With on-premise object storage, organizations retain complete control over the security and physical location of their data—yet can enjoy all the key advantages of cloud and object storage, like scalability, efficiency, resiliency and simplicity. On-premise object storage gives you full control and security—you know where your data is and how it’s managed—vital if you have specific data governance requirements. And don’t forget the potential cost savings—it’s estimated that on-premise object storage like EMC ECS can deliver up to 65% lower TCO than using a public cloud solution.

##### Object Storage Advantages...

<img src="https://www.emc.com/content/dam/uwaem/production-design-assets/en/sdsaemmodule/images/ecs-object-storage-object-storage-advantages.gif">




