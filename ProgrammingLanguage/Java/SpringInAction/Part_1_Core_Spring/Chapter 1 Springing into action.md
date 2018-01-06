## 1.1 Simplifying Java development

To back up its attack on Java complexity, Spring employs four key strategies:

* Lightweight and minimally invasive development with POJOs  
* Loose coupling through DI and interface orientation  
* Declarative programming through aspects and common conventions   
* Eliminating boilerplate code with aspects and templates  

### 1.1.1 Unleashing the power of POJOs

>  A __plain old Java object (POJO)__ is an ordinary Java object, not bound by any special restriction and not requiring any class path. The term was coined by Martin Fowler, Rebecca Parsons and Josh MacKenzie in September 2000: "We wondered why people were so against using regular objects in their systems and concluded that it was because simple objects lacked a fancy name. So we gave them one, and it's caught on very nicely." The POJO phenomenon has most likely gained widespread acceptance because of the need for a common and easily understood term that contrasts with complicated object frameworks.


If you’ve been doing Java development for long, you’ve probably seen (and may have even worked with) frameworks that lock you in by forcing you to extend one of their classes or implement one of their interfaces. 

Spring avoids (as much as possible) littering your application code with its API. Spring almost never forces you to implement a Spring-specific interface or extend a Spring-specific class. Instead, the classes in a Spring-based application often have no indication that they’re being used by Spring. At worst, a class may be annotated with one of Spring’s annotations, but it’s otherwise a POJO.

### 1.1.2 Injecting dependencies


##### HOW DI WORKS

Any nontrivial application (pretty much anything more complex than a Hello World example) is made up of two or more classes that collaborate with each other to per- form some business logic. Traditionally, each object is responsible for obtaining its own references to the objects it collaborates with (its dependencies). This can lead to highly coupled and hard-to-test code.

For example, consider the Knight class shown next.

```java
package com.springinaction.knights;
public class DamselRescuingKnight implements Knight {
      private RescueDamselQuest quest;
      public DamselRescuingKnight() {
          this.quest = new RescueDamselQuest(); // Tightly coupled to RescueDamselQuest
      }
       public void embarkOnQuest() {
          quest.embark();
      } 
}
```

Coupling is a two-headed beast. On the one hand, tightly coupled code is difficult to test, difficult to reuse, and difficult to understand, and it typically exhibits “whack-a- mole” bug behavior (fixing one bug results in the creation of one or more new bugs). On the other hand, a certain amount of coupling is necessary—completely uncoupled code doesn’t do anything. In order to do anything useful, classes need to know about each other somehow. Coupling is necessary but should be carefully managed.

With DI, objects are given their dependencies at creation time by some third party that coordinates each object in the system. Objects aren’t expected to create or obtain their dependencies. Dependencies are injected into the objects that need them.

```java
package com.springinaction.knights;
public class BraveKnight implements Knight {
  private Quest quest;
  public BraveKnight(Quest quest) {
    this.quest = quest;  // Quest is injected
  }
  public void embarkOnQuest() {
    quest.embark();
  } 
}
```

As you can see, BraveKnight, unlike DamselRescuingKnight, doesn’t create his own quest. Instead, he’s given a quest at construction time as a constructor argument. This is a type of DI known as __constructor injection__.

The point is that BraveKnight isn’t coupled to any specific implementation of Quest. It doesn’t matter to him what kind of quest he’s asked to embark on, as long as it implements the Quest interface. That’s the key benefit of DI—loose coupling. __If an object only knows about its dependencies by their interface (not by their implementation or how they’re instantiated), then the dependency can be swapped out with a different implementation without the depending object knowing the difference.__

### 1.1.3 Applying aspects

Although DI makes it possible to tie software components together loosely, __aspect-oriented programming (AOP)__ enables you to capture functionality that’s used throughout your application in reusable components.

AOP is often defined as a technique that promotes separation of concerns in a soft- ware system. Systems are composed of several components, each responsible for a spe- cific piece of functionality. But often these components also carry additional respon- sibilities beyond their core functionality. System services such as logging, transaction management, and security often find their way into components whose core responsibilities is something else. These system services are commonly referred to as cross-cut- ting concerns because they tend to cut across multiple components in a system.

By spreading these concerns across multiple components, you introduce two levels of complexity to your code:

* The code that implements the system-wide concerns is duplicated across multi- ple components. This means that if you need to change how those concerns work, you’ll need to visit multiple components. Even if you’ve abstracted the concern to a separate module so that the impact to your components is a single method call, that method call is duplicated in multiple places.  
* Your components are littered with code that isn’t aligned with their core functionality. A method that adds an entry to an address book should only be concerned with how to add the address and not with whether it’s secure or transactional.  

