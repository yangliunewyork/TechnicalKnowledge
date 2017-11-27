



# Q & A

##### Is Pthread library actually a user thread solution?

pthreads, per se, isn't really a threading library. pthreads is the interface which a specific threading library implements, using the concurrency resources available on that platform. So there's a pthreads implementation on linux, on bsd, on solaris, etc., and while the interface (the header files and the meaning of the calls) is the same, the implementation of each is different.

So what pthread_create actually does, in terms of kernel thread objects, varies between OSes and pthread library implementations. At a first approximation, you don't need to know (that's stuff that the pthread abstraction allows you to not need to know about). Eventually you might need to see "behind the curtain", but for most pthread users that's not necessary.

If you want to know what a /specific/ pthread implementation does, on a specific OS, you'll need to clarify your question. What Solaris and Linux do, for example, is very different.
