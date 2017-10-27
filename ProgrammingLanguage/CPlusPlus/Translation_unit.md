In C programming language terminology, a translation unit is the ultimate input to a C compiler from which an object file is generated.[1] In casual usage it is sometimes referred to as a compilation unit. A translation unit roughly consists of a source file after it has been processed by the C preprocessor, meaning that header files listed in #include directives are literally included, sections of code within #ifdef may be included, and macros have been expanded.

# Context

A C program consists of units called source files (or preprocessing files), which, in addition to source code, includes directives for the C preprocessor. A translation unit is the output of the C preprocessor – a source file after it has been preprocessed.

_Preprocessing notably consists of expanding a source file to recursively replace all #include directives with the literal file declared in the directive (usually header files, but possibly other source files); the result of this step is a preprocessing translation unit. Further steps include macro expansion of #define directives, and conditional compilation of #ifdef directives, among others; this translates the preprocessing translation unit into a translation unit. From a translation unit, the compiler generates an object file, which can be further processed and linked (possibly with other object files) to form an executable program._

Note that the preprocessor is in principle language agnostic, and is a __lexical preprocessor__, working at the __lexical analysis__ level – it does not do parsing, and thus is unable to do any processing specific to C syntax. The input to the compiler is the translation unit, and thus it does not see any preprocessor directives, which have all been processed before compiling starts. While a given translation unit is fundamentally based on a file, the actual source code fed into the compiler may appear substantially different than the source file that the programmer views, particularly due to the recursive inclusion of headers.

### Scope

_Translation units define a scope_, roughly file scope, and functioning similarly to module scope; in C terminology this is referred to as __internal linkage__, which is one of the two forms of linkage in C. Names (functions and variables) declared outside of a function block may be visible either only within a given translation unit, in which case they are said to have internal linkage – they are not visible to the linker – or may be visible to other object files, in which case they are said to have __external linkage__, and are visible to the linker.

C does not have a notion of modules. However, separate object files (and hence also the translation units used to produce object files) function similarly to separate modules, and if a source file does not include other source files, internal linkage (translation unit scope) may be thought of as "file scope, including all header files".














