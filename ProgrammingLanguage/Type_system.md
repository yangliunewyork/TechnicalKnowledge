In programming languages, a type system is a set of rules that assigns a property called type to the various constructs of a computer program, such as variables, expressions, functions or modules. These types formalize and enforce the otherwise implicit categories the programmer uses for data structures and components (e.g. "string", "array of float", "function returning boolean"). _The main purpose of a type system is to reduce possibilities for bugs in computer programs by defining interfaces between different parts of a computer program, and then checking that the parts have been connected in a consistent way. This checking can happen statically (at __compile time__), dynamically (at __run time__), or as a combination of static and dynamic checking._ Type systems have other purposes as well, such as expressing business rules, enabling certain compiler optimizations, allowing for multiple dispatch, providing a form of documentation, etc.

A type system associates a type with each computed value and, by examining the flow of these values, attempts to ensure or prove that no type errors can occur. The given type system in question determines exactly what constitutes a type error, but in general the aim is to prevent operations expecting a certain kind of value from being used with values for which that operation does not make sense (logic errors); memory errors will also be prevented. Type systems are often specified as part of programming languages, and built into the interpreters and compilers for them; although the type system of a language can be extended by optional tools that perform added kinds of checks using the language's original type syntax and grammar.

### Fundamentals

Formally, type theory studies type systems. A programming language must have occurrence to type check using the type system whether at compile time or runtime, manually annotated or automatically inferred. As Mark Manasse concisely put it:

The fundamental problem addressed by a type theory is to ensure that programs have meaning. The fundamental problem caused by a type theory is that meaningful programs may not have meanings ascribed to them. The quest for richer type systems results from this tension.

__Assigning a data type, termed typing, gives meaning to a sequence of bits such as a value in memory or some object such as a variable. The hardware of a general purpose computer is unable to discriminate between for example a memory address and an instruction code, or between a character, an integer, or a floating-point number, because it makes no intrinsic distinction between any of the possible values that a sequence of bits might mean. Associating a sequence of bits with a type conveys that meaning to the programmable hardware to form a symbolic system composed of that hardware and some program.__

A program associates each value with at least one specific type, but it also can occur that one value is associated with many subtypes. Other entities, such as objects, modules, communication channels, dependencies can become associated with a type. Even a type can become associated with a type. An implementation of a type system could in theory associate identifications called data type (a type of a value), class (a type of an object), and kind (a type of a type, or metatype). These are the abstractions that typing can go through, on a hierarchy of levels contained in a system.

When a programming language evolves a more elaborate type system, it gains a more finely grained rule set than basic type checking, but this comes at a price when the type inferences (and other properties) become undecidable, and when more attention must be paid by the programmer to annotate code or to consider computer-related operations and functioning. It is challenging to find a sufficiently expressive type system that satisfies all programming practices in a type safe manner.

__The more type restrictions that are imposed by the compiler, the more strongly typed a programming language is. Strongly typed languages often require the programmer to make explicit conversions in contexts where an implicit conversion would cause no harm.__ Pascal's type system has been described as "too strong" because, for example, the size of an array or string is part of its type, making some programming tasks difficult. Haskell is also strongly typed but its types are automatically inferred so that explicit conversions are often (but not always) unnecessary.

A programming language compiler can also implement a dependent type or an effect system, which enables even more program specifications to be verified by a type checker. Beyond simple value-type pairs, a virtual "region" of code is associated with an "effect" component describing what is being done with what, and enabling for example to "throw" an error report. Thus the symbolic system may be a type and effect system, which endows it with more safety checking than type checking alone.

Whether automated by the compiler or specified by a programmer, a type system makes program behavior illegal if outside the type-system rules. Advantages provided by programmer-specified type systems include:

* Abstraction (or modularity) – Types enable programmers to think at a higher level than the bit or byte, not bothering with low-level implementation. For example, programmers can begin to think of a string as a set of character values instead of as a mere array of bytes. Higher still, types enable programmers to think about and express interfaces between two of any-sized subsystems. This enables more levels of localization so that the definitions required for interoperability of the subsystems remain consistent when those two subsystems communicate.  
* Documentation – In more expressive type systems, types can serve as a form of documentation clarifying the intent of the programmer. For example, if a programmer declares a function as returning a timestamp type, this documents the function when the timestamp type can be explicitly declared deeper in the code to be an integer type.  

### Type checking

The process of verifying and enforcing the constraints of types—type checking—may occur either at compile-time (a static check) or at run-time. If a language specification requires its typing rules strongly (i.e., more or less allowing only those automatic type conversions that do not lose information), one can refer to the process as strongly typed, if not, as weakly typed. The terms are not usually used in a strict sense.

