## What is Web Cache ?
A web cache (or HTTP cache) is an information technology for the temporary storage (caching) of web documents, such as HTML pages and images, to reduce bandwidth usage, server load, and perceived lag. A web cache system stores copies of documents passing through it; subsequent requests may be satisfied from the cache if certain conditions are met. A web cache system can refer either to an appliance, or to a computer program.

## Pros and Cons of Web Caching

### Advantages

The advantages of web caching via proxy servers include: 

* faster access to valid cached resources
* saving on costly use of bandwidth
* imposing controls on access to dubious material
* collecting useful statistics on web access
* providing cached resources even when origin server is down

Caching offers significant overall speed ups on access to web pages of general interest. It can also reduce the costs of network accesses. Currently universities in Britain are billed on the basis of the number of megabytes they have pulled every month from the USA through JANET's transatlantic network link to the USA. Universities that deploy effective web caching by their users have markedly reduced these bills. Shared web caches can also be configured quite easily to block access to dubious web sites. In Britain this might safeguard users from breaching the law forbidding access to indecent pictures of children. Shared web cache logs can also be processed to generate useful statistics on patterns of web access by users. Shared web caches can also provide copies of resources when the resource is no longer available from its original source because that source is down.

Proxy servers can also add value to web accesses by 

* protocol translation - support protocols unknown to web browser
* support preloading for fast delivery at given time
* transparent redirection

Proxy servers can support access to services that a web browser cannot manage by itself. This might be because the proxy server has more rights and permissions than the web browser or knows URL supporting protocols like LDAP that are unknown to the web browser. Proxy servers can also have their cache primed by preloading to support rapid access to resources that might otherwise be delivered rather more slowly. This can be useful when giving demonstrations. Proxy servers can be also be configured to redirect requests to more appropriate servers. A request to a web site might be redirected to a closer mirror site which will offer the same service but rather quicker.

### Disadvantages

Disadvantages of web caching include 

* slower performance if the resource isn't found in the cache
* being given a stale copy of a resource when an uptodate copy is needed
* resources sometimes getting mangled/lost on route
* sharing an access point to the web increasing risks to service
* proxy server access logs invading the privacy of users
* proxy intermediary confusing logging and access control by subscription services

If a web page isn't found in a web cache, the user has had to wait that amount of time longer, while the cache is searched, than he would have had to wait if the remote web server had been asked for the web page in the first place. Also if the cache uses a weak cache consistency protocol, then there is always the risk that the resource delivered to the user might be out-of-date. Because going via one or more proxy servers is more complicated, there is an increased risk in the shuffle of this complexity that a web resource being transferred might get lost or mangled as it is passed along. Furthermore, if a proxy server offering a shared caching service goes down, all the web users using it will lose their access to the web until their browser is reconfigured not to use the proxy server. Whereas if those users had not been using the proxy server then they would be unaffected. Thus channeling all these HTTP requests through a proxy server increases the risks of many users suffering a simultaneous service disruption. Another commonly perceived drawback to the use of proxy servers is that their logs contain records of who has been accessing what pages on the web. This provides an opportunity for their privacy to be violated. Proxy servers can also prevent or make access control by subscription services problematic.
