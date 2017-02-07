## What is OLTP ?
__Online transaction processing, or OLTP, is a class of information systems that facilitate and manage transaction-oriented applications, typically for data entry and retrieval transaction processing.__

The term is somewhat ambiguous; some understand a "transaction" in the context of computer or database transactions, while others (such as the Transaction Processing Performance Council) define it in terms of business or commercial transactions. OLTP has also been used to refer to processing in which the system responds immediately to user requests. An automated teller machine (ATM) for a bank is an example of a commercial transaction processing application. __Online transaction processing applications are high throughput and insert or update-intensive in database management.__ These applications are used concurrently by hundreds of users. __The key goals of OLTP applications are availability, speed, concurrency and recoverability.__ Reduced paper trails and the faster, more accurate forecast for revenues and expenses are both examples of how OLTP makes things simpler for businesses. However, like many modern online information technology solutions, some systems require offline maintenance, which further affects the cost–benefit analysis of on line transaction processing system.

OLTP is typically contrasted to OLAP (online analytical processing), which is generally characterized by much more complex queries, in a smaller volume, for the purpose of business intelligence or reporting rather than to process transactions. Whereas OLTP systems process all kinds of queries (read, insert, update and delete), OLAP is generally optimized for read only and might not even support other kinds of queries.

## Overview
OLTP system is a popular data processing system in today's enterprises. Some examples of OLTP systems include order entry, retail sales, and financial transaction systems.[3] On line transaction processing system increasingly requires support for transactions that span a network and may include more than one company. For this reason, modern on line transaction processing software use client or server processing and brokering software that allows transactions to run on different computer platforms in a network.

In large applications, efficient OLTP may depend on sophisticated transaction management software (such as CICS) and/or database optimization tactics to facilitate the processing of large numbers of concurrent updates to an OLTP-oriented database.

For even more demanding decentralized database systems, OLTP brokering programs can distribute transaction processing among multiple computers on a network. OLTP is often integrated into __service-oriented architecture (SOA)__ and __Web services__.
On line transaction processing (OLTP) involves gathering input information, processing the information and updating existing information to reflect the gathered and processed information. As of today, most organizations use a database management system to support OLTP. OLTP is carried in a client server system.

On line transaction process concerns about concurrency and atomicity. Concurrency controls guarantee that two users accessing the same data in the database system will not be able to change that data or the user has to wait until the other user has finished processing, before changing that piece of data. Atomicity controls guarantee that all the steps in transaction are completed successfully as a group. That is, if any steps between the transaction fail, all other steps must fail also.  

## What is the difference between OLTP and OLAP?
* OLTP (On-line Transaction Processing) is characterized by a large number of short on-line transactions (INSERT, UPDATE, DELETE). The main emphasis for OLTP systems is put on very fast query processing, maintaining data integrity in multi-access environments and an effectiveness measured by number of transactions per second. In OLTP database there is detailed and current data, and schema used to store transactional databases is the entity model (usually 3NF). 

* OLAP (On-line Analytical Processing) is characterized by relatively low volume of transactions. Queries are often very complex and involve aggregations. For OLAP systems a response time is an effectiveness measure. OLAP applications are widely used by Data Mining techniques. In OLAP database there is aggregated, historical data, stored in multi-dimensional schemas (usually star schema). 


The following table summarizes the major differences between OLTP and OLAP system design.

* OLTP System - Online Transaction Processing (Operational System)
* OLAP System - Online Analytical Processing (Data Warehouse)

* Source of data
  * OLTP: Operational data; OLTPs are the original source of the data.
  * OLAP: Consolidation data; OLAP data comes from the various OLTP Databases

* Purpose of data
  * OLTP: To control and run fundamental business tasks
  * OLAP: To help with planning, problem solving, and decision support

* What the data
  * OLTP: Reveals a snapshot of ongoing business processes
  * OLAP: Multi-dimensional views of various kinds of business activities

* Inserts and Updates
  * OLTP: Short and fast inserts and updates initiated by end users
  * OLAP: Periodic long-running batch jobs refresh the data

* Queries
  * OLTP: Relatively standardized and simple queries Returning relatively few records
  * OLAP: Often complex queries involving aggregations

* Processing Speed
  * OLTP: Typically very fast
  * OLAP: Depends on the amount of data involved; batch data refreshes and complex queries may take many hours; query speed can be improved by creating indexes

* Space Requirements
  * OLTP: Can be relatively small if historical data is archived
  * OLAP: Larger due to the existence of aggregation structures and history data; requires more indexes than OLTP

* DatabaseDesign
  * OLTP: Highly normalized with many tables
  * OLAP: Typically de-normalized with fewer tables; use of star and/or snowflake schemas

* Backup and Recovery
  * OLTP: Backup religiously; operational data is critical to run the business, data loss is likely to entail significant monetary loss and legal liability
  * OLAP: Instead of regular backups, some environments may consider simply reloading the OLTP data as a recovery methodsource: 


