> Access control (or implementation hiding) is about not getting it right the first time.

All good writers including those who write software know that a piece of work isn't good until it's been rewritten, often many times. If you leave a piece of code in a drawer for a while and come back to it, you may see a much better way to do it. This is one of the prime motivations for refactoring, which rewrites working code in order to make it more readable, understandable, and thus maintainable.

There is a tension, however, in this desire to change and improve your code. There are often consumers (client programmers) who rely on some aspect of your code staying the same. So you want to change it; they want it to stay the same. __Thus a primary consideration in object-oriented design is to separate the things that change from the things that stay the same__.

This is particularly important for libraries. Consumers of that library must rely on the part they use, and know that they won't need to rewrite code if a new version of the library comes out. On the flip side, the library creator must have the freedom to make modifications and improvements with the certainty that the client code won't be affected by those changes.

To solve this problem, Java provides access specifiers to allow the library creator to say what is available to the client programmer and what is not. The levels of access control from “most access” to “least access” are public, protected, package access (which has no keyword), and private. From the previous paragraph you might think that, as a library designer, you’ll want to keep everything as “private” as possible, and expose only the methods that you want the client programmer to use. This is exactly right, even though it’s often counterintuitive for people who program in other languages (especially C) and who are used to accessing everything without restriction.

The concept of a library of components and the control over who can access the components of that library is not complete, however. There's still the question of how the components are bundled together into a cohesive library unit. This is controlled with the __package__ keyword in Java, and the access specifiers are affected by whether a class is in the same package or in a separate package.


## package: the library unit
A package contains a group of classes, organized together under a single namespace.
When you create a source-code file for Java, it’s commonly called a __compilation unit__ (sometimes a __translation unit__). __Each compilation unit must have a name ending in .java, and inside the compilation unit there can be a public class that must have the same name as the file (including capitalization, but excluding the .java file name extension). There can be only one public class in each compilation unit; otherwise, the compiler will complain. If there are additional classes in that compilation unit, they are hidden from the world outside that package because they’re not public, and they comprise “support” classes for the main public class.__

#### Code organization
__When you compile a .java file, you get an output file for each class in the .java file. Each output file has the name of a class in the .java file, but with an extension of .class. Thus you can end up with quite a few .class files from a small number of .java files. If you’ve programmed with a compiled language, you might be used to the compiler spitting out an intermediate form (usually an “obj” file) that is then packaged together with others of its kind using a linker (to create an executable file) or a librarian (to create a library). That’s not how Java works. A working program is a bunch of .class files, which can be packaged and compressed into a Java ARchive (JAR) file (using Java’s jar archiver). The Java interpreter is responsible for finding, loading, and interpreting2 these files.__

A library is a group of these class files. Each source file usually has a public class and any number of non-public classes, so there's one public component for each source file. If you want to say that all these components (each in its own separate .java and .class files) belong together, that's where the __package__ keyword comes in.

It’s worth keeping in mind that what the __package__ and __import__ keywords allow you to do, as a library designer, is to divide up the single global namespace so you won’t have clashing names, no matter how many people get on the Internet and start writing classes in Java.


Java provides access specifiers to allow the library creator to say what is available to the client programmer and what is not. The levels of access control from “most access” to “least access” are __public, protected, package access (which has no keyword), and private__. 

#### Creating unique package names
You might observe that, since a package never really gets packaged into a single file, a package can be made up of many __.class__ files, and things could get a bit cluttered. To prevent this, a logical thing to do is to place all the .class files for a particular package into a single directory; that is, use the hierarchical file structure of the operating system to your advantage. This is one way that Java references the problem of clutter; you'll see the other way later when the __jar__ utility is introduced.

Collecting the package files into a single subdirectory solves two other problems: creating unique package names, and finding those classes that might be buried in a directory structure someplace. This is accomplished by encoding the path of the location of the .class file into the name of the package. __By convention, the first part of the package name is the reversed Internet domain name of the creator of the class. Since Internet domain names are guaranteed to be unique, if you follow this convention, your package name will be unique and you’ll never have a name clash.__ (That is, until you lose the domain name to someone else who starts writing Java code with the same path names as you did.) Of course, if you don’t have your own domain name, then you must fabricate an unlikely combination (such as your first and last name) to create unique package names. If you’ve decided to start publishing Java code, it’s worth the relatively small effort to get a domain name.

The second part of this trick is resolving the package name into a directory on your machine, so that when the Java program runs and it needs to load the .class file, it can locate the directory where the .class file resides.


