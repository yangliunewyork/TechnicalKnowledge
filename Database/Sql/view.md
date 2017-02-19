### What is database view ?
A view, or virtual table, can be defined as an alternate way of collecting data from one or more tables in a database. Thus, the view consists of rows and columns just like a normal table that is generated dynamically when a query is executed. It, however, does not actually exist as a stored set of data in the database.

### Usage
Views are useful for the following purposes:
* To restrict a user to specific rows in a table.
* To restrict a user to specific columns.
* To join columns from multiple tables so that they appear to be a single table.
* To get aggregate information instead of supplying details.

### Create View
```
create view [ owner  .] view_name  
[( column_name  [,  column_name ]...)] 
as select [distinct] select_statement
[with check option]
```

### Restrictions:
There are a few restrictions on the  select  statements in a view definition: 
* You cannot include  order by  or  compute  clauses. 
* You cannot include the into  keyword. 
* You cannot reference a temporary table. 
