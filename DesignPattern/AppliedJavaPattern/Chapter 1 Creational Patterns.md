These patterns support one of the most common tasks in object-oriented programming—the creation of objects in a system. Most OO systems of any complexity require many objects to be instantiated over time, and these patterns support the creation process by helping to provide the following capabilities: 

* Generic instantiation – This allows objects to be created in a system without having to identify a specific class type in code. 
* Simplicity – Some of the patterns make object creation easier, so callers will not have to write large, complex code to instantiate an object. 
* Creation constraints – Some patterns enforce constraints on the type or number of objects that can be created within a system. 

The following patterns are discussed in this chapter: 

* Abstract Factory – To provide a contract for creating families of related or dependent objects without having to specify their concrete classes.   
* Builder – To simplify complex object creation by defining a class whose purpose is to build instances of another class. The Builder produces one main product, such that there might be more than one class in the product, but there is always one main class.   
* Factory Method – To define a standard method to create an object, apart from a constructor, but the decision of what kind of an object to create is left to subclasses.   
* Prototype – To make dynamic creation easier by defining classes whose objects can create duplicates of themselves.  
* Singleton – To have only one instance of this class in the system, while allowing other classes to get access to this instance.  

Of these patterns, the Abstract Factory and Factory Method are explicitly based on the concept of defining flexible object creation; they assume that the classes or interfaces to be created will be extended in an implementing system. As a result, these two patterns are frequently combined with other creational patterns.

# Abstract Factory

Also known as Kit, Toolkit

##### Pattern Properties  

* Type: Creational, Object
* Level: Component

##### Purpose  

To provide a contract for creating families of related or dependent objects without having to specify their concrete classes.

### Introduction

Suppose you plan to manage address and telephone information as part of a personal information manager (PIM) application. The PIM will act as a combination address book, personal planner, and appointment and contact manager, and will use the address and phone number data extensively.

You can initially produce classes to represent your address and telephone number data. Code these classes so that they store the relevant information and enforce business rules about their format. For example, all phone numbers in North America are limited to ten digits and the postal code must be in a particular format.

Shortly after coding your classes, you realize that you have to manage address and phone information for another country, such as the Netherlands. The Netherlands has different rules governing what constitutes a valid phone number and address, so you modify your logic in the Address and PhoneNumber classes to take the new country into account.

Now, as your personal network expands, you need to manage information from another foreign country... and another... and another. With each additional set of business rules, the base Address and PhoneNumber classes become even more bloated with code and even more difficult to manage. What's more, this code is brittle—with every new country added, you need to modify and recompile the classes to manage contact information.

It’s better to flexibly add these paired classes to the system; to take the general rules that apply to address and phone number data, and allow any number of possible foreign variations to be “loaded” into a system.

The Abstract Factory solves this problem. Using this pattern, you define an AddressFactory—a generic framework for producing objects that follow the general pattern for an Address and PhoneNumber. At runtime, this factory is paired with any number of concrete factories for different countries, and each country has its own version of Address and PhoneNumber classes.

Instead of going through the nightmare of adding functional logic to the classes, extend the Address to a DutchAddress and the PhoneNumber to a DutchPhoneNumber. Instances of both classes are created by a DutchAddressFactory. This gives greater freedom to extend your code without having to make major structural modifications in the rest of the system.  

### Applicability

Use the Abstract Factory pattern when:

* The client should be independent of how the products are created.  
* The application should be configured with one of multiple families of products.  
* Objects need to be created as a set, in order to be compatible.  
* You want to provide a collection of classes and you want to reveal just their contracts and their relationships, not their implementations.   

### Implementation

