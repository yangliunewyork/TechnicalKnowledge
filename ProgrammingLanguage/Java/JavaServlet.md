https://www.javatpoint.com/servlet-tutorial

## What is Java Servlet ?
A Java servlet is a Java program that extends the capabilities of a server. Although servlets can respond to any types of requests, they most commonly implement applications hosted on __Web servers__. Such Web servlets are the Java counterpart to other dynamic Web content technologies such as PHP and ASP.NET.

## Introduction
A Java servlet processes or stores a Java class in Java EE that conforms to the Java Servlet API, a standard for implementing Java classes that respond to requests. Servlets could in principle communicate over any client–server protocol, but they are most often used with the HTTP protocol. Thus "servlet" is often used as shorthand for "HTTP servlet". Thus, a software developer may use a servlet to add dynamic content to a web server using the Java platform. The generated content is commonly HTML, but may be other data such as XML. Servlets can maintain state in session variables across many server transactions by using HTTP cookies, or URL rewriting.

To deploy and run a servlet, a __web container__ must be used. A web container (also known as a servlet container) is essentially the component of a web server that interacts with the servlets. The web container is responsible for managing the lifecycle of servlets, mapping a URL to a particular servlet and ensuring that the URL requester has the correct access rights.

The Servlet API, contained in the Java package hierarchy javax.servlet, defines the expected interactions of the web container and a servlet.

A Servlet is an object that receives a request and generates a response based on that request. The basic Servlet package defines Java objects to represent servlet requests and responses, as well as objects to reflect the servlet's configuration parameters and execution environment. The package javax.servlet.http defines HTTP-specific subclasses of the generic servlet elements, including session management objects that track multiple requests and responses between the web server and a client. Servlets may be packaged in a WAR file as a web application.

## Servelet vs CGI

A web application is an application accessible from the web. A web application is composed of web components like Servlet, JSP, Filter etc. and other components such as HTML. The web components typically execute in Web Server and respond to HTTP request.

__CGI(Commmon Gateway Interface)__ technology enables the web server to call an external program and pass HTTP request information to the external program to process the request. For each request, it starts a new process.

![alt](https://www.javatpoint.com/images/cgi.JPG)

There are many problems in CGI technology:

* If number of clients increases, it takes more time for sending response.
* For each request, it starts a process and Web server is limited to start processes.
* It uses platform dependent language e.g. C, C++, perl.


![alt](https://www.javatpoint.com/images/servlet.JPG)

There are many advantages of servlet over CGI. The web container creates threads for handling the multiple requests to the servlet. Threads have a lot of benefits over the Processes such as they share a common memory area, lightweight, cost of communication between the threads are low. The basic benefits of servlet are as follows:

* Better performance: because it creates a thread for each request not process.
* Portability: because it uses java language.
* Robust: Servlets are managed by JVM so we don't need to worry about memory leak, garbage collection etc.
* Secure: because it uses java language..

## Life cycle of a servlet

