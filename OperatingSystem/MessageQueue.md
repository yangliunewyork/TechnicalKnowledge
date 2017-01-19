## What is Message Queue ?
In computer science, message queues and mailboxes are software-engineering components used for inter-process communication (IPC), or for inter-thread communication within the same process. They use a queue for messaging – the passing of control or of content. Group communication systems provide similar kinds of functionality.
The message queue paradigm is a sibling of the publisher/subscriber pattern, and is typically one part of a larger message-oriented middleware system. Most messaging systems support both the publisher/subscriber and message queue models in their API.

## Overview
Message queues provide an asynchronous communications protocol, meaning that the sender and receiver of the message do not need to interact with the message queue at the same time. Messages placed onto the queue are stored until the recipient retrieves them. Message queues have implicit or explicit limits on the size of data that may be transmitted in a single message and the number of messages that may remain outstanding on the queue.
Many implementations of message queues function internally: within an operating system or within an application. Such queues exist for the purposes of that system only.
