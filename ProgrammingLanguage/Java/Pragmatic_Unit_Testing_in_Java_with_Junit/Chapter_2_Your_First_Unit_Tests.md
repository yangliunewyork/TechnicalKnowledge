To check if code is behaving as you expect, you use an assertion, a simple method call that veries that something is true. For instance, the method assertTrue checks that the given boolean condition is true, and fails the current test if it is not. It might be implemented like the following.

```java
public void assertTrue(boolean condition) {
  if (!condition) { 
    abort();
  }
}
```

You could use this assert to check all sorts of things, including whether numbers are equal to each other:

```java
int a = 2;
assertTrue(a == 2);
```

If for some reason a does not equal 2 when the assertTrue() is called, then the program will abort.

Since we check for equality a lot, it might be easier to have an assert just for numbers. To check that two integers are equal, for instance, we could write a method that takes two integer parameters:

```java
public void assertEquals(int a, int b) {
  assertTrue(a == b);
}
```

__Finally, a reminder: all code - test or production - should be clear and simple. Test code especially must be easy to understand, even at the expense of performance or verbosity.__

