## Source
* http://www.erg.abdn.ac.uk/users/gorry/course/intro-pages/uni-b-mcast.html
* https://www.quora.com/What-is-the-difference-between-broadcasting-and-multicasting
* http://www.utilizewindows.com/the-difference-between-unicast-multicast-and-broadcast-messages/
* https://www.esds.co.in/blog/difference-between-unicast-broadcast-and-multicast/#sthash.bqSQSJOr.dpbs

## What is broadcasting ?
In telecommunication and information theory, broadcasting is a method of transferring a message to all recipients simultaneously. Broadcasting can be performed as a high level operation in a program, for example broadcasting Message Passing Interface, or it may be a low level networking operation, for example broadcasting on Ethernet.

All-to-all communication is a computer communication method in which each sender transmits messages to all receivers within a group. This contrasts with the point-to-point method in which each sender communicates with one receiver.

## Overview
In computer networking, broadcasting refers to transmitting a packet that will be received by every device on the network. In practice, the scope of the broadcast is limited to a broadcast domain. Broadcasting a message is in contrast to __unicast__ addressing in which a host sends datagrams to another single host identified by a unique IP address.

Broadcasting is the most general communication method, and is also the most intensive in the sense that a large number of messages are required.

Broadcasting may be performed as "all scatter" in which each sender performs its own scatter in which the messages are distinct for each receiver, or "all broadcast" in which they are the same.

__Broadcasting is largely confined to local area network (LAN) technologies, most notably Ethernet and token ring, where the performance impact of broadcasting is not as large as it would be in a wide area network.__

The successor to Internet Protocol Version 4 (IPv4), IPv6 also does not implement the broadcast method, so as to prevent disturbing all nodes in a network when only a few may be interested in a particular service. Instead it relies on multicast addressing - a conceptually similar one-to-many routing methodology. However, multicasting limits the pool of receivers to those that join a specific multicast receiver group.

Broadcasting may be abused to perform a type of DoS-attack known as a Smurf attack. The attacker sends fake ping requests with the source IP-address of the victim computer. The victim computer is flooded by the replies from all computers in the domain.

## Unicast vs Broadcast vs Multicase

#### Unicast

Unicast is the term used to describe communication where a piece of information is sent from one point to another point. In this case there is just one sender, and one receiver.

Unicast transmission, in which a packet is sent from a single source to a specified destination, is still the predominant form of transmission on LANs and within the Internet. All LANs (e.g. Ethernet) and IP networks support the unicast transfer mode, and most users are familiar with the standard unicast applications (e.g. http, smtp, ftp and telnet) which employ the TCP transport protocol.

#### Broadcast

Broadcast is the term used to describe communication where a piece of information is sent from one point to all other points. In this case there is just one sender, but the information is sent to all connected receivers.

Broadcast transmission is supported on most LANs (e.g. Ethernet), and may be used to send the same message to all computers on the LAN (e.g. the address resolution protocol (arp) uses this to send an address resolution query to all computers on a LAN). Network layer protocols (such as IPv4) also support a form of broadcast that allows the same packet to be sent to every system in a logical network (in IPv4 this consists of the IP network ID and an all 1's host number).

#### Multicast

Multicast is the term used to describe communication where a piece of information is sent from one or more points to a set of other points. In this case there is may be one or more senders, and the information is distributed to a set of receivers (theer may be no receivers, or any other number of receivers).

One example of an application which may use multicast is a video server sending out networked TV channels. Simultaneous delivery of high quality video to each of a large number of delivery platforms will exhaust the capability of even a high bandwidth network with a powerful video clip server. This poses a major salability issue for applications which required sustained high bandwidth. One way to significantly ease scaling to larger groups of clients is to employ multicast networking.

Multicasting is the networking technique of delivering the same packet simultaneously to a group of clients. IP multicast provides dynamic many-to-many connectivity between a set of senders (at least 1) and a group of receivers. The format of IP multicast packets is identical to that of unicast packets and is distinguished only by the use of a special class of destination address (class D IPv4 address) which denotes a specific multicast group. Since TCP supports only the unicast mode, multicast applications must use the UDP transport protocol.

Unlike broadcast transmission (which is used on some local area networks), multicast clients receive a stream of packets only if they have previously elect to do so (by joining the specific multicast group address). Membership of a group is dynamic and controlled by the receivers (in turn informed by the local client applications). The routers in a multicast network learn which sub-networks have active clients for each multicast group and attempt to minimise the transmission of packets across parts of the network for which there are no active clients.

The multicast mode is useful if a group of clients require a common set of data at the same time, or when the clients are able to receive and store (cache) common data until needed. Where there is a common need for the same data required by a group of clients, multicast transmission may provide significant bandwidth savings (up to 1/N of the bandwidth compared to N separate unicast clients).

The majority of installed LANs (e.g. Ethernet) are able to support the multicast transmission mode. Shared LANs (using hubs/repeaters) inherently support multicast, since all packets reach all network interface cards connected to the LAN. The earliest LAN network interface cards had no specific support for multicast and introduced a big performance penalty by forcing the adaptor to receive all packets (promiscuous mode) and perform software filtering to remove all unwanted packets. Most modern network interface cards implement a set of multicast filters, relieving the host of the burden of performing excessive software filtering.


Simply put:
------------------------------------------------------------
| TYPE      | ASSOCIATIONS     | SCOPE           | EXAMPLE |
------------------------------------------------------------
| Unicast   | 1 to 1           | Whole network   | HTTP    | 
------------------------------------------------------------
| Broadcast | 1 to Many        | Subnet          | ARP     |
------------------------------------------------------------
| Multicast | One/Many to Many | Defined horizon | SLP     |
------------------------------------------------------------
| Anycast   | Many to Few      | Whole network   | 6to4    |
------------------------------------------------------------
Unicast is used when two network nodes need to talk to each other. This is pretty straight forward, so I'm not going to spend much time on it. TCP by definition is a Unicast protocol, except when there is Anycast involved (more on that below).

When you need to have more than two nodes see the traffic, you have options.

If all of the nodes are on the same subnet, then broadcast becomes a viable solution. All nodes on the subnet will see all traffic. There is no TCP-like connection state maintained. Broadcast is a layer 2 feature in the Ethernet protocol, and also a layer 3 feature in IPv4.

Multicast is like a broadcast that can cross subnets, but unlike broadcast does not touch all nodes. Nodes have to subscribe to a multicast group to receive information. Multicast protocols are usually UDP protocols, since by definition no connection-state can be maintained. Nodes transmitting data to a multicast group do not know what nodes are receiving. By default, Internet routers do not pass Multicast traffic. For internal use, though, it is perfectly allowed; thus, "Defined horizon" in the above chart. Multicast is a layer 3 feature of IPv4 & IPv6.

To use anycast you advertise the same network in multiple spots of the Internet, and rely on shortest-path calculations to funnel clients to your multiple locations. As far the network nodes themselves are concerned, they're using a unicast connection to talk to your anycasted nodes. For more on Anycast, try: What is "anycast" and how is it helpful?. Anycast is also a layer 3 feature, but is a function of how route-coalescing happens.

