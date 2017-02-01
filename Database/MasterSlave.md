## What is Master-Slave databases 
Master databases receive data from applications. Slave databases get copies of that data from the masters. Slaves are therefore read-only from the application's point of view while masters are read-write.

Writes to a database are more "expensive" than reads.  Most web applications require a much higher ratio of reads to writes.  So setting up master-slave replication in the right scenario lets an application distribute its queries efficiently.
