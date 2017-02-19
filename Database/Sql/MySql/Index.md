##  Indexing Basics

###  Index Concepts
To understand what indexes allow MySQL to do, it's best to think about how MySQL works to answer a query. Imagine that phone_book is a table containing an aggregate phone book for the state of California, with roughly 35 million entries. And keep in mind that records within tables aren't inherently sorted. Consider a query like this one:

```
SELECT * FROM phone_book WHERE last_name = 'Zawodny'
```

Without any sort of index to consult, MySQL must read all the records in the phone_book table and compare the last_name field with the string "Zawodny" to see whether they match. Clearly that's not efficient. As the number of records increases, so does the effort necessary to find a given record. In computer science, we call that an O(n) problem.

Just as the book author or publisher may choose to create an index of the important concepts and terms in the book, you can choose to create an index on a particular column of a database table. Using the previous example, you might create an index on the last name to make looking up phone numbers faster:
```
ALTER TABLE phone_book ADD INDEX (last_name)
```
In doing so, you're asking MySQL to create an ordered list of all the last names in the phone_book table. Along with each name, it notes the positions of the matching records—just as the index at the back of this book lists page numbers for each entry.

> That's a bit of a lie. MySQL doesn't always store the position of the matching records.

From the database server's point of view, indexes exist so that the database can quickly eliminate possible rows from the result set when executing a query. Without any indexes, MySQL (like any database server) must examine every row in a table. Not only is that time consuming, it uses a lot of disk I/O and can effectively pollute the disk cache.

In the real world, it's rare to find dynamic data that just happens to be sorted (and stays sorted). Books are a special case; they tend to remain static.

Because MySQL needs to maintain a separate list of indexes' values and keep them updated as your data changes, you really don't want to index every column in a table. Indexes are a trade-off between space and time. You're sacrificing some extra disk space and a bit of CPU overhead on each INSERT, UPDATE, and DELETE query to make most (if not all) your queries much faster.

#### Partial indexes
Indexes trade space for performance. But sometimes you'd rather not trade too much space for the performance you're after. Luckily, MySQL gives you a lot of control over how much space is used by the indexes. Maybe you have a phone_book table with 2 billion rows in it. Adding an index on last_name will require a lot of space. If the average last_name is 8 bytes long, you're looking at roughly 16 GB of space for the data portion of the index; the row pointers are there no matter what you do, and they add another 4-8 bytes per record.

> That's a bit of an oversimplification, too. MySQL has some strategies for reducing the size of the index, but they also come at a price.

Instead of indexing the entire last name, you might index only the first 4 bytes:
```
ALTER TABLE phone_book ADD INDEX (last_name(4))
```
In doing so, you've reduced the space requirements for the data portion of the index by roughly half. The trade-off is that MySQL can't eliminate quite as many rows using this index. A query such as:
```
SELECT * FROM phone_book WHERE last_name = 'Smith'
```
retrieves all fields beginning with Smit, including all people with name Smith, Smitty, and so on. The query must then discard Smitty and all other irrelevant rows.

#### Multicolumn indexes
Like many relational database engines, MySQL allows you to create indexes that are composed of multiple columns:
```
ALTER TABLE phone_book ADD INDEX (last_name, first_name)
```
Such indexes can improve the query speed if you often query all columns together in the WHERE clause or if a single column doesn't have sufficient variety. Of course, you can use partial indexes to reduce the space required:
```
ALTER TABLE phone_book ADD INDEX (last_name(4), first_name(4))
```
In either case, a query to find Josh Woodward executes quickly:
```
SELECT * FROM phone_book
WHERE last_name = 'Woodward'
AND first_name = 'Josh'
```
Having the last name and first name indexed together means that MySQL can eliminate rows based on both fields, thereby greatly reducing the number of rows it must consider. After all, there are a lot more people in the phone book whose last name starts with "Wood" than there are folks whose last name starts with "Wood" and whose first name also starts with "Josh."

