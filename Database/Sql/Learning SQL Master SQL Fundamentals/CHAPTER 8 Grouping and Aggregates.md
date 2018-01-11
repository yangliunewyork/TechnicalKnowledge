# Grouping Concepts

Sometimes you will want to find trends in your data that will require the database server to cook the data a bit before you can generate the results you are looking for. For example, let’s say that you are in charge of operations at the bank, and you would like to find out how many accounts are being opened by each bank teller. You could issue a simple query to look at the raw data:

```sql
mysql> SELECT open_emp_id
-> FROM account;
```

```
+-------------+
| open_emp_id |
+-------------+
| 1 |
| 1 |
| 1 |
| 1 |
| 1 |
| 1 |
| 1 |
| 1 |
| 10 |
| 10 |
| 10 |
| 10 |
| 10 |
| 10 |
| 10 |
| 13 |
| 13 |
| 13 |
| 16 |
| 16 |
| 16 |
| 16 |
| 16 |
| 16 |
+-------------+
24 rows in set (0.01 sec)
```

With only 24 rows in the account table, it is relatively easy to see that four different employees opened accounts and that employee ID 16 has opened six accounts; however, if the bank has dozens of employees and thousands of accounts, this approach would prove tedious and error-prone. 

Instead, you can ask the database server to group the data for you by using the __group by__ clause. Here’s the same query but employing a group by clause to group the account data by employee ID:

```sql
mysql> SELECT open_emp_id
-> FROM account
-> GROUP BY open_emp_id;
```

```
+-------------+
| open_emp_id |
+-------------+
| 1 |
| 10 |
| 13 |
| 16 |
+-------------+
4 rows in set (0.00 sec)
```

The result set contains one row for each distinct value in the open_emp_id column, resulting in four rows instead of the full 24 rows. The reason for the smaller result set is that each of the four employees opened more than one account. To see how many accounts each teller opened, you can use an __aggregate function__ in the select clause to count the number of rows in each group:

```sql
mysql> SELECT open_emp_id, COUNT(*) as how_many
-> FROM account
-> GROUP BY open_emp_id;
```

```
+-------------+----------+
| open_emp_id | how_many |
+-------------+----------+
| 1 | 8 |
| 10 | 7 |
| 13 | 3 |
| 16 | 6 |
+-------------+----------+
4 rows in set (0.00 sec)
```

The aggregate function count() counts the number of rows in each group, and the asterisk tells the server to count everything in the group. Using the combination of a group by clause and the count() aggregate function, you are able to generate exactly the data needed to answer the business question without having to look at the raw data.

When grouping data, you may need to filter out undesired data from your result set based on groups of data rather than based on the raw data. __Since the group by clause runs after the where clause has been evaluated, you cannot add filter conditions to your where clause for this purpose.__ For example, here’s an attempt to filter out any cases where an employee has opened fewer than five accounts:

```sql
mysql> SELECT open_emp_id, COUNT(*) how_many
-> FROM account
-> WHERE COUNT(*) > 4
-> GROUP BY open_emp_id;
ERROR 1111 (HY000): Invalid use of group function
```

You cannot refer to the aggregate function count(*) in your where clause, because the groups have not yet been generated at the time the where clause is evaluated. Instead, you must put your group filter conditions in the having clause. Here’s what the query would look like using having:

```sql
mysql> SELECT open_emp_id, COUNT(*) how_many
-> FROM account
-> GROUP BY open_emp_id
-> HAVING COUNT(*) > 4;
```

```
+-------------+----------+
| open_emp_id | how_many |
+-------------+----------+
| 1 | 8 |
| 10 | 7 |
| 16 | 6 |
+-------------+----------+
3 rows in set (0.00 sec)
```

Because those groups containing fewer than five members have been filtered out via the having clause, the result set now contains only those employees who have opened five or more accounts, thus eliminating employee ID 13 from the results.

# Aggregate Functions

Aggregate functions perform a specific operation over all rows in a group. Although every database server has its own set of specialty aggregate functions, the common aggregate functions implemented by all major servers include: 

* Max() Returns the maximum value within a set   
* Min() Returns the minimum value within a set   
* Avg() Returns the average value across a set  
* Sum() Returns the sum of the values across a set  
* Count() Returns the number of values in a set  

Here’s a query that uses all of the common aggregate functions to analyze the available balances for all checking accounts:

```sql
mysql> SELECT MAX(avail_balance) max_balance,
-> MIN(avail_balance) min_balance,
-> AVG(avail_balance) avg_balance,
-> SUM(avail_balance) tot_balance,
-> COUNT(*) num_accounts
-> FROM account
-> WHERE product_cd = 'CHK';
```

```
+-------------+-------------+-------------+-------------+--------------+
| max_balance | min_balance | avg_balance | tot_balance | num_accounts |
+-------------+-------------+-------------+-------------+--------------+
| 38552.05 | 122.37 | 7300.800985 | 73008.01 | 10 |
+-------------+-------------+-------------+-------------+--------------+
1 row in set (0.09 sec)
```

### Implicit Versus Explicit Groups

