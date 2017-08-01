In computer networking, localhost is a hostname that means this computer. It is used to access the network services that are running on the host via its loopback network interface. Using the loopback interface bypasses any local network interface hardware.

The local loopback mechanism is useful for testing software during development, independently of any networking configurations. For example, if a computer has been configured to provide a website, directing a locally running web browser to http://localhost may display its home page.

On most computer systems, localhost resolves to the IP address 127.0.0.1, which is the most commonly used IPv4 loopback address, and to the IPv6 loopback address ::1.

The name localhost is also a reserved top-level domain name, set aside to avoid confusion with the definition as a hostname. The IETF standards restrict domain name registrars from assigning the name localhost in registration procedures, such as for second-level domains.

# Name resolution

IPv4 network standards reserve the entire 127.0.0.0/8 address block for loopback purposes. That means any packet sent to one of those 16,777,214 addresses (127.0.0.1 through 127.255.255.254) is looped back. IPv6 has just a single address, ::1.

The resolution of the name localhost into one or more IP addresses is configured by the following lines in the operating system's hosts file:

```
127.0.0.1    localhost
::1          localhost
```

However, it may also be resolved with the Domain Name System (DNS). Localhost may be mapped to other IPv4 loopback addresses, and additional names may be assigned to any loopback address.

The processing of any packets sent to a loopback address is implemented in the link layer of the TCP/IP stack. Such packets are never delivered to any network interface controller (NIC) or device driver, which permits testing of software in the absence of any hardware network interfaces.

Like any other packets traversing the TCP/IP stack, looped-back packets convey the IP address and port number they were addressed to. Thus, the services that ultimately receive them can respond according to the specified loopback destination. For example, an HTTP service could route packets addressed to 127.0.0.99:80 and 127.0.0.100:80 to different Web servers, or to a single server that would return different web pages. To simplify such testing, the hosts file can be modified to provide appropriate aliases for each such address.

