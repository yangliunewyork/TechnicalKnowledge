Network topology is the arrangement of the elements (links, nodes, etc.) of a communication network.

Network topology is the topological structure of a network and may be depicted physically or logically. It is an application of graph theory wherein communicating devices are modeled as nodes and the connections between the devices are modeled as links or lines between the nodes. Physical topology is the placement of the various components of a network (e.g., device location and cable installation), while logical topology illustrates how data flows within a network. Distances between nodes, physical interconnections, transmission rates, or signal types may differ between two different networks, yet their topologies may be identical. A network’s physical topology is a particular concern of the physical layer of the OSI model. Network topology can be used to define or describe the arrangement of various types of telecommunication networks, including command and control radio networks, industrial fieldbusses, and computer networks.

Examples of network typologies are found in local area networks (LAN), a common computer network installation. Any given node in the LAN has one or more physical links to other devices in the network; graphically mapping these links results in a geometric shape that can be used to describe the physical topology of the network. A wide variety of physical topologies have been used in LANs, including ring, bus, mesh and star. Conversely, mapping the data flow between the components determines the logical topology of the network. In comparison, Controller Area Networks, common in vehicles, are primarily distributed control system networks of one or more controllers interconnected with sensors and actuators over, invariably, a physical bus topology.

### Topologies

Two basic categories of network topologies exist, physical topologies and logical topologies.

The transmission medium layout used to link devices is the physical topology of the network. For conductive or fiber optical mediums, this refers to the layout of cabling, the locations of nodes, and the links between the nodes and the cabling.[1] The physical topology of a network is determined by the capabilities of the network access devices and media, the level of control or fault tolerance desired, and the cost associated with cabling or telecommunications circuits.

In contrast, logical topology is the way that the signals act on the network media, or the way that the data passes through the network from one device to the next without regard to the physical interconnection of the devices. A network's logical topology is not necessarily the same as its physical topology. For example, the original twisted pair Ethernet using repeater hubs was a logical bus topology carried on a physical star topology. Token ring is a logical ring topology, but is wired as a physical star from the media access unit. Physically, AFDX can be a cascaded star topology of multiple dual redundant Ethernet switches; however, the AFDX Virtual links are modeled as time-switched single-transmitter bus connections, thus following the safety model of a single-transmitter bus topology previously used in aircraft. Logical topologies are often closely associated with media access control methods and protocols. Some networks are able to dynamically change their logical topology through configuration changes to their routers and switches. 

### Network Topology: The logical layout of the cables and devices that connects the nodes of the network.

Network topologies can be either logical or physical.

A network topologies play an important role in preventing collisions

1. Bus Topology uses one cable. All the peripheral devices are connected in series to that cable. A special device, called terminator, is attached at the cable’s start and end points, to stop network signals so they do not break down the cable.
  * Advantage Of Bus Topology is that it uses the less cabling of any topology.
  * Disadvantage Of Bus Topology is that extra circuitry ad software are used to keep data packets from colliding with one another. A broken connection can bring down all part of the network.
2. Star Topology probably the most common topology. In star network, all nodes are connected to a device called hub and communicate through it. Data packets travel through the hub and are sent to attached nodes,eventually reaching their destinations. Some hubs - known as intelligent hubs- can monitor traffic and help prevent collisions.
  * Advantages of Star Topology :In star topology a broken connection between a node and the hub does not affect the rest of the network.
  * Disadvantage of Star Topology: If the hub is lost, however all the nodes connected to that hub are unable to communicate.
3. The Ring Topology connects the network’s nodes in a circular chain, with each node connected to the next. The last node connected to the first,completing the ring. Each node examines data as it travels through the ring. If data —known as a token — is not addressed to the node examining it,that node passes it to the next node.
  * Advantages of Ring Topology There is no danger of collisions because only one packet of data travels the ring at a time.
  * Disadvantages of Ring Topology If the ring is broken, however, the entire network is unable to communicate.
4. Mesh Topology is the least used network topology and the most expensive to implement. In mesh environment, a cable runs from every computer to every other computer. If you have four computers, you must have six cables—three coming from each computer to the other computers.
  * Formula: (n(n-1))/2
  * Advantage Of Mesh Topology The big advantage to this arrangement is that data can never fail to be delivered. If any one connection goes down, there are other ways to route the data to its destination.
  * Disadvantage of Mesh Topology Most expensive network as large amount of cabling is required. Expensive hardware and software is needed to implement this network.
5. Tree Topology or Hierarchical Topology is the combination of the characteristics of a star topology and a bus topology. In this topology, a star -configured workstation in a group are connected to cable which acts as a linear bus backbone. The tree bus can connect only with the hub device directly. It has a central hub acts as a root of a tree of a network device. It has a central root node which is connected to one or more nodes present in the lower hierarchical topology.
  * Advantage of Tree Topology Point to point wiring for every segment is the main advantage. It is also supported by most of the hardware and software vendors.
  * Disadvantage Of Tree Topology The type of the cabling limits the overall length of each segment. When the backbone line breaks, it leads to the breakdown of the complete segment. Tree topology becomes more difficulty to configure and wire comparision to the other topologies.
6. Hybrid Topology is a combination of any two or more network topologies. The topology obtained as a result of connecting two basic network topologies together retains the basic character of the network and is not a hybrid network.
    Consider the example of a tree network which is connected to another tree network; the resulting network is still a tree network but not a hybrid network.
