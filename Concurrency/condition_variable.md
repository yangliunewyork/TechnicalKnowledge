

##### Why does a condition variable need a lock (and therefore also a mutex) ?


down vote
accepted
It's just the way that condition variables are (or were originally) implemented.

The mutex is used to protect the condition variable itself. That's why you need it locked before you do a wait.

The wait will "atomically" unlock the mutex, allowing others access to the condition variable (for signalling). Then when the condition variable is signalled or broadcast to, one or more of the threads on the waiting list will be woken up and the mutex will be magically locked again for that thread.

You typically see the following operation with condition variables, illustrating how they work. The following example is a worker thread which is given work via a signal to a condition variable.

```
thread:
    initialise.
    lock mutex.
    while thread not told to stop working:
        wait on condvar using mutex.
        if work is available to be done:
            do the work.
    unlock mutex.
    clean up.
    exit thread.
```

The work is done within this loop provided that there is some available when the wait returns. When the thread has been flagged to stop doing work (usually by another thread setting the exit condition then kicking the condition variable to wake this thread up), the loop will exit, the mutex will be unlocked and this thread will exit.

The code above is a single-consumer model as the mutex remains locked while the work is being done. For a multi-consumer variation, you can use, as an example:

```
thread:
    initialise.
    lock mutex.
    while thread not told to stop working:
        wait on condvar using mutex.
        if work is available to be done:
            copy work to thread local storage.
            unlock mutex.
            do the work.
            lock mutex.
    unlock mutex.
    clean up.
    exit thread.
```

which allows other consumers to receive work while this one is doing work.

The condition variable relieves you of the burden of polling some condition instead allowing another thread to notify you when something needs to happen. Another thread can tell that thread that work is available as follows:

```
lock mutex.
flag work as available.
signal condition variable.
unlock mutex.
```

The vast majority of what are often erroneously called spurious wakeups was generally always because multiple threads had been signalled within their pthread_cond_wait call (broadcast), one would return with the mutex, do the work, then re-wait.

Then the second signalled thread could come out when there was no work to be done. So you had to have an extra variable indicating that work should be done (this was inherently mutex-protected with the condvar/mutex pair here - other threads needed to lock the mutex before changing it however).

It was technically possible for a thread to return from a condition wait without being kicked by another process (this is a genuine spurious wakeup) but, in all my many years working on pthreads, both in development/service of the code and as a user of them, I never once received one of these. Maybe that was just because HP had a decent implementation :-)

In any case, the same code that handled the erroneous case also handled genuine spurious wakeups as well since the work-available flag would not be set for those.
