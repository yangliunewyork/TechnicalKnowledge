In computer science, an interpreter is a computer program that directly executes, i.e. performs, instructions written in a programming or scripting language, without previously compiling them into a machine language program. An interpreter generally uses one of the following strategies for program execution:

* parse the source code and perform its behavior directly;  
* translate source code into some efficient intermediate representation and immediately execute this;  
* explicitly execute stored precompiled code made by a compiler which is part of the interpreter system.  

While interpretation and compilation are the two main means by which programming languages are implemented, they are not mutually exclusive, as most interpreting systems also perform some translation work, just like compilers. The terms "interpreted language" or "compiled language" signify that the canonical implementation of that language is an interpreter or a compiler, respectively. A high level language is ideally an abstraction independent of particular implementations.

### Compilers versus interpreters

__Programs written in a high level language are either directly executed by some kind of interpreter or converted into machine code by a compiler (and assembler and linker) for the CPU to execute.__

While compilers (and assemblers) generally produce machine code directly executable by computer hardware, they can often (optionally) produce an intermediate form called object code. This is basically the same machine specific code but augmented with a symbol table with names and tags to make executable blocks (or modules) identifiable and relocatable. Compiled programs will typically use building blocks (functions) kept in a library of such object code modules. A linker is used to combine (pre-made) library files with the object file(s) of the application to form a single executable file. The object files that are used to generate an executable file are thus often produced at different times, and sometimes even by different languages (capable of generating the same object format).

A simple interpreter written in a low level language (e.g. assembly) may have similar machine code blocks implementing functions of the high level language stored, and executed when a function's entry in a look up table points to that code. However, an interpreter written in a high level language typically uses another approach, such as generating and then walking a parse tree, or by generating and executing intermediate software-defined instructions, or both.

Thus, both compilers and interpreters generally turn source code (text files) into tokens, both may (or may not) generate a parse tree, and both may generate immediate instructions (for a stack machine, quadruple code, or by other means). The basic difference is that a compiler system, including a (built in or separate) linker, generates a stand-alone machine code program, while an interpreter system instead performs the actions described by the high level program.

A compiler can thus make almost all the conversions from source code semantics to the machine level once and for all (i.e. until the program has to be changed) while an interpreter has to do some of this conversion work every time a statement or function is executed. However, in an efficient interpreter, much of the translation work (including analysis of types, and similar) is factored out and done only the first time a program, module, function, or even statement, is run, thus quite akin to how a compiler works. However, a compiled program still runs much faster, under most circumstances, in part because compilers are designed to optimize code, and may be given ample time for this. This is especially true for simpler high level languages without (many) dynamic data structures, checks, or type-checks.

In traditional compilation, the executable output of the linkers (.exe files or .dll files or a library, see picture) is typically relocatable when run under a general operating system, much like the object code modules are but with the difference that this relocation is done dynamically at run time, i.e. when the program is loaded for execution. On the other hand, compiled and linked programs for small embedded systems are typically statically allocated, often hard coded in a NOR flash memory, as there is often no secondary storage and no operating system in this sense.

### Development cycle

During the software development cycle, programmers make frequent changes to source code. When using a compiler, each time a change is made to the source code, they must wait for the compiler to translate the altered source files and link all of the binary code files together before the program can be executed. The larger the program, the longer the wait. By contrast, a programmer using an interpreter does a lot less waiting, as the interpreter usually just needs to translate the code being worked on to an intermediate representation (or not translate it at all), thus requiring much less time before the changes can be tested. Effects are evident upon saving the source code and reloading the program. Compiled code is generally less readily debugged as editing, compiling, and linking are sequential processes that have to be conducted in the proper sequence with a proper set of commands. For this reason, many compilers also have an executive aid, known as a Make file and program. The Make file lists compiler and linker command lines and program source code files, but might take a simple command line menu input (e.g. "Make 3") which selects the third group (set) of instructions then issues the commands to the compiler, and linker feeding the specified source code files.

### Distribution

A compiler converts source code into binary instruction for a specific processor's architecture, thus making it less portable. This conversion is made just once, on the developer's environment, and after that the same binary can be distributed to the user's machines where it can be executed without further translation. A cross compiler can generate binary code for the user machine even if it has a different processor than the machine where the code is compiled.

An interpreted program can be distributed as source code. It needs to be translated in each final machine, which takes more time but makes the program distribution independent of the machine's architecture. However, the portability of interpreted source code is dependent on the target machine actually having a suitable interpreter. If the interpreter needs to be supplied along with the source, the overall installation process is more complex than delivery of a monolithic executable since the interpreter itself is part of what need be installed.

The fact that interpreted code can easily be read and copied by humans can be of concern from the point of view of copyright. However, various systems of encryption and obfuscation exist. Delivery of intermediate code, such as bytecode, has a similar effect to obfuscation, but bytecode could be decoded with a decompiler or disassembler.

### Efficiency

__The main disadvantage of interpreters is that an interpreted program typically runs slower than if it had been compiled.__ The difference in speeds could be tiny or great; often an order of magnitude and sometimes more. It generally takes longer to run a program under an interpreter than to run the compiled code but it can take less time to interpret it than the total time required to compile and run it. This is especially important when prototyping and testing code when an edit-interpret-debug cycle can often be much shorter than an edit-compile-run-debug cycle.

__Interpreting code is slower than running the compiled code because the interpreter must analyze each statement in the program each time it is executed and then perform the desired action, whereas the compiled code just performs the action within a fixed context determined by the compilation.__ This run-time analysis is known as _"interpretive overhead"_. Access to variables is also slower in an interpreter because the mapping of identifiers to storage locations must be done repeatedly at run-time rather than at compile time.


















