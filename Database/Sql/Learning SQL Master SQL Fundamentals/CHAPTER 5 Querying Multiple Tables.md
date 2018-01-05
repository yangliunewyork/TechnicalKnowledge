### Cartesian Product

We have an ```employee`` table with 18 records, and a ```department``` with 3 records.

Here’s a query that retrieves the employee’s first and last names along with the department name, with a from clause naming both tables separated by the join keyword:

```sql
mysql> SELECT e.fname, e.lname, d.name
-> FROM employee e JOIN department d;
```

Because the query didn’t specify how the two tables should be joined, the database server generated the __Cartesian product__, which is every permutation of the two tables (18 employees × 3 departments = 54 permutations). This type of join is known as a __cross join__, and it is rarely used (on purpose, at least).

### Inner Joins

To modify the previous query so that only 18 rows are included in the result set (one for each employee), you need to describe how the two tables are related. Earlier, I showed that the employee.dept_id column serves as the link between the two tables, so this information needs to be added to the ON subclause of the from clause:

```sql
mysql> SELECT e.fname, e.lname, d.name
-> FROM employee e JOIN department d
-> ON e.dept_id = d.dept_id;
```

Instead of 54 rows, you now have the expected 18 rows due to the addition of the on subclause, which instructs the server to join the employee and department tables by using the dept_id column to traverse from one table to the other.

If a value exists for the dept_id column in one table but not the other, then the join fails for the rows containing that value and those rows are excluded from the result set. This type of join is known as an __inner join__, and it is the most commonly used type of join. To clarify, if the department table contains a fourth row for the marketing department, but no employees have been assigned to that department, then the marketing department would not be included in the result set. Likewise, if some of the employees had been assigned to department ID 99, which doesn’t exist in the department table, then these employees would be left out of the result set. If you want to include all rows from one table or the other regardless of whether a match exists, you need to specify an __outer join__.

In the previous example, I did not specify in the from clause which type of join to use. However, when you wish to join two tables using an inner join, you should explicitly specify this in your from clause; here’s the same example, with the addition of the join type (note the keyword INNER):

```sql
mysql> SELECT e.fname, e.lname, d.name
-> FROM employee e INNER JOIN department d
-> ON e.dept_id = d.dept_id;
```

If you do not specify the type of join, then the server will do an inner join by default. As you will see later in the book, however, there are several types of joins, so you should get in the habit of specifying the exact type of join that you require.

### Joining Three or More Tables

```sql
mysql> SELECT a.account_id, c.fed_id, e.fname, e.lname
-> FROM account a INNER JOIN customer c
-> ON a.cust_id = c.cust_id
-> INNER JOIN employee e
-> ON a.open_emp_id = e.emp_id
-> WHERE c.cust_type_cd = 'B';
```

At first glance, the order in which the tables are named might cause you to think that the employee table is being joined to the customer table, since the account table is named first, followed by the customer table, and then the employee table. If you switch the order in which the first two tables appear, however, you will get the exact same results.

One way to think of a query that uses three or more tables is as a snowball rolling down a hill. The first two tables get the ball rolling, and each subsequent table gets tacked on to the snowball as it heads downhill. You can think of the snowball as the _intermediate result set_, which is picking up more and more columns as subsequent tables are joined. _Therefore, the employee table is not really being joined to the account table, but rather the intermediate result set created when the customer and account tables were joined._

#### Does Join Order Matter?

If you are confused about why all three versions of the account/employee/customer query yield the same results, keep in mind that _SQL is a nonprocedural language, meaning that you describe what you want to retrieve and which database objects need to be involved, but it is up to the database server to determine how best to execute your query_. Using statistics gathered from your database objects, the server must pick one of three tables as a starting point (the chosen table is thereafter known as the driving table), and then decide in which order to join the remaining tables. Therefore, the order in which tables appear in your from clause is not significant.

#### Using Subqueries As Tables

You have already seen several examples of queries that use three tables, but there is one variation worth mentioning: what to do if some of the data sets are generated by subqueries.

```sql
 SELECT a.account_id, a.cust_id, a.open_date, a.product_cd
 FROM account a INNER JOIN
  (SELECT emp_id, assigned_branch_id
  WHERE start_date < '2007-01-01'
  AND (title = 'Teller' OR title = 'Head Teller')) e
 ON a.open_emp_id = e.emp_id
  INNER JOIN
  (SELECT branch_id
   FROM branch
  WHERE name = 'Woburn Branch') b
  ON e.assigned_branch_id = b.branch_id;
```

### Using the Same Table Twice































