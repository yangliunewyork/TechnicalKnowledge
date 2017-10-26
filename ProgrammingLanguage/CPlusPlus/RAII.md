# Introduction

__Resource acquisition is initialization (RAII)__ is a programming idiom used in several object-oriented languages. _In RAII, holding a resource is a class invariant, and is tied to object lifetime: resource allocation (or acquisition) is done during object creation (specifically initialization), by the constructor, while resource deallocation (release) is done during object destruction (specifically finalization), by the destructor._ Thus the resource is guaranteed to be held between when initialization finishes and finalization starts (holding the resources is a class invariant), and to be held only when the object is alive. Thus if there are no object leaks, there are no resource leaks.

The technique was developed for exception-safe resource management in C++ during 1984–89, primarily by Bjarne Stroustrup and Andrew Koenig, and the term itself was coined by Stroustrup. RAII is generally pronounced as an initialism, sometimes pronounced as "R, A, double I".


#### Example

The following C++11 example demonstrates usage of RAII for file access and mutex locking:

```cpp
#include <mutex>
#include <iostream>
#include <string> 
#include <fstream>
#include <stdexcept>

void write_to_file (const std::string & message) {
    // mutex to protect file access (shared across threads)
    static std::mutex mutex;

    // lock mutex before accessing file
    std::lock_guard<std::mutex> lock(mutex);

    // try to open file
    std::ofstream file("example.txt");
    if (!file.is_open())
        throw std::runtime_error("unable to open file");
    
    // write message to file
    file << message << std::endl;
    
    // file will be closed 1st when leaving scope (regardless of exception)
    // mutex will be unlocked 2nd (from lock destructor) when leaving
    // scope (regardless of exception)
}
```

This code is exception-safe because C++ guarantees that all stack objects are destroyed at the end of the enclosing scope, known as __stack unwinding__. The destructors of both the lock and file objects are therefore guaranteed to be called when returning from the function, whether an exception has been thrown or not.

_Local variables allow easy management of multiple resources within a single function: they are destroyed in the reverse order of their construction, and an object is destroyed only if fully constructed—that is, if no exception propagates from its constructor._

Using RAII greatly simplifies resource management, reduces overall code size and helps ensure program correctness. RAII is therefore highly recommended in C++, and most of the C++ standard library follows the idiom.


#### Typical uses

The RAII design is often used for controlling mutex locks in multi-threaded applications. In that use, the object releases the lock when destroyed. Without RAII in this scenario the potential for deadlock would be high and the logic to lock the mutex would be far from the logic to unlock it. With RAII, the code that locks the mutex essentially includes the logic that the lock will be released when execution leaves the scope of the RAII object.

Another typical example is interacting with files: We could have an object that represents a file that is open for writing, wherein the file is opened in the constructor and closed when execution leaves the object's scope. In both cases, RAII ensures only that the resource in question is released appropriately; care must still be taken to maintain exception safety. If the code modifying the data structure or file is not exception-safe, the mutex could be unlocked or the file closed with the data structure or file corrupted.

Ownership of dynamically allocated objects (memory allocated with new in C++) can also be controlled with RAII, such that the object is released when the RAII (stack-based) object is destroyed. For this purpose, the C++11 standard library defines the smart pointer classes std::unique_ptr for single-owned objects and std::shared_ptr for objects with shared ownership. Similar classes are also available through std::auto_ptr in C++98, and boost::shared_ptr in the Boost libraries.

# Benefits

The advantages of RAII as a resource management technique are that it provides encapsulation, exception safety (for stack resources), and locality (it allows acquisition and release logic to be written next to each other).

Encapsulation is provided because resource management logic is defined once in the class, not at each call site. Exception safety is provided for stack resources (resources that are released in the same scope as they are acquired) by tying the resource to the lifetime of a stack variable (a local variable declared in a given scope): if an exception is thrown, and proper exception handling is in place, the only code that will be executed when exiting the current scope are the destructors of objects declared in that scope. Finally, locality of definition is provided by writing the constructor and destructor definitions next to each other in the class definition.
Resource management therefore needs to be tied to the lifespan of suitable objects in order to gain automatic allocation and reclamation. Resources are acquired during initialization, when there is no chance of them being used before they are available, and released with the destruction of the same objects, which is guaranteed to take place even in case of errors.

Comparing RAII with the finally construct used in Java, Stroustrup wrote that "In realistic systems, there are far more resource acquisitions than kinds of resources, so the "resource acquisition is initialization" technique leads to less code than use of a "finally" construct."




