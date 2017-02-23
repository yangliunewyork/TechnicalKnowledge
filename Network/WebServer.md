### What is Web Server ?

![alt](http://www.ibm.com/support/knowledgecenter/SSAW57_8.5.5/com.ibm.websphere.nd.multiplatform.doc/ae/images/inst_was_nd_sa_2nodes_en.gif)

A web server is a computer system that processes requests via HTTP, the basic network protocol used to distribute information on the World Wide Web. The term can refer to the entire system, or specifically to the software that accepts and supervises the HTTP requests.

So, a Web Server to start with is any source which provides a service on a Client-Server based model, typically over HTTP protocol. The whole and sole task of the web server is to continuously listen to the incoming requests and understand the specifics of the request as per the knowledge of the protocol(HTTP) and dispatch the response back, again with the specifics of the protocol.

How and from where this response is computed has to be the understanding of the another application, which takes care of opening and reading files, making database connections, running algorithms and to do all that understanding the specifics and implications of the programming platform. This part or module or engine computes the response and does all the hard part and communicates back to the web server for the dispatch. Essentially this needs not to be a server, but a computational engine alone. But more often it ends up being a server to coordinate with the front heading web server.
### Web Server vs Application Server

#### Web Server
* Processes HTTP requests by responding with HTML pages
* Servers static content(html,images,etc)
* No server side programming
* No database or dynamic generation of HTML
* No fore functionality

#### Application Server
* Serves business logic to application programs through various protocols
* Handles all application operations between users and an organization's backend business applications or databases
* Deploy applications

### Overview

The primary function of a web server is to store, process and deliver web pages to clients. The communication between client and server takes place using the Hypertext Transfer Protocol (HTTP). Pages delivered are most frequently HTML documents, which may include images, style sheets and scripts in addition to text content.

A user agent, commonly a web browser or web crawler, initiates communication by making a request for a specific resource using HTTP and the server responds with the content of that resource or an error message if unable to do so. The resource is typically a real file on the server's secondary storage, but this is not necessarily the case and depends on how the web server is implemented.

While the primary function is to serve content, a full implementation of HTTP also includes ways of receiving content from clients. This feature is used for submitting web forms, including uploading of files.


### Load limits
A web server (program) has defined load limits, because it can handle only a limited number of concurrent client connections (usually between 2 and 80,000, by default between 500 and 1,000) per IP address (and TCP port) and it can serve only a certain maximum number of requests per second (RPS, also known as queries per second or QPS) depending on:

* its own settings,
* the HTTP request type,
* whether the content is static or dynamic,
* whether the content is cached
* the hardware and software limitations of the OS of the computer on which the web server runs.

When a web server is near to or over its limit, it becomes unresponsive.


#### Common Web Servers

* Apache
* IIS
* GWS


## WEB SERVERS & WEB SERVICES

### Web Servers

A server is “a computer or device on a network that manages network resources.” (http://www.webopedia.com/TERM/s/server.html) There are many different kinds of servers: the dial-up server that serves as a gateway for the user to access the rest of the Internet; the printer server that manages one or more printers connected to the network, allowing users to access various printers remotely; and Web Servers that stores web pages and other data and information that are provided to users upon request.

A Web Server is the central nervous system of Web Site. It is the Web Server that hosts both the components of a Web page such as the actual Web page HTML files, CSS files and templates and all other essential technologies that make a Web site function the way it does. Although all Web servers function similarly, the set up and the way a server could be set can vary drastically.

There are two common ways to setting up Web Servers: P2P and Client-Server. P2P, or Peer-to-Peer, indicates a direct connection of individual computers to one another where each computer can specify what data it is willing to share. (http://www.hchs.hc.edu.tw/cc/計概/網路的架構.htm) This kind of network is very easy and cheap to set up. Furthermore, the speed of file transfer in a P2P network is not constrained by the capability of any single server/computer. Since each computer in the network is capable of becoming a server on its own, a file could be shared and transferred from multiple servers at the same time, thus increasing the file transfer rate. However, since each computer in the network is a server, each computer on the network needs to be set up individually. The responsibility of managing the system lies in the hands of every single owner of every single computer that is connected to the network. Consequently, the management of a P2P network is extremely difficult. Due to the decentralized management of the network, servers with a P2P connection are susceptible to virus and worm attacks.

The Client-Server network, on the other hand, is a highly centralized network system with one central computer as the server. This set up is easy to manage and secure. Yet, maintaining a centralized network requires tremendous amount of resources ranging from manpower to hardware. As a result, the cost of a client-server network is very high. Another drawback of a client-server set up is that the speed of file transfer between the client and the server slows down when the number of clients accessing the server at a time is too high. Nevertheless, because of its ease to manage and good security, client-server network is still the dominant set up of Web Servers. Apache, a free server technology, is currently one of the most popular server technologies in use today.

The first version of Apache, based on the NCSA httpd Web Server, was developed in 1995 by a “loosely-knit group of [about 20] programmers.” (http://www.webopedia.com/TERM/A/Apache_Web_server.html) Apache provides full source code and an unrestrictive license. Apache users can easily change, adapt, or modify the software in accordance with the needs of their particular organization. Additional modules, either written by the user or downloaded free of charge from the vast Apache module library online, could easily be added to accommodate any specific needs of the user. Apache is also capable of performing many functions such as DBM database authentication, multiple DirectoryIndex directives, unlimited flexible URL rewriting and aliasing, content negotiation and virtual hosts.

### Web Services

Web Service is a very powerful tool that has greatly enhanced the efficiency and communication among businesses. According to the World Wide Web Consortium, “a Web Service is a software system designed to support interoperable machine-to-machine interaction over a network.” (http://www.w3.org/TR/2003/WD-ws-arch-20030808/#id2608472) Alternatively, Zeldman defines Web Services as a “reusable software components based on XML and related protocols that enable near zero-cost interaction throughout the business ecosystem.” (Zeldman, p. 112) In other words, Web Services is a software system that allows machines (including servers) to communicate with each other regardless of each individual machine’s operating systems and programming languages. The Symon's Extensible Markup Language (XML) Page provides a very nice formula that neatly defines the major components of Web Services: “Web services = XML + SOAP + WSDL + UDDI” (http://home.earthlink.net/~symonchang/xml.htm).

Extensible Markup Language (XML) is the universal markup language that all machines are capable of understanding. In the process of inter-machine communication via Web services, XML is used to tag the data involved. Web Services Description Language (WSDL), on the other hand, is being used for describing the services available. Then Universal Description, Discovery and Integration (UDDI) lists the services available from that particular machine. Lastly, Simple Object Access Protocol (SOAP) is used to transfer data for each exchange of information between machines and servers, which typically involve “HTTP with an XML serialization in conjunction with other Web-related standards.” (http://www.w3.org/TR/2003/WD-ws-arch-20030808/#id2608472) Consequently, Web Services “are not tied to any one operating system or programming language.” As a result, via Web Services, Java based programs will be able to talk to servers running C++ based programs and a Windows machine will be able to communicate with a LINUX machine. (http://www.webopedia.com/TERM/W/Web_services.html)

While serving a similar function as the Web, Web Services do have some significant differences. The most prominent difference between Web services and the Web is that instead of a user interface, Web Services functions via application interfaces. In other words, the machines communicate with each other application to application. Such exchanges limit possible user errors and thus increase the efficiency of the exchange.

### How HTTP, Web Servers and Web Services Work Together

The interaction among HTTP, Web Servers and Web Services is simple: HTTP is a simple protocol browsers use to communicate with Web Servers. Web Servers, on the other hand, fulfill users’ requests and store the information users provide. Meanwhile, Web Services allow different Web Servers to communicate and interact with one another in order to process the request and/or commands of the user.

A good example of how the interconnectivity among the three technologies works would be a user trying to buy a plane ticket online. The user would access a travel agency’s Web page to query for the availability of seats, date and time of the flight and prices of the plane ticket. In this querying process, HTTP acts as the language that users end up using to communicate with the Web server that actually can access the information of flight date, time, seat availability and prices from the airlines database. According to the values users input into the Web page (i.e. GUI) and transmitted to the Web server via HTTP, the Web server performs the command of search by sending out commands of this query to each individual airline’s flight schedule databases using an application to application interface, i.e. Web services. Web services translate whichever markup language the Web server uses into the universally understood XML that gets relayed to the databases of all the airlines. When the XML is received by the airline databases, Web services then translates the XML into whatever programming language that each database is using so that the database would be able to understand the command the Web server sent out. After the query has been completed, the result would be transmitted back to the Web server through Web services again. Then the Web server would relay these search results to the user via HTTP which would present the information to the user through an HTML file that could be interpreted by a browser.

In sum, the simple function of querying for flight schedules and seats requires all three technologies, HTTP, Web server and Web services, to work together. Without any of these technologies, the query would fail or the scope of the search would be drastically limited.
