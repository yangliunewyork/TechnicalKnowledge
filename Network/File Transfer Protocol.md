The File Transfer Protocol (FTP) is a standard network protocol used for the transfer of computer files between a client and server on a computer network.

FTP is built on a client-server model architecture and uses separate control and data connections between the client and the server.[1] FTP users may authenticate themselves with a clear-text sign-in protocol, normally in the form of a username and password, but can connect anonymously if the server is configured to allow it. For secure transmission that protects the username and password, and encrypts the content, FTP is often secured with SSL/TLS (FTPS) or replaced with SSH File Transfer Protocol (SFTP).

### Protocol overview

#### Communication and data transfer

<img src="https://cdn.ttgtmedia.com/rms/onlineImages/FTP_active_passive_desktop.jpg">

FTP may run in active or passive mode, which determines how the data connection is established.[6] In both cases, the client creates a TCP control connection from a random, usually an unprivileged, port N to the FTP server command port 21.

* In active mode, the client starts listening for incoming data connections from the server on port M. It sends the FTP command PORT M to inform the server on which port it is listening. The server then initiates a data channel to the client from its port 20, the FTP server data port.  
* In situations where the client is behind a firewall and unable to accept incoming TCP connections, passive mode may be used. In this mode, the client uses the control connection to send a PASV command to the server and then receives a server IP address and server port number from the server, which the client then uses to open a data connection from an arbitrary client port to the server IP address and server port number received.  

The server responds over the control connection with three-digit status codes in ASCII with an optional text message. For example, "200" (or "200 OK") means that the last command was successful. The numbers represent the code for the response and the optional text represents a human-readable explanation or request (e.g. <Need account for storing file>). An ongoing transfer of file data over the data connection can be aborted using an interrupt message sent over the control connection.

While transferring data over the network, four data representations can be used:

* ASCII mode: Used for text. Data is converted, if needed, from the sending host's character representation to "8-bit ASCII" before transmission, and (again, if necessary) to the receiving host's character representation. As a consequence, this mode is inappropriate for files that contain data other than plain text.
* Image mode (commonly called Binary mode): The sending machine sends each file byte by byte, and the recipient stores the bytestream as it receives it. (Image mode support has been recommended for all implementations of FTP).
* EBCDIC mode: Used for plain text between hosts using the EBCDIC character set.
* Local mode: Allows two computers with identical setups to send data in a proprietary format without the need to convert it to ASCII.

Data transfer can be done in any of three modes:

* Stream mode: Data is sent as a continuous stream, relieving FTP from doing any processing. Rather, all processing is left up to TCP. No End-of-file indicator is needed, unless the data is divided into records.
* Block mode: FTP breaks the data into several blocks (block header, byte count, and data field) and then passes it on to TCP.
* Compressed mode: Data is compressed using a simple algorithm (usually run-length encoding).  

#### Differences from HTTP

HTTP essentially fixes the bugs in FTP that made it inconvenient to use for many small ephemeral transfers as are typical in web pages.

FTP has a stateful control connection which maintains a current working directory and other flags, and each transfer requires a secondary connection through which the data are transferred. In "passive" mode this secondary connection is from client to server, whereas in the default "active" mode this connection is from server to client. This apparent role reversal when in active mode, and random port numbers for all transfers, is why firewalls and NAT gateways have such a hard time with FTP. HTTP is stateless and multiplexes control and data over a single connection from client to server on well-known port numbers, which trivially passes through NAT gateways and is simple for firewalls to manage.

Setting up an FTP control connection is quite slow due to the round-trip delays of sending all of the required commands and awaiting responses, so it is customary to bring up a control connection and hold it open for multiple file transfers rather than drop and re-establish the session afresh each time. In contrast, HTTP originally dropped the connection after each transfer because doing so was so cheap. While HTTP has subsequently gained the ability to reuse the TCP connection for multiple transfers, the conceptual model is still of independent requests rather than a session.

When FTP is transferring over the data connection, the control connection is idle. If the transfer takes too long, the firewall or NAT may decide that the control connection is dead and stop tracking it, effectively breaking the connection and confusing the download. The single HTTP connection is only idle between requests and it is normal and expected for such connections to be dropped after a time-out.

# What’s the Difference? FTP, SFTP, and FTP/S 

### FTP (File Transfer Protocol)

FTP is a very well-established protocol, developed in the 1970s to allow two computers to transfer data over the internet. One computer acts as the server to store information and the other acts as the client to send or request files from the server. The FTP protocol typically uses port 21 as its main means of communication. An FTP server will listen for client connections on port 21.

