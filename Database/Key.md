## The Definition of A Key in SQL

According to the SQL Standard, a key is a subset of columns in a table that allow a row to be uniquely identified. So, a key can be more than just one column. And, every row in the table will have a unique value for the key – or a unique combination of values if the key consists of more than just one column.

### Can a key have NULL values in SQL?

According to the SQL standard, a key is not allowed to have values that are NULL-able. Any key that has more columns than necessary to uniquely identify each row in the table is called a super-key (think of it as a super-set). But, if the key has the minimum amount of columns necessary to uniquely identify each row then it is called a minimal super-key. A minimal super-key is also known as a candidate key, and there must be one or more candidate keys in a table.

## Keys in actual RDBMS implementations

Even though the SQL standard says that a key can not be NULL, in practice actual RDBMS implementations (like SQL Server and Oracle), allow both foreign and unique keys to actually be NULL. And there are plenty of times when that actually makes sense. However, a primary key can never be NULL.

## In SQL, what are the differences between primary, foreign, and unique keys?

The one thing that primary, unique, and foreign keys all have in common is the fact that each type of key can consist of more than just one column from a given table. In other words, foreign, primary, and unique keys are not restricted to having just one column from a given table – each type of key can cover multiple columns. So, that is one feature that all the different types of keys share – they can each be comprised of more than just one column, which is something that many people in software are not aware of.

Of course, the database programmer is the one who will actually define which columns are covered by a foreign, primary, or unique key. That is one similarity all those keys share, but there are also some major differences that exist between primary, unique, and foreign keys. We will go over those differences in this article. But first, we want to give a thorough explanation of why foreign keys are necessary in some situations.

### What is the point of having a foreign key?

Foreign keys are used to reference unique columns in another table. So, for example, a foreign key can be defined on one table A, and it can reference some unique column(s) in another table B. Why would you want a foreign key? Well, whenever it makes sense to have a relationship between columns in two different tables.

#### An example of when a foreign key is necessary

Suppose that we have an Employee table and an Employee Salary table. Also assume that every employee has a unique ID. The Employee table could be said to have the ‘master list’ of all Employee ID’s in the company. But, if we want to store employees salaries in another table, then do we want to recreate the entire master list of employee ID’s in the Employee Salary table as well? No – we don’t want to do that because it’s inefficient. It would make a lot more sense to just define a relationship between an Employee ID column in the Employee Salary table and the “master” Employee ID column in the Employee table – one where the Employee Salary table can just reference the employee ID in the Employee table. This way, whenever someone’s employee ID is updated in the Employee table, it will also automatically get updated in the Employee Salary table. Sounds good right? So now, nobody has to manually update the employee ID’s in the Employee Salary table every time the ID is update in the master list inside the Employee table. And, if an employee is removed from the Employee table, he/she will also automatically be removed (by the RDBMS) from the Employee Salary table – of course all of this behavior has to be defined by the database programmer, but hopefully you get the point.

#### Foreign keys and referential integrity

Foreign keys have a lot to do with the concept of referential integrity. What we discussed in the previous paragraph are some of the principles behind referential integrity. You can and should read a more in depth article on that concept here: Referential integrity explained.

##### Can a table have multiple unique, foreign, and/or primary keys?
 A table can have multiple unique and foreign keys. However, a table can have only one primary key.
##### Can a unique key have NULL values? Can a primary key have NULL values?
Unique key columns are allowed to hold NULL values. The values in a primary key column, however, can never be NULL.
##### Can a foreign key reference a non-primary key?
Yes, a foreign key can actually reference a key that is not the primary key of a table. But, a foreign key must reference a unique key.

##### Can a foreign key contain null values?

Yes, a foreign key can hold NULL values. Because foreign keys can reference unique, non-primary keys – which can hold NULL values – this means that foreign keys can themselves hold NULL values as well.

##### Some other differences between foreign, primary, and unique keys

While unique and primary keys both enforce uniqueness on the column(s) of one table, foreign keys define a relationship between two tables. A foreign key identifies a column or group of columns in one (referencing) table that refers to a column or group of columns in another (referenced) table – in our example above, the Employee table is the referenced table and the Employee Salary table is the referencing table.

As we stated earlier, both unique and primary keys can be referenced by foreign keys.

## Natural key
You have probably come across the term natural key within the context of SQL and data warehouses. What exactly is a natural key? A natural key is a key composed of columns that actually have a logical relationship to other columns within a table. What does that mean in plain English? Well, let’s go through an example of a natural key.

### Natural Key Example
Consider a table called People. If we use the columns First_Name, Last_Name, and Address together to form a key then that would be a natural key because those columns are something that are natural to people, and there is definitely a logical relationship between those columns and any other columns that may exist in the table.

### Why is it called a natural key?

The reason it’s called a natural key is because the columns that belong to the key are just naturally a part of the table and have a relationship with other columns in the table. So, a natural key already exists within a table – and columns do not need to be added just to create an “artificial” key.

#### Natural keys versus business keys

Natural keys are often also called business keys – so both terms mean exactly the same thing.

#### Natural keys versus domain keys

Domain keys also mean the same thing as natural keys.

#### Natural keys versus surrogate keys

