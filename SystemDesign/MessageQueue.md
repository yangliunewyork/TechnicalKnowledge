## What is message queue ?
Message queues provide an asynchronous communications protocol, meaning that the sender and receiver of the message do not need to interact with the message queue at the same time. Messages placed onto the queue are stored until the recipient retrieves them. Message queues have implicit or explicit limits on the size of data that may be transmitted in a single message and the number of messages that may remain outstanding on the queue.


## Message Queue vs RPC
RPC is synchronous. You post a request and read the response. Message queues are asynchronous. You post a request and keep computing. You may have a second queue from which you may later read a response but while the request is being processed you may do other computing at the request generator.

Message queues are good for asynchronous, event oriented interactions and latency hiding. RPC is good for synchronous (Request/Response) interactions. Synchronous interactions are easier to reason about but rob you of opportunities for concurrency.
