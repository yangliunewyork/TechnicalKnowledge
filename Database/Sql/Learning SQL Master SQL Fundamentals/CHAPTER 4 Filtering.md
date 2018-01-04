Sometimes you will want to work with every row in a table, such as: 

* Purging all data from a table used to stage new data warehouse feeds      
* Modifying all rows in a table after a new column has been added     
* Retrieving all rows from a message queue table    

In cases like these, your SQL statements won’t need to have a WHERE clause, since you don’t need to exclude any rows from consideration. Most of the time, however, you will want to narrow your focus to a subset of a table’s rows. Therefore, all the SQL data statements (except the INSERT statement) include an optional WHERE clause to house filter conditions used to restrict the number of rows acted on by the SQL statement. Additionally, the SELECT statement includes a HAVING clause in which filter conditions pertaining to grouped data may be included.

#### Equality Conditions

A large percentage of the filter conditions that you write or come across will be of the form 'column = expression' as in:

```
title = 'Teller'
fed_id = '111-11-1111'
amount = 375.25
dept_id = (SELECT dept_id FROM department WHERE name = 'Loans')
```

Conditions such as these are called equality conditions because they equate one expression to another. The first three examples equate a column to a literal (two strings and a number), and the fourth example equates a column to the value returned from a subquery. The following query uses two equality conditions; one in the ON clause (a join condition), and the other in the WHERE clause (a filter condition):

```sql
mysql> SELECT pt.name product_type, p.name product
-> FROM product p INNER JOIN product_type pt
-> ON p.product_type_cd = pt.product_type_cd
-> WHERE pt.name = 'Customer Accounts';
```

This query shows all products that are customer account types.

#### Inequality conditions

Another fairly common type of condition is the __inequality condition__, which asserts that two expressions are not equal. Here抯 the previous query with the filter condition in the where clause changed to an inequality condition:

```sql
mysql> SELECT pt.name product_type, p.name product
-> FROM product p INNER JOIN product_type pt
-> ON p.product_type_cd = pt.product_type_cd
-> WHERE pt.name <> 'Customer Accounts';
```

This query shows all products that are not customer account types. When building inequality conditions, you may choose to use either the != or <> operator.

Equality/inequality conditions are commonly used when modifying data. For example, let’s say that the bank has a policy of removing old account rows once per year. Your task is to remove rows from the account table that were closed in 2002. Here’s one way to tackle it:

```sql
DELETE FROM account WHERE status = 'CLOSED' AND YEAR(close_date) = 2002; 
```

This statement includes two equality conditions: one to find only closed accounts, and another to check for those accounts closed in 2002.

##### Using wildcards

When searching for partial string matches, you might be interested in:  

* Strings beginning/ending with a certain character   
* Strings beginning/ending with a substring   
* Strings containing a certain character anywhere within the string   
* Strings containing a substring anywhere within the string   
* Strings with a specific format, regardless of individual characters  

| Wildcard character | Matches                                                                          |
|-------------|-----------------------------------------------------------------------------------|
| _      | Exactly one character                     |
| %      | Any number of characters (including 0)                     |


The underscore character takes the place of a single character, while the percent sign can take the place of a variable number of characters. When building conditions that utilize search expressions, you use the LIKE operator, as in:

```sql
mysql> SELECT lname
-> FROM employee
-> WHERE lname LIKE '_a%e%';
```

##### Using regular expressions

If you find that the wildcard characters don't provide enough flexibility, you can use regular expressions to build search expressions.

```sql
mysql> SELECT emp_id, fname, lname
-> FROM employee
-> WHERE lname REGEXP '^[FG]';
```

# Null: That Four-Letter Word

I put it off as long as I could, but it’s time to broach a topic that tends to be met with fear, uncertainty, and dread: the null value. Null is the absence of a value; before an employee is terminated, for example, her end_date column in the employee table should be null. There is no value that can be assigned to the end_date column that would make sense in this situation. Null is a bit slippery, however, as there are various flavors of null:

* Not applicable : Such as the employee ID column for a transaction that took place at an ATM machine   
* Value not yet known : Such as when the federal ID is not known at the time a customer row is created   
* Value undefined : Such as when an account is created for a product that has not yet been added to the database  

When working with null, you should remember:

* An expression can be null, but it can never equal null.
* __Two nulls are never equal to each other__.

To test whether an expression is null, you need to use the __is null__ operator, as demonstrated by the following:

```sql
mysql> SELECT emp_id, fname, lname, superior_emp_id
-> FROM employee
-> WHERE superior_emp_id IS NULL;
```

Before putting null aside for a while, it would be helpful to investigate one more potential pitfall. Suppose that you have been asked to identify all employees who are not managed by Helen Fleming (whose employee ID is 6). Your first instinct might be to do the following:

```sql
mysql> SELECT emp_id, fname, lname, superior_emp_id
-> FROM employee
-> WHERE superior_emp_id != 6;
```

While it is true that these 14 employees do not work for Helen Fleming, if you look carefully at the data, you will see that there is one more employee who doesn’t work for Helen who is not listed here. That employee is Michael Smith, and his superior_emp_id column is null (because he’s the big cheese). To answer the question correctly, therefore, you need to account for the possibility that some rows might contain a null in the superior_emp_id column:

```sql
mysql> SELECT emp_id, fname, lname, superior_emp_id
-> FROM employee
-> WHERE superior_emp_id != 6 OR superior_emp_id IS NULL;
```

When working with a database that you are not familiar with, it is a good idea to find out which columns in a table allow nulls so that you can take appropriate measures with your filter conditions to keep data from slipping through the cracks.

