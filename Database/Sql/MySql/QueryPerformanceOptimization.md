### Slow Query Basics: Optimize Data Access
The most basic reason a query doesn’t perform well is because it’s working with too much data. Some queries just have to sift through a lot of data and can’t be helped. That’s unusual, though; most bad queries can be changed to access less data. We’ve found it useful to analyze a poorly performing query in two steps:
1. Find out whether your application is retrieving more data than you need. That usually means it’s accessing too many rows, but it might also be accessing too many columns. 
2. Find out whether the MySQL server is analyzing more rows than it needs.

#### Is MySQL Examining Too Much Data?
Once you’re sure your queries retrieve only the data you need, you can look for queries that examine too much data while generating results. In MySQL, the simplest query cost metrics are: 
* Execution time 
* Number of rows examined 
* Number of rows returned
None of these metrics is a perfect way to measure query cost, but they reflect roughly how much data MySQL must access internally to execute a query and translate approximately into how fast the query runs. All three metrics are logged in the slow query log, so looking at the slow query log is one of the best ways to find queries that examine too much data.

### Ways to Restructure Queries

* Complex Queries Versus Many Queries
* Chopping Up a Query
* Join Decomposition

### Query Execution Basics
If you need to get high performance from your MySQL server, one of the best ways to invest your time is in learning how MySQL optimizes and executes queries. Once you understand this, much of query optimization is simply a matter of reasoning from principles, and query optimization becomes a very logical process.

1. The client sends the SQL statement to the server. 
2. The server checks the query cache. If there’s a hit, it returns the stored result from the cache; otherwise, it passes the SQL statement to the next step. 
3. The server parses, preprocesses, and optimizes the SQL into a query execution plan. 
4. The query execution engine executes the plan by making calls to the storage engine API. 
5. The server sends the result to the client.

