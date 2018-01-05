# Working with String Data

When working with string data, you will be using one of the following character data types: 

* __CHAR__ : Holds fixed-length, blank-padded strings. MySQL allows CHAR values up to 255 characters in length, Oracle Database permits up to 2,000 characters, and SQL Server allows up to 8,000 characters.  
* __varchar__ : Holds variable-length strings. MySQL permits up to 65,535 characters in a varchar column, Oracle Database (via the varchar2 type) allows up to 4,000 characters, and SQL Server allows up to 8,000 characters.  
* __text__ : (MySQL and SQL Server) or CLOB (Character Large Object; Oracle Database) Holds very large variable-length strings (generally referred to as documents in this context). MySQL has multiple text types (tinytext, text, mediumtext, and long text) for documents up to 4 GB in size. SQL Server has a single text type for documents up to 2 GB in size, and Oracle Database includes the CLOB data type, which can hold documents up to a whopping 128 TB. SQL Server 2005 also includes the varchar(max) data type and recommends its use instead of the text type, which will be removed from the server in some future release.  

When inserting string data into a table, remember that if the length of the string exceeds the maximum size for the character column (either the designated maximum or the maximum allowed for the data type), the server will throw an exception. Although this is the default behavior for all three servers, you can configure MySQL and SQL Server to silently truncate the string instead of throwing an exception.

# Working with Numeric Data

Unlike string data (and temporal data, as you will see shortly), numeric data generation is quite straightforward. You can type a number, retrieve it from another column, or generate it via a calculation. All the usual arithmetic operators (+, -, *, /) are available for performing calculations, and parentheses may be used to dictate precedence.

The main concern when storing numeric data is that numbers might be rounded if they are larger than the specified size for a numeric column. For example, the number 9.96 will be rounded to 10.0 if stored in a column defined as float(3,1).

```
Acos(x) Calculates the arc cosine of x
Asin(x) Calculates the arc sine of x
Atan(x) Calculates the arc tangent of x
Cos(x) Calculates the cosine of x
Cot(x) Calculates the cotangent of x
Exp(x) Calculates ex
Ln(x) Calculates the natural log of x
Sin(x) Calculates the sine of x
Sqrt(x) Calculates the square root of x
Tan(x) Calculates the tangent of x
```

# Working with Temporal Data

You can generate temporal data via any of the following means:

* Copying data from an existing date, datetime, or time column  
* Executing a built-in function that returns a date, datetime, or time  
* Building a string representation of the temporal data to be evaluated by the server  

To use the last method, you will need to understand the various components used in formatting dates.

















