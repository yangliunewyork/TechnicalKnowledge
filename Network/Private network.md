### What is private network ?

In the Internet addressing architecture, a private network is a network that uses private IP address space. Both, the IPv4 and the IPv6 specifications define private addressing ranges. These addresses are commonly used for local area networks (LANs) in residential, office, and enterprise environments. Private IP address spaces were originally defined in an effort to delay IPv4 address exhaustion.

Private network addresses are not allocated to any specific organization and anyone may use these addresses without approval from a regional Internet registry. However, IP packets addressed from them cannot be routed through the public Internet. 

Here's a look at the default private (also called "local") IP addresses for popular brands of routers:

```
    Linksys routers use 192.168.1.1
    D-Link and NETGEAR routers are set to 192.168.0.1
    Cisco routers use either 192.168.10.2, 192.168.1.254 or 192.168.1.1
    Belkin and SMC routers often use 192.168.2.1
```

### How you connect to the world

You're public IP address is the IP address that someone on the other end of your Internet activity would see (if they bothered to look for it). That's the only reason it's known as a public IP address. 

With traditional mail, when you send a letter, you have to know the address to send it to—such as "1234 Main Street,"—so that the postman knows which street and which house to take it to.

The Internet works similarly, except it directs your personal activity (emails, answers to Google inquiries, etc.), and forwards the electronic messages to your computer's address.

#### Public and Private. Working together to get you connected

In theory, your computer must have its own unique IP address so that it will only receive the information that is meant for you.


However, that's not how it works out, because of one major exception—network computers that are linked to a router and share the same public IP address. 

### Reserved for private networks

The organizations that distribute IP addresses to the world reserves a range of IP addresses for private networks. 

```
    192.168.0.0 - 192.168.255.255 (65,536 IP addresses)
    172.16.0.0 - 172.31.255.255 (1,048,576 IP addresses)
    10.0.0.0 - 10.255.255.255 (16,777,216 IP addresses)
```

Your simple home network, with its router at the center and computers connected to it—wired or wireless—classifies as one of those networks.

Your router—once it makes its Internet connection through your __Internet Service Provider__—sends Internet activity to any computer connected to your router, and is the basis of a networking innovation called a __Network Address Translation (NAT)__.

NAT is a process in which your router changes your private IP Address into a public one so that it can send your traffic over the Internet, keeping track of the changes in the process. When the information comes back to your router, it reverses the change—from a real IP address into a private one—and forwards the traffic back to your computer. 

In other words, the router connects to the other devices (usually desktops, laptops and tablets).That's the point: Your private address is just for your router, your network and you.The private address ranges in a network don't have to be synchronized with the rest of the world and Internet. As a matter of fact, the private address range can be used by more than one address. A network administrator using these private addresses has more room for subnetting, and many more assignable addresses.

The private IP address does one job for your home network. These blocks of addresses can be used by a private network. Even if your neighbor is using the exact same addresses, it won't cause a problem, because that's HIS or HER network, not yours.
Don't let that confuse you. You see, these private addresses are known as non-routable addresses. The networking on the Internet routes Internet activity connected to your public IP address only, not your private IP.

<img src="https://cdn.whatismyipaddress.com/images-v4/private-ip_diagram.jpg">  

### Four key takeaways

To wrap up our discussion about public and private IP addresses, keep these four ideas in mind:

1. Private IP addresses are untracked and unrestricted. WhatIsMyIPaddess.com cannot geographically locate a user's computer by their private IP address.  
2. It is perfectly normal to see traffic from these numbers if you have a small home or office network. By default, most routers and access points use these numbers to assign to your local computers. It is most likely these numbers represent computers on your own internal network.    
3. If you see these numbers in the headers of an unsolicited email, they usually indicate transit between servers within a corporate network or ISP. Again, they are not useful in identifying the origin of an email. In such cases, you can usually find the true origin by looking for the earliest "Received" mail header.  
4. The traffic does not come from the IANA (the Internet Assigned Numbers Authority), a non-government, Internet-specific organization that gives out (assigns and allocates) IP addresses. As the authority for IP addresses, they do not use or operate them, and they are not the source of the traffic.  
