## What’s referential integrity?

Referential integrity is a relational database concept in which multiple tables share a relationship based on the data stored in the tables, and that relationship must remain consistent.

The concept of referential integrity, and one way in which it’s enforced, is best illustrated by an example. Suppose company X has 2 tables, an Employee table, and an Employee Salary table. In the Employee table we have 2 columns – the employee ID and the employee name. In the Employee Salary table, we have 2 columns – the employee ID and the salary for the given ID.

Now, suppose we wanted to remove an employee because he no longer works at company X. Then, we would remove his entry in the Employee table. Because he also exists in the Employee Salary table, we would also have to manually remove him from there also. Manually removing the employee from the Employee Salary table can become quite a pain. And if there are other tables in which Company X uses that employee then he would have to be deleted from those tables as well – an even bigger pain.

By enforcing referential integrity, we can solve that problem, so that we wouldn’t have to manually delete him from the Employee Salary table (or any others). Here’s how: first we would define the employee ID column in the Employee table to be our primary key. Then, we would define the employee ID column in the Employee Salary table to be a foreign key that points to a primary key that is the employee ID column in the Employee table. Once we define our foreign to primary key relationship, we would need to add what’s called a ‘constraint’ to the Employee Salary table. The constraint that we would add in particular is called a ‘cascading delete’ – this would mean that any time an employee is removed from the Employee table, any entries that employee has in the Employee Salary table would also automatically be removed from the Employee Salary table.

Note in the example given above that referential integrity is something that must be enforced, and that we enforced only one rule of referential integrity (the cascading delete). There are actually 3 rules that referential integrity enforces:

* 1.We may not add a record to the Employee Salary table unless the foreign key for that record  points to an existing employee in the Employee table.

2.If a record in the Employee table is deleted, all corresponding records in the Employee Salary table must be deleted using a cascading delete.  This was the example we had given earlier.
  
3.If the primary key for a record in the Employee table changes, all corresponding records in the Employee Salary table must be modified using what's called a cascading update.

It’s worth noting that most RDBMS’s – relational databases like Oracle, DB2, Teradata, etc. – can automatically enforce referential integrity if the right settings are in place. But, a large part of the burden of maintaining referential integrity is placed upon whoever designs the database schema – basically whoever defined the tables and their corresponding structure/relationships in the database that you are using. Referential integrity is an important concept and you simply must know it for any programmer interview.
