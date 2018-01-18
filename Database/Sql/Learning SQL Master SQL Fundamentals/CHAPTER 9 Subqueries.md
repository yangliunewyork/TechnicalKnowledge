### What Is a Subquery? 

A subquery is a query contained within another SQL statement (which I refer to as the containing statement for the rest of this discussion). A subquery is always enclosed within parentheses, and it is usually executed prior to the containing statement. Like any query, a subquery returns a result set that may consist of: 

* A single row with a single column   
* Multiple rows with a single column   
* Multiple rows and columns  

The type of result set the subquery returns determines how it may be used and which operators the containing statement may use to interact with the data the subquery returns. When the containing statement has finished executing, the data returned by any subqueries is discarded, making a subquery act like a temporary table with statement scope (meaning that the server frees up any memory allocated to the subquery results after the SQL statement has finished execution).

### Subquery Types 

Along with the differences noted previously regarding the type of result set a subquery returns (single row/column, single row/multicolumn, or multiple columns), you can use another factor to differentiate subqueries; some subqueries are completely selfcontained (called __noncorrelated subqueries__), while others reference columns from the containing statement (called __correlated subqueries__). The next several sections explore these two subquery types and show the different operators that you can employ to interact with them.

### Noncorrelated Subqueries

The example from earlier in the chapter is a noncorrelated subquery; it may be executed alone and does not reference anything from the containing statement. Most subqueries that you encounter will be of this type unless you are writing update or delete statements, which frequently make use of correlated subqueries (more on this later). Along with being noncorrelated, the example from earlier in the chapter also returns a table comprising a single row and column. This type of subquery is known as a scalar subquery and can appear on either side of a condition using the usual operators (=, <>, <, >, <=, >=). The next example shows how you can use a scalar subquery in an inequality condition:

```sql
mysql> SELECT account_id, product_cd, cust_id, avail_balance
-> FROM account
-> WHERE open_emp_id <> (SELECT e.emp_id
-> FROM employee e INNER JOIN branch b
-> ON e.assigned_branch_id = b.branch_id
-> WHERE e.title = 'Head Teller' AND b.city = 'Woburn');
```

### Multiple-Row, Single-Column Subqueries

If your subquery returns more than one row, you will not be able to use it on one side of an equality condition, as the previous example demonstrated. However, there are four additional operators that you can use to build conditions with these types of subqueries.

##### The in and not in operators

While you can’t equate a single value to a set of values, you can check to see whether a single value can be found within a set of values. The next example, while it doesn’t use a subquery, demonstrates how to build a condition that uses the in operator to search for a value within a set of values:

```sql
mysql> SELECT emp_id, fname, lname, title
-> FROM employee
-> WHERE emp_id IN (SELECT superior_emp_id
-> FROM employee);
```

Along with seeing whether a value exists within a set of values, you can check the converse using the not in operator. Here’s another version of the previous query using not in instead of in:

```sql
mysql> SELECT emp_id, fname, lname, title
-> FROM employee
-> WHERE emp_id NOT IN (SELECT superior_emp_id
-> FROM employee
-> WHERE superior_emp_id IS NOT NULL);
```

##### The all operator

While the in operator is used to see whether an expression can be found within a set of expressions, the all operator allows you to make comparisons between a single value and every value in a set. To build such a condition, you will need to use one of the comparison operators (=, <>, <, >, etc.) in conjunction with the all operator. For example, the next query finds all employees whose employee IDs are not equal to any of the supervisor employee IDs:

```sql
mysql> SELECT emp_id, fname, lname, title
-> FROM employee
-> WHERE emp_id <> ALL (SELECT superior_emp_id
-> FROM employee
-> WHERE superior_emp_id IS NOT NULL);
```

Once again, the subquery returns the set of IDs for those employees who supervise other people, and the containing query returns data for each employee whose ID is not equal to all of the IDs returned by the subquery. In other words, the query finds all employees who are not supervisors. If this approach seems a bit clumsy to you, you are in good company; most people would prefer to phrase the query differently and avoid using the all operator. For example, this query generates the same results as the last example in the previous section, which used the not in operator. It’s a matter of preference, but I think that most people would find the version that uses not in to be easier to understand.

##### The any operator

Like the all operator, the any operator allows a value to be compared to the members of a set of values; unlike all, however, a condition using the any operator evaluates to true as soon as a single comparison is favorable. This is different from the previous example using the all operator, which evaluates to true only if comparisons against all members of the set are favorable. For example, you might want to find all accounts having an available balance greater than any of Frank Tucker’s accounts:

```sql
mysql> SELECT account_id, cust_id, product_cd, avail_balance
-> FROM account
-> WHERE avail_balance > ANY (SELECT a.avail_balance
-> FROM account a INNER JOIN individual i
-> ON a.cust_id = i.cust_id
-> WHERE i.fname = 'Frank' AND i.lname = 'Tucker');
```

### Multicolumn Subqueries

So far, all of the subquery examples in this chapter have returned a single column and one or more rows. In certain situations, however, you can use subqueries that return two or more columns. To show the utility of multiple-column subqueries, it might help to look first at an example that uses multiple, single-column subqueries:

```sql
mysql> SELECT account_id, product_cd, cust_id
-> FROM account
-> WHERE open_branch_id = (SELECT branch_id
-> FROM branch
-> WHERE name = 'Woburn Branch')
-> AND open_emp_id IN (SELECT emp_id
-> FROM employee
-> WHERE title = 'Teller' OR title = 'Head Teller');
```

This query uses two subqueries to identify the ID of the Woburn branch and the IDs of all bank tellers, and the containing query then uses this information to retrieve all checking accounts opened by a teller at the Woburn branch. However, since the employee table includes information about which branch each employee is assigned to, you can achieve the same results by comparing both the account.open_branch_id and account.open_emp_id columns to a single subquery against the employee and branch tables. To do so, your filter condition must name both columns from the account table surrounded by parentheses and in the same order as returned by the subquery, as in:

```sql
mysql> SELECT account_id, product_cd, cust_id
-> FROM account
-> WHERE (open_branch_id, open_emp_id) IN
-> (SELECT b.branch_id, e.emp_id
-> FROM branch b INNER JOIN employee e
-> ON b.branch_id = e.assigned_branch_id
-> WHERE b.name = 'Woburn Branch'
-> AND (e.title = 'Teller' OR e.title = 'Head Teller'));
```

This version of the query performs the same function as the previous example, but with a single subquery that returns two columns instead of two subqueries that each return a single column.












