## 3.2 JUnit Asserts

As we've seen, there are some helper methods that assist you in determining whether a method under test is performing correctly or not. Generically, we call all these methods __asserts__. They let you assert that some condition is true; that two bits of data are equal, or not, and so on. We'll take a look at each one of the assert methods that JUnit provides next.

All of the following methods will record failures (that's when the assertion is false) or errors (that's when you get an unexpected exception), and report these through the JUnit classes. For the text version, that means an error message will be printed to the console. The GUI version will show a red bar and supporting details to indicate a failure.

When a failure or error occurs, execution of the current test method is aborted. Other tests within the same test class will still be run.

Asserts are the fundamental building block for unit tests; the JUnit library provides a number of different forms of assert.

```
assertEquals([String message], expected, actual)
```

This is the most-often used form of assert. expected is a value you hope to see (typically hard-coded), and actual is a value actually produced by the code under test. message is an optional message that will be reported in the event of a failure. You can omit the message argument and simply provide the expected and actual values.

Any kind of object may be tested for equality; the appropriate equals method will be used for the comparison. In particular, you can compare the contents of strings using this method. Different method signatures are also provided for all the native types (boolean, int, short, etc.) and Object. Be aware that the equals method for native arrays, however, does not compare the contents of the arrays, just the array reference itself, which is probably not what you want.

```
assertEquals([String message], expected, actual, tolerance)
```

Computers cannot represent all foating-point numbers exactly, and will usually be off a little bit. Because of this, if you are using an assert to compare foating point numbers (foats or doubles in Java), you need to specify one additional piece of information, the tolerance. This specifies just how close to .equals. you need the result to be. For most business applications, 4 or 5 decimal places is probably enough. For scientific apps, you may need much greater precision.

```
assertNull([String message], java.lang.Object object)
assertNotNull([String message], java.lang.Object object)
```

Asserts that the given object is null (or not null), failing otherwise. The message is optional.

```
assertSame([String message], expected, actual)
```

Asserts that expected and actual refer to the same object, and fails the test if they do not. The message is optional.

```
assertNotSame([String message], expected, actual)
```

Asserts that expected and actual do not refer to the same object, and fails the test if they are the same object. The message is optional.

```
assertTrue([String message], boolean condition)
```

Asserts that the given boolean condition is true, otherwise the test fails. The message is optional.

```
assertFalse([String message], boolean condition)
```

Asserts that the given boolean condition is false, otherwise the test fails. The message is optional.

```
fail([String message])
```

Fails the test immediately, with the optional message. Often used to mark sections of code that should not be reached (for instance, after an exception is expected).

### Using asserts

You usually have multiple asserts in a given test method, as you prove various aspects and relationships of the method(s) under test. When an assert fails, that test method will be aborted - the remaining assertions in that method will not be executed this time. But that shouldn't be of any concern; you have to fix the failing test before you can proceed anyway. And you fix the next failing test. And the next. And so on.

You should normally expect that all tests pass all of the time. In practice, that means that when you introduce a bug, only one or two tests fail. Isolating the problem is usually pretty easy in that environment.

Under no circumstances should you continue to add features when there are failing tests! Fix any test as soon as it fails, and keep all tests passing all of the time.

To maintain that discipline, you'll need an easy way to run all the testsor to run groups of tests, particular subsystems, and so on.

## 3.3 JUnit Framework



