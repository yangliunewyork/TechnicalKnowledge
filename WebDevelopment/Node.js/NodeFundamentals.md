The official website (http://www.nodejs.org) defines Node as “a platform built on Chrome’s JavaScript runtime for easily building fast, scalable network applications. Node.js uses an event-driven, non-blocking I/O model that makes it lightweight and efficient, perfect for data-intensive real-time applications that run across distributed devices.”

### Asynchronous and evented: the browser

Node provides an event-driven and asynchronous platform for server-side JavaScript. It brings JavaScript to the server in much the same way a browser brings JavaScript to the client. It’s important to understand how the browser works in order to understand how Node works. Both are event-driven (they use an event loop) and non-blocking when handling I/O (they use asynchronous I/O).

The I/O happens asynchronously and doesn’t “block” the script execution, allowing the event loop to respond to whatever other interactions or requests are being performed on the page. This enables the browser to be responsive to the client and to handle a lot of interactivity on the page.

### Asynchronous and evented: the server
If a program blocks on I/O, what does the server do when there are more requests to handle? Typically you’d use a multithreaded approach in this context. A common implementation is to use one thread per connection and set up a thread pool for those connections. You can think of threads as computational workspaces in which the processor works on one task. In many cases, a thread is contained inside a process and maintains its own working memory. Each thread handles one or more server connections. Although this may sound like a natural way to delegate server labor—at least to developers who’ve been doing this a long time—managing threads within an application can be complex. Also, when a large number of threads is needed to handle many concurrent server connections, threading can tax operating system resources. Threads require CPU to perform context switches, as well as additional RAM.

In Node, I/O is almost always performed outside of the main event loop, allowing the server to stay efficient and responsive, like NGINX. This makes it much harder for a process to become I/O-bound because I/O latency isn’t going to crash your server or use the resources it would if you were blocking. It allows the server to be lightweight on what are typically the slowest operations a server performs.

### DIRT applications
There actually is an acronym for the types of applications Node is designed for: DIRT. It stands for __data-intensive real-time__ applications. Because Node itself is very lightweight on I/O, it’s good at shuffling or proxying data from one pipe to another. It allows a server to hold a number of connections open while handling many requests and keeping a small memory footprint. It’s designed to be responsive, like the browser.

Real-time applications are a new use case of the web. Many web applications now provide information virtually instantly, implementing things like online whiteboard collaboration, real-time pinpointing of approaching public transit buses, and multiplayer games. Whether it’s existing applications being enhanced with real-time components or completely new types of applications, the web is moving toward more responsive and collaborative environments. These new types of web applications, however, call for a platform that can respond almost instantly to a large number of concurrent users. Node is good at this, and not just for web applications, but also for other I/O-heavy applications.

### DIRT by default
Node was built from the ground up to have an event-driven and asynchronous model. JavaScript has never had standard I/O libraries, which are common to server-side languages. The “host” environment has always determined this for JavaScript. The most common host environment for JavaScript—the one most developers are used to—is the browser, which is event-driven and asynchronous.

### Creating modules
Modules can either be single files or directories containing one or more files.To create a typical module, you create a file that defines properties on the exports object with any kind of data, such as strings, objects, and functions.
To utilize your new module, use Node’s require function, which takes a path to the module you wish to use as an argument. Node performs a synchronous lookup in order to locate the module and loads the file’s contents.After Node has located and evaluated your module, the require function returns the contents of the exports object defined in the module.

### A note about require and synchronous I/O 
require is one of the few synchronous I/O operations available in Node. Because modules are used often and are typically included at the top of a file, having require be synchronous helps keep code clean, ordered, and readable. But avoid using require in I/O-intensive parts of your application. Any synchronous call will block Node from doing anything until the call has finished. For example, if you’re running an HTTP server, you would take a performance hit if you used require on each incoming request. This is typically why require and other synchronous operations are used only when the application initially loads.

### Asynchronous programming techniques
If you’ve done front-end web programming in which interface events (such as mouse clicks) trigger logic, then you’ve done asynchronous programming. Server-side asynchronous programming is no different: events occur that trigger response logic. There are two popular models in the Node world for managing response logic: callbacks and event listeners.
__Callbacks__ generally define logic for one-off responses. If you perform a database query, for example, you can specify a callback to determine what to do with the query results. The callback may display the database results, do a calculation based on the results, or execute another callback using the query results as an argument.
__Event listeners__, on the other hand, are essentially callbacks that are associated with a conceptual entity (an event). For comparison, a mouse click is an event you would handle in the browser when someone clicks the mouse. As an example, in Node an HTTP server emits a request event when an HTTP request is made. You can listen for that request event to occur and add some response logic. In the following example, the function handleRequest will be called whenever a request event is emitted:
server.on('request', handleRequest)
A Node HTTP server instance is an example of an event emitter, a class (EventEmitter) that can be inherited and that adds the ability to emit and handle events. Many aspects of Node’s core functionality inherit from EventEmitter, and you can also create your own.
Now that we’ve established that response logic is generally organized in one of two ways in Node, let’s jump into how it all works by learning about the following:

* How to handle one-off events with callbacks
* How to respond to repeating events using event listeners
* Some of the challenges of asynchronous programming

### Handling one-off events with callbacks
A callback is a function, passed as an argument to an asynchronous function, that describes what to do after the asynchronous operation has completed. Callbacks are used frequently in Node development, more so than event emitters, and they’re simple to use.

### The Node convention for asynchronous callbacks
Most Node built-in modules use callbacks with two arguments: the first argument is for an error, should one occur, and the second argument is for the results. The error argument is often abbreviated as er or err.
Here’s a typical example of this common function signature:

```
var fs = require('fs');
fs.readFile('./titles.json', function(er, data) {
if (er) throw er;
// do something with data if no error has occurred
});
```
### Handling repeating events with event emitters
Event emitters fire events and include the ability to handle those events when triggered. Some important Node API components, such as HTTP servers, TCP servers, and streams, are implemented as event emitters. You can also create your own.

As we mentioned earlier, events are handled through the use of listeners. A listener is the association of an event with a callback function that gets triggered each time the event occurs. For example, a TCP socket in Node has an event called data that’s triggered whenever new data is available on the socket:

``` socket.on('data', handleData); ```

A convention you can use when creating event emitters is to emit an error type event instead of directly throwing an error. This allows you to define custom event response logic by setting one or more listeners for this event type. The following code shows how an error listener handles an emitted error by logging into the console:

```
var events = require('events');
var myEmitter = new events.EventEmitter();
myEmitter.on('error', function(err) {
console.log('ERROR: ' + err.message);
});
myEmitter.emit('error', new Error('Something is wrong.'));
```
If no listener for this event type is defined when the error event type is emitted, the event emitter will output a stack trace (a list of program instructions that had executed up to the point when the error occurred) and halt execution. The stack trace will indicate an error of the type specified by the emit call’s second argument. This behavior is unique to error type events; when other event types are emitted, and they have no listeners, nothing happens.

If an error type event is emitted without an error object supplied as the second argument, a stack trace will indicate an “Uncaught, unspecified ‘error’ event” error, and your application will halt. There is a deprecated method you can use to deal with this error—you can define your own response by defining a global handler using the following code:

```
process.on('uncaughtException', function(err){
console.error(err.stack);
process.exit(1);
});
```

By learning how to use callbacks to define one-off asynchronous logic and how to use event emitters to dispatch asynchronous logic repeatedly, you’re one step closer to mastering control of a Node application’s behavior. In a single callback or event emitter listener, however, you may want to include logic that performs additional asynchronous tasks. If the order in which these tasks are performed is important, you may be faced with a new challenge: how to control exactly when each task, in a series of asynchronous tasks, executes.

### Challenges with asynchronous development
When creating asynchronous applications, you have to pay close attention to how your application flows and keep a watchful eye on application state: the conditions of the event loop, application variables, and any other resources that change as program logic executes.

Node’s event loop, for example, keeps track of asynchronous logic that hasn’t completed processing. As long as there’s uncompleted asynchronous logic, the Node process won’t exit. A continually running Node process is desirable behavior for something like a web server, but it isn’t desirable to continue running processes that are expected to end after a period of time, like command-line tools. The event loop will keep track of any database connections until they’re closed, preventing Node from exiting.

### Sequencing asynchronous logic
During the execution of an asynchronous program, there are some tasks that can happen any time, independent of what the rest of the program is doing, without causing problems. But there are also some tasks, however, that should happen only before or after certain other tasks.

The concept of sequencing groups of asynchronous tasks is called flow control by the Node community. There are two types of flow control: serial and parallel.Tasks that need to happen one after the other are called serial.Tasks that don’t need to happen one after the other are called parallel.Keeping track of serial and parallel flow control involves programmatic bookkeeping. When you implement serial flow control, you need to keep track of the task currently executing or maintain a queue of unexecuted tasks. When you implement parallel flow control, you need to keep track of how many tasks have executed to completion.








































