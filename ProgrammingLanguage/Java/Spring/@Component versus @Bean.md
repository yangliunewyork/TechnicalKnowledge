Most of the developers has confused about the real use and the purpose of @Bean and @Component annotations. most of them are thinking that they are just two annotations used for same purpose. This is completely wrong idea and those are two different annotations used for two different purposes. lets look at each of their purpose.

 

### @Component

This is a generic annotation and can be applied to any class of the application to make it a spring managed component(simply, generic stereotype for any spring managed component). when the classpath is scanned by the spring’s component-scan (@ComponentScan) feature, it will identify the classes annotated with @Component annotation (within the given package) and create the beans of such classes and register them in the ApplicationContext. @Component is a class level annotation and its purpose it to make the class as spring managed component and auto detectable bean for classpath scanning feature.

If you want to know more about  @Component and other stereo type annotations, it is recommended to look at [this article](https://springbootdev.com/2017/07/31/spring-framework-component-service-repository-and-controller/).

 

### @Bean

@Bean is used to explicitly declare and register a bean (as a configuration bean) in Spring IOC container that is returned from a method. @Bean is a method level annotation and it is used within a class that is annotated with @Configuration. Simply, @Bean annotation is used to register the bean returned by a method as a spring configuration bean in IOC Container.  @Bean is only a method level annotation and it cannot be used with classes and object declaration.

@Bean annotation indicates that a method produces a bean that should be managed by the Spring container.

To declare a bean, simply annotate a method with the @Bean annotation. When JavaConfig encounters such a method, it will execute that method and register the return value as a bean within a ApplicationContext. By default, the bean name will be the same as the method name.The following is a simple example of a @Bean method declaration.

```java
@Configuration
public class ApplicationConfig {

 @Bean
 public User adminUserProfile() 
 {
     return new User("Chathuranga","Tennakoon");
 }
}
```

In the ApplicationConfig class, you can see that we first use the @Configuration annotation to inform Spring that this is a Java-based configuration file. Afterward, the @Bean annotation is used to declare a Spring bean and the DI requirements.
The @Bean annotation is equivalent to the <bean> tag, the method name is equivalent to the id attribute within the <bean> tag.

### Some answers from stack-overflow


@Component and @Bean do two quite different things, and shouldn't be confused.

@Component (and @Service and @Repository) are used to auto-detect and auto-configure beans using classpath scanning. There's an implicit one-to-one mapping between the annotated class and the bean (i.e. one bean per class). Control of wiring is quite limited with this approach, since it's purely declarative.

@Bean is used to explicitly declare a single bean, rather than letting Spring do it automatically as above. It decouples the declaration of the bean from the class definition, and lets you create and configure beans exactly how you choose.

@Component Preferable for component scanning and automatic wiring.

When should you use @Bean?

Sometimes automatic configuration is not an option. When? Let's imagine that you want to wire components from 3rd-party libraries (you don't have the source code so you can't annotate its classes with @Component), so automatic configuration is not possible.

The @Bean annotation returns an object that spring should register as bean in application context. The body of the method bears the logic responsible for creating the instance.
