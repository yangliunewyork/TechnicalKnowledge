# What is Unix Domain Socket ?
A Unix domain socket or IPC socket (inter-process communication socket) is a data communications endpoint for exchanging data between processes executing on the same host operating system. Like named pipes, Unix domain sockets support transmission of a reliable stream of bytes (SOCK_STREAM, compare to TCP). In addition, they support ordered and reliable transmission of datagrams (SOCK_SEQPACKET), or unordered and unreliable transmission of datagrams (SOCK_DGRAM, compare to UDP). The Unix domain socket facility is a standard component of POSIX operating systems.
The API for Unix domain sockets is similar to that of an Internet socket, but rather than using an underlying network protocol, all communication occurs entirely within the operating system kernel. Unix domain sockets use the file system as their address name space. Processes reference Unix domain sockets as file system inodes, so two processes can communicate by opening the same socket.
In addition to sending data, processes may send file descriptors across a Unix domain socket connection using the sendmsg() and recvmsg() system calls. This allows the sending processes to grant the receiving process access to a file descriptor for which the receiving process otherwise does not have access.


#### UNIX socket vs Network socket
A UNIX socket is an inter-process communication mechanism that allows bidirectional data exchange between processes running on the same machine.

IP sockets (especially TCP/IP sockets) are a mechanism allowing communication between processes over the network. In some cases, you can use TCP/IP sockets to talk with processes running on the same computer (by using the loopback interface).

UNIX domain sockets know that they’re executing on the same system, so they can avoid some checks and operations (like routing); which makes them faster and lighter than IP sockets. So if you plan to communicate with processes on the same host, this is a better option than IP sockets.

#### Relate commands
You can list your own machine local unix sockets with the following command:
```
netstat -a -p --unix
```

### Overview

__Sockets are communication points on the same or different computers to exchange data. Sockets are supported by Unix, Windows, Mac, and many other operating systems.__ 

Sockets allow communication between two different processes on the same or different machines. To be more precise, it's a way to talk to other computers using standard Unix file descriptors. In Unix, every I/O action is done by writing or reading a file descriptor. A file descriptor is just an integer associated with an open file and it can be a network connection, a text file, a terminal, or something else.

To a programmer, a socket looks and behaves much like a low-level file descriptor. This is because commands such as read() and write() work with sockets in the same way they do with files and pipes.

A Unix Socket is used in a client-server application framework. A server is a process that performs some functions on request from a client. Most of the application-level protocols like FTP, SMTP, and POP3 make use of sockets to establish connection between client and server and then for exchanging data.

### Socket Types

There are four types of sockets available to the users. The first two are most commonly used and the last two are rarely used.

Processes are presumed to communicate only between sockets of the same type but there is no restriction that prevents communication between sockets of different types.

* Stream Sockets − Delivery in a networked environment is guaranteed. If you send through the stream socket three items "A, B, C", they will arrive in the same order − "A, B, C". These sockets use TCP (Transmission Control Protocol) for data transmission. If delivery is impossible, the sender receives an error indicator. Data records do not have any boundaries.

* Datagram Sockets − Delivery in a networked environment is not guaranteed. They're connectionless because you don't need to have an open connection as in Stream Sockets − you build a packet with the destination information and send it out. They use UDP (User Datagram Protocol).

* Raw Sockets − These provide users access to the underlying communication protocols, which support socket abstractions. These sockets are normally datagram oriented, though their exact characteristics are dependent on the interface provided by the protocol. Raw sockets are not intended for the general user; they have been provided mainly for those interested in developing new communication protocols, or for gaining access to some of the more cryptic facilities of an existing protocol.

* Sequenced Packet Sockets − They are similar to a stream socket, with the exception that record boundaries are preserved. This interface is provided only as a part of the Network Systems (NS) socket abstraction, and is very important in most serious NS applications. Sequenced-packet sockets allow the user to manipulate the Sequence Packet Protocol (SPP) or Internet Datagram Protocol (IDP) headers on a packet or a group of packets, either by writing a prototype header along with whatever data is to be sent, or by specifying a default header to be used with all outgoing data, and allows the user to receive the headers on incoming packets.

### Network Addresses

Before we proceed with the actual stuff, let us discuss a bit about the Network Addresses − the IP Address.

The IP host address, or more commonly just IP address, is used to identify hosts connected to the Internet. IP stands for Internet Protocol and refers to the Internet Layer of the overall network architecture of the Internet.

__An IP address is a 32-bit quantity interpreted as four 8-bit numbers or octets. Each IP address uniquely identifies the participating user network, the host on the network, and the class of the user network.__

