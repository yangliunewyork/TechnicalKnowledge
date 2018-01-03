# Query Mechanics

Once the server has verified your username and password and issued you a connection, you are ready to execute queries (along with other SQL statements). Each time a query is sent to the server, the server checks the following things prior to statement execution:

* Do you have permission to execute the statement?  
* Do you have permission to access the desired data?  
* Is your statement syntax correct?  

If your statement passes these three tests, then your query is handed to the __query optimizer__, whose job it is to determine the most efficient way to execute your query. The optimizer will look at such things as the order in which to join the tables named in your _from clause_ and what indexes are available, and then picks an __execution plan__, which the server uses to execute your query.

# Query Clauses

| Clause name | Purpose                                                                           |
|-------------|-----------------------------------------------------------------------------------|
| Select      | Determines which columns to include in the query’s result set                     |
| From        | Identifies the tables from which to draw data and how the tables should be joined |
| Where       | Filters out unwanted data                                                         |
| Group by    | Used to group rows together by common column values                               |
| Having      | Filters out unwanted groups                                                       |
| Order by    | Sorts the rows of the final result set by one or more columns                     |


#### The select Clause

__Even though the select clause is the first clause of a select statement, it is one of the last clauses that the database server evaluates.__ The reason for this is that before you can determine what to include in the final result set, you need to know all of the possible columns that could be included in the final result set.

The select clause determines which of all possible columns should be included in the query’s result set.

Keep in mind that generating a distinct set of results requires the data to be sorted, which can be time-consuming for large result sets. Don’t fall into the trap of using DISTINCT just to be sure there are no duplicates; instead, take the time to understand the data you are working with so that you will know whether duplicates are possible.

#### The from Clause

The FROM clause defines the tables used by a query, along with the means of linking the tables together.

When confronted with the term table, most people think of a set of related rows stored in a database. While this does describe one type of table, I would like to use the word in a more general way by removing any notion of how the data might be stored and concentrating on just the set of related rows. Three different types of tables meet this relaxed definition: 

* Permanent tables (i.e., created using the create table statement)   
* Temporary tables (i.e., rows returned by a subquery)   
* Virtual tables (i.e., created using the create view statement)   

Each of these table types may be included in a query’s from clause. By now, you should be comfortable with including a permanent table in a from clause, so I briefly describe the other types of tables that can be referenced in a from clause.

A __subquery__ is a query contained within another query. Subqueries are surrounded by parentheses and can be found in various parts of a select statement; within the from clause, however, a subquery serves the role of generating a temporary table that is visible from all other query clauses and can interact with other tables named in the from clause.

```sql
mysql> SELECT e.emp_id, e.fname, e.lname
-> FROM (SELECT emp_id, fname, lname, start_date, title
-> FROM employee) e;
```

A view is a query that is stored in the data dictionary. It looks and acts like a table, but there is no data associated with a view (this is why I call it a virtual table). When you issue a query against a view, your query is merged with the view definition to create a final query to be executed.

```sql
mysql> CREATE VIEW employee_vw AS
-> SELECT emp_id, fname, lname,
-> YEAR(start_date) start_year
-> FROM employee;
Query OK, 0 rows affected (0.10 sec)
```

When the view is created, no additional data is generated or stored: the server simply tucks away the select statement for future use.

Views are created for various reasons, including to hide columns from users and to simplify complex database designs.

#### The where Clause

The where clause is the mechanism for filtering out unwanted rows from your result set.

All the queries thus far have retrieved raw data without any manipulation. Sometimes, however, you will want to find trends in your data that will require the database server to cook the data a bit before you retrieve your result set. One such mechanism is the group by clause, which is used to group data by column values. For example, rather than looking at a list of employees and the departments to which they are assigned, you might want to look at a list of departments along with the number of employees assigned to each department. When using the __group by__ clause, you may also use the __having__ clause, which allows you to filter group data in the same way the __where__ clause lets you filter raw data.

```sql
mysql> SELECT d.name, count(e.emp_id) num_employees
-> FROM department d INNER JOIN employee e
-> ON d.dept_id = e.dept_id
-> GROUP BY d.name
-> HAVING count(e.emp_id) > 2;
```

#### The order by Clause

The ORDER BY clause is the mechanism for sorting your result set using either raw column data or expressions based on column data.

