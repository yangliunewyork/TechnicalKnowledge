### Introduction
In a distributed computing environment, distributed object communication realizes communication between distributed objects. The main role is to allow objects to access data and invoke methods on remote objects (objects residing in non-local memory space). Invoking a method on a remote object is known as remote method invocation or remote invocation, and is the object-oriented programming analog of a remote procedure call.

### Class stubs and skeletons
The widely used approach on how to implement the communication channel is realized by using stubs and skeletons. They are generated objects whose structure and behavior depends on chosen communication protocol, but in general provide additional functionality that ensures reliable communication over the network.

In RMI, a stub (which is the bit on the client) is defined by the programmer as an interface. The rmic compiler uses this to create the class stub. The stub performs type checking. The skeleton is defined in a class which implements the interface stub.

When a caller wants to perform remote call on the called object, it delegates requests to its stub which initiates communication with the remote skeleton. Consequently, the stub passes caller arguments over the network to the server skeleton. The skeleton then passes received data to the called object, waits for a response and returns the result to the client stub. Note, there is no direct communication between the caller and the called object.
In more details, the communication consists of several steps:

1. caller calls a local procedure implemented by the stub
2. stub marshalls call type and in the input arguments into a request message
3. client stub sends the message over the network to the server and blocks the current execution thread
4. server skeleton receives the request message from the network
5. skeleton unpacks call type from the request message and looks up the procedure on the called object
6. skeleton unmarshalls procedure arguments
7. skeleton executes the procedure on the called object
8. called object performs a computation and returns the result
9. skeleton packs the output arguments into a response message
10. skeleton sends the message over the network back to the client
11. client stub receives the response message from the network
12. stub unpacks output arguments from the message
13. stub passes output arguments to the caller, releases execution thread and caller then continues in execution

The advantage of this architecture is that neither the caller nor the called object has to implement network related logic. This functionality, that ensures reliable communication channel over the network, has been moved to the stub and the skeleton layer.

### Stub
The client side object participating in distributed object communication is known as a stub or proxy, and is an example of a proxy object.
The stub acts as a gateway for client side objects and all outgoing requests to server side objects that are routed through it. The stub wraps client object functionality and by adding the network logic ensures the reliable communication channel between client and server. The stub can be written up manually or generated automatically depending on chosen communication protocol.
The stub is responsible for:

* initiating the communication towards the server skeleton
* translating calls from the caller object
* marshalling of the parameters
* informing the skeleton that the call should be invoked
* passing arguments to the skeleton over the network
* unmarshalling of the response from the skeleton
* informing the skeleton that the call is complete

### Skeleton
The server side object participating in distributed object communication is known as a skeleton (or stub; term avoided here).
A skeleton acts as gateway for server side objects and all incoming clients requests are routed through it. The skeleton wraps server object functionality and exposes it to the clients, moreover by adding the network logic ensures the reliable communication channel between clients and server. Skeletons can be written up manually or generated automatically depending on chosen communication protocol.
The skeleton is responsible for:

* translating incoming data from the stub to the correct up-calls to server objects
* unmarshalling of the arguments from received data
* passing arguments to server objects
* marshalling of the returned values from server objects
* passing values back to the client stub over the network

