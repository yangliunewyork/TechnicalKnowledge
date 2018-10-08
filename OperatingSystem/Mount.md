Mounting is a process by which the operating system makes files and directories on a storage device (such as hard drive, CD-ROM, or network share) available for users to access via the computer's file system.

In general, the process of mounting comprises operating system acquiring access to the storage medium; recognizing, reading, processing file system structure and metadata on it; before registering them to the virtual file system (VFS) component.

The exact location in VFS that the newly-mounted medium got registered is called mount point; when the mounting process is completed, the user can access files and directories on the medium from there.

An opposite process of mounting is called unmounting, in which the operating system cuts off all user access to files and directories on the mount point, writes the remaining queue of user data to the storage device, refreshes file system metadata, then relinquishes access to the device; making the storage device safe for removal.

Normally, when the computer is shutting down, every mounted storage will undergo an unmounting process to ensure that all queued data got written, and to preserve integrity of file system structure on the media. 
