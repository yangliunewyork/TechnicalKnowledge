## What is consistency model ?
In computer science, Consistency models are used in distributed systems like distributed shared memory systems or distributed data stores (such as a filesystems, databases, optimistic replication systems or Web caching). The system is said to support a given model if operations on memory follow specific rules. The data consistency model specifies a contract between programmer and system, wherein the system guarantees that if the programmer follows the rules, memory will be consistent and the results of memory operations will be predictable.

## Types
There are two methods to define and categorize consistency models; issue and view.

* Issue: Issue method describes the restrictions that define how a process can issue operations.
* View: View method which defines the order of operations visible to processes.

For example, a consistency model can define that a process is not allowed to issue an operation until all previously issued operations are completed. Different consistency models enforce different conditions. One consistency model can be considered stronger than another if it requires all conditions of that model and more. In other words, a model with fewer constraints is considered a weaker consistency model.

These models define how the hardware needs to be laid out and at high-level, how the programmer must code. The chosen model also affects how the compiler can re-order instructions. Generally, if control dependencies between instructions and if writes to same location are ordered, then the compiler can reorder as required. However, with the models described below, some may allow Writes before Loads to be reordered while some may not.

## Strict Consistency
Strict consistency is the strongest consistency model. Under this model, a write to a variable by any processor needs to be seen instantaneously by all processors. The Strict model diagram and non-Strict model diagrams describe the time constraint – instantaneous. It can be better understood as though a global clock is present in which every write should be reflected in all processor caches by the end of that clock period. The next operation must happen only in the next clock period.

This is the most rigid model and is impossible to implement without forgoing performance. In this model, the programmer’s expected result will be received every time. It is deterministic. __A distributed system with many nodes will take some time to copy information written to one node to all the other nodes responsible for replicating that information. That time can't be zero because it takes time for information to propagate through space, and there is a limit to how fast information can travel through space: the speed of light. Therefore, strict consistency is impossible.__ The best one can do is design a system where the time-to-replicate approaches the theoretical minimum.

## Sequential Consistency
The sequential consistency model is a weaker memory model than strict consistency. A write to a variable does not have to be seen instantaneously, however, writes to variables by different processors have to be seen in the same order by all processors. As defined by Lamport(1979), Sequential Consistency is met if “the result of any execution is the same as if the operations of all the processors were executed in some sequential order, and the operations of each individual processor appear in this sequence in the order specified by its program.”

Program order within each processor and sequential ordering of operations between processors should be maintained. In order to preserve sequential order of execution between processors, all operations must appear to execute instantaneously or atomically with respect to every other processor. These operations need only “appear” to be completed because it is physically impossible to send information instantaneously. For instance, once a bus line is posted with information, It is guaranteed that all processors will see the information at the same instant. Thus, passing the information to the bus line completes the execution with respect to all processors and has appeared to have been executed. Cache-less architectures or cached architectures with interconnect networks that are not instantaneous can contain a slow path between processors and memories. These slow paths can result in sequential inconsistency, because some memories receive the broadcast data faster than others.

Sequential consistency can produce non-deterministic results. This is because the sequence of sequential operations between processors can be different during different runs of the program. All memory operations need to happen in the program order.
Linearizability (also known as atomic consistency) can be defined as sequential consistency with the real-time constraint.


## Client-centric Consistency Models

In distributed systems, maintaining sequential consistency in order to control the concurrent operations is essential. In some special data stores without simultaneous updates, client-centric consistency models can deal with inconsistencies in a less costly way. The following models are some client-centric consistency models:
* Eventual Consistency : An eventual consistency is a weak consistency model in the system with the lack of simultaneous updates. It defines that if no update takes a very long time, all replicas eventually become consistent.
* Monotonic Read Consistency :  "If a process reads the value of a data item x, any successive read operation on x by that process will always return that same value or a more recent value." Monotonic read consistency guarantees that after a process reads a value of data item x at time t, it will never see the older value of that data item.
* Monotonic Write Consistency : "A write operation by a process on a data item X is completed before any successive write operation on X by the same process."


