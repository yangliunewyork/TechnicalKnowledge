Database-as-a-Service (DBaaS) is the fastest growing cloud service, and the Platform-as-a-Service component and provides dramatic improvements in productivity, performance, standardization, and data security of databases. This article introduces the reader to DBaaS, describes the benefits and introduces the user to some popular DBaaS solutions in the market.

### Database-as-a-Service defined

<img src="https://www.stratoscale.com/wp-content/uploads/What_is_DBaaS.png">

The term “Database-as-a-Service” (DBaaS) refers to software that enables users to provision, manage, consume, configure, and operate database software using a common set of abstractions (primitives), without having to either know nor care about the exact implementations of those abstractions for the specific database software.

In other words, a DBaaS user could provision a MySQL database, manage, configure and operate it using the same set of API calls as he (or she) would use if it were an Oracle or MongoDB database. The user would be able, for example, to request a backup of the database using an API call which did the right thing(s) for the database that was being used. Similarly, the user could request a MySQL cluster or a MongoDB cluster, and then resize that cluster using the same API call(s), without having to know exactly how that operation was being performed for each of those database technologies.

DBaaS is often considered to be a component of a Platform-as-a-Service, the “platform” in this case being the database (or a number of databases). The DBaaS solution would consume resources of the underlying Infrastructure-as-a-Service (IaaS), for example provisioning compute, storage and networking from that IaaS.

### DBaaS in the context of other cloud components

It is important to understand that like other cloud technologies, DBaaS has two primary consumers:

* The IT organization (which operates the cloud, very often also the DBA)
* And the developer (sometimes DevOps, or the end user who uses the cloud resources)

An IT organization deploys DBaaS that enables end users (developers) to provision a database of their choice from a catalog of supported databases. These could include popular relational and non-relational databases and the IT organization can configure the DBaaS to support specific releases of these software titles. The IT organization can further restrict the configurations that specific users can provision (for example, developers can only provision with small memory footprint, with traditional disks while devops could provision higher capacity servers with SSD’s). Finally, the IT organization can setup policies for standard database operations like backups to ensure that the data is properly saved from time to time to allow for recovery when required.

Typically an end user would access the DBaaS system through a portal that allows him or her to choose from a number of database titles, and in a variety of different configuration options.   With a few clicks this requested this database will be provisioned for them. The DBaaS system quickly provisions the database and returns a query able endpoint like:

mysql://192.168.15.243:3306/

and the application developer can use this in his or her application directly. The DBaaS system provides simple mechanisms to add users, create databases (schemas) and grant permissions to different users as required by the application.

### The benefits of DBaaS

A DBaaS solution provides an organization a number of benefits, the chief among them being:

* Developer agility
* DBA productivity
* Application reliability, performance and security

##### Developer agility

When a developer wishes to provision a database, the steps involved include provisioning compute, storage and networking components, configuring them properly and then installing database software. Finally, the database software must be configured properly to utilize the underlying infrastructure components.

This multi-step process leaves many opportunities for errors, omissions and non-standard modes of operation. When the thing that is being provisioned (a database) is the “system of record”, this is unacceptable.

The IT organization in configuring the DBaaS establishes the standards by which databases will be provisioned. By standardizing the provisioning model, DBaaS ensures that a database can be provisioned in a single operation, and that databases are provisioned in a consistent way, and in a manner that is aligned with the best practices for that particular database and business.

Once in operation, complex database operations like resizing a cluster are now a simple API call and the developer need not concern him or her selves with the minutiae of how this operation should be performed for the specific database and version. The abstraction provided by the DBaaS handles all of that and allows the developer to focus his or her  energy on the application rather than the underlying database.

Finally, the activities of a developer are often iterative and involve spinning up, using, and then destroying database servers. Abstractions in the DBaaS allow for the final step in this process to be automated as well, securely erasing all storage used for the database and ensuring that all the resources are released and that data integrity is preserved at all times.

#### DBA productivity

When an enterprise operates hundreds of instances of many different databases, a considerable  resources get consumed on maintenance and upkeep. This includes things like tuning, configuration, patching, periodic backups, and so on; all the things that DBAs have to do to keep databases in proper working order.

DBaaS solutions provide abstractions that allow DBAs to manage groups of databases and perform operations like upgrades and configuration changes on a fleet of databases in a simplified way. This frees up the DBAs to focus more on activities like establishing the standards of operation for the enterprise and verifying that they have the best tools available for themselves and the developers who they serve.

##### Application reliability, performance and security

Databases are often the “system of record” and are the repository of valuable information in the organization. A database outage could have catastrophic impact. Through automation and standardization, DBaaS ensures that all common workflows involved in the provisioning, configuration, management, and operation of databases are consistent.

Through this standardization, a DBaaS ensures that all databases are operated in the same way, and in keeping with the best practices established by the IT organization.  This , frees up the developer and DBA to work on more important things like the application and  innovation rather than the boring minutiae of running a database.

It is important to realize that most enterprises today operate applications that require many different database technologies, a departure from recent years where the ‘corporate standard’ mandated a single database solution for all application needs. With this diversity in database technologies, DBaaS solutions allow IT organizations to ensure application reliability, performance and data security no matter what database solution is in use, without requiring that the IT organization or the developer team have deep knowledge of the finer points of each of the technologies. DBaaS solutions encapsulate those best practices and codify the proper way(s) to deploy, manage and operate all of the different technologies thereby freeing up the DBAs and developers from these chores.

### Conclusion

Database-as-a-Service provides a framework within which enterprises can operate all of their databases. It provides end users (developers and application deployers) with improved agility and simplified provisioning and operation, and the flexibility to choose from amongst a number of pre-configured options established by the IT organization. DBaaS improves the operation (IT and DBA) of fleets of diverse database through automation and standardization allowing IT organizations to cost-effectively offer their users with a number of database choices while also ensuring that these databases are operated in a safe and secure way and in compliance with established best practices.
