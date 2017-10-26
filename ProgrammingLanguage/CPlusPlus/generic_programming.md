_Generic programming techniques using templates are an important way to develop large, complex software applications and systems. So are object oriented techniques. Both are important ways to express polymorphism – at compile time and at run time, respectively._ And they work great together in C++.

C++ supports generic programming. Generic programming is a way of developing software that maximizes code reuse in a way that does not sacrifice performance. (The “performance” part isn’t strictly necessary, but it is highly desirable.)

Generic programming is programming based on parameterization: You can parameterize a type with another (such as a vector with its element types) and an algorithm with another (such as a sort function with a comparison function). The aim of generic programming is to generalize a useful algorithm or data structure to its most general and useful form. For example, a vector of integers is fine and so is a function that finds the largest value in a vector of integers. However, a better generic find function will be able to find an element in a vector of any type or better still in any sequence of elements described with a pair of iterators:

```cpp
auto p = find(begin(vs), end(vs), "Grail"s); // vector<string> vs; p is vector<string>::iterator 
auto q = find(begin(vi), end(vi), 42);       // vector<int> vi;    q is vector<int>::iterator 
auto r = find(begin(ld), end(ld), 1.2);      // list<double> ld;   r is list<double>::iterator 
auto s = find(begin(ar), end(ar), 10);       // int ar[10];        s is int *
```

Generic programming is in some ways more flexible than object-oriented programming. In particular, it does not depend on hierarchies. For example, there is no hierarchical relationship between an int and a string. Generic programming is generally more structured than OOP; in fact, a common term used to describe generic programming is “parametric polymorphism”, with “ad hoc polymorphism” being the corresponding term for object-oriented programming. In the context of C++, generic programming resolves all names at compile time; it does not involve dynamic (run-time) dispatch. This has led generic programming to become dominant in areas where run-time performance is important.

Please note that generic programming is not a panacea. There are many parts of a program that need no parameterization and many examples where run-time dispatch (OOP) is more approriate.

Generic components are pretty easy to use, at least if they’re designed well, and they tend to hide a lot of complexity. The other interesting feature is that they tend to make your code faster, particularly if you use them more. This creates a pleasant non-tradeoff: when you use the components to do the nasty work for you, your code gets smaller and simpler, you have less chance of introducing errors, and your code will often run faster.
