# MySQL Data Types

In general, all the popular database servers have the capacity to store the same types of data, such as strings, dates, and numbers. Where they typically differ is in the specialty data types, such as XML documents or very large text or binary documents. Since this is an introductory book on SQL, and since 98% of the columns you encounter will be simple data types, this book covers only the character, date, and numeric data types.

### Character Data

__Character data can be stored as either fixed-length or variable-length strings; the difference is that fixed-length strings are right-padded with spaces and always consume the same number of bytes, and variable-length strings are not right-padded with spaces and don’t always consume the same number of bytes.__ When defining a character column, you must specify the maximum size of any string to be stored in the column. For example, if you want to store strings up to 20 characters in length, you could use either of the following definitions:

```
char(20) /* fixed-length */
varchar(20) /* variable-length */
```

The maximum length for char columns is currently 255 bytes, whereas varchar columns can be up to 65,535 bytes. If you need to store longer strings (such as emails, XML documents, etc.), then you will want to use one of the text types (mediumtext and longtext). In general, you should use the char type when all strings to be stored in the column are of the same length, such as state abbreviations, and the varchar type when strings to be stored in the column are of varying lengths. Both char and varchar are used in a similar fashion in all the major database servers.

### Text data

If you need to store data that might exceed the 64 KB limit for varchar columns, you will need to use one of the text types.

```
Tinytext 255
Text 65,535
Mediumtext 16,777,215
Longtext 4,294,967,295
```

When choosing to use one of the text types, you should be aware of the following: 

* If the data being loaded into a text column exceeds the maximum size for that type, the data will be truncated.   
* Trailing spaces will not be removed when data is loaded into the column.   
* When using text columns for sorting or grouping, only the first 1,024 bytes are used, although this limit may be increased if necessary.   
* The different text types are unique to MySQL. SQL Server has a single text type for large character data, whereas DB2 and Oracle use a data type called clob, for Character Large Object.   
* Now that MySQL allows up to 65,535 bytes for varchar columns (it was limited to 255 bytes in version 4), there isn’t any particular need to use the tinytext or text type.  

If you are creating a column for free-form data entry, such as a notes column to hold data about customer interactions with your company’s customer service department, then varchar will probably be adequate. If you are storing documents, however, you should choose either the _mediumtext_ or _longtext_ type.

### Numeric Data

Although it might seem reasonable to have a single numeric data type called “numeric,” there are actually several different numeric data types that reflect the various ways in which numbers are used, as illustrated here: 

* A column indicating whether a customer order has been shipped : This type of column, referred to as a Boolean, would contain a 0 to indicate false and a 1 to indicate true.  
* A system-generated primary key for a transaction table : This data would generally start at 1 and increase in increments of one up to a potentially very large number.   
* An item number for a customer’s electronic shopping basket : The values for this type of column would be positive whole numbers between 1 and, at most, 200 (for shopaholics).  
* Positional data for a circuit board drill machine : High-precision scientific or manufacturing data often requires accuracy to eight decimal points.   

To handle these types of data (and more), MySQL has several different numeric data types. The most commonly used numeric types are those used to store whole numbers. When specifying one of these types, you may also specify that the data is unsigned, which tells the server that all data stored in the column will be greater than or equal to zero.

```
Tinyint −128 to 127 0 to 255
Smallint −32,768 to 32,767 0 to 65,535
Mediumint −8,388,608 to 8,388,607 0 to 16,777,215
Int −2,147,483,648 to 2,147,483,647 0 to 4,294,967,295
Bigint −9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 0 to 18,446,744,073,709,551,615
```

When you create a column using one of the integer types, MySQL will allocate an appropriate amount of space to store the data, which ranges from one byte for a tinyint to eight bytes for a bigint. Therefore, you should try to choose a type that will be large enough to hold the biggest number you can envision being stored in the column without needlessly wasting storage space.

For floating-point numbers (such as 3.1415927), you may choose from :

```
Float(p,s) −3.402823466E+38 to −1.175494351E-38 and 1.175494351E-38 to 3.402823466E+38
Double(p,s) −1.7976931348623157E+308 to −2.2250738585072014E-308 and 2.2250738585072014E-308 to 1.7976931348623157E+308
```

When using a floating-point type, you can specify a precision (the total number of allowable digits both to the left and to the right of the decimal point) and a scale (the number of allowable digits to the right of the decimal point), but they are not required. These values are represented in Table 2-4 as p and s. If you specify a precision and scale for your floating-point column, remember that the data stored in the column will be rounded if the number of digits exceeds the scale and/or precision of the column. For example, a column defined as float(4,2) will store a total of four digits, two to the left of the decimal and two to the right of the decimal. Therefore, such a column would handle the numbers 27.44 and 8.19 just fine, but the number 17.8675 would be rounded to 17.87, and attempting to store the number 178.375 in your float(4,2) column would generate an error.

### Temporal Data

Along with strings and numbers, you will almost certainly be working with information about dates and/or times. This type of data is referred to as temporal, and some examples of temporal data in a database include:  

* The future date that a particular event is expected to happen, such as shipping a customer’s order   
* The date that a customer’s order was shipped   
* The date and time that a user modified a particular row in a table   
* An employee’s birth date  
* The year corresponding to a row in a yearly_sales fact table in a data warehouse   
* The elapsed time needed to complete a wiring harness on an automobile assembly line  

MySQL includes data types to handle all of these situations.

```
Date YYYY-MM-DD 1000-01-01 to 9999-12-31
Datetime YYYY-MM-DD HH:MI:SS 1000-01-01 00:00:00 to 9999-12-31 23:59:59
Timestamp YYYY-MM-DD HH:MI:SS 1970-01-01 00:00:00 to 2037-12-31 23:59:59
Year YYYY 1901 to 2155
Time HHH:MI:SS −838:59:59 to 838:59:59
```

While database servers store temporal data in various ways, the purpose of a format string is to show how the data will be represented when retrieved, along with how a date string should be constructed when inserting or updating a temporal column. Thus, if you wanted to insert the date March 23, 2005 into a date column using the default format YYYY-MM-DD, you would use the string '2005-03-23'.

# Table Creation