When discussing multicolumn indexes, you may see the individual indexed columns referred to as key parts or "parts of the key." __Multicolumn indexes__ are also referred to as __composite indexes__ or __compound indexes__.

So why not just create two indexes, one on last_name and one on first_name? You could do that, but MySQL won't use them both at the same time. __In fact, MySQL will only ever use one index per table per query—except for UNIONs. This fact is important enough to say again: MySQL will only ever use one index per table per query.__

> In a UNION, each logical query is run separately, and the results are merged.

With separate indexes on first_name and last_name, MySQL will choose one or the other. It does so by making an educated guess about which index allows it to match fewer rows. We call it an educated guess because MySQL keeps track of some index statistics that allow it to infer what the data looks like. The statistics, of course, are generalizations. While they often let MySQL make smart decisions, if you have very clumpy data, MySQL may make suboptimal choices about index use. We call data clumpy if the key being indexed is sparse in some areas (such as names beginning with X) and highly concentrated in others (such as the name Smith in English-speaking countries). 

#### Index order

How does MySQL order values in the index? If you've used another RDBMS, you might expect MySQL to have syntax for specifying that an index be sorted in ascending, descending, or some other order. MySQL gives you no control over its internal sorting of index values. It has little reason to. It does a good job of optimizing cases that cause slower performance for other database systems.

For example, some database products may execute this query quickly:
```
SELECT * FROM phone_book WHERE last_name = 'Zawodny'
ORDER BY first_name DESC
```

And this query slowly:

```
SELECT * FROM phone_book WHERE last_name = 'Zawodny'
ORDER BY first_name ASC
```

Why? Because some databases store the indexes in descending order and are optimized for reading them in that order. In the first case, the database uses the multicolumn index to locate all the matching records. Since the records are already stored in descending order, there's no need to sort them. But in the second case, the server finds all matching records and then performs a second pass over those rows to sort them.

MySQL is smart enough to "traverse the index backwards" when necessary. It will execute both queries very quickly. In neither case does it need to sort the records.

#### Indexes as constraints

Indexes aren't always used to locate matching rows for a query. A unique index specifies that a particular value may only appear once in a given column. In the phone book example, you might create a unique index on phone_number to ensure that each phone number appears only once:

> Except for NULL, of course. NULL is always a special case.

> In the real world, however, this would be a very bad practice, as anyone who has shared a phone with several housemates can tell you.

```
ALTER TABLE phone_book ADD UNIQUE (phone_number)
```

The unique index serves a dual purpose. It functions just like any other index when you perform a query based on a phone number:

```
SELECT * FROM phone_book WHERE phone_number = '555-7271'
```

However, it also checks every value when attempting to insert or update a record to ensure that the value doesn't already exist. In this way, the unique index acts as a constraint.

Unique indexes use as much space as nonunique indexes do. The value of every column as well as the record's location is stored. This can be a waste if you use the unique index as a constraint and never as an index. Put another way, you may rely on the unique index to enforce uniqueness but never write a query that uses the unique value. In this case, there's no need for MySQL to store the locations of every record in the index: you'll never use them.

Unfortunately, there's no way to signal your intentions to MySQL. 

#### Clustered and secondary indexes

With MyISAM tables, the indexes are kept in a completely separate file that contains a list of primary (and possibly secondary) keys and a value that represents the byte offset for the record. These ensure MySQL can find and then quickly skip to that point within the database to locate the record. MySQL has to store the indexes this way because the records are stored in essentially random order.

With clustered indexes, the primary key and the record itself are "clustered" together, and the records are all stored in primary-key order. InnoDB uses clustered indexes. In the Oracle world, clustered indexes are known as "index-organized tables," which may help you remember the relationship between the primary key and row ordering.

When your data is almost always searched on via its primary key, clustered indexes can make lookups incredibly fast. With a standard MyISAM index, there are two lookups, one to the index, and a second to the table itself via the location specified in the index. With clustered indexes, there's a single lookup that points directly to the record in question.

