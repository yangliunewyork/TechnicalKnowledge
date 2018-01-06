# Inheritance
Inheritance is an integral part of Java (and all OOP languages). It turns out that you’re always doing inheritance when you create a class, because unless you explicitly inherit from some other class, you implicitly inherit from Java’s standard root class __Object__.

Since there are now two classes involved—the base class and the derived class—instead of just one, it can be a bit confusing to try to imagine the resulting object produced by a derived class. From the outside, it looks like the new class has the same interface as the base class and maybe some additional methods and fields. But inheritance doesn’t just copy the interface of the base class. When you create an object of the derived class, it contains within it a subobject of the base class. This subobject is the same as if you had created an object of the base class by itself. It’s just that from the outside, the subobject of the base class is wrapped within the derived-class object.

Of course, it’s essential that the base-class subobject be initialized correctly, and there’s only one way to guarantee this: Perform the initialization in the constructor by calling the base-class constructor, which has all the appropriate knowledge and privileges to perform the base-class initialization. Java automatically inserts calls to the base-class constructor in the derived-class constructor.

Java SE5 has added the @Override annotation, which is not a keyword but can be used as if it were. When you mean to override a method, you can choose to add this annotation and the compiler will produce an error message if you accidentally overload instead of overriding.

# Upcasting
The most important aspect of inheritance is not that it provides methods for the new class. It’s the relationship expressed between the new class and the base class. This relationship can be summarized by saying, “The new class is a type of the existing class.” The term is based on the way that class inheritance diagrams have traditionally been drawn: with the root at the top of the page, growing downward.

Casting from a derived type to a base type moves up on the inheritance diagram, so it’s commonly referred to as upcasting. Upcasting is always safe because you’re going from a more specific type to a more general type. That is, the derived class is a superset of the base class. It might contain more methods than the base class, but it must contain at least the methods in the base class. The only thing that can occur to the class interface during the upcast is that it can lose methods, not gain them. This is why the compiler allows upcasting without any explicit casts or other special notation.

# Composition vs. inheritance revisited
In object-oriented programming, the most likely way that you’ll create and use code is by simply packaging data and methods together into a class, and using objects of that class. You’ll also use existing classes to build new classes with composition. Less frequently, you’ll use inheritance. So although inheritance gets a lot of emphasis while learning OOP, it doesn’t mean that you should use it everywhere you possibly can. On the contrary, you should use it sparingly, only when it’s clear that inheritance is useful. One of the clearest ways to determine whether you should use composition or inheritance is to ask whether you’ll ever need to upcast from your new class to the base class. If you must upcast, then inheritance is necessary, but if you don’t need to upcast, then you should look closely at whether you need inheritance.

# The final keyword
Java’s final keyword has slightly different meanings depending on the context, but in general it says “This cannot be changed.” You might want to prevent changes for two reasons: design or efficiency. Because these two reasons are quite different, it’s possible to misuse the final keyword.

The following sections discuss the three places where final can be used: for data, methods, and classes.


## final data
Many programming languages have a way to tell the compiler that a piece of data is “constant.” A constant is useful for two reasons:
1. It can be a compile-time constant that won’t ever change.
2. It can be a value initialized at run time that you don’t want changed.

When final is used with object references rather than primitives, the meaning can be confusing. With a primitive, final makes the value a constant, but with an object reference, final makes the reference a constant. Once the reference is initialized to an object, it can never be changed to point to another object. However, the object itself can be modified; Java does not provide a way to make any arbitrary object a constant. (You can, however, write your class so that objects have the effect of being constant.) This restriction includes arrays, which are also objects.

Java allows the creation of __blank finals__, which are fields that are declared as final but are not given an initialization value. In all cases, the blank final must be initialized before it is used, and the compiler ensures this. However, blank finals provide much more flexibility in the use of the final keyword since, for example, a final field inside a class can now be different for each object, and yet it retains its immutable quality.

Java allows you to make arguments final by declaring them as such in the argument list. This means that inside the method you cannot change what the argument reference points to/

## final methods
There are two reasons for final methods. The first is to put a "lock" on the method to prevent any inheriting class from changing its meaning. This is done for design reasons when you want to make sure that a method's behavior is retained during inheritance and cannot be overridden.

