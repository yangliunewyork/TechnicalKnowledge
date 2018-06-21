The PHP Hypertext Preprocessor (PHP) is a programming language that allows web developers to create dynamic content that interacts with databases. PHP is basically used for developing web based software applications. 

PHP started out as a small open source project that evolved as more and more people found out how useful it was. Rasmus Lerdorf unleashed the first version of PHP way back in 1994.

* PHP is a recursive acronym for "PHP: Hypertext Preprocessor".
* PHP is a server side scripting language that is embedded in HTML. It is used to manage dynamic content, databases, session tracking, even build entire e-commerce sites.
* It is integrated with a number of popular databases, including MySQL, PostgreSQL, Oracle, Sybase, Informix, and Microsoft SQL Server.
* PHP is pleasingly zippy in its execution, especially when compiled as an Apache module on the Unix side. The MySQL server, once started, executes even very complex queries with huge result sets in record-setting time.
* PHP supports a large number of major protocols such as POP3, IMAP, and LDAP. PHP4 added support for Java and distributed object architectures (COM and CORBA), making n-tier development a possibility for the first time.
* PHP is forgiving: PHP language tries to be as forgiving as possible.
* PHP Syntax is C-Like.

#### Common uses of PHP

* PHP performs system functions, i.e. from files on a system it can create, open, read, write, and close them.  
* PHP can handle forms, i.e. gather data from files, save data to a file, through email you can send data, return data to the user.  
* You add, delete, modify elements within your database through PHP.  
* Access cookies variables and set cookies.  
* Using PHP, you can restrict users to access some pages of your website.  
*  It can encrypt data.  

#### Hellow world

```php
<html>
   
   <head>
      <title>Hello World</title>
   </head>
   
   <body>
      <?php echo "Hello, World!";?>
   </body>

</html>
```


If you examine the HTML output of the above example, you'll notice that the PHP code is not present in the file sent from the server to your Web browser. All of the PHP present in the Web page is processed and stripped from the page; the only thing returned to the client from the Web server is pure HTML output.

All PHP code must be included inside one of the three special markup tags ATE are recognised by the PHP Parser.

```php
<?php PHP code goes here ?>

<?    PHP code goes here ?>

<script language = "php"> PHP code goes here </script>
```

# PHP - Web Concepts

PHP creates some useful environment variables that can be seen in the phpinfo.php page that was used to setup the PHP environment.

One of the environment variables set by PHP is HTTP_USER_AGENT which identifies the user's browser and operating system.

PHP provides a function getenv() to access the value of all the environment variables. The information contained in the HTTP_USER_AGENT environment variable can be used to create dynamic content appropriate to the browser.

#### The GET Method

The GET method sends the encoded user information appended to the page request. The page and the encoded information are separated by the ? character.

```
http://www.test.com/index.htm?name1=value1&name2=value2
```


* The GET method produces a long string that appears in your server logs, in the browser's Location: box.
* The GET method is restricted to send upto 1024 characters only.
* Never use GET method if you have password or other sensitive information to be sent to the server.
* GET can't be used to send binary data, like images or word documents, to the server.
* The data sent by GET method can be accessed using ```QUERY_STRING``` environment variable.
* The PHP provides ```$_GET``` associative array to access all the sent information using GET method.

#### The POST Method

The POST method transfers information via HTTP headers. The information is encoded as described in case of GET method and put into a header called QUERY_STRING.

* The POST method does not have any restriction on data size to be sent.
* The POST method can be used to send ASCII as well as binary data.
* The data sent by POST method goes through HTTP header so security depends on HTTP protocol. By using Secure HTTP you can make sure that your information is secure.
* The PHP provides ```$_POST``` associative array to access all the sent information using POST method.

#### The $\_REQUEST variable

The PHP ```$_REQUEST``` variable contains the contents of both ```$_GET```, ```$_POST```, and ```$_COOKIE```. \

The PHP ```$_REQUEST``` variable can be used to get the result from form data sent with both the GET and POST methods.

