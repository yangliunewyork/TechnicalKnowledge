In computer science, a __call stack__ is a stack data structure that stores information about the active subroutines of a computer program. This kind of stack is also known as an execution stack, program stack, control stack, run-time stack, or machine stack, and is often shortened to just "the stack". Although maintenance of the call stack is important for the proper functioning of most software, the details are normally hidden and automatic in high-level programming languages. Many computer instruction sets provide special instructions for manipulating stacks.

# Description

Since the call stack is organized as a stack, the caller pushes the return address onto the stack, and the called subroutine, when it finishes, pulls or pops the return address off the call stack and transfers control to that address. If a called subroutine calls on yet another subroutine, it will push another return address onto the call stack, and so on, with the information stacking up and unstacking as the program dictates. If the pushing consumes all of the space allocated for the call stack, an error called a __stack overflow__ occurs, generally causing the program to crash. Adding a subroutine's entry to the call stack is sometimes called "winding"; conversely, removing entries is "unwinding".

There is usually exactly one call stack associated with a running program (or more accurately, with each task or thread of a process), although additional stacks may be created for signal handling or cooperative multitasking (as with setcontext). Since there is only one in this important context, it can be referred to as the stack (implicitly, "of the task"); however, in the Forth programming language the data stack or parameter stack is accessed more explicitly than the call stack and is commonly referred to as the stack (see below).

In high-level programming languages, the specifics of the call stack are usually hidden from the programmer. They are given access only to a set of functions, and not the memory on the stack itself. This is an example of abstraction. Most assembly languages, on the other hand, require programmers to be involved with manipulating the stack. The actual details of the stack in a programming language depend upon the compiler, operating system, and the available instruction set.

# Structure

![alt](https://upload.wikimedia.org/wikipedia/commons/d/d3/Call_stack_layout.svg)

A call stack is composed of __stack frames__ (also called activation records or activation frames). These are machine dependent and ABI-dependent data structures containing subroutine state information. This data is sometimes referred to as CFI (Call Frame Information).[1] Each stack frame corresponds to a call to a subroutine which has not yet terminated with a return. For example, if a subroutine named DrawLine is currently running, having been called by a subroutine DrawSquare, the top part of the call stack might be laid out like in the picture on the right.

A diagram like this can be drawn in either direction as long as the placement of the top, and so direction of stack growth, is understood. Furthermore, independently of this, architectures differ as to whether call stacks grow towards higher addresses or towards lower addresses. The logic of the diagram is independent of the addressing choice.

The stack frame at the top of the stack is for the currently executing routine. The stack frame usually includes at least the following items (in push order):

* the arguments (parameter values) passed to the routine (if any);
* the return address back to the routine's caller (e.g. in the DrawLine stack frame, an address into DrawSquare's code); and
* space for the local variables of the routine (if any).

##### Stack and frame pointers

stack pointer. At function return, the stack pointer is instead restored to the frame pointer, the value of the stack pointer just before the function was called. Each stack frame contains a stack pointer to the top of the frame immediately below. The stack pointer is a mutable register shared between all invocations. A frame pointer of a given invocation of a function is a copy of the stack pointer as it was before the function was invoked.

The locations of all other fields in the frame can be defined relative either to the top of the frame, as negative offsets of the stack pointer, or relative to the top of the frame below, as positive offsets of the frame pointer. The location of the frame pointer itself must inherently be defined as a negative offset of the stack pointer.

### Stack Unwinding

Returning from the called function will pop the top frame off of the stack, perhaps leaving a return value. The more general act of popping one or more frames off the stack to resume execution elsewhere in the program is called stack unwinding and must be performed when non-local control structures are used, such as those used for exception handling. In this case, the stack frame of a function contains one or more entries specifying exception handlers. When an exception is thrown, the stack is unwound until a handler is found that is prepared to handle (catch) the type of the thrown exception.

When applying a continuation, the stack is (logically) unwound and then rewound with the stack of the continuation. This is not the only way to implement continuations; for example, using multiple, explicit stacks, application of a continuation can simply activate its stack and wind a value to be passed. The Scheme programming language allows arbitrary thunks to be executed in specified points on "unwinding" or "rewinding" of the control stack when a continuation is invoked.




