

A private IP address is an IP address that's reserved for internal use behind a router or other Network Address Translation (NAT) device, apart from the public.

Private IP addresses are in contrast to public IP addresses, which are public and can not be used within a home or business network.

### Which IP Addresses Are Private? 



The Internet Assigned Numbers Authority (IANA) reserves the following IP address blocks for use as private IP addresses:

```
    10.0.0.0 to 10.255.255.255
    172.16.0.0 to 172.31.255.255
    192.168.0.0 to 192.168.255.255
```

The first set of IP addresses from above allow for over 16 million addresses, the second for over 1 million, and over 65,000 for the last range.

Another range of private IP addresses is 169.254.0.0 to 169.254.255.255, but those addresses are for Automatic Private IP Addressing (APIPA) use only.

### Why Private IP Addresses Are Used 

Instead of having devices inside a home or business network each use a public IP address, of which there's a limited supply, private IP addresses provide an entirely separate set of addresses that still allow access on a network but without taking up a public IP address space.

For example, let's consider a standard router on a home network. Most routers in homes and businesses across the globe, probably yours and your next door neighbor's, all have the IP address of 192.168.1.1, and assign 192.168.1.2, 192.168.1.3, ... to the various devices that connect to it (via something called DHCP).

It doesn't matter how many routers use the 192.168.1.1 address, or how many dozens or hundreds of devices inside that network share IP addresses with users of other networks, because they aren't communicating with each other directly.

Instead, the devices in a network use the router to translate their requests through the public IP address, which can communicate with other public IP addresses and eventually to other local networks.

The hardware within a specific network that are using a private IP address can communicate with all the other hardware within the confines of that network, but will require a router to communicate with devices outside the network, after which the public IP address will be used for the communication.

For example, before landing on this page, your device (be it a computer, phone, or whatever), which uses a private IP address, requested this page through a router, which has a public IP address. Once the request was made and Lifewire responded to deliver the page, it was downloaded to your device through a public IP address before reaching your router, after which it got handed off to your private/local address to reach your device.

All the devices (laptops, desktops, phones, tablets, etc.) that are contained within private networks around the world can use a private IP address with virtually no limitation, which can't be said for public IP addresses.

Private IP addresses also provide a way for devices that don't need contact with the internet, like file servers, printers, etc., to still communicate with the other devices on a network without being directly exposed to the public.

### Reserved IP Addresses 

Another set of IP addresses that are restricted even further are called reserved IP addresses. These are similar to private IP addresses in the sense that they can't be used for communicating on the greater internet, but they're even more restrictive than that.

The most famous reserved IP is 127.0.0.1. This address is called the loopback address and is used to test the network adapter or integrated chip. No traffic addressed to 127.0.0.1 is sent over the local network or public internet.

Technically, the entire range from 127.0.0.0 to 127.255.255.255 is reserved for loopback purposes but you'll almost never see anything but 127.0.0.1 used in the real world.

Addresses in the range from 0.0.0.0 to 0.255.255.255 are also reserved but don't do anything at all. If you're even able to assign a device an IP address in this range, it will not function properly no matter where on the network it's installed.

### More Information on Private IP Addresses 

When a device like a router is plugged in, it receives a public IP address from an ISP. It's the devices that are then connected to the router that are given private IP addresses.

As we mentioned above, private IP addresses can't communicate directly with a public IP address. This means if a device that has a private IP address is connected directly into the internet, and therefore becomes non-routable, the device will have no network connection until the address is translated into a working address through a NAT, or until the requests it's sending are sent through a device that does have a valid public IP address.

All traffic from the internet can interact with a router. This is true for everything from regular HTTP traffic to things like FTP and RDP. However, because private IP addresses are hidden behind a router, the router must know which IP address it should forward information to if you're wanting something like an FTP server to be set up on a home network.

For this to work properly for private IP addresses, you must set up port forwarding. Forwarding one or more ports to a specific private IP address involves logging into the router to access its settings, and then choosing which port(s) to forward, and to where it should go.


