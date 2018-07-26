https://www.tutorialspoint.com/spring/spring_bean_definition.htm  

The objects that form the backbone of your application and that are managed by the Spring IoC container are called beans. A bean is an object that is instantiated, assembled, and otherwise managed by a Spring IoC container. These beans are created with the configuration metadata that you supply to the container. For example, in the form of XML <bean/> definitions which you have already seen in the previous chapters.

Bean definition contains the information called configuration metadata, which is needed for the container to know the following :

* How to create a bean
* Bean's lifecycle details
* Bean's dependencies  

All the above configuration metadata translates into a set of the following properties that make up each bean definition.

* class : This attribute is mandatory and specifies the bean class to be used to create the bean.
* name : This attribute specifies the bean identifier uniquely. In XMLbased configuration metadata, you use the id and/or name attributes to specify the bean identifier(s).
* scope : This attribute specifies the scope of the objects created from a particular bean definition and it will be discussed in bean scopes chapter.
* constructor-arg : This is used to inject the dependencies and will be discussed in subsequent chapters.
* properties :  This is used to inject the dependencies.
* autowiring mode : This is used to inject the dependencies and will be discussed in subsequent chapters.
* lazy-initialization mode : A lazy-initialized bean tells the IoC container to create a bean instance when it is first requested, rather than at the startup.
* initialization method : A callback to be called just after all necessary properties on the bean have been set by the container. It will be discussed in bean life cycle chapter.
* destruction method : A callback to be used when the container containing the bean is destroyed. It will be discussed in bean life cycle chapter.

##### Example

http://www.java2s.com/Tutorials/Java/Spring/0140__Spring_Map_Properties.htm

```xml
<beans>
    <bean id="sessionFactory"
          class="org.springframework.orm.hibernate3.LocalSessionFactoryBean">
        <property name="dataSource" ref="dataSource"/>
        <property name="mappingResources">
             <list>
                 <value>com/acme/Bank.hbm.xml</value>
                 <value>com/acme/Account.hbm.xml</value>
                 <value>com/acme/Customer.hbm.xml</value>
             </list>
        </property>
    </bean>

    <bean id="dataSource" class="...">
        <!-- ... -->
    </bean>
</beans>
```

