### What is DNS ?
The Domain Name System (aka DNS) is used to resolve human-readable hostnames like www.Dyn.com into machine-readable IP addresses like 204.13.248.115. DNS also provides other information about domain names, such as mail services.
### Why is DNS important?
DNS is like a phone book for the Internet. If you know a person’s name but don’t know their telephone number, you can simply look it up in a phone book. DNS provides this same service to the Internet.
When you visit http://dyn.com in a browser, your computer uses DNS to retrieve the website’s IP address of 204.13.248.115. Without DNS, you would only be able to visit our website (or any website) by visiting its IP address directly, such as http://204.13.248.115.

### Services Provided by DNS
We have just seen that there are two ways to identify a host—by a hostname and by an IP address. People prefer the more mnemonic hostname identifier, while routers prefer fixed-length, hierarchically structured IP addresses. In order to reconcile these preferences, we need a directory service that translates hostnames to IP addresses. This is the main task of the Internet’s domain name system (DNS). The DNS is (1) a distributed database implemented in a hierarchy of DNS servers, and (2) an application-layer protocol that allows hosts to query the distributed database. The DNS servers are often UNIX machines running the Berkeley Internet Name Domain (BIND) software [BIND 2012]. The DNS protocol runs over UDP and uses port 53.

DNS provides a few other important services in addition to translating hostnames to IP addresses:
* __Host aliasing.__ A host with a complicated hostname can have one or more alias names. For example, a hostname such as relay1.west-coast.enterprise. com could have, say, two aliases such as enterprise.com and www.enterprise.com. In this case, the hostname relay1.westcoast. enterprise.com is said to be a __canonical hostname__. Alias hostnames, when present, are typically more mnemonic than canonical hostnames.DNS can be invoked by an application to obtain the canonical hostname for a supplied alias hostname as well as the IP address of the host.
* __Mail server aliasing.__ For obvious reasons, it is highly desirable that e-mail addresses be mnemonic. For example, if Bob has an account with Hotmail, Bob’s e-mail address might be as simple as bob@hotmail.com. However, the hostname of the Hotmail mail server is more complicated and much less mnemonic than simply hotmail.com (for example, the canonical hostname might be something like relay1.west-coast.hotmail.com). DNS can be invoked by a mail application to obtain the canonical hostname for a supplied alias hostname as well as the IP address of the host. In fact, the MX record (see below) permits a company’s mail server and Web server to have identical (aliased) hostnames; for example, a company’s Web server and mail server can both be called enterprise.com.
* __Load distribution.__ DNS is also used to perform load distribution among replicated servers, such as replicated Web servers. Busy sites, such as cnn.com, are replicated over multiple servers, with each server running on a different end system and each having a different IP address. For replicated Web servers, a set of IP addresses is thus associated with one canonical hostname. The DNS database contains this set of IP addresses. When clients make a DNS query for a name mapped to a set of addresses, the server responds with the entire set of IP addresses, but rotates the ordering of the addresses within each reply. Because a client typically sends its HTTP request message to the IP address that is listed first in the set, DNS rotation distributes the traffic among the replicated servers.


## Overview of How DNS Works

#### A Distributed, Hierarchical Database

