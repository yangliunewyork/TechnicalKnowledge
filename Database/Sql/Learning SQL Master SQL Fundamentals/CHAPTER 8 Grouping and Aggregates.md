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

In the previous example, every value returned by the query is generated by an aggregate function, and the aggregate functions are applied across the group of rows specified by the filter condition product_cd = 'CHK'. Since there is no group by clause, there is a single, _implicit group_ (all rows returned by the query).

In most cases, however, you will want to retrieve additional columns along with columns generated by aggregate functions. What if, for example, you wanted to extend the previous query to execute the same five aggregate functions for each product type, instead of just for checking accounts? For this query, you would want to retrieve the product_cd column along with the five aggregate functions, as in:

```sql
SELECT product_cd,
MAX(avail_balance) max_balance,
MIN(avail_balance) min_balance,
AVG(avail_balance) avg_balance,
SUM(avail_balance) tot_balance,
COUNT(*) num_accounts
FROM account;
```

However, if you try to execute the query, you will receive the following error:

```
ERROR 1140 (42000): Mixing of GROUP columns (MIN(),MAX(),COUNT(),...) with no GROUP
columns is illegal if there is no GROUP BY clause
```

While it may be obvious to you that you want the aggregate functions applied to each set of products found in the account table, this query fails because you have not explicitly specified how the data should be grouped. Therefore, you will need to add a group by clause to specify over which group of rows the aggregate functions should be applied:

```
mysql> SELECT product_cd,
-> MAX(avail_balance) max_balance,
-> MIN(avail_balance) min_balance,
-> AVG(avail_balance) avg_balance,
-> SUM(avail_balance) tot_balance,
-> COUNT(*) num_accts
-> FROM account
-> GROUP BY product_cd;
```

With the inclusion of the group by clause, the server knows to group together rows having the same value in the product_cd column first and then to apply the five aggregate functions to each of the groups.

### How Nulls Are Handled

When performing aggregations, or, indeed, any type of numeric calculation, you should always consider how null values might affect the outcome of your calculation.

The difference is that count(\*) counts the number of rows, whereas count(val) counts the number of values contained in the val column and ignores any null values encountered.

# Generating Groups

People are rarely interested in looking at raw data; instead, people engaging in data analysis will want to manipulate the raw data to better suit their needs. Examples of common data manipulations include:

* Generating totals for a geographic region, such as total European sales  
* Finding outliers, such as the top salesperson for 2005  
* Determining frequencies, such as the number of new accounts opened for each branch  

To answer these types of queries, you will need to ask the database server to group rows together by one or more columns or expressions. As you have seen already in several examples, the group by clause is the mechanism for grouping data within a query. In this section, you will see how to group data by one or more columns, how to group data using expressions, and how to generate rollups within groups.

# Group Filter Conditions

When grouping data, you also can apply filter conditions to the data after the groups have been generated. The having clause is where you should place these types of filter conditions. Consider the following example:

```sql
mysql> SELECT product_cd, SUM(avail_balance) prod_balance
-> FROM account
-> WHERE status = 'ACTIVE'
-> GROUP BY product_cd
-> HAVING SUM(avail_balance) >= 10000;
```

This query has two filter conditions: one in the where clause, which filters out inactive accounts, and the other in the having clause, which filters out any product whose total available balance is less than $10,000. Thus, one of the filters acts on data before it is grouped, and the other filter acts on data after the groups have been created.

If you mistakenly put both filters in the where clause, you will see the following error:

```sql
mysql> SELECT product_cd, SUM(avail_balance) prod_balance
-> FROM account
-> WHERE status = 'ACTIVE'
-> AND SUM(avail_balance) > 10000
-> GROUP BY product_cd;
ERROR 1111 (HY000): Invalid use of group function
```

This query fails because you cannot include an aggregate function in a query’s where clause. This is because the filters in the where clause are evaluated before the grouping occurs, so the server can’t yet perform any functions on groups.

__When adding filters to a query that includes a group by clause, think carefully about whether the filter acts on raw data, in which case it belongs in the where clause, or on grouped data, in which case it belongs in the having clause.__

