
PATH is an environmental variable in Linux and other Unix-like operating systems that tells the shell which directories to search for executable files (i.e., ready-to-run programs) in response to commands issued by a user. It increases both the convenience and the safety of such operating systems and is widely considered to be the single most important environmental variable.

Environmental variables are a class of variables (i.e., items whose values can be changed) that tell the shell how to behave as the user works at the command line (i.e., in a text-only mode) or with shell scripts (i.e., short programs written in a shell programming language). A shell is a program that provides the traditional, text-only user interface for Unix-like operating systems; its primary function is to read commands that are typed in at the command line and then execute (i.e., run) them.

PATH (which is written with all upper case letters) should not be confused with the term path (lower case letters). The latter is a file's or directory's address on a filesystem (i.e., the hierarchy of directories and files that is used to organize information stored on a computer). A relative path is an address relative to the current directory (i.e., the directory in which a user is currently working). An absolute path (also called a full path) is an address relative to the root directory (i.e., the directory at the very top of the filesystem and which contains all other directories and files).

A user's PATH consists of a series of colon-separated absolute paths that are stored in plain text files. Whenever a user types in a command at the command line that is not built into the shell or that does not include its absolute path and then presses the Enter key, the shell searches through those directories, which constitute the user's search path, until it finds an executable file with that name.

The concentrating by default of most executable files in just a few directories rather than spread all over the filesystem and the use of the PATH variable to find them eliminates the need for users to remember which directories they are in and to type their absolute path names. That is, any such program can be run by merely typing its name, such as ls instead of /bin/ls and head instead of /usr/bin/head, regardless of where the user is currently working on the filesystem. This also greatly reduces the possibility of damage to data or even to the system as a whole from the accidental running of a script that has the same name as a standard command.1

A list of all the current environmental variables and their values for the current user, including all the directories in the PATH variable, can be seen by running the env command without any options or arguments (i.e., input data), i.e.,

```
env
```

As there can be considerable output, it can be convenient to modify this command so that it displays just the PATH environmental variable and its value. This can be accomplished by using a pipe (represented by the vertical bar character) to transfer the output of env to the grep filter and use PATH as an argument to grep, i.e.,

```
env | grep PATH
```

Another way to view the contents of just PATH alone is by using the echo command with $PATH as an argument:

```
echo $PATH
```

echo repeats on the display screen whatever follows it on the command line. The dollar sign immediately preceding PATH tells echo to repeat the value of the variable PATH rather than its name.

Each user on a system can have a different PATH variable. When an operating system is installed, one default PATH variable is created for the root (i.e., administrative) account and another default is created that will be applied to all ordinary user accounts as they are added to the system. The PATH variable for the root user contains more directories than for ordinary users because it includes directories, such as /sbin and /usr/sbin, that contain programs that are normally used only by that user.

PATH variables can be changed relatively easily. They can be changed just for the current login session, or they can be changed permanently (i.e., so that the changes will persist through future sessions).

It is a simple matter to add a directory to a user's PATH variable (and thereby add it to the user's default search path). It can be accomplished for the current session by using the following command, in which directory is the full path of the directory to be entered:

```
PATH="directory:$PATH"
```

For example, to add the directory /usr/sbin, the following would be used:

```
PATH="/usr/sbin:$PATH"
```

An alternative is to employ the export command, which is used to change aspects of the environment. Thus, the above absolute path could be added with the following two commands in sequence

```
PATH=$PATH:/usr/sbin
export PATH
```

or its single-line equivalent

```
export PATH=$PATH:/usr/sbin
```

That the directory has been added can be easily confirmed by again using the echo command with $PATH as its argument.

An addition to a user's PATH variable can be made permanent by adding it to that user's .bash_profile file. .bash_profile is a hidden file in each user's home directory that defines any specific environmental variables and startup programs for that user. A hidden file is a file whose name begins with a dot (i.e., a period) and which is normally not visible; however, it can be seen by using the ls (i.e., list) command with its -a (i.e., all) option.

Thus, for example, to add a directory named /usr/test to a user's PATH variable, it should be appended with a text editor to the line that begins with PATH so that the line reads something like PATH=$PATH:$HOME/bin:/usr/test. It is important that each absolute path be directly (i.e., with no intervening spaces) preceded by a colon.

It is sometimes desired to run a script or program which has been installed in a user's home directory or some other location that is not in the user's default search path. Such script or program can, of course, be run by typing in its absolute path. But an often more convenient alternative when the script or program is in the current directory is to merely precede the command name with a dot slash (i.e., a dot followed by a forward slash and with no intervening spaces). The dot is used in paths to represent the current directory and the slash is used as a directory separator and to separate directory names from file names.

MS-DOS also uses a PATH variable. However, it differs from Unix-like operating systems in that it searches the user's current directory before it searches in any directories in that variable.

