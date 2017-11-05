In computing, a __word__ is the natural unit of data used by a particular processor design. A word is a fixed-sized piece of data handled as a unit by the instruction set or the hardware of the processor. The number of bits in a word (the word size, word width, or word length) is an important characteristic of any specific processor design or computer architecture.

The size of a word is reflected in many aspects of a computer's structure and operation; the majority of the registers in a processor are usually word sized and the largest piece of data that can be transferred to and from the working memory in a single operation is a word in many (not all) architectures. The largest possible address size, used to designate a location in memory, is typically a hardware word (here, "hardware word" means the full-sized natural word of the processor, as opposed to any other definition used).

### What is the difference between a word and a byte?

Byte: Today, a byte is almost always 8 bit. However, that wasn't always the case and there's no "standard" or something that dictates this. Since 8 bits is a convenient number to work with it became the de facto standard.

Word: The natural size with which a processor is handling data (the register size). The most common word sizes encountered today are 8, 16, 32 and 64 bits, but other sizes are possible. For examples, there were a few 36 bit machines, or even 12 bit machines.

The byte is the smallest addressable unit for a CPU. If you want to set/clear single bits, you first need to fetch the corresponding byte from memory, mess with the bits and then write the byte back to memory.

The word by contrast is biggest chunk of bits with which a processor can do processing (like addition and subtraction) at a time. That definition is a bit fuzzy, as some processor might have different word sizes for different tasks (integer vs. floating point processing for example). The word size is what the majority of operations work with.