AOP makes it possible to modularize these services and then apply them declaratively to the components they should affect. This results in components that are more cohe- sive and that focus on their own specific concerns, completely ignorant of any system services that may be involved. In short, aspects ensure that POJOs remain plain.



## 1.2 Containing your beans

In a Spring-based application, your application objects live in the Spring __container__. The container creates the objects, wires them together, configures them, and manages their complete lifecycle from cradle to grave (or new to finalize(), as the case may be).

The container is at the core of the Spring Framework. Spring’s container uses DI to manage the components that make up an application. This includes creating associa- tions between collaborating components. As such, these objects are cleaner and easier to understand, they support reuse, and they’re easy to unit test.

### 1.2.1 Working with an application context


Loading an application context from the filesystem or from the classpath is similar to how you load beans into a bean factory. For example, here’s how you’d load a File- SystemXmlApplicationContext:

```java
ApplicationContext context = new FileSystemXmlApplicationContext("c:/knight.xml");
```

Similarly, you can load an application context from the application’s classpath using ClassPathXmlApplicationContext:

```java
ApplicationContext context = new ClassPathXmlApplicationContext("knight.xml");
```

The difference between using FileSystemXmlApplicationContext and ClassPathXml- ApplicationContext is that FileSystemXmlApplicationContext looks for knight.xml in a specific location within the filesystem, whereas ClassPathXmlApplicationContext looks for knight.xml anywhere in the classpath (including JAR files).

### 1.2.2 A bean’s life

In a traditional Java application, the lifecycle of a bean is simple. Java’s new keyword is used to instantiate the bean, and it’s ready to use. Once the bean is no longer in use, it’s eligible for garbage collection and eventually goes to the big bit bucket in the sky.

In contrast, the lifecycle of a bean in a Spring container is more elaborate. It’s important to understand the lifecycle of a Spring bean, because you may want to take advantage of some of the opportunities that Spring offers to customize how a bean is created. 

