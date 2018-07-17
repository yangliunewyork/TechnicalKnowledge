In computer networking, peering is a voluntary interconnection of administratively separate Internet networks for the purpose of exchanging traffic between the users of each network. The pure definition of peering is settlement-free, also known as "bill-and-keep," or "sender keeps all," meaning that neither party pays the other in association with the exchange of traffic; instead, each derives and retains revenue from its own customers.

An agreement by two or more networks to peer is instantiated by a physical interconnection of the networks, an exchange of routing information through the Border Gateway Protocol (BGP) routing protocol and, in some special cases, a formalized contractual document.

Occasionally the word "peering" is used to describe situations where there is some settlement involved. In the face of such ambiguity, the phrase "settlement-free peering" is sometimes used to explicitly denote pure cost-free peering.

在两个ISP之间交换路由通告，以确保来自第一个ISP的业务能够到达第二个ISP的客户，反之亦然。对等操作主要在IXP进行，通常是免费提供或遵照双方商定的商务协议提供。

### How peering works

The Internet is a collection of separate and distinct networks referred to as autonomous systems, each one operating under a common framework of globally unique IP addressing and global BGP routing.

The relationships between these networks are generally described by one of the following three categories:


* Transit (or pay) – The network operator pays money (or settlement) to another network for Internet access (or transit).
* Peer (or swap) – Two networks exchange traffic between their users freely, and for mutual benefit.
* Customer (or sell) – A network pays another network money to be provided with Internet access.

Furthermore, in order for a network to reach any specific other network on the Internet, it must either:

* Sell transit (or Internet access) service to that network (making them a 'customer'),
* Peer directly with that network, or with a network which sells transit service to that network, or
* Pay another network for transit service, where that other network must in turn also sell, peer, or pay for access.

The Internet is based on the principle of global reachability (sometimes called end-to-end reachability), which means that any Internet user can reach any other Internet user as though they were on the same network. Therefore, any Internet connected network must by definition either pay another network for transit, or peer with every other network which also does not purchase transit.

### Motivations for peering

Peering involves two networks coming together to exchange traffic with each other freely, and for mutual benefit. This 'mutual benefit' is most often the motivation behind peering, which is often described solely by "reduced costs for transit services". Other less tangible motivations can include:

* Increased redundancy (by reducing dependence on one or more transit providers).
* Increased capacity for extremely large amounts of traffic (distributing traffic across many networks).
* Increased routing control over one's traffic.
* Improved performance (attempting to bypass potential bottlenecks with a "direct" path).
* Improved perception of one's network (being able to claim a "higher tier").
* Ease of requesting for emergency aid (from friendly peers).

### Physical interconnections for peering

The physical interconnections used for peering are categorized into two types:

* Public peering – Interconnection utilizing a multi-party shared switch fabric such as an Ethernet switch.
* Private peering – Interconnection utilizing a point-to-point link between two parties.


#### Public peering

Public peering is accomplished across a Layer 2 access technology, generally called a shared fabric. At these locations, multiple carriers interconnect with one or more other carriers across a single physical port. Historically, public peering locations were known as network access points (NAPs). Today they are most often called exchange points or Internet exchanges ("IXP"). Many of the largest exchange points in the world can have hundreds of participants, and some span multiple buildings and colocation facilities across a city.[2]

Since public peering allows networks interested in peering to interconnect with many other networks through a single port, it is often considered to offer "less capacity" than private peering, but to a larger number of networks. Many smaller networks, or networks which are just beginning to peer, find that public peering exchange points provide an excellent way to meet and interconnect with other networks which may be open to peering with them. Some larger networks utilize public peering as a way to aggregate a large number of "smaller peers", or as a location for conducting low-cost "trial peering" without the expense of provisioning private peering on a temporary basis, while other larger networks are not willing to participate at public exchanges at all.

A few exchange points, particularly in the United States, are operated by commercial carrier-neutral third parties, which are critical for achieving cost-effective data center connectivity.

#### Private peering

Private peering is the direct interconnection between only two networks, across a Layer 1 or 2 medium that offers dedicated capacity that is not shared by any other parties. Early in the history of the Internet, many private peers occurred across "telco" provisioned SONET circuits between individual carrier-owned facilities. Today, most private interconnections occur at carrier hotels or carrier neutral colocation facilities, where a direct crossconnect can be provisioned between participants within the same building, usually for a much lower cost than telco circuits.

Most of the traffic on the Internet, especially traffic between the largest networks, occurs via private peering. However, because of the resources required to provision each private peer, many networks are unwilling to provide private peering to "small" networks, or to "new" networks which have not yet proven that they will provide a mutual benefit.


