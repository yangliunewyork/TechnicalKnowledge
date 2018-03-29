* https://www.tutorialspoint.com/nodejs/nodejs_callbacks_concept.htm

### First-class object/citizen
In programming language design, a first-class citizen (also object, entity, or value) in a given programming language is an entity which supports all the operations generally available to other entities. These operations typically include being passed as a parameter, returned from a function, and assigned to a variable.

Another definition:A first class object is an entity that can be dynamically created, destroyed, passed to a function, returned as a value, and have all the rights as other variables in the programming language have.

##### In JavaScript, functions are first-class objects
That is, functions are of the type Object and they can be used in a first-class manner like any other object (String, Array, Number, etc.) since they are in fact objects themselves. They can be “stored in variables, passed as arguments to functions, created within functions, and returned from functions”.

Because functions are first-class objects, we can pass a function as an argument in another function and later execute that passed-in function or even return it to be executed later. This is the essence of using callback functions in JavaScript.
Callback functions are derived from a programming paradigm known as functional programming. At a fundamental level, functional programming specifies the use of functions as arguments. Functional programming was—and still is, though to a much lesser extent today—seen as an esoteric technique of specially trained, master programmers.

##### What is a Callback or Higher-order Function?
A callback function, also known as a higher-order function, is a function that is passed to another function (let’s call this other function “otherFunction”) as a parameter, and the callback function is called (or executed) inside the otherFunction. A callback function is essentially a pattern (an established solution to a common problem), and therefore, the use of a callback function is also known as a callback pattern.

```
var friends = ["Mike", "Stacy", "Andy", "Rick"];
friends.forEach(function (eachName, index){
console.log(index + 1 + ". " + eachName); // 1. Mike, 2. Stacy, 3. Andy, 4. Rick​
});
```

##### How Callback Functions Work?
We can pass functions around like variables and return them in functions and use them in other functions. When we pass a callback function as an argument to another function, we are only passing the function definition. We are not executing the function in the parameter. In other words, we aren’t passing the function with the trailing pair of executing parenthesis () like we do when we are executing a function.
And since the containing function has the callback function in its parameter as a function definition, it can execute the callback anytime.
Note that the callback function is not executed immediately. It is “called back” (hence the name) at some specified point inside the containing function’s body.
```
//The anonymous function is not being executed there in the parameter. 
//The item is a callback function
$("#btn_1").click(function() {
  alert("Btn 1 Clicked");
});
```

##### Callback Functions Are Closures
When we pass a callback function as an argument to another function, the callback is executed at some point inside the containing function’s body just as if the callback were defined in the containing function. This means the callback is a closure. As we know, closures have access to the containing function’s scope, so the callback function can access the containing functions’ variables, and even the variables from the global scope.

## What is Callback?
Callback is an asynchronous equivalent for a function. A callback function is called at the completion of a given task. Node makes heavy use of callbacks. All the APIs of Node are written in such a way that they support callbacks.

For example, a function to read a file may start reading file and return the control to the execution environment immediately so that the next instruction can be executed. Once file I/O is complete, it will call the callback function while passing the callback function, the content of the file as a parameter. So there is no blocking or wait for File I/O. This makes Node.js highly scalable, as it can process a high number of requests without waiting for any function to return results.

#### Blocking Code Example
```
var fs = require("fs");

var data = fs.readFileSync('input.txt');

console.log(data.toString());
console.log("Program Ended");
```

Output:
```
Tutorials Point is giving self learning content
to teach the world in simple and easy way!!!!!
Program Ended
```

#### Non-Blocking Code Example
```
var fs = require("fs");

fs.readFile('input.txt', function (err, data) {
   if (err) return console.error(err);
   console.log(data.toString());
});

console.log("Program Ended");
```

Output :
```
Program Ended
Tutorials Point is giving self learning content
to teach the world in simple and easy way!!!!!
```

These two examples explain the concept of blocking and non-blocking calls.

* The first example shows that the program blocks until it reads the file and then only it proceeds to end the program.

* The second example shows that the program does not wait for file reading and proceeds to print "Program Ended" and at the same time, the program without blocking continues reading the file.

Thus, a blocking program executes very much in sequence. From the programming point of view, it is easier to implement the logic but non-blocking programs do not execute in sequence. In case a program needs to use any data to be processed, it should be kept within the same block to make it sequential execution.
