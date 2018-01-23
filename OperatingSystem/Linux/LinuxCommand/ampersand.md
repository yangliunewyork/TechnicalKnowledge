
#### What does ampersand mean at the end of a shell script line?

Example,

```
sh sys-snap.sh &
```

Why put & at the end of the line?

This is known as _job control_ under unix. The & informs the shell to put the command in the background. This means it continues to run the ```sys-snap.sh``` command but returns you to your shell to allows you to continue doing parallel commands.

You can see the list of jobs presently running with the jobs command. You can return to the command (bring to the 'foreground) with use of the fg command. Which pulls the command back to the state where you see no prompt and you have to issue ```Ctrl-C``` to kill the process. You can however suspend (pause) that process, issuing ```Ctrl-Z```. This will pause sys-snap.sh and return you to your prompt. You can then background it (as though you had issued it with the &) with the bg command, and it will resume running from it's paused state the ```Ctrl-Z``` had put it in.

Note that you can have more than one job at a time (as shown by jobs):

```
[1]-  Running          sys-snap.sh &
[2]+  Running          another-script.sh &
```

You can background and foreground them using their job number, %1 will be sys-snap.sh and %2 will be another-script.sh. If you use fg or bg without arguments it will action the command on the job marked by + in the jobs output above.

```
fg %1
```

will put sys-snap.sh back into the foreground, whilst leaving another-script.sh in the background.

You can issue the ```Ctrl-C``` sequence to running jobs without having to foreground them with the kill command, ```kill %1``` will send the equivalent of ```Ctrl-C``` to sys-snap.sh.

If you are using bash shell, the man bash command has a detailed section under the section headed 'JOB CONTROL' going into more detail.

As to the name of sys-snap.sh, under unix file names are arbitrary (with a couple of exceptions like dynamic loader files). There is no requirement for them to have specific file extentions to make them run as a shell script, invoke other commands such as perl or php etc. It is usually used to provide clarity, that in this instance, it is .sh a Shell Script using the Bourne Shell /bin/sh.

The functional part of sys-snap.sh (when you look at it's contents with something like the less command) is the Shebang. On the first line you will probably find one of:

```
#! /bin/sh
#! /bin/bash
#! /usr/local/bin/bash
```

or similar. In basic terms, a the command after the #! (such as /bin/sh) is ran and the contents of the rest of the script file is fed to it a line at a time. Note that the file must also be set executable with chmod so that you can run it as a command. If the permissions were not set, then the shebang has no effect, because you would either get the error:

```
bash: sys-snap.sh: command not found
```

or if you ran it by explicit path ./sys-snap.sh (. meaning the current working directory) you would get:

```
bash: ./sys-snap.sh: Permission denied
```

The other alternative is to leave it without execute permissions and explicitly ask /bin/sh to run it:

```
/bin/sh sys-snap.sh &
```
