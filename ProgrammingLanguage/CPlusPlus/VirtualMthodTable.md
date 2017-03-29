## What is Virtual Method Table ?
A virtual method table (VMT), virtual function table, virtual call table, dispatch table, vtable, or vftable is a mechanism used in a programming language to support dynamic dispatch (or run-time method binding).

Whenever a class defines a virtual function (or method), most compilers add a hidden member variable to the class which points to an array of pointers to (virtual) functions called the virtual method table (VMT or Vtable). These pointers are used at runtime to invoke the appropriate function implementations, because at compile time it may not yet be known if the base function is to be called or a derived one implemented by a class that inherits from the base class.

Suppose a program contains several classes in an inheritance hierarchy: a superclass, Cat, and two subclasses, HouseCat and Lion. Class Cat defines a virtual function named speak, so its subclasses may provide an appropriate implementation (e.g. either meow or roar).

When the program calls the speak function on a Cat reference (which can refer to an instance of Cat, or an instance of HouseCat or Lion), the code must be able to determine which implementation of the function the call should be dispatched to. This depends on the actual class of the object, not its declared class Cat. The class can not generally be determined statically (that is, at compile time), so neither can the compiler decide which function to call at that time. The call must be dispatched to the right function dynamically (that is, at run time) instead.

There are many different ways to implement such dynamic dispatch, but the vtable (virtual table) solution is especially common among C++ and related languages (such as D and C#). Languages which separate the programmatic interface of objects from the implementation, like Visual Basic and Delphi, also tend to use the vtable approach, because it allows objects to use a different implementation simply by using a different set of method pointers.

## Implementation
An object's dispatch table will contain the addresses of the object's dynamically bound methods. Method calls are performed by fetching the method's address from the object's dispatch table. The dispatch table is the same for all objects belonging to the same class, and is therefore typically shared between them. Objects belonging to type-compatible classes (for example siblings in an inheritance hierarchy) will have dispatch tables with the same layout: the address of a given method will appear at the same offset for all type-compatible classes. Thus, fetching the method's address from a given dispatch table offset will get the method corresponding to the object's actual class.

The C++ standards do not mandate exactly how dynamic dispatch must be implemented, but compilers generally use minor variations on the same basic model.

Typically, the compiler creates a separate vtable for each class. When an object is created, a pointer to this vtable, called the virtual table pointer, vpointer or VPTR, is added as a hidden member of this object. As such, the compiler must also generate "hidden" code in the constructors of each class to initialize a new object's vpointer to the address of its class's vtable.

## Efficiency
A virtual call requires at least an extra indexed dereference, and sometimes a "fixup" addition, compared to a non-virtual call, which is simply a jump to a compiled-in pointer. Therefore, calling virtual functions is inherently slower than calling non-virtual functions. An experiment done in 1996 indicates that approximately 6–13% of execution time is spent simply dispatching to the correct function, though the overhead can be as high as 50%. The cost of virtual functions may not be so high on modern CPU architectures due to much larger caches and better branch prediction.

Furthermore, in environments where JIT compilation is not in use, virtual function calls usually cannot be inlined. In certain cases it may be possible for the compiler to perform a process known as devirtualization in which, for instance, the lookup and indirect call are replaced with a conditional execution of each inlined body, but such optimizations are not common.

To avoid this overhead, compilers usually avoid using vtables whenever the call can be resolved at compile time.

## How  vTable and VPTR works in C++
To implement virtual functions, C++ uses a special form of late binding known as the virtual table or vTable. The virtual table is a lookup table of functions used to resolve function calls in a dynamic/late binding manner.

Every class that uses virtual functions (or is derived from a class that uses virtual functions) is given its own virtual table.

This table is simply a static array that the compiler creates at compile time. A virtual table contains one entry for each virtual function that can be called by objects of the class.

Each entry in this vTable is simply a Function Pointer that points to the most-derived function accessible by that class ie the most Base Class.

The compiler also adds a hidden pointer to the base class, which we will call *__vPtr.

*__vPtr is set (automatically) when a class instance is created so that it points to the virtual table for that class. *__vPtr is inherited by derived classes,

let’s take a look at a simple example

```
class Base
{
public:
 virtual void function1() {};
 virtual void function2() {};
};
class D1: public Base
{
public:
 virtual void function1() {};
};
class D2: public Base
{
public:
 virtual void function2() {};
};
```

Because there are 3 classes here, the compiler will set up 3 virtual tables: one for Base, one for D1, and one for D2.

The compiler also adds a hidden pointer to the most Base class that uses virtual functions.

```
class Base
{
public:
 FunctionPointer *__vptr;
 virtual void function1() {};
 virtual void function2() {};
};
class D1: public Base
{
public:
 virtual void function1() {};
};
class D2: public Base
{
public:
 virtual void function2() {};
};
```

When a class object is created, *__vPtr is set to point to the virtual table for that class. For example, when a object of type Base is created, *__vPtr is set to point to the virtual table for Base. When objects of type D1 or D2 are constructed, *__vPtr is set to point to the virtual table for D1 or D2 respectively.

Because there are only two virtual functions here, each virtual table will have two entries (one for function1(), and one for function2()).

Base’s virtual table is simple. An object of type Base can only access the members of Base. Base has no access to D1 or D2 functions. Consequently, the entry for function1 points to Base::function1(), and the entry for function2 points to Base::function2().

D1’s virtual table is slightly more complex. An object of type D1 can access members of both D1 and Base. However, D1 has overridden function1(), making D1::function1() more derived than Base::function1(). Consequently, the entry for function1 points to D1::function1(). D1 hasn’t overridden function2(), so the entry for function2 will point to Base::function2().

D2’s virtual table is similar to D1, except the entry for function1 points to Base::function1(), and the entry for function2 points to D2::function2().

Here’s a picture of this graphically:

![alt](http://www.learncpp.com/images/CppTutorial/Section12/VTable.gif)

By using these tables, the compiler and program are able to ensure function calls resolve to the appropriate virtual function, even if you’re only using a pointer or reference to a base class.


