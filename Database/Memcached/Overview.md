
Memcached is an open source, high-performance, distributed memory caching system intended to speed up dynamic web applications by reducing the database load. It is a key-value dictionary of strings, objects, etc, stored in the memory, resulting from database calls, API calls, or page rendering.

The key features of Memcached are as follows −

* It is open source.
* Memcached server is a big hash table.
* It significantly reduces the database load.
* It is perfectly efficient for websites with high database load.
* It is distributed under Berkeley Software Distribution (BSD) license.
* It is a client-server application over TCP and/or UDP.

Memcached is not 

* a persistent data store
* a database
* application-specific
* a large object cache
* fault-tolerant or
* highly available

##### Run Memcached

```
$memcached -p 11111 -U 11111 -u user -d
```

It should start the server and listen on TCP port 11111 and UDP port 11111 as a daemon process.

This command is explained below −

* -p is for TCP port number
* -U is for UDP port number
* -u is for user name
* -d runs memcached as daemon process

# Storage Commands

### Set data

Memcached set command is used to set a value to key; if the key does not exist, a new key is created and value is assigned to that key.

```
set key flags exptime bytes [noreply] 
value
```

* key - It is the name of the unique key by which data is accessed.
* flags - It is the 32-bit unsigned integer that the server stores with the data provided by the user, and returns along with the data when the item is retrieved.
* exptime - It is the expiration time (seconds) of data stored in cache. A 0 value means "never expire", i.e. it should not be removed from the cache unless required. If the exptime is more than 30 days then Memcached interprets it as UNIX timestamp for expiration.
* bytes - This is the length of the data in bytes that needs to be stored in Memcached.
* noreply (optional) - This parameter informs the server not to send any reply.
* value - It is the data that needs to be stored. The data needs to be given on the new line after executing the command with the above options.

Example
```
set tutorialspoint 0 900 9
memcached
STORED

get tutorialspoint
VALUE tutorialspoint 0 9
memcached

END
```

### Add Data

Memcached add command is used to set a value to a new key. If the key already exists, then it gives the output NOT_STORED.

```
add key flags exptime bytes [noreply]
value
```

* key - It is the name of the unique key by which data is accessed.
* flags - It is the 32-bit unsigned integer that the server stores with the data provided by the user, and returns along with the data when the item is retrieved.
* exptime - It is the expiration time (seconds) of data stored in cache. A 0 value means "never expire", i.e. it should not be removed from the cache unless required. If the exptime is more than 30 days then Memcached interprets it as UNIX timestamp for expiration.
* bytes - This is the length of the data in bytes that needs to be stored in Memcached.
* noreply (optional) - This parameter informs the server not to send any reply.
* value - It is the data that needs to be stored. The data needs to be given on the new line after executing the command with the above options.

Example
```
add new_key 0 900 10
data_value
STORED
get new_key
VALUE new_key 0 10
data_value
END
```

### Replace Data

Memcached replace command is used to replace the value of an existing key. If the key does not exist, then it gives the output NOT_STORED.

```
replace key flags exptime bytes [noreply]
value
```

Example:

```
add mykey 0 900 10
data_value
STORED
get mykey
VALUE mykey 0 10
data_value
END
replace mykey 0 900 16
some_other_value
get key
VALUE mykey 0 16
some_other_value
END
```

### Append Data

Memcached append command is used to add data in an existing key. This data is added at the end of the previous value.

```
append key flags exptime bytes [noreply]
value
```

Example:

```
set tutorials 0 900 9
memcached
STORED
get tutorials
VALUE tutorials 0 14
memcached
END
append tutorials 0 900 5
redis
STORED
get tutorials
VALUE tutorials 0 14
memcachedredis
END
```

### Prepend Data

```
prepend key flags exptime bytes [noreply]
value
```

Example:
```
set tutorials 0 900 9
memcached
STORED
get tutorials
VALUE tutorials 0 14
memcached
END
prepend tutorials 0 900 5
redis
STORED
get tutorials
VALUE tutorials 0 14
redismemcached
END
```

