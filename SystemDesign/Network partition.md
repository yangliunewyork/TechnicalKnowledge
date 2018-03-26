A __network partition__ refers to network decomposition into relatively independent subnets for their separate optimization as well as network split due to the failure of network devices. In both cases the partition-tolerant behavior of subnets is expected. This means that even after network is partitioned into multiple sub-systems, it still works correctly.

For example, in a network with multiple subnets where nodes A and B are located in one subnet and nodes C and D are in another, a partition occurs if the switch between the two subnets fails. In that case nodes A and B can no longer communicate with nodes C and D, but all nodes A-D work the same as before.

<img src="http://i39.tinypic.com/wundjn.jpg" height="500" width="600">

