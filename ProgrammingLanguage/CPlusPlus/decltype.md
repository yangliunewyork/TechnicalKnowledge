In the C++ programming language, __decltype__ is a keyword used to query the type of an expression. Introduced in C++11, its primary intended use is in generic programming, where it is often difficult, or even impossible, to express types that depend on template parameters.

As generic programming techniques became increasingly popular throughout the 1990s, the need for a type-deduction mechanism was recognized. Many compiler vendors implemented their own versions of the operator, typically called typeof, and some portable implementations with limited functionality, based on existing language features were developed. In 2002, Bjarne Stroustrup proposed that a standardized version of the operator be added to the C++ language, and suggested the name "decltype", to reflect that the operator would yield the "declared type" of an expression.

decltype's semantics were designed to cater to both generic library writers and novice programmers. In general, the deduced type matches the type of the object or function exactly as declared in the source code. Like the sizeof operator, decltype's operand is not evaluated.

# Example

```cpp
const int&& foo();
const int bar();
int i;
struct A { double x; };
const A* a = new A();
decltype(foo()) x1; // type is const int&&
decltype(bar()) x2; // type is int
decltype(i) x3; // type is int
decltype(a->x) x4; // type is double
decltype((a->x)) x5; // type is const double&
```
