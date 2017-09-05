__A router is a networking device that forwards data packets between computer networks.__ Routers perform the traffic directing functions on the Internet. A data packet is typically forwarded from one router to another router through the networks that constitute an internetwork until it reaches its destination node.

A router is connected to two or more data lines from different networks. When a data packet comes in on one of the lines, the router reads the network address information in the packet to determine the ultimate destination. Then, using information in its routing table or routing policy, it directs the packet to the next network on its journey.

The most familiar type of routers are home and small office routers that simply pass IP packets between the home computers and the Internet. An example of a router would be the owner's cable or DSL router, which connects to the Internet through an __Internet service provider (ISP)__. More sophisticated routers, such as enterprise routers, connect large business or ISP networks up to the powerful core routers that forward data at high speed along the optical fiber lines of the Internet backbone. Though routers are typically dedicated hardware devices, software-based routers also exist.

# Applications

When multiple routers are used in interconnected networks, the routers can exchange information about destination addresses using a __dynamic routing protocol__. Each router builds up a routing table listing the preferred routes between any two systems on the interconnected networks.


A router has two stages of operation called planes:

* Control plane: A router maintains a routing table that lists which route should be used to forward a data packet, and through which physical interface connection. It does this using internal pre-configured directives, called static routes, or by learning routes using a dynamic routing protocol. Static and dynamic routes are stored in the Routing Information Base (RIB). The control-plane logic then strips non-essential directives from the RIB and builds a Forwarding Information Base (FIB) to be used by the forwarding-plane.
* Forwarding plane: The router forwards data packets between incoming and outgoing interface connections. It routes them to the correct network type using information that the packet header contains. It uses data recorded in the routing table control plane.

# Difference between a network hub, switch, and router?

There are three main devices that work to connect one computer to another computer. A network hub, switch, and router can all perform this function. It can sometimes be confusing when trying to figure out what device is currently being used on a computer network, without knowing what each device does.

##### Network Hub

A network hub is designed to connect computers to each other with no real understanding of what it is transferring. Typically, a network hub is used for a private network, one that does not have any connections to sources other than local computers (meaning, no Internet access). __When a hub receives a packet of data from a connected device, it broadcasts that data packet to all other connected devices regardless of which one ends up being the final destination.__ Additionally, network bandwidth is split between all of the connected computers. So, the more computer that are connected, the less bandwidth that is available for each computer, which means slower connection speeds.

In the past, network switches and routers were expensive, confusing, and hard to use for most users and most opted for network hubs. Today, home network switches and routers are much easier to use and cheaper, which is why network hubs are rarely used or found anymore.

##### Network switch 

__A network switch also connects computers to each other, like a hub. Where the switch differs from a hub is in the way it handles packets of data. When a switch receives a packet of data, it determines what computer or device the packet is intended for and sends it to that computer only. It does not broadcast the packet to all computers as a hub does which means bandwidth is not shared and makes the network much more efficient. For this reason alone, switches are usually preferred over a hub.__

##### Network Router

A network router is quite different from a switch or hub since its primary function is to route data packets to other networks, instead of just the local computers. A router is quite common to find in homes and businesses since it allows your network to communicate with other networks including the Internet. Essentially, a router bridges the gap between other networks and gives your network access to more features, e.g. a firewall, QoS, traffic monitoring, VPN, and more.




