https://hashnode.com/post/clean-code-summary-part-1-naming-ciymphs8x00002w53maa5d30d  

# Part 1 Naming

> Clean Code is code that has been taken care of to be descriptive and readable..

* use intention revealing names: ```radius``` instead of ```r```.
* don't use abbreviations.
* name is better than nameString (unnecessary information).
* clear distinctions: avoid ```getAccount()```, ```getAccounts()```, ```getAccountInfo()``` in same class, or e.g. avoid ```get()```, ```fetch()```, ```retrieve()```.
* use pronouncable and meaningfull names.
* Serchable names ( can be found easily by search tools as per their meaning).
* Avoid encodings (coded names).
* minimize the usage of prefixes like ```addr_name```.
* Classes and objects should have noun or noun phrase names like ```Customer```, ```Account```.
* Methods should have verb or verb phrase names likepostPayment, deletePage, or save.
* Don't use cute or humourous or witty names.
* Accessors, mutators, and predicates should be named for their value and prefixed with ```get```, ```set```, and ```is```, according to the javabean standard.
* Use names related to the solution applied like the pattern used e.g. ```factory```, ```builder```.
* If not possible relate it to the problem being solved, like relate variables to address e.g. ```addressName```, ```addressNumber``` etc..
* Add meaningful context, like creating a class which will hold the variables that are being used in the same context, this will make the variables belong to that class and thus have contextual meaning.  

# Part Functions (Methods)

* Functions should be small; one line, two-three or four maximum.
* This means that if satatements, for loops and while loops, should be one line long, obviously this line should be calling another function.
* For switch statements, every case should have one line, usualy a call to another function.
* Indentation level in functions should not be bigger than one or two levels.
* Functions should do one thing only, not to make multiple things, and that should be reflected on their names, e.g., don't make a ```saveAndCloseDiaolg()``` function, instead, make two functions: ```save()```, and ```closeDialog()```.

> Functions should do only one thing

* In the same context, they shouldn't have side effects, meaning, they should not lead to another part or initialize another thing etc.. e.g. the save() function should only do the saving part, it should never do anything else.  
* Function mames should be descriptive, don't be afraid to make them very long as long as they are descriptive.  

> You know you are working on clean code when each routine turns out to be pretty much what you expected, ward's principle

* Be consistent in naming the functions, meaning, don't make ```includeName()```, ```addAdress()```, instead: ```includeName()```, ```includeAdress()```, Or, ```addName()```, ```addAdress()```.
* Code should be like telling a story, can be read as a top down narrative, every function leading to the next one smoothly .  
* In other words: Every function should have one level of abstraction, the other level should be in another function that follows the first one, like in the following narration: To include the setups and teardowns, we include setups, then we include the test page content, and then we include the teardowns. To include the setups, we include the suite setup if this is a suite, then we include the regular setup. To include the suite setup, we search the parent hierarchy for the SuiteSetUp page and add an include statement with the path of that page. To search the parent. . 

```java
private void includeSetupAndTeardownPages() throws Exception {
            includeSetupPages();
            includePageContent();
            includeTeardownPages();
            updatePageContent();
}

private void includeSetupPages() throws Exception {
            if (isSuite){
            includeSuiteSetupPage();}
            includeSetupPage();  
}

private void includeSuiteSetupPage() throws Exception {
            include(SuiteResponder.SUITE_SETUP_NAME, "-setup");  
}

private void includeSetupPage() throws Exception {
        include("SetUp", "-setup");  
} 
```

> "Master programmers think of systems as stories to be told rather than programs to be written." Author.

* We should never use output arguments in functions, i.e. functions that takes a variable as its argument, then change its * state, it is very confusing.
* It is better that functions shouldn't have arguments at all!, or at least one argument, three arguments maximum.
* We can convert two arguments of a 3 or more argument function to be part of a class like e.g.:

```java
Circle makeCircle(double x, double y, double radius);
Circle makeCircle(Point center, double radius);
```

* Or we can use argument lists if all arguments are of the same type:

```
public String format(String format, Object... args)
```

* Don't return a boolean as a validation for the successful operation of a function.  
* A try and catch block should exist alone in one function i.e. error handling is one thing to do, as we have said previously, functions should do only one thing.   