__The Java interpreter proceeds as follows. First, it finds the environment variable CLASSPATH (set via the operating system, and sometimes by the installation program that installs Java or a Java-based tool on your machine). CLASSPATH contains one or more directories that are used as roots in a search for .class files. Starting at that root, the interpreter will take the package name and replace each dot with a slash to generate a path name off of the CLASSPATH root (so package foo.bar.baz becomes foo\bar\baz or foo/bar/baz or possibly something else, depending on your operating system). This is then concatenated to the various entries in the CLASSPATH. That’s where it looks for the .class file with the name corresponding to the class you’re trying to create. (It also searches some standard directories relative to where the Java interpreter resides.)__

To understand this, consider my domain name, which is MindView.net. By reversing this and making it all lowercase, net.mindview establishes my unique global name for my classes. (The com, edu, org, etc., extensions were formerly capitalized in Java packages, but this was changed in Java 2 so the entire package name is lowercase.) I can further subdivide this by deciding that I want to create a library named simple, so I抣l end up with a package name:

``` 
package net.mindview.simple; 
```


There’s a variation when using JAR files, however. You must put the actual name of the JAR file in the classpath, not just the path where it’s located. So for a JAR named grape.jar your classpath would include:
```
CLASSPATH=.;D:\JAVA\LIB;C:\flavors\grape.jar
```

When the compiler encounters the import statement for the simple library, it begins searching at the directories specified by CLASSPATH, looking for subdirectory net/mindview/simple, then seeking the compiled files of the appropriate names (Vector.class for Vector, and List.class for List). Note that both the classes and the desired methods in Vector and List must be public.

#### Using imports to change behavior
A feature that is missing from Java is C’s conditional compilation, which allows you to change a switch and get different behavior without changing any other code. The reason such a feature was left out of Java is probably because it is most often used in C to solve cross- platform issues: Different portions of the code are compiled depending on the target platform. Since Java is intended to be automatically cross-platform, such a feature should not be necessary.

However, there are other valuable uses for conditional compilation. A very common use is for debugging code. The debugging features are enabled during development and disabled in the shipping product. You can accomplish this by changing the package that’s imported in order to change the code used in your program from the debug version to the production version. This technique can be used for any kind of conditional code.

#### Package caveat
It's worth remembering that anytime you create a package, you implicitly specify a directory structure when you give the package a name. The package must live in the directory indicated by its name, which must be a directory that is searchable starting from the CLASSPATH. Experimenting with the package keyword can be a bit frustrating at first, because unless you adhere to the package-name to directory-path rule, you'll get a lot of mysterious runtime messages about not being able to find a particular class, even if that class is sitting there in the same directory. If you get a message like this, try commenting out the package statement, and if it runs, you抣l know where the problem lies.

Note that compiled code is often placed in a different directory than source code, but the path to the compiled code must still be found by the JVM using the CLASSPATH.

## Java access specifiers


## Summary
In any relationship it’s important to have boundaries that are respected by all parties involved. When you create a library, you establish a relationship with the user of that library—the client programmer—who is another programmer, but one using your library to build an application or a bigger library.

Without rules, client programmers can do anything they want with all the members of a class, even if you might prefer they don’t directly manipulate some of the members. Everything’s naked to the world.

It is estimated that a C programming project begins to break down somewhere between 50K and 100K lines of code because C has a single namespace, and names begin to collide, causing extra management overhead. In Java, the package keyword, the package naming scheme, and the import keyword give you complete control over names, so the issue of name collision is easily avoided.
There are two reasons for controlling access to members. The first is to keep users’ hands off portions that they shouldn’t touch. These pieces are necessary for the internal operations of the class, but not part of the interface that the client programmer needs. So making methods and fields private is a service to client programmers, because they can easily see what’s important to them and what they can ignore. It simplifies their understanding of the class.

The second and most important reason for access control is to allow the library designer to change the internal workings of the class without worrying about how it will affect the client programmer. You might, for example, build a class one way at first, and then discover that restructuring your code will provide much greater speed. If the interface and implementation are clearly separated and protected, you can accomplish this without forcing client programmers to rewrite their code. Access control ensures that no client programmer becomes dependent on any part of the underlying implementation of a class.

The public interface to a class is what the user does see, so that is the most important part of the class to get “right” during analysis and design. Even that allows you some leeway for change. If you don’t get the interface right the first time, you can add more methods, as long as you don’t remove any that client programmers have already used in their code.

Notice that access control focuses on a relationship—and a kind of communication—between a library creator and the external clients of that library. There are many situations where this is not the case. For example, you are writing all the code yourself, or you are working in close quarters with a small team and everything goes into the same package. These situations have a different kind of communication, and rigid adherence to access rules may not be optimal. Default (package) access may be just fine.

