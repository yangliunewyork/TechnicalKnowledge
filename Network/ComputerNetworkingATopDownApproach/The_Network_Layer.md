In this chapter, we’ll make an important distinction between the __forwarding__ and __routing__ functions of the network layer. Forwarding involves the transfer of a packet from an incoming link to an outgoing link within a single router. Routing involves all of a network’s routers, whose collective interactions via routing proto- cols determine the paths that packets take on their trips from source to destination node. This will be an important distinction to keep in mind.

## 4.1 Introduction

### 4.1.1 Forwarding and Routing

The role of the network layer is thus deceptively simple—to move packets from a sending host to a receiving host. To do so, two important network-layer functions can be identified:

* Forwarding. When a packet arrives at a router’s input link, the router must move the packet to the appropriate output link.
* Routing. The network layer must determine the route or path taken by packets as they flow from a sender to a receiver. The algorithms that calculate these paths are referred to as __routing algorithms__. A routing algorithm would determine, for example, the path along which packets flow from H1 to H2.

Forwarding refers to the router-local action of transferring a packet from an input link interface to the appropriate output link interface. Routing refers to the network-wide process that determines the end-to-end paths that packets take from source to destina- tion. Using a driving analogy, consider the trip from Pennsylvania to Florida under- taken by our traveler. During this trip, our driver passes through many interchanges en route to Florida. We can think of forwarding as the process of getting through a single interchange: A car enters the interchange from one road and determines which road it should take to leave the interchange. We can think of routing as the process of planning the trip from Pennsylvania to Florida: Before embarking on the trip, the driver has consulted a map and chosen one of many paths possible, with each path consisting of a series of road segments connected at interchanges.

Every router has a __forwarding table__. A router forwards a packet by examin- ing the value of a field in the arriving packet’s header, and then using this header value to index into the router’s forwarding table. The value stored in the forward- ing table entry for that header indicates the router’s outgoing link interface to which that packet is to be forwarded. Depending on the network-layer protocol, the header value could be the destination address of the packet or an indication of the connection to which the packet belongs.

![alt](http://www.networkinginfoblog.com/contentsimages/Routing%20algorithms%20determine%20values%20in%20forwarding%20tables..JPG)

You might now be wondering how the forwarding tables in the routers are con- figured. This is a crucial issue, one that exposes the important interplay between routing and forwarding. As shown in Figure 4.2, the routing algorithm determines the values that are inserted into the routers’ forwarding tables. The routing algorithm may be centralized (e.g., with an algorithm executing on a central site and down- loading routing information to each of the routers) or decentralized (i.e., with a piece of the distributed routing algorithm running in each router). In either case, a router receives routing protocol messages, which are used to configure its forward- ing table. The distinct and different purposes of the forwarding and routing func- tions can be further illustrated by considering the hypothetical (and unrealistic, but technically feasible) case of a network in which all forwarding tables are configured directly by human network operators physically present at the routers. In this case, no routing protocols would be required! Of course, the human operators would need to interact with each other to ensure that the forwarding tables were configured in such a way that packets reached their intended destinations. It’s also likely that human configuration would be more error-prone and much slower to respond to changes in the network topology than a routing protocol. We’re thus fortunate that all networks have both a forwarding and a routing function!

While we’re on the topic of terminology, it’s worth mentioning two other terms that are often used interchangeably, but that we will use more carefully. We’ll reserve the term packet switch to mean a general packet-switching device that transfers a packet from input link interface to output link interface, according to the value in a field in the header of the packet. Some packet switches, called link-layer switches base their forwarding decision on values in the fields of the link- layer frame; switches are thus referred to as link-layer (layer 2) devices. Other packet switches, called routers, base their forwarding decision on the value in the network- layer field. Routers are thus network-layer (layer 3) devices, but must also implement layer 2 protocols as well, since layer 3 devices require the services of layer 2 to imple- ment their (layer 3) functionality.  To confuse matters, marketing literature often refers to “layer 3 switches” for routers with Ethernet interfaces, but these are really layer 3 devices. Since our focus in this chapter is on the network layer, we use the term router in place of packet switch. We’ll even use the term router when talking about packet switches in virtual-circuit networks.

##### Connection Setup
We just said that the network layer has two important functions, forwarding and routing. But we’ll soon see that in some computer networks there is actually a third important network-layer function, namely, __connection setup__. Recall from our study of TCP that a three-way handshake is required before data can flow from sender to receiver. This allows the sender and receiver to set up the needed state information (for example, sequence number and initial flow-control window size). In an analogous manner, some network-layer architectures—for example, ATM, frame relay, and MPLS ––require the routers along the chosen path from source to destination to handshake with each other in order to set up state before network-layer data packets within a given source-to-destination connection can begin to flow. In the network layer, this process is referred to as __connection setup__.

### 4.1.2 Network Service Models
The __network service model__ defines the characteristics of end-to-end transport of packets between sending and receiving end systems.

Let’s now consider some possible services that the network layer could provide. In the sending host, when the transport layer passes a packet to the network layer, specific services that could be provided by the network layer include:

* __Guaranteed delivery__. This service guarantees that the packet will eventually arrive at its destination.
* __Guaranteed delivery with bounded delay__. This service not only guarantees deliv- ery of the packet, but delivery within a specified host-to-host delay bound (for example, within 100 msec).

Furthermore, the following services could be provided to a flow of packets between a given source and destination:
* __In-order packet delivery__. This service guarantees that packets arrive at the desti- nation in the order that they were sent.
* __Guaranteed minimal bandwidth__. This network-layer service emulates the behavior of a transmission link of a specified bit rate (for example, 1 Mbps) between send- ing and receiving hosts. As long as the sending host transmits bits (as part of pack- ets) at a rate below the specified bit rate, then no packet is lost and each packet arrives within a prespecified host-to-host delay (for example, within 40 msec).
* __Guaranteed maximum jitter__. This service guarantees that the amount of time between the transmission of two successive packets at the sender is equal to the amount of time between their receipt at the destination (or that this spacing changes by no more than some specified value).
* __Security services__. Using a secret session key known only by a source and destination host, the network layer in the source host could encrypt the payloads of all datagrams being sent to the destination host. The network layer in the destination host would then be responsible for decrypting the payloads. With such a service, confidentiality would be provided to all transport-layer segments (TCP and UDP) between the source and destination hosts. In addition to confi- dentiality, the network layer could provide data integrity and source authentication services.

This is only a partial list of services that a network layer could provide—there are countless variations possible.

The Internet’s network layer provides a single service, known as __best-effort service__.From Table 4.1, it might appear that best-effort service is a euphemism for no service at all. With best-effort service, timing between packets is not guaranteed to be preserved, packets are not guaranteed to be received in the order in which they were sent, nor is the eventual delivery of transmitted packets guaranteed. Given this definition, a network that delivered no packets to the destination would satisfy the definition of best-effort delivery service. As we’ll discuss shortly, however, there are sound reasons for such a minimalist network-layer service model.

![alt](http://www.networkinginfoblog.com/contentsimages/Internet%20ATM%20CBR%20and%20ATM%20ABR%20service%20models.JPG)

Other network architectures have defined and implemented service models that go beyond the Internet’s best-effort service. For example, the ATM network archi- tecture provides for multiple service models, mean- ing that different connections can be provided with different classes of service within the same network. 

## 4.2 Virtual Circuit and Datagram Networks





