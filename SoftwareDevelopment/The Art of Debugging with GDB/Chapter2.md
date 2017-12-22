A symbolic debugger such as GDB can run your program, just like you can. However, with the magic of including debugging symbols in the executable, the debugger gives the illusion of executing the program line by line of source code, instead of instruction by instruction of compiled machine code. This seemingly humble fact is precisely what makes a symbolic debugger so useful in debug- ging programs.

If all the debugger could do is run a program, it wouldn’t be of much use to us. We could certainly do the same thing, and more efficiently, to boot. The usefulness of the debugger lies in the fact that we can instruct it to pause execution of the program. Once paused, the debugger gives us a chance to inspect variables, trace the execution path, and much more.

## 2.1 Mechanisms for Pause

There are three ways to instruct GDB to pause execution of your program:

* A __breakpoint__ tells GDB to pause execution at a particular location within the program.   
* A __watchpoint__ tells GDB to pause execution when a particular memory location (or an expression involving one or more locations) changes value.   
* A __catchpoint__ tells GDB to pause execution when a particular event occurs.  

Confusingly (at first), all three mechanisms are collectively termed break-points in the GDB documentation. This may be because they share many of the same attributes and commands. For example, you’ll learn about GDB’s _delete_ command which, as the help blurb says, deletes a breakpoint:

```
(gdb) help delete
Delete some breakpoints or auto-display expressions.
Arguments are breakpoint numbers with spaces in between.
To delete all breakpoints, give no argument.
```

However, the experienced GDB user knows that the help blurb really means the delete command deletes breakpoints, watchpoints, and catchpoints!

## 2.2 Overview of Breakpoints

A breakpoint is like a tripwire within a program: You set a breakpoint at a particular “place” within your program, and when execution reaches that point, the debugger will pause the program’s execution (and will, in the case of a text-based debugger such as GDB, give you a command prompt).

GDB is very flexible about the meaning of “place”; it could mean things as varied as a line of source code, an address of code, a line number within a source file, or the entry into a function.

## 2.3 Keeping Track of Breakpoints

Each breakpoint (which includes breakpoints, watchpoints, and catchpoints) you create is assigned a unique integer identifier, starting at 1. This identi- fier is used to perform various operations on the breakpoint. The debugger also includes a means of listing all your breakpoints and their properties.

## 2.4 Setting Breakpoints

Debugging tools typically offer a variety of mechanisms with which to set breakpoints.

You're learned that GDB gives the illusion of running a program line by line of source code. You抳e also learned that in order to do anything really use- ful with GDB you need to instruct it where to pause execution so you can perform debugging activitites with GDB抯 command-line prompt. In this section, you’ll learn how to set breakpoints, which tell GDB where to stop within your source code.

There are many different ways to specify a breakpoint in GDB; here are some of the most common methods:

##### break function

Set a breakpoint at the entry (first executable line) of the function function().
You saw an example of this in Section 2.3.1; the command

```
(gdb) break main
```
sets a breakpoint at the entry of main().

##### break line_number

Set a breakpoint at line line_number of the currently active source code file. For multi-file programs, this is either the file whose contents you last looked at using the list command or the file containing main().

```
(gdb) break 35
```

which set a breakpoint at line 35 in file bed.c.

##### break filename:line_number

Set a breakpoint at line line_number of the source code file filename. If filename isn’t in your current working directory, you can give a relative or full pathname to help GDB find the file, for example: 

```
(gdb) break source/bed.c:35
```

##### break filename:function 

Set a breakpoint at the entry of function function() within the file filename. Using this form may be required for overloaded functions or for pro- grams that use identically named static functions, for example: 

```
(gdb) break bed.c:parseArguments
```

As we’ll see, when a breakpoint is set, it stays in effect until you delete it, disable it, or quit GDB. However, a __temporary breakpoint__ is a breakpoint that is automatically deleted after the first time it’s reached. A temporary breakpoint is set with the _tbreak_ command, which takes the same type of arguments that break takes. For example, tbreak foo.c:10 sets a temporary breakpoint at line 10 of file foo.c.

