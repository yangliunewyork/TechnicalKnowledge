
```
Reentrancy means that locks are acquired on a per-thread rather than per-invocation basis.
```

That is a misleading definition. It is true (sort of), but it misses the real point.

Reentrancy means (in general CS / IT terminology) that you do something, and while you are still doing it, you do it again. In the case of locks it means you do something like this on a single thread:

```
Acquire a lock on "foo".
Do something
Acquire a lock on "foo". Note that we haven't released the lock that we previously acquired.
...
Release lock on "foo"
...
Release lock on "foo"
```

With a reentrant lock / locking mechanism, the attempt to acquire the same lock will succeed, and will increment an internal counter belonging to the lock. The lock will only be released when the current holder of the lock has released it twice.

Here's a example in Java using primitive object locks / monitors ... which are reentrant:

```
Object lock = new Object();
...
synchronized (lock) {
    ...
    doSomething(lock, ...)
    ...
}

public void doSomething(Object lock, ...) {
    synchronized (lock) {
        ...
    }
}
```

The alternative to reentrant is non-reentrant locking, where it would be an error for a thread to attempt to acquire a lock that it already holds.

The advantage of using reentrant locks is that you don't have to worry about the possibility of failing due to accidentally acquiring a lock that you already hold. The downside is that you can't assume that nothing you call will change the state of the variables that the lock is designed to protect. However, that's not usually a problem. Locks are generally used to protect against concurrent state changes made by other threads.
