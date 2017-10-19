In computer science, __functional programming__ is a programming paradigm—a style of building the structure and elements of computer programs—that treats computation as the evaluation of mathematical functions and avoids changing-state and mutable data. It is a declarative programming paradigm, which means programming is done with expressions or declarations instead of statements. In functional code, the output value of a function depends only on the arguments that are passed to the function, so calling a function f twice with the same value for an argument x will produce the same result f(x) each time; this is in contrast to procedures depending on a local or global state, which may produce different results at different times when called with the same arguments but a different program state. __Eliminating side effects, i.e. changes in state that do not depend on the function inputs, can make it much easier to understand and predict the behavior of a program, which is one of the key motivations for the development of functional programming.__

In contrast, imperative programming changes state with commands in the source code, the simplest example being assignment. Imperative programming does have functions—not in the mathematical sense—but in the sense of subroutines. They can have side effects that may change the value of program state. Functions without return values therefore make sense. Because of this, they lack __referential transparency__, i.e. the same language expression can result in different values at different times depending on the state of the executing program.

# Concepts

A number of concepts and paradigms are specific to functional programming, and generally foreign to imperative programming (including object-oriented programming). However, programming languages are often hybrids of several programming paradigms, so programmers using "mostly imperative" languages may have utilized some of these concepts.

#### First-class and higher-order functions

__Higher-order functions__ are functions that can either take other functions as arguments or return them as results.

Higher-order functions are closely related to first-class functions in that higher-order functions and first-class functions both allow functions as arguments and results of other functions. The distinction between the two is subtle: "higher-order" describes a mathematical concept of functions that operate on other functions, while "first-class" is a computer science term that describes programming language entities that have no restriction on their use (thus first-class functions can appear anywhere in the program that other first-class entities like numbers can, including as arguments to other functions and as their return values).

# Comparison to imperative programming 

Functional programming is very different from imperative programming. The most significant differences stem from the fact that functional programming avoids side effects, which are used in imperative programming to implement state and I/O. Pure functional programming completely prevents side-effects and provides __referential transparency__.

Higher-order functions are rarely used in older imperative programming. A traditional imperative program might use a loop to traverse and modify a list. A functional program, on the other hand, would probably use a higher-order “map” function that takes a function and a list, generating and returning a new list by applying the function to each list item.

##### Referential transparency

__Referential transparency__ and referential opacity are properties of parts of computer programs. __An expression is said to be referentially transparent if it can be replaced with its corresponding value without changing the program's behavior. As a result, evaluating a referentially transparent function gives the same value for same arguments. Such functions are called pure functions. An expression that is not referentially transparent is called referentially opaque.__

In mathematics all function applications are referentially transparent, by the definition of what constitutes a mathematical function. However, this is not always the case in programming, where the terms procedure and method are used to avoid misleading connotations. In functional programming only referentially transparent functions are considered. Some programming languages provide means to guarantee referential transparency. Some functional programming languages enforce referential transparency for all functions.
The importance of referential transparency is that it allows the programmer and the compiler to reason about program behavior as a rewrite system. This can help in proving correctness, simplifying an algorithm, assisting in modifying code without breaking it, or optimizing code by means of memoization, common subexpression elimination, lazy evaluation, or parallelization.

__As referential transparency requires the same results for any given set of inputs at any point in time, a referentially transparent expression is therefore deterministic.__

### Simulating state

There are tasks (for example, maintaining a bank account balance) that often seem most naturally implemented with state. Pure functional programming performs these tasks, and I/O tasks such as accepting user input and printing to the screen, in a different way.
The pure functional programming language Haskell implements them using monads, derived from category theory. Monads offer a way to abstract certain types of computational patterns, including (but not limited to) modeling of computations with mutable state (and other side effects such as I/O) in an imperative manner without losing purity. While existing monads may be easy to apply in a program, given appropriate templates and examples, many students find them difficult to understand conceptually, e.g., when asked to define new monads (which is sometimes needed for certain types of libraries).

Another way in which functional languages can simulate state is by passing around a data structure that represents the current state as a parameter to function calls. On each function call, a copy of this data structure is created with whatever differences are the result of the function. This is referred to as 'state-passing style'.

Impure functional languages usually include a more direct method of managing mutable state. Clojure, for example, uses managed references that can be updated by applying pure functions to the current state. This kind of approach enables mutability while still promoting the use of pure functions as the preferred way to express computations.

Alternative methods such as Hoare logic and uniqueness have been developed to track side effects in programs. Some modern research languages use effect systems to make the presence of side effects explicit.

### Efficiency issues

Functional programming languages are typically less efficient in their use of CPU and memory than imperative languages such as C and Pascal. This is related to the fact that some mutable data structures like arrays have a very straightforward implementation using present hardware (which is a highly evolved Turing machine). Flat arrays may be accessed very efficiently with deeply pipelined CPUs, prefetched efficiently through caches (with no complex pointer chasing), or handled with SIMD instructions. It is also not easy to create their equally efficient general-purpose immutable counterparts. For purely functional languages, the worst-case slowdown is logarithmic in the number of memory cells used, because mutable memory can be represented by a purely functional data structure with logarithmic access time (such as a balanced tree). However, such slowdowns are not universal. For programs that perform intensive numerical computations, functional languages such as OCaml and Clean are only slightly slower than C according to The Computer Language Benchmarks Game.[64] For programs that handle large matrices and multidimensional databases, array functional languages (such as J and K) were designed with speed optimizations.

Immutability of data can in many cases lead to execution efficiency by allowing the compiler to make assumptions that are unsafe in an imperative language, thus increasing opportunities for inline expansion.

Lazy evaluation may also speed up the program, even asymptotically, whereas it may slow it down at most by a constant factor (however, it may introduce memory leaks if used improperly). Launchbury 1993 discusses theoretical issues related to memory leaks from lazy evaluation, and O'Sullivan et al. 2008 give some practical advice for analyzing and fixing them. However, the most general implementations of lazy evaluation making extensive use of dereferenced code and data perform poorly on modern processors with deep pipelines and multi-level caches (where a cache miss may cost hundreds of cycles).
