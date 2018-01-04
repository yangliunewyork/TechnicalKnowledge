http://techthoughts.typepad.com/managing_computers/2007/10/split-brain-quo.html

# What is Split-brain ?

Split-brain is a computer term, based on an analogy with the medical Split-brain syndrome. It indicates data or availability inconsistencies originating from the maintenance of two separate data sets with overlap in scope, either because of servers in a network design, or a failure condition based on servers not communicating and synchronizing their data to each other. This last case is also commonly referred to as a network partition.

High-availability clusters usually use a __heartbeat private network__ connection which is used to monitor the health and status of each node in the cluster. For example, the split-brain syndrome may occur when all of the private links go down simultaneously, but the cluster nodes are still running, each one believing they are the only one running. The data sets of each cluster may then randomly serve clients by their own "idiosyncratic" data set updates, without any coordination with the other data sets.

A shared storage may experience data corruption. If the data storages are kept separate data inconsistencies that might require operator intervention and cleanup.

# Approaches for dealing with split-brain

Davidson et al.,[2] after surveying several approaches to handle the problem, classify them as either optimistic or pessimistic.

The optimistic approaches simply let the partitioned nodes work as usual; this provides a greater level of availability, at the cost of sacrificing correctness. Once the problem has ended, automatic or manual reconciliation might be required in order to have the cluster in a consistent state. One current implementation for this approach is Hazelcast, which does automatic reconciliation of its key-value store.[3]

The pessimistic approaches sacrifice availability in exchange for consistency. Once a network partitioning has been detected, access to the sub-partitions is limited in order to guarantee consistency. A typical approach, as described by Coulouris et al.,[4] is to use a quorum-consensus approach. This allows the sub-partition with a majority of the votes to remain available, while the remaining sub-partitions should fall down to an auto-fencing mode. One current implementation for this approach is the one used by MongoDB replica sets.[5] And another such implementation is Galera replication for MariaDB and MySQL. .[6]

Modern commercial general-purpose HA clusters (see High Availability Cluster ) typically use a combination of heartbeat network connections between cluster hosts, and quorum witness storage. The challenge with two-node clusters is that adding a witness device adds cost and complexity (even if implemented in the cloud), but without it, if heartbeat fails, cluster members cannot determine which should be active. In such clusters (without quorum), if a member fails, even if the members normally assign primary and secondary statuses to the hosts, there is at least a 50% probability that a 2-node HA cluster will totally fail until human intervention is provided, to prevent multiple members becoming active independently and either directly conflicting or corrupting data.
