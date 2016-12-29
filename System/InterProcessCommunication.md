### What is IPC
In computer science, inter-process communication or interprocess communication (IPC) refers specifically to the mechanisms an operating system provides to allow processes it manages to share data. Typically, applications can use IPC, categorized as clients and servers, where the client requests data and the server responds to client requests. Many applications are both clients and servers, as commonly seen in distributed computing. Methods for achieving IPC are divided into categories which vary based on software requirements, such as performance and modularity requirements, and system circumstances, such as network bandwidth and latency.
### Why need IPC?
There are two type of processes in Operating Systems.

1. Independent processes
2. Cooperating processes

Independent process are free from other executing processes in OS, whereas cooperating processes require to interact with each other to progress further.
These process need to interact with each other for following reason:
* Data transfer
* Sharing data
* Event modification
* Resource sharing
* Process control

Since, process need to communicate with each other, hence there's a need of well structured communication that enables them to do so. This is done by Inter processing communication that enables them to send and receive data to other processes.
Moreover, IPC has two models:

1. Shared memory
2. Message passing