![alt](https://www.uml-diagrams.org/examples/class-example-abstract-factory.png)  

You typically use the following to implement the Abstract Factory pattern:  

* AbstractFactory – An abstract class or interface that defines the create methods for abstract products.   
* AbstractProduct – An abstract class or interface describing the general behavior of the resource that will be used by the application.
* ConcreteFactory – A class derived from the abstract factory . It implements create methods for one or more concrete products.
* ConcreteProduct – A class derived from the abstract product, providing an implementation for a specific resource or operating environment.

### Benefits and Drawbacks

An Abstract Factory helps to increase the overall flexibility of an application. This flexibility manifests itself both during design time and runtime. During design, you do not have to predict all future uses for an application. Instead, you create the generic framework and then develop implementations independently from the rest of the application. At runtime, the application can easily integrate new features and resources.  

A further benefit of this pattern is that it can simplify testing the rest of the application. Implementing a TestConcreteFactory and TestConcreteProduct is simple ; it can simulate the expected resource behavior.

To realize the benefits of this pattern, carefully consider how to define a suitably generic interface for the abstract product. If the abstract product is improperly defined, producing some of the desired concrete products can be difficult or impossible.

### Example

AddressFactory.java
```java
public interface AddressFactory {
  public Address createAddress();
  public PhoneNumber createPhoneNumber();
}
```

Note that the AddressFactory defines two factory methods, createAddress and createPhoneNumber. The methods produce the abstract products Address and PhoneNumber, which define methods that these products support.

Address.java

```java
public abstract class Address {
  private String street;
  private String city;
  private String region;
  private String postalCode;

  public static final String EOL_STRING = System.getProperty("line.separator");
  public static final String SPACE = " ";

  public String getStreet() {
    return street;
  }

  public String getCity() {
    return city;
  }

  public String getPostalCode() {
    return postalCode;
  }
  public String getRegion() {
    return region;
  }

  public abstract String getCountry();

  public String getFullAddress() {
    return street + EOL_STRING +
    city + SPACE + postalCode + EOL_STRING;
  }

}
```

PhoneNumber.java
```java
public abstract class PhoneNumber{
  private String phoneNumber;
  public abstract String getCountryCode();

  public String getPhoneNumber() {
  return phoneNumber;
}

  public void setPhoneNumber(String newNumber) {
    try {
      Long.parseLong(newNumber);
      phoneNumber = newNumber;
    }
    catch (NumberFormatException exc) {
    }
  }
}
```

Address and PhoneNumber are abstract classes in this example, but could easily be defined as interfaces if you did not need to define code to be used for all concrete products.

To provide concrete functionality for the system, you need to create Concrete Factory and Concrete Product classes. In this case, you define a class that implements AddressFactory, and subclass the Address and PhoneNumber classes. The three following classes show how to do this for U.S. address information.

USAddressFactory.java
```java
public class USAddressFactory implements AddressFactory{
  public Address createAddress(){
    return new USAddress();
  }

  public PhoneNumber createPhoneNumber(){
    return new USPhoneNumber();
  }
}
```

USAddress.java

```java
public class USAddress extends Address{
  private static final String COUNTRY = "UNITED STATES";
  private static final String COMMA = ",";

  public String getCountry(){ return COUNTRY; }

  public String getFullAddress(){
    return getStreet() + EOL_STRING +
      getCity() + COMMA + SPACE + getRegion() +
      SPACE + getPostalCode() + EOL_STRING +
      COUNTRY + EOL_STRING;
  }
}
```


USPhoneNumber.java
```java
public class USPhoneNumber extends PhoneNumber{
  private static final String COUNTRY_CODE = "01";
  private static final int NUMBER_LENGTH = 10;

  public String getCountryCode(){ return COUNTRY_CODE; }

  public void setPhoneNumber(String newNumber){
    if (newNumber.length() == NUMBER_LENGTH){
      super.setPhoneNumber(newNumber);
    }
  }
}
```

The generic framework from AddressFactory, Address, and PhoneNumber makes it easy to extend the system to support additional countries. With each additional country, define an additional Concrete Factory class and a matching Concrete Product class. These are files for French address information.

FrenchAddressFactory.java

```java
public class FrenchAddressFactory implements AddressFactory{
 public Address createAddress(){
  return new FrenchAddress();
  }

  public PhoneNumber createPhoneNumber(){
    return new FrenchPhoneNumber();
  }
}
```

FrenchAddress.java
```java
public class FrenchAddress extends Address{
 private static final String COUNTRY = "FRANCE";

 public String getCountry(){ return COUNTRY; }

 public String getFullAddress(){
  return getStreet() + EOL_STRING +
    getPostalCode() + SPACE + getCity() +
    EOL_STRING + COUNTRY + EOL_STRING;
  }
}
```

FrenchPhoneNumber.java
```java
public class FrenchPhoneNumber extends PhoneNumber{
  private static final String COUNTRY_CODE = "33";
  private static final int NUMBER_LENGTH = 9;

  public String getCountryCode(){ return COUNTRY_CODE; }

  public void setPhoneNumber(String newNumber){
    if (newNumber.length() == NUMBER_LENGTH){
      super.setPhoneNumber(newNumber);
    }
  }
}
```

