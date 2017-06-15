> Polymorphism is the third essential feature of an object-oriented programming language, after data abstraction and inheritance.It provides another dimension of separation of interface from implementation, to decouple what from how. Polymorphism allows improved code organization and readability as well as the creation of extensible programs that can be 揼rown?not only during the original creation of the project, but also when new features are desired.

Encapsulation creates new data types by combining characteristics and behaviors. Implementation hiding separates the interface from the implementation by making the details private. This sort of mechanical organization makes ready sense to someone with a procedural programming background. But polymorphism deals with decoupling in terms of types. In the last chapter, you saw how inheritance allows the treatment of an object as its own type or its base type. This ability is critical because it allows many types (derived from the same base type) to be treated as if they were one type, and a single piece of code to work on all those different types equally. The polymorphic method call allows one type to express its distinction from another, similar type, as long as they抮e both derived from the same base type. This distinction is expressed through differences in behavior of the methods that you can call through the base class.

# Method-call binding
Connecting a method call to a method body is called __binding__. When binding is performed before the program is run (by the compiler and linker, if there is one), it’s called __early binding__. You might not have heard the term before because it has never been an option with procedural languages. C compilers have only one kind of method call, and that’s early binding.

__Late binding__, which means that the binding occurs at run time, based on the type of object. Late binding is also called dynamic binding or runtime binding. When a language implements late binding, there must be some mechanism to determine the type of the object at run time and to call the appropriate method. That is, the compiler still doesn't know the object type, but the method-call mechanism finds out and calls the correct method body. The late-binding mechanism varies from language to language, but you can imagine that some sort of type information must be installed in the objects.


__All method binding in Java uses late binding unless the method is static or final (private methods are implicitly final). This means that ordinarily you don’t need to make any decisions about whether late binding will occur—it happens automatically.__

Once you know that all method binding in Java happens polymorphically via late binding, you can write your code to talk to the base class and know that all the derived-class cases will work correctly using the same code. Or to put it another way, you “send a message to an object and let the object figure out the right thing to do.”

# Constructors and polymorphism
As usual, constructors are different from other kinds of methods. This is also true when polymorphism is involved. Even though constructors are not polymorphic (they’re actually static methods, but the static declaration is implicit), it’s important to understand the way constructors work in complex hierarchies and with polymorphism. This understanding will help you avoid unpleasant entanglements.

A constructor for the base class is always called during the construction process for a derived class, chaining up the inheritance hierarchy so that a constructor for every base class is called. This makes sense because the constructor has a special job: to see that the object is built properly. A derived class has access to its own members only, and not to those of the base class (whose members are typically private). Only the base-class constructor has the proper knowledge and access to initialize its own elements. Therefore, it’s essential that all constructors get called; otherwise the entire object wouldn’t be constructed. That’s why the compiler enforces a constructor call for every portion of a derived class. It will silently call the default constructor if you don’t explicitly call a base-class constructor in the derived-class constructor body. If there is no default constructor, the compiler will complain. (In the case where a class has no constructors, the compiler will automatically synthesize a default constructor.)

The order of the constructor calls is important. When you inherit, you know all about the base class and can access any public and protected members of the base class. This means that you must be able to assume that all the members of the base class are valid when you’re in the derived class. In a normal method, construction has already taken place, so all the members of all parts of the object have been built. Inside the constructor, however, you must be able to assume that all members that you use have been built. The only way to guarantee this is for the base-class constructor to be called first. Then when you’re in the derived-class constructor, all the members you can access in the base class have been initialized. Knowing that all members are valid inside the constructor is also the reason that, whenever possible, you should initialize all member objects (that is, objects placed in the class using composition) at their point of definition in the class. If you follow this practice, you will help ensure that all base class members and member objects of the current object have been initialized. Unfortunately, this doesn’t handle every case, as you will see in the next section.

### Inheritance and cleanup
When using composition and inheritance to create a new class, most of the time you won’t have to worry about cleaning up; subobjects can usually be left to the garbage collector. If you do have cleanup issues, you must be diligent and create a dispose( ) method (the name I have chosen to use here; you may come up with something better) for your new class. And with inheritance, you must override dispose( ) in the derived class if you have any special cleanup that must happen as part of garbage collection. When you override dispose( ) in an inherited class, it’s important to remember to call the base-class version of dispose( ), since otherwise the base-class cleanup will not happen.

