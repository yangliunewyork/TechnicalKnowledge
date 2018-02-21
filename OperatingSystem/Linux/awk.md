### grep, sed, awk

How many times have we used grep to narrow our searches on a Linux FS (File System)? Well, this is a good question since almost everyone (intended as Linux average User) knows grep and its basic features set. To recap: g/re/p stands for globally search a regular expression and print, a name, a manifesto I would say.

The Linux’s ecosystem has two other very useful and powerful tools for patterns search: sed that stands for stream editor, and awk that instead is named by the names of its creators, Aho, Weinberger and Kerningham.

Given the three, what is the main difference? Which is the best usage for each one of the three? Straight to the point, very good questions that hereafter are answered.

* grep. A fast and powerful pattern search tool that can be easily combined with other filters to find results and customize the display, even if the main aim is to search for matches. Its main usage consists in narrowing search results by forcing the match with the given pattern.
* sed. A fast stream editor, able to search for a pattern and apply the given transformations and/or commands; still easy to combine in sophisticated filters, but serving a different aim: modifying the text in the stream. Its main usage consists in editing in-memory a stream according to the given pattern.
* awk. A loosely typed programming language for stream processing, where the basic unit is the String (intended as an array of characters) that can be i. matched, ii. substituted and iii. worked around; most of the times, it is no really needed to combine awk with other filters, since its reporting capabilities are very powerful (the printf built-in function allows to format the output text as in C). Its main usage consists in perform fine-grained (variables can be defined and modified incrementally) and programmatic manipulations (flow control statements) to the input stream.

