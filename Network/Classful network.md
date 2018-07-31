A __classful network__ is a network addressing architecture used in the Internet from 1981 until the introduction of Classless Inter-Domain Routing in 1993. The method divides the IP address space for Internet Protocol version 4 (IPv4) into five address classes based on the leading four address bits. Classes A, B, and C provide unicast addresses for networks of three different network sizes. Class D is for multicast networking and the class E address range is reserved for future or experimental purposes.

Since its discontinuation, remnants of classful network concepts have remained in practice only in limited scope in the default configuration parameters of some network software and hardware components, most notably in the default configuration of subnet masks. 

In the original address definition, the most significant eight bits of the 32-bit IPv4 address was the _network number field_ which specified the particular network a host was attached to. The remaining 24 bits specified the local address, also called _rest field (the rest of the address)_, which uniquely identified a host connected to that network.[1] This format was sufficient at a time when only a few large networks existed, such as the ARPANET (network number 10), and before the wide proliferation of local area networks (LANs). As a consequence of this architecture, the address space supported only a low number (254) of independent networks. It became clear early in the growth of the network that this would be a critical scalability limitation.

### Introduction of address classes

Expansion of the network had to ensure compatibility with the existing address space and the IPv4 packet structure, and avoid the renumbering of the existing networks. The solution was to expand the definition of the network number field to include more bits, allowing more networks to be designated, each potentially having fewer hosts. Since all existing network numbers at the time were smaller than 64, they had only used the 6 least-significant bits of the network number field. Thus it was possible to use the most-significant bits of an address to introduce a set of address classes while preserving the existing network numbers in the first of these classes.

The new addressing architecture was introduced by RFC 791 in 1981 as a part of the specification of the Internet Protocol.[2] It divided the address space into primarily three address formats, henceforth called address classes, and left a fourth range reserved to be defined later.

The first class, designated as Class A, contained all addresses in which the most significant bit is zero. The network number for this class is given by the next 7 bits, therefore accommodating 128 networks in total, including the zero network, and including the IP networks already allocated. A Class B network was a network in which all addresses had the two most-significant bits set to 1 and 0 respectively. For these networks, the network address was given by the next 14 bits of the address, thus leaving 16 bits for numbering host on the network for a total of 65536 addresses per network. Class C was defined with the 3 high-order bits set to 1, 1, and 0, and designating the next 21 bits to number the networks, leaving each network with 256 local addresses.

The leading bit sequence 111 designated an at-the-time unspecified addressing mode ("escape to extended addressing mode"), which was later subdivided as Class D (1110) for multicast addressing, while leaving as reserved for future use the 1111 block designated as Class E.

### Classful addressing definition

<img src="http://www.tcpipguide.com/free/diagrams/ipclasses.png">

Today, IP addresses are associated with a __subnet mask__. This was not required in a classful network because the mask was implicitly derived from the IP address itself; Any network device would inspect the first few bits of the IP address to determine the class of the address.

The blocks numerically at the start and end of classes A, B and C were originally reserved for special addressing or future features, i.e., 0.0.0.0/8 and 127.0.0.0/8 are reserved in former class A; 128.0.0.0/16 and 191.255.0.0/16 were reserved in former class B but are now available for assignment; 192.0.0.0/24 and 223.255.255.0/24 are reserved in former class C. While the 127.0.0.0/8 network is a Class A network, it is designated for loopback and cannot be assigned to a network.[4]

Class D is reserved for multicast and cannot be used for regular unicast traffic.

Class E is reserved and cannot be used on the public Internet. Many older routers will not accept using it in any context.

#### Bit-wise representation

In the following table:

* n indicates a bit used for the network ID.
* H indicates a bit used for the host ID.
* X indicates a bit without a specified purpose.

```
Class A
  0.  0.  0.  0 = 00000000.00000000.00000000.00000000
127.255.255.255 = 01111111.11111111.11111111.11111111
                  0nnnnnnn.HHHHHHHH.HHHHHHHH.HHHHHHHH

Class B
128.  0.  0.  0 = 10000000.00000000.00000000.00000000
191.255.255.255 = 10111111.11111111.11111111.11111111
                  10nnnnnn.nnnnnnnn.HHHHHHHH.HHHHHHHH

Class C
192.  0.  0.  0 = 11000000.00000000.00000000.00000000
223.255.255.255 = 11011111.11111111.11111111.11111111
                  110nnnnn.nnnnnnnn.nnnnnnnn.HHHHHHHH

Class D
224.  0.  0.  0 = 11100000.00000000.00000000.00000000
239.255.255.255 = 11101111.11111111.11111111.11111111
                  1110XXXX.XXXXXXXX.XXXXXXXX.XXXXXXXX

Class E
240.  0.  0.  0 = 11110000.00000000.00000000.00000000
255.255.255.255 = 11111111.11111111.11111111.11111111
                  1111XXXX.XXXXXXXX.XXXXXXXX.XXXXXXXX
```
