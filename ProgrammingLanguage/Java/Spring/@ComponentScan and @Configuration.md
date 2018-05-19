@ComponentScan 如果不设置basePackage的话 默认会扫描包的所有类，所以最好还是写上basePackage ,减少加载时间。默认扫描**/*.class路径 比如这个注解在com.wuhulala 下面 ，那么会扫描这个包下的所有类还有子包的所有类,比如com.wuhulala.service包的应用

@Configuration 表示这个类是一个spring 配置类，一般这里面会定义Bean，会把这个类中bean加载到spring容器中
