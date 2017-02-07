## In SQL, what’s the difference between an inner and outer join?
Joins are used to combine the data from two tables, with the result being a new, temporary table. The temporary table is created based on column(s) that the two tables share, which represent meaningful column(s) of comparison. The goal is to extract meaningful data from the resulting temporary table. Joins are performed based on something called a predicate, which specifies the condition to use in order to perform a join. A join can be either an inner join or an outer join, depending on how one wants the resulting table to look.

It is best to illustrate the differences between inner and outer joins by use of an example. Here we have 2 tables that we will use for our example:


#### Employee	
```
EmpID	EmpName
13	Jason
8	Alex
3	Ram
17	Babu
25	Johnson
```

#### Location
```
EmpID	EmpLoc
13	San Jose
8	Los Angeles
3	Pune, India
17	Chennai, India
39	Bangalore, India
```

It’s important to note that the very last row in the Employee table does not exist in the Employee Location table. Also, the very last row in the Employee Location table does not exist in the Employee table. These facts will prove to be significant in the discussion that follows.

## Outer Joins

Let’s start the explanation with outer joins. Outer joins can be be further divided into left outer joins, right outer joins, and full outer joins. Here is what the SQL for a left outer join would look like, using the tables above:

```
select * from employee left outer join location 
on employee.empID = location.empID;
```

In this SQL we are joining on the condition that the employee ID’s match in the rows tables. So, we will be essentially combining 2 tables into 1, based on the condition that the employee ID’s match. Note that we can get rid of the "outer" in left outer join, which will give us the SQL below. This is equivalent to what we have above.(__I personally always keep the ```outer``` keyword, and I think that is the best practice here )__.

```
select * from employee left join location 
on employee.empID = location.empID;
```

A left outer join retains all of the rows of the left table, regardless of whether there is a row that matches on the right table. The SQL above will give us the result set shown below.

```
Employee.EmpID	Employee.EmpName	Location.EmpID	Location.EmpLoc
13	Jason	13	San Jose
8	Alex	8	Los Angeles
3	Ram	3	Pune, India
17	Babu	17	Chennai, India
25	Johnson	NULL	NULL
```

### The Join Predicate – a geeky term you should know
Earlier we had mentioned something called a join predicate. In the SQL above, the join predicate is "on employee.empID = location.empID". This is the heart of any type of join, because it determines what common column between the 2 tables will be used to "join" the 2 tables. As you can see from the result set, all of the rows from the left table are returned when we do a left outer join. The last row of the Employee table (which contains the "Johson" entry) is displayed in the results even though there is no matching row in the Location table. As you can see, the non-matching columns in the last row are filled with a "NULL". So, we have "NULL" as the entry wherever there is no match.

A right outer join is pretty much the same thing as a left outer join, except that the rows that are retained are from the right table. This is what the SQL looks like:

```
select * from employee right outer join location 
on employee.empID = location.empID;

// taking out the "outer", this also works:

select * from employee right join location 
on employee.empID = location.empID;
```
Using the tables presented above, we can show what the result set of a right outer join would look like:

```
Employee.EmpID	Employee.EmpName	Location.EmpID	Location.EmpLoc
13	Jason	13	San Jose
8	Alex	8	Los Angeles
3	Ram	3	Pune, India
17	Babu	17	Chennai, India
NULL	NULL	39	Bangalore, India
```
We can see that the last row returned in the result set contains the row that was in the Location table, but not in the Employee table (the "Bangalore, India" entry). Because there is no matching row in the Employee table that has an employee ID of "39", we have NULL’s in the result set for the Employee columns.

## Inner Joins

Now that we’ve gone over outer joins, we can contrast those with the inner join. The difference between an inner join and an outer join is that an inner join will return only the rows that actually match based on the join predicate. Once again, this is best illustrated via an example. Here’s what the SQL for an inner join will look like:
```
select * from employee inner join location on 
employee.empID = location.empID
```

This can also be written as:

```
select * from employee, location
where employee.empID = location.empID
```

Now, here is what the result of running that SQL would look like:

```
Employee.EmpID	Employee.EmpName	Location.EmpID	Location.EmpLoc
13	Jason	13	San Jose
8	Alex	8	Los Angeles
3	Ram	3	Pune, India
17	Babu	17	Chennai, India
```

