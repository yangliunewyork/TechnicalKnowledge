On POSIX-compliant platforms, SIGHUP ("signal hang up") is a signal sent to a process when its controlling terminal is closed. (It was originally designed to notify the process of a serial line drop.) SIGHUP is a symbolic constant defined in the header file signal.h.

# Modern usage

With the decline of access via serial line, the meaning of SIGHUP has changed somewhat on modern systems, often meaning a controlling pseudo or virtual terminal has been closed. If a command is executed inside a terminal window and the terminal window is closed while the command process is still running, it receives SIGHUP.

If the process receiving SIGHUP is a Unix shell, then as part of job control it will often intercept the signal and ensure that all stopped processes are continued before sending the signal to child processes (more precisely, process groups, represented internally by the shell as a "job"), which by default terminates them.

This can be circumvented in two ways. Firstly, the Single UNIX Specification describes a shell utility called nohup, which can be used as a wrapper to start a program and make it ignore SIGHUP by default. Secondly, child process groups can be "disowned" by invoking disown with the job id, which removes the process group from the shell's job table (so they will not be sent SIGHUP), or (optionally) keeps them in the job table but prevents them from receiving SIGHUP on shell termination.

Different shells also have other methods of controlling and managing SIGHUP, such as the disown facility of ksh. Most modern Linux distributions documentation specify using kill -HUP <processID> to send the SIGHUP signal.

Daemon programs sometimes use SIGHUP as a signal to restart themselves, the most common reason for this being to re-read a configuration file that has been changed.

### The 3 most important "kill" signals on the Linux/UNIX command line

Most Linux or UNIX users know that there is a kill(1) command to stop processes, but what are the options, what do they mean?

These options are called signals, which can be expressed in either numbers or words. Some known once are "-1" or "-HUP". Also well known is "-9" (aka "-KILL")。

* -1 or -HUP - This argument makes kill send the "Hang Up" signal to processes. This probably originates from the modem/dial-in era. Processes have to be programmed to actually listen to this process and do something with it. Most daemons are programmed to re-read their configuration when they receive such a signal. Anyway; this is very likely the safest kill signal there is, it should not obstruct anything.  
* -2 or -SIGINT - This is the same as starting some program and pressing CTRL+C during execution. Most programs will stop, you could lose data.  
* -9 or -KILL - The kernel will let go of the process without informing the process of it. An unclean kill like this could result in data loss. This is the "hardest", "roughest" and most unsafe kill signal available, and should only be used to stop something that seems unstoppable.  
* -15 or -TERM - Tell the process to stop whatever it's doing, and end itself. When you don't specify any signal, this signal is used. It should be fairly safe to perform, but better start with a "-1" or "-HUP".  

