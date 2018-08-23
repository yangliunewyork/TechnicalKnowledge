http://blog.httrack.com/blog/2013/11/15/everything-you-always-wanted-to-know-about-fsync/  

The operating system, by default, caches file data that is read from and written to disk.

A typical read operation involves physical disk access to read the data from disk into the file system cache, and then to copy the data from the cache to the application buffer. Similarly, a write operation involves physical disk access to copy the data from the application buffer into the file system cache, and then to copy it from the cache to the physical disk.

# Everything You Always Wanted to Know About Fsync