> "When I write functions, they come out long and complicated. They have lots of indenting and nested loops. They have long argument lists. The names are arbitrary, and there is duplicated code. But I also have a suite of unit tests that cover every one of those clumsy lines of code. So then I massage and refine that code, splitting out functions, changing names, eliminating duplication. I shrink the methods and reorder them. Sometimes I break out whole classes, all the while keeping the tests passing. In the end, I wind up with functions that follow the rules I’ve laid down in this chapter. I don’t write them that way to start. I don’t think anyone could." -the author

#  Part 3 Comments

In this chapter, Uncle Bob introduces a new mind blowing concept that most programmers might not be used to: Comments are a necessary evil, in his book he says:

> Nothing can be quite so helpful as a well-placed comment. Nothing can clutter up a module more than frivolous dogmatic comments. Nothing can be quite so damaging as an oldcrufty comment that propagates lies and misinformation.

And Why is that? because:

> Programmers can’t realistically maintain comments.

* Comments are a necessary evil, we should be writing functions in a descriptive way, so that we can avoid writing comments at all, so the ideal case is that there should be no comments at all!.
* Comments should be used only as an explanation , never add obsolete code as a comment, instead remove it and depend on version control systems to preserve the history of the code.
* TODO comments are ok because the IDE can find them easily before ending the project.
* Don't write redundunt comments, if the code is self explanatory no need to add comments.
* Its a wrong concept that every function should have javadoc for documentation purpose, its better to have descriptive names than having a javadoc.
* Instead of using comments as function headers, replace them with a descreptive name for the function if possible.
* Instead of writing a comment to explain a long line of code, divide this line into more simpler lines by using local variables so as to make the code more descriptive and readable.
* Position markers like this:```java\\The following are the private methods\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\``` are ok, as long as they are not execcisvely used, otherwise the eyes will be trained to ignore them automatically, use them rarely in cases you need to put an important distinction.
* Attribute comments like: ```/* added by john smith on 1/10..*/``` are ok but not to be a MISLEADING info or to be execcisve.
* Again, NEVER retain commented out code
* Don't put in a comment non local information, i.e. information that are not in the same context of the line,like e.g. something related to the whole program or to the whole module etc..
* Don’t put interesting historical discussions or irrelevant descriptions of details into your comments
* Don't put comments that have poor or no connection to the code it explains.  

# Part 4 - Formatting

* Vertical Formatting: The file length in lines should be around the size of : 200-500 lines, this is not mandatory off course , but to be followed whenever possible.  
* Vertical Opennes: Methods should be separated by blank lines, also lines of code that differ in functionality should be separated by blank lines.  

> i.e: Opennes separates concepts 

* On the other hand: Vertical density (no blank lines) implies close link or assossiation.  
* Vertical distance: Concepts that are closely related should be kept vertically close to each other , e.g. methods of similar functions or of related function should be grouped and ordered together We want to avoid forcing our readers to hop around through our source files and classes.  
* Variable declarations inside methods should be as close as possible to their usages, e.g.:You declare a variable and use it directly in the following line of code.  

```java
      StringBuilder name = new StringBuilder();
      name.append("John");
```

* Instance variable declarations should be in one location and most prefeably on the top of the class, or at least in the bottom.  
* Dependent Functions: If one function calls another, they should be vertically close, and the caller should be above the callee, if at all possible.  
* Conceptual Affinity: Certain bits of code want to be near other bits, The stronger that affinity, the less vertical distance there should be between them. Affinity might be caused because a group of functions perform a similar operation.
* Horizontal Formatting: lines should be of the sizes 100-120-max 200 characters.  
* Horizontal Opennes: The following example shows the use of spaces to add horizontal opennes to the code, Pay attention how we used the horizontal spaces:

```java
x = 1;
X += 1;    
count++;
public void method(Argument arg, Argument2 arg2) {
    y = -b / (2\*a); y = c\*2 +y\*5;} //because multiplication is of higher precedance than addition
```

* Indentation should be used to show different levels of hierarchy in the file.
* Don't break the indentation rule even in the case of short If statements or short methods.  

# Part 5: Objects and Data Structures:



      


