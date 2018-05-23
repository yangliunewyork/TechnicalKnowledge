__Virtual hosting__ is a method for hosting multiple domain names (with separate handling of each name) on a single server (or pool of servers). This allows one server to share its resources, such as memory and processor cycles, without requiring all services provided to use the same host name. The term virtual hosting is usually used in reference to web servers but the principles do carry over to other internet services.

One widely used application is shared web hosting. Shared web hosting prices are lower than a dedicated web server because many customers can be hosted on a single server. It is also very common for a single entity to want to use multiple names on the same machine so that the names can reflect services offered rather than where those services happen to be hosted.

There are two main types of virtual hosting, name-based and IP-based. Name-based virtual hosting uses the host name presented by the client. This saves IP addresses and the associated administrative overhead but the protocol being served must supply the host name at an appropriate point. In particular, there are significant difficulties using name-based virtual hosting with SSL/TLS. IP-based virtual hosting uses a separate IP address for each host name, and it can be performed with any protocol but requires a dedicated IP address per domain name served. Port-based virtual hosting is also possible in principle but is rarely used in practice because it is unfriendly to users.

Name-based and IP-based virtual hosting can be combined: a server may have multiple IP addresses and serve multiple names on some or all of those IP addresses. This technique can be useful when using SSL/TLS with wildcard certificates. For example, if a server operator had two certificates, one for *.example.com and one for *.example.net, the operator could serve foo.example.com and bar.example.com off the same IP address but would need a separate IP address for baz.example.net.

#### What is the difference between virtual hosts and virtual servers?

One server can host multiple sites. For example, I can send requests for Foo.com to /home/sites/foo and requests for bar.com to /home/sites/bar. This has the advantage of performance (only one copy of the software is running to do this), and literally thousands of sites can be hosted this way on a reasonable server. The problem is that any given account has limited access to configure the server (by necessity; as any change might affect other sites).

One server could also host multiple virtual servers. Usually a special kind of OS software (called a hypervisor) is used to run complete copies of operating systems in isolation from one another. Since you have completely separate space, each user gets their own machine with which s/he can do basically whatever config changes they like. Since you have to load a whole OS, however, you have fewer virtual servers-per-physical server than you would virtual hosts-per-server. So they’re quite a bit more expensive. OTOH, you COULD run multiple virtual hosts on your virtual server (so you could decide to run dozens of sites on your virtual server).

Finally, if you have a physical server, you can run a hypervisor. Which can in turn run virtual servers. Which can in turn run virtual hosts. But you have to procure a box and get it in a data center (colocation) or just rent a dedicated physical server from your provider.

In summary:

* vhost - less control, cheap
* vserver - more control, expensive
* physical server - most control, most expensive
