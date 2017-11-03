In computer science, the __test-and-set__ instruction is an instruction used to write 1 (set) to a memory location and return its old value as a single atomic (i.e., non-interruptible) operation. If multiple processes may access the same memory location, and if a process is currently performing a test-and-set, no other process may begin another test-and-set until the first process's test-and-set is finished. A CPU may use a test-and-set instruction offered by another electronic component, such as dual-port RAM; a CPU itself may also offer a test-and-set instruction.

A lock can be built using an atomic test-and-set instruction as follows:

```
function Lock(boolean *lock) { 
    while (test_and_set(lock) == 1); 
}
```

The calling process obtains the lock if the old value was 0 otherwise while-loop spins waiting to acquire the lock. This is called a spinlock. "Test and Test-and-set" is another example.

# Performance evaluation of test-and-set locks