A comment needs to be made about functions with the same name. C++ allows you to overload functions (define functions with the same name). Even C allows you to do this if you use the static qualifier to declare the functions with file scope. Using _break_ function will set a breakpoint at all functions with the same name. If you want to set a breakpoint at a particular instance of the function, you need to be unambiguous, such as by giving the line number within a source code file in your break command.

> ##### Other break Arguments
> There are other, perhaps less used, arguments you can use with the break command.
> * Withbreak +offset or break -offset, you can set a breakpoint offset lines ahead or behind the executing line of source code
in the currently selected stack frame.
> * Theformbreak *address can be used to set a breakpoint at a virtual memory address. This would be necessary for sections of a program that don’t have debugging information, like when the source code is unavailable or for shared libraries, for instance.

The location at which GDB actually sets a breakpoint may be different from where you requested it to be placed. This can be somewhat disconcerting for people new to GDB, so let’s look at a short example that demon- strates this quirk. Consider the following short program, test1.c:

```
int main(void)
{
 int i;
 i = 3;

 return 0;
}
```

Compile this program without optimization and try setting a breakpoint at the entry of main(). You would think that the breakpoint would be placed at the top of the function—either line 1, line 2, or line 3. Those would be good guesses for the location of the breakpoint, but they’re wrong. The breakpoint is actually set at line 4.

```
$ gcc -g3 -Wall -Wextra -o test1 test1.c
$ gdb test1
(gdb) break main
Breakpoint 1 at 0x6: file test1.c, line 4.
```

Line 4 is hardly the first line of main(), so what happened? As you may have guessed, one issue is that that line is executable. _Recall that GDB actually works with machine language instructions, but with the magic of an enhanced symbol table, GDB gives the illusion of working with source code lines. Normally, this fact isn’t terribly important, but this is a situation in which it becomes important. Actually, declaring i does generate machine code, but it is not code that GDB finds useful for our debugging purposes._ Therefore, when you told GDB to break at the start of main(), it set a breakpoint at line 4.

The problem may become worse when you compile the program with optimizations. Let’s take a look. Recompile the program with optimization turned on:

```
$ gcc -O9 -g3 -Wall -Wextra -o test1 test1.c
$ gdb test1
(gdb) break main
Breakpoint 1 at 0x3: file test1.c, line 6.
```

We asked to put a breakpoint at the start of main(), but GDB placed one on the last line of main(). Now what happened? The answer is the same as be- fore, but GCC took a more active role. __With optimizations turned on, GCC noticed that although i was assigned a value, it was never used. So in an effort to generate more efficient code, GCC simply optimized lines 3 and 4 out of existence. GCC never generated machine instructions for these lines. Therefore, the first line of source code that generated machine instructions happens to be the last line of main(). This is one of the reasons you should never optimize code until you’re finished debugging it.__

The upshot of all this is that if you find that setting a breakpoint doesn’t produce a breakpoint exactly where you’d expect it to, you now know why. Don’t be surprised. On a related matter, we’d like to mention what happens when more than one breakpoint lives at the same line of source code. When GDB breaks at a source code line with more than one breakpoint, it will only break there once. In other words, after it hits that line of code, if you resume execution, the other breakpoints which happen to be on the same line will be ignored. In fact, GDB keeps track of which breakpoint “triggered” the program exe- cution to stop. On a line of code with multiple breakpoints, the breakpoint that triggers the break will be the breakpoint with the lowest identifier.

> Catchpoints : C++ programmers will want to check out the catch command, which sets catchpoints. Catchpoints are similar to breakpoints, but can be triggered by different things like thrown exceptions, caught exceptions, signals, calls to fork(), loading and unloading of libraries, and many other events.

## 2.6 Persistence of Breakpoints

We said “much later on” above to make the point that you should not exit GDB during your debugging session. For example, when you find and fix one bug, but other bugs remain, you should not exit and then re-enter GDB to use the new version of your program. That would be unnecessary trouble, and more importantly, you would have to re-enter your breakpoints. If you do not exit GDB when you change and recompile your code, the next time you issue GDB’s run command, GDB will sense that your code has changed and automatically reload the new version. However, note that your breakpoints may “move.” 

