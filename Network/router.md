__A router is a networking device that forwards data packets between computer networks.__ Routers perform the traffic directing functions on the Internet. A data packet is typically forwarded from one router to another router through the networks that constitute an internetwork until it reaches its destination node.

A router is connected to two or more data lines from different networks. When a data packet comes in on one of the lines, the router reads the network address information in the packet to determine the ultimate destination. Then, using information in its routing table or routing policy, it directs the packet to the next network on its journey.

The most familiar type of routers are home and small office routers that simply pass IP packets between the home computers and the Internet. An example of a router would be the owner's cable or DSL router, which connects to the Internet through an __Internet service provider (ISP)__. More sophisticated routers, such as enterprise routers, connect large business or ISP networks up to the powerful core routers that forward data at high speed along the optical fiber lines of the Internet backbone. Though routers are typically dedicated hardware devices, software-based routers also exist.

# Applications

When multiple routers are used in interconnected networks, the routers can exchange information about destination addresses using a __dynamic routing protocol__. Each router builds up a routing table listing the preferred routes between any two systems on the interconnected networks.


A router has two stages of operation called planes:

* Control plane: A router maintains a routing table that lists which route should be used to forward a data packet, and through which physical interface connection. It does this using internal pre-configured directives, called static routes, or by learning routes using a dynamic routing protocol. Static and dynamic routes are stored in the Routing Information Base (RIB). The control-plane logic then strips non-essential directives from the RIB and builds a Forwarding Information Base (FIB) to be used by the forwarding-plane.
* Forwarding plane: The router forwards data packets between incoming and outgoing interface connections. It routes them to the correct network type using information that the packet header contains. It uses data recorded in the routing table control plane.

