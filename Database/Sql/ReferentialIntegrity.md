## What is referential integrity?

Referential integrity is a property of data which, when satisfied, requires every value of one attribute (column) of a relation (table) to exist as a value of another attribute (column) in a different (or the same) relation (table).

For referential integrity to hold in a relational database, any column in a base table that is declared a foreign key can contain either a null value, or only values from a parent table's primary key or a candidate key. __In other words, when a foreign key value is used it must reference a valid, existing primary key in the parent table.__ For instance, deleting a record that contains a value referred to by a foreign key in another table would break referential integrity. Some relational database management systems (RDBMS) can enforce referential integrity, normally either by deleting the foreign key rows as well to maintain integrity, or by returning an error and not performing the delete. Which method is used may be determined by a referential integrity constraint defined in a data dictionary.

__The adjective 'referential' describes the action that a foreign key performs, 'referring' to a link column in another table. In simple terms, 'referential integrity' is a guarantee that the target it 'refers' to will be found. A lack of referential integrity in a database can lead relational databases to return incomplete data, usually with no indication of an error.__

> Entity integrity referred as primary key. Referential integrity referred as foreign key.




