### Round-trip time (RTT)
Round-trip time (RTT), also called round-trip delay, is the time required for a signal pulse or packet to travel from a specific source to a specific destination and back again. In this context, the source is the computer initiating the signal and the destination is a remote computer or system that receives the signal and retransmits it.

On the Internet, an end user can determine the RTT to and from an IP (Internet Protocol) address by pinging that address. The result depends on various factors including:
* The data transfer rate of the source's Internet connection
* The nature of the transmission medium (copper, optical fiber, wireless or satellite)
* The physical distance between the source and the destination
* The number of nodes between the source and the destination
* The amount of traffic on the LAN (local area network) to which the end user is connected
* The number of other requests being handled by intermediate nodes and the remote server
* The speed with which intermediate nodes and the remote server function
* The presence of interference in the circuit.

In a network, particularly a WAN (wide-area network) or the Internet, RTT is one of several factors affecting latency, which is the time between a request for data and the complete return or display of that data. The RTT can range from a few milliseconds (thousandths of a second) under ideal conditions between closely spaced points to several seconds under adverse conditions between points separated by a large distance.A theoretical minimum is imposed on the RTT because it can never be less than the total length of time the signals spend propagating in or through the transmission media.

### What is Initial RTT, and why bother?

Initial RTT is the round trip time that is determined by looking at the TCP Three Way Handshake. It is good to know the base latency of the connection, and the packets of the handshake are very small. This means that they have a good chance of getting through at maximum speed, because larger packets are often buffered somewhere before being passed on to the next hop. Another point is that the handshake packets are handled by the TCP stack of the operating system, so there is no application interference/delay at all. As  a bonus, each TCP session starts with these packets, so they’re easy to find (if the capture was started early enough to catch it, of course).

Knowing Initial RTT is necessary to calculate the optimum TCP window size of a connection, in case it is performing poorly due to bad window sizes. It is also important to know when analyzing packet loss and out of order packets, because it helps to determine if the sender could even have known about packet loss. Otherwise a packet marked as retransmission could just be an out of order arrival.

### How to check RTT
```
$ ping -c 10 -i 0.5 -s 16  google.com
PING google.com (172.217.4.46) 16(44) bytes of data.
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=1 ttl=55 time=3.82 ms
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=2 ttl=55 time=3.94 ms
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=3 ttl=55 time=3.80 ms
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=4 ttl=55 time=3.83 ms
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=5 ttl=55 time=3.82 ms
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=6 ttl=55 time=3.81 ms
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=7 ttl=55 time=3.79 ms
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=8 ttl=55 time=3.81 ms
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=9 ttl=55 time=3.82 ms
24 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=10 ttl=55 time=3.78 ms

--- google.com ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 4516ms
rtt min/avg/max/mdev = 3.789/3.826/3.941/0.092 ms

```
