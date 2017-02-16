If you care about database performance in your applications (and if you're reading this book, you probably do), benchmarking needs to become part of your development testing process. When you're testing an upgrade to MySQL or some MySQL configuration changes, run the benchmark tests you developed while building the application. Look at the results. Make sure they don't surprise you.

## The Importance of Benchmarking

Benchmarking is fundamentally a "what if" game. By setting up a simple test, you can quickly answer questions such as the following:

* What if I increase the number of rows by a factor of 10? Will my queries still be fast?
* Will a RAM upgrade really help? If so, how much?
* Is the new server really twice as fast as the old one?
* What if I disable the query cache?
* Which is faster, using a subquery or two shorter queries?
* What happens when this query is run multiple times or is run with other queries?

Benchmarking is often about comparisons. When deciding to make an important change, you'll want first to test the alternative(s) and then decide what to do based on the results of the test.

Our goal is to make benchmarking MySQL easy. Anytime you catch yourself wondering if A is faster than B, or whether A or B uses more memory, just pull out your favorite benchmarking tool and find out. Sometimes you'll be surprised by the results. To achieve the goal of easy MySQL benchmarking, we've tried to document how to use the available tools.

Beyond answering what-if questions, benchmarking is especially important in database-driven applications because it can highlight problems that are otherwise difficult to pinpoint. When an application slows down, the database may not be the first suspect. After spending a lot of time testing the application code, you'll eventually need to isolate the database to see whether it is a significant bottleneck. Having a prebuilt benchmark makes that task trivial.

## Benchmarking Strategies
To make benchmarking as realistic and hassle-free as possible, here are several suggestions to consider:


#### Change one thing at a time
In science this is called isolating the variable. No matter how well you think you understand the effects your changes will have, don't make more than one change between test runs. Otherwise you'll never know which one was responsible for the doubling (or halving) of performance. You might be surprised to find that an adjustment you made once before to improve performance actually makes it worse in your current tests.

#### Test iteratively
Try not to make dramatic changes. When adjusting MySQL's buffers and caches, you'll often be trying to find the smallest value that comfortably handles your load. Rather than increasing a value by 500%, start with a 50% or 100% increase and continue using that percentage increase on subsequent tests. You'll probably find the optimal value faster this way. Similarly, if you're working from larger values to smaller, the time-tested "divide and conquer" technique is your best bet. Cut the current value in half, retest, and repeat the process until you've zeroed in close to the correct value.

#### Always repeat tests
No matter how carefully you control the environment, something can creep in and really mess up your numbers. Maybe you forgot to disable cron, or you have some disk-intensive script running in the background. Because the disk is already being hit, you may not notice the new process, but it sure can slow down MySQL.

By running each test several times (we recommend no fewer than four) and throwing out the first result, you minimize the chance of an outside influence getting in the way. It will be pretty clear that something was wrong with the first result when the second and third set of tests run twice as fast as the first. Also, consider restarting MySQL and even rebooting your server between test runs to factor out caching artifacts.


#### Use real data
It sounds like common sense, doesn't it? If you're not testing with real data, it's difficult to draw conclusions based on the numbers you get. As you'll see in Chapter 4, MySQL will often behave differently when presented with different sets of data. The query optimizer makes decisions based on what it knows about the data you've stored. If you're testing with fake data, there's a chance that the optimizer's decisions aren't the same as they'll be when you switch to using your real data.

In a similar vein, try to use a realistic amount of data. If you plan to have 45 million rows in a table but test with only 45 thousand, you'll find that performance drops off quite a bit after the table is filled up—and it has nothing to do with limits in MySQL. The simple fact is that your server probably has enough memory to keep 45 thousand rows cached, but 45 million rows aren't nearly as likely to be entirely cached.


#### Don't use too many clients
Try not to go crazy with benchmarking. It's fun to see how hard you can push your server, but unless you're doing stress testing, there's little need to run more than 40 or 50 concurrent clients in day-to-day benchmarking. What you'll likely find is that performance (measured in queries/second) reaches a plateau when you try to increase the simulated clients beyond a certain number.

 There will always be exceptions. If your site must routinely handle 450 connections, you'll obviously need to test with numbers close to 450.

When you attempt to use too many clients, your server will refuse to accept any more connections than specified by the max_clients setting. Be careful not to increase this value too much; if you do, the server may start to swap wildly and grind to a halt simply because it doesn't have the resources (typically memory) to handle huge numbers of clients. We'll come back to this in Chapter 6 when we look at service performance. But the test doesn't help you evaluate your server realistically.

You can find the optimal number of clients by using a simple iterative testing method. Start with a small number such as 20, and run the benchmark. Double the number, and run it again. Continue doubling it until the performance does not increase, meaning that the total queries per second stays the same or decreases. Another option is to use data from your logs to find out roughly how many concurrent users you handle during peak times.


#### Separate the clients from the server
Even if your real application runs on the same host as MySQL, it's best to run the benchmarking client on a separate machine. In this way, you need not worry about the resources required by the client interfering with MySQL's performance during the test.

