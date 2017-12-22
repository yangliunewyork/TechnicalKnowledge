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

A common approach in debugging is to isolate the first data item at which trouble appears. In the context here, that could be accomplished by printing out the entire tree each time you finish a call to insert(). Since you have a function in your source file to do this anyway—printtree()— you could simply add a call to this function right after your call to insert() in the source code:

```c
for (i = 1; i < argc; i++) {
  insert(&root,atoi(argv[i]));
  printtree(root);
}
```

However, this would be undesirable from various points of view. It would mean, for instance, that you would have to take time to edit your source file and recompile it. The former would be distracting and the latter could take some time if you had a large program. This, after all, is what you are trying to get away from by using a debugger.

Instead, it would be nice to do the same thing from within GDB. You can do this via GDB’s call command. For example, you could set a breakpoint at line 57, the end of insert(), and then do the following:

```
(gdb) commands 2
Type commands for when breakpoint 1 is hit, one per line.
End with a line saying just "end".
>printf "*********** current tree ***********"
>call printtree(root)
>end
```

### 3.2.4 Inspecting Dynamic Arrays

As discussed in Chapter 1, in GDB you can print an entire array, say declared as

```
int x[25];
```

by typing

```
(gdb) p x
```

But what if the array had been created dynamically, say as

```
int *x;
...
x = (int *) malloc(25*sizeof(int));
```

If you wanted to print out the array in GDB, you could not type

```
(gdb) p x
```

This would simply print the address of the array. Nor could you type

```
(gdb) p *x
```

That would print out only one element of the array, x[0]. You could still print out individual elements, as in the command p x[5], but you could not print the entire array simply using the print command on x.

#### 3.2.4.1 Solutions in GDB

In GDB you can solve this problem by creating an __artificial array__.

```
(gdb) p *x@25
$1 = {0, 0, 0, 12, 0 <repeats 21 times>}
```

As you can see, the general form is

```
*pointer@number_of_elements
```

GDB also allows casts to be used when appropriate, for example,

```
(gdb) p (int [25]) *x
$2 = {0, 0, 0, 12, 0 <repeats 21 times>}
```

Of course, you do have to keep in mind that GDB needs you to specify variables according to the same scope rules that C++ uses. For example:

```
(gdb) p *root
Cannot access memory at address 0x0
(gdb) p *node::root
$8 = {static root = 0x8049d08, val = 12, left = 0x8049d18, right = 0x8049d28}
```

We needed to specify root via its full name, node::root. 

GDB and DDD do not have built-in class browsers, but the GDB's _ptype_ command is handy to get a quick review of the structure of a class or struct, for example,

```
(gdb) ptype node
type = class node {
public:
static node *root;
int val;
node *left;
node *right;
node(int);
static void insert(int);
static void printtree(node*);
}
```

### 3.2.6 Monitoring Local Variables

In GDB, you can get a list of values of all the local variables in the current stack frame by invoking the ```info locals``` command.

## 3.3 Setting Variables from Within GDB/DDD/Eclipse

In some cases, it is useful to set the value of a variable using the debugger, in the midst of stepping through a program. This way you can quickly answer “what if” questions that arise when you are hypothesizing various sources for a bug. 

In GDB, you can set values very easily, for example,

```
(gdb) set x = 12
```
will change the current value of x to 12.

## 3.4 GDB’s Own Variables

