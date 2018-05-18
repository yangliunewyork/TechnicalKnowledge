__WAR (Web application ARchive)__ files are used to distribute Java-based web applications. A WAR has the same file structure as a JAR file, which is a single compressed file that contains multiple files bundled inside it.

WAR files are used to combine JSPs, servlets, Java class files, XML files, javascript libraries, JAR libraries, static web pages, and any other resources needed to run the application.

WAR files are usually deployed in servlet containers, but can also be deployed to Java EE application servers. When a WAR file is deployed to a container, the container usually unpacks it to access the files and then launches the application. With servlet containers being the most prolific platform for Java web applications, WAR files are not only a Java spec standard, but a very common format for distributing Java applications and supported by a wide range of tools.

WAR files cannot be edited while the application is running. Any changes require rebuilding the file.

#### Difference between jar and war files?

These files are simply zipped files using the java jar tool. These files are created for different purposes. Here is the description of these files:

* .jar files: The .jar files contain libraries, resources and accessories files like property files.  
* .war files: The war file contains the web application that can be deployed on any servlet/jsp container. The .war file contains jsp, html, javascript and other files necessary for the development of web applications.  
