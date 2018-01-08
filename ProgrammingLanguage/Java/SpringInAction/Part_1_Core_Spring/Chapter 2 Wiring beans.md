In Spring, objects aren’t responsible for finding or creating the other objects that they need to do their jobs. Instead, the container gives them references to the objects that they collaborate with. An order-manager component, for example, may need a credit-card authorizer—but it doesn’t have to create the credit-card authorizer. It just needs to show up empty-handed, and it’s given a credit-card authorizer to work with.

The act of creating these associations between application objects is the essence of dependency injection (DI) and is commonly referred to as __wiring__.

## 2.1 Exploring Spring’s configuration options

When it comes to expressing a bean wiring specification, Spring is incredibly flexible, offering three primary wiring mechanisms:

* Explicit configuration in XML  
* Explicit configuration in Java  
* Implicit bean discovery and automatic wiring  

## 2.2 Automatically wiring beans

Spring attacks automatic wiring from two angles:

* Component scanning—Spring automatically discovers beans to be created in the application context.
* Autowiring—Spring automatically satisfies bean dependencies.  

```java
import org.springframework.stereotype.Component;

@Component
public class SgtPeppers implements CompactDisc {
    private String title = "Sgt. Pepper's Lonely Hearts Club Band";
    private String artist = "The Beatles";
    public void play() {
        System.out.println("Playing " + title + " by " + artist);
    }
}
```

What you should take note of is that SgtPeppers is annotated with @Component. This simple annotation identifies this class as a component class and serves as a clue to Spring that a bean should be created for the class. There’s no need to explicitly configure a SgtPeppers bean; Spring will do it for you because this class is annotated with @Component. Component scanning isn’t turned on by default, however. You’ll still need to write an explicit configuration to tell Spring to seek out classes annotated with @Component and to create beans from them. The configuration class in the following listing shows the minimal configuration to make this possible.

```java
package soundsystem;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
@Configuration
@ComponentScan
public class CDPlayerConfig {
}
```

Observe that CDPlayerConfig doesn’t explicitly define any beans itself. Instead, it’s annotated with @ComponentScan to enable component scanning in Spring.

### 2.2.2 Naming a component-scanned bean

All beans in a Spring application context are given an ID. What may not have been apparent from the previous example is that although you didn’t explicitly give the SgtPeppers bean an ID, it was given one derived from its class name. Specifically, the bean was given an ID of sgtPeppers by lowercasing the first letter of the class name. If you’d rather give the bean a different ID, all you have to do is pass the desired ID as a value to the @Component annotation. For example, if you wanted to identify the bean as lonelyHeartsClub, then you’d annotate the SgtPeppers class with @Component like this:

```java
@Component("lonelyHeartsClub")
public class SgtPeppers implements CompactDisc {
...
}
```

### 2.2.3 Setting a base package for component scanning

Thus far, you’ve used @ComponentScan with no attributes. That means it will default to the configuration class’s package as its base package to scan for components. But what if you want to scan a different package? Or what if you want to scan multiple base packages? One common reason for explicitly setting the base package is so that you can keep all of your configuration code in a package of its own, separate from the rest of your application’s code. In that case, the default base package won’t do. No problem. To specify a different base package, you only need to specify the package in @ComponentScan’s value attribute:

```java
@Configuration
@ComponentScan("soundsystem")
public class CDPlayerConfig {}
```

### 2.2.4 Annotating beans to be automatically wired

Put succinctly, autowiring is a means of letting Spring automatically satisfy a bean’s dependencies by finding other beans in the application context that are a match to the bean’s needs. To indicate that autowiring should be performed, you can use Spring’s @Autowired annotation.

For example, consider the CDPlayer class in the following listing. Its constructor is annotated with @Autowired, indicating that when Spring creates the CDPlayer bean, it should instantiate it via that constructor and pass in a bean that is assignable to CompactDisc.

```java
package soundsystem;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
@Component
public class CDPlayer implements MediaPlayer {
    private CompactDisc cd;
    @Autowired
    public CDPlayer(CompactDisc cd) {
        this.cd = cd;
    }
    public void play() {
        cd.play();
    }
}
```

