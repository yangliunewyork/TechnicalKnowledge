__Object storage__ (also known as object-based storage) is a computer data storage architecture that manages data as objects, as opposed to other storage architectures like file systems which manage data as a file hierarchy and __block storage__ which manages data as blocks within sectors and tracks.[2] Each object typically includes the data itself, a variable amount of metadata, and a globally unique identifier. Object storage can be implemented at multiple levels, including the device level (object storage device), the system level, and the interface level. In each case, object storage seeks to enable capabilities not addressed by other storage architectures, like interfaces that can be directly programmable by the application, a namespace that can span multiple instances of physical hardware, and data management functions like data replication and data distribution at object-level granularity.


Object-storage systems allow retention of massive amounts of unstructured data. Object storage is used for purposes such as storing photos on Facebook, songs on Spotify, or files in online collaboration services, such as Dropbox.

# Object Storage vs. Block Storage Services

Flexible and scalable data storage is a baseline requirement for most applications and services being developed with modern techniques and tools. Whether storing large or small amounts of images, videos, or blobs of text, application developers need a solution for the storage and retrieval of user-generated content, logs, backups, and so on.

With today's complex deployments, containers, and ephemeral infrastructure, the days of simply saving files to disk on a single server are gone. _Cloud providers have developed services to fill the storage needs of modern application deployments, and they mostly fit into two categories: object storage, and block storage._

### What is Block Storage

Block storage services are relatively simple and familiar. They provide a traditional block storage device — like a hard drive — over the network. Cloud providers often have products that can provision a block storage device of any size and attach it to your virtual machine.

From there, you would treat it like a normal disk. You could format it with a filesystem and store files on it, combine multiple devices into a RAID array, or configure a database to write directly to the block device, avoiding filesystem overhead entirely. Additionally, network-attached block storage devices often have some unique advantages over normal hard drives:

* You can easily take live snapshots of the entire device for backup purposes
* Block storage devices can be resized to accommodate growing needs
* You can easily detach and move block storage devices between machines

This is a very flexible setup that can be useful for most any kind of application. Let's summarize some advantages and disadvantages of the technology.

Some advantages of block storage are:

* Block storage is a familiar paradigm. People and software understand and support files and filesystems almost universally
* Block devices are well supported. Every programming language can easily read and write files
* Filesystem permissions and access controls are familiar and well-understood
* Block storage devices provide low latency IO, so they are suitable for use by databases.

The disadvantages of block storage are:

* Storage is tied to one server at a time  
* Blocks and filesystems have limited metadata about the blobs of information they're storing (creation date, owner, size). Any additional information about what you're storing will have to be handled at the application and database level, which is additional complexity for a developer to worry about  
* You need to pay for all the block storage space you've allocated, even if you're not using it  
* You can only access block storage through a running server  
* Block storage needs more hands-on work and setup vs object storage (filesystem choices, permissions, versioning, backups, etc.)  

Because of its fast IO characteristics, block storage services are well suited for storing data in traditional databases. Additionally, many legacy applications that require normal filesystem storage will need to use a block storage device.

### What is Object Storage

In the modern world of cloud computing, object storage is the storage and retrieval of unstructured blobs of data and metadata using an HTTP API. Instead of breaking files down into blocks to store it on disk using a filesystem, we deal with whole objects stored over the network. These objects could be an image file, logs, HTML files, or any self-contained blob of bytes. They are unstructured because there is no specific schema or format they need to follow.

Object storage took off because it greatly simplified the developer experience. Because the API consists of standard HTTP requests, libraries were quickly developed for most programming languages. Saving a blob of data became as easy as an HTTP PUT request to the object store. Retrieving the file and metadata is a normal GET request. Further, most object storage services can also serve the files publicly to your users, removing the need to maintain a web server to host static assets.

On top of that, object storage services charge only for the storage space you use (some also charge per HTTP request, and for transfer bandwidth). This is a boon for small developers, who can get world-class storage and hosting of assets at costs that scale with use.

Object storage isn't the right solution for every situation though. Let's look at a summary of benefits and disadvantages.

Some advantages of object storage are:

* A simple HTTP API, with clients available for all major operating systems and programming languages  
* A cost structure that means you only pay for what you use  
* Built-in public serving of static assets means one less server for you to run yourself  
* Some object stores offer built-in CDN integration, which cache your assets around the globe to make downloads and page loads faster for your users  
* Optional versioning means you can retrieve old versions of objects to recover from accidental overwrites of data  
* Object storage services can easily scale from modest needs to really intense use-cases without the developer having to launch more resources or rearchitect to handle the load  
* Using an object storage service means you don't have to maintain hard drives and RAID arrays, as that's handled by the service provider
* Being able to store chunks of metadata alongside your data blob can further simplify your application architecture

Some disadvantages of object storage are:

* You can't use object storage services to back a traditional database, due to the high latency of such services
* Object storage doesn't allow you to alter just a piece of a data blob, you must read and write an entire object at once. This has some performance implications. For instance, on a filesystem, you can easily append a single line to the end of a log file. On an object storage system, you'd need to retrieve the object, add the new line, and write the entire object back. This makes object storage less ideal for data that changes very frequently
* Operating systems can't easily mount an object store like a normal disk. There are some clients and adapters to help with this, but in general, using and browsing an object store is not as simple as flipping through directories in a file browser












