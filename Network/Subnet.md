<img src="https://tr1.cbsistatic.com/hub/i/2015/06/03/90ebe410-098c-11e5-940f-14feb5cc3d2a/t01820010322eje20_02.gif">

A subnet (short for "subnetwork") is an identifiably separate part of an organization's network. Typically, a subnet may represent all the machines at one geographic location, in one building, or on the same local area network (LAN). Having an organization's network divided into subnets allows it to be connected to the Internet with a single shared network address. Without subnets, an organization could get multiple connections to the Internet, one for each of its physically separate subnetworks, but this would require an unnecessary use of the limited number of network numbers the Internet has to assign. It would also require that Internet routing tables on gateways outside the organization would need to know about and have to manage routing that could and should be handled within an organization.

A mask used to determine what subnet an IP address belongs to. An IP address has two components, the network address and thehost address. For example, consider the IP address150.215.017.009. Assuming this is part of a Class B network, the first two numbers (150.215) represent the Class B network address, and the second two numbers (017.009) identify a particular host on this network.

#### What is Subnetting?

Subnetting enables the network administrator to further divide the host part of the address into two or more subnets. In this case, a part of the host address is reserved to identify the particular subnet. This is easier to see if we show the IP address in binary format.

The full address is:

10010110.11010111.00010001.00001001

The Class B network part is:

10010110.11010111

The host address is:

00010001.00001001

If this network is divided into 14 subnets, however, then the first 4 bits of the host address (0001) are reserved for identifying the subnet.

The subnet mask is the network address plus the bits reserved for identifying the subnetwork -- by convention, the bits for the network address are all set to 1, though it would also work if the bits were set exactly as in the network address. In this case, therefore, the subnet mask would be 11111111.11111111.11110000.00000000. It's called a mask because it can be used to identify the subnet to which an IP address belongs by performing abitwise AND operation on the mask and the IP address. The result is the subnetwork address:

Subnet Mask

255.255.240.000

11111111.11111111.11110000.00000000

IP Address

150.215.017.009

10010110.11010111.00010001.00001001

Subnet Address

150.215.016.000

10010110.11010111.00010000.00000000

The subnet address, therefore, is 150.215.016.000.
