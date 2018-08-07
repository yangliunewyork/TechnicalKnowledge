https://docs.oracle.com/cd/E19396-01/817-7619/intro.html

Directory Server provides a central repository for storing and managing information. Almost any kind of information can be stored, from identity profiles and access privileges to information about application and network resources, printers, network devices and manufactured parts. Information stored in Directory Server can be used for the authentication and authorization of users to enable secure access to enterprise and Internet services and applications. Directory Server is extensible, can be integrated with existing systems, and enables the consolidation of employee, customer, supplier, and partner information.

Directory Server provides the foundation for the new generation of e-business applications and Web services, with a centralized and distributed data repository that can be used in your intranet or over your extranet with your trading partners. 

# What Is a Directory Service? 

### About Directory Services 

Directory services are an essential part of today's network-centric computing infrastructure. Directory-enabled applications now power almost all the mission critical processes of an enterprise, including resource planning, value chain management, security and firewalls, and resource provisioning. Directory services also provide the foundation for deployment of e-business and extranet applications. So what exactly is a Directory Service?

A directory service is the collection of software and processes that store information about your enterprise, subscribers, or both. An example of a directory service is the Domain Name System (DNS), which is provided by DNS servers. A DNS server stores the mappings of computer host names and other forms of domain name to IP addresses. A DNS client sends questions to a DNS server about these mappings (e.g. what is the IP address of test.example.com?). Thus, all of the computing resources (hosts) become clients of the DNS server. The mapping of host names enables users of the computing resources to locate computers on a network, using host names rather than complex numerical IP addresses.

Whereas the DNS server stores only two types of information: names and IP addresses, an LDAP directory service can store information on many other kinds of real-world and conceptual objects. Sun Java System Directory Server stores all of these types of information in a single, network-accessible repository. You may for example want to store physical device information, employee information (name, E-mail address), contract or account information (name, delivery dates, contract numbers, etc.), authentication information, manufactured production information. It is worth noting that although a directory service can be considered an extension of a database, directory services generally have the following characteristics:

* Hierarchical naming model : A hierarchical naming model uses the concept of containment to reduce ambiguity between names and simplify administration. The name for most objects in the directory is relative to the name of some other object which conceptually contains it. For example, the name of an object representing an employee of a particular company contains the name of the object representing the company, and the name of the company might contain the name of the objects representing the country where the company operates, e.g. cn=John Smith, o=Example Corporation, c=US. Together the names of all objects in the directory service form a tree, and each Directory Server holds a branch of that tree, which in the Sun Java System Directory Server documentation is also referred to as a suffix.
* Extended search capability : Directory services provide robust search capabilities, allowing searches on individual attributes of entries.
* Distributed information model : A directory service enables directory data to be distributed across multiple servers within a network.
* Shared network access : While databases are defined in terms of APIs, directories are defined in terms of protocols. Directory access implies network access by definition. Directories are designed specifically for shared access among applications. This is achieved through the object-oriented schema model. By contrast, most databases are designed for use only by particular applications and do not encourage data sharing.
* Replicated data : Directories support replication (copies of directory data on more than one server) which make information systems more accessible and more resistant to failure.
* Datastore optimized for reads : The storage mechanism in a directory service is generally designed to support a high ratio of reads to writes.
* Extensible schema : The schema describes the type of data stored in the directory. Directory services generally support the extension of schema, meaning that new data types can be added to the directory.

###  About Enterprise-Wide Directory Services

Directory Server provides enterprise-wide directory services, meaning it provides information to a wide variety of applications. Until recently, many applications came bundled with their own proprietary user databases, with information about the users specific to that application. While a proprietary database can be convenient if you use only one application, multiple databases become an administrative burden if the databases manage the same information.

For example, suppose your network supports three different proprietary E-mail systems, each system with its own proprietary directory service. If users change their passwords in one directory, the changes are not automatically replicated in the others. Managing multiple instances of the same information results in increased hardware and personnel costs, a problem referred to as the n+ 1 directory problem.

An enterprise-wide directory service solves the n+ 1 directory problem by providing a single, centralized repository of directory information that any application can access. However, giving a wide variety of applications access to the directory requires a network-based means of communicating between the applications and the directory. Directory Server provides two ways in which applications can access its enterprise-wide directory:

* Lightweight Directory Access Protocol (LDAP)
* Directory Services Markup Language (DSML)

###  About LDAP

LDAP provides a common language that client applications and servers use to communicate with one another. LDAP-based applications can easily search, add, delete and modify directory entries. LDAP is a "lightweight" version of the Directory Access Protocol (DAP) defined in the ISO/ITU-T X.500 standard. DAP gives any application access to the directory via an extensible and robust information framework, but at an expensive administrative cost. DAP does not use the Internet standard TCP/IP protocol and has complicated directory-naming conventions. LDAP preserves the best features of DAP while reducing administrative burdens. LDAP uses an open directory access protocol running over TCP/IP and uses simplified encoding methods. It retains the X 500 standard data model and can support millions of entries for a comparatively modest investment in hardware and network infrastructure. 

###  Tuned for Enterprise and e-business Directory Roles

Online directories that support LDAP have become critical components of e-business infrastructure, supporting identity and risk management in several important roles. They provide a dynamic and flexible means of storing information and retrieving it over the internet, and can of course be configured to use the Secure Sockets Layer (SSL) or Transport Layer Security (TLS) protocols for authenticated and encrypted communications. As protected repositories of personal information, LDAP directories are also a key component for the personalized delivery of services to users of the directory and personalized treatment of information contained in the directory. Directories have the following three primary roles to play, each of which have very different deployment characteristics:

#### Network Operating System (NOS) Directory 

A NOS is a distributed operating system that manages multiple requests concurrently in a multiuser environment. It consists of clients and servers configured so that client machines can access the drivers on servers as if they were local drives on the client machine, and servers can handle requests from the client to share files and applications as well as network devices such as printers or faxes.

A NOS directory is used to administer a NOS allowing intranet users to log in once for all network file and printing requirements. The user population for a NOS directory ranges from 20 to 20,000 users, The NOS directory provides a single point of integrated administration and management for the network and the most important characteristics of this directory role are the tight integration with the NOS and sophisticated management tools for clients and servers.

#### Enterprise Directory

An enterprise directory provides a global repository for shared information about people, organizations, and devices, including white/yellow pages, organization charts, seating charts, information about network devices such as routers, etc. It is important for an enterprise directory to provide flexible ways of organizing data and flexible management tools that can accommodate heterogeneous application environments or autonomous business units (through delegated administration). The user population for an enterprise directory tends to range from between 20,000 and 200,000 users.

#### e-business Directory

An e-business directory maintains information about customers, trading partners, and suppliers, which involves making the information available to an extranet as necessary and appropriate. The user population for an e-business directory is typically millions of users, and in addition to the flexible management tools required the NOS and enterprise directories, e-business directories require a high degree of reliability and scalability to be able to rapidly accommodate millions of users.

