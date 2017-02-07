## Source

* http://horicky.blogspot.com/2008/03/database-scalability.html

## Database Scalability

Database is typically the last piece of the puzzle of the scalability problem. There are some common techniques to scale the DB tire.

#### Indexing

Make sure appropriate indexes is built for fast access. Analyze the frequently-used queries and examine the query plan when it is executed (e.g. use "explain" for MySQL). Check whether appropriate index exist and being used.

#### Data De-normalization

Table join is an expensive operation and should be reduced as much as possible. One technique is to de-normalize the data such that certain information is repeated in different tables.

#### DB Replication

For typical web application where the read/write ratio is high, it will be useful to maintain multiple read-only replicas so that read access workload can be spread across. For example, in a 1 master/N slaves case, all update goes to master DB which send a change log to the replicas. However, there will be a time lag for replication.

#### Table Partitioning

You can partition vertically or horizontally.

Vertical partitioning is about putting different DB tables into different machines or moving some columns (rarely access attributes) to a different table. Of course, for query performance reason, tables that are joined together inside a query need to reside in the same DB.

Horizontally partitioning is about moving different rows within a table into a separated DB. For example, we can partition the rows according to user id. Locality of reference is very important, we should put the rows (from different tables) of the same user together in the same machine if these information will be access together.

#### Transaction Processing

Avoid mixing OLAP (query intensive) and OLTP (update intensive) operations within the same DB. In the OLTP system, avoid using long running database transaction and choose the isolation level appropriately. A typical technique is to use optimistic business transaction. Under this scheme, a long running business transaction is executed outside a database transaction. Data containing a version stamp is read outside the database trsnaction. When the user commits the business transaction, a database transaction is started at that time, the lastest version stamp of the corresponding records is re-read from the DB to make sure it is the same as the previous read (which means the data is not modified since the last read). Is so, the changes is pushed to the DB and transaction is commited (with the version stamp advanced). In case the version stamp is mismatched, the DB transaction as well as the business transaction is aborted.


#### Object / Relational Mapping
Although O/R mapping layer is useful to simplify persistent logic, it is usually not friendly to scalability. Consider the performance overhead carefully when deciding to use O/R mapping.

There are many tuning parameters in O/R mapping. Consider these ...
* When an object is dereferenced, how deep the object will be retrieved
* If a collection is dereferenced, does the O/R mapper retrieve all the object contained in the collection ?
* When an object is expanded, choose carefully between multiple "single-join" queries and single "multiple join" query