Eventually, your current debugging session will end, say, because it’s time to eat, sleep, or relax. If you don’t normally keep your computer run- ning continuously, you will need to exit your debugger. Is there any way to save your breakpoints? For GDB and DDD, the answer is yes, to some extent. You can place your breakpoints in a .gdbinit startup file in the directory where you have your source code (or the directory from which you invoke GDB).

## 2.7 Deleting and Disabling Breakpoints

During the course of a debugging session, you may find that a breakpoint has outlived its usefulness. If you’re sure the breakpoint will no longer be needed, you can delete it. It may also be the case that you think the breakpoint can be of use to you later on during the debugging session. Perhaps you’d rather not delete the breakpoint, but instead, cook things up so that for the time being the debugger will skip breaks at that point in your code. This is called disabling a breakpoint. You can re-enable it later if/when it becomes useful again.

This section covers deleting and disabling breakpoints. Everything men- tioned applies to watchpoints as well.

### 2.7.1 Deleting Breakpoints in GDB

If the breakpoint in question is truly no longer needed (perhaps that particular bug was fixed!) then you can delete that breakpoint. There are two commands that are used to delete breakpoints in GDB. The _delete_ command is used to delete breakpoints based on their identifier, and the _clear_ command is used to delete breakpoints using the same syntax you use to create breakpoints.

##### delete breakpoint_list 

Deletes breakpoints using their numeric identifiers. It can be a single number, such as delete 2 which deletes the second breakpoint, or a list of numbers, like delete 2 4 which deletes the second and fourth breakpoints.

##### delete 

Deletes all breakpoints. GDB will ask you to confirm this operation un- less you issue the set confirm off command, which can also be placed in your .gdbinit startup file.

##### clear 

Clears a breakpoint at the next instruction that GDB will execute. This method is useful when you want to delete the breakpoint that GDB has just reached.

```
clear function
clear filename:function
clear line_number
clear filename:line_number
```

These clear a breakpoint based on its location and work analogously to the break counterparts.

### 2.7.2 Disabling Breakpoints in GDB

Each breakpoint can be enabled or disabled. GDB will pause the program’s execution only when it hits an enabled breakpoint; it ignores disabled break- points. By default, breakpoints start life as being enabled.

Why would you want to disable breakpoints? During the course of a de-bugging session, you may collect a large number of breakpoints. For loop structures or functions that repeat often, it can be extremely inconvenient for GDB to break so often. If you want to keep the breakpoints for later use but don’t want GDB to stop execution for the time being, you can disable them and enable them later.

You disable a breakpoint with the disable breakpoint-list command and enable a breakpoint with the enable breakpoint-list command, where breakpoint-list is a space-separated list of one or more breakpoint identifiers. For example,

```
(gdb) disable 3
```

will disable the third breakpoint. Similarly,

```
(gdb) enable 1 5
```

will enable the first and fifth breakpoints.

Issuing the _disable_ command without any arguments will disable all existing breakpoints. Similarly, the _enable_ command with no arguments will enable all existing breakpoints.

There’s also an enable once command that will cause a breakpoint to become disabled after the next time it causes GDB to pause execution. The syntax is:

```
enable once breakpoint-list
```

For example, enable once 3 will cause breakpoint 3 to become disabled the next time it causes GDB to stop execution of your program. It's very similar to the tbreak command, but it disables rather than deletes when the breakpoint is encountered.

## 2.8 More on Viewing Breakpoint Attributes

### 2.8.1 GDB

As you saw in Section 2.3.1, each breakpoint you create is assigned a unique integer identifier. The first breakpoint you set is assigned to ‘1’, and each new breakpoint thereafter is assigned an integer one greater than the pre- viously assigned identifier. Each breakpoint also has a number of attributes that control and fine-tune its behavior. Using the unique identifiers, you can adjust the attributes of each breakpoint individually.

You can use the info breakpoints command (abbreviated as i b) to obtain a listing of all the breakpoints you抳e set, along with their attributes. The output of info breakpoints will look more or less like this:

