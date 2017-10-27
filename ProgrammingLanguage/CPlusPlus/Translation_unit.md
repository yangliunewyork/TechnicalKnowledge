In C programming language terminology, a translation unit is the ultimate input to a C compiler from which an object file is generated.[1] In casual usage it is sometimes referred to as a compilation unit. A translation unit roughly consists of a source file after it has been processed by the C preprocessor, meaning that header files listed in #include directives are literally included, sections of code within #ifdef may be included, and macros have been expanded.

# Context

A C program consists of units called source files (or preprocessing files), which, in addition to source code, includes directives for the C preprocessor. A translation unit is the output of the C preprocessor – a source file after it has been preprocessed.

_Preprocessing notably consists of expanding a source file to recursively replace all #include directives with the literal file declared in the directive (usually header files, but possibly other source files); the result of this step is a preprocessing translation unit. Further steps include macro expansion of #define directives, and conditional compilation of #ifdef directives, among others; this translates the preprocessing translation unit into a translation unit. From a translation unit, the compiler generates an object file, which can be further processed and linked (possibly with other object files) to form an executable program._

Note that the preprocessor is in principle language agnostic, and is a __lexical preprocessor__, working at the __lexical analysis__ level – it does not do parsing, and thus is unable to do any processing specific to C syntax. The input to the compiler is the translation unit, and thus it does not see any preprocessor directives, which have all been processed before compiling starts. While a given translation unit is fundamentally based on a file, the actual source code fed into the compiler may appear substantially different than the source file that the programmer views, particularly due to the recursive inclusion of headers.

### Scope

_Translation units define a scope_, roughly file scope, and functioning similarly to module scope; in C terminology this is referred to as __internal linkage__, which is one of the two forms of linkage in C. Names (functions and variables) declared outside of a function block may be visible either only within a given translation unit, in which case they are said to have internal linkage – they are not visible to the linker – or may be visible to other object files, in which case they are said to have __external linkage__, and are visible to the linker.

C does not have a notion of modules. However, separate object files (and hence also the translation units used to produce object files) function similarly to separate modules, and if a source file does not include other source files, internal linkage (translation unit scope) may be thought of as "file scope, including all header files".


# Other

Before going to linkage types, you have to understand what does a translation unit mean.

A translation unit, is the input of any C compiler, that is your source file after passing the preprocessing step, so that preprocessor macros are expanded, all external libraries and header files are included.

External linkage, means that the variable could be defined somewhere else outside the file you are working on, which means you can define it inside any other translation unit rather your current one (you will have to use the keyword extern when defining it in the other source code).

Internal linkage, means that the variable must be defined in your translation unit scope, which means it should either be defined in any of the included libraries, or in the same file scope.

None linkage, points to the default functions and braces  scopes, such as defining an auto variable inside a function, this will make the variable only accessable within that function's scope.

Note that:

* Any global object is externally linked by default, you can disable that by using the keyword static.
* Any constant global object is internally linked by default, you can disable that by using the keyword extern.

Example:

```cpp
int n;
const int z=1;
static int a;
extern const int b;
 
void bla()
{
     int y;     
}
```


In this snippet of code, you can notice that:

```
variable n: is externally linked by default.
variable z: is internally linked by default.
variable a: is internally linked.
variable b : is externally linked.
variable y: is a local variable.
```









