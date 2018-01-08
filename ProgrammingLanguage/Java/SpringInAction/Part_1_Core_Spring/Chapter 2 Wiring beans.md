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