The order of disposal should be the reverse of the order of initialization, in case one subobject is dependent on another. For fields, this means the reverse of the order of declaration (since fields are initialized in declaration order). For base classes (following the form that’s used in C++ for destructors), you should perform the derived-class cleanup first, then the base-class cleanup. That’s because the derived-class cleanup could call some methods in the base class that require the base-class components to be alive, so you must not destroy them prematurely.


### Behavior of polymorphic methods inside constructors
The hierarchy of constructor calls brings up an interesting dilemma. What happens if you’re inside a constructor and you call a dynamically-bound method of the object being constructed?

Inside an ordinary method, the dynamically-bound call is resolved at run time, because the object cannot know whether it belongs to the class that the method is in or some class derived from it.

If you call a dynamically-bound method inside a constructor, the overridden definition for that method is used. However, the effect of this call can be rather unexpected because the overridden method will be called before the object is fully constructed. This can conceal some difficult-to-find bugs.

Conceptually, the constructor’s job is to bring the object into existence (which is hardly an ordinary feat). Inside any constructor, the entire object might be only partially formed—you can only know that the base-class objects have been initialized. If the constructor is only one step in building an object of a class that’s been derived from that constructor’s class, the derived parts have not yet been initialized at the time that the current constructor is being called. A dynamically bound method call, however, reaches “outward” into the inheritance hierarchy. It calls a method in a derived class. If you do this inside a constructor, you call a method that might manipulate members that haven’t been initialized yet—a sure recipe for disaster.

As a result, a good guideline for constructors is, “Do as little as possible to set the object into a good state, and if you can possibly avoid it, don’t call any other methods in this class.” The only safe methods to call inside a constructor are those that are final in the base class. (This also applies to private methods, which are automatically final.) These cannot be overridden and thus cannot produce this kind of surprise. You may not always be able to follow this guideline, but it’s something to strive towards.

# Covariant return types

Java SE5 adds covariant return types, which means that an overridden method in a derived class can return a type derived from the type returned by the base-class method.


# Designing with inheritance

Once you learn about polymorphism, it can seem that everything ought to be inherited, because polymorphism is such a clever tool. This can burden your designs; in fact, if you choose inheritance first when you’re using an existing class to make a new class, things can become needlessly complicated.

A better approach is to choose composition first, especially when it’s not obvious which one you should use. Composition does not force a design into an inheritance hierarchy. But composition is also more flexible since it’s possible to dynamically choose a type (and thus behavior) when using composition, whereas inheritance requires an exact type to be known at compile time.

## Downcasting and runtime type information
Since you lose the specific type information via an upcast (moving up the inheritance hierarchy), it makes sense that to retrieve the type information梩hat is, to move back down the inheritance hierarchy梱ou use a downcast. However, you know an upcast is always safe because the base class cannot have a bigger interface than the derived class. Therefore, every message you send through the base class interface is guaranteed to be accepted. But with a downcast, you don抰 really know that a shape (for example) is actually a circle. It could instead be a triangle or square or some other type.

To solve this problem, there must be some way to guarantee that a downcast is correct, so that you won’t accidentally cast to the wrong type and then send a message that the object can’t accept. This would be quite unsafe.

In some languages (like C++) you must perform a special operation in order to get a type-safe downcast, but in Java, every cast is checked! So even though it looks like you’re just performing an ordinary parenthesized cast, at run time this cast is checked to ensure that it is in fact the type you think it is. If it isn’t, you get a ClassCastException. This act of checking types at run time is called runtime type identification (RTTI).

# Summary

Polymorphism means “different forms.” In object-oriented programming, you have the same interface from the base class, and different forms using that interface: the different versions of the dynamically bound methods.

You’ve seen in this chapter that it’s impossible to understand, or even create, an example of polymorphism without using data abstraction and inheritance. Polymorphism is a feature that cannot be viewed in isolation (like a switch statement can, for example), but instead works only in concert, as part of the larger picture of class relationships.

To use polymorphism—and thus object-oriented techniques—effectively in your programs, you must expand your view of programming to include not just members and messages of an individual class, but also the commonality among classes and their relationships with each other. Although this requires significant effort, it’s a worthy struggle. The results are faster program development, better code organization, extensible programs, and easier code maintenance.









































