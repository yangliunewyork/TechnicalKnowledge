The __export__ command is one of the bash shell BUILTINS commands, which means it is part of your shell. The export command is fairly simple to use as it has straightforward syntax with only three available command options. __In general, the export command marks an environment variable to be exported with any newly forked child processes and thus it allows a child process to inherit all marked variables.__ 

### Export basics

Think over the following example:
```
$ a=linuxcareer.com
$ echo $a
linuxcareer.com
$ bash
$ echo $a

$
```

1. Line 1: new variable called "a" is created to contain string "linuxcareer.com"
2. Line 2: we use echo command to print out a content of the variable "a"
3. Line 3: we have created a new child bash shell
4. Line 4: variable "a" no longer have any values defined

From the above we can see that any new child process forked from a parent process by default does not inherit parent's variables. This is where the export command comes handy. What follows is a new version of the above example using the export command:

```
$ a=linuxcareer.com
$ echo $a
linuxcareer.com
$ export a
$ bash
$ echo $a
linuxcareer.com
$
```

On the line 3 we have now used the export command to make the variable "a" to be exported when a new child process is created. As a result the variable "a" still contains the string "linuxcareer.com" even after a new bash shell was created. It is important to note that, in order to export the variable "a" to be available in the new process, the process must be forked from the parent process where the actual variable was exported. The relationship between the child and parent process is explained below.

