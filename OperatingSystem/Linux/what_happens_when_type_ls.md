https://medium.com/meatandmachines/what-really-happens-when-you-type-ls-l-in-the-shell-a8914950fd73  


### What (really) happens when you type ls -l in the shell

![alt](https://cdn-images-1.medium.com/max/600/1*zEv6mAa2wzHnz4a5uWW4gw.png)

To understand what (really) happens when you type ls -l in the shell, you have to understand what the shell is, in relation to the kernel.

* The __kernel__ is the central, most fundamental part of a computer operating system. It’s a program that controls all other programs on the computer, talking to the hardware and software, highly involved in resource management.

*The __shell__ is an application, one of the two major ways of controlling a computer (GUI the other). It is the way a user talks to the kernel, by typing commands into the command line (why it’s known as the command line interpreter).

On the superficial level, typing ```ls -l``` displays all the files and directories in the current working directory, along with respective permissions, owners, and created date and time.

### On the deeper level, this is what happens when you type “ls -l” and “enter” in the shell:

First and foremost, the shell prints the prompt, prompting the user to enter a command. The shell reads the command ```ls -l``` from the getline() function’s STDIN, parsing the command line into arguments that it is passing to the program it is executing.

The shell checks if ```ls``` is an alias. If it is, the alias replaces ```ls``` with its value.

If ls isn’t an alias, the shell checks if the word of a command is a built-in.

#### The environment is copied and passed to the new process


Then, the shell looks for a program file called ls where all the executable files are in the system — in the shell’s environment (an array of strings), specifically in the $PATH variable. The $PATH variable is a list of directories the shell searches every time a command is entered. $PATH, one of the environment variables, is parsed using the ‘=’ as a delimiter. Once the $PATH is identified, all the directories in $PATH are tokenized, parsed further using ‘:’ as a delimiter.

![alt](https://cdn-images-1.medium.com/max/800/1*xvpwLH0XuOvYFhCJNkysHA.png)

The ```ls``` binary executable file will be located [in one of the major subdirectories of the ‘/usr’ directory] in the file ‘/usr/bin/ls’ — ‘/usr/bin’ contains most of the executable files (ie. ready-to-run programs).

```
To execute ls, three system calls are made: fork / execve / wait
```

> System calls are calls to the Kernel code to do something.

To create new processes (to run commands) in Unix, the system call fork() is made to duplicate the (Shell) parent process, creating a child process of the (Shell) parent process.

The system call execve() is made and does three things: the operating system (OS) stops the duplicated process (of the parent), loads up the new program (in this case: ls), and starts (the new program ls). execve() replaces defining parts of the current process’ memory stack with the new stuff loaded from the ls executable file.


The input to execve (for ls -l) will be:

```
execve(“/bin/ls”, {“ls” or “/bin/ls”, “-l”, NULL}, NULL);
```

If the executable binary (ls) file does not exist, an error will be printed.

Meanwhile, the parent process continues to do other things, keeping track of its children as well, using the system call wait().

Lastly, After ls -l is executed, the shell executes shutdown commands, frees up memory, exits, and re-prompts the user for input.


