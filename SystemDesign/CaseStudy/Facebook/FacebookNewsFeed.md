# Feed Basics

### What’s the job?

▪ Fetch recent activity from all your friends  
▪ Gather it in a central place  
▪ Group into stories  
▪ Rank stories by relevance  
▪ Send back results    

### The Scale

* 10 billion / day  Homepage views and feed queries  
* 60 ms  Average latency
* 99.999% Average query success rate


# Moving content to your friends

### Megafeed : Broadcast writes to your friends vs Multifeed : Multi-fetch and aggregate stories at read time

* Write amplification makes the storage needs expensive in Megafeed  
* Developing with read-time aggregation is flexible  
* Memory and network easier to engineer around  
* Fan-out reads can be bounded. Writes, often cannot  

# The Architecture

![alt](https://image.slidesharecdn.com/facebookarchitecture-110921042408-phpapp01/95/facebook-architecture-31-728.jpg)