![alt](http://img.blog.csdn.net/20161003204712177)

As you can see, a bean factory performs several setup steps before a bean is ready to use. Let’s break down figure 1.5 in more detail:

1. Spring instantiates the bean.
2. Spring injects values and bean references into the bean’s properties.
3. If the bean implements BeanNameAware, Spring passes the bean’s ID to the setBeanName() method.
4. If the bean implements BeanFactoryAware, Spring calls the setBeanFactory() method, passing in the bean factory itself.
5. If the bean implements ApplicationContextAware, Spring calls the setApplicationContext() method, passing in a reference to the enclosing application context.
6. If the bean implements the BeanPostProcessor interface, Spring calls its postProcessBeforeInitialization() method.
7. If the bean implements the InitializingBean interface, Spring calls its afterPropertiesSet() method. Similarly, if the bean was declared with an initmethod, then the specified initialization method is called.
8. If the bean implements BeanPostProcessor, Spring calls its postProcessAfterInitialization() method.
9. At this point, the bean is ready to be used by the application and remains in the application context until the application context is destroyed.
10. If the bean implements the DisposableBean interface, Spring calls its destroy() method. Likewise, if the bean was declared with a destroy-method, the specified method is called.

Now you know how to create and load a Spring container. But an empty container isn’t much good by itself; it doesn’t contain anything unless you put something in it. To achieve the benefits of Spring DI, you must wire your application objects into the Spring container. 

## 1.3 Surveying the Spring landscape

As you’ve seen, the Spring Framework is focused on simplifying enterprise Java devel- opment through DI, AOP, and boilerplate reduction. Even if that were all Spring did, it’d be worth using. But there’s more to Spring than meets the eye.

Within the Spring Framework proper, you’ll find several ways that Spring can ease Java development. But beyond the Spring Framework is a greater ecosystem of proj- ects that build on the core framework, extending Spring into areas such as web ser- vices, REST, mobile, and NoSQL.

Let’s first break down the core Spring Framework to see what it brings to the table. Then we’ll expand our sights to review the other members of the greater Spring portfolio.

### 1.3.1 Spring modules

When you download the Spring distribu- tion and dig into its libs folder, you’ll find several JAR files. As of Spring 4.0, there are 20 distinct modules in the Spring Framework distribution, with three JAR files for each module (the binary class library, the source JAR file, and a JavaDoc JAR file). The complete list of library JAR files is shown in figure 1.6.

![alt](http://3.bp.blogspot.com/-Oei0syhgzW0/VlXmL69QwjI/AAAAAAAAAL8/0kv-Zu5c9Wc/s1600/Untitled.png)

These modules can be arranged into six categories of functionality, as illus- trated in figure 1.7.

![alt](http://apprize.info/javascript/spring_1/spring_1.files/image024.jpg)

##### CORE SPRING CONTAINER

The centerpiece of the Spring Framework is a container that manages how the beans in a Spring-enabled application are created, configured, and managed. In this mod- ule is the Spring bean factory, which is the portion of Spring that provides DI. Build- ing on the bean factory, you’ll find several implementations of Spring’s application context, each of which provides a different way to configure Spring.

In addition to the bean factory and application context, this module also supplies many enterprise services such as email, JNDI access, EJB integration, and scheduling.

All of Spring’s modules are built on top of the core container. You’ll implicitly use these classes when you configure your application. 

##### SPRING’S AOP MODULE

Spring provides rich support for aspect-oriented programming in its AOP module. This module serves as the basis for developing your own aspects for your Spring- enabled application. Like DI, AOP supports loose coupling of application objects. But with AOP, application-wide concerns (such as transactions and security) are decoupled from the objects to which they’re applied.

##### DATA ACCESS AND INTEGRATION

Working with JDBC often results in a lot of boilerplate code that gets a connection, creates a statement, processes a result set, and then closes the connection. Spring’s JDBC and __data-access objects (DAO)__ module abstracts away the boilerplate code so that you can keep your database code clean and simple, and prevents problems that result from a failure to close database resources. This module also builds a layer of meaningful exceptions on top of the error messages given by several database servers. No more trying to decipher cryptic and proprietary SQL error messages!

For those who prefer using an __object-relational mapping (ORM)__ tool over straight JDBC, Spring provides the ORM module. Spring’s ORM support builds on the DAO sup- port, providing a convenient way to build DAOs for several ORM solutions. Spring doesn’t attempt to implement its own ORM solution but does provide hooks into sev- eral popular ORM frameworks, including Hibernate, Java Persistence API, Java Data Objects, and iBATIS SQL Maps. Spring’s transaction management supports each of these ORM frameworks as well as JDBC.

This module also includes a Spring abstraction over the Java Message Service (JMS) for asynchronous integration with other applications through messaging. And, as of Spring 3.0, this module includes the object-to-XML mapping features that were origi- nally part of the Spring Web Services project.

In addition, this module uses Spring’s AOP module to provide transaction- management services for objects in a Spring application.

##### WEB AND REMOTING

The Model-View-Controller (MVC) paradigm is a commonly accepted approach to build- ing web applications such that the user interface is separate from the application logic. Java has no shortage of MVC frameworks, with Apache Struts, JSF, WebWork, and Tapestry being among the most popular MVC choices.

Even though Spring integrates with several popular MVC frameworks, its web and remoting module comes with a capable MVC framework that promotes Spring’s loosely coupled techniques in the web layer of an application. 

In addition to user-facing web applications, this module also provides several remoting options for building applications that interact with other applications. Spring’s remoting capabilities include Remote Method Invocation (RMI), Hessian, Bur- lap, JAX-WS, and Spring’s own HTTP invoker. Spring also offers first-class support for exposing and consuming REST APIs.

##### INSTRUMENTATION

Spring’s instrumentation module includes support for adding agents to the JVM. Spe- cifically, it provides a weaving agent for Tomcat that transforms class files as they’re loaded by the classloader.

##### TESTING

Recognizing the importance of developer-written tests, Spring provides a module ded- icated to testing Spring applications.

## 1.5 Summary

You should now have a good idea of what Spring brings to the table. Spring aims to make enterprise Java development easier and to promote loosely coupled code. Vital to this are dependency injection and aspect-oriented programming.

DI is a way of associating application objects such that the objects don’t need to know where their dependencies come from or how they’re implemented. Rather than acquiring dependencies on their own, dependent objects are given the objects that they depend on. Because dependent objects often only know about their injected objects through interfaces, coupling is kept low.

In addition to DI, you also saw a glimpse of Spring’s AOP support. AOP enables you to centralize in one place—an aspect—logic that would normally be scattered throughout an application. When Spring wires your beans together, these aspects can be woven in at runtime, effectively giving the beans new behavior.

DI and AOP are central to everything in Spring. Thus you must understand how to use these principal functions of Spring to be able to use the rest of the framework. In this chapter, we’ve just scratched the surface of Spring’s DI and AOP features. Over the next few chapters, we’ll dig deeper into DI and AOP.

