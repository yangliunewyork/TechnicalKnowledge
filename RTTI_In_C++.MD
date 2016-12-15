### What is RTTI ?
In computer programming, run-time type information or **run-time type identification (RTTI)** refers to a C++ mechanism that exposes information about an object's data type at runtime. Run-time type information can apply to simple data types, such as integers and characters, or to generic types. This is a C++ specialization of a more general concept called type introspection. Similar mechanisms are also known in other programming languages, such as Object Pascal (Delphi).
In the original C++ design, Bjarne Stroustrup did not include run-time type information, because he thought this mechanism was often misused.

### Overview
The dynamic_cast<> operation and typeid operator in C++ are part of RTTI.
The C++ run-time type information permits performing safe typecasts and manipulating type information at run time.
RTTI is available only for classes which are polymorphic, which means they have at least one virtual method. In practice, this is not a limitation because base classes must have a virtual destructor to allow objects of derived classes to perform proper cleanup if they are deleted from a base pointer.
RTTI is optional with some compilers; the programmer can choose at compile time whether to include the function. There may be a resource cost to making RTTI available even if the program does not use it.
