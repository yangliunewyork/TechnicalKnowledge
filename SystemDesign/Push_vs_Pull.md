__In push protocols, the client opens a connection to the server and keeps it constantly active. The server will send (push) all new events to the client using that single always-on connection.__ In other words, the server PUSHes the new events to the client.

__In pull protocols, the client periodically connects to the server, checks for and gets (pulls) recent events and then closes the connection and disconnects from the server.__ The client repeats this whole procedure to get updated about new events. In this mode, the clients periodically PULLs the new events from the server.

The difference is that in push protocols, you get new events (such as a new email, a new chat message, etc) literally instantly. But you may experience a small time delay in pull protocols. Although many apps using the pull protocol, check for new events so regular (e.g. every 30 seconds) that the time delay is mostly not noticeable.

For example, your cell phone is always connected to the mobile network. You can tell this by the signal bars on your phone's screen. When a caller calls, the network sends the call to your cell phone via that active connection your cell phone already have. This is PUSH.

But, when you're waiting for a specific program on your TV, you repeatedly turn it on and check if your program started and then turn in off. This is PULL.

##### Example, SMTP vs HTTP

Let’s now briefly compare SMTP with HTTP. Both protocols are used to transfer files from one host to another: HTTP transfers files (also called objects) from a Web server to a Web client (typically a browser); SMTP transfer files (that is, e-mail messages) from one mail server to another mail server. When transferring the files, both persistent HTTP and SMTP use persistent connections. Thus, the two protocols have common characteristics. However, there are important differences. First, HTTP is mainly a pull protocol – someone loads information on a web server and users use HTTP to pull the information from the server at their convenience. In particular, the TCP connection is initiated by the machine that wants to receive the file. On the other hand, SMTP is primarily a push protocol – the sending mail server pushes the file to the receiving mail server. In particular, the TCP connection is initiated by the machine that wants to send the file.

A second difference, which we alluded to earlier, is that SMTP requires each message, including the body of each message, to be in 7-bit ASCII format. If the message contains characters that are not 7-bit ASCII (for example, French characters with accents) or contain binary data (such as an image file), then the message has to be encoded into 7-bit ASCII. HTTP data does not impose this restriction.

A third important difference concerns how a document consisting of text and images (along with possibly other media types) is handled. HTTP encapsulates each object in its own HTTP response message. Internet mail places all of the message’s objects into on messasge.
