## What is inode ?

![alt](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter12/12_09_UNIX_inode.jpg)

An inode is a data structure on a filesystem on Linux and other Unix-like operating systems that stores all the information about a file except its name and its actual data.

A data structure is a way of storing data so that it can be used efficiently. Different types of data structures are suited to different types of applications, and some are highly specialized for specific types of tasks.

A filesystem is the hierarchy of directories (also referred to as the directory tree) that is used to organize files on a computer. On Unix-like operating systems, the directories start with the root directory (designated by a forward slash), which contains a series of subdirectories, each of which, in turn, may contain further subdirectories, etc. A variant of this definition is the part of the entire hierarchy of directories or of the directory tree that is located on a single hard disk drive (HDD) or other storage device or on a single partition (i.e., a logically independent section of a HDD).

A file is a named collection of related information that appears to the user as a single, contiguous block of data and that is retained in storage. It does not automatically contain information about itself (e.g., its size, when it was created or where it is located on the system), unless some human purposely adds in such data. Such information about a file, in contrast to the data contained in a file, is its metadata (i.e., data about data).

Storage refers to computer devices or media that can hold data for relatively long periods of time (e.g., years or decades), such as disk drives and magnetic tape. A directory (referred to as a folder on some operating systems) in Unix-like operating systems is merely a special type of file that associates file names with a collection of inodes.

When a file is created, it is assigned both a name and an inode number, which is an integer that is unique within the filesystem. Both the file names and their corresponding inode numbers are stored as entries in the directory that appears to the user to contain the files. That is, the directory associates file names with inodes.

Whenever a user or a program refers to a file by name, the operating system uses that name to look up the corresponding inode, which then enables the system to obtain the information it needs about the file to perform further operations. **That is, a file name in a Unix-like operating system is merely an entry in a table with inode numbers, rather than being associated directly with a file (in contrast to other operating systems such as the Microsoft Windows systems).** The inode numbers and their corresponding inodes are held in inode tables, which are stored in strategic locations in a filesystem, including near its beginning.

![alt](https://upload.wikimedia.org/wikipedia/commons/f/f8/File_table_and_inode_table.svg)

This detaching of a file's name from its other metadata is what allows the system to implement hard links and thus have multiple names for any file. A hard link is an entry in a directory that contains a pointer directly to the inode bearing the file's metadata. When a new hard link to a file is created, both links share the same inode number because the link is only a pointer, not a copy of the file.

The concept of inodes is particularly important to the recovery of damaged filesystems. When parts of the inode are lost, they appear in the lost+found directory within the partition in which they once existed.

Whereas a file contains only its own content and a directory holds only the names of the files that appear to the user to be contained in it and their inode numbers, an inode contains all the other information describing a file. This metadata includes (1) the size of the file (in bytes) and its physical location (i.e., the addresses of the blocks of storage containing the file's data on a HDD), (2) the file's owner and group, (3) the file's access permissions (i.e., which users are permitted to read, write and/or execute the file), (4) timestamps telling when the inode was created, last modified and last accessed and (5) a reference count telling how many hard links point to the inode.

The operating system obtains a file's inode number and information in the inode through the use of the system call named stat. A system call is a request in a Unix-like operating system by an active process for a service performed by the kernel (i.e., the core of the operating system), such as input/output (I/O) or process creation. System calls can also be viewed as clearly-defined, direct entry points into the kernel through which programs request services from it. A process is an instance of a program in execution, and an active process process is one which is currently progressing in the CPU (central processing unit).

Space for inodes must be set aside when an operating system (or a new filesystem) is installed and that system does its initial structuring of the filesystem. Within any filesystem, the maximum number of inodes, and hence the maximum number of files, is set when the filesystem is created.

**There are two ways in which a filesystem can run out of space: it can consume all the space for adding new data (i.e., to existing files or to new files), or it can use up all the inodes. The latter can bring computer use to a sudden stop just as easily as can the former, because exhaustion of the inodes will prohibit the creation of additional files even if sufficient HDD space exists. It is particularly easy to run out of inodes if a filesystem contains a very large number of very small files. A typical system, however, runs out of file space first, because the average file size on most system is larger than two kilobytes.**

The decision as to how many inodes to create is made on Linux using an algorithm (i.e., a set of precise and unambiguous rules that specify how to solve some problem or perform some task) that considers the size of the partition and the average file size. The default setting creates an inode for every 2K bytes contained in the filesystem, but the number can be adjusted by the user when creating the filesystem. For example, it can be wise to create fewer inodes when setting up a filesystem that will contain just a few large files. Similarly, for a filesystem intended for mostly small files, it is advisable to allocate more space to inodes and less to file contents.

A file's inode number can easily be found by using the ls command, which by default lists the objects (i.e., files, links and directories) in the current directory (i.e., the directory in which the user is currently working), with its -i option. Thus, for example, the following will show the name of each object in the current directory together with its inode number:
```
ls -i
```
Additional information can be obtained about the inodes on a system by using the df command. This command by default shows the names and sizes of each mounted (i.e., logically connected to the main filesystem) filesystem as well as how much of each is used and unused. One of df's most useful options is -h, which formats the information in human readable form (i.e., in terms of kilobytes, megabytes and gigabytes). Thus the following provides a nice display of both the currently available space and the used space for each filesystem or partition:
```
df -h
```

df's -i option instructs it to supply information about inodes on each filesystem rather than about available space. Specifically, it tells df to return for each mounted filesystem the total number of inodes, the number of free inodes, the number of used inodes and the percentage of inodes used. This option can be used together with the -h option as follows to make the output easier to read:
```
df -hi
```
The exact story behind the creation of the term inode has been lost, but it is very likely that the i originally stood for index and/or information.


## What's the difference between inode number and file descriptor?
inode numbers are like pointers within the file system, and are stored within the file system itself. (In particular, a directory entry is the combination of a name and an inode, and you can see this using ```ls -i```.) File descriptor numbers, on the other hand, are not stored anywhere within the file system, and are dynamically generated by the kernel when you call open() (or certain other system calls). They are pointers into the kernel's file descriptor table for a particular process.

An inode number always refers to something on a device somewhere. A file descriptor may also refer to an anonymous pipe, a socket, or some other kind of resource, such as the result of a call to ```epoll_create()``` on Linux.

An inode number unambiguously identifies a file or directory on a given device, but two files on different mounts may have the same inode. A file descriptor does not unambiguously identify anything by itself; in combination with a process ID it unambiguously identifies some resource on the system, even if you don't know which device it's on.

Every file or directory on a given device has a unique inode number. (If two files on the same device have the same inode number, then they are really the same file with two different names.) On the other hand, a file or directory may be opened several times by the same process or by different processes, and thus have multiple different file descriptors. Additionally, files or directories that are not currently open by any process do not have any file descriptors referring to them.

A valid file descriptor is associated with file mode flags and offset. That is, it grants the possessing process the right to read or write the file (or both), based on how the file descriptor was obtained; it also remembers some position within the file. However, it does not contain any metadata associated with the file itself, such as timestamps or Unix permission bits. An inode contains timestamps and Unix permission bits, but no file mode flags or offset.
