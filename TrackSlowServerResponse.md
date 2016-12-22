In general, these two parts: 1) network latency, the time it takes for the packets to traverse the network; 2) server delay, the time it takes for the server to process that application request.
In detail,
## Is it the network? (i.e. from client to sever)
1. Is the request not hitting cache of edge server in the CDN? Or Cache expired? If this case, it will be slower since we have to reach the origin server. Depends on how CDN is set up, what optimization strategy is used?
2. Check DNS response time (it should not be longer than 150ms or so)
3. If DNS is quick, next will send TCP SYN packet, compare this connection establish time with network roundtrip time. (TCP three way handshake: SYN->SYN-ACK->ACK, then and only then we can transmit data)
4. Next, check the time diff between SYN sent from client and SYN-ACK sent back from server.
5. Once TCP connection is established, client will request data from the server, check the time diff of server receiving the request and server actually sends back response. (if this time is high, then it is server's problem) (retransimission will happen if packet is lost, then this is a network problem)

## Is it server being slow? 
http://blog.scoutapp.com/articles/2014/07/31/slow_server_flow_chart

![alt](http://image.xlgps.com/upload/f/a1/fa11de3b4a78b409e955a77965f5d844.png)

1. Check I/O("wa"), If wait is high, may due to many users are accessing the server at the same time;
2. If CPU wait is low, we can rule out disk access. Anything above 10% I/O wait should be considered high.
3. Check CPU idle time, If your idle time is consistently above 25%, consider it "high enough".
4. If I/O wait is low and idle time is low, this means some process is consuming large percent of CPU, use top to identify the process.
5. If I/O wait is low and idle time is high (this is good), so it's not due to I/O or CPU issues, slowness is mostly caused by application level (deadlocks?).
6. Check memory usage (top -> M), if there is any memory leaks

## Database slowness:
1) Bind Variables: When a SQL query is sent to the database engine for processing and sending the result, it is compiled by the database compiler to get the tokens of the query. This involves parsing, optimizing and identifying the query. After a number of steps, the SQL query is passed to the database engine for processing. In a small application with a user base of less than 500, it is usually the same query which is executed more often than others. The use of bind variables helps in storing the compiled query once and executing it with different data at different times. For using bind variables, one needs to use PreparedStatement objects in Java.

2) Query is not well formed: Usually the same SQL query can be written in multiple ways. There are ways by which a query can be optimized to give the best performance. The corresponding SQL construct should be chosen depending upon requirement. I have scenarios where people have used WHERE clause instead of GROUP BY and are complaining of poor response times. Similarly Sub queries and Joins complement each other.

3) Database structure is not well defined/normalized: This is probably known to everybody that the database tables should be properly normalized as this is part of every DBMS course at graduation level. If the tables are not properly designed and normalized, anomalies set in.

4) Proper caching is not in place: Many applications make use of temporary caches on the application server to store the reference data or frequently accessed data as memory is less of an issue than the time with new generation servers.

5) Number of rows in the table too large: If the table itself has too much of data then the queries will take time to execute. Partitioning a table into multiple tables is recommended in these situations. For example: If a table has employee records of 1000000 employees then it could be split into 5 small tables each having 200000 rows. The advantage is we know beforehand in which smaller table to look for a particular employee code as the division of large table can be done on the employee id column.

6) Connections are not being pooled: If connections are not pooled then the each time a new connection is requested for a request to database. Maintaining a connection pool is much better than creating and destroying the connection for executing every SQL query. Of course, there are frameworks like Hibernate which take care of creating the connection pools and also allow the customization of these pools

7) Connections not closed/returned to pool in case of exceptions: When an exception occurs while performing database operations, it ought to be caught. Usually catching the exception is not the issue because SQLException is a checked exception but closing the connection is something that most of the times is left out. If the connection is not released, the same connection cannot be used for any other purpose till the connection is timed out.

8) Stored procedures for complex computations on database: Stored procedures are a good way to perform database intensive operations. This is because they are already compiled and there is less network trips for getting the same results as compared to SQL queries.
