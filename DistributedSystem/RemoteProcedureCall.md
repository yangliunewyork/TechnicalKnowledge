## Introduction
In distributed computing a remote procedure call (RPC) is when a computer program causes a procedure (subroutine) to execute in another address space (commonly on another computer on a shared network), which is coded as if it were a normal (local) procedure call, without the programmer explicitly coding the details for the remote interaction. That is, the programmer writes essentially the same code whether the subroutine is local to the executing program, or remote. This is a form of __client–server interaction__ (caller is client, executer is server), typically implemented via a __request–response message-passing system__. The object-oriented programming analog is __remote method invocation (RMI)__. The RPC model implies a level of location transparency, namely that calling procedures is largely the same whether it is local or remote, but usually they are not identical, so local calls can be distinguished from remote calls. Remote calls are usually orders of magnitude slower and less reliable than local calls, so distinguishing them is important.

RPCs are a form of __inter-process communication (IPC)__, in that different processes have different address spaces: if on the same host machine, they have distinct virtual address spaces, even though the physical address space is the same; while if they are on different hosts, the physical address space is different. Many different (often incompatible) technologies have been used to implement the concept.

#### Message passing
RPC is a kind of request–response protocol. An RPC is initiated by the client, which sends a request message to a known remote server to execute a specified procedure with supplied parameters. The remote server sends a response to the client, and the application continues its process. While the server is processing the call, the client is blocked (it waits until the server has finished processing before resuming execution), unless the client sends an asynchronous request to the server, such as an XHTTP call. There are many variations and subtleties in various implementations, resulting in a variety of different (incompatible) RPC protocols.

An important difference between remote procedure calls and local calls is that remote calls can fail because of unpredictable network problems. Also, callers generally must deal with such failures without knowing whether the remote procedure was actually invoked. __Idempotent__ procedures (those that have no additional effects if called more than once) are easily handled, but enough difficulties remain that code to call remote procedures is often confined to carefully written low-level subsystems.

#### Sequence of events

![alt](https://www.cs.rutgers.edu/~pxk/417/notes/images/rpc-flow.png)

1. The client calls the client __stub__. The call is a local procedure call, with parameters pushed on to the stack in the normal way.
2. The client stub packs the parameters into a message and makes a system call to send the message. Packing the parameters is called __marshalling__.
3. The client's local operating system sends the message from the client machine to the server machine.
4. The local operating system on the server machine passes the incoming packets to the server stub.
5. The server stub unpacks the parameters from the message. Unpacking the parameters is called __unmarshalling__.
6. Finally, the server stub calls the server procedure. The reply traces the same steps in the reverse direction.

### RPC vs RMI
RPC has structured programming semantics, on the other side, RMI is object oriented.

With RPC you can just call remote functions exported into a server, in RMI you can have references to remote objects and invoke their methods, and also pass and return more remote object references that can be distributed among many JVM instances, so it's much more powerful.

RMI stands out when the need to develop something more complex than a pure client-server architecture arises. It's very easy to spread out objects over a network enabling all the clients to communicate without having to stablish individual connections explicitly.