Natural keys are often compared to surrogate keys. What exactly is a surrogate key? Well, first consider the fact that the word surrogate literally means substitute. The reason a surrogate key is like a substitute is because it’s unnatural, in the sense that the column used for the surrogate key has no logical relationship to other columns in the table.

In other words, the surrogate key really has no business meaning – i.e., the data stored in a surrogate key has no intrinsic meaning to it.

#### Why are surrogate keys used?
A surrogate key could be considered to be the “artificial” key that we mentioned earlier. In most databases, surrogate keys are only used to act as a primary key. Surrogate keys are usually just simple sequential numbers – where each number uniquely identifies a row. For example, Sybase and SQL Server both have what’s called an identity column specifically meant to hold a unique sequential number for each row. MySQL allows you to define a column with the AUTO_INCREMENT attribute, which just means that the value in the column will automatically increment the value in a given column to be 1 greater than the value in the previous row. This just means that every time you add a new row, the value in the column that is auto incremented is 1 greater than the value in the most recent row added to the table. You can also set the increment value to be whatever you want it to be.

## Simple key

In a database table, a simple key is just a single attribute (which is just a column) that can uniquely identify a row. So, any single column in a table that can uniquely identify a row is a simple key. The reason it’s called a simple key is because of the fact that it is simple in the sense that it’s just composed of one column (as opposed to multiple columns) and that’s it.


#### Example of a simple key

Let’s go through an example of a simple key. Consider a table called Employees. If every employee has a unique ID and a column called EmployeeID, then the EmployeeID column would be considered a simple key because it’s a single column that can uniquely identify every row in the table (where each row is a separate employee). Simple isn’t it?

## Secondary key

You may have heard the term secondary key in Oracle, MySQL, SQL Server, or whatever other dbms you are dealing with. What exactly is a secondary key? Let’s start with a definition, and then a simple example that will help you understand further.

A given table may have more than just one choice for a primary key. Basically, there may be another column (or combination of columns for a multi-column primary key) that qualify as primary keys. Any combination of column(s) that may qualify to be a primary key are known as candidate keys. This is because they are considered candidates for the primary key. And the options that are not selected to be the primary key are known as secondary keys.

#### Example of a Secondary Key in SQL

Let’s go through an example of a secondary key. Consider a table called Managers that stores all of the managers in a company. Each manager has a unique Manager ID Number, a physical address, and an email address. Let’s say that the Manager ID is chosen to be the primary key of the Managers table. Both the physical address and email address could have been selected as the primary key, because they are both unique fields for every manager row in the Managers table. But, because the email address and physical address were not selected as the primary key, they are considered to be secondary keys.

## superkey 

In SQL, the definition of a superkey is a set of columns in a table for which there are no two rows that will share the same combination of values. So, the superkey is unique for each and every row in the table. A superkey can also be just a single column.


#### Example of a superkey

Suppose we have a table that holds all the managers in a company, and that table is called Managers. The table has columns called ManagerID, Name, Title, and DepartmentID. Every manager has his/her own ManagerID, so that value is always unique in each and every row.

This means that if we combine the ManagerID column value for any given row with any other column value, then we will have a unique set of values. So, for the combinations of (ManagerID, Name), (ManagerID, TItle), (ManagerID, DepartmentID), (ManagerID, Name, DepartmentID), etc – there will be no two rows in the table that share the exact same combination of values, because the ManagerID will always be unique and different for each row. This means that pairing the Manager ID with any other column(s) will ensure that the combination will also be unique across all rows in the table.

And that is exactly what defines a superkey – it’s any combination of column(s) for which that combination of values will be unique across all rows in a table. So, all of those combinations of columns in the Manager table that we gave earlier would be considered to be superkeys. Even the ManagerID column is considered to be a superkey, although a special type of superkey as you can read more about below.

#### What is a minimal superkey?

A minimal superkey is the minimum number of columns that can be used to uniquely identify a single row. In other words, the minimum number of columns, which when combined, will give a unique value for every row in the table. Remember that we mentioned earlier that a superkey can be just a single column. So, in our example above, the minimal superkey would be the ManagerID since it is unique for each and every row in the Manager table.

#### Can a table have multiple minimal superkeys?

Yes, a table can have multiple minimal superkeys. Let use our example of a Manager table again. Suppose we add another column for the Social Security Number (which, for our non-American readers, is a unique 9 digit number assigned to every citizen of the USA) to the Manager table – let’s just call it SSN. Since that column will clearly have a unique value for every row in the table, it will also be a minimal superkey – because it’s only one column and it also is unique for every row.

#### Can a minimal superkey have more than one column?

Absolutely. If there is no single column that is unique for every row in a given table, but there is a combination of columns that produce a unique value for every row in a table, then that combination of columns would be the minimal superkey. This is of course provided that the combination is the smallest number of columns necessary to produce a unique value for each row.

#### Why is it called a superkey?

It’s called a superkey because it comes from RDBMS theory, as in superset and subset. So, a superkey is essentially all the superset combinations of keys, which will of course uniquely identify a row in a table.

#### Superkey versus candidate key

We discussed minimal superkeys and defined exactly what they are. Candidate keys are actually minimal superkeys – so both candidate keys and minimal superkeys mean exactly the same thing.


