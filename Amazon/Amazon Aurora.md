Amazon Aurora (Aurora) is a fully managed relational database engine that's compatible with MySQL and PostgreSQL. You already know how MySQL and PostgreSQL combine the speed and reliability of high-end commercial databases with the simplicity and cost-effectiveness of open-source databases. The code, tools, and applications you use today with your existing MySQL and PostgreSQL databases can be used with Aurora. With some workloads, Aurora can deliver up to five times the throughput of MySQL and up to three times the throughput of PostgreSQL without requiring changes to most of your existing applications.

Aurora includes a high-performance storage subsystem. Its MySQL- and PostgreSQL-compatible database engines are customized to take advantage of that fast distributed storage. The underlying storage grows automatically as needed, up to 64 terabytes. Aurora also automates and standardizes database clustering and replication, which are typically among the most challenging aspects of database configuration and administration. 

#### An introduction to Amazon RDS

Amazon Relational Database Service (Amazon RDS) is a hosted database service which provides multiple database products to choose from, including Aurora, PostgreSQL, MySQL, MariaDB, Oracle, and Microsoft SQL Server. We will focus on MySQL and Aurora.

With regards to systems administration, both solutions are time-saving. You get an environment ready to deploy your application and if there are no dedicated DBAs, RDS gives you great flexibility for operations like upgrades or backups. For both products, Amazon applies required updates and the latest patches without any downtime. You can define maintenance windows and automated patching (if enabled) will occur within them. Data is continuously backed up to S3 in real time, with no performance impact. This eliminates the need for backup windows and other, complex or not, scripted procedures. Although this sounds great, the risk of vendor lock-in and the challenges of enforced updates and client-side optimizations are still there.

AWS RDS is the managed database solution which provides support for multiple database options Amazon Aurora, PostgreSQL, MySQL, MariaDB, Oracle, and Microsoft SQL Server. When you go with RDS it will provide inbuilt configuration options such as.

* Database Replication for High Availability  
* Read Replicas for Scalability  
* Backups & Restore  
* Operating system and software patches & etc.  

This simplifies the overhead of database administration. However the flexibility is limited to the RDS offerings.

Alternatively if you host your database in EC2 instance, you can install the required versions of the database engines, install needed extensions & etc. which provides more flexibility but also requires expertise & adds administration overhead.

When you consider Amazon Aurora in RDS, it differs from the rest of the engines because, its new and fully implemented by Amazon from ground up and offers higher performance, reliability out of the box (As marketed by Amazon) with reasonable pricing. However one limitation with Aurora is that its not included in AWS free-tier, where the smallest instance type it supports is "small".
