### 3.2.1 Inspection in GDB

##### First improvement: Print the struct in its entirety

It would be quite laborious to keep typing those three print commands each time we reached a breakpoint. Here is how we could do the same thing with just one print command:

```
(gdb) p *tmp
$4 = {val = 12, left = 0x8049698, right = 0x0}
```

Since tmp points to the struct, *tmp then is the struct itself, and thus GDB shows us the entire contents.

##### Second improvement: Use the GDB display command

Typing p *tmp above saves time and effort. Each time you hit a breakpoint, you would need to type only one GDB command, not three. But if you know you will type this each time you hit a breakpoint, you can save even more time and effort using GDB’s _display_ command, abbreviated _disp_. This command tells GDB to automatically print the specified item each time there is a pause in execution (due to a breakpoint, the next or step commands, and so on):

```
(gdb) disp *tmp
1: *tmp = {val = 12, left = 0x8049698, right = 0x0}
(gdb) c
Continuing.
Breakpoint 1, insert (btp=0x804967c, x=5) at bintree.c:37
37 if (x < tmp->val) {
1: *tmp = {val = 8, left = 0x0, right = 0x0}
```

As seen here, GDB automatically printed *tmp after hitting the break- point, since you had issued the display command. Of course, a variable in the display list will only be displayed during times in which it is in scope.

##### Third improvement: Use the GDB commands command

Suppose you wish to look at the values in the child nodes when you are at a given node. Recalling GDB’s commands command from Chapter 1, you could do something like this:

```
(gdb) b 37
Breakpoint 1 at 0x8048403: file bintree.c, line 37.
(gdb) commands 1
Type commands for when breakpoint 1 is hit, one per line.
End with a line saying just "end".
>p tmp->val
>if (tmp->left != 0)
>p tmp->left->val
>else
>printf "%s\n", "none"
>end
>if (tmp->right != 0)
>p tmp->right->val
>else
>printf "%s\n", "none"
>end
>end
```

##### Fourth improvement: Use the GDB call command

