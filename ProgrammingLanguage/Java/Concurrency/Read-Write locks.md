A ```java.util.concurrent.locks.ReadWriteLock``` is an advanced thread lock mechanism. It allows multiple threads to read a certain resource, but only one to write it, at a time.

The idea is, that multiple threads can read from a shared resource without causing concurrency errors. The concurrency errors first occur when reads and writes to a shared resource occur concurrently, or if multiple writes take place concurrently.

### ReadWriteLock Locking Rules

The rules by which a thread is allowed to lock the ReadWriteLock either for reading or writing the guarded resource, are as follows:

* Read Lock : If no threads have locked the ```ReadWriteLock``` for writing,  and no thread have requested a write lock (but not yet obtained it). Thus, multiple threads can lock the lock for reading.
* Write Lock : If no threads are reading or writing. Thus, only one thread at a time can lock the lock for writing.


#### Example

```java
ReadWriteLock readWriteLock = new ReentrantReadWriteLock();

readWriteLock.readLock().lock();

    // multiple readers can enter this section
    // if not locked for writing, and not writers waiting
    // to lock for writing.

readWriteLock.readLock().unlock();


readWriteLock.writeLock().lock();

    // only one writer can enter this section,
    // and only if no threads are currently reading.

readWriteLock.writeLock().unlock();
```