The @Autowired annotation's use isn't limited to constructors. It can also be used on a property抯 setter method. For example, if CDPlayer had a setCompactDisc() method, you might annotate it for autowiring like this:

```java
@Autowired
public void setCompactDisc(CompactDisc cd) {
  this.cd = cd;
}
```

## 2.3 Wiring beans with Java

Although automatic Spring configuration with component scanning and automatic wiring is preferable in many cases, there are times when automatic configuration isn’t an option and you must configure Spring explicitly. For instance, let’s say that you want to wire components from some third-party library into your application. Because you don’t have the source code for that library, there’s no opportunity to annotate its classes with @Component and @Autowired. Therefore, automatic configuration isn’t an option. In that case, you must turn to explicit configuration. You have two choices for explicit configuration: Java and XML.

JavaConfig is the preferred option for explicit configuration because it’s more powerful, type-safe, and refactor-friendly. That’s because it’s just Java code, like any other Java code in your application.

At the same time, it’s important to recognize that JavaConfig code isn’t just any other Java code. It’s conceptually set apart from the business logic and domain code in your application. Even though it’s expressed in the same language as those components, JavaConfig is configuration code. This means it shouldn’t contain any business logic, nor should JavaConfig invade any code where business logic resides. In fact, although it’s not required, JavaConfig is often set apart in a separate package from the rest of an application’s logic so there’s no confusion as to its purpose.

### 2.3.1 Creating a configuration class

```java
package soundsystem;
import org.springframework.context.annotation.Configuration;
@Configuration
    public class CDPlayerConfig {
}
```

The key to creating a JavaConfig class is to annotate it with @Configuration. The @Configuration annotation identifies this as a configuration class, and it’s expected to contain details on beans that are to be created in the Spring application context.

### 2.3.2 Declaring a simple bean

To declare a bean in JavaConfig, you write a method that creates an instance of the desired type and annotate it with @Bean. For example, the following method declares the CompactDisc bean:

```java
@Bean
public CompactDisc sgtPeppers() {
return new SgtPeppers();
}
```

The @Bean annotation tells Spring that this method will return an object that should be registered as a bean in the Spring application context. The body of the method contains logic that ultimately results in the creation of the bean instance.

### 2.3.3 Injecting with JavaConfig

The CompactDisc bean you declared was simple and had no dependencies of its own. But now you must declare the CDPlayer bean, which depends on a CompactDisc. How can you wire that up in JavaConfig? The simplest way to wire up beans in JavaConfig is to refer to the referenced bean’s method. For example, here’s how you might declare the CDPlayer bean:

```java
@Bean
public CDPlayer cdPlayer() {
return new CDPlayer(sgtPeppers());
}
```

The cdPlayer() method, like the sgtPeppers() method, is annotated with @Bean to indicate that it will produce an instance of a bean to be registered in the Spring application context. The ID of the bean will be cdPlayer, the same as the method’s name.

The body of the cdPlayer() method differs subtly from that of the sgtPeppers() method. Rather than construct an instance via its default method, the CDPlayer instance is created by calling its constructor that takes a CompactDisc.

It appears that the CompactDisc is provided by calling sgtPeppers, but that抯 not exactly true. Because the sgtPeppers() method is annotated with @Bean, Spring will intercept any calls to it and ensure that the bean produced by that method is returned rather than allowing it to be invoked again.

If the call to sgtPeppers() was treated like any other call to a Java method, then each CDPlayer would be given its own instance of SgtPeppers. That would make sense if we were talking about real CD players and compact discs. If you have two CD players, there’s no physical way for a single compact disc to simultaneously be inserted into two CD players. 

In software, however, there’s no reason you couldn’t inject the same instance of SgtPeppers into as many other beans as you want. __By default, all beans in Spring are singletons__, and there’s no reason you need to create a duplicate instance for the second CDPlayer bean. So Spring intercepts the call to sgtPeppers() and makes sure that what is returned is the Spring bean that was created when Spring itself called sgtPeppers() to create the CompactDisc bean. Therefore, both CDPlayer beans will be given the same instance of SgtPeppers.

## 2.4 Wiring beans with XML













