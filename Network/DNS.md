### What is DNS ?
The Domain Name System (aka DNS) is used to resolve human-readable hostnames like www.Dyn.com into machine-readable IP addresses like 204.13.248.115. DNS also provides other information about domain names, such as mail services.
### Why is DNS important?
DNS is like a phone book for the Internet. If you know a person’s name but don’t know their telephone number, you can simply look it up in a phone book. DNS provides this same service to the Internet.
When you visit http://dyn.com in a browser, your computer uses DNS to retrieve the website’s IP address of 204.13.248.115. Without DNS, you would only be able to visit our website (or any website) by visiting its IP address directly, such as http://204.13.248.115.

### How does DNS work?

![alt](http://ecoupon.io/wp-content/uploads/2016/05/how-dns-works-wm.png)

When you visit a domain such as dyn.com, your computer follows a series of steps to turn the human-readable web address into a machine-readable IP address. This happens every time you use a domain name, whether you are viewing websites, sending email or listening to Internet radio stations like Pandora.

Step 1: Request information

The process begins when you ask your computer to resolve a hostname, such as visiting http://dyn.com. The first place your computer looks is its local DNS cache, which stores information that your computer has recently retrieved.

If your computer doesn’t already know the answer, it needs to perform a DNS query to find out.

Step 2: Ask the recursive DNS servers

If the information is not stored locally, your computer queries (contacts) your ISP’s recursive DNS servers. These specialized computers perform the legwork of a DNS query on your behalf. Recursive servers have their own caches, so the process usually ends here and the information is returned to the user.

Step 3: Ask the root nameservers

If the recursive servers don’t have the answer, they query the root nameservers. A nameserver is a computer that answers questions about domain names, such as IP addresses. The thirteen root nameservers act as a kind of telephone switchboard for DNS. They don’t know the answer, but they can direct our query to someone that knows where to find it.

Step 4: Ask the TLD nameservers

The root nameservers will look at the first part of our request, reading from right to left — www.dyn.com — and direct our query to the Top-Level Domain (TLD) nameservers for .com. Each TLD, such as .com, .org, and .us, have their own set of nameservers, which act like a receptionist for each TLD. These servers don’t have the information we need, but they can refer us directly to the servers that do have the information.

Step 5: Ask the authoritative DNS servers

The TLD nameservers review the next part of our request — www.dyn.com — and direct our query to the nameservers responsible for this specific domain. These authoritative nameservers are responsible for knowing all the information about a specific domain, which are stored in DNS records. There are many types of records, which each contain a different kind of information. In this example, we want to know the IP address for www.dyndns.com, so we ask the authoritative nameserver for the Address Record (A).

Step 6: Retrieve the record

The recursive server retrieves the A record for dyn.com from the authoritative nameservers and stores the record in its local cache. If anyone else requests the host record for dyn.com, the recursive servers will already have the answer and will not need to go through the lookup process again. All records have a time-to-live value, which is like an expiration date. After a while, the recursive server will need to ask for a new copy of the record to make sure the information doesn’t become out-of-date.

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
