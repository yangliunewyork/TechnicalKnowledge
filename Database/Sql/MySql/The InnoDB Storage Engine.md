https://dev.mysql.com/doc/refman/5.7/en/innodb-storage-engine.html

InnoDB is a general-purpose storage engine that balances high reliability and high performance. 

### Key Advantages of InnoDB

Key advantages of InnoDB include:

* Its DML operations follow the ACID model, with transactions featuring commit, rollback, and crash-recovery capabilities to protect user data. 

* Row-level locking and Oracle-style consistent reads increase multi-user concurrency and performance. 

* InnoDB tables arrange your data on disk to optimize queries based on primary keys. Each InnoDB table has a primary key index called the clustered index that organizes the data to minimize I/O for primary key lookups. 

* To maintain data integrity, InnoDB supports FOREIGN KEY constraints. With foreign keys, inserts, updates, and deletes are checked to ensure they do not result in inconsistencies across different tables. 

![alt](https://4.bp.blogspot.com/-pl0YgVZLSSA/V6QmidFf-GI/AAAAAAAABCA/WVA8tfy1DRs1N58mSpO9F-lkQshsh23DACLcB/s1600/InnoDB.jpg)


