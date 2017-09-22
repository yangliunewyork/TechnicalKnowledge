# Why NewsHQ ?

Being  a passive, reactive engineer who gets pushed around by system/processes issues, clients’ complaints is not fun at all. You may be working on developing features that our clients desperately want, our product managers are looking forward to and you may even already gave them an estimated delivery time, and then “boom”, something is not working. And you have to do a “context switch” and  jump on to analyze the issues. That happens a lot, happens to me, happens to you as well.

We can't sit there and pray nothing is going to break, that's not going to happen.

There are inevitably times when things break, when hardware degrade.  A dashboard that monitors your servers/processes can mean the difference between spotting an issue before clients do,  or prevent those issues from happenning.  And if something bad happens, it also help you track down the issue faster.

A dashboard report helps us monitor and track our servers/processes performance to stay in control of our business at all times. You cannot correct or improve something that cannot be effectively identified and measured. Without effective metrics/KPIs, managers/engineers may not be able to respond to situations correctly and will end up spending a lot of time to anaylyze and debugging issues. And also keeping the project team headed in the right direction cannot be done easily without effective identification and measurement of metrics.

Nurturing daily data monitoring habits has big results. The future of project management may very well be metric-driven project management.

More and more companies including FactSet often develop and maintain different tools/platforms to query and visualize the metrics. For example, FactSet Monster or CLP. However, the problem is that sometimes these centralized platforms are not easy to use, or lack the features/metrics our own team need. To simply put, you can use these platforms only in a general way but they are not customized for you and you don't own them at all. Since these centrailized platforms aim at provide generic usage company-wide, they have redundant information you don't care at all. Let's admit it, you only use monster page when something suspicious happens. That's not we call "daily data monitoring".

And NewsHQ is our own dashboard delicating to serve News team only. You can display any metrics here, use any chart you prefer, customize in any way you want. News team is its only owner, and NewsHQ only work for us. 

NewsHQ is a dashboard that help us to stay on top of our operations by monitoring, tracking, and reporting real-time/historical key metrics about our servers and processes. Whether you're concerned about a major event or keeping an eye on day-to-day activities, you can use NewsHQ Dashboard to focus on what matters most to you. 


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
Each small square represents a process, "green" means the process is running, "red" means it is down.
When your mouse hover over any small square, it will show the process name. And you can click it, a new tab will be open and direct you to the corresponding process page. Each process page can be cunstomized by monitoring different metrics(process responding time, latency or throughput), and by default, the uptime/downtime is shown up there.

On the right panel, we have "Recent Activity" and "Upcoming Events", 


### Host Page

We have a slogan for host page, which is "every box in one page". It is very clear and straightforward.

You can see the CPU/Memory/Disk/Inodes of all the boxes we are concerning about within one page.

And when any value is changing, the tiny animation will make sure you won't miss that.

__NewsHQ provide these real-time key performance indicators  and metrics that show live data and refresh automatically. You don’t need to manually re-run dashboards or sync data every time your data updates.They just update automatically.__

We have 3 health status for all the metrics here. Other than the normal status, if metrics goes up to 50%, it will be shown as in orange text, if goes up to 70%, the text will be highlighted as red.

This page brings  us a very clear system realtime summary on all our boxes. It is an example to show that how NewsHQ can help us to be more proactive.

What if you want to get more system information about a specific host?

Just lick any host here, it will guide you to a specifix host page which give you a more detailed system information about that host.

All the information and charts on this page are  updated every 20 seconds.

On the top,  there are Fill Gauge CPU chart and other memory pie charts. 

And then we have CPU line chart and memory bar chart which give you realtime as well as historical information.

By simply clicking the zoom in links, you can get different datetime range, up to 24 hours.

By hovering above any data point, you can see a detailed information with a tiny tooltip.

__NewsHQ has a wide range of charts and visualizations to present data  - from basic ones like line, area, scatter plot to advanced ones like heatmap, gauge and bubble charts.__ We wrote these charts libraries from scratch with D3.js, which means we don't need to pay license fee to third-party charts libraries like Highchart. And no matter what kind of chart you see online, we can write a smilar or even a better one. Any of our chart simply take an array of key-value pairs for x-axis and y-axis data to produce dynamic, interactive visualizations. They are very simple to be used and customized.

On the bottom, we have the status information of all the processes running on that host.

Click any process will direct you to the process page, which by default give you uptime/downtime information as well as the general process information. For example, the process's owner group and their notification email address. 

### Services page

News HQ services page lists all the services we are concerning about.  Click any service tile will direct you to that service page, which lists all the operations you can do about that service there.

As you can see, NewsHQ has a very clear visual hierarchy layout. We don't need to give you a manual about it and you won't get lost here. And NewsHQ's URL reveals the hierarhy as well,  you can consider the URL as the street sign which can guide you here and make the navigation easier.


#### NSS redirection page

News searching have two database clusters, A and B. If one of the data centers fails then we need a way to redirect traffic to the other data center. Previously, we need to ssh to the NSS boxes and modify the configuration files there and restart NSS instances.

Right now we have this redirection page which can perform traffic switch over within as minimal as 2 clicks, and can be grandular down to news feed basis. It's just that simple. It is as simple as Amazon one-click payment. Maybe we should file a patent for this too?

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

Elasticsearch page provide us with the primary information about our Elasticsearch clusters.
It talks to the Elasticsearch instances directly through their API.

Select the cluster from the dropdown list, and you can get a clear view about the cluster.

Indices tab lists all the indexes of the cluster , with the index information there. You can sort by any table headers as well as using the filter textbox. In fact, you can combime them as "filter-then-sort". 


You can get the setting information about a specific index on the setting tab.

If you wan to check the mapping information about an index or just a feed, you can go to the mapping tab.

Cluster health tab give the JVM heap usage and CPU usage information of all the boxes in the selected cluster.

Finally, the statistics tab give you information about how many documents each news feed has in the cluster. You can even choose a any datetime range, even just seconds.

##### MATT page

NewsDistribution team and content team use MATT page regularlly to perform documents backfill and Elasticsearch update.
You can basically halt the documents indexing here. It talk to MATT service directly.

No need to go to details here.

### Stats page

##### Alerting Notifier page
The Monster team announced the next generation charting and dashboarding engine, Grafana! With Grafana, users can make dashboards using existing Monster data, and aggregate, pivot and dissect data in ways not previously possible. 

Here I am going to show you how easy it is to integrate Grafana into NewsHQ.

```
<div class="container-fluid">
    <div class="col-lg-12">
        <iframe src="http://grafana.factset.io/dashboard/db/notifier" width="100%" height="1000" frameborder="0"></iframe>
    </div>
</div>
```

##### Searching MATT page

On this page, you can get in-depth information about documents being processed by MATT process.

You can see the queue size, how many bad files, how many attemps have been made for each document on both Elasticsearch queue and MySQL queue.

Of course, you can sort the table by any headers as well.

We also have a simple filter here.



















