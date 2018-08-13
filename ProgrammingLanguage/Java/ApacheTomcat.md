## What is Apache Tomcat ?
Apache Tomcat, often referred to as Tomcat Server, is an open-source Java Servlet Container developed by the Apache Software Foundation (ASF). Tomcat implements several Java EE specifications including Java Servlet, JavaServer Pages (JSP), Java EL, and WebSocket, and provides a "pure Java" HTTP web server environment in which Java code can run.

Tomcat is developed and maintained by an open community of developers under the auspices of the Apache Software Foundation, released under the Apache License 2.0 license, and is open-source software.

### Apache HTTP Server vs Apache Tomcat 

In general, the Apache HTTP server is just a plain old web server designed to serve static web pages. There are plenty of modules which can be installed to enhance Apache's abilities so that it can serve dynamic webpages using various technologies such as PHP, CGI or whatever, but the core of Apache is just a plain old HTTP server.

Tomcat, on the other hand, is specifically designed from the ground-up to serve as a Java Servlet engine. It's primary purpose is to implement the Java Servlet API and execute Java servlets for the purpose of building dynamic websites. Tomcat can also be used as a regular HTTP server that serves static pages, but that is not its primary purpose. (Also, Tomcat is allegedly slower than Apache httpd when it comes to serving static pages.)

The two technologies can be used together through a connector module called mod_jk. This will allow you to use the Apache HTTP server to serve regular static webpages, and the Tomcat Servlet engine to execute servlets.

