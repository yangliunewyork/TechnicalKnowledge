# Symbolic link

In computing, a __symbolic link__ (also __symlink__ or __soft link__) is the nickname for any file that contains a reference to another file or directory in the form of an absolute or relative path and that affects pathname resolution.

### Overview

__A symbolic link contains a text string that is automatically interpreted and followed by the operating system as a path to another file or directory. This other file or directory is called the "target". The symbolic link is a second file that exists independently of its target. If a symbolic link is deleted, its target remains unaffected. If a symbolic link points to a target, and sometime later that target is moved, renamed or deleted, the symbolic link is not automatically updated or deleted, but continues to exist and still points to the old target, now a non-existing location or file. Symbolic links pointing to moved or non-existing targets are sometimes called broken, orphaned, dead, or dangling.__

Symbolic links are different from hard links. Hard links do not link paths on different volumes or file systems, whereas symbolic links may point to any file or directory irrespective of the volumes on which the link and target reside. Hard links always refer to an existing file, whereas symbolic links may contain an arbitrary path that does not point to anything.

Symbolic links operate transparently for many operations: programs that read or write to files named by a symbolic link will behave as if operating directly on the target file. However, they have the effect of changing an otherwise hierarchical filesystem from a tree into a directed graph, which can have consequences for such simple operations as figuring out the current directory of a process. Even the Unix .. convention for navigating to a directory's parent directory no longer works reliably in the face of symlinks. Some shells heuristically try to uphold the illusion of a tree-shaped hierarchy, but when they do, this causes them to produce different results from other programs that manipulate pathnames without such heuristic, relying on the operating system instead. Programs that need to handle symbolic links specially (e.g., shells and backup utilities) thus need to identify and manipulate them directly.

Some Unix as well as Linux distributions use symbolic links extensively in an effort to reorder the file system hierarchy. This is accomplished with several mechanisms, such as variant, context-dependent symbolic links. This offers the opportunity to create a more intuitive or application-specific directory tree and to reorganize the system without having to redesign the core set of system functions and utilities.

# Hard link

In computing, a hard link is a directory entry that associates a name with a file on a file system. All directory-based file systems must have (at least) one hard link giving the original name for each file. The term “hard link” is usually only used in file systems that allow more than one hard link for the same file.

Creating a hard link has the effect of giving one file multiple names (e.g. different names in different directories) all of which independently connect to the same data on the disk, none of which depends on any of the others.[1] This causes an alias effect: e.g. if the file is opened by any one of its names, and changes are made to its content, then these changes will also be visible when the file is opened by an alternative name. By contrast, a soft link or “shortcut” to a file is not a direct link to the data itself, but rather is a short file that contains the text of a file name, or a location that gives direct access to yet another file name within some directory. The name contained in or referred to by the soft link may either be a hard link or another soft link. This also creates aliasing, but in a different way.

Every directory is itself a file, only special because it contains a list of file names maintained by the file system. Since directories themselves are files, multiple hard links to directories are possible which would create loops within the structure of the directories, rather than a branching structure like a tree. For that reason, the creation of hard links to directories is sometimes forbidden, even if possible.

### Link counter

Most file systems that support hard links use reference counting. An integer value is stored with each physical data section. This integer represents the total number of links that have been created to point to the data. When a new link is created, this value is increased by one. When a link is removed, the value is decreased by one. If the link count becomes zero, the operating system usually automatically deallocates the data space of the file if no process has the file opened for access, but it may choose not to do so immediately, either for performance sake or to enable undelete command.

The maintenance of this value assists users in preventing data loss, for operating system's kernel guarantees that there will be no dangling hard links pointing nowhere (which can and does happen with symbolic links) and that filesystem file and associated inode will be preserved as long as a single hard link (directory reference) points to it or any process keeps the associated file open, relieving the burden of this accounting from programmer or user. This is a simple method for the file system to track the use of a given area of storage, as zero values indicate free space and nonzero values indicate used space.


# Soft link vs hard link

![alt](https://i.stack.imgur.com/f7Ijz.jpg)

Create two files:

```
$ touch blah1   
$ touch blah2
```

Enter some data into them:

```
$ echo "Cat" > blah1
$ echo "Dog" > blah2
```

And as expected:

```
$cat blah1; cat blah2
Cat
Dog
```

Let's create hard and soft links:

```
$ ln blah1 blah1-hard
$ ln -s blah2 blah2-soft
```
Let's see what just happened:

```
$ ls -ltr

-rw-r--r-- 2 yaliu dev 4 2017-10-18 11:49 blah1-hard
-rw-r--r-- 2 yaliu dev 4 2017-10-18 11:49 blah1
-rw-r--r-- 1 yaliu dev 4 2017-10-18 11:49 blah2
lrwxrwxrwx 1 yaliu dev 5 2017-10-18 11:50 blah2-soft -> blah2
```

Changing the name of blah1 does not matter:

```
$ mv blah1 blah1-new
$ cat blah1-hard
Cat
``

blah1-hard points to the inode, the contents, of the file - that wasn't changed.

```
$ mv blah2 blah2-new
$ ls blah2-soft
blah2-soft
$ cat blah2-soft  
cat: blah2-soft: No such file or directory
```

The contents of the file could not be found because the soft link points to the name, that was changed, and not to the contents.
Similarly, If blah1 is deleted, blah1-hard still holds the contents; if blah2 is deleted, blah2-soft is just a link to a non-existing file.
