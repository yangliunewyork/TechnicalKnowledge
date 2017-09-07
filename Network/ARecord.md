### What is an A record?

An A record maps a domain name to the IP address (IPv4) of the computer hosting the domain. Simply put, an A record is used to find the IP address of a computer connected to the internet from a name.

The A in A record stands for Address. Whenever you visit a web site, send an email, connect to Twitter or Facebook or do almost anything on the Internet, the address you enter is a series of words connected with dots.

For example, to access the DNSimple website you enter www.dnsimple.com. At our name server there is an A record that points to the IP address 208.93.64.253. This means that a request from your browser to www.dnsimple.com is directed to the server with IP address 208.93.64.253.

A Records are the simplest type of DNS records, yet one of the primary records used in DNS servers.

You can actually do quite a bit more with A records, including using multiple A records for the same domain in order to provide redundancy. Additionally, multiple names could point to the same address, in which case each would have its own A record pointing to the that same IP address.

##### How many A (host) records can a domain have?

Functionally a zone can have an infinite number of A records but if you have a large number of A's in a DNS round robin then there can be performance implications from the switch to TCP instead of UDP due to response packet sizes.

For example, let's say you have the domain example.com and you want to serve www.example.com using DNS round robin for cheap load balancing. You'd configure it like this (from a BIND zone file):

```
www             IN      A       127.0.0.1
www             IN      A       127.0.0.2
www             IN      A       127.0.0.3
```

This is perfectly normal and is in use all over the Internet. However, if you expanded this round robin to many, many more A records (more than a couple dozen) then the response that the DNS server sends to clients will grow in size. DNS is primarily transmitted over UDP but in some situations will use TCP instead. 


### Querying A records

You can use dig to determine the A record associated to a domain name. The result is contained in the ANSWER section and it contains the fully-qualified domain name (FQDN), the remaining time-to-live (TTL) and the IP address.
```
$ dig A api.dnsimple.com

; <<>> DiG 9.8.3-P1 <<>> A api.dnsimple.com
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 5792
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;api.dnsimple.com.		IN	A

;; ANSWER SECTION:
api.dnsimple.com.	59	IN	A	208.93.64.253

;; Query time: 80 msec
;; SERVER: 8.8.8.8#53(8.8.8.8)
;; WHEN: Sun Jul 31 22:21:31 2016
;; MSG SIZE  rcvd: 50
```
### A record format

In DNSimple we represent A record with the following information:

* __Name__	The host name for the record, without the domain name. This is generally referred as “subdomain”. We automatically append the domain name.
* __TTL__	The time-to-leave in seconds. This is the amount of time the record is allowed to be cached by a resolver.
* __Address__	The IPv4 address the A record points to.
