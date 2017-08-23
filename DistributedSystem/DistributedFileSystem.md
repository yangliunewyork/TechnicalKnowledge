A distributed file system is a client/server-based application that allows clients to access and process data stored on the server as if it were on their own computer. When a user accesses a file on the server, the server sends the user a copy of the file, which is cached on the user's computer while the data is being processed and is then returned to the server.

Ideally, a distributed file system organizes file and directory services of individual servers into a global directory in such a way that remote data access is not location-specific but is identical from any client. All files are accessible to all users of the global file system and organization is hierarchical and directory-based.

Since more than one client may access the same data simultaneously, the server must have a mechanism in place (such as maintaining information about the times of access) to organize updates so that the client always receives the most current version of data and that data conflicts do not arise. Distributed file systems typically use file or database replication (distributing copies of data on multiple servers) to protect against data access failures.

Distributed file systems do not share block level access to the same storage but use a network protocol.[2][3] These are commonly known as network file systems, even though they are not the only file systems that use the network to send data.[citation needed] Distributed file systems can restrict access to the file system depending on access lists or capabilities on both the servers and the clients, depending on how the protocol is designed.

The difference between a distributed file system and a distributed data store is that a distributed file system allows files to be accessed using the same interfaces and semantics as local files – for example, mounting/unmounting, listing directories, read/write at byte boundaries, system's native permission model. Distributed data stores, by contrast, require using a different API or library and have different semantics (most often those of a database).

##### Design goals

Distributed file systems may aim for "transparency" in a number of aspects. That is, they aim to be "invisible" to client programs, which "see" a system which is similar to a local file system. Behind the scenes, the distributed file system handles locating files, transporting data, and potentially providing other features listed below.
* Access transparency is that clients are unaware that files are distributed and can access them in the same way as local files are accessed.
* Location transparency; a consistent name space exists encompassing local as well as remote files. The name of a file does not give its location.
* Concurrency transparency; all clients have the same view of the state of the file system. This means that if one process is modifying a file, any other processes on the same system or remote systems that are accessing the files will see the modifications in a coherent manner.
* Failure transparency; the client and client programs should operate correctly after a server failure.
* Heterogeneity; file service should be provided across different hardware and operating system platforms.
* Scalability; the file system should work well in small environments (1 machine, a dozen machines) and also scale gracefully to huge ones (hundreds through tens of thousands of systems).
* Replication transparency; to support scalability, we may wish to replicate files across multiple servers. Clients should be unaware of this.
* Migration transparency; files should be able to move around without the client's knowledge.
