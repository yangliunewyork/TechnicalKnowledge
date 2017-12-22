In computer science, a __symbol table__ is a data structure used by a language translator such as a compiler or interpreter, where each identifier (a.k.a. symbol) in a program's source code is associated with information relating to its declaration or appearance in the source.

A symbol table may only exist during the translation process, or it may be embedded in the output of that process, such as in an ABI object file for later exploitation. For example, it might be used during an interactive debugging session, or as a resource for formatting a diagnostic report during or after execution of a program.

#### Implementation

Numerous data structures are available for implementing tables. Trees, linear lists and self-organizing lists can all be used to implement a symbol table. The symbol table is accessed by most phases of a compiler, beginning with lexical analysis, and continuing through optimization.

A compiler may use one large symbol table for all symbols or use separated, hierarchical symbol tables for different scopes.

A common data structure used to implement symbol tables is the hash table. The time for searching in hash tables is independent of the number of elements stored in the table, so it is efficient for a large number of elements. It also simplifies[how?] the classification of literals in tabular format.

As the lexical analyser spends a great proportion of its time looking up the symbol table, this activity has a crucial effect on the overall speed of the computer. A symbol table must be organised in such a way that entries can be found as quick as possible. Hash tables are used to organise a symbol table, where the keyword or identifier is 'hashed' to produce an array subscript. Collisions are inevitable in a hash table, and a common way of handling them is to store the synonym in the next available free space in the table.

