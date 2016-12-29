A running Linux system consists of numerous processes, many of which operate independently of each other. Some processes, however, cooperate to achieve their intended purposes, and these processes need methods of communicating with one another and synchronizing their actions.
One way for processes to communicate is by reading and writing informa- tion in disk files. However, for many applications, this is too slow and inflexible.Therefore, Linux, like all modern UNIX implementations, provides a rich set of mech- anisms for interprocess communication (IPC), including the following:
* signals, which are used to indicate that an event has occurred;
* pipes (familiar to shell users as the | operator) and FIFOs, which can be used to
transfer data between processes;
* sockets, which can be used to transfer data from one process to another, either on the same host computer or on different hosts connected by a network;
* file locking, which allows a process to lock regions of a file in order to prevent other processes from reading or updating the file contents;
* message queues, which are used to exchange messages (packets of data) between processes;
* semaphores, which are used to synchronize the actions of processes; and
* shared memory, which allows two or more processes to share a piece of memory. When one process changes the contents of the shared memory, all of the other processes can immediately see the changes.
