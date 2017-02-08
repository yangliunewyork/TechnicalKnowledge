## What is the difference between a derived table and a subquery?
Both derived tables and subqueries can look the same and many people may even think they are the same thing, but there are definitely differences. Don’t worry, even if you don’t know what a derived table or a subquery is in SQL, it should be clear by the time you are done reading below.

A subquery is a SELECT statement that is nested within another statement – that’s why it’s called a subquery, because it’s like having a query within another query . Subqueries are usually used in the WHERE clause as a way to filter out certain rows returned in the result set of the outer query.

Let’s say that we have a table called employee with columns employee_name, last_name, employee_salary, and employee_number. And we also have another table called department that has columns called manager_employee_number and department_name.

Using those tables as our sample data, here is what a subquery looks like:

```
select employee_name 
from employee
where employee_salary >
-- this is a subquery:
(select avg(employee_salary)
        from employee)
```

The SQL above will find all employees who have a salary that is above average. That SQL could be written much more simply, but it is just for illustrative purposes to show you what a simple subquery would look like.

#### Example of a subquery not used with a where clause

It is possible to have a subquery that is not used in conjunction with a WHERE clause. Here we are using a subquery to select an id and name from the student_details table and then insert that data into the math_study_group table.

```
INSERT INTO math_study_group(id, name) 
-- this is a subquery:
SELECT id, name
FROM student_details WHERE subject= 'Math' 
```
## Derived tables

A derived table is basically a subquery, except it is always in the FROM clause of a SQL statement. The reason it is called a derived table is because it essentially functions as a table as far as the entire query is concerned.

But, remember that a derived table only exists in the query in which it is created. So, derived tables are not actually part of the database schema because they are not real tables.

An example of a derived table will help clarify:

```
select max(age) 
from (
-- this part of the query is a derived table:
select age from table
) as Age -- must give derived table an alias
```

In the SQL above, you can see that the derived table is inside the FROM portion of the SQL. The results of the “Select age from table” query are considered to be the derived table. And, hopefully it’s fairly obvious to you how the derived table essentially acts as a table from which something else is selected.

You may have noticed the “as Age” text on the bottom of the SQL above. We must include that otherwise we will get an error that says something like “Every derived TABLE must have its own alias”.

Of course, instead of using a derived table in the query above, you can simply write something like “select max(age) from table”, but this example was chosen for it’s simplicity in illustrating what a derived table would look like, certainly not for its real world applicability.



## Summary of the difference between derived tables and subqueries

* derived tables are used in the FROM clause
* subqueries are used in the WHERE clause, but can also be used to select from one table and insert into another as we showed above

## What is the difference between correlated subqueries and uncorrelated subqueries?
Let’s start out with an example of what an uncorrelated subquery looks like, and then we can compare that with a correlated subquery. Here is an example of an uncorrelated subquery:

#### Example of an Uncorrelated Subquery

Here is an example of some SQL that represents an uncorrelated subquery:

```
select Salesperson.Name from Salesperson 
where Salesperson.ID NOT IN(
select Orders.salesperson_id from Orders, Customer 
where Orders.cust_id = Customer.ID 
and Customer.Name = 'Samsonic')
```

If the SQL above looks scary to you, don’t worry – it’s still easy to understand for our purposes here. The subquery portion of the SQL above begins after the “NOT IN” statement. The reason that the query above is an uncorrelated subquery is that the subquery can be run independently of the outer query. Basically, the subquery has no relationship with the outer query.

Now, a correlated subquery has the opposite property – the subquery can not be run independently of the outer query. You can take a look at this example of a correlated subquery below and easily see the difference yourself:

Example of a correlated subquery

```
SELECT *
FROM Employee Emp1
WHERE (1) = (
SELECT COUNT(DISTINCT(Emp2.Salary))
FROM Employee Emp2
WHERE Emp2.Salary > Emp1.Salary)
```

What you will notice in the correlated subquery above is that the inner subquery uses Emp1.Salary, but the alias Emp1 is created in the outer query. This is why it is called a correlated subquery, because the subquery references a value in it’s WHERE clause (in this case, it uses a column belonging to Emp1) that is used in the outer query.

### How does a correlated query work exactly?
It’s important to understand the order of operations in a correlated subquery. First, a row is processed in the outer query. Then, for that particular row the subquery is executed – so for each row processed by the outer query, the subquery will also be processed. In our example of a correlated subquery above, every time a row is processed for Emp1, the subquery will also choose that row’s value for Emp1.Salary and run. And then the outer query will move on to the next row, and the subquery will execute for that row’s value of Emp1.Salary. This will continue until the “WHERE (1) = (… )” condition is satisfied.
