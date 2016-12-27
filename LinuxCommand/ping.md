###　About PING
PING (Packet INternet Groper) command is the best way to test connectivity between two nodes. Whether it is Local Area Network (LAN) or Wide Area Network (WAN). Ping use ICMP (Internet Control Message Protocol) to communicate to other devices. You can ping host name of ip address using below command.

ping uses the ICMP protocol’s mandatory ECHO_REQUEST datagram to elicit an ICMP ECHO_RESPONSE from a host or gateway. ECHO_REQUEST datagrams (“pings”) have an IP and ICMP header, followed by a struct timeval and then an arbitrary number of “pad” bytes used to fill out the packet.

### Usage
1. Send 10 packets to google.com
```
$ ping -c 10 google.com
PING google.com (172.217.4.46) 56(84) bytes of data.
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=1 ttl=55 time=3.91 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=2 ttl=55 time=3.79 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=3 ttl=55 time=3.82 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=5 ttl=55 time=3.72 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=6 ttl=55 time=3.81 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=7 ttl=55 time=3.74 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=8 ttl=55 time=3.77 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=9 ttl=55 time=3.74 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=10 ttl=55 time=3.83 ms

--- google.com ping statistics ---
10 packets transmitted, 9 received, 10% packet loss, time 10013ms
rtt min/avg/max/mdev = 3.726/3.796/3.919/0.099 ms

```

2. Send 10 packets, waiting for 0.5 second before sending next packet
```
$ ping -c 10 -i 0.5 google.com
PING google.com (172.217.4.46) 56(84) bytes of data.
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=1 ttl=55 time=3.92 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=2 ttl=55 time=3.81 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=3 ttl=55 time=3.91 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=4 ttl=55 time=3.89 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=5 ttl=55 time=3.83 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=6 ttl=55 time=3.89 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=7 ttl=55 time=3.84 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=8 ttl=55 time=3.92 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=9 ttl=55 time=3.81 ms
64 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=10 ttl=55 time=3.84 ms

--- google.com ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 4517ms
rtt min/avg/max/mdev = 3.810/3.871/3.929/0.076 ms
```
3.Change Ping Packet Size

Example: Change the default packet size from 56 to 100.
```
$ ping -c 5 -i 0.5 -s 100 google.com
PING google.com (172.217.4.46) 100(128) bytes of data.
72 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=1 ttl=55 (truncated)
72 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=2 ttl=55 (truncated)
72 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=3 ttl=55 (truncated)
72 bytes from lga15s46-in-f14.1e100.net (172.217.4.46): icmp_seq=4 ttl=55 (truncated)

--- google.com ping statistics ---
5 packets transmitted, 4 received, 20% packet loss, time 2504ms
rtt min/avg/max/mdev = 3.817/3.837/3.866/0.047 ms
```
**Note : Ping Bytes Sent = Ping Packet Size + Ping Header Packet Size (28 bytes)**
