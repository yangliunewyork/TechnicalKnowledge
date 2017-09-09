* http://skillachie.com/2014/07/25/mysql-high-availability-architectures/#more-1192

Multi-master replication is a method of database replication which allows data to be stored by a group of computers, and updated by any member of the group. All members are responsive to client data queries. The multi-master replication system is responsible for propagating the data modifications made by each member to the rest of the group, and resolving any conflicts that might arise between concurrent changes made by different members.

Multi-master replication can be contrasted with master-slave replication, in which a single member of the group is designated as the "master" for a given piece of data and is the only node allowed to modify that data item. Other members wishing to modify the data item must first contact the master node. Allowing only a single master makes it easier to achieve consistency among the members of the group, but is less flexible than multi-master replication.

Multi-master replication can also be contrasted with __failover clustering__ where passive slave servers are replicating the master data in order to prepare for takeover in the event that the master stops functioning. The master is the only server active for client interaction.

__The primary purposes of multi-master replication are increased availability and faster server response time.__

##### Advantages

* If one master fails, other masters continue to update the database.
* Masters can be located in several physical sites, i.e. distributed across the network.

##### Disadvantages

* Most multi-master replication systems are only loosely consistent, i.e. lazy and asynchronous, violating ACID properties.
* Eager replication systems are complex and increase communication latency.
* Issues such as conflict resolution can become intractable as the number of nodes involved rises and latency increases.


# MySQL High Availability Architectures

### MySQL Master/Slave(s) Replication

MySQL master to slave(s) configuration is the most popular setup. In this design One(1) server acts as the master database  and all other server(s) act as slaves.Writes can only occur on the master node by the application.

##### Pros

* Analytic applications can read from the slave(s) without impacting the master  
* Backups of the entire database of relatively no impact on the master  
* Slaves can be taken offline  and sync back to the master without any downtime  

##### Cons  

* In the instance of a failure a slave has to be promoted to master to take over its place. No automatic failover  
* Downtime and possibly lost of data when a master fails  
* All writes also have to be made to the master in a master-slave design  
* Each additional slave add some load to the master since the binary log have to be read and data copied to each slave  
* Application might have to be restarted  

In the diagram below the App(Application) talks to a load balancer/VIP/elastic IP. The application(App) is not configured to point directly to the address  of the MySQL master node to reduce the configuration changes that might be required within the application (App) in the case of a failure.

Load Balancer –  Configured with  a fail over load balancing policy/algo(highest priority). In this configuration all requests are sent to a single route or the highest priority(master). Only in the instance of a failure will requests be sent to the alternative route(slave)

Elastic IP – The IP exposed to the application can be configured to point to the master database . When a failure is discovered on the master, the same IP can then be configured to point to the slave database.

![alt](http://skillachie.com/wp-content/uploads/2014/07/MySQL-Master-Slave-Architecture2.png)


VIP –  Same as elastic ip above. Can be configured to point to the master/slave as required

### MySQL Master/Master Replication

In a master-master configuration each master is configured as a slave to the other. Writes and reads can occur on both servers.

##### Pros

* Applications can read  from both masters
* Distributes write load across both master nodes
* Simple ,automatic and quick failover

##### Cons

* __Loosely consistent__
* Not as simple as master-slave to configure and deploy

In the diagram below the only significant difference between the master-slave diagram above is that replication(copying data) occurs on both sides of the masters and that both reads & writes can occur on either server.

![alt](http://skillachie.com/wp-content/uploads/2014/07/MySQL-Master-Master-Replication1.png)

