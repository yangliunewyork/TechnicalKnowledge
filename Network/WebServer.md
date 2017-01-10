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
