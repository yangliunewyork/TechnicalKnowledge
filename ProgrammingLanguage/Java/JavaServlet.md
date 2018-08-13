https://www.javatpoint.com/servlet-tutorial

# Watch this

https://www.youtube.com/watch?v=7TOmdDJc14s&list=PLsyeobzWxl7oGCz4k9VyxhfmQpSU1dV9b  

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

A servlet life cycle can be defined as the entire process from its creation till the destruction. The following are the paths followed by a servlet.

1. The servlet is initialized by calling the init() method.  
2. The servlet calls service() method to process a client's request.  
3. The servlet is terminated by calling the destroy() method.  
4. Finally, servlet is garbage collected by the garbage collector of the JVM.  

#### The init() Method

The init method is called only once. It is called only when the servlet is created, and not called for any user requests afterwards. So, it is used for one-time initializations, just as with the init method of applets.

The servlet is normally created when a user first invokes a URL corresponding to the servlet, but you can also specify that the servlet be loaded when the server is first started.

When a user invokes a servlet, a single instance of each servlet gets created, with each user request resulting in a new thread that is handed off to doGet or doPost as appropriate. The init() method simply creates or loads some data that will be used throughout the life of the servlet.

The init method definition looks like this −

```java
public void init() throws ServletException {
   // Initialization code...
}
```

#### The service() Method
The service() method is the main method to perform the actual task. The servlet container (i.e. web server) calls the service() method to handle requests coming from the client( browsers) and to write the formatted response back to the client.

Each time the server receives a request for a servlet, the server spawns a new thread and calls service. The service() method checks the HTTP request type (GET, POST, PUT, DELETE, etc.) and calls doGet, doPost, doPut, doDelete, etc. methods as appropriate.

Here is the signature of this method −

```java
public void service(ServletRequest request, ServletResponse response) 
   throws ServletException, IOException {
}
```

The service () method is called by the container and service method invokes doGet, doPost, doPut, doDelete, etc. methods as appropriate. So you have nothing to do with service() method but you override either doGet() or doPost() depending on what type of request you receive from the client.

The doGet() and doPost() are most frequently used methods with in each service request. Here is the signature of these two methods.

#### The destroy() Method

The destroy() method is called only once at the end of the life cycle of a servlet. This method gives your servlet a chance to close database connections, halt background threads, write cookie lists or hit counts to disk, and perform other such cleanup activities.

After the destroy() method is called, the servlet object is marked for garbage collection. The destroy method definition looks like this −

```java
public void destroy() {
   // Finalization code...
}
```

#### Architecture Diagram

The following figure depicts a typical servlet life-cycle scenario.

<img src="https://www.tutorialspoint.com/servlets/images/servlet-lifecycle.jpg">

* First the HTTP requests coming to the server are delegated to the servlet container.  
* The servlet container loads the servlet before invoking the service() method.  
* Then the servlet container handles multiple requests by spawning multiple threads, each thread executing the service() method of a single instance of the servlet.  


# Q & A

##### How many objects of a servlet are created for multiple requests?

Servlet is instanciated as singleton in servlet container, thats why we can't declare global variables in it.

Servlets are managed resources in the servlet container, whenever a request comes for the servlet for the first time, servlet is loaded and instantiated and used for request processing.

A Servlet is instantiated only once in the container, and this Servelt object is used for any further request processing, be it another 15-20 different requests, this servlet object is shared among the different requests.

So is there any thing that is shared amongst requests you need to manage synchronization.

##### Why Servlets are not thread Safe?

Servlets are normal java classes and thus are NOT Thread Safe.

But that said, Java classes are Thread safe if you do not have instance variables. Only instance variables need to synchronize. (Instance variable are variables declared in the class and not in within its methods.
