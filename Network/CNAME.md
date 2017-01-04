### What is CNAME record?
A Canonical Name record (abbreviated as CNAME record) is a type of resource record in the Domain Name System (DNS) used to specify that a domain name is an alias for another domain, which is the "canonical" domain.
This can prove convenient when running multiple services (like an FTP server and a webserver; each running on different ports) from a single IP address. One can, for example, point ftp.example.com and www.example.com to the DNS entry for example.com, which in turn has an A record which points to the IP address. Then, if the IP address ever changes, one only has to record the change in one place within the network: in the DNS A record for example.com.
CNAME records must always point to another domain name, never directly to an IP address.

#### Detail
CNAME records are handled specially in the domain name system, and have several restrictions on their use. When a DNS resolver encounters a CNAME record while looking for a regular resource record, it will restart the query using the canonical name instead of the original name. (If the resolver is specifically told to look for CNAME records, the canonical name (right-hand side) is returned, rather than restarting the query.) The canonical name that a CNAME record points to can be anywhere in the DNS, whether local or on a remote server in a different DNS zone.
For example, if there is a DNS zone as follows:
```
NAME                    TYPE   VALUE
--------------------------------------------------
bar.example.com.        CNAME  foo.example.com.
foo.example.com.        A      192.0.2.23
```
when an A record lookup for bar.example.com is carried out, the resolver will see a CNAME record and restart the checking at foo.example.com and will then return 192.0.2.23.


####  Differences between the A and CNAME records

The A and CNAME records are the two common ways to map a host name (name hereafter) to one or more IP address. Before going ahead, it’s important that you really understand the differences between these two records. I’ll keep it simple.

The A record points a name to a specific IP. For example, if you want the name blog.dnsimple.com to point to the server 185.31.17.133 you will configure:
```
blog.dnsimple.com.     A        185.31.17.133
```
The CNAME record points a name to another name, instead of an IP. The CNAME source represents an alias for the target name and inherits its entire resolution chain.

Let’s take our blog as example:
```
blog.dnsimple.com.      CNAME   aetrion.github.io.
aetrion.github.io.      CNAME   github.map.fastly.net.
github.map.fastly.net.  A       185.31.17.133
```
We use GitHub Pages and we set blog.dnsimple.com as a CNAME of aetrion.github.io, which in turns is itself a CNAME of github.map.fastly.net, which is an A record pointing to 185.31.17.133. In short terms, this means that blog.dnsimple.com resolves to 185.31.17.133.

To summarize, an A record points a name to an IP. CNAME record can point a name to another CNAME or an A record.
