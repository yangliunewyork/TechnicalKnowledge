## What is Processor Register ?

In computer architecture, a processor register is a quickly accessible location available to a digital processor's central processing unit (CPU). Registers usually consist of a small amount of fast storage, although some registers have specific hardware functions, and may be read-only or write-only. Registers are typically addressed by mechanisms other than main memory, but may in some cases be memory mapped.

Almost all computers, whether load/store architecture or not, load data from a larger memory into registers where it is used for arithmetic operations and is manipulated or tested by machine instructions. Manipulated data is then often stored back to main memory, either by the same instruction or by a subsequent one. Modern processors use either static or dynamic RAM as main memory, with the latter usually accessed via one or more cache levels.

Processor registers are normally at the top of the memory hierarchy, and provide the fastest way to access data. The term normally refers only to the group of registers that are directly encoded as part of an instruction, as defined by the instruction set. However, modern high-performance CPUs often have duplicates of these "architectural registers" in order to improve performance via register renaming, allowing parallel and speculative execution.

A common property of computer programs is locality of reference, which refers to accessing the same values repeatedly and holding frequently used values in registers to improve performance; this makes fast registers and caches meaningful. Allocating frequently used variables to registers can be critical to a program's performance; this register allocation is performed either by a compiler in the code generation phase, or manually by an assembly language programmer.

