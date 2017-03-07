## Introduction
Time to live (TTL) or hop limit is a mechanism that limits the lifespan or lifetime of data in a computer or network. TTL may be implemented as a counter or timestamp attached to or embedded in the data. Once the prescribed event count or timespan has elapsed, data is discarded. In computer networking, TTL prevents a data packet from circulating indefinitely. In computing applications, TTL is used to improve performance of caching or to improve privacy.

### IP packets
Under the Internet Protocol, TTL is an 8-bit field. In the IPv4 header, TTL is the 9th octet of 20. In the IPv6 header, it is the 8th octet of 40. The maximum TTL value is 255, the maximum value of a single octet. A recommended initial value is 64.

The time-to-live value can be thought of as an upper bound on the time that an IP datagram can exist in an Internet system. The TTL field is set by the sender of the datagram, and reduced by every router on the route to its destination. If the TTL field reaches zero before the datagram arrives at its destination, then the datagram is discarded and an ICMP error datagram (11 - Time Exceeded) is sent back to the sender. The purpose of the TTL field is to avoid a situation in which an undeliverable datagram keeps circulating on an Internet system, and such a system eventually becoming swamped by such "immortals".

In theory, under IPv4, time to live is measured in seconds, although every host that passes the datagram must reduce the TTL by at least one unit. In practice, the TTL field is reduced by one on every hop. To reflect this practice, the field is renamed hop limit in IPv6.

### DNS records
TTLs also occur in the Domain Name System (DNS), where they are set by an authoritative name server for a particular resource record. When a caching (recursive) nameserver queries the authoritative nameserver for a resource record, it will cache that record for the time (in seconds) specified by the TTL. If a stub resolver queries the caching nameserver for the same record before the TTL has expired, the caching server will simply reply with the already cached resource record rather than retrieve it from the authoritative nameserver again. TTL for NXDOMAIN responses is set from the minimum of the MINIMUM field of the SOA record and the TTL of the SOA itself, and indicates how long a resolver may cache the negative answer.

Shorter TTLs can cause heavier loads on an authoritative nameserver, but can be useful when changing the address of critical services like Web servers or MX records, and therefore are often lowered by the DNS administrator prior to a service being moved, in order to minimize disruptions.

The units used are seconds. An older common TTL value for DNS was 86400 seconds, which is 24 hours. A TTL value of 86400 would mean that, if a DNS record was changed on the authoritative nameserver, DNS servers around the world could still be showing the old value from their cache for up to 24 hours after the change.

Newer DNS methods that are part of a DR (Disaster Recovery) system may have some records deliberately set extremely low on TTL. For example, a 300-second TTL would help key records expire in 5 minutes to help ensure these records are flushed quickly worldwide. This gives administrators the ability to edit and update records in a timely manner. TTL values are "per record" and setting this value on specific records is sometimes honored automatically by all standard DNS systems worldwide. However, a problem persists in that some caching DNS nameservers set their own TTLs regardless of the authoritative records, so it cannot be guaranteed that all downstream DNS servers have the new records after the TTL has expired.

