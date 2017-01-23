## What is Pipeline ?

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f6/Pipeline.svg/560px-Pipeline.svg.png)

In Unix-like computer operating systems, a pipeline is a sequence of processes chained together by their standard streams, so that the output of each process (stdout) feeds directly as input (stdin) to the next one.

The standard shell syntax for pipelines is to list multiple commands, separated by vertical bars ("pipes" in common unix verbiage). For example, to list files in the current directory (ls), retain only the lines of ls output containing the string "key" (grep), and view the result in a scrolling page (less), a user types the following into the command line of a terminal:

```  ls -l | grep key | less ``` 

```ls -l``` produces a process, the output (stdout) of which is piped to the input (stdin) of the process for ```grep key```; and likewise for the process for ```less```. Each process takes input from the previous process and produces output for the next process via standard streams. Each "|" tells the shell to connect the standard output of the command on the left to the standard input of the command on the right by an inter-process communication mechanism called an (anonymous) pipe, implemented in the operating system. Pipes are unidirectional, data flows through the pipeline from left to right.

``` process1 | process2 | process3 ```

### Error stream
By default, the standard error streams ("stderr") of the processes in a pipeline are not passed on through the pipe; instead, they are merged and directed to the console. However, many shells have additional syntax for changing this behavior. In the csh shell, for instance, using "|&" instead of "|" signifies that the standard error stream should also be merged with the standard output and fed to the next process. The Bourne Shell can also merge standard error, using 2>&1, as well as redirect it to a different file.
