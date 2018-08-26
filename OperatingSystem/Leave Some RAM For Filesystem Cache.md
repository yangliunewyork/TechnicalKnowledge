Many system administrators don’t realize it, but in most OSes RAM that’s unused by applications goes towards filesystem cache, which speeds disk operations. Some VM “right-sizing” tools don’t take this into account, and recommend pretty tight memory allocations which end up causing more disk I/O in the long term. Trading some RAM for better I/O performance is often a very good move, both for an individual VM and for the virtual environment as a whole.

To understand what’s happening on a Linux VM and make a decision about how much RAM we should leave for filesystem cache we need to understand the ‘free’ command:

```
             total       used       free     shared    buffers     cached
Mem:       2058824    1772172     286652          0     214708     879744
-/+ buffers/cache:     677720    1381104
Swap:      1048568         84    1048484
```

In this case the VM in question has 2 gigabytes of memory assigned to it, which you can see in the “total” column. Looking at the “used” column it also looks like it’s close to running out of memory. That’s because RAM being used as filesystem cache counts in the “used” totals. Tricky? Yes. Don’t ever believe an OS when it tells you all the RAM is in use (if you’re in doubt see if it’s swapping, because that’s a real telltale sign that you actually are out of memory).

Also look at the line labeled “-/+ buffers/cache.” The number in the “used” column (677,720) indicates how much RAM is actually in use, minus the buffers & cache, and the “free” column (1,381,104) shows us how much free RAM we would have if all the buffers and cache were empty (which they never will be, BTW). So really, this VM’s OS and apps are consuming just over 661 MB of RAM.

So is that the right amount of cache for this application? Does it need more, or are we wasting resources by having it this large? Like most questions in IT, the answer is “it depends.” And it’s more of an art than a science at times.

The rule with caching is simple: you want the cache closest to the work being performed. The farther down the stack you go the less the cache knows about what it’s caching, which means it’s less effective (and you need more cache to achieve the same results — think about the huge, expensive caches on disk arrays).

So if your application has the ability to cache you probably want to let the application have the RAM, instead of the filesystem cache. You don’t want to give it 100% of the unused RAM, because some filesystem cache is good (remember you still have logging and other things going on), and remember that you still need free RAM for buffers. But if it’s a choice between giving your database 10 GB of RAM for its cache or giving the filesystem cache 10 extra gigabytes of RAM, I’d choose the database.

If your app doesn’t cache I/O then it might be better to give the OS resources to do it. In my example here the VM is running a standard LAMP stack, with a mostly-untuned (aka “stock”) web server and a database, but they’re very low-usage. We can see from the ‘free’ output that the OS is really only caching 879,744 KB of data. If we add the amount of cached data (879,744) to the amount of RAM actually in use by processes (677,720) we get 1,557,464, which is about a 0.5 GB difference between the total memory and what’s being used. I’m comfortable with that. Given what I know about the usage patterns and the performance of the app I think that’s enough headroom to support a small spike in usage, and I don’t think it’s a waste of RAM. Besides, VMware can & will reclaim some of that anyhow, through transparent page sharing, etc., depending on how your limits & reservations are set.

Another application I support in a VM is a performance monitoring app that is constantly doing heavy filesystem I/O, and for a while it wasn’t keeping up. My solution? I tripled the amount of RAM allocated to the VM. The application didn’t need it, but the additional filesystem cache did wonders for the I/O performance, which also reduced the load on the disk array (and in turn caused performance to increase for the other VMs on the array).
