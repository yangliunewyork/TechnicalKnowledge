### Thread Design Patterns
* Boss/workers model
- boss gets assignments, dispatches tasks to workers
- many variants (thread pool, single thread per connection, etc.)
* Pipeline model
- do some work, pass the partial result to the next thread
* Up-calls
- fast (or even synchronous) control flow transfer for layered systems
* Version stamps
- a common technique for keeping shared information consistent

