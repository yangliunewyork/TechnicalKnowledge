__An interpreted language is a programming language for which most of its implementations execute instructions directly, without previously compiling a program into machine-language instructions. The interpreter executes the program directly, translating each statement into a sequence of one or more subroutines already compiled into machine code.__

The terms interpreted language and compiled language are not well defined because, in theory, any programming language can be either interpreted or compiled. In modern programming language implementation it is increasingly popular for a platform to provide both options.
Interpreted languages can also be contrasted with __machine languages__. Functionally, both execution and interpretation mean the same thing — fetching the next instruction/statement from the program and executing it. Although interpreted byte code is additionally identical to machine code in form and has an assembler representation, the term "interpreted" is practically reserved for "software processed" languages (by virtual machine or emulator) on top of the native (i.e. hardware) processor.

In principle, programs in many languages may be compiled or interpreted, emulated or executed natively, so this designation is applied solely based on common implementation practice, rather than representing an essential property of a language.

Interpreted languages can also be contrasted with machine languages. Functionally, both execution and interpretation mean the same thing — fetching the next instruction/statement from the program and executing it. Although interpreted byte code is additionally identical to machine code in form and has an assembler representation, the term "interpreted" is practically reserved for "software processed" languages (by virtual machine or emulator) on top of the native (i.e. hardware) processor.

In principle, programs in many languages may be compiled or interpreted, emulated or executed natively, so this designation is applied solely based on common implementation practice, rather than representing an essential property of a language.

### Advantages

Interpreting a language gives implementations some additional flexibility over compiled implementations. Features that are often easier to implement in interpreters than in compilers include:

* platform independence (Java's byte code, for example)
* reflection and reflective use of the evaluator (e.g. a first-order eval function)
* dynamic typing
* smaller executable program size (since implementations have flexibility to choose the instruction code)
* dynamic scoping

Furthermore, source code can be read and copied, giving users more freedom.

### Disadvantages

Disadvantages of interpreted languages are:

* Without static type-checking, which is usually performed by a compiler, programs can be less reliable, because type checking eliminates a class of programming errors.
* Interpreters can be susceptible to Code injection attacks.
* Slower execution compared to direct native machine code execution on the host CPU. A technique used to improve performance is just-in-time compilation which converts frequently executed sequences of interpreted instruction to host machine code. JIT is most often combined with compilation to byte-code as in Java.
* Source code can be read and copied (e.g. JavaScript in web pages), or more easily reverse engineered through reflection in applications where intellectual property has a commercial advantage. In some cases, obfuscation is used as a partial defense against this.




















