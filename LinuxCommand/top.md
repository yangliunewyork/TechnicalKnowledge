### What Information Is Shown
The following information is displayed when you run the Linux top command:
```
$ top
top - 13:22:17 up 73 days,  4:02, 13 users,  load average: 14.01, 12.75, 9.17
Tasks: 910 total,   5 running, 905 sleeping,   0 stopped,   0 zombie
Cpu(s):  4.4%us,  1.9%sy,  0.0%ni, 90.9%id,  2.8%wa,  0.0%hi,  0.0%si,  0.0%st
Mem:  65922536k total, 65209996k used,   712540k free,    77840k buffers
Swap:  2047996k total,  2047996k used,        0k free, 60009256k cached

  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND
34637 root      20   0 65104  18m 4416 S 35.1  0.0   0:03.73 cf-agent
35333 tom     20   0 99760  86m 1292 D 14.6  0.1   0:00.44 ld
35363 jack     20   0 70552  60m 1200 R  6.6  0.1   0:00.20 ld
35374 steven     20   0 84376  74m 1080 R  6.0  0.1   0:00.18 ld
```

Line 1:
* The time
* How long the computer has been running
* Number of users
* Load average
The load average shows the system load time for the last 1, 5 and 15 minutes.

Line 2:
* Total number of tasks
* Number of running tasks
* Number of sleeping tasks
* Number of stopped tasks
* Number of zombie tasks

Line 3:
* CPU usage as a percentage by the user
* CPU usage as a percentage by system
* CPU usage as a percentage by low priority processes
* CPU usage as a percentage by idle processes
* CPU usage as a percentage by io wait
* CPU usage as a percentage by hardware interrupts
* CPU usage as a percentage by software interrupts
* CPU usage as a percentage by steal time

Line 3:
* Total system memory
* Free memory
* Memory used
* Buffer cache

Line 4:
* Total swap available
* Total swap free
* Total swap used
* available memory

Main table:
* Process ID
* User
* Priority
* Nice level
* Virtual memory used by process
* Resident memory used by a process
* Shareable memory
* CPU used by process as a percentage
* Memory used by process as a percentage
* Time process has been running
* Command


Key Switches For The Top Command:
* -h - Show the current version
* -c - This toggles the command column between showing command and program name
* -d - Specify the delay time between refreshing the screen
* -o - Sorts by the named field
* -p - Only show processes with specified process IDs
* -u - Show only processes by the specified user
