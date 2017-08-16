# What is port ?

In the internet protocol suite, a port is an endpoint of communication in an operating system. While the term is also used for female connectors on hardware devices (see computer port), in software it is a logical construct that identifies a specific process or a type of network service.

A port is always associated with an IP address of a host and the protocol type of the communication, and thus completes the destination or origination network address of a communication session. A port is identified for each address and protocol by a 16-bit number, commonly known as the port number. For example, an address may be "protocol: TCP, IP address: 1.2.3.4, port number: 80", which may be written 1.2.3.4:80 when the protocol is known from context.

Specific port numbers are often used to identify specific services. Of the thousands of enumerated ports, 1024 well-known port numbers are reserved by convention to identify specific service types on a host. In the client–server model of application architecture, the ports that network clients connect to for service initiation provide a multiplexing service. After initial communication binds to the well-known port number, this port is freed by switching each instance of service requests to a dedicated, connection-specific port number, so that additional clients can be serviced. The protocols that primarily use ports are the transport layer protocols, such as the Transmission Control Protocol (TCP) and the User Datagram Protocol (UDP).

Ports were unnecessary on direct point-to-point links when the computers at each end could only run one program at a time. Ports became necessary after computers became capable of executing more than one program at a time and were connected to modern networks.

# Details

Transport layer protocols, such as the __Transmission Control Protocol (TCP)__ and the __User Datagram Protocol (UDP)__, specify a source and destination port number in their headers. A port number is a 16-bit unsigned integer, thus ranging from 0 to 65535. A process associates its input or output channels, via an Internet socket (a type of file descriptor), with a transport protocol, a port number, and an IP address. This process is known as __binding__, and enables sending and receiving data via the network. The operating system's networking software has the task of transmitting outgoing data from all application ports onto the network, and forwarding arriving network packets to processes by matching the packet's IP address and port number. Only one process may bind to a specific IP address and port combination using the same transport protocol. Common application failures, sometimes called __port conflicts__, occur when multiple programs attempt to bind to the same port numbers on the same IP address using the same protocol.

Applications implementing common services often use specifically reserved __well-known port numbers__ for receiving service requests from clients. This process is known as __listening__, and involves the receipt of a request on the well-known port and establishing a one-to-one server-client dialog, using the same local port number. Other clients may continue to connect to the listening port; this works because a TCP connection is identified by a tuple consisting of the local address, the local port, the remote address, and the remote port. The well-known ports are defined by convention overseen by the Internet Assigned Numbers Authority (IANA). The core network services, such as the World-Wide Web, typically use well-known port numbers. In many operating systems special privileges are required for applications to bind to these ports, because these are often deemed critical to the operation of IP networks. Conversely, the client end of a connection typically uses a high port number allocated for short term use, therefore called an ephemeral port.

The port numbers are encoded in the transport protocol packet header, and they can be readily interpreted not only by the sending and receiving computers, but also by other components of the networking infrastructure. In particular, firewalls are commonly configured to differentiate between packets based on their source or destination port numbers. Port forwarding is an example application of this.

The practice of attempting to connect to a range of ports in sequence on a single computer is commonly known as __port scanning__. This is usually associated either with malicious cracking attempts or with network administrators looking for possible vulnerabilities to help prevent such attacks. Port connection attempts are frequently monitored and logged by computers. The technique of port knocking uses a series of port connections (knocks) from a client computer to enable a server connection.

# Q & A

##### How do multiple clients connect simultaneously to one port, say 80, on a server?

First off, a "port" is just a number. All a "connection to a port" really represents is a packet which has that number specified in its "destination port" header field.

Now, there are two answers to your question, one for stateful protocols and one for stateless protocols.

For a stateless protocol (ie UDP), there is no problem because "connections" don't exist - multiple people can send packets to the same port, and their packets will arrive in whatever sequence. Nobody is ever in the "connected" state.

For a stateful protocol (like TCP), a connection is identified by a 4-tuple consisting of source and destination ports and source and destination IP addresses. So, if two different machines connect to the same port on a third machine, there are two distinct connections because the source IPs differ. If the same machine (or two behind NAT or otherwise sharing the same IP address) connects twice to a single remote end, the connections are differentiated by source port (which is generally a random high-numbered port).

Simply, if I connect to the same web server twice from my client, the two connections will have different source ports from my perspective and destination ports from the web server's. So there is no ambiguity, even though both connections have the same source and destination IP addresses.

Ports are a way to multiplex IP addresses so that different applications can listen on the same IP address/protocol pair. Unless an application defines its own higher-level protocol, there is no way to multiplex a port. If two connections using the same protocol have identical source and destination IPs and identical source and destination ports, they must be the same connection.


##### What is the difference between a port and a socket?

A socket represents a single connection between two network applications. These two applications nominally run on different computers, but sockets can also be used for interprocess communication on a single computer. Applications can create multiple sockets for communicating with each other. Sockets are bidirectional, meaning that either side of the connection is capable of both sending and receiving data. Therefore a socket can be created theoretically at any level of the OSI model from 2 upwards. Programmers often use sockets in network programming, albeit indirectly. Programming libraries like Winsock hide many of the low-level details of socket programming. Sockets have been in widespread use since the early 1980s.

A port represents an endpoint or "channel" for network communications. Port numbers allow different applications on the same computer to utilize network resources without interfering with each other. Port numbers most commonly appear in network programming, particularly socket programming. Sometimes, though, port numbers are made visible to the casual user. For example, some Web sites a person visits on the Internet use a URL like the following:

http://www.mairie-metz.fr:8080/ In this example, the number 8080 refers to the port number used by the Web browser to connect to the Web server. Normally, a Web site uses port number 80 and this number need not be included with the URL (although it can be).

In IP networking, port numbers can theoretically range from 0 to 65535. Most popular network applications, though, use port numbers at the low end of the range (such as 80 for HTTP).

















