* https://msdn.microsoft.com/en-us/library/ff648849.aspx

In computer programming, a __message broker__ is an intermediary program module that translates a message from the formal messaging protocol of the sender to the formal messaging protocol of the receiver. Message brokers are elements in telecommunication or computer networks where software applications communicate by exchanging formally-defined messages. Message brokers are a building block of __Message oriented middleware__.

# Pattern
A message broker is an architectural pattern for message validation, transformation and routing. It mediates communication amongst applications, minimizing the mutual awareness that applications should have of each other in order to be able to exchange messages, effectively implementing decoupling.

The purpose of a broker is to take incoming messages from applications and perform some action on them. The following are examples of actions that might be taken in by the broker:

* Route messages to one or more of many destinations
* Transform messages to an alternative representation
* Perform message aggregation, decomposing messages into multiple messages and sending them to their destination, then recomposing the responses into one message to return to the user
* Interact with an external repository to augment a message or store it
* Invoke Web services to retrieve data
* Respond to events or errors
* Provide content and topic-based message routing using the publish–subscribe pattern

# Case Study

#### Context
You have an online store that integrates several systems, such as the Web-based front-end system, the credit card verification system, the retail system, and the shipping system. The control flow usually originates in the front end. For example, a customer placing an order causes the online store to send a request message to the credit card verification system. If the credit card information is validated, the online store sends request messages to the various retail systems, depending on the ordered items. An order for books translates into a purchase order message for the book retailer; an order for electronics translates into a purchase order message for the electronics retailer; and an order for gardening supplies translates into a purchase order message for the home and garden supplier.
The control flow could also originate in a retail or shipping system. For example, when a retailer updates a catalog, the retail system sends catalog update messages to the store so that the store can display the new items. When a shipper changes the shipping rates, the shipping system sends a rate update message to the store so that the store can compute the correct shipping charges. Similarly, when a shipper changes pickup times, the shipping system sends update messages to all the retailers the system serves so that they can have the shipments ready in time.

#### Problem
How do you integrate applications without enforcing a common interface and also allow each application to initiate interactions with several other applications?

#### Forces
To integrate applications without changing their interfaces, you must balance the following forces:
* Point-to-point integration requires a large number of connections between applications. Many connections usually translate into many interfaces.
* Message Bus integration facilitates adding new applications, but it requires a common bus interface. Because integration solutions usually involve applications that have proprietary interfaces provided by multiple vendors, Message Bus integration is difficult.
* Run-time control of qualities such as availability and performance may require dynamic reconfiguration.
* The applications in an integration solution could have conflicting quality of service (QoS) requirements.
* The applications in an integration solution could belong to different security realms.

#### Solution
Extend the integration solution by using Message Broker. A message broker is a physical component that handles the communication between applications. Instead of communicating with each other, applications communicate only with the message broker. An application sends a message to the message broker, providing the logical name of the receivers. The message broker looks up applications registered under the logical name and then passes the message to them.

Communication between applications involves only the sender, the message broker, and the designated receivers. The message broker does not send the message to any other applications. From a control-flow perspective, the configuration is symmetric because the message broker does not restrict the applications that can initiate calls. 

![alt](https://i-msdn.sec.s-msft.com/dynimg/IC171851.gif)

The message broker can expose different interfaces to the collaborating applications, and it can translate messages between these interfaces. In other words, the message broker does not enforce a common interface on the applications.
Prior to using a message broker, you must register the applications that receive communications so that the message broker can dispatch requests to them. The message broker may provide its own registration mechanism, or it may rely on an external service such as a directory.

Placing the message broker between the sender and the receiver provides flexibility in several ways. First, the message broker allows the integration solution to dynamically change its configuration. For example, if an application must be shut down for maintenance, the message broker could start routing requests to a failover application. Likewise, if the receiver cannot keep up with the incoming messages, the message broker could start load balancing between several receivers.

Second, the message broker can choose between applications that have different QoS levels. This resembles the dynamic configuration, but the message broker selects the application based on specified criteria. For example, an application for premium accounts may fulfill requests quickly, but an application for general use may have a longer processing time.

Third, the message broker allows the sender and the receiver to reside in different security realms. In other words, the message broker can reside on the boundary between two security realms and bridge requests between those two realms. 

#### Example
Consider an online store that allows shoppers to browse a variety of retail catalogs and to place orders. When an order is placed, the online store groups the shopping cart items by retailer and places appropriate orders with each retailer. As each retailer fulfills and ships the order, it sends the online store a tracking number. The online store updates its records so that this information is presented on the Check Order Status page. If the customer has configured e-mail alerts, the store also sends an e-mail message that contains the tracking information.

The online store that is illustrated in Figure 2 uses a message broker to communicate with the individual retailers. The broker knows how to reach each retailer and how to place orders, to cancel orders, and to check the order status. Likewise, the retailers communicate with the broker when they send tracking numbers. Each retailer must know how to reach the broker and how to send the tracking number. In other words, both the store side and the retailer side can initiate a communication, and the data flows in both directions.

![alt](https://i-msdn.sec.s-msft.com/dynimg/IC135451.gif)

#### Resulting Context
The decision to use a message broker for integration entails balancing the benefits of removing inter-application coupling against the effort associated with using the message broker. Use the following benefits and liabilities to evaluate the balance:

##### Benefits
* Reduced coupling. The message broker decouples the senders and the receivers. Senders communicate only with the message broker, and the potential grouping of many receivers under a logical name is transparent to them.
* Improved integrability. The applications that communicate with the message broker do not need to have the same interface. Unlike integration through a bus, the message broker can handle interface-level differences. In addition, the message broker can also act as a bridge between applications that are from different security realms and that have different QoS levels.
* Improved modifiability. The message broker shields the components of the integration solution from changes in individual applications. It also enables the integration solution to change its configuration dynamically.
* Improved security. Communication between applications involves only the sender, the broker, and the receivers. Other applications do not receive the messages that these three exchange. Unlike bus-based integration, applications communicate directly in a manner that protects the information without the use of encryption.
* Improved testability. The message broker provides a single point for mocking. Mocking facilitates the testing of individual applications as well as of the interaction between them.


##### Liabilities
* Increased complexity. Communicating through a message broker is more complex than direct communication for the following reasons:
The message broker must communicate with all the parties involved. This could mean providing many interfaces and supporting many protocols.The message broker is likely to be multithreaded, which makes it hard to trace problems.
* Increased maintenance effort. Broker-based integration requires that the integration solution register the applications with the broker. Bus-based integration does not have this requirement.
* Reduced availability. A single component that mediates communication between applications is a single point of failure. A secondary message broker could solve this problem. However, a secondary message broker adds the issues that are associated with synchronizing the states between the primary message broker and the secondary message broker.
* Reduced performance. The message broker adds an intermediate hop and incurs overhead. This overhead may eliminate a message broker as a feasible option for solutions where fast message exchange is critical.































