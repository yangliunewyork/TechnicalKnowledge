# Why NewsHQ ?
One year ago, Tom, Guang and I were tracking a searching related issue reported by client.  We log into our searching boxes, ran top commands on each of them to check system summary information, grep searching log to see any eccentric behaviors， check monster chars for historical information.
During lunchtime, Tom said that he saw a dashboard somewhere online and think it was cool, and he showed to me after lunch. I saw that online dashboard and  said, “it is quite good and it will be cool if monster can be as simple as this ”. And then Tom asked, “Yang, do you want to be a full-stack engineer?” And I said, “Tom, I was an Asp.net developer before join FactSet”, and Tom said, “that’s even better”.
And that’s how we begin to work on NewsHQ.
NewsHQ is a dashboard that help us to monitor our applications and databases' mission critical key performance metrics like uptime, load time, response time, cpu usage, memory usage and the multitude of other components that help us to deliver a stable end user experience to our clients.

There are inevitably times when things break, when hardware degrade.  A dashboard that monitors your core processes - even just a simple one - can mean the difference between spotting an issue before clients do,   and finding a mountain of support tickets from angry customers. 

Being  a passive, reactive engineers who sometimes get pushed around by system issues, clients’ complaints is not fun at all. You may be working on developing features that our clients desperately want, our product managers are looking forward to and you may even already gave them an estimated delivery time, and then “boom”, something is not working. And you have to do a “context switch” and  jump on to analyze the issues. 

### What can NewsHQ bring to us?

It save us from tedious manual operation work.
It reduce our time to track issues.
It let us know what is not working and also what is working BUT not working WELL.
It integrates our scattered around operation tools into one centralized stop.
It bring better processes/system analysis tools for us to find out what can be improved and what must be fixed.
It help us from being passive, reactive to be proactive and more productive.
It help us to make patching smooth.


# Demo

NewsHQ has a very clear visual hierarchy on each page.

### Home page

The left panel is "System Overview". It has the process heatmap which lists all the boxes and running process on them.
Each small square represents a process, "green" means it is running, "red" means it is down.
When your mouse hover the small square, it will show the process name. And once you click it, a new tab will be open and direct you to the corresponding process page. Each process page can be cunstomized by monitoring different metrics, and by default, the uptime/downtime is shown up there.


