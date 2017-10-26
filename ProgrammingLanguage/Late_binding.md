__Late binding__, or __dynamic binding__, is a computer programming mechanism in which the method being called upon an object or the function being called with arguments is looked up by name at runtime.

With __early binding__, or __static binding__, in an object-oriented language, the compilation phase fixes all types of variables and expressions. This is usually stored in the compiled program as an offset in a __virtual method table ("v-table")__ and is very efficient. With late binding the compiler does not have enough information to verify the method even exists, let alone bind to its particular slot on the v-table. Instead the method is looked up by name at runtime.


In C++, late binding (also called "dynamic binding") normally happens when the virtual keyword is used in a method's declaration. C++ then creates a so-called virtual table, which is a look-up table for such functions that will always be consulted when they are called. Usually, the "late binding" term is used in favor of "dynamic dispatch".