```
(gdb) info breakpoints
Num Type Disp Enb Address What
1 breakpoint keep y 0x08048404 in main at int_swap.c:9
breakpoint already hit 1 time
2 breakpoint keep n 0x08048447 in main at int_swap.c:14
3 breakpoint keep y 0x08048460 in swap at int_swap.c:20
breakpoint already hit 1 time
4 hw watchpoint keep y counter
```

Let’s look at this output from info breakpoints in detail:

__Identifier (Num)__: The breakpoint’s unique identifier.   
__Type (Type)__: This field tells you whether the breakpoint is a breakpoint, watchpoint, or catchpoint.    
__Disposition (Disp)__: Each breakpoint has a disposition, which indicates what will happen to the breakpoint after the next time it causes GDB to pause the program’s execution. There are three possible dispositions: 
  * _keep_ The breakpoint will be unchanged after the next time it’s reached. This is the default disposition of newly created breakpoints. 
  * _del_ The breakpoint will be deleted after the next time it’s reached. This disposition is assigned to any breakpoint you create with the tbreak command. 
  * _dis_ The breakpoint will be disabled the next time it’s reached. This is set using the enable once command.   
__Enable Status (Enb)__: This field tells you whether the breakpoint is currently enabled or disabled.    
__Address (Address)__: This is the location in memory where the breakpoint is set. This would mainly be of use to assembly language programmers or people trying to debug an executable that wasn’t compiled with an augmented symbol table. Location (What): As discussed, each breakpoint lives at a particular line within your source code. The What field shows the line number and filename of the location of the breakpoint. For watchpoints, this field shows which variable is being watched. This makes sense because a variable is actually a memory address with a name, and a memory address is a location.  

As you can see, in addition to listing all the breakpoints and their at- tributes, the i b command also tells you how many times a particular break- point has caused GDB to halt execution of the program so far. If, for instance, you have a breakpoint within a loop, it will tell you at a glance how many iterations of the loop have been executed so far, which can be very useful.

## 2.9 Resuming Execution

Knowing how to instruct the debugger where or when to pause execution of your program is important, but knowing how to instruct it to resume ex- ecution is just as important. After all, inspecting your variables may not be enough. Sometimes you need to know how the variables’ values interact with the rest of the code.

Recall the Principle of Confirmation in Chapter 1: You continue to con- firm that certain variables have the values you think they do, until you en- counter one that fails to match your expectation. That failure will then be a clue as to the likely location of your bug. But typically the failure will not occur until you have paused and resumed execution at a number of break- points (or multiple times at the same breakpoint). Thus, resuming execution at a breakpoint is just as important as setting the breakpoint itself, which is why a debugging tool will typically have a fairly rich set of methods for resuming execution.

There are three classes of methods for resuming execution. The first in- volves “single stepping” through your program with _step_ and _next_, executing only the next line of code and then pausing again. The second consists of using _continue_, which makes GDB unconditionally resume execution of the program until it hits another breakpoint or the program finishes. The last class of methods involves conditions: resuming with the _finish_ or _until_ commands. In this case, GDB will resume execution and the program will run until either some predetermined condition is met (e.g., the end of a function is reached), another breakpoint is reached, or the program finishes.

### 2.9.1 In GDB

### 2.9.1.1 Single-stepping with step and next

Once GDB stops at a breakpoint, the _next_ (abbreviated as n) and _step_ (abbreviated as s) commands are used to single-step through your code. After a breakpoint is triggered and GDB pauses, you can use next and step to execute just the very next line of code. After the line is executed, GDB will again pause and give a command prompt.

We see that both next and step execute the next line of code. So the big question is: “How are these commands different?” They both appear to execute the next line of code. The difference between these two commands is how they handle function calls: _next_ will execute the function, without pausing within it, and then pause at the first statement following the call. _step_, on the other hand, will pause at the first statement within the function.

This is the main difference between the two commands. _next_ considers the function call to be a single line of code, and executes the entire function in one operation, which is called stepping over the function

