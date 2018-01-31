https://theboostcpplibraries.com/boost.ref  
https://stackoverflow.com/questions/26254652/how-does-boostref-work  

The library Boost.Ref provides two functions, boost::ref() and boost::cref(), in the header file boost/ref.hpp. They are useful if you use, for example, std::bind() for a function which expects parameters by reference. Because std::bind() takes parameters by value, you have to deal with references explicitly.

Boost.Ref was added to the standard library in C++11, where you will find the functions std::ref() and std::cref() in the header file functional.

```cpp
#include <boost/ref.hpp>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

void print(std::ostream &os, int i)
{
  os << i << std::endl;
}

int main()
{
  std::vector<int> v{1, 3, 2};
  std::for_each(v.begin(), v.end(),
    std::bind(print, boost::ref(std::cout), std::placeholders::_1));
}
```

In Example 42.1, the function print() is passed to std::for_each() to write the numbers in v to an output stream. Because print() expects two parameters – an output stream and the number to be written – std::bind() is used. The first parameter passed to print() through std::bind() is std::cout. However, print() expects a reference to an output stream, while std::bind() passes parameters by value. Therefore, boost::ref() is used to wrap std::cout. boost::ref() returns a proxy object that contains a reference to the object passed to it. This makes it possible to pass a reference to std::cout even though std::bind() takes all parameters by value.

The function template boost::cref() lets you pass a const reference.

### How does boost::ref work?


7
down vote
accepted
reference_wrapper is really simple, the easiest way to understand how it works is simply to look at the code. The generator functions, ref and cref that create a reference_wrapper are even simpler, again, just look at their definitions.

Understanding what it's for is also pretty simple: the intended use of reference_wrapper is to pass a variable by reference through a generic API that usually takes arguments by value. That's it.

That's useful when you have wrapped some function or functor in a forwarding API, and want to ensure the forwarding API passes references not values.

For instance, boost::bind copies its arguments into the callable object that it returns, and then invokes the target function passing the copied objects as arguments.

e.g. when you call boost::bind(&func, i) it returns a functor that contains a copy of &func and a copy of i. When you invoke that functor, it calls func with the copy of i. So if the function takes a reference, that reference is bound to the internal copy of i not to i itself. So if you have:

```cpp
void func(int& i) { ++i; }
int i = 0;
auto bound = boost::bind(&func, i);
bound();
assert( i == 1 );  // FAILS!
```

The assertion will fail, because the int that gets passed to func is not i but a copy of i stored inside bound.

If you actually want the bound function to be called with a reference, you need something that is copyable like a value but implements reference semantics, which is where reference_wrapper comes in:

```cpp
void func(int& i) { ++i; }
int i = 0;
auto bound = boost::bind(&func, boost::ref(i));
bound();
assert( i == 1 );  // passes
```

Now ref(i) creates a reference_wrapper<int> that refers to i and so bound contains a copy of that reference_wrapper<int>, also referring to i. When you invoke bound it passes the reference_wrapper<int> to func, which triggers the implicit conversion to int&, so that the reference binds to i, and i gets incremented as desired.

Other examples where you would use reference_wrapper are std::thread and std::async (and the Boost equivalents). They copy their arguments and then pass them to the wrapped target functor as rvalues, so if the functor has lvalue reference parameters then you must use reference_wrapper for the code to even compile.

Using reference_wrapper with your a_func_tmpl example doesn't really match the intended use, because the function doesn't take a reference, and you're not calling it through a generic API that would decay references to value anyway. Personally I wouldn't worry too much about why your example works in one case and not in the other, because it isn't the intended use case for reference_wrapper anyway. It's more important to understand what it is meant for, so you can use it in the appropriate places when necessary.

