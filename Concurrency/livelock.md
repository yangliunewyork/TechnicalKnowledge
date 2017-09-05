
### livelock vs deadlock vs starvation

Deadlock: A situation in which two or more processes are unable to proceed because each is waiting for one the others to do something.

For example, consider two processes, P1 and P2, and two resources, R1 and R2. Suppose that each process needs access to both resources to perform part of its function. Then it is possible to have the following situation: the OS assigns R1 to P2, and R2 to P1. Each process is waiting for one of the two resources. Neither will release the resource that it already owns until it has acquired the other resource and performed the function requiring both resources. The two processes are deadlocked.

Livelock: A situation in which two or more processes continuously change their states in response to changes in the other process(es) without doing any useful work. It is somewhat similar to the deadlock but the difference is processes are getting polite and let other to do the work. This can be happen when a process trying to avoid a deadlock.

Starvation: A situation in which a runnable process is overlooked indefinitely by the scheduler; although it is able to proceed, it is never chosen. this can be happen since greedy threads which would never give a chance to other threads to proceed.

Deadlock: "Me first, Me first"
Livelock: " You first, You first"
Starvation: "Some first, Others never"

