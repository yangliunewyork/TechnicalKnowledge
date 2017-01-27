## Rule 1 - Don’t Overengineer the Solution
Overengineering (or over-engineering) is the designing of a product to be more robust or complicated than is necessary for its application, either (charitably) to ensure sufficient factor of safety, sufficient functionality, or because of design errors. Overengineering can be desirable when safety or performance on a particular criterion is critical, or when extremely broad functionality is required, but it is generally criticized from the point of view of value engineering as wasteful. As a design philosophy, such overcomplexity is the opposite of the less is more school of thought.

AsWikipedia explains, overengineering falls into two broad categories.1 The first category covers products designed and implemented to exceed the useful requirements of the product.The second category of overengineering covers products that are made to be overly complex.

## Rule 2—Design Scale into theSolution (D-I-D Process)


## Rule 3—Simplify the Solution 3 Times Over

## Rule 4—Reduce DNS Lookups
The Domain Name System (DNS) is one of the most important parts of the infrastructure of the Internet or any other network that utilizes the Internet Protocol Suite (TCP/IP). It allows the translation from domain name (www.akfpartners.com) to an IP address (184.72.236.173) and is often analogized to a phone book. DNS is maintained by a distributed database system, the nodes of which are the name servers.The top of the hierarchy consists of the root name servers. Each domain has at least one authoritative DNS server that publishes information about that domain.

This process of translating domains into IP addresses is made quicker by caching on many levels, including the browser, computer operating system, Internet service provider, and so on. However, in our world where pages can have hundreds or thousands of objects, many from different domains, small milliseconds of time can add up to something noticeable to the customer.

Browsers take advantage of the fact that almost all Web pages are comprised of many different objects (images, JavaScript files, css files, and so on) by having the ability to download multiple objects through simultaneous connections. Browsers limit the maximum number of simultaneous persistent connections per server or proxy.

Every distinct domain that serves one or more objects for a Web page requires a DNS lookup either from cache or out to a DNS name server. For example, let’s assume we have a simple Web page that has four objects: 1) the HTML page itself that contains text and directives for other objects, 2) a CSS file for the layout, 3) a JavaScript file for a menu item, and 4) a JPG image.The HTML comes from our domain (akfpartners.com), but the CSS and JPG are served from a subdomain (static.akfpartners. com), and the JavaScript we’ve linked to from Google (ajax.googleapis.com). In this scenario our browser first receives the request to go to page www.akfpartners.com, which requires a DNS lookup of the akfpartners.com domain. Once the HTML is downloaded the browser parses it and finds that it needs to download the CSS and JPG both from static.akfpartners. com, which requires another DNS lookup. Finally, the parsing reveals the need for an external JavaScript file from yet another domain. Depending on the freshness of DNS cache in our browser, operating system, and so on, this lookup can take essentially no time up to hundreds of milliseconds.As a general rule, the fewer DNS lookups on your pages the better your page download performance will be.

## Rule 5—Reduce Objects Where Possible
Web pages consist of many different objects (HTML, CSS, images, JavaScript, and so on), which allows our browsers to download them somewhat independently and often in parallel. One of the easiest ways to improve Web page performance and thus increase your scalability (fewer objects to serve per page means your servers can serve more pages) is to reduce the number of objects on a page.The biggest offenders on most pages are graphical objects such as pictures and images.

Reducing the number of objects on the page is a great way to improve performance and scalability, but before you rush off to remove all your images there are a few other things to consider.

In summary, the fewer the number of objects on a page the better for performance, but this must be balanced with many other factors. Included in these factors are the amount of content that must be displayed, how many objects can be combined, how to maximize the use of simultaneous connections by adding domains, the total page weight and whether penalization can help, and so on.While this rule touches on many Web site performance improvement techniques the real focus is how to improve performance and thus increase the scalability of your site through the reduction of objects on the page. Many other techniques for optimizing performance should be considered, including loading CSS at the top of the page and JavaScript files at the bottom, minifying files, and making use of caches, lazy loading, and so on.



