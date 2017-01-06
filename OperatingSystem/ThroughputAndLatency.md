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