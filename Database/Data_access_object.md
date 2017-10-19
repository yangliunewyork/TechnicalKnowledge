In computer software, a __data access object (DAO)__ is an object that provides an abstract interface to some type of database or other persistence mechanism. By mapping application calls to the persistence layer, the DAO provides some specific data operations without exposing details of the database. This isolation supports the __Single responsibility principle__. It separates what data access the application needs, in terms of domain-specific objects and data types (the public interface of the DAO), from how these needs can be satisfied with a specific DBMS, database schema, etc. (the implementation of the DAO).

Although this design pattern is equally applicable to most programming languages, most types of software with persistence needs, and most types of databases, it is traditionally associated with Java EE applications and with relational databases (accessed via the JDBC API because of its origin in Sun Microsystems' best practice guidelines "Core J2EE Patterns" for that platform).

### Advantages

The advantage of using data access objects is the relatively simple and rigorous separation between two important parts of an application that can but should not know anything of each other, and which can be expected to evolve frequently and independently. Changing business logic can rely on the same DAO interface, while changes to persistence logic do not affect DAO clients as long as the interface remains correctly implemented. All details of storage are hidden from the rest of the application (see information hiding). Thus, possible changes to the persistence mechanism can be implemented by just modifying one DAO implementation while the rest of the application isn't affected. DAOs act as an intermediary between the application and the database. They move data back and forth between objects and database records. Unit testing the code is facilitated by substituting the DAO with a test double in the test, thereby making the tests non-dependent on the persistence layer.


### Disadvantages

Potential disadvantages of using DAO include __leaky abstraction__, code duplication, and __abstraction inversion__. In particular, the abstraction of the DAO as a regular Java object can hide the high cost of each database access, and can also force developers to trigger multiple database queries to retrieve information that could otherwise be returned in a single operation with normal SQL set operations. If an application requires multiple DAOs, one might find oneself repeating essentially the same create, read, update, and delete code for each DAO. This boiler-plate code may be avoided however, by implementing a generic DAO that handles these common operations.

> Leaky abstraction : In software development, a leaky abstraction is an abstraction that exposes details and limitations of its underlying implementation to its users that should ideally be hidden away. Leaky abstractions are considered problematic, since the purpose of abstractions is to manage complexity by concealing unnecessary details from the user.

> Abstraction inversion : In computer programming, abstraction inversion is an anti-pattern arising when users of a construct need functions implemented within it but not exposed by its interface. The result is that the users re-implement the required functions in terms of the interface, which in its turn uses the internal implementation of the same functions. This may result in implementing lower-level features in terms of higher-level ones, thus the term 'abstraction inversion'.