# CAS Command

CAS stands for Check-And-Set or Compare-And-Swap. Memcached CAS command 'checks' and 'set' data item if and only if, no other client process has updated it since last read by this client.

For example, if in the past, we retrieved the value <key, value> as <total, 3784>. If we now try to set or modify this value using CAS command, then CAS command will first check if it is the same value or is changed by some other client. If it is changed, then we should not change it to avoid any race anomalies in the system. If the value is not modified since our last fetch, CAS now sets the updated value.

Memcached server assigns a unique 64-bit CAS token to all items stored in it. We use gets command to retrieve CAS number of any item.

```
cas key flags exptime bytes unique_cas_token [noreply]
```

##### Example
To execute a CAS command in Memcached, you need to obtain a CAS token from the Memcached gets command. gets command is variation of get command, it is explained in forthcoming chapter.

In this example we should see −

* Incorrect cas statement i.e. unique cas key missing
* casing a non-existing key
* add a key value item
* obtain unique cas key using gets command
* use cas and unique_cas_key to update data item
* use get command and check if data is updated

```
cas tp 0 900 9
ERROR             <− unique cas key missing

cas tp 0 900 9 2
memcached
NOT_FOUND         <− the key tp does not exist

set tp 0 900 9
memcached
STORED

gets tp
VALUE tp 0 9 1
memcached
END

cas tp 0 900 5 1
redis
STORED

get tp
VALUE tp 0 5
redis
END
```

# Retrieval Commands

### Get

Memcached get command is used to get the value stored at key. No value is returned if the key does not exist.

```
get key

get key1 key2 key3
```


### Get CAS Data

Memcached gets command is used to get the value with CAS token. No value is returned if the key does not exist.

```
gets key

gets key1 key2 key3
```

### Delete Key

Memcached delete command is used to delete an existing key from the Memcached server.

```
delete key [noreply]
```

Example

```
set tutorialspoint 0 900 9
memcached
STORED
get tutorialspoint
VALUE tutorialspoint 0 9
memcached
END
delete tutorialspoint
DELETED
get tutorialspoint
END
delete tutorialspoint
NOT_FOUND
```

### Increment Decrement Data
Memcached incr and decr commands are used to increment or decrement the numeric value of an existing key. If the key is not found, then it returns NOT_FOUND. If the key is not numeric, then it returns CLIENT_ERROR cannot increment or decrement non-numeric value. Otherwise, ERROR is returned.


```
incr key increment_value

decr key decrement_value
```


##### Increment Example

```
set visitors 0 900 2
10
STORED
get visitors
VALUE visitors 0 2
10
END
incr visitors 5
15
get visitors
VALUE visitors 0 2
15
END
```

##### Decrement Example

```
set visitors 0 900 2
10
STORED
get visitors
VALUE visitors 0 2
10
END
decr visitors 5
5
get visitors
VALUE visitors 0 1
5
END
```

# Statistics Commands

### Stats
Memcached stats command is used to return server statistics such as PID, version, connections, etc.

```
stats
```

### Stats Items
Memcached stats items command is used to get items statistics such as count, age, eviction, etc. organized by slabs ID.

```
stats items
```

### Stats Slabs

Memcached stats slabs command displays slabs statistics such as size, memory usage, commands, count etc. organized by slabs ID.

```
stats slabs
```

### Stats Sizes

Memcached stats sizes command provides information about the sizes and number of items of each size within the cache. The information is returned in two columns. The first column is the size of the item (rounded up to the nearest 32 byte boundary) and the second column is the count of the number of items of that size within the cache.

```
stats sizes
```

### Clear Data

Memcached flush_all command is used to delete all data (key-value pairs) from the Memcached server. It accepts an optional parameter called time, that sets a time after which the Memcached data is to be cleared.

```
flush_all [time] [noreply]
```



