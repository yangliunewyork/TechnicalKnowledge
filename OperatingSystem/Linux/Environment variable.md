An __environment variable__ is a dynamic-named value that can affect the way running processes will behave on a computer.

They are part of the environment in which a process runs. For example, a running process can query the value of the TEMP environment variable to discover a suitable location to store temporary files, or the HOME or USERPROFILE variable to find the directory structure owned by the user running the process.

# Design

__In all Unix and Unix-like systems, each process has its own separate set of environment variables. By default, when a process is created, it inherits a duplicate environment of its parent process, except for explicit changes made by the parent when it creates the child.__ At the API level, these changes must be done between running ```fork``` and ```exec```. Alternatively, from command shells such as bash, a user can change environment variables for a particular command invocation by indirectly invoking it via ```env``` or using the ```ENVIRONMENT_VARIABLE=VALUE <command>``` notation. A running program can access the values of environment variables for configuration purposes.

Shell scripts and batch files use environment variables to communicate data and preferences to child processes. They can also be used to store temporary values for reference later in a shell script. However, in Unix, other variables are usually used for this.

In Unix, an environment variable that is changed in a script or compiled program will only affect that process and possibly child processes. The parent process and any unrelated processes will not be affected. In MS-DOS, changing or removing a variable's value inside a batch file will change the variable for the duration of COMMAND.COM's existence.

In Unix, the environment variables are normally initialized during system startup by the system init scripts, and hence inherited by all other processes in the system. Users can, and often do, augment them in the profile script for the command shell they are using. In Microsoft Windows, each environment variable's default value is stored in the Windows registry or set in the AUTOEXEC.BAT file.

On Unix, a setuid program is given an environment chosen by its caller, but it runs with different authority from its caller. The dynamic linker will usually load code from locations specified by the environment variables $LD_LIBRARY_PATH and $LD_PRELOAD and run it with the process's authority. If a setuid program did this, it would be insecure, because its caller could get it to run arbitrary code and hence misuse its authority. For this reason, libc unsets these environment variables at startup in a setuid process. setuid programs usually unset unknown environment variables and check others or set them to reasonable values.

# Syntax

The variables can be used both in scripts and on the command line. They are usually referenced by putting special symbols in front of or around the variable name. For instance, to display the user home directory, in most scripting environments, the user has to type:

```
echo $HOME
```

The commands ```env```, ```set```, and ```printenv``` display all environment variables and their values. printenv can also be used to print a single variable by giving that variable name as the sole argument to the command.

A few simple principles govern how environment variables achieve their effect:

* Environment variables are local to the process in which they were set. If two shell processes are spawned and the value of an environment variable is changed in one, that change will not be seen by the other.
* When a child process is created, it inherits all the environment variables and their values from the parent process. Usually, when a program calls another program, it first creates a child process by _forking_, then the child adjusts the environment as needed and lastly the child replaces itself with the program to be called. This procedure gives the calling program control over the environment of the called program.
* In Unix and Unix-like systems, the names of environment variables are case-sensitive.

In Unix shells, variables may be assigned without the ```export``` keyword. Variables defined in this way are displayed by the ```set``` command, but are not true environment variables, as they are stored only by the shell and not recognized by the kernel. The printenv command will not display them, and child processes do not inherit them.

The persistence of an environment variable can be session-wide or system-wide.

