### What is Derived Table ?
In very basic terms, a derived table is a virtual table that’s returned from a SELECT statement. This concept is similar to temporary tables, but using derived tables in your SELECT statements is much simpler because they don’t require all the steps that temporary tables do. There has been much debate as to whether derived tables, views, or temporary tables are actually faster in terms of performance. Supporters of derived tables cite that they allow to you to replace the code required for managing a temporary table with a single command, which can be faster than the series it replaces. The fact is that there is no simple answer, as different queries require different optimizations; each has its place in the database administrator’s arsenal.</br>

### Derived Tabls vs Sub-query
##### Sub-query
A lot of people use the terms derived tables and subqueries interchangeably. Not surprising, considering that a subquery is defined as any query that appears within another SQL command. These can be further broken down into stand-alone sub-queries, which are those that you can run independent of the command that contains it, and correlated, which relate to fields from the containing command. The most common use for subqueries is filtering data in the WHERE clause of a SQL command or in the column list. Here’s a subquery that retrieves a list of all customers who placed orders in the specified year. The main query uses that list to find the reverse - those who didn't order in that year:
```
SELECT CompanyName

SELECT CompanyName
FROM   Customers
WHERE  CustomerID NOT IN (SELECT CustomerID
                          FROM   Orders
                          WHERE  YEAR(OrderDate) = 2003);
```
This statement fetches basic client information. A subquery performs a lookup on another table to retrieve the birth_country description:
```
SELECT itt.family_nme,
       itt.given_nme,
       itt.birth_dt,
       (SELECT english_desc 
        FROM   vcode_value 
        WHERE  code_value_id = itt.birth_country_cd) AS 'birth_country'
        FROM identity_tombstone_id AS itt;
```
The above statement can also be said to contain a correlated subquery because it refers back to the outer main query.

#### Derived tables

A derived table is basically a subquery, except it is always in the FROM clause of a SQL statement. The reason it is called a derived table is because it essentially functions as a table as far as the entire query is concerned.

But, remember that a derived table only exists in the query in which it is created. So, derived tables are not actually part of the database schema because they are not real tables.
Compare the previous two queries to the following one:
```
SELECT u.last_name, 
       a.state
FROM   User AS u,
       (SELECT user_id, state FROM Address) AS a
WHERE  u.id = a.user_id;
```
The above query selects directly from the derived table created by the subquery. Of course, in the simple example above, you could just as easily define the join without the derived table, but as we’ll see in the next section, there are other, more complex criteria, which call for the use of one or more derived tables.

##### Summary of the difference between derived tables and subqueries

In simplest terms, a summary of the differences between derived tables and subqueries are:

* derived tables are used in the FROM clause
* subqueries are used in the WHERE clause, but can also  be used to select from one table and insert into  another as we showed above