Some operations render clustered indexes less effective. For instance, consider when a secondary index is in use. Going back to our phone book example, suppose you have last_name set as the primary index and phone_number set as a secondary index, and you perform the following query:
```
SELECT * FROM phone_book WHERE phone_number = '555-7271'
```
MySQL scans the phone_number index to find the entry for 555-7271, which contains the primary key entry Zawodny because phone_book's primary index is the last name. MySQL then skips to the relevant entry in the database itself.

In other words, lookups based on your primary key happen exceedingly fast, and lookups based on secondary indexes happen at essentially the same speed as MyISAM index lookups would.

But under the right (or rather, the wrong) circumstances, the clustered index can actually degrade performance. When you use one together with a secondary index, you have to consider the combined impact on storage. Secondary indexes point to the primary key rather than the row. Therefore, if you index on a very large value and have several secondary indexes, you will end up with many duplicate copies of that primary index, first as the clustered index stored alongside the records themselves, but then again for as many times as you have secondary indexes pointing to those clustered indexes. With a small value as the primary key, this may not be so bad, but if you are using something potentially long, such as a URL, this repeated storage of the primary key on disk may cause storage issues.

Another less common but equally problematic condition happens when the data is altered such that the primary key is changed on a record. This is the most costly function of clustered indexes. A number of things can happen to make this operation a more severe performance hit:

* Alter the record in question according to the query that was issued.
* Determine the new primary key for that record, based on the altered data record.
* Relocate the stored records so that the record in question is moved to the proper location in the tablespace.
* Update any secondary indexes that point to that primary key.

As you might imagine, if you're altering the primary key for a number of records, that UPDATE command might take quite some time to do its job, especially on larger tables. __Choose your primary keys wisely. Use values that are unlikely to change, such as a Social Security account number instead of a last name, serial number instead of a product name, and so on.__

#### Unique indexes versus primary keys

If you're coming from other relational databases, you might wonder what the difference between a primary key and a unique index is in MySQL. As usual, it depends. __In MyISAM tables, there's almost no difference. The only thing special about a primary key is that it can't contain NULL values. The primary key is simply a NOT NULL UNIQUE INDEX named PRIMARY. MyISAM tables don't require that you declare a primary key.__

__InnoDB and BDB tables require primary keys for every table. There's no requirement that you specify one, however. If you don't, the storage engine automatically adds a hidden primary key for you. In both cases, the primary keys are simply incrementing numeric values, similar to an AUTO-INCREMENT column. If you decide to add your own primary key at a later time, simply use ALTER TABLE to add one. Both storage engines will discard their internally generated keys in favor of yours.__ Heap tables don't require a primary key but will create one for you. In fact, you can create Heap tables with no indexes at all.

#### Indexing NULLs

It is often difficult to remember that SQL uses tristate logic when performing logical operations. Unless a column is declared NOT NULL, there are three possible outcomes in a logical comparison. The comparison may be true because the values are equivalent; it may be false because the values aren't equivalent; or it may not match because one of the values is NULL. Whenever one of the values is NULL, the outcome is also NULL.

Programmers often think of NULL as undefined or unknown. It's a way of telling the database server "an unknown value goes here." So how do NULL values affect indexes?

__NULL values may be used in normal (nonunique) indexes. This is true of all database servers. However, unlike many database servers, MySQL allows you to use NULL values in unique indexes. You can store as many NULL values as you'd like in such an index. This may seem a bit counterintuitive, but that's the nature of NULL. Because NULL represents an undefined value, MySQL needs to assert that all NULL values are the same if it allowed only a single value in a unique index.__


To make things just a bit more interesting, a NULL value may appear only once as a primary key. Why? The SQL standard dictates this behavior. It is one of the few ways in which primary keys are different from unique indexes in MySQL. And, in case you're wondering, allowing NULL values in the index really doesn't impact performance.
