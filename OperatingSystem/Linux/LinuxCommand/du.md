The __du (i.e., disk usage)__ command reports the sizes of directory trees inclusive of all of their contents and the sizes of individual files. This makes it useful for tracking down space hogs, i.e., directories and files that consume large or excessive amounts of space on a __hard disk drive (HDD)__ or other storage media. 

 A directory tree is a hierarchy of directories that consists of a single directory, called the parent directory or top level directory, and all levels of its subdirectories (i.e., directories within a directory). Any directory can be regarded as being the start of its own directory tree, at least if it contains subdirectories. Thus, a typical computer contains a large number of directory trees.

du is commonly employed by system administrators as a supplement to automated monitoring and notification programs that help prevent key directories and partitions (i.e., logically independent sections of a HDD) from becoming full. Full, or even nearly full, directories and partitions can cause a system to slow down, prevent users from logging in and even result in a system crash. Although visually identifying heavy consumers of disk space can be practical if there are relatively few users on a system, it is clearly not efficient for large systems with hundreds or thousands of users.

A minor limitation of du is the fact that the sizes of directories and files it reports are approximations, not exact numbers, and there is frequently a small discrepancy between these sizes and the sizes reported by other commands. However, this rarely detracts from its usefulness.

Also, du can only be used to estimate space consumption for directories and files for which the user has reading permission. Thus, an ordinary user would generally not be able to use du to determine space consumption for files or directories belonging to other users, including those belonging to the root account (i.e., the system administrator). However, as du is used mainly by system administrators, this is usually not a problem. 

### Further reading

http://www.linfo.org/du.html

https://www.geeksforgeeks.org/du-command-linux-examples/