The second reason for final methods is efficiency. In earlier implementations of Java, if you made a method final, you allowed the compiler to turn any calls to that method into inline calls. When the compiler saw a final method call, it could (at its discretion) skip the normal approach of inserting code to perform the method call mechanism (push arguments on the stack, hop over to the method code and execute it, hop back and clean off the stack arguments, and deal with the return value) and instead replace the method call with a copy of the actual code in the method body. This eliminated the overhead of the method call. Of course, if a method is big, then your code begins to bloat, and you probably wouldn't see any performance gains from inlining, since any improvements will be dwarfed by the amount of time spent inside the method.

In more recent version of Java, the virtual machine (in particular, the hotspot technologies) can detect these situations and optimize away the extra indirection, so its no longer necessary-in fact, it is now generally discouraged-to use final to try to help the optimizer. With Java SE5/6, you should let the compiler and JVM handle efficiency issues and make a method final only if you want to explicitly prevent overriding.

#### final and private

Any private methods in a class are implicitly final. Because you can’t access a private method, you can’t override it. You can add the final specifier to a private method, but it doesn’t give that method any extra meaning.

This issue can cause confusion, because if you try to override a private method (which is implicitly final), it seems to work, and the compiler doesn’t give an error message.

"Overriding" can only occur if something is part of the base-class interface. That is, you must be able to upcast an object to its base type and call the same method (the point of this will become clear in the next chapter). If a method is private, it isn't part of the base-class interface. It is just some code that's hidden away inside the class, and it just happens to have that name, but if you create a public, protected, or package-access method with the same name in the derived class, there's no connection to the method that might happen to have that name in the base class. You haven't overridden the method; you're just created a new method. Since a private method is unreachable and effectively invisible, it doesn't factor into anything except for the code organization of the class for which it was defined.


## final classes
When you say that an entire class is final (by preceding its definition with the final keyword), you state that you don’t want to inherit from this class or allow anyone else to do so. In other words, for some reason the design of your class is such that there is never a need to make any changes, or for safety or security reasons you don’t want subclassing.

Note that the fields of a final class can be final or not, as you choose. The same rules apply to final for fields regardless of whether the class is defined as final. However, because it prevents inheritance, all methods in a final class are implicitly final, since there’s no way to override them. You can add the final specifier to a method in a final class, but it doesn’t add any meaning.

# Initialization and class loading
In more traditional languages, programs are loaded all at once as part of the startup process. This is followed by initialization, and then the program begins. The process of initialization in these languages must be carefully controlled so that the order of initialization of statics doesn't cause trouble. C++, for example, has problems if one static expects another static to be valid before the second one has been initialized.

Java doesn't have this problem because it takes a different approach to loading. This is one of the activities that become easier, because everything in Java is an object. Remember that the compiled code for each class exists in its own separate file. That file isn't loaded until the code is needed. In general, you can say that "Class code is loaded at the point of first use."This is usually when the first object of that class is constructed, but loading also occurs when a static field or static method is accessed.

The point of first use is also where the static initialization takes place. All the static objects and the static code block will be initialized in textual order (that is, the order that you write them down in the class definition) at the point of loading. The statics, of course, are initialized only once.


# Summary

Both inheritance and composition allow you to create a new type from existing types. Composition reuses existing types as part of the underlying implementation of the new type, and inheritance reuses the interface.

With Inheritance, the derived class has the base-class interface, so it can be upcast to the base, which is critical for polymorphism, as you'll see in the next chapter.

Despite the strong emphasis on inheritance in object-oriented programming, when you start a design you should generally prefer composition (or possibly delegation) during the first cut and use inheritance only when it is clearly necessary. Composition tends to be more flexible. In addition, by using the added artifice of inheritance with your member type, you can change the exact type, and thus the behavior, of those member objects at run time. Therefore, you can change the behavior of the composed object at run time.
When designing a system, your goal is to find or create a set of classes in which each class has a specific use and is neither too big (encompassing so much functionality that it't unwieldy to reuse) nor annoyingly small (you can't use it by itself or without adding functionality). If your designs become too complex, it't often helpful to add more objects by breaking down existing ones into smaller parts.

When you set out to design a system, it't important to realize that program development is an incremental process, just like human learning. It relies on experimentation; you can do as much analysis as you want, but you still won't know all the answers when you set out on a project. You'll have much more success-and more immediate feedback-if you start out to "grow" your project as an organic, evolutionary creature, rather than constructing it all at once like a glass-box skyscraper. Inheritance and composition are two of the most fundamental tools in object-oriented programming that allow you to perform such experiments.





