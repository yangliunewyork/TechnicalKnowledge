### What is Interpreter pattern?

![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/b/bc/Interpreter_UML_class_diagram.svg/804px-Interpreter_UML_class_diagram.svg.png)

Interpreter Design Pattern: Interpreter pattern provides a way to evaluate language grammar or expression. 
This pattern involves implementing an expression interface which tells to interpret a particular context. 
In computer programming, the interpreter pattern is a design pattern that specifies how to evaluate sentences 
in a language. The basic idea is to have a class for each symbol (terminal or nonterminal) in a specialized 
computer language. The syntax tree of a sentence in the language is an instance of the composite pattern and 
is used to evaluate (interpret) the sentence for a client. In computer science, an abstract syntax tree (AST), 
or just syntax tree, is a tree representation of the abstract syntactic structure of source code written in 
a programming language. Each node of the tree denotes a construct occurring in the source code. 
The syntax is "abstract" in not representing every detail appearing in the real syntax.
A parse tree or parsing tree or derivation tree or (concrete) syntax tree is an ordered, 
rooted tree that represents the syntactic structure of a string according to some context-free grammar. 
The term parse tree itself is used primarily in computational linguistics; in theoretical syntax 
the term syntax tree is more common. Parse trees are distinct from the abstract syntax trees used in computer programming, 
in that their structure and elements more concretely reflect the syntax of the input language. 

### Intent
Given a language, define a represention for its grammar along with aninterpreter that uses the representation to interpret sentences in thelanguage. 

### Participants
1. AbstractExpression
* declares an abstract Interpret operation that is common to all nodes in the abstract syntax tree.
2. TerminalExpression
* implements an Interpret operation associated with terminal symbols in the grammar.
* an instance is required for every terminal symbol in a sentence.
3. NonterminalExpression
* one such class is required for every rule R ::= R1 R2 ... Rn in the grammar.
* maintains instance variables of type AbstractExpression for each of the symbols R1 through Rn.
* implements an Interpret operation for nonterminal symbols in the grammar. Interpret typically calls itself recursively on the variables representing R1 through Rn.
4. Context
* contains information that's global to the interpreter.
5· Client
* builds (or is given) an abstract syntax tree representing a particular sentence in the language that the grammar defines. The abstract syntax tree is assembled from instances of the NonterminalExpression and TerminalExpression classes.
* invokes the Interpret operation. 

### Applicability
Use the Interpreter pattern when there is a language to interpret, and you can represent statements in the language as abstract syntax trees.The Interpreter pattern works best when
* the grammar is simple. For complex grammars, the class hierarchy forthe grammar becomes large and unmanageable. Tools such as parsergenerators are a better alternative in such cases. They can interpretexpressions without building abstract syntax trees, which can savespace and possibly time.
* efficiency is not a critical concern. The most efficient interpreters are usually not implemented by interpreting parse trees directlybut by first translating them into another form. For example, regularexpressions are often transformed into state machines. But even then,the translator can be implemented by the Interpreter pattern, so the pattern is still applicable. 

### Collaborations
* The client builds (or is given) the sentence as an abstract syntaxtree of NonterminalExpression and TerminalExpression instances. Thenthe client initializes the context and invokes the Interpretoperation.
* Each NonterminalExpression node defines Interpret in terms ofInterpret on each subexpression. The Interpret operation of each TerminalExpression defines the base case in the recursion.
* The Interpret operations at each node use the context tostore and access the state of the interpreter. 