__The difference between stepping into a function (what _step_ does) and stepping over a function (what _next_ does) is very important.__

Whether you use _next_ or _step_ is really a matter of what you are trying to do. If you’re in a part of the code with no function calls, it doesn’t matter which one you use. In this case, the two commands are completely equivalent. However, if you’re debugging a program and find yourself about to step into a function that you know is free of bugs (or irrelevent to the bug you’re trying to track down), clearly you’d want to use next to save yourself from stepping through each line of a function you’re not interested in.

One of the general debugging principles laid out in Chapter 1 was to take a top-down approach to debugging. If you’re stepping through source code and encounter a function call, it is typically better to use _next_ instead of _step_. Immediately after using next in this situation, you would check if the result of the call was correct. If so, the bug is likely not in the function, meaning the use of next instead of step saved you the time and effort of stepping through every line of the function. On the other hand, if the result of the function is incorrect, you can re-run the program with a temporary break-point set at the function call, and then use _step_ to enter the function.

Both the _next_ and _step_ commands take an optional numerical argument which indicates the number of extra lines to next or step through. In other words, ```next 3``` is the same as typing next three times in a row (or typing next once followed by hitting the ENTER key twice).

#### 2.9.1.2 Resuming Program Execution with continue

The second method of resuming execution is with the continue command, abbreviated as c. In contrast to _step_ and _next_, which execute only one line of code, this command causes GDB to resume execution of your program until a breakpoint is triggered or the program terminates.

The continue command can take an optional integer argument, n. This number tells GDB to ignore the next n breakpoints. For instance, ```continue 3``` tells GDB to resume program execution and ignore the next 3 breakpoints.

#### 2.9.1.3 Resuming Program Execution with finish

Once a breakpoint is triggered, the _next_ and _step_ commands are used to execute the program line by line. Sometimes this can be a painful endeavor. For example, suppose GDB reached a breakpoint within a function. You’ve inspected a few variables and have gathered all the information you had intended to get. At this point, you’re not interested in single-stepping through the remainder of the function. You’d like to return back to the calling function where GDB was before you stepped into the called function. However, setting an extraneous breakpoint and using _continue_ seems wasteful if all you want to do is skip the remainder of the function. That’s where _finish_ comes in.

The _finish_ command (abbreviated fin) instructs GDB to resume execution until just after the current stack frame finishes. In English, this means that if you’re in a function other than main(), the finish command will cause GDB to resume execution until just after the function returns.

If you’re within a recursive function, finish will only take you one level up in the recursion. This is because each call is considered a function call in its own right, since each one has its own stack frame. If you want to get completely out of a recursive function when the recursive level is high, a temporary breakpoint along with _continue_, or using the _until_ command, is more appropriate.

#### 2.9.1.4 Resuming Program Execution with until

Recall that the _finish_ command completes execution of the current function without further pauses within the function (except at any intervening breakpoints). Similarly, the _until_ command (abbreviated simply as u) is typically used to complete an executing loop, without further pauses within the loop, except at any intervening breakpoints within the loop.

Consider the follow- ing code snippet.

```
...previous code...
int i = 9999;
while (i--) {
printf("i is %d\n", i);
... lots of code ...
}
...future code...
```

Suppose GDB is stopped at a breakpoint at the while statement, you’ve inspected a few variables, and now you’d like to leave the loop to debug “future code.”

The problem is that i is so large, it would take forever to use next to complete the loop. You can’t use finish because that command will pass right over “future code” and take us out of the function. You could set a temporary breakpoint at the future code and use _continue_; however, this is exactly the situation that _until_ was meant to address.

Using until will execute the rest of the loop, leaving GDB paused at the first line of code following the loop.

In fact, what _until_ really does is execute until it reaches a machine instruction that has a higher memory address than the current one, rather than until it reaches a larger line number in the source code. In practice, this sort of thing may not arise too often, but it’s nice to un- derstand it when it does occur. Additionally, by looking at some of GDB’s odd behavior, you can glean information about how compilers turn source code into machine instructions—not a bad bit of knowledge to have.

## 2.10 Conditional Breakpoints
