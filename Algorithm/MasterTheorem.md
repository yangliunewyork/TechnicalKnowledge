# What is Master Theorem ?
In the analysis of algorithms, the master theorem for divide-and-conquer recurrences provides an asymptotic analysis (using Big O notation) for recurrence relations of types that occur in the analysis of many divide and conquer algorithms. The approach was first presented by Jon Bentley, Dorothea Haken, and James B. Saxe in 1980, where it was described as a "unifying method" for solving such recurrences.

### Introduction
Consider a problem that can be solved using a recursive algorithm such as the following:

```
procedure p( input x of size n ):
   if n < some constant k:
     Solve x directly without recursion
   else:
     Create a subproblems of x, each having size n/b
     Call procedure p recursively on each subproblem
     Combine the results from the subproblems
```

The above algorithm divides the problem into a number of subproblems recursively, each subproblem being of size n/b. Its call tree has a node for each recursive call, with the children of that node being the other calls made from that call. The leaves of the tree are the base cases of the recursion, the subproblems (of size less than k) that do not recurse. The above example would have a child nodes at each non-leaf node. Each node does an amount of work that corresponds to the size of the sub problem n passed to that instance of the recursive call and given by f(n). The total amount of work done by the entire algorithm is the sum of the work performed by all the nodes in the tree.

The runtime of an algorithm such as the 'p' above on an input of size 'n', usually denoted  T(n), can be expressed by the recurrence relation

![alt](https://wikimedia.org/api/rest_v1/media/math/render/svg/2f5661cc61a3a08b59ef5b55309cd1e4d4514815)

where f(n) is the time to create the subproblems and combine their results in the above procedure. This equation can be successively substituted into itself and expanded to obtain an expression for the total amount of work done. The master theorem allows many recurrence relations of this form to be converted to Θ-notation directly, without doing an expansion of the recursive relation.

The master theorem allows us to compute the asymptotic running time for divide-and-conquer algorithms that divide each problem up into aa subproblems where each subproblem is bb times smaller than the original problem. Also, at each iteration, an additional amount of work equal to f(n)f(n) is done.

So our recurrence is: T(n)=aT(n/b)+f(n)T(n)=aT(n/b)+f(n)

To understand this intuitively, picture the tree structure of recursive calls, with the entire problem at the root, and its immediate subproblems as its children, and so on. Notice that f(n)f(n) is the amount of work done on the first level, af(n/b)af(n/b) is the amount of work done on the second level, a2f(n/b2)a2f(n/b2) is the amount of work done on the third level, and so on.

The bolded words below highlight the intuition. The rest is just algebra.

There are three cases:

Case 1: f(n)=O(nc)f(n)=O(nc) where c<logbac<logb⁡a. This is equivalent to a/bc>1a/bc>1.

If f(n)=O(nc)f(n)=O(nc) then the amount of work done on the ith level is aiO((n/bi)c)aiO((n/bi)c), or O((a/bc)knc)O((a/bc)knc). Since a/bc>1a/bc>1, this means that the amount of work done on each level beyond the first increases geometrically, or faster. Therefore approximately a constant fraction of the work is done on the bottommost level. There are about logbnlogb⁡n levels, so the bottommost level has about alogbn=nlogbaalogb⁡n=nlogb⁡a nodes. Therefore the total work done is about f(1)nlogba=Θ(nlogba)f(1)nlogb⁡a=Θ(nlogb⁡a).

Case 2: f(n)=Θ(nclogkn)f(n)=Θ(nclogk⁡n) where c=logbac=logb⁡a. This means that a/bc=1a/bc=1. First let's consider what happens if k=0k=0. Then the amount of work done on each level is O((a/bc)knc)=O(nc)O((a/bc)knc)=O(nc); which is independent of the level. The amount of work done on each level is approximately the same. So the total work is simply the number of levels times the work done on the first level, T(n)=Θ(f(n)logbn)=Θ(nclogn)T(n)=Θ(f(n)logb⁡n)=Θ(nclog⁡n).

Now what if k>0k>0? Then the amount of work done on the ith level is modified slightly to Θ(nclogk(n/bi))Θ(nclogk⁡(n/bi)) so it is not really constant anymore; it falls allometrically as you go deeper (i.e., as a power law). You can verify by approximating the sum as an integral that the average amount of work done per level is a constant fraction (constant w.r.t. nn, that is) of the amount of work done on the first level. Therefore the total work is again T(n)=Θ(f(n)logbn)=Θ(nclogk+1n)T(n)=Θ(f(n)logb⁡n)=Θ(nclogk+1⁡n).

Case 3: f(n)=Ω(nc)f(n)=Ω(nc) where c>logbac>logb⁡a; plus an additional regularity condition. This is equivalent to a/bc<1a/bc<1. By the same reasoning as in case 1, the amount of work done on the ith level is Ω((a/bc)knc)Ω((a/bc)knc), so the amount of work done on each level decreases geometrically or faster as you go down. Therefore approximately a constant fraction of the work is done at the topmost level. Therefore T(n)=Θ(f(n))T(n)=Θ(f(n)).

The regularity condition ensures that the amount of work done on each level really does decrease geometrically, by prohibiting badly-behaved functions ff that oscillate wildly for arbitrarily large nn.
