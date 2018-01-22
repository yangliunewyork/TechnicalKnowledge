In Unix-like computer operating systems, a __pipeline__ is a sequence of processes chained together by their standard streams, so that the output of each process (stdout) feeds directly as input (stdin) to the next one.

The concept of pipelines was championed by Douglas McIlroy at Unix's ancestral home of Bell Labs, during the development of Unix, shaping its toolbox philosophy. It is named by analogy to a physical pipeline.

The standard shell syntax for pipelines is to list multiple commands, separated by vertical bars ("pipes" in common Unix verbiage). For example, to list files in the current directory (ls), retain only the lines of ls output containing the string "key" (grep), and view the result in a scrolling page (less), a user types the following into the command line of a terminal:

```
 ls -l | grep key | less
 ```
 
 "ls -l" produces a process, the output (stdout) of which is piped to the input (stdin) of the process for "grep key"; and likewise for the process for "less". Each process takes input from the previous process and produces output for the next process via standard streams. Each "|" tells the shell to connect the standard output of the command on the left to the standard input of the command on the right by an _inter-process communication_ mechanism called an (anonymous) pipe, implemented in the operating system. Pipes are _unidirectional_; data flows through the pipeline from left to right.
 
 ```
  process1 | process2 | process3
  ```
  
  
