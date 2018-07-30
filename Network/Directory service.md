In computing, __directory service__ or __name service__ maps the names of network resources to their respective network addresses. It is a shared information infrastructure for locating, managing, administering and organizing everyday items and network resources, which can include volumes, folders, files, printers, users, groups, devices, telephone numbers and other objects. A directory service is a critical component of a network operating system. A __directory server__ or name server is a server which provides such a service. Each resource on the network is considered an object by the directory server. Information about a particular resource is stored as a collection of attributes associated with that resource or object.

A directory service defines a namespace for the network. The namespace is used to assign a name (unique identifier) to each of the objects. Directories typically have a set of rules determining how network resources are named and identified, which usually includes a requirement that the identifiers be unique and unambiguous. When using a directory service, a user does not have to remember the physical address of a network resource; providing a name locates the resource. Some directory services include access control provisions, limiting the availability of directory information to authorized users. 

### Comparison with relational databases

Several things distinguish a directory service from a relational database. Data can be redundant if it aids performance.

Directory schemas are object classes, attributes, name bindings and knowledge (namespaces) where an object class has:

* Must - attributes that each instances must have
* May - attributes which can be defined for an instance but can be omitted, with the absence similar to NULL in a relational database

Attributes are sometimes multi-valued, allowing multiple naming attributes at one level (such as machine type and serial number concatenation, or multiple phone numbers for "work phone"). Attributes and object classes are standardized throughout the industry, and formally registered with the IANA for their object ID. Therefore, directory applications try to reuse standard classes and attributes to maximize the benefit of existing directory-server software.

Object instances are slotted into namespaces; each object class inherits from its parent object class (and ultimately from the root of the hierarchy), adding attributes to the must-may list. Directory services are often central to the security design of an IT system and have a correspondingly-fine granularity of access control. 