### Inner vs Outer Joins

We can see that an inner join will only return rows in which there is a match based on the join predicate. In this case, what that means is anytime the Employee and Location table share an Employee ID, a row will be generated in the results to show the match. Looking at the original tables, one can see that those Employee ID’s that are shared by those tables are displayed in the results. But, with a left or right outer join, the result set will retain all of the rows from either the left or right table.


## Self Join

### What is a self join? Explain it with an example and tutorial.

Let’s illustrate the need for a self join with an example. Suppose we have the following table – that is called employee. The employee table has 2 columns – one for the employee name (called employee_name), and one for the employee location (called employee_location):

employee 
```
employee_name	employee_location
Joe	New York
Sunil	India
Alex	Russia
Albert	Canada
Jack	New York
```
Now, suppose we want to find out which employees are from the same location as the employee named Joe. In this example, that location would be New York. Let’s assume – for the sake of our example – that we can not just directly search the table for people who live in New York with a simple query like this (maybe because we don’t want to hardcode the city name) in the SQL query:
```
SELECT employee_name
FROM employee
WHERE employee_location = "New York"
```
So, instead of a query like that what we could do is write a nested SQL query (basically a query within another query – which is more commonly called a subquery) like this:
```
SELECT employee_name
FROM employee
WHERE employee_location in
( SELECT employee_location
FROM employee
WHERE employee_name = "Joe")
```

__A subquery is inefficient__

Using a subquery for such a simple question is inefficient. Is there a more efficient and elegant solution to this problem?

It turns out that there is a more efficient solution – we can use something called a self join. __A self join is basically when a table is joined to itself. The way you should visualize a self join for a given table is by imagining that a join is performed between two identical copies of that table. And that is exactly why it is called a self join – because of the fact that it’s just the same table being joined to another copy of itself rather than being joined with a different table.__

#### A self join must have aliases
In a self join we are joining the same table to itself by essentially creating two copies of that table. But, how do we distinguish between the two different copies of the table – because there is only one table name after all? Well, when we do a self join, the table names absolutely must use aliases otherwise the column names would be ambiguous. In other words, we would not know which of the two copies of the table’s columns is being referenced without using an alias for each copy of the table. If you don’t already know what an alias is, it’s simply another name given to a table – think of an alias as a nickname – and that nickname is then used in the SQL query to reference the table. Because we need two copies of the employee table, we will just use the aliases e1 and e2 for the employee table when we do a self join.

#### Self join predicate

As with any join there must be a condition upon which a self join is performed – we can not just arbitrarily say “do a self join”, without specifying some condition. That condition will be our join predicate. If you need a refresher on join predicates (or just joins in general) then check this link out: Inner vs. Outer joins.

Now, let’s come up with a solution to the original problem using a self join instead of a subquery. This will help illustrate how exactly a self join works. The key question that we must ask ourselves is what should our join predicate be in this example? Well, we want to find all the employees who have the same location as Joe.

Because we want to match between our two tables (both of which are the same table – employee – aliased as e1 and e2) on location our join predicate should clearly be “WHERE e1.employee_location = e2.employee_location”. But is that enough to give us what we want? No, it’s not, because we also want to filter the rows returned since we only want people who are from the same location as Joe.

So, how can we filter the rows returned so that only people from Joe’s location are returned? Well, what we can do is simply add a condition on one of the tables (e2 in our example) so that it only returns the row where the name is Joe. Then, the other table (e1) will match up all the names that have the same location in e2, because of our join predicate – which is “WHERE e1.employee_location = e2.employee_location”. We will then just select the names from e1, and not e2 because e2 will only have Joe’s name. If that’s confusing then keep reading further to understand more about how the query will work.

So, the self join query that we come up with looks like this:

```
SELECT e1.employee_name
FROM employee e1, employee e2
WHERE e1.employee_location = e2.employee_location
AND e2.employee_name="Joe";
```
This query will return the names Joe and Jack – since Jack is the only other person who lives in New York like Joe.

Generally, queries that refer to the same table can be greatly simplified by re-writing the queries as self joins. And, there is definitely a performance benefit for this as well.

#### What does a self join look like?

