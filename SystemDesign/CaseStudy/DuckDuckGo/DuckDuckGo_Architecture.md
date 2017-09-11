* http://highscalability.com/blog/2013/1/28/duckduckgo-architecture-1-million-deep-searches-a-day-and-gr.html

Innovative search engine upstart DuckDuckGo had 30 million searches in February 2012 and averages over 1 million searches a day. It’s being positioned by super investor Fred Wilson as a clean, private, impartial and fast search engine.

Choosing DuckDuckGo can be thought of as not just a technical choice, but a vote for revolution. In an age when knowing your essence is not about about love or friendship, but about more effectively selling you to advertisers, DDG is positioning themselves as the do not track alternative, keepers of the privacy flame. You will still be monetized of course, but in a more civilized and anonymous way. 

Pushing privacy is a good way to carve out a competitive niche against Google et al, as by definition they can never compete on privacy. I get that. But what I found most compelling is DDG’s strong vision of a crowdsourced network of plugins giving broader search coverage by tying an army of vertical data suppliers into their search framework. For example, there's a specialized Lego plugin for searching against a complete Lego database. Use the name of a spice in your search query, for example, and DDG will recognize it and may trigger a deeper search against a highly tuned recipe database. Many different plugins can be triggered on each search and it’s all handled in real-time.

Can’t searching the Open Web provide all this data? No really. This is structured data with semantics. Not an HTML page. You need a search engine that’s capable of categorizing, mapping, merging, filtering, prioritizing, searching, formatting, and disambiguating richer data sets and you can’t do that with a keyword search. You need the kind of smarts DDG has built into their search engine. One problem of course is now that data has become valuable many grown ups don’t want to share anymore. 

Being ad supported puts DDG in a tricky position. Targeted ads are more lucrative, but ironically DDG’s do not track policies means they can’t gather targeting data. Yet that’s also a selling point for those interested in privacy. But as search is famously intent driven, DDG’s technology of categorizing queries and matching them against data sources is already a form of high value targeting. 

# Stats

* 30 million searches in February 2012  
* Averages over 1 million searches a day  
* 12M API requests per day  

# The Platform

```
EC2
Ubuntu
Perl & CPAN
Server Density - monitoring
Solr
PostgreSQL
Memcached
Bucardo - asynchronous PostgreSQL replication system
Global Traffic Director - load balancing between regions
Nginx
getFavicon - serves favicons
daemontools - free tools for managing Unix services
Git
Asana - project management.
HipChat - internal communication
Yammer
JavaScript
YUI (moving to jQuery)
```




