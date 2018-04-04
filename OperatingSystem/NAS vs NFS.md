## Network-attached storage

__Network-attached storage (NAS)__ is a file-level computer data storage server connected to a computer network providing data access to a heterogeneous group of clients. NAS is specialized for serving files either by its hardware, software, or configuration. It is often manufactured as a computer appliance – a purpose-built specialized computer. NAS systems are networked appliances which contain one or more storage drives, often arranged into logical, redundant storage containers or RAID. Network-attached storage removes the responsibility of file serving from other servers on the network. They typically provide access to files using network file sharing protocols such as NFS, SMB/CIFS, or AFP. From the mid-1990s, NAS devices began gaining popularity as a convenient method of sharing files among multiple computers. Potential benefits of dedicated network-attached storage, compared to general-purpose servers also serving files, include faster data access, easier administration, and simple configuration.

## Network File System

Network File System (NFS) is a distributed file system protocol originally developed by Sun Microsystems in 1984,[1] allowing a user on a client computer to access files over a computer network much like local storage is accessed. NFS, like many other protocols, builds on the Open Network Computing Remote Procedure Call (ONC RPC) system. The NFS is an open standard defined in Request for Comments (RFC), allowing anyone to implement the protocol.


### What's the difference between NAS and NFS?

This is an oddly-worded question - it's like saying "What's the difference between fruit and an apple" - one is a class, one is a member of that class.

NAS contribute to a general-purpose network by only sharing one or more protocols that can include NFS.

NFS is a protocol that can be shared from one or more devices on a general purpose network, these devices can share only using NFS or simultaneously with other protocols.

A NAS (Networked Attached Storage) is a device serving files via the network. One protocol to accomplish this is NFS. So a NAS can use the NFS protocol (or another protocol).
