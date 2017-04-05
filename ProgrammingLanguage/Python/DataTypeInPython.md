## Strong and weak typing
In computer programming, programming languages are often colloquially classified as strongly typed or weakly typed (loosely typed). These terms do not have a precise definition, but in general, a strongly typed language is more likely to generate an error or refuse to compile if the argument passed to a function does not closely match the expected type. On the other hand, a weakly typed language may produce unpredictable results or may perform implicit type conversion.

### Definitions of "strong" or "weak"
A number of different language design decisions have been referred to as evidence of "strong" or "weak" typing. In fact, many of these are more accurately understood as the presence or absence of type safety, memory safety, static type-checking, or dynamic type-checking.

In a weakly typed language, the type of a value depends on how it is used. For example if I can pass a string to the addition operator and it will AutoMagically be interpreted as a number or cause an error if the contents of the string cannot be translated into a number. Similarly, I can concatenate strings and numbers or use strings as booleans, etc.

In a strongly typed language, a value has a type and that type cannot change. What you can do to a value depends on the type of the value.

The advantage of a strongly typed language is that you are forced to make the behaviour of your program explicit. If you want to add a number and a string your code must translate the string into a number to be used as an operand of the addition operator. This makes code easier to understand because there is no (or less) hidden behaviour. However, it also makes your code more verbose.
The advantage of a weakly typed language is that you need to write less code. However, that code is harder to understand because a lot of its behaviour is hidden in implicit type conversions.

Strong vs. weak typing is comparable to static vs. dynamic typing. __In a statically typed language, type checking is performed at compile time; in a dyamically typed language type checking is performed at run time. In practice, weakly typed languages are usually dynamically typed.__

All languages can be placed somewhere in the 2D "typing" space whose axes are strong <-> weak and static <-> dynamic.

## Programming language is statically typed of dynamically typed ?
A language is statically typed if the type of a variable is known at compile time. For some languages this means that you as the programmer must specify what type each variable is (e.g.: Java, C, C++); other languages offer some form of type inference, the capability of the type system to deduce the type of a variable (e.g.: OCaml, Haskell, Scala)

The main advantage here is that all kinds of checking can be done by the compiler, and therefore a lot of trivial bugs are caught at a very early stage.

A language is dynamically typed if the type is associated with run-time values, and not named variables/fields/etc. This means that you as a programmer can write a little quicker because you do not have to specify types every time (unless using a statically-typed language with type inference). Example: Perl, Ruby, Python

Most scripting languages have this feature as there is no compiler to do static type-checking anyway, but you may find yourself searching for a bug that is due to the interpreter misinterpreting the type of a variable. Luckily, scripts tend to be small so bugs have not so many places to hide.

Most dynamically typed languages do allow you to provide type information, but do not require it. One language that is currently being developed (Rascal) takes a hybrid approach allowing dynamic typing within functions but enforcing static typing for the function signature.


## How Python's Datatypes Compare to Other Programming Languages

#### statically typed language vs dynamically typed language

* statically typed language ： A language in which types are fixed at compile time. Most statically typed languages enforce this by requiring you to declare all variables with their datatypes before using them. Java and C are statically typed languages.

* dynamically typed language : A language in which types are discovered at execution time; the opposite of statically typed. VBScript and Python are dynamically typed, because they figure out what type a variable is when you first assign it a value.

#### strongly typed language weakly typed language

* strongly typed language : A language in which types are always enforced. Java and Python are strongly typed. If you have an integer, you can't treat it like a string without explicitly converting it.
* weakly typed language : A language in which types may be ignored; the opposite of strongly typed. VBScript is weakly typed. In VBScript, you can concatenate the string '12' and the integer 3 to get the string '123', then treat that as the integer 123, all without any explicit conversion.


__So Python is both dynamically typed (because it doesn't use explicit datatype declarations) and strongly typed (because once a variable has a datatype, it actually matters).__
