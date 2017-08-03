In computing and related technologies such as networking, failover is switching to a redundant or standby computer server, system, hardware component or network upon the failure or abnormal termination of the previously active application, server, system, hardware component, or network. Failover and switchover are essentially the same operation, except that __failover is automatic and usually operates without warning, while switchover requires human intervention.__

Systems designers usually provide failover capability in servers, systems or networks requiring near-continuous availability and a high degree of reliability.

At the server level, failover automation usually uses a "heartbeat" system that connects two servers, either through using a separate cable (for example, RS-232 serial ports/cable) or a network connection. As long as a regular "pulse" or "heartbeat" continues between the main server and the second server, the second server will not bring its systems online. There may also be a third "spare parts" server that has running spare components for "hot" switching to prevent downtime. The second server takes over the work of the first as soon as it detects an alteration in the "heartbeat" of the first machine. Some systems have the ability to send a notification of failover.

Certain systems, intentionally, do not failover entirely automatically, but require human intervention. This "automated with manual approval" configuration runs automatically once a human has approved the failover.

Failback is the process of restoring a system, component, or service previously in a state of failure back to its original, working state, and having the standby system go from functioning back to standby.

The use of virtualization software has allowed failover practices to become less reliant on physical hardware through the process referred to as migration in which a running virtual machine is moved from one physical host to another, with little or no disruption in service.

