Let's start by describing some common terminology pertaining to keys and then work through an example.  These terms are:

* __Key.__ A key is one or more data attributes that uniquely identify an entity.  In a physical database a key would be formed of one or more table columns whose value(s) uniquely identifies a row within a relational table. 
* __Composite key.__  A key that is composed of two or more attributes. 
* __Natural key.__  A key that is formed of attributes that already exist in the real world.  For example, U.S. citizens are issued a Social Security Number (SSN)  that is unique to them (this isn't guaranteed to be true, but it's pretty darn close in practice).  SSN could be used as a natural key, assuming privacy laws allow it, for a Person entity (assuming the scope of your organization is limited to the U.S.). 
* __Surrogate key.__  A key with no business meaning.
* __Candidate key.__  An entity type in a logical data model will have zero or more candidate keys, also referred to simply as unique identifiers (note: some people don't believe in identifying candidate keys in LDMs, so there's no hard and fast rules).  For example, if we only interact with American citizens then SSN is one candidate key for the Person entity type and the combination of name and phone number (assuming the combination is unique) is potentially a second candidate key.  Both of these keys are called candidate keys because they are candidates to be chosen as the primary key, an alternate key  or perhaps not even a key at all within a physical data model. 
* __Primary key.__  The preferred key for an entity type.
* __Alternate key.__ Also known as a secondary key, is another unique identifier of a row within a table. 
* __Foreign key.__ One or more attributes in an entity type that represents a key, either primary or secondary, in another entity type.

#### Candidate Key
A candidate key is a combination of attributes that can be uniquely used to identify a database record without any extraneous data. Each table may have one or more candidate keys. In general, one of these candidate keys is selected as the table primary key.
Example - EMPLOYEE_ID, EMPLOYEE_SSN_ID, and EMPLOYEE_DEPT_ID can be considered as candidate keys

#### Primary Key
A primary key is a single column or combination of columns that uniquely defines a record. None of the columns that are part of the primary key can contain a null value. A table can have only one primary key.
Example - EMPLOYEE_ID or EMPLOYEE_SSN_ID can be considered as primary keys

#### Unique Key
A unique key or primary key [is a candidate key] to uniquely identify each row in a table. It be comprised of either a single column or multiple columns.
The major difference is that for unique keys the implicit NOT NULL constraint is not automatically enforced, while for primary keys it is enforced. Thus, the values in unique key columns may or may not be NULL.

##### Differences between Primary Key and Unique Key
Primary Keys -

1. It will not accept null values.       
2. There will be only one primary key in a table.       
3. Clustered index is created in Primary key.       
4. Primary key allows each row in a table to be uniquely identified and ensures that no duplicate rows exist.    

Unique Keys -

1. Null values are accepted.
2. More than one unique key will be there in a table.
3. Non-Clustered index is created in unique key.
4. Unique key constraint is used to prevent the duplication of key values within the rows of a table and allow null values.

#### Alternate Key
A candidate key that is not the primary key is called an alternate key.
Example - If EMPLOYEE_ID is considered as primary keys then EMPLOYEE_SSN_ID is an alternate key.

#### Superkey
A superkey is a combination of attributes that can be uniquely used to identify a database record. A table might have many superkeys. Candidate keys are a special subset of superkeys that do not have any extraneous information in them.
A primary key is therefore a minimum superkey.
Examples - Any combination of the following can be considered as a Super key

- EMPLOYEE_ID - Minimal Super Key
- EMPLOYEE_ID and EMPLOYEE_SSN_ID
- EMPLOYEE_ID, EMPLOYEE_SSN_ID and EMPLOYEE_DEPT_ID
- EMPLOYEE_ID, EMPLOYEE_SSN_ID, EMPLOYEE_DEPT_ID, EMPLOYEE_FIRST_NAME
- EMPLOYEE_SSN_ID, EMPLOYEE_FIRST_NAME, EMPLOYEE_LAST_NAME

#### Foreign Key
The foreign key identifies a column or a set of columns in one (referencing) table that refers to a column or set of columns in another (referenced) table.

#### Composite Key
A primary key that made up of more than one attribute is known as a composite key.
Example - [ EMPLOYEE_ID and EMPLOYEE_SSN_ID ] can together be treated as (one of) composite keys. Another combination can be [ EMPLOYEE_ID, EMPLOYEE_SSN_ID and EMPLOYEE_DEPT_ID ]

#### Surrogate Key
Surrogate keys are keys that have no business meaning and are solely used to identify a record in the table.
Such keys are either database generated (example: Identity in SQL Server, Sequence in Oracle, Sequence/Identity in DB2 UDB etc.) or system generated values (like generated via a table in the schema).