An IP address is usually written in a dotted-decimal notation of the form N1.N2.N3.N4, where each Ni is a decimal number between 0 and 255 decimal (00 through FF hexadecimal).

#### Address Classes


IP addresses are managed and created by the Internet Assigned Numbers Authority (IANA). There are five different address classes. You can determine which class an IP address is in by examining the first four bits of the IP address.

* Class A addresses begin with 0xxx, or 1 to 126 decimal.

* Class B addresses begin with 10xx, or 128 to 191 decimal.

* Class C addresses begin with 110x, or 192 to 223 decimal.

* Class D addresses begin with 1110, or 224 to 239 decimal.

* Class E addresses begin with 1111, or 240 to 254 decimal.

Addresses beginning with 01111111, or 127 decimal, are reserved for loopback and for internal testing on a local machine [You can test this: you should always be able to ping 127.0.0.1, which points to yourself]; __Class D addresses are reserved for multicasting; Class E addresses are reserved for future use. They should not be used for host addresses.__

#### Subnetting

Subnetting or subnetworking basically means to branch off a network. It can be done for a variety of reasons like network in an organization, use of different physical media (such as Ethernet, FDDI, WAN, etc.), preservation of address space, and security. The most common reason is to control network traffic.

The basic idea in subnetting is to partition the host identifier portion of the IP address into two parts:

* A subnet address within the network address itself; and
* A host address on the subnet.

### Network Host Names

Host names in terms of numbers are difficult to remember and hence they are termed by ordinary names such as Takshila or Nalanda. We write software applications to find out the dotted IP address corresponding to a given name.

The process of finding out dotted IP address based on the given alphanumeric host name is known as __hostname resolution__.

A hostname resolution is done by special software residing on high-capacity systems. These systems are called Domain Name Systems (DNS), which keep the mapping of IP addresses and the corresponding ordinary names.

#### The /etc/hosts File

The correspondence between host names and IP addresses is maintained in a file called hosts. On most of the systems, this file is found in /etc directory.

Entries in this file look like the following

```
# This represents a comments in /etc/hosts file.
127.0.0.1       localhost
192.217.44.207  nalanda metro
153.110.31.18   netserve
153.110.31.19   mainserver centeral
153.110.31.20   samsonite
64.202.167.10   ns3.secureserver.net
64.202.167.97   ns4.secureserver.net
66.249.89.104   www.google.com
68.178.157.132  services.amrood.com
```

Note that more than one name may be associated with a given IP address. This file is used while converting from IP address to host name and vice versa.

You would not have access to edit this file, so if you want to put any host name along with IP address, then you would need to have root permission.

### Client Server Model

Most of the Net Applications use the Client-Server architecture, which refers to two processes or two applications that communicate with each other to exchange some information. One of the two processes acts as a client process, and another process acts as a server.

#### Client Process

This is the process, which typically makes a request for information. After getting the response, this process may terminate or may do some other processing.

Example, Internet Browser works as a client application, which sends a request to the Web Server to get one HTML webpage.

#### Server Process

This is the process which takes a request from the clients. After getting a request from the client, this process will perform the required processing, gather the requested information, and send it to the requestor client. Once done, it becomes ready to serve another client. Server processes are always alert and ready to serve incoming requests.

Example − Web Server keeps waiting for requests from Internet Browsers and as soon as it gets any request from a browser, it picks up a requested HTML page and sends it back to that Browser.

Note that the client needs to know the address of the server, but the server does not need to know the address or even the existence of the client prior to the connection being established. Once a connection is established, both sides can send and receive information.

#### How to Make Client

The system calls for establishing a connection are somewhat different for the client and the server, but both involve the basic construct of a socket. Both the processes establish their own sockets.

The steps involved in establishing a socket on the client side are as follows −

* Create a socket with the socket() system call.

* Connect the socket to the address of the server using the connect() system call.

* Send and receive data. There are a number of ways to do this, but the simplest way is to use the read() and write() system calls.

#### How to make a Server

The steps involved in establishing a socket on the server side are as follows −

* Create a socket with the socket() system call.

* Bind the socket to an address using the bind() system call. For a server socket on the Internet, an address consists of a port number on the host machine.

* Listen for connections with the listen() system call.

* Accept a connection with the accept() system call. This call typically blocks the connection until a client connects with the server.

* Send and receive data using the read() and write() system calls.

#### Client and Server Interaction

![alt](https://www.tutorialspoint.com/unix_sockets/images/socket_client_server.gif)