![alt](https://upload.wikimedia.org/wikipedia/commons/b/b1/Dns-server-hierarchy.gif)

Three classes of DNS servers: 
* __Root DNS servers.__ In the Internet there are 13 root DNS servers (labeled A through M), most of which are located in North America. An October 2006 map of the root DNS servers is shown in Figure 2.20; a list of the current root DNS servers is available via [Root-servers 2012]. Although we have referred to each of the 13 root DNS servers as if it were a single server, each “server” is actually a network of replicated servers, for both security and reliability purposes. All together, there are 247 root servers as of fall 2011. 
* __Top-level domain (TLD) servers.__ These servers are responsible for top-level domains such as com, org, net, edu, and gov, and all of the country top-level domains such as uk, fr, ca, and jp. The company Verisign Global Registry Services maintains the TLD servers for the com top-level domain, and the company Educause maintains the TLD servers for the edu top-level domain. 
* __Authoritative DNS servers.__ Every organization with publicly accessible hosts (such as Web servers and mail servers) on the Internet must provide publicly accessible DNS records that map the names of those hosts to IP addresses. An organization’s authoritative DNS server houses these DNS records. An organization can choose to implement its own authoritative DNS server to hold these records; alternatively, the organization can pay to have these records stored in an authoritative DNS server of some service provider. Most universities and large companies implement and maintain their own primary and secondary (backup) authoritative DNS server.

There is another important type of DNS server called the __local DNS server__. A local DNS server does not strictly belong to the hierarchy of servers but is nevertheless central to the DNS architecture. Each ISP—such as a university, an academic department, an employee’s company, or a residential ISP—has a local DNS server (also called a default name server). When a host connects to an ISP, the ISP provides the host with the IP addresses of one or more of its local DNS servers (typically through DHCP, which is discussed in Chapter 4). You can easily determine the IP address of your local DNS server by accessing network status windows in Windows or UNIX. A host’s local DNS server is typically “close to” the host. For an institutional ISP, the local DNS server may be on the same LAN as the host; for a residential ISP, it is typically separated from the host by no more than a few routers. When a host makes a DNS query, the query is sent to the local DNS server, which acts a proxy, forwarding the query into the DNS server hierarchy.

![alt](http://electronicspost.com/wp-content/uploads/2016/05/2.21.png)

Let’s take a look at a simple example. Suppose the host cis.poly.edu desires the IP address of gaia.cs.umass.edu. Also suppose that Polytechnic’s local DNS server is called dns.poly.edu and that an authoritative DNS server for gaia.cs.umass.edu is called dns.umass.edu. As shown in Figure 2.21, the host cis.poly.edu first sends a DNS query message to its local DNS server, dns.poly.edu. The query message contains the hostname to be translated, namely, gaia.cs.umass.edu. The local DNS server forwards the query message to a root DNS server. The root DNS server takes note of the edu suffix and returns to the local DNS server a list of IP addresses for TLD servers responsible for edu. The local DNS server then resends the query message to one of these TLD servers. The TLD server takes note of the umass.edu suffix and responds with the IP address of the authoritative DNS server for the University of Massachusetts, namely, dns.umass.edu. Finally, the local DNS server resends the query message directly to dns.umass.edu, which responds with the IP address of gaia.cs.umass.edu. Note that in this example, in order to obtain the mapping for one hostname, eight DNS messages were sent: four query messages and four reply messages!

![alt](http://www.networkinginfoblog.com/contentsimages/Recursive%20queries%20in%20DNS.JPG)

The example shown in Figure 2.21 makes use of both recursive queries and iterative queries. The query sent from cis.poly.edu to dns.poly.edu is a recursive query, since the query asks dns.poly.edu to obtain the mapping on its behalf. But the subsequent three queries are iterative since all of the replies are directly returned to dns.poly.edu. In theory, any DNS query can be iterative or recursive. For example, Figure 2.22 shows a DNS query chain for which all of the queries are recursive. In practice, the queries typically follow the pattern in Figure 2.21: The query from the requesting host to the local DNS server is recursive, and the remaining queries are iterative.

#### DNS Caching
Our discussion thus far has ignored DNS caching, a critically important feature of the DNS system. In truth, DNS extensively exploits DNS caching in order to improve the delay performance and to reduce the number of DNS messages ricocheting around the Internet. The idea behind DNS caching is very simple. In a query chain, when a DNS server receives a DNS reply (containing, for example, a mapping from a hostname to an IP address), it can cache the mapping in its local memory. For example, in Figure 2.21, each time the local DNS server dns.poly.edu receives a reply from some DNS server, it can cache any of the information contained in the reply. If a hostname/IP address pair is cached in a DNS server and another query arrives to the DNS server for the same hostname, the DNS server can provide the desired IP address, even if it is not authoritative for the hostname. Because hosts and mappings between hostnames and IP addresses are by no means permanent, DNS servers discard cached information after a period of time (often set to two days).

As an example, suppose that a host apricot.poly.edu queries dns.poly.edu for the IP address for the hostname cnn.com. Furthermore, suppose that a few hours later, another Polytechnic University host, say, kiwi.poly.fr, also queries dns.poly.edu with the same hostname. Because of caching, the local DNS server will be able to immediately return the IP address of cnn.com to this second requesting host without having to query any other DNS servers. A local DNS server can also cache the IP addresses of TLD servers, thereby allowing the local DNS server to bypass the root DNS servers in a query chain (this often happens).

## DNS Records and Messages
The DNS servers that together implement the DNS distributed database store __resource records (RRs)__, including RRs that provide hostname-to-IP address mappings. Each DNS reply message carries one or more resource records.
A resource record is a four-tuple that contains the following fields: 

``` (Name, Value, Type, TTL) ```

TTL is the time to live of the resource record; it determines when a resource should be removed from a cache. In the example records given below, we ignore the TTL field. The meaning of __Name__ and __Value__ depend on __Type__:
* If Type=A, then Name is a hostname and Value is the IP address for the hostname. Thus, a Type A record provides the standard hostname-to-IP address mapping. As an example, (relay1.bar.foo.com, 145.37.93.126, A) is a Type A record.
* If Type=NS, then Name is a domain (such as foo.com) and Value is the hostname of an authoritative DNS server that knows how to obtain the IP addresses for hosts in the domain. This record is used to route DNS queries further along in the query chain. As an example, (foo.com, dns.foo.com, NS) is a Type NS record.
* If Type=CNAME, then Value is a canonical hostname for the alias hostname Name. This record can provide querying hosts the canonical name for a hostname. As an example, (foo.com, relay1.bar.foo.com, CNAME) is a CNAME record.
* If Type=MX, then Value is the canonical name of a mail server that has an alias hostname Name. As an example, (foo.com, mail.bar.foo.com, MX) is an MX record. MX records allow the hostnames of mail servers to have simple aliases. Note that by using the MX record, a company can have the same aliased name for its mail server and for one of its other servers (such as its Web server). To obtain the canonical name for the mail server, a DNS client would query for an MX record; to obtain the canonical name for the other server, the DNS client would query for the CNAME record.

If a DNS server is authoritative for a particular hostname, then the DNS server will contain a Type A record for the hostname. (Even if the DNS server is not authoritative, it may contain a Type A record in its cache.) If a server is not authoritative for a hostname, then the server will contain a Type NS record for the domain that includes the hostname; it will also contain a Type A record that provides the IP address of the DNS server in the Value field of the NS record. As an example, suppose an edu TLD server is not authoritative for the host gaia.cs.umass.edu. Then this server will contain a record for a domain that includes the host gaia.cs.umass.edu, for example, (umass.edu, dns.umass.edu, NS). The edu TLD server would also contain a Type Arecord, which maps the DNS server dns.umass.edu to an IP address, for example, (dns.umass.edu, 128.119.40.111, A).



## How does DNS work?

![alt](http://ecoupon.io/wp-content/uploads/2016/05/how-dns-works-wm.png)

When you visit a domain such as dyn.com, your computer follows a series of steps to turn the human-readable web address into a machine-readable IP address. This happens every time you use a domain name, whether you are viewing websites, sending email or listening to Internet radio stations like Pandora.

Step 1: Request information

The process begins when you ask your computer to resolve a hostname, such as visiting http://dyn.com. The first place your computer looks is its local DNS cache, which stores information that your computer has recently retrieved. Computer's local DNS cache includes browser and operating system's cache. 
If your computer doesn’t already know the answer, it needs to perform a DNS query to find out.

Step 2: Ask the recursive DNS servers

If the information is not stored locally, your computer queries (contacts) your __ISP’s recursive DNS servers__. These specialized computers perform the legwork of a DNS query on your behalf. Recursive servers have their own caches, so the process usually ends here and the information is returned to the user.

Step 3: Ask the root nameservers

If the recursive servers don’t have the answer, they query the __root nameservers__. A nameserver is a computer that answers questions about domain names, such as IP addresses. The thirteen root nameservers act as a kind of telephone switchboard for DNS. They don’t know the answer, but they can direct our query to someone that knows where to find it.

Step 4: Ask the TLD nameservers

The root nameservers will look at the first part of our request, reading from right to left — www.dyn.com — and direct our query to the __Top-Level Domain (TLD) nameservers__ for .com. Each TLD, such as .com, .org, and .us, have their own set of nameservers, which act like a receptionist for each TLD. These servers don’t have the information we need, but they can refer us directly to the servers that do have the information.

Step 5: Ask the authoritative DNS servers

The TLD nameservers review the next part of our request — www.dyn.com — and direct our query to the nameservers responsible for this specific domain. These __authoritative nameservers__ are responsible for knowing all the information about a specific domain, which are stored in DNS records. There are many types of records, which each contain a different kind of information. In this example, we want to know the IP address for www.dyndns.com, so we ask the authoritative nameserver for the __Address Record (A)__.

Step 6: Retrieve the record

The recursive server retrieves the A record for dyn.com from the authoritative nameservers and stores the record in its local cache. If anyone else requests the host record for dyn.com, the recursive servers will already have the answer and will not need to go through the lookup process again. All records have a __time-to-live__ value, which is like an expiration date. After a while, the recursive server will need to ask for a new copy of the record to make sure the information doesn’t become out-of-date.

Step 7: Receive the answer

Armed with the answer, recursive server returns the A record back to your computer. Your computer stores the record in its cache, reads the IP address from the record, then passes this information to your browser. The browser then opens a connection to the webserver and receives the website.

This entire process, from start to finish, takes only milliseconds to complete.

### Authoritative name server
An authoritative name server provides actual answer to your DNS queries such as – mail server IP address or web site IP address (A resource record). It provides original and definitive answers to DNS queries. It does not provides just cached answers that were obtained from another name server. Therefore it only returns answers to queries about domain names that are installed in its configuration system. There are two types of Authoritative Name Servers:

1. Master server (primary name server) – A master server stores the original master copies of all zone records. A hostmaster only make changes to master server zone records. Each slave server gets updates via special automatic updating mechanism of the DNS protocol. All slave servers maintain an identical copy of the master records.
2. Slave server (secondary name server) – A slave server is exact replica of master server. It is used to share DNS server load and to improve DNS zone availability in case master server fails. It is recommend that you should at least have 2 slave servers and one master server for each domain name.

### Recursive query
If a name server cannot answer a query because it does not contain an entry for the host in its DNS cache, it may recursively query name servers higher up in the hierarchy.[10]This is known as a recursive query or recursive lookup.
In principle, authoritative name servers suffice for the operation of the Internet. However, with only authoritative name-servers operating, every DNS query must start with recursive queries at the root zone of the Domain Name System and each user system must implement resolver software capable of recursive operation.

### Caching name server
Caching name servers (DNS caches) store DNS query results for a period of time determined in the configuration (time-to-live) of each domain-name record. DNS caches improve the efficiency of the DNS by reducing DNS traffic across the Internet, and by reducing load on authoritative name-servers, particularly root name-servers. Because they can answer questions more quickly, they also increase the performance of end-user applications that use the DNS. Recursive name servers resolve any query they receive, even if they are not authoritative for the question being asked, by consulting the server or servers that are authoritative for the question. Caching name servers are often also recursive name servers—they perform every step necessary to answer any DNS query they receive. To do this the name server queries each authoritative name-server in turn, starting from the DNS root zone. It continues until it reaches the authoritative server for the zone that contains the queried domain name. That server provides the answer to the question, or definitively says it can't be answered, and the caching resolver then returns this response to the client that asked the question. The authority, resolving and caching functions can all be present in a DNS server implementation, but this is not required: a DNS server can implement any one of these functions alone, without implementing the others. Internet service providers typically provide caching resolvers for their customers.


## Recursive DNS

![alt](http://windowsitpro.com/site-files/windowsitpro.com/files/archive/windowsitpro.com/content/content/48527/figure_01.gif)

Recursive DNS is the piece that allows users to find the domain names that companies setup.  Consumers may not realize it, but every time they go on their computers or phones to read the news, access their bank accounts or even read this blog, they are using recursive DNS services.

#### WHAT IS RECURSIVE DNS – AND HOW DOES IT WORK?
Recursive DNS is the middle-man between the consumer and the Authoritative DNS servers that are hosting a company’s domains and the IP addresses that are associated with a domain name. Recursive DNS does two major tasks:

When a user types in a URL in their web browser, the URL is sent to the recursive DNS server first. The first task the recursive DNS server does is check its cache memory to see if the IP address for the requested URL is already stored. If the IP address information is already in memory, then the recursive DNS server will immediately provide the IP address back to the browser and the user will be taken to the website.

If the recursive DNS server does not have the IP address in memory, it will go through the process of fetching the IP address (called “walking the DNS tree”) and return it to the user. The recursive DNS server will then store the IP address in memory for a certain amount of time - the amount of time that the IP address is stored in memory is defined by the owner of the domain using a setting called “Time To Live” (TTL).