#### Static type checking

Static type checking is the process of verifying the type safety of a program based on analysis of a program's text (source code). If a program passes a static type checker, then the program is guaranteed to satisfy some set of type safety properties for all possible inputs.

Static type checking can be considered a limited form of program verification (see type safety), and in a type-safe language, can be considered also an optimization. If a compiler can prove that a program is well-typed, then it does not need to emit dynamic safety checks, allowing the resulting compiled binary to run faster and to be smaller.

Static type checking for Turing-complete languages is inherently conservative. That is, if a type system is both sound (meaning that it rejects all incorrect programs) and decidable (meaning that it is possible to write an algorithm that determines whether a program is well-typed), then it will always be possible to define an unsound program that is poorly-typed , thereby defeating the type system, but which does not encounter runtime errors: "... any sound, decidable type system must be incomplete" —D. Remy。


A number of useful and common programming language features cannot be checked statically, such as downcasting. Thus, many languages will have both static and dynamic type checking; the static type checker verifies what it can, and dynamic checks verify the rest.

#### Dynamic type checking and runtime type information

Dynamic type checking is the process of verifying the type safety of a program at runtime. Implementations of dynamically type-checked languages generally associate each runtime object with a type tag (i.e., a reference to a type) containing its type information. This runtime type information (RTTI) can also be used to implement dynamic dispatch, late binding, downcasting, reflection, and similar features.

Most type-safe languages include some form of dynamic type checking, even if they also have a static type checker.[citation needed] The reason for this is that many useful features or properties are difficult or impossible to verify statically. For example, suppose that a program defines two types, A and B, where B is a subtype of A. If the program tries to convert a value of type A to type B, which is known as downcasting, then the operation is legal only if the value being converted is actually a value of type B. Thus, a dynamic check is needed to verify that the operation is safe. This requirement is one of the criticisms of downcasting.

By definition, dynamic type checking may cause a program to fail at runtime. In some programming languages, it is possible to anticipate and recover from these failures. In others, type-checking errors are considered fatal.

Programming languages that include dynamic type checking but not static type checking are often called "dynamically typed programming languages". For a list of such languages, see the category for dynamically typed programming languages.

#### Combining static and dynamic type checking

Static typing can find type errors reliably at compile time, which should increase the reliability of the delivered program. However, programmers disagree over how commonly type errors occur, resulting in further disagreements over the proportion of those bugs that are coded that would be caught by appropriately representing the designed types in code.[9][10] Static typing advocates[who?] believe programs are more reliable when they have been well type-checked, whereas dynamic-typing advocates[who?] point to distributed code that has proven reliable and to small bug databases.[citation needed] The value of static typing, then, presumably[vague] increases as the strength of the type system is increased. Advocates of dependent typing,[who?] implemented in languages such as Dependent ML and Epigram, have suggested that almost all bugs can be considered type errors, if the types used in a program are properly declared by the programmer or correctly inferred by the compiler.

Static typing usually results in compiled code that executes faster. When the compiler knows the exact data types that are in use, it can produce optimized machine code. Further, compilers for statically typed languages can find assembler shortcuts more easily.[vague] Some dynamically typed languages such as Common Lisp allow optional type declarations for optimization for this reason. Static typing makes this pervasive.


Dynamic typing allows constructs that some static type checking would reject as illegal. For example, eval functions, which execute arbitrary data as code, become possible. An eval function is possible with static typing, but requires advanced uses of algebraic data types. Further, dynamic typing better accommodates transitional code and prototyping, such as allowing a placeholder data structure (mock object) to be transparently used in place of a full data structure (usually for the purposes of experimentation and testing).
Dynamic typing typically allows duck typing (which enables easier code reuse). Many languages with static typing also feature duck typing or other mechanisms like generic programming that also enable easier code reuse.

Dynamic typing typically makes metaprogramming easier to use. For example, C++ templates are typically more cumbersome to write than the equivalent Ruby or Python code since C++ has stronger rules regarding type definitions (for both functions and variables). This forces a developer to write more boilerplate code for a template than a Python developer would need to. More advanced run-time constructs such as metaclasses and introspection are often harder to use in statically typed languages. In some languages, such features may also be used e.g. to generate new types and behaviors on the fly, based on run-time data. Such advanced constructs are often provided by dynamic programming languages; many of these are dynamically typed, although dynamic typing need not be related to dynamic programming languages.


















































