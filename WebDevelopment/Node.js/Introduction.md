Node.js is an open-source, cross-platform JavaScript run-time environment for executing JavaScript code server-side. Historically, JavaScript was used primarily for client-side scripting, in which scripts written in JavaScript are embedded in a webpage's HTML, to be run client-side by a JavaScript engine in the user's web browser. Node.js enables JavaScript to be used for server-side scripting, and runs scripts server-side to produce dynamic web page content before the page is sent to the user's web browser. Consequently, Node.js has become one of the foundational elements of the "JavaScript everywhere" paradigm, allowing web application development to unify around a single programming language, rather than rely on a different language for writing server side scripts.

# Overview

#### Platform architecture

Node.js brings event-driven programming to web servers, enabling development of fast web servers in JavaScript. Developers can create highly scalable servers without using threading, by using a simplified model of __event-driven programming__ that uses callbacks to signal the completion of a task. Node.js connects the ease of a scripting language (JavaScript) with the power of Unix network programming.

Node.js was built on the __Google V8 JavaScript engine__ since it was open-sourced under the BSD license, extremely fast, and proficient with internet fundamentals such as HTTP, DNS, TCP. Also, JavaScript was a well-known language, making Node.js immediately accessible to the entire web development community.

# Technical details

Node.js is a Javascript runtime environment that processes incoming requests in a loop, called the __event loop__.

### Threading

Node.js operates on a single thread, using __non-blocking I/O__ calls, allowing it to support tens of thousands of concurrent connections without incurring the cost of thread context switching. The design of sharing a single thread among all the requests that use the observer pattern is intended for building highly concurrent applications, where any function performing I/O must use a __callback__. In order to accommodate the single-threaded event loop, Node.js utilizes the libuv library that, in turn, uses a fixed-sized thread pool that is responsible for some of the non-blocking asynchronous I/O operations.

A downside of this single-threaded approach is that Node.js doesn't allow vertical scaling by increasing the number of CPU cores of the machine it is running on without using an additional module, such as cluster, StrongLoop Process Manager, or pm2. However, developers can increase the default number of threads in the libuv thread pool; these threads are likely to be distributed across multiple cores by the server operating system.

Execution of parallel tasks in Node.js is handled by a thread pool. The main thread call functions post tasks to the shared task queue that threads in the thread pool pull and execute. Inherently non-blocking system functions such as networking translates to kernel-side non-blocking sockets, while inherently blocking system functions such as file I/O run in a blocking way on its own thread. When a thread in the thread pool completes a task, it informs the main thread of this, which in turn, wakes up and execute the registered callback. Since callbacks are handled in serial on the main thread, long lasting computations and other CPU-bound tasks will freeze the entire event-loop until completion.

### V8 

V8 is the JavaScript execution engine built for Google Chrome and open-sourced by Google in 2008. Written in C++, V8 compiles JavaScript source code to native machine code instead of interpreting it in real time.
Node.js uses libuv to handle asynchronous events. Libuv is an abstraction layer for network and file system functionality on both Windows and POSIX-based systems such as Linux, macOS, OSS on NonStop, and Unix.
The core functionality of Node.js resides in a JavaScript library. The Node.js bindings, written in C++, connect these technologies to each other and to the operating system.

### Event loop

__Node.js registers itself with the operating system in order to be notified when a connection is made, and the operating system will issue a callback.__ Within the Node.js runtime, each connection is a small heap allocation. Traditionally, relatively heavyweight OS processes or threads handled each connection. Node.js uses an event loop for scalability, instead of processes or threads. In contrast to other event-driven servers, Node.js's event loop does not need to be called explicitly. Instead callbacks are defined, and the server automatically enters the event loop at the end of the callback definition. Node.js exits the event loop when there are no further callbacks to be performed.