It will help tremendously to actually visualize the actual results of a self join internally. Remember that a self join is just like any other join, where the two tables are merged into one temporary table. First off, you should visualize that we have two separate copies of the employee table, which are given aliases of e1 and e2. These copies would simply look like this – note that we shortened the column names from employee_name and employee_location to just Name and Location for convenience:

e1	
```
Name	Location
Joe	New York
Sunil	India
Alex	Russia
Albert	Canada
Jack	New York
```
e2
```
Name	Location
Joe	New York
Sunil	India
Alex	Russia
Albert	Canada
Jack	New York
```

And the final results of running the self join query above – the actual joined table – would look like this:

```
e1.employee_name	e1.employee_location	e2.employee_name	e2.employee_location
Joe	New York	Joe	New York
Jack	New York	Joe	New York
```
### Self joins versus inner joins
Are self joins and inner joins the same? You might be wondering if all self joins are also inner joins. After all, in our example above our self join uses an inner join because only the rows that match based on the join predicate are returned – non-matching rows are not returned. Well, it turns out that a self join and inner join are completely different concepts. A self join could just as well be an outer join or an inner join – it just depends on how the query is written. We could easily change the query we used above to do a LEFT OUTER JOIN – while the query still remains a self join – but that wouldn’t give us the results we want in our example. So, we use an implied inner join instead because that gives us the correct results. Remember that a query is a self join as long as the two tables being joined are exactly the same table, but whether it’s an inner join or outer join depends on what is specified in the SQL. And, inner/outer joins are separate concepts entirely from a self join.


#### Self joins manager employee example

The most commonly used example for self joins is the classic employee manager table. The table is called Employee, but holds all employees – including their managers. Every employee has an ID, and there is also a column for the manager ID. So, for example, let’s say we have a table that looks like this – and we call it Employee:
```
EmployeeID	Name	ManagerID
1	Sam	10
2	Harry	4
4	Manager	NULL
10	AnotherManager	NULL
```
Notice that in the table above there are two managers, conveniently named “Manager” and “AnotherManager”. And, those managers don’t have managers of their own – as noted by the NULL value in their Manager column.

Now, given the table above, how can we return results that will show each employee’s name, and his/her manager’s name in nicely arranged results – with the employee in one column and his/her manager’s name in the other column. Well, it turns out we can use a self join to do this. Try to come up with the SQL on your own before reading our answer.

#### Self join manager employee answer

In order to come up with a correct answer for this problem, our goal should be to perform a self join that will have both the employee information and manager information in one row. First off, since we are doing a self join, it helps to visualize the one table as two tables – let’s give them aliases of e1 and e2. Now, with that in mind, we want the employee’s information on one side of the joined table and the manager’s information on the other side of the joined table. So, let’s just say that we want e1 to hold the employee information and e2 to hold the corresponding manager’s information. What should our join predicate be in that case?

Well, the join predicate should look like “ON e1.ManagerID = e2.EmployeeID” – this basically says that we should join the two tables (a self join) based on the condition that the manager ID in e1 is equal to the employee ID in e2. In other words, an employee’s manager in e1 should have the manager’s information in e2. An illustration will help clarify this. Suppose we use that predicate and just select everything after we join the tables. So, our SQL would look like this:

```
SELECT *
FROM Employee e1
INNER JOIN Employee e2
ON e1.ManagerID = e2.EmployeeID
```

The results of running the query above would look like this:

```
e1.EmployeeID	e1.Name	e1.ManagerID	e2.EmployeeID	e2.Name	e2.ManagerID
1	Sam	10	10	AnotherManager	NULL
2	Harry	4	4	Manager	NULL
```

Note that there are only 2 rows returned – this is because an inner join is performed, which means that only when there is a match between employee ID’s and manager ID’s will there be a result returned. And since there are 2 people without managers (who have a manager ID of NULL), they will not be returned as part of table e1, because no employees have a matching ID of NULL.

Now, remember that we only want to return the names of the employee and corresponding manager as a pair. So, we can fine-tune the SQL as follows:
```
SELECT e1.Name, e2.Name
FROM Employee e1
INNER JOIN Employee e2
ON e1.ManagerID = e2.EmployeeID
```
unning the SQL above would return:
```
Sam    AnotherManager
Harry  Manager
```
And that is the answer to the employee manager problem using a self join!