FTP clients will then connect to the FTP server on port 21 and initiate a conversation. This main connection is called the Control Connection or Command Connection. The FTP client will usually authenticate itself with the FTP server by sending over a username and a password. After authentication, the client and server will typically, through a series of synchronized commands controlled by the Command Connection, negotiate a new common port called the Data Connection over which the file will be transferred. The Control Connection remains idle until the end of this exchange, when it reports that the file transfer has either failed or was completed successfully. The conversation between client and server is performed in plain text—all communication between the two parties is sent unprotected, verbatim, over the internet. This makes FTP very unsecure; it would not be terribly difficult for a third party, such as a Man-in-the-Middle Attacker (MITMA), to steal users’ credentials.

There’s an exception to this rule called One Time Password (OTP), in which the server sends a series of digits to the client server in response to the receipt of the USER command. The client grabs those digits and, using a pre-known algorithm such as ROT13 or MD5, the client will generate a hash of their password along with the series of digits to produce a unique password (used one time, hence the OTP). The client presents this hash to the server, which takes the user’s password, already stored on the server, and uses the same digits. If the hashes of the password match, they are authenticated. This is somewhat more secure because the user’s password does not go over the wire– only a hash of the user’s password– so a MITMA usually can’t reverse engineer the password from the hash.

The need for a Data Connection, and its inherent security loopholes, is a major concern in internet usage today. FTP traditionally requires a block of ports to remain open on either the server firewall or the client firewall to aid with the creation of Data Connections. For security reasons, companies are limiting the number of ports in their publicly facing firewalls and looking for alternate solutions in order to keep ports closed and information secure.

### FTP/S (File Transfer Protocol over Secure Sockets Layers)

Along with file transfers, clients will typically request directory information from the server. The format of information in directories is often primitive by today’s standards, and as such, the FTP client is sometimes only able to retrieve a subset of the attributes or properties of files available on the server (for instance, the date the file was last modified, but not the date of the file’s creation).

While generic FTP is not secure, extensions have been added over the years to allow for the securing of FTP conversations—namely, the industry standard 2048 bit Transport Layer Security (TLS), the most upgraded version of the old 1024 bit standard SSL. FTP over SSL (FTP/S, as it’s commonly known) allows for the encryption of both the Control and Data Connections either concurrently or independently. This is important because the negotiation of the SSL connection is time-consuming, and having to do it twice—once for the Data Connection and once for the Control Connection—can be expensive if a client plans to transfer a large number of small files.

FTP/S commonly runs on port 990 and sometimes on port 21, the primary difference being that port 990 is an Implicit FTP/S, and port 21 is an Explicit FTP/S. If a client connects to an FTP/S server on port 990, the assumption is that the client intends to perform SSL. Therefore, the SSL handshake takes place immediately; it is referred to as Implicit because the port number implies security.  FTP clients who connect on port 21 and intend to use SSL for security will need to take the extra step to explicitly state their intentions by sending an AUTH SSL or AUTH TLS command to the server. Once the server receives this command, the two parties perform an SSL handshake and enter a secure state—hence why port 21 is referred to as Explicit. This allows the client the opportunity to activate greater security when necessary, or speed the process up on less security-sensitive file transfers.

### SFTP (Secure File Transfer Protocol)

SFTP (Secure File Transfer Protocol) is a relatively new protocol developed in the 1990s, which allows for the transfer of files and other data over a connection that has previously been secured using the Secure Shell (SSH) protocol.  While similar to FTP/S in that both protocols communicate over a secure connection, that’s basically where the similarities end.

Unlike FTP, the SFTP protocol is packet-based instead of text-based. Where FTP might send a command such as “DELE file.txt,” SFTP would send a binary 0xBC and then “file.txt.” The key difference is that by sending less data, the SFTP protocol is faster over the long-term as less data is crossing the wire.

Another difference is that with SFTP, file transfers are performed in-line over the main Control Connection, thus eliminating the need to open a separate Data Connection for transfers. This has many benefits. First, by re-using the main connection, no other connections are opened between the client and the server, resulting in a single secure, efficient connection through firewalls.

Since SFTP runs over SSH, it is inherently secure. There is no non-secure version—the encryption cannot be triggered or turned off using AUTH commands, as in FTP/S. This is a plus for system administrators who are trying to enforce corporate security policies.

Another difference is that most versions of SFTP Server software are able to deliver a much richer and more detailed set of data about the files, such as the permissions, date, time, size, and other information not normally available to FTP, thanks to the more robust request protocol of the SFTP.
