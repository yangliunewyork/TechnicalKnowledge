RAID (Redundant Array of Independent Disks, originally Redundant Array of Inexpensive Disks) is a data storage virtualization technology that combines multiple physical disk drive components into one or more logical units for the purposes of data redundancy, performance improvement, or both.

Data is distributed across the drives in one of several ways, referred to as RAID levels, depending on the required level of redundancy and performance. The different schemes, or data distribution layouts, are named by the word "RAID" followed by a number, for example RAID 0 or RAID 1. Each scheme, or RAID level, provides a different balance among the key goals: reliability, availability, performance, and capacity. RAID levels greater than RAID 0 provide protection against unrecoverable sector read errors, as well as against failures of whole physical drives.

### Data striping

In computer data storage, data striping is the technique of segmenting logically sequential data, such as a file, so that consecutive segments are stored on different physical storage devices.

Striping is useful when a processing device requests data more quickly than a single storage device can provide it. By spreading segments across multiple devices which can be accessed concurrently, total data throughput is increased. It is also a useful method for balancing I/O load across an array of disks. Striping is used across disk drives in redundant array of independent disks (RAID) storage, network interface controllers, different computers in clustered file systems and grid-oriented storage, and RAM in some systems.

<img src="http://www.maxtronic.com/images/stories/Product/RAID-Level/raid-0.png">

##### Advantages and disadvantages

Advantages of striping include performance and throughput. Sequential time interleaving of data accesses allows the lesser data access throughput of each storage devices to be cumulatively multiplied by the number of storage devices employed. Increased throughput allows the data processing device to continue its work without interruption, and thereby finish its procedures more quickly. This is manifested in improved performance of the data processing.

Because different segments of data are kept on different storage devices, the failure of one device causes the corruption of the full data sequence. In effect, the failure rate of the array of storage devices is equal to the sum of the failure rate of each storage device. This disadvantage of striping can be overcome by the storage of redundant information, such as parity, for the purpose of error correction. In such a system, the disadvantage is overcome at the cost of requiring extra storage.

### Disk mirroring

<img src="http://cottagedata.com/sysadmin/raid/raid1_1.jpg">

In data storage, disk mirroring is the replication of logical disk volumes onto separate physical hard disks in real time to ensure continuous availability. It is most commonly used in RAID 1. A mirrored volume is a complete logical representation of separate volume copies.

In a disaster recovery context, mirroring data over long distance is referred to as storage replication. Depending on the technologies used, replication can be performed synchronously, asynchronously, semi-synchronously, or point-in-time. Replication is enabled via microcode on the disk array controller or via server software. It is typically a proprietary solution, not compatible between various data storage device vendors.

Mirroring is typically only synchronous. Synchronous writing typically achieves a recovery point objective (RPO) of zero lost data. Asynchronous replication can achieve an RPO of just a few seconds while the remaining methodologies provide an RPO of a few minutes to perhaps several hours.

Disk mirroring differs from file shadowing that operates on the file level, and disk snapshots where data images are never re-synced with their origins.



### What Is A RAID?

RAID set-ups are software and hardware systems that are capable of  writing or reading data to and from numerous hard drives, in a modern  system various levels of RAID systems may be nested or joined to provide  more data redundancy & integrity or for more read/write speed, The  level of a RAID is consistently indicated with a number from 0-6 for  example RAID 0 or RAID 1 an instance of a nested RAID would be RAID 1+0  the 1 means a RAID 1 and the 0 means a RAID 0.

When you are explaining the features of a RAID level there are only two  phrases that are most commonly used these are; Striping & Mirroring,  Striping is when a file is written to numerous drives in the same way  this supplies a substantially faster write speed but doesn't provide any  defence from data loss in its most basic sort. Mirroring is where  documents are written to 2 or more drives in the same fashion this  supplies a faster read speed when several users need the same data, it  also offers defences against data loss as the identical data is on  numerous drives.

<img src="https://qph.fs.quoracdn.net/main-qimg-0c415511a124d83989d2549602070069-c">

### What Is A RAID 5?

A RAID 5 uses striping to provide fault tolerance in case of hard drive  failure and it provides a better read speed, fault-tolerance is achieved  through having data stored across the drives but with parity data  stored as well, whether a hard drive breaks the lost data may be rebuilt  with the parity data stored in the other drives. RAID 5 set-ups  maximise storage space provided by RAID's as there are no sizeable  quantities of data on one drive, a RAID 5 has certain advantages.
RAID 5 Advantages :

1. Optimise Storage use
2. Protection against disk failure
3. Quick read speed

<img src="https://qph.fs.quoracdn.net/main-qimg-12d26aeabd0e1503c4b7993c39ed4465">

A RAID 5 has a fast read speed making it perfect for companies which  have data that is used by many users at one time, although it does have a  lower write speed in comparison to other RAID's this is because it has  to write the core data as well as the parity data. This type of RAID  isn't acceptable for a company where there data is always being changed  and updated as this sort of RAID is made to be quick at reading data and  have fault tolerance.

##### RAID 5 Failures

With a RAID 5 if one hard drive breaks then it is crucial that the  broken drive is replaced with a new drive whenever possible because if  the hard drive isn't changed it causes damaging issues if one more hard  drive breaks, since it's expensive to get data regained. When one hard  disk drive breaks the system enters a critical state where write and  read rate is reduced massively but it is still possible to read and  write to and from the hard drive. Remember that RAID's are not a backup  option they are always there to provide fault tolerance.

RAID 5's can provide a high-read speed for companies that rely on quick  use of their data to be successful, it additionally provides a level of  built-in security against hard drive failure, therefore if your business  does process tons of data it is probably the top setup to go for, you  will notice a significant difference in the rate of computer system.
