## Principles of Network Applications
At the core of network application development is writing programs that run on different end systems and communicate with each other over the network. 

### Network Application Architectures
From the application developer’s perspective, the network architecture is fixed and provides a specific set of services to applications. The __application architecture__, on the other hand, is designed by the application developer and dictates how the application is structured over the various end systems. In choosing the application architecture, an application developer will likely draw on one of the two predominant architectural paradigms used in modern network applications: __the client-server architecture or the peer-to-peer (P2P) architecture__.

![alt](http://weblogs.foxite.com/photos/1000.257.6938.cs003.jpg)

In a __client-server architecture___, there is an __always-on host, called the server__, which services requests from many other hosts, called clients. A classic example is the Web application for which an always-on Web server services requests from browsers running on client hosts. When a Web server receives a request for an object from a client host, it responds by sending the requested object to the client host. Note that with the client-server architecture, clients do not directly communicate with each other; for example, in the Web application, two browsers do not directly communi- cate. Another characteristic of the client-server architecture is that the server has a fixed, well-known address, called an IP address. Because the server has a fixed, well-known address, and because the server is always on, a client can always contact the server by sending a packet to the server’s IP address. Some of the better-known applications with a client-server architecture include the Web, FTP, Telnet, and e-mail.

Often in a client-server application, a single-server host is incapable of keeping up with all the requests from clients. For example, a popular social-networking site can quickly become overwhelmed if it has only one server handling all of its requests. For this reason, a __data center__, housing a large number of hosts, is often used to create a powerful virtual server. A data center can have hundreds of thousands of servers, which must be powered and maintained. Additionally, the service providers must pay recurring interconnection and bandwidth costs for sending data from their data centers.

![alt](http://www.networkinginfoblog.com/contentsimages/Client-server%20architecture.JPG)

In a __P2P architecture__, there is minimal (or no) reliance on dedicated servers in data centers. Instead the application exploits direct communication between pairs of intermittently connected hosts, called peers. The peers are not owned by the service provider, but are instead desktops and laptops controlled by users, with most of the peers residing in homes, universities, and offices. Because the peers communicate without passing through a dedicated server, the architecture is called peer-to-peer. Many of today’s most popular and traffic-intensive applications are based on P2P architectures. These applications include file sharing (e.g., BitTorrent), peer-assisted download acceleration (e.g., Xunlei), Internet Telephony (e.g., Skype), and IPTV (e.g., Kankan and PPstream). 

One of the most compelling features of P2P architectures is their __self-scalability__. For example, in a P2P file-sharing application, although each peer generates workload by requesting files, each peer also adds service capacity to the system by distributing files to other peers. P2P architectures are also cost effective, since they normally don’t require significant server infrastructure and server bandwidth (in contrast with clients-server designs with datacenters). However, future P2P applications face three major challenges:

* ISP Friendly. Most residential ISPs (including DSL and cable ISPs) have been dimensioned for “asymmetrical” bandwidth usage, that is, for much more downstream than upstream traffic. But P2P video streaming and file distribu- tion applications shift upstream traffic from servers to residential ISPs, thereby putting significant stress on the ISPs. Future P2P applications need to be designed so that they are friendly to ISPs.
* Security. Because of their highly distributed and open nature, P2P applications can be a challenge to secure.
* Incentives. The success of future P2P applications also depends on convincing users to volunteer bandwidth, storage, and computation resources to the appli- cations, which is the challenge of incentive design.

### Processes Communicating
Processes on two different end systems communicate with each other by exchanging __messages__ across the computer network. A sending process creates and sends mes- sages into the network; a receiving process receives these messages and possibly responds by sending messages back. 

##### Client and Server Processes
>  In the context of a communication session between a pair of processes, the process that initiates the communication (that is, initially contacts the other process at the beginning of the session) is labeled as the client. The process that waits to be contacted to begin the session is the server.

##### The Interface Between the Process and the Computer Network
A process sends messages into, and receives messages from, the network through a software interface called a __socket__. A socket is the interface between the application layer and the transport layer within a host. It is also referred to as the __Application Programming Interface (API)__ between the application and the network, since the socket is the pro- gramming interface with which network applications are built. The application developer has control of everything on the application-layer side of the socket but has little control of the transport-layer side of the socket.  The only control that the application developer has on the transport-layer side is (1) the choice of transport protocol and (2) perhaps the ability to fix a few transport-layer parameters such as maximum buffer and maximum segment sizes (to be covered in Chapter 3). Once the application developer chooses a transport protocol (if a choice is available),the application is built using the transport-layer services provided by that protocol.

##### Addressing Processes
In order to send postal mail to a particular destination, the destination needs to have an address. Similarly, in order for a process running on one host to send packets to a process running on another host, the receiving process needs to have an address. To identify the receiving process, two pieces of information need to be specified: (1) the address of the host and (2) an identifier that specifies the receiving process in the destination host.

In the Internet, the host is identified by its __IP address__. In addition to knowing the address of the host to which a message is destined, the sending process must also identify the receiving process (more specifically, the receiving socket) running in the host. This information is needed because in gen- eral a host could be running many network applications. A destination port number serves this purpose. Popular applications have been assigned specific port numbers.

### Transport Services Available to Applications
Recall that a socket is the interface between the application process and the transport-layer protocol. The application at the sending side pushes messages through the socket. At the other side of the socket, the transport-layer protocol has the responsibility of getting the messages to the socket of the receiving process. Many networks, including the Internet, provide more than one transport-layer protocol. When you develop an application, you must choose one of the available transport-layer protocols. What are the services that a transport-layer protocol can offer to applications invoking it? We can broadly classify the possible services along four dimensions: __reliable data transfer, throughput, timing, and security__.

##### Reliable Data Transfer
If a protocol provides such a guaranteed data delivery service, it is said to provide __reliable data transfer__. One important service that a transport-layer protocol can potentially provide to an application is process-to-process reliable data transfer. When a transport protocol provides this service, the sending process can just pass its data into the socket and know with complete confidence that the data will arrive without errors at the receiving process.

When a transport-layer protocol doesn’t provide reliable data transfer, some of the data sent by the sending process may never arrive at the receiving process. This may be acceptable for __loss-tolerant applications__, most notably multimedia applica- tions such as conversational audio/video that can tolerate some amount of data loss. In these multimedia applications, lost data might result in a small glitch in the audio/video—not a crucial impairment.

##### Throughput
We introduced the concept of available throughput, which, in the con- text of a communication session between two processes along a network path, is the rate at which the sending process can deliver bits to the receiving process. Because other sessions will be sharing the bandwidth along the network path, and because these other sessions will be coming and going, the available throughput can fluctuate with time. These observations lead to another natural service that a transport-layer protocol could provide, namely, guaranteed available throughput at some specified rate. With such a service, the application could request a guar- anteed throughput of r bits/sec, and the transport protocol would then ensure that the available throughput is always at least r bits/sec. Applications that have throughput requirements are said to be __bandwidth-sensitive applications__. Many current multimedia applications are bandwidth sensitive, although some multimedia applications may use adaptive coding techniques to encode digitized voice or video at a rate that matches the currently available throughput.

While bandwidth-sensitive applications have specific throughput requirements, __elastic applications__ can make use of as much, or as little, throughput as happens to be available. 

##### Timing
A transport-layer protocol can also provide timing guarantees. 

##### Security
Finally, a transport protocol can provide an application with one or more security services. For example, in the sending host, a transport protocol can encrypt all data transmitted by the sending process, and in the receiving host, the transport-layer protocol can decrypt the data before delivering the data to the receiving process. Such a service would provide confidentiality between the two processes, even if the data is somehow observed between sending and receiving processes. A transport protocol can also provide other security services in addition to confidentiality, including data integrity and end-point authentication.

### Transport Services Provided by the Internet
