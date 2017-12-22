### GDB

The most commonly used debugging tool among Unix programmers is GDB, the GNU Project Debugger developed by Richard Stallman, a prominent leader of the open source software movement, which played a key role in the development of Linux.

Most Linux sytems should have GDB preinstalled. If it is not, you must download the GCC compiler package.

## 1.3 The Principles of Debugging

### 1.3.1 The Essence of Debugging: The Principle of Confirmation

The following rule is the essence of debugging: 

> The Fundamental Principle of Confirmation : Fixing a buggy program is a process of confirming, one by one, that the many things you believe to be true about the code actually are true. When you find that one of your assumptions is not true, you have found a clue to the location (if not the exact nature) of a bug.

Another way of saying this is: Surprises are good!

When one of the things that you think is true about the program fails to confirm, you are surprised. But it’s a good surprise, because this discovery can lead you to the location of a bug.

### 1.3.2 Of What Value Is a Debugging Tool for the Principle of Confirmation?

The classic debugging technique is to simply add __trace code__ to the program to print out values of variables as the program executes, using printf() or cout statements, for example. You might ask, “Isn’t this enough? Why use a debugging tool like GDB, DDD, or Eclipse?”

First of all, this approach requires a constant cycle of strategically adding trace code, recompiling the program, running the program and analyzing the output of the trace code, removing the trace code after the bug is fixed, and repeating these steps for each new bug that is discovered. This is highly time consuming and fatigue making. Most importantly, these actions distract you from the real task and reduce your ability to focus on the reasoning pro- cess necessary to find the bug.

In contrast, with graphical debugging tools like DDD and Eclipse, all you have to do in order to examine the value of a variable is move the mouse pointer over an instance of that variable in the code display, and you are shown its current value. Why make yourself even wearier than necessary, for longer than necessary, during an all-night debugging session by doing this using printf() statements? Do yourself a favor and reduce the amount of time you have to spend and the tedium you need to endure by using a debugging tool.

You also get a lot more from a debugging tool than the ability to look at variables. In many situations, a debugger can tell you the approximate lo- cation of a bug. Suppose, for example, that your program bombs or crashes with a _segmentation fault_, that is, a memory access error. As you will see in our sample debugging session later in this chapter, GDB/DDD/Eclipse can im- mediately tell you the location of the seg fault, which is typically at or near the location of the bug.

Similarly, a debugger lets you set watchpoints that can tell you at what point during a run of the program the value of a certain variable reaches a suspect value or range. This information can be difficult to deduce by look- ing at the output of calls to printf().

### 1.3.3 Other Debugging Principles

##### Start small

At the beginning of the debugging process, you should run your program on easy, simple cases. This may not expose all of your bugs, but it is likely to uncover a few of them. If, for example, your code consists of a large loop, the easiest bugs to find are those that arise on the first or second iteration.

##### Use a top-down approach 

You probably know about using a top-down or modular approach to writing code: Your main program should not be too long, and it should consist mostly of calls to functions that do substantial work. If one of those functions is lengthy, you should consider breaking it up, in turn, into smaller modules. Not only should you write code in a top-down manner, you should also debug code from the top down. 

For example, suppose your program uses a function f(). When you step through the code using a debugging tool and encounter a call to f(), the debugger will give you a choice as to where the next pause in ex- ecution will occur—either at the first line within the function about to be called or at the statement following the function call. In many cases, the latter is the better initial choice: You perform the call and then in- spect the values of variables that depend on the results of the call in or- der to see whether or not the function worked correctly. If so, then you will have avoided the time-consuming and needless effort of stepping through the code inside the function, which was not misbehaving (in this case).

##### Use a debugging tool to determine the location of a segmentation fault

The very first step you take when a seg fault occurs should be to run your program within the debugger and reproduce the seg fault. The debugger will tell you the line of code at which the fault occurred. You can then get additional useful information by invoking the debugger’s backtrace facility, which displays the sequence of function calls leading to the invocation of the function in which the fault occurred.

In some cases it may be difficult to reproduce the seg fault, but if you have a core file, you can still do a backtrace to determine the situation that produced the seg fault. 

##### Determine the location of an infinite loop by issuing an interrupt

If you suspect your program has an infinite loop, enter the debugger and run your program again, letting it execute long enough to enter the loop. Then use the debugger’s interrupt command to suspend the pro- gram, and do a backtrace to see what point of the loop body has been reached and how the program got there. (The program has not been killed; you can resume execution if you wish.)

##### Use binary search

Suppose you know that the value stored in a certain variable goes bad sometime dur- ing the first 1,000 iterations of a loop. One way that might help you track down the iteration where the value first goes bad is to use a watch- point, an advanced technique that we will discuss in Section 1.5.3. An- other approach is to use binary search, in this case in time rather than in space. You’d first check the variable’s value at the 500th iteration; if it is still all right at that point, you’d next check the value at the 750th iteration, and so on.

As another example, suppose one of the source files in your pro- gram will not even compile. The line of code cited in the compiler mes- sage generated by a syntax error is sometimes far from the actual loca- tion of the error, and so you may have trouble determining that loca- tion. Binary search can help here: You remove (or comment out) one half of the code in the compilation unit, recompile the remaining code, and see if the error message persists. If it does, then the error is in that second half; if the message does not appear, then the error is in the half that you deleted. Once you determine which half of the code contains the bug, you further confine the bug to half of that portion, and keep going until you locate the problem. Of course, you should make a copy of the original code before starting this process or, better yet, use your text editor’s undo feature.

### 1.4.2 Compromises

Since version 6.1, GDB has offered a compromise between text-based and graphical user interaction in the form of a mode named __TUI (Terminal User Interface)__. In this mode, GDB splits the terminal screen into analogs of DDD’s Source Text window and Console; you can follow the progress of your program’s execution in the former while issuing GDB commands in the latter. Alternatively, you can use another program, CGDB, which offers similar functionality.

#### 1.4.2.1 GDB in TUI Mode

To run GDB in TUI mode, you can either specify the option -tui on the command line when invoking GDB or type CTRL-X-A from within GDB while in non-TUI mode. The latter command also toggles you out of TUI mode if you are currently in it. In TUI mode, the GDB window is divided into two subwindows—one for GDB commands and one for viewing source code. 











