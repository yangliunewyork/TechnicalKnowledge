## How to Keep Interactions Visible

#### Problem
You want to know what visibility means and what you can do to keep HTTP requests and responses visible.

#### Solution
Once you identify and design resources, use GET to get a representation of a resource, PUT to update a resource, DELETE to delete a resource, and POST to perform a variety of potentially nonidempotent and unsafe operations. Add appropriate HTTP headers to describe requests and responses.

#### Discussion
Features like the following depend entirely on keeping requests and responses visible:

* Caching : Caching responses and automatically invalidating cached responses when resources are modified
* Optimistic concurrency control : Detecting concurrent writes and preventing resource changes when such opera- tions are based on stale representations
* Content negotiation : Selecting a representation among alternatives available for a given resource
* Safety and idempotency : Ensuring that clients can repeat or retry certain HTTP requests

When a web service does not maintain visibility, such features will not work correctly.

HTTP achieves visibility by virtue of the following:
* HTTP interactions are __stateless__. Any HTTP intermediary can infer the meaning of any given request and response without correlating them with past or future re- quests and responses.
* HTTP uses a uniform interface consisting of OPTIONS, GET, HEAD, POST, PUT, DELETE, and TRACE methods. Each method in this interface operates on one and only one resource. The syntax and the meaning of each method do not change from application to application or from resource to resource. That is why HTTP is known as a uniform interface.
* HTTP uses a MIME-like envelope format to encode representations. This format maintains a clear separation between headers and the body. Headers are visible, and except for the software that is creating the message and the software that is processing the message, every piece of software in between can treat the body as completely opaque.

## When to Trade Visibility

#### Problem
You want to know common situations that may require you to keep requests and re- sponses less visible to the protocol.

#### Solution
Whenever you have multiple resources that share data or whenever an operation modi- fies more than one resource, be prepared to trade visibility for better abstraction of information, loose coupling, network efficiency, resource granularity, or pure client convenience.


## How to Maintain Application State

#### Problem
You want to know how to manage state in RESTful web services such that you do not need to rely on in-memory sessions on servers.

#### Solution
Encode application state into URIs, and include those URIs into representations via links. Let clients use these URIs to interact with resources. If the state is large or cannot be transported to clients for security or privacy reasons, store the application state in a durable storage (such as a database or a filesystem), and encode a reference to that state in URIs.

#### Discussion
Since HTTP is a stateless protocol, each request is independent of any previous request. However, interactive applications often require clients to follow a sequence of steps in a particular order. This forces servers to temporarily store each client’s current position in those sequences outside the protocol. The trick is to manage state such that you strike a balance between reliability, network performance, and scalability.

> Choose a durable storage such as a database or a filesystem to store application state. Using a nondurable storage such as a cache or an in- memory session reduces the reliability of the web service as such state may not survive server restart. Such solutions may also reduce scalability of the server.

##  How to Implement Safe and Idempotent Methods on the Server

#### Problem
You want to know what idempotency and safety mean, and what you can do to ensure that the server’s implementation of various HTTP methods maintain these two characteristics.

#### Solution
While implementing GET, OPTIONS, and HEAD methods, do not cause any side effects. When a client resubmits a GET, HEAD, OPTIONS, PUT, or DELETE request, ensure that the server provides the same response except under concurrent conditions.

#### Discussion
In HTTP, safe methods are not expected to cause side effects. Clients can send requests with safe methods without worrying about causing unintended side effects. To provide this guarantee, implement safe methods as read-only operations.

![alt](https://image.slidesharecdn.com/soapvsrest-151018153254-lva1-app6891/95/soap-vs-rest-14-638.jpg)

Safety does not mean that the server must return the same response every time. It just means that the client can make a request knowing that it is not going to change the state of the resource. 

Idempotency guarantees clients that repeating a request has the same effect as making a request just once. Idempotency matters most in the case of network or software failures. Clients can repeat such requests and expect the same outcome. 

## How to Treat Safe and Idempotent Methods in Clients

#### Problem
You want to know how to implement HTTP requests that are idempotent and/or safe.

#### Solution
Treat GET, OPTIONS, and HEAD as read-only operations, and send those requests whenever required.
In the case of network or software failures, resubmit GET, PUT, and DELETE requests to confirm, supplying If-Unmodified-Since and/or If-Match conditional headers.
Do not repeat POST requests, unless the client knows ahead of time (e.g., via server’s documentation) that its implementation of POST for any particular resource is idempotent.

#### Discussion
Any client should be able to make GET, OPTIONS and HEAD requests as many times as necessary. If a server’s implementation causes unexpected side effects when processing these requests, it is fair to conclude that the server’s implementation of HTTP is in- correct.Idempotency guarantees that the client can repeat a request when it is not certain the server successfully processed that request. In HTTP, all meth- ods except POST are idempotent.

## When to Use GET

#### Problem
You want to know when and when not to use GET and the potential consequences of using GET inappropriately.

#### Solution
Use GET for safe and idempotent information retrieval.

#### Discussion
Each method in HTTP has certain semantics. The purpose of GET is to get a representation of a resource, PUT is to create or update a resource, DELETE is to delete a resource, and POST is either to create new resources or to make various other changes to resources.Of all these methods, GET can take the least amount of misuse. This is because GET is both safe and idempotent.

> Do not use GET for unsafe or nonidempotent operations. Doing so could cause permanent, unexpected, and undesirable changes to resources.

## When to Use POST
#### Problem
You want to know the potential applications of the POST method.

#### Solution
Use POST for the following:
* To create a new resource, using the resource as a factory.
* To modify one or more resources via a controller resource.
* To run queries with large inputs.
* To perform any unsafe or nonidempotent operation when no other HTTP method seems appropriate.

#### Discussion
In HTTP, the semantics of method POST are the most generic. HTTP specifies that this method is applicable for the following.*
* Annotation of existing resources;
* Posting a message to a bulletin board, newsgroup, mailing list, or similar group of articles;
* Providing a block of data, such as the result of submitting a form, to a data-handling process;
* Extending a database through an append operation.

All such operations are unsafe and nonidempotent, and all HTTP-aware tools treat
POST as such:
* Caches do not cache responses of this method.
* Crawlers and such tools do not automatically activate POST requests.
* Most generic HTTP tools do not resubmit POST requests automatically.

In addition, the following situations force you to use POST even when GET is the right method to use:
* HTML clients like browsers use the URI of the page as the Referer header while making requests to fetch any linked resources. This may leak any sensitive infor- mation contained in the URI to external servers.
In such cases, if using Transport Layer Security (TLS, a successor to SSL) or if the encryption of any sensitive information in the URI is not possible, consider using POST to serve HTML documents.
* POST may be the only option when queries from clients contain too many parameters.

Even in these conditions, use POST only as the last resort.

## How to Create Resources Using POST


