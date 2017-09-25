# Why NewsHQ ?

There are inevitably times when things break, it could be related to hardware/network/project issues.  A dashboard that monitors our servers/processes can help us spot issues before clients do, or even better prevent those issues from happening.  And if something bad really happens, it also helps us track down the issue faster.

##### NewsHQ bring better troubleshooting tools
While, you may want to ask, why spend time building a new dashboard? Doesn't FactSet already have monster charts and other tools/platforms already?  Or why not just use an open source one?  Well, one primary reason is that those platforms do a decent job,  while they barely offer any team/project-specific customizations.  The consequence is that we still need to build different tools (python scripts, webpages) to help us perform regular operations. And these tools are scattered around everywhere, they could be in perforce, github, and they are even  stored in people's local directories. NewsHQ is a platform to integrate all these tools as well as bring more troubleshooting features. What's better, it has centralized log to audit those operations.

##### NewsHQ bring better metrics
Other problems with those platforms is that they are not easy to use, or lack the metrics and features our own team need. NewsHQ lets us choose whatever metrics we want to use, which is more effective because different teams and different projects need different types of metrics. Moreover, we can use a wide range of interactive charts and tubulars to display our metrics. And we won't get the flexibility from those platforms, they only offer predefined charts and tubulars.

# Demo

### Home page

The left side is "System Overview". It has the process heatmap which lists all the hosts and running processes on them.
Each small square represents a process, "green" means the process is running, "red" means it is down.
When your mouse hover over any small square, it will show the process name. After you  click it, a new tab will be open and direct you to the corresponding process page. Each process page can be cunstomized by monitoring different metrics(process responding time, latency or throughput), and right now by default, the uptime/downtime is shown up there.

On the top of right side, we have “Recent Activity” section, which is a timeline of all our rpd states.
You can filter the rpd by environment or status as well as using the dropdown filter.
For each rpd, you can see the "time last updated", status, title. assignee. 
Click the RPD link you will be redirected the the actual rpd feed.

On the bottome of the right side, we have a section shows you the important upcoming events like unix patching or Elasticsearch patching. 




### Host Page

This page brings us a very clear view of system realtime information on all our hosts.

These hosts are divided into 3 groups, production/staging/development.

You can click the section-header here to collapse and expand the section.

You can see the CPU/Memory/Disk/Inodes of all the hosts we are concerning about within this single page.

__These metrics are live data and refresh automatically. You don’t need to manually re-run dashboards or click refresh button.__

And when any metrics is changing, the small animation will make sure you won't miss that.

If metrics goes up to 50%, it will be highlighted as yellow, if goes up to 70%, the text will be highlighted as red.

What if you want to get more system information about a specific host?

Just lick any host here, it will guide you to a specifix host page which gives you a more detailed system information about that host.

All the information and charts on this page are  updated every 20 seconds.

On the top,  there are Fill Gauge CPU chart and other memory pie charts, they provide the realtime information. 

In the middle, we have CPU line chart and memory bar chart which give you realtime as well as historical metrics.

By simply click the zoom in links, you can get different time range, up to 24 hours.

By hovering above any data point, you can see a detailed information with a tiny tooltip.

__As you can see, NewsHQ has a wide range of charts and visualizations to present data  - from basic ones like line charts, bar charts to advanced ones like heatmap, gauge and bubble charts.__ We wrote these charts libraries from scratch with Javascript, which means we don't need to pay license fee to third-party charts libraries like Highchart.js. Any of our chart simply takes an array of data points to produce dynamic, interactive visualizations. They are very simple to be used and customized.

On the bottom, we have the status information of all the processes running on that host.

Click any process will direct you to the process page, which by default give you uptime/downtime information as well as the general process information. For example, the process's owner group and their notification email address. And you can go back to the host page by click the host link here.

### Services page

NewsHQ services page lists all the services we are concerning about.  Click any service tile will direct you to that service page, which lists all the operations you can do about that service there.

As you can see, NewsHQ has a very clear visual hierarchy layout. We don't need to give you a manual about it and you won't get lost here.  The URL also reveals the hierarhy as well,  you can consider the URL as the street sign which can guide you here and make the navigation easier.

#### NSS redirection page

News searching have two database clusters, A and B. If one of the data centers fails then we need a way to redirect traffic to the other data center. Previously, we need to ssh to the NSS boxes and modify the configuration files there and restart NSS instances.

Right now we have this redirection page which can talk to NSS instances directly and perform traffic switch over within as minimal as 2 clicks, and you switch the traffic for any news feed. It's just that simple. It is as simple as Amazon one-click payment.

We can also use the filter box to narrow down the news feeds we are looking for, it's quite convinient.

Usually, we can't disable two clusters at the same time for any news feed, that means the requests to that feed will be send to nowhere. And we don't want to do that accidentally. If you do that, the row will be highlighted as red before you click the submit button. And you probably won't miss that.

And we log all the sensitive operations on NewsHQ, so we can find out "who take what action at what time"?


#### Shared Search Server / Alerts look up page

Previously alerting folks need to run different python scripts to get alerts information for a specific client. 

This page give you all the alerts created by any client. All you need to do is input the client's username and serial number.

And if you want to look at the specific information about one alert, just click the "search UUID".

And again, you can modify url to get the alerting information directly.

Example : http://news-hq.factset.io/services/sss/alertinfo?username=TDIAL&userserial=FDS&env=PRODUCTION



#### Elasticsearch page

Elasticsearch page provide us with the primary information about our Elasticsearch clusters.
It talks to the Elasticsearch instances directly through their API.

Select the cluster from the dropdown list, and you can get a clear view about the cluster.

Indices tab lists all the indexes of the cluster , with the index information there. You can sort by any table headers as well as using the filter textbox. In fact, you can combine them as "filter-then-sort". 

You can get the setting information about a specific index on the setting tab.

If you wan to check the mapping information about an index or just a feed of that index, you can go to the mapping tab.

Cluster health tab give the JVM heap usage and CPU usage information of all the boxes in the selected cluster.

Finally, the statistics tab give you information about how many documents each news feed has in the cluster. You can even choose  any datetime range, even just seconds.

##### MATT page

NewsDistribution team and content team use MATT page regularlly to perform documents backfill and Elasticsearch update.
You can basically halt the documents indexing here. It talk to MATT service directly.

No need to go to details here.

### Stats page

##### Alerting Notifier page
The Monster team announced their new dashboarding engine, Grafana! With Grafana, users can make dashboards using existing Monster data. 

Here I am going to show you how easy it is to integrate Grafana chart into NewsHQ.
An iframe is an object that allows you to embed external content in your HTML page.

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


# In Summary

NewsHQ is our own dashboard helping us to stay on top of our operations by monitoring, tracking, and reporting real-time/historical metrics about our servers and processes. It also acts as a proxy to manage our processes/databases directly. Whether we're concerned about a major event or keeping an eye on day-to-day activities, we can use NewsHQ Dashboard to focus on what matters most to us.  We can display any metrics here, use any chart we prefer, customize in any way we want. 

Question?
















