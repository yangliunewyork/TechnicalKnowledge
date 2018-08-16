Mockito is a mocking framework, JAVA-based library that is used for effective unit testing of JAVA applications. Mockito is used to mock interfaces so that a dummy functionality can be added to a mock interface that can be used in unit testing.

# Mockito - Overview

### What is Mocking?

Mocking is a way to test the functionality of a class in isolation. Mocking does not require a database connection or properties file read or file server read to test a functionality. Mock objects do the mocking of the real service. A mock object returns a dummy data corresponding to some dummy input passed to it.

### Mockito

Mockito facilitates creating mock objects seamlessly. It uses Java Reflection in order to create mock objects for a given interface. Mock objects are nothing but proxy for actual implementations.

Consider a case of Stock Service which returns the price details of a stock. During development, the actual stock service cannot be used to get real-time data. So we need a dummy implementation of the stock service. Mockito can do the same very easily, as its name suggests.

### Benefits of Mockito

* No Handwriting − No need to write mock objects on your own.
* Refactoring Safe − Renaming interface method names or reordering parameters will not break the test code as Mocks are created at runtime.
* Return value support − Supports return values.
* Exception support − Supports exceptions.
* Order check support − Supports check on order of method calls.
* Annotation support − Supports creating mocks using annotation.

