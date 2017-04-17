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


