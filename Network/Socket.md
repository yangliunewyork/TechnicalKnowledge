
## Socket vs Port
A socket represents a single connection between two network applications. These two applications nominally run on different computers, but sockets can also be used for interprocess communication on a single computer. Applications can create multiple sockets for communicating with each other. Sockets are bidirectional, meaning that either side of the connection is capable of both sending and receiving data. Therefore a socket can be created theoretically at any level of the OSI model from 2 upwards. Programmers often use sockets in network programming, albeit indirectly. Programming libraries like Winsock hide many of the low-level details of socket programming. Sockets have been in widespread use since the early 1980s.

A port represents an endpoint or "channel" for network communications. Port numbers allow different applications on the same computer to utilize network resources without interfering with each other. Port numbers most commonly appear in network programming, particularly socket programming. Sometimes, though, port numbers are made visible to the casual user. For example, some Web sites a person visits on the Internet use a URL like the following:

http://www.mairie-metz.fr:8080/ In this example, the number 8080 refers to the port number used by the Web browser to connect to the Web server. Normally, a Web site uses port number 80 and this number need not be included with the URL (although it can be).

In IP networking, port numbers can theoretically range from 0 to 65535. Most popular network applications, though, use port numbers at the low end of the range (such as 80 for HTTP).

Think of your machine as an apartment building:

* An IP address is the street address of the building.
* A port is an apartment number.
* A socket is the door of an apartment. (apartment can have multiple doors)
