## Difference, example of throughput and latency

* Latency is the time required to perform some action or to produce some result. Latency is measured in units of time -- hours, minutes, seconds, nanoseconds or clock periods.
* Throughput is the number of such actions executed or results produced per unit of time. This is measured in units of whatever is being produced (cars, motorcycles, I/O samples, memory words, iterations) per unit of time.

Many systems can be characterized as dominated either by throughput limitations or by latency limitations in terms of end-user utility or experience.Latency and throughput are not necessarily correlated, because of data density. A system that has high latency but can transfer a huge amount of data can still have higher throughput than a low-latency system.

Example:
An assembly line is manufacturing cars. It takes eight hours to manufacture a car and that the factory produces one hundred and twenty cars per day.
The latency is: 8 hours.
The throughput is: 120 cars / day or 5 cars / hour.


#### Bandwidth vs Throughput
Bandwidth is the raw capability of a communications channel to move data through that channel. Typically measured in bits or bytes per second (or some, possibly large, multiple thereof). May also be measured in hertz.

Throughput is the total capability of a processing system to move product through that system. It can be measured in any quantifiable unit and may be measured in units relevant to the business process that the system supports (e.g. transactions or documents) rather than in technical units. 

Bandwidth is but one of several factors that will limit the throughput of a system. Others include things like processing speed, latency, jitter, and reliability.


### Network Latency and Throughput

Here's what Glenn Paulley has to say on the subject in the "Measuring network performance" section of Optimizing Adaptive Server Anywhere Performance Over a WAN:

Latency and throughput can be used together to describe the performance of a network. Latency refers to the time delay between when one machine sends a packet of data and the second machine receives the data (for example, if the second machine receives the data 10 ms later than the first machine sent it, the latency is 10 ms). Throughput refers to the amount of data that can be transferred in a given time (for example, if a one machine sends 1000 KB of data, and it takes 5 seconds for all of it to be received by the second machine, the throughput is 200 KB/s). On a LAN, latency is typically less than 1 ms, and throughput is typically more than 1 MB/s. On a WAN, the latency is typically significantly higher (perhaps 5 ms to 500 ms), and the throughput is typically significantly lower (perhaps 4 KB/s to 200 KB/s).

You can measure network latency between two machines by the round trip time reported by the system’s ping utility. The round trip time is the latency to transfer data from one machine to a second machine plus the latency to transfer data from the second machine back to the first machine. You can measure network throughput by copying a file of a known size of at least 200 KB from one machine to a second machine and timing the copy. This copy could be performed as a regular file copy, using FTP, or by downloading a file using an Internet browser.

To get reasonable Adaptive Server Anywhere performance on a network that has high latency, but reasonable throughput, the number of requests made by the client must be minimized. If a network has reasonable latency, but low throughput, the amount of data transferred between the client and server must be minimized.

### Example

Latency – In simplest terms this is Remote Response time. For instance, you want to invoke a web service or access a web page. Apart from the processing time that is needed on the server to process your request, there is a delay involved for your request to reach to server. While referring to Latency, it’s that delay we are talking about. This becomes a big issue for a remote data center which is hosting your service/page. Imagine your data center in US, and accessing it from India. If ignored, latency can trigger your SLA’s. Though it’s quite difficult to improve latency it’s important to measure it. 

Throughput – transactions per second your application can handle (motivation / result of load testing). A typical enterprise application will have lots of users performing lots of different transactions. You should ensure that your application meets the required capacity of enterprise before it hits production. Load testing is the solution for that. Strategy here is to pick up a mix of transactions (frequent, critical, and intensive) and see how many pass successfully in an acceptable time frame governed by your SLAs. 
