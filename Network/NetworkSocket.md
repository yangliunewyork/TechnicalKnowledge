### What is network socket ?
A network socket is an endpoint for sending or receiving data at a single node in a computer network. Concretely, it is an internal representation of this endpoint in the networking software (protocol stack), such as an entry in a table (listing communication protocol, destination, status, etc.), and is a form of system resource. The term "socket" is also used for an endpoint of local inter-process communication (IPC) (not over a network).</br>
A socket can be referred to by a process (a running computer program) by using a socket descriptor, a type of handle (abstract reference, often represented internally as an integer). A process first requests that the protocol stack create a socket, and the stack returns a descriptor to the process so it can identify the socket. The process then passes the descriptor back to the protocol stack when it wishes to send or receive data using this socket.</br>
Sockets are local (specific to one node): they are local resources and cannot be referred to directly by other nodes, nor are they necessarily associated with a persistent connection (channel) for communication between two nodes, nor is there necessarily some single other endpoint. For example, a datagram socket can be used for connectionless communication, and a multicast socket can be used to send to multiple nodes, or an address range where there may or may not be any nodes to receive data. However, in practice for internet communication, sockets generally have associated addresses and often have a connection.</br>

#### Socket addresses
In practice "socket" usually refers to a socket in an Internet Protocol (IP) network (where sockets may be called Internet sockets), in particular for the Transmission Control Protocol (TCP), which is a protocol for one-to-one connections. In this context, sockets are assumed to be associated with a specific socket address, namely the IP address and a port number for the local node, and there is a corresponding socket address at the foreign node (other node), which itself has an associated socket, used by the foreign process. Associating a socket with a socket address is called binding.</br>
Note that while a local process can communicate with a foreign process by sending or receiving data to or from a foreign socket address, it does not have access to the foreign socket itself, nor can it use the foreign socket descriptor, as these are both internal to the foreign node. For example, in a connection between 123:4 and 567:8 (local IP address:local port, foreign IP address:foreign port), there will also be an associated socket at each end, corresponding to the internal representation of the connection by the protocol stack on that node, which are referred to locally by numerical socket descriptors, say 317 at one side and 922 at the other. A process on node 123 can request to communicate with node 567 on port 8 (request that the protocol stack create a socket to communicate with that destination), and once it has created a socket and received a socket descriptor (317), it can communicate via this socket by using the descriptor (317): the protocol stack will then forward data to and from node 567 on port 8. However, a process on node 123 cannot request to communicate with "socket 922" or "socket 922 on node 567": these are meaningless numbers to the protocol stack on node 123.</br>

#### Definition
The distinctions between a socket (internal representation), socket descriptor (abstract identifier), and socket address (public address) are subtle, and these are not carefully distinguished in everyday usage. Further, specific definitions of a socket
An Internet socket is characterized by at least the following:
* local socket address, consisting of the local IP address and (for TCP and UDP, but not IP) a port number
* protocol: A transport protocol, e.g., TCP, UDP, raw IP. This means that (local or remote) endpoints with TCP port 53 and UDP port 53 are distinct sockets, while IP does not have ports.</br>

A socket that has been connected to another socket, e.g., during the establishment of a TCP connection, also has a remote socket address.
Within the operating system and the application that created a socket, a socket is referred to by a unique integer value called a socket descriptor. The operating system forwards the payload of incoming IP packets to the corresponding application by extracting the socket address information from the IP and transport protocol headers and stripping the headers from the application data.

#### Types
Several types of Internet socket are available:
* Datagram sockets, also known as connectionless sockets, which use User Datagram Protocol (UDP).
* Stream sockets, also known as connection-oriented sockets, which use Transmission Control Protocol (TCP), Stream Control Transmission Protocol (SCTP) or Datagram Congestion Control Protocol (DCCP).
* Raw sockets (or Raw IP sockets), typically available in routers and other network equipment. Here the transport layer is bypassed, and the packet headers are made accessible to the application, and there is no port number in the address, just the IP address.

#### Socket states in the client-server model
Computer processes that provide application services are referred to as servers, and create sockets on start up that are in listening state. These sockets are waiting for initiatives from client programs.</br>
A TCP server may serve several clients concurrently, by creating a child process for each client and establishing a TCP connection between the child process and the client. Unique dedicated sockets are created for each connection. These are in established state when a socket-to-socket virtual connection or virtual circuit (VC), also known as a TCP session, is established with the remote socket, providing a duplex byte stream.</br>
A server may create several concurrently established TCP sockets with the same local port number and local IP address, each mapped to its own server-child process, serving its own client process. They are treated as different sockets by the operating system, since the remote socket address (the client IP address and/or port number) are different; i.e. since they have different socket pair tuples.</br>
A UDP socket cannot be in an established state, since UDP is connectionless. Therefore, netstat does not show the state of a UDP socket. A UDP server does not create new child processes for every concurrently served client, but the same process handles incoming data packets from all remote clients sequentially through the same socket. It implies that UDP sockets are not identified by the remote address, but only by the local address, although each message has an associated remote address.</br>
#### Socket pairs
Communicating local and remote sockets are called socket pairs. Each socket pair is described by a unique 4-tuple consisting of source and destination IP addresses and port numbers, i.e. of local and remote socket addresses.[3][4] As seen in the discussion above, in the TCP case, each unique socket pair 4-tuple is assigned a socket number, while in the UDP case, each unique local socket address is assigned a socket number.

#### Related commands
* /proc/net/tcp -a list of open tcp sockets
* /proc/net/udp -a list of open udp sockets
* /proc/net/raw -a list all the 'raw' sockets

Also you can use ss utility to dump sockets statistics.
```
ss -s

Total: 91 (kernel 0)
TCP:   18 (estab 11, closed 0, orphaned 0, synrecv 0, timewait 0/0), ports 0

Transport Total     IP        IPv6
*         0         -         -        
RAW       0         0         0        
UDP       4         2         2        
TCP       18        16        2        
INET      22        18        4        
FRAG      0         0         0
```
You can use netstat command
```
netstat --listen
```
To display open ports and established TCP connections,
```
netstat -vatn
```
To display only open UDP ports try the following command:

netstat -vaun
