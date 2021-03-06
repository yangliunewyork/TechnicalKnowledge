## Query Processing Basics

### Query Cache

You can enable the query cache (available as of MySQL 4.0.1) by setting query_cache_type to an appropriate value in my.cnf:
```
query_cache_type = 1
```
MySQL attempts to locate the results of any SELECT query in the query cache before bothering to analyze or execute it. It does this by hashing the query and using the hashed value to check for the results in the cache. __MySQL uses the exact query text it receives, so the cache is sensitive to the most trivial variations.__

As far as the cache is concerned, the query:
```
SELECT * FROM table1
```
is different from:
```
select * FROM table1
```
The same goes for variations in whitespace. MySQL doesn't trim extra space from the beginning or end of queries. This is rarely a problem because most repetitive queries are generated by applications rather than humans sitting at a keyboard.

__To save some effort, MySQL cheats a bit. It only bothers to hash SELECT queries, since they're the only ones it makes any sense to cache. Unfortunately, older 4.0 versions of MySQL don't consider every SELECT query. The logic it uses simply checks the first three characters of your query, looking for SEL in a case-insensitive way.__

As a result of this three-character "tunnel vision," any time you introduce whitespace or anything else at the beginning of the query, MySQL won't bother with the query cache. This can be a real problem in some applications. We know of a feed-processing system in which the developers uses comments to embed extra information at the beginning of each query:
```
/* <b>GetLatestStuff</b> */ SELECT * FROM sometable WHERE ...
```
The comment made is easier to identify the queries in an administrative tool that grabs the output of SHOW PROCESSLIST for display on a web page. Unfortunately, there's no way to tell MySQL to "try harder" when deciding whether a query is a SELECT, so these queries are never cached. Luckily, this problem is cured with a simple upgrade to MySQL 5.0.

It is possible to tell MySQL that it should not cache a given query, however. The way to dodge the query cache is to add the SQL_NO_CACHE hint to your query.
```
SELECT SQL_NO_CACHE * FROM mytable
```
This is helpful in controlling cache pollution. If your application has a set of queries that will never benefit from the query cache (perhaps because they run only once a day), there's no sense in caching them. Telling MySQL not to cache such queries leaves more room for storing the results of repetitive queries.

When the query cache is running in ondemand mode (set query_cache_type to 2 in my.cnf), MySQL does the work of trying to find a query in the cache only when it sees a SQL_CACHE hint in the query:
```
SELECT SQL_CACHE * FROM mytable
```
If the query's hashed value is found in the cache, MySQL sends the results from the cache to the client, bypassing any additional effort, just as expected.

The format of the results in the query cache is identical to the format used when sending them to a client. So there is very little overhead in retrieving results from the cache and sending them to a client. MySQL simply sends the data over the network.

### Parsing, Analysis, and Optimization
Before MySQL can do anything interesting (or useful) with a noncached query, it must parse the query into its component parts. As part of that process, it verifies that the query is syntactically valid and gathers some basic information about the query:

* What type of query is this? Is it a SELECT, INSERT, UPDATE, or DELETE, or some other administrative command such as SET or GRANT?
* Which tables are involved? Are there any aliases used?
* What is the WHERE clause?
* Are there other hints or modifiers involved?

Once a query is broken down into more basic pieces, MySQL begins the more challenging work of figuring out what to do with it. This is where the query optimizer kicks in. The query optimizer's goal, simply put, is to find the most efficient way to execute a query given all the available information. Most of the time, this means the optimizer works to limit the number of records it must examine. It does this because the time associated with disk I/O is often (but not always) the governing factor that determines how long a query will take. Intuitively, this makes complete sense. It is an extension of the very same logic that explains why indexes are so helpful.

How the optimizer goes about making decisions is often regarded by people unfamiliar with MySQL internals as something like voodoo. Of course, it's not voodoo at all. MySQL has a set of rules and heuristics that have been evolving since its early days. These rules guide its decision-making process. But like any computer program that must deal with the infinite ways humans can assemble data and ask questions about it, the optimizer's not perfect. The rules and heuristics it uses work very well much of the time, but, on occasion, they do not.

The MySQL developers are constantly improving the optimizer—attempting to make it smarter and faster with each new release. Based on feedback from real-world users, they are always looking for ways to refine MySQL's ability to make the right decision. If you find a query that causes MySQL to make bad decisions, be sure to report it. Unreported problems are rarely fixed.

To make good decisions, MySQL tries to answer several important questions.

Are there any indexes that are candidates for finding the rows quickly?

Which index is best? If multiple tables are involved, which index is best for each table?

Which tables depend on which other tables in the join?

What's the optimal join order for the tables?

Of course, MySQL needs to make a decision very quickly and without actually testing all the options. Otherwise it might spend more time deciding how to execute the query than actually executing it!

The bulk of MySQL's effort centers around indexes and table join order. These aren't the only factors, but they're certainly the important ones. To get a better understanding of what MySQL is thinking about a SELECT query, it's best to look at the EXPLAIN output for the query.

### Using EXPLAIN

So, what sort of knowledge can MySQL gather without expending a lot of effort and time? Let's look at a some queries against a news headline table—the sort of thing you might use to build a customizable news web site. The structure of the table is listed next. Rather than guessing what MySQL will probably do, we'll use its under-appreciated EXPLAIN command to help figure that out. In doing so, we'll see how adding an index or simply rephrasing a query can often better use an existing index and greatly improve performance.

### Joins

Things become slightly more complex when you're querying multiple tables. MySQL has to decide which order makes the most sense. Again, the goal it to read as few rows as possible, so it will consider each table and estimate how many rows it must read from each. In doing so, it also needs to understand the relationship among the tables. For example, with a query like this, it's clear that MySQL can't read the table order first:
```
SELECT customer.name, order.date_placed, region.name
FROM customer, order, region
WHERE order.customer_id = customer.id
AND customer.region_id = region.id
AND customer.name = 'John Doe'
```
The rows MySQL will need to retrieve from the order table depend on the customer table. So it must read customer before order. In fact, the same is true of region. So in this case, MySQL has to read customer records first. From there it will decide to read the remaining tables in whatever order it chooses.

Unfortunately, finding the optimal join order is one of MySQL's weakest skills. Rather than being clever about this problem, the optimizer simply tries to brute-force its way through. It tries every possible combination before choosing one. That can spell disaster in a some cases. We've seen at least one case in which MySQL took 29 seconds to decide how to execute a multitable join and then 1 second to actually execute it. In this particular case, there were over 10 tables involved. Since MySQL is considering all possible combinations, performance begins to degrade quite drastically as you go beyond a handful of tables. The exact number, of course, depends on how powerful CPUs are this year.


##### Execution

There's not a lot to say about query execution. MySQL simply follows its plan, fetching rows from each table in order and joining based on the relevant columns (hopefully using indexes). Along the way, it may need to create a temporary table (in memory or on disk) to store the results. Once all the rows are available, it sends them to the client.

Along the way, MySQL gathers some information and statistics about each query it executes, including:

* Who issued the query
* How long the process took
* How many rows were returned

That information will appear in the slow query log (discussed later in this chapter) if the query time exceeds the server's threshold, and the log is enabled. If the query is issued interactively, it will also appear after the query results.

## Optimizer Features and Oddities
