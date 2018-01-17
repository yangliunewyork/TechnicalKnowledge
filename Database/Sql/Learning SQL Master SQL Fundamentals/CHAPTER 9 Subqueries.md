### What Is a Subquery? 

A subquery is a query contained within another SQL statement (which I refer to as the containing statement for the rest of this discussion). A subquery is always enclosed within parentheses, and it is usually executed prior to the containing statement. Like any query, a subquery returns a result set that may consist of: 

* A single row with a single column   
* Multiple rows with a single column   
* Multiple rows and columns  

The type of result set the subquery returns determines how it may be used and which operators the containing statement may use to interact with the data the subquery returns. When the containing statement has finished executing, the data returned by any subqueries is discarded, making a subquery act like a temporary table with statement scope (meaning that the server frees up any memory allocated to the subquery results after the SQL statement has finished execution).

### Subquery Types 

Along with the differences noted previously regarding the type of result set a subquery returns (single row/column, single row/multicolumn, or multiple columns), you can use another factor to differentiate subqueries; some subqueries are completely selfcontained (called __noncorrelated subqueries__), while others reference columns from the containing statement (called __correlated subqueries__). The next several sections explore these two subquery types and show the different operators that you can employ to interact with them.

### Noncorrelated Subqueries

