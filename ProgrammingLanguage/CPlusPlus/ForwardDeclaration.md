## What is forward declaration ? 

In computer programming, a forward declaration is a declaration of an identifier (denoting an entity such as a type, a variable, a constant, or a function) for which the programmer has not yet given a complete definition.

It is required for a compiler to know certain properties of an identifier (size for memory allocation, data type for type checking, such as type signature of functions), but not other details, like the particular value it holds (in case of variables or constants) or definition (in the case of functions). This is particularly useful for one-pass compilers and separate compilation.

Forward declaration is used in languages that require declaration before use; it is necessary for mutual recursion in such languages, as it is impossible to define such functions (or data structures) without a forward reference in one definition: one of the functions (respectively, data structures) must be defined first. It is also useful to allow flexible code organization, for example if one wishes to place the main body at the top, and called functions below it.

In other languages forward declarations are not necessary, which generally requires instead a multi-pass compiler and for some compilation to be deferred to link time. In these cases identifiers must be defined (variables initialized, functions defined) before they are used in execution, but do not need to be defined before they are used in source code for compilation or interpretation: identifiers do not need to be immediately resolved to an existing entity.
