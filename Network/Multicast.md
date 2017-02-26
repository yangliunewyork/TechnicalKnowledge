In computer networking, multicast (one-to-many or many-to-many distribution) is __group communication__ where information is addressed to a group of destination computers simultaneously. Group communication may either be __application layer multicast__ or __network assisted multicast__, where the latter makes it possible for the source to efficiently send to the group in a single transmission. Copies are automatically created in other network elements, such as routers, switches and cellular network base stations, but only to network segments that currently contain members of the group.

Network assisted multicast may be implemented at the Data Link Layer using one-to-many addressing and switching such as Ethernet multicast addressing, Asynchronous Transfer Mode (ATM) point-to-multipoint virtual circuits (P2MP) or Infiniband multicast. Network assisted multicast may also be implemented at the Internet layer using IP multicast. In IP multicast the implementation of the multicast concept occurs at the IP routing level, where routers create optimal distribution paths for datagrams sent to a multicast destination address.

Multicast is often employed in Internet Protocol (IP) applications of streaming media, such as Internet television scheduled content (but not media-on-demand) and multipoint videoconferencing, but also for ghost distribution of backup disk images to multiple computers simultaneously.

Multicast should not be confused with physical layer point-to-multipoint communication.

## IP multicast
IP multicast is a technique for one-to-many communication over an IP infrastructure in a network. The destination nodes send join and leave messages, for example in the case of Internet television when the user changes from one TV channel to another. IP multicast scales to a larger receiver population by not requiring prior knowledge of who or how many receivers there are. Multicast uses network infrastructure efficiently by requiring the source to send a packet only once, even if it needs to be delivered to a large number of receivers. The nodes in the network take care of replicating the packet to reach multiple receivers only when necessary.

The most common transport layer protocol to use multicast addressing is User Datagram Protocol (UDP). By its nature, UDP is not reliable—messages may be lost or delivered out of order. By adding loss detection and re-transmission mechanisms, reliable multicast has been implemented on top of UDP or IP by various middleware products, e.g. those that implement the Real-Time Publish-Subscribe (RTPS) Protocol of the Object Management Group (OMG) Data Distribution Service (DDS) standard, as well as by special transport protocols such as Pragmatic General Multicast (PGM).

IP multicast is widely deployed in enterprises, commercial stock exchanges, and multimedia content delivery networks. A common enterprise use of IP multicast is for IPTV applications such as distance learning and televised company meetings.

