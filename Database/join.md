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
