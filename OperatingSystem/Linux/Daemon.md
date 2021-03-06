In multitasking computer operating systems, a daemon (/ˈdiːmən/ or /ˈdeɪmən/)[1] is a computer program that runs as a background process, rather than being under the direct control of an interactive user. Traditionally, the process names of a daemon end with the letter d, for clarification that the process is, in fact, a daemon, and for differentiation between a daemon and a normal computer program. For example, _syslogd_ is the daemon that implements the system logging facility, and _sshd_ is a daemon that serves incoming SSH connections.

In a Unix environment, the parent process of a daemon is often, but not always, the _init_ process. A daemon is usually either created by a process forking a child process and then immediately exiting, thus causing init to adopt the child process, or by the init process directly launching the daemon. In addition, a daemon launched by forking and exiting typically must perform other operations, such as dissociating the process from any controlling terminal (tty). Such procedures are often implemented in various convenience routines such as daemon in Unix.

Systems often start daemons at boot time which will respond to network requests, hardware activity, or other programs by performing some task. Daemons such as cron may also perform defined tasks at scheduled times.




