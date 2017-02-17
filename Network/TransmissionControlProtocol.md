## What is TCP?
The Transmission Control Protocol (TCP) is one of the main protocols of the Internet protocol suite. It originated in the initial network implementation in which it complemented the Internet Protocol (IP). Therefore, the entire suite is commonly referred to as TCP/IP. TCP provides reliable, ordered, and error-checked delivery of a stream of octets between applications running on hosts communicating by an IP network. Major Internet applications such as the World Wide Web, email, remote administration, and file transfer rely on TCP. Applications that do not require reliable data stream service may use the User Datagram Protocol (UDP), which provides a connectionless datagram service that emphasizes reduced latency over reliability.

## Network function
The Transmission Control Protocol provides a communication service at an intermediate level between an application program and the Internet Protocol. It provides host-to-host connectivity at the __Transport Layer__ of the Internet model. An application does not need to know the particular mechanisms for sending data via a link to another host, such as the required packet fragmentation on the transmission medium. At the transport layer, the protocol handles all handshaking and transmission details and just presents an abstraction of the network connection to the application.

At the lower levels of the protocol stack, due to network congestion, traffic load balancing, or other unpredictable network behaviour, IP packets may be lost, duplicated, or __delivered out of order__. TCP detects these problems, requests __re-transmission__ of lost data, rearranges out-of-order data and even helps minimise network congestion to reduce the occurrence of the other problems. If the data still remains undelivered, its source is notified of this failure. Once the TCP receiver has reassembled the sequence of octets originally transmitted, it passes them to the receiving application. Thus, TCP abstracts the application's communication from the underlying networking details.

TCP is used extensively by many applications available by internet, including the World Wide Web (WWW), E-mail, File Transfer Protocol, Secure Shell, peer-to-peer file sharing, and streaming media applications.

__TCP is optimised for accurate delivery rather than timely delivery. Therefore, TCP sometimes incurs relatively long delays (on the order of seconds) while waiting for out-of-order messages or re-transmissions of lost messages. It is not particularly suitable for real-time applications such as Voice over IP.__ For such applications, protocols like the Real-time Transport Protocol (RTP) operating over the User Datagram Protocol (UDP) are usually recommended instead.

__TCP is a reliable stream delivery service which guarantees that all bytes received will be identical with bytes sent and in the correct order.__ Since packet transfer by many networks is not reliable, a technique known as 'positive acknowledgement with re-transmission' is used to guarantee reliability of packet transfers. This fundamental technique requires the receiver to respond with an acknowledgement message as it receives the data. The sender keeps a record of each packet it sends and maintains a timer from when the packet was sent. The sender re-transmits a packet if the timer expires before the message has been acknowledged. The timer is needed in case a packet gets lost or corrupted.

While IP handles actual delivery of the data, TCP keeps track of 'segments' - the individual units of data transmission that a message is divided into for efficient routing through the network. For example, when an HTML file is sent from a web server, the TCP software layer of that server divides the sequence of file octets into segments and forwards them individually to the IP software layer (Internet Layer). The Internet Layer encapsulates each TCP segment into an IP packet by adding a header that includes (among other data) the destination IP address. When the client program on the destination computer receives them, the TCP layer (Transport Layer) re-assembles the individual segments and ensures they are correctly ordered and error-free as it streams them to an application.


## Connection establishment
To establish a connection, TCP uses a __three-way handshake__. Before a client attempts to connect with a server, the server must first bind to and listen at a port to open it up for connections: this is called a passive open. Once the passive open is established, a client may initiate an active open. To establish a connection, the three-way (or 3-step) handshake occurs:

* SYN: The active open is performed by the client sending a SYN to the server. The client sets the segment's sequence number to a random value A.
* SYN-ACK: In response, the server replies with a SYN-ACK. The acknowledgment number is set to one more than the received sequence number i.e. A+1, and the sequence number that the server chooses for the packet is another random number, B.
* ACK: Finally, the client sends an ACK back to the server. The sequence number is set to the received acknowledgement value i.e. A+1, and the acknowledgement number is set to one more than the received sequence number i.e. B+1.
At this point, both the client and server have received an acknowledgment of the connection. The steps 1, 2 establish the connection parameter (sequence number) for one direction and it is acknowledged. The steps 2, 3 establish the connection parameter (sequence number) for the other direction and it is acknowledged. With these, a full-duplex communication is established.

## Data transfer
There are a few key features that set TCP apart from User Datagram Protocol:

* Ordered data transfer — the destination host rearranges according to sequence number
* Retransmission of lost packets — any cumulative stream not acknowledged is retransmitted
* Error-free data transfer
* Flow control — limits the rate a sender transfers data to guarantee reliable delivery. The receiver continually hints the sender on how much data can be received (controlled by the sliding window). When the receiving host's buffer fills, the next acknowledgment contains a 0 in the window size, to stop transfer and allow the data in the buffer to be processed.
* Congestion control

#### What is the reason behind Youtube using TCP and not UDP?
Video streaming meets with TCP in their nature. First, video streaming adopts pre-fetching and buffering to achieve smooth play-out. TCP provides such (network) buffer, as well as the reliable transmission guarantee for no loss of frame (a frame could still miss the play-out deadline and discarded, however). Second, TCP's bandwidth probing and congestion control will attempt to use all of the available bandwidth between server and client, fetching content as quick as possible while being friendly to other (TCP) traffic on the same links.

However, live streaming opts in UDP, because little pre-fetching can be done and buffering will add delay to the video play-out. Since UDP serves only the most basic transport layer functionality, it is used jointly with other application layer protocols such as RTSP  to do video streaming. Firewalls (from enterprise, ISPs) dislike these protocols, making video traffic difficult to traverse through or being throttled.

In order to deliver videos, platforms adopt/rent Content Delievery Networks (CDN). Most of the CDN servers (e.g. Akamai's) are configured to support web services as their primary course. Thus, streaming video over HTTP works out the box without setting up dedicated servers, and most of the firewalls won't block HTTP traffic. In fact, Dynamic Adaptive Streaming over HTTP (DASH) has become a common practice. Although in theory HTTP can be encapsulated other protocols, they still need to provide reliable transfer, which again precludes UDP. Notably, for companies such as Google and Netflix, they build their own CDN.
