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
1. Query is not well formed, Database structure is not well defined/normalized
2. Missing cache of frequntly used queries, etc.
3. Number of rows in the table too large
4. Connections are not being pooled (i.e. creating and destroying connection everytime),
   or connections are not closed/returned to pool in case of exception
5. Lacking of stored procedure (pre compiled SQL queries)
6. Missing index/Poor index design
