### What is database trigger
A trigger is a special kind of stored procedure that automatically executes when an event occurs in the database server. DML triggers execute when a user tries to modify data through a data manipulation language (DML) event. DML events are INSERT, UPDATE, or DELETE statements on a table or view. These triggers fire when any valid event is fired, regardless of whether or not any table rows are affected. 

### How trigger works
A  trigger  is a stored procedure that goes into effect when you insert, delete, or update data in a table. You can use triggers to perform a number of automatic actions, such as cascading changes through related tables, enforcing column restrictions, comparing the results of data modifications, and maintaining the referential integrity of data across a database.
Triggers are automatic. They work no matter what caused the data modification—a clerk’s data entry or an application action. A trigger is specific to one or more of the data modification operations,  update,  insert , and  delete  and is executed once for each SQL statement.

### Usage
Triggers are most useful in these situations:
* Triggers can cascade changes through related tables in the database. 
* Triggers can disallow, or roll  back, changes that would violate referential integrity, canceling the attempted data modification transaction. 
* Triggers can enforce restrictions that are much more complex than those that are defined with rules.  Unlike rules, triggers can reference columns or database objects. 
* Triggers can perform simple “what if” analyses.


### Using triggers vs. integrity constraints
referential integrity constraints cannot :
* Cascade changes through related tables in the database
* Enforce complex restrictions by referencing other columns or database objects
* Perform “what if” analyses

Also, referential integrity constraints do not roll back the current transaction as a result of enforcing data integrity. With triggers, you can either roll back or continue the transaction, depending on how you handle referential integrity.



### Create Trigger
```
create trigger [ owner .] trigger_name  
on [ owner .] table_name 
{for {insert, update, delete} 
as SQL_statements
```

Example:
```
USE AdventureWorks2012;
GO
IF OBJECT_ID ('Purchasing.LowCredit','TR') IS NOT NULL
   DROP TRIGGER Purchasing.LowCredit;
GO
-- This trigger prevents a row from being inserted in the Purchasing.PurchaseOrderHeader table
-- when the credit rating of the specified vendor is set to 5 (below average).

CREATE TRIGGER Purchasing.LowCredit ON Purchasing.PurchaseOrderHeader
AFTER INSERT
AS
IF EXISTS (SELECT *
           FROM Purchasing.PurchaseOrderHeader p 
           JOIN inserted AS i 
           ON p.PurchaseOrderID = i.PurchaseOrderID 
           JOIN Purchasing.Vendor AS v 
           ON v.BusinessEntityID = p.VendorID
           WHERE v.CreditRating = 5
          )
BEGIN
RAISERROR ('A vendor''s credit rating is too low to accept new
purchase orders.', 16, 1);
ROLLBACK TRANSACTION;
RETURN 
END;
GO
```
### SQL statements not allowed in Trigger
* All create  commands, including create database,  create   table,  create index ,  create   procedure,  create   default,  create   rule ,  create   trigger , and  create   view 
* All drop commands
*  alter table and  alter database 
* truncate   table 
* grant and  revoke
* update  statistics
* reconfigure 
* load database  and  load transaction
* disk init,  disk mirror ,  disk refit ,  disk reinit ,  disk remirror ,  disk unmirror
* select   into
