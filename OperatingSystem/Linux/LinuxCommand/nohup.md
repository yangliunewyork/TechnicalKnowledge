Sometimes a process takes so long that you would like to start it running, then turn off the terminal and go home without waiting for it to finish. But if you turn off your terminal or break your connection, the process will normally be killed even if you used &. The Command __nohup__("no hangup") was created to deal with this situation, if you say:

```
$nohup command &
```

the command will continue to run if you log out. Any output from the command is saved in a file called nohup.out. There is no way to nohup a command retroactively.

If your process will take a lot of processor resources, it is kind to those who share your system to run your job with lower than normal priority; this is done by another program called __nice__:

```
$ nice expensive-command &
```

nohup automatically calls nice, because if you're going to log out you can afford to have the command take a little longer.

### What is nohup?

__nohup__ is a POSIX command to ignore the __HUP__ (hangup) signal. The HUP signal is, by convention, the way a terminal warns dependent processes of logout.

Output that would normally go to the terminal goes to a file called nohup.out if it has not already been redirected.

### Use

The first of the commands below starts the program abcd in the background in such a way that the subsequent logout does not stop it.

```
$ nohup abcd &
$ exit
```

Note that these methods prevent the process from being sent a 'stop' signal on logout, but if input/output is being received for these standard I/O files (stdin, stdout, or stderr), they will still hang the terminal.

nohup is often used in combination with the nice command to run processes on a lower priority.

```
$ nohup nice abcd &
```

