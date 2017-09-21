# Why NewsHQ ?
 Tom, Guang and I were tracking a searching related issue reported by client.  We log into our searching boxes, ran top commands on each of them to check system summary information, grep searching log to see any eccentric behaviors， check monster chars for historical information. And sometimes NewsAlerting folks need to run a bunch of python scripts to search clients-defined alerting criteria to check why clients did not receive alerts they are expecting. All the debug/track operations are time-consuming and they usually happen a short time after market open, 2 or 3 such operations will take away the whole morning, which the most productive time of the whole day.

One year ago,during lunchtime, Tom said that he saw a dashboard somewhere online and think it was cool, and he showed to me after lunch. I saw that online dashboard and  said, “it is quite good and it will be cool if monster can be as simple as this ”. And then Tom asked, “Yang, do you want to be a full-stack engineer?” And I said, “Tom, I was an Asp.net developer before join FactSet”, and Tom said, “ so you have front end experience, that’s even better”.

And that’s how we begin to work on NewsHQ.

NewsHQ is a dashboard that help us to monitor our applications and databases' mission critical key performance metrics like uptime, load time, response time, cpu usage, memory usage and the multitude of other components that help us to deliver a stable end user experience to our clients.

There are inevitably times when things break, when hardware degrade.  A dashboard that monitors your core processes can mean the difference between spotting an issue before clients do,   and finding a mountain of support tickets from angry customers. 

Being  a passive, reactive engineers who sometimes get pushed around by system issues, clients’ complaints is not fun at all. You may be working on developing features that our clients desperately want, our product managers are looking forward to and you may even already gave them an estimated delivery time, and then “boom”, something is not working. And you have to do a “context switch” and  jump on to analyze the issues. 

### What can NewsHQ bring to us?

It save us from tedious manual operation work.
It reduce our time to track issues.
It let us know what is not working and also what is working BUT just not working WELL.
It integrates our scattered around operation tools into one centralized stop.
It bring better processes/system analysis tools for us to find out what can be improved and what must be fixed.
It help us from being passive, reactive to be more proactive and productive.
It help us to make patching smooth.


# Demo

### Home page

The left panel is "System Overview". It has the process heatmap which lists all the boxes and running processes on them.
Each small square represents a process, "green" means it is running, "red" means it is down.
When your mouse hover over any small square, it will show the process name. And once you click it, a new tab will be open and direct you to the corresponding process page. Each process page can be cunstomized by monitoring different metrics, and by default, the uptime/downtime is shown up there.

On the right panel, we have "Recent Activity" and "Upcoming Events", 


### Host Page

We have a slogan for host page, which is "every box in one page". It is very clear and straightforward.

You can see the CPU/Memory/Disk/Inodes of all the boxes we are concerning about within one page.

And when any value is changing, the tiny animation will make sure you won't miss that.

We have 3 health status for all the metrics here. Other than the normal status, if metrics goes up to 50%, it will be shown as in orange text, if goes up to 70%, the text will be highlighted as red.

This page brings  us a very clear system realtime summary on all our boxes. It is an example to show that how NewsHQ can help us to be more proactive.

What if you want to get more system information about a specific box?

Just lick any box here, it will guide us to a specifix box page which give you a more detailed system information about that box.

All the information and charts on this page are  updated every 20 seconds.

On the top,  there are Fill Gauge CPU chart and other memory pie charts. 

And then we have CPU line chart and memory bar chart which give you realtime view as well as historical information.

By simply clicking the zoom in links, you can get different datetime range, up to 24 hours.

By hovering above any data point, you can see a tiny tooltip.

On the bottom, we have the status information of all the processes running on that host.

Click any process will direct you to the process page, which by default give you uptime/downtime information as well as the general process information. For example, the process's owner group and their email address. 

### Services page

News HQ services page lists all the services we are concerning about.  Click any service tile will direct you to that service page, which listed all the operations you can do about that service there.

As you can see, NewsHQ has a very clear visual hierarchy layout. We don't need to give you a manual about it and you won't get lost here. And NewsHQ's URL reveals the hierarhy as well,  you can consider the URL as the Polaris which can guide you here and make the navigation easier.


#### NSS redirection page

News searching have two database clusters, A and B. If one of the data centers fails then we need a way to redirect traffic to the other data center. Previously, we need to ssh to the NSS boxes and modify the configuration files there and restart NSS instances.

Right now we have this redirection page which can perform traffic switch over within as minimal as 2 clicks, and can be grandular down to feed basis. It's just that simple. It is as simple as Amazon one-click payment. Maybe we should file a patent for this too?

We can also use the filter box to narrow down the news feeds we looking for, it's quite convinient.

Usually, we can't disable two clusters at the same time for any news feed, that means the requests to that feed will be send to nowhere. And we don't want to do that accidentally. What if we did?

Then the feed row will be as "bloody red" as bloody margarita cocktail. And you probably won't miss that.

And we log all the sensitive operations on NewsHQ dashboard, so we can find out "who take what action at what time"?


#### Shared Search Server / Alerts look up page

Like I said, previously alerting folks need to run python scripts to get alerts information for a specific client. 

This page give you all the alerts created by any client. All you need to do is input the client's username and serial number.

And if you want to look at the specific information about one alert, just click the "search UUID".

And again, you can modify url to get the alerting information directly.

Example : http://news-hq.factset.io/services/sss/alertinfo?username=TDIAL&userserial=FDS&env=PRODUCTION



#### Elasticsearch page











