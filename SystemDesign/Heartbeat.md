In a system running Heartbeat, nodes communicate by exchanging packets called "heartbeats" at the rate of approximately 2 Hz (twice per second). The name of the program comes from the regularity of the packet exchanges.

When Heartbeat is used in a multi-node system, one machine is designated as the primary node and the other as the secondary node. If the primary node fails or requires downtime, the secondary node can take over the primary role. A script called "shoot the other node in the head (STONITH)" shuts down the primary node before the secondary node comes online. STONITH prevents "split-brain" operation, with the consequent risk of file corruption, that could occur if both nodes attempt to play the primary role at the same time.

Heartbeat is commonly bundled with a software component called Distributed Replicated Block Device (DRBD), which facilitates the replacement of shared storage systems by networked mirroring.

