### Answering whether or not I/O is causing system slowness
To identify whether I/O is causing system slowness you can use several commands but the easiest is the unix command top.
```
 $ top
 top - 14:31:20 up 35 min, 4 users, load average: 2.25, 1.74, 1.68
 Tasks: 71 total, 1 running, 70 sleeping, 0 stopped, 0 zombie
 Cpu(s): 2.3%us, 1.7%sy, 0.0%ni, 0.0%id, 96.0%wa, 0.0%hi, 0.0%si, 0.0%st
 Mem: 245440k total, 241004k used, 4436k free, 496k buffers
 Swap: 409596k total, 5436k used, 404160k free, 182812k cached
```
From the CPU(s) line you can see the current percentage of CPU in I/O Wait; The higher the number the more cpu resources are waiting for I/O access.

wa -- iowait
 Amount of time the CPU has been waiting for I/O to complete.

### Finding which disk is being written to
The above top command shows I/O Wait from the system as a whole but it does not tell you what disk is being affected; for this we will use the iostat command.
```
 $ iostat -x 2 5
 avg-cpu: %user %nice %system %iowait %steal %idle
  3.66 0.00 47.64 48.69 0.00 0.00

 Device: rrqm/s wrqm/s r/s w/s rkB/s wkB/s avgrq-sz avgqu-sz await r_await w_await svctm %util
 sda 44.50 39.27 117.28 29.32 11220.94 13126.70 332.17 65.77 462.79 9.80 2274.71 7.60 111.41
 dm-0 0.00 0.00 83.25 9.95 10515.18 4295.29 317.84 57.01 648.54 16.73 5935.79 11.48 107.02
 dm-1 0.00 0.00 57.07 40.84 228.27 163.35 8.00 93.84 979.61 13.94 2329.08 10.93 107.02
```
The iostat command in the example will print a report every 2 seconds for 5 intervals; the -x tells iostat to print out an extended report.

The 1st report from iostat will print statistics based on the last time the system was booted; for this reason in most circumstances the first report from iostat should be ignored. Every sub-sequential report printed will be based on the time since the previous interval. For example in our command we will print a report 5 times, the 2nd report are disk statistics gathered since the 1st run of the report, the 3rd is based from the 2nd and so on.

In the above example the %utilized for sda is 111.41% this is a good indicator that our problem lies with processes writing to sda. While the test system in my example only has 1 disk this type of information is extremely helpful when the server has multiple disks as this can narrow down the search for which process is utilizing I/O.

Aside from %utilized there is a wealth of information in the output of iostat; items such as read and write requests per millisecond(rrqm/s & wrqm/s), reads and writes per second (r/s & w/s) and plenty more. In our example our program seems to be read and write heavy this information will be helpful when trying to identify the offending process.

### Finding the processes that are causing high I/O
iotop
```
 # iotop
 Total DISK READ: 8.00 M/s | Total DISK WRITE: 20.36 M/s
  TID PRIO USER DISK READ DISK WRITE SWAPIN IO> COMMAND
 15758 be/4 root 7.99 M/s 8.01 M/s 0.00 % 61.97 % bonnie++ -n 0 -u 0 -r 239 -s 478 -f -b -d /tmp
```
The simplest method of finding which process is utilizing storage the most is to use the command iotop. After looking at the statistics it is easy to identify bonnie++ as the process causing the most I/O utilization on this machine.

While iotop is a great command and easy to use, it is not installed on all (or the main) Linux distributions by default; and I personally prefer not to rely on commands that are not installed by default. A systems administrator may find themselves on a system where they simply cannot install the non-defualt packages until a scheduled time which may be far too late depending on the issue.

If iotop is not available the below steps will also allow you to narrow down the offending process/processes.
