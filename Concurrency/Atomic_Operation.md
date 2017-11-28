In simple terms, atomicity is unbreakability, i.e. an uninterrupted operation. If two users issue a print command, each print should go in single attempt. If the printer driver is sending parts of data from two users, the printout will not be as expected. Hence, the printer driver must send the print command as unbreakable operation from one application at a time (in other words synchronize the access to printer).

With an example we can understand the atomicity in programming well. Consider in a multi-threaded application, a function is incrementing a global/static variable,

```
count++; // count has permanent storage in RAM
```

The above statement can be decomposed into, atleast three operations.

```
1. Fetching count value
2. Incrementing count value
3. Storing the updated value
```

If a thread executing the function containing the above statement is fetching its value (say 2). It is possible that at this point of execution, the thread can be preempted and another thread may invoke the same function. Consequently, the value of count will be incremented to 3 by that thread. When the former thread is resumed, it still retains the previous value (2), instead of latest value (3), and ends up in writing back 3 again. Infact, the value of count should be 4 due to affect of both the threads.

Such kind of bugs are quite difficult to recreate and locate.

An example of atomic operation is instruction execution, usually an instruction feed to the execution unit can’t be stopped in the middle. Yet, a statement in high level language results in multiple instructions. It is the root cause of non-atomic operations.
