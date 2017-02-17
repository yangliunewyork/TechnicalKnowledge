### What's the difference between Ethernet and TCP/IP?

Back to basics, there are 7 layers of the OSI model. 
OSI and TCP/IP Model(Bottom => Top)

1. Physical—this is where Ethernet lives.  
2. Data Link—this is where MAC addresses live
3. Network—this is where IP lives
4. Transport—this is where TCP/UDP lives
5. Session
6. Presentation
7. Application
 
You’ve heard of an Ethernet cable?  That’s because it’s PHYSICAL.

Ethernet is a Physical layer & MAC standard (The definition actually covers Layers 1 & 2 of the OSI model).  It defines how data “packets” are transmitted on the physical cables.  Ethernet is used for wired interfaces (the most common being the RJ45 cat5 cable, but it covers many copper & fiber-optic cable types).

TCP/IP are higher layer protocols that are mostly in layers 3 & 4 of the transport protocol (IP is layer 3 and TCP is layer 4, see above and the hyperlink).  TCP/IP can be used over many types of network interconnects.  TCP/IP is used on Ethernet links, on WiFi links (WiFi is NOT Ethernet), and even by your cell phone (in fact, if you have a 3G LTE phone, everything is done over IP).

Here’s a bit of how it works:

ARP is a layer 2 protocol that resolves Network addresses (IP) to Data Link addresses (MAC) so the layers can communicate.  Address Resolution Protocol

MAC addresses include Ethernet header information.  Each layer depends on the other layers.  At a high level, from the IP address of your machine over a TCP connection to the Data Link Mac Layer (resolved via ARP) to the wire (Ethernet/Physical), and now you’re communicating via “1s and 0s” (bits/bytes) on the wire.
TCP is the connection oriented protocol.  Wikipedia has it right:  Ethernet
Back to the OSI hyperlink example, note how the TCP/IP protocol stack has its own 4 layers. TCP/IP is are both protocols.  Ethernet exists in both the OSI model and the TCP/IP protocol stack.  
