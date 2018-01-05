When performing set operations on two data sets, the following guidelines must apply: 

* Both data sets must have the same number of columns.   
* The data types of each column across the two data sets must be the same (or the server must be able to convert one to the other).  

# Set Operators

### The union Operator

The UNION and UNION ALL operators allow you to combine multiple data sets. The difference between the two is that __UNION sorts the combined set and removes duplicates__, whereas UNION ALL does not. With UNION ALL, the number of rows in the final data set will always equal the sum of the number of rows in the sets being combined. This operation is the simplest set operation to perform (from the server’s point of view), since there is no need for the server to check for overlapping data.

### The intersect Operator

The ANSI SQL specification includes the INTERSECT operator for performing intersections.

### The except Operator

The ANSI SQL specification includes the EXCEPT operator for performing the except operation.

# Set Operation Rules

The following sections outline some rules that you must follow when working with compound queries.

#### Sorting Compound Query Results

If you want the results of your compound query to be sorted, you can add an order by clause after the last query. When specifying column names in the order by clause, you will need to choose from the column names in the first query of the compound query. If you specify a column name from the second query in your order by clause, you will see error。

In general, compound queries containing three or more queries are evaluated in order from top to bottom, but with the following caveats:

* The ANSI SQL specification calls for the intersect operator to have precedence over the other set operators.
* You may dictate the order in which queries are combined by enclosing multiple queries in parentheses.




