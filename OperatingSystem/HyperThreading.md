Firstly, hyperthreading is an Intel (company) marketing term and was not an idea that was spawned at Intel. It's actually quite a few years old and is called simultaneous multithreading (SMT) in Computer Architecture (the field that studies the design of computers) literature. 

A modern CPU is composed of several different hardware components. The ones that we care about for this discussion are called Functional Units. These pieces of hardware are responsible for the performing the actual computations on data. Functional units do different kinds of work, but for simplicity, let's assume that a CPU has 4 and that each functional unit can do the same types of computation that the others can.

Even with this being true, it may be that at some period of time that one program can only make use of 2 or 3 functional units at a given time. This means that there is hardware in the CPU that is currently doing nothing. The original goal of SMT was to make it such that functional units were doing as much work as possible. Intel CPUs execute two programs at the same time and those programs combined will use more functional units than a single program can. This directly equates to programs running faster.

Most modren CPUs are multi-core. This actually means that when you buy a chip for your desktop (or laptop) it actually contains more than one CPU (Apple Macbook air has dual core CPUs, Apple macbook  Pro has quad core CPUs). You can also buy chips which contain 6 or more cores. For purposes of answering this question, we are only going to focus on one of the CPUs inside the package that you bought (since that is the level at which hyperthreading or simultaneous multi threading really applies).

A modern CPU has several different functional units and  no one program can use all of them at once. For example, a CPU may have 4 ALUs which can do addition. It will be very rare (except in graphics) to find programs that need to do 4 additions all the time. So the solution would be to run 2 separate programs at the same time in the hope that all the ALUs are kept busy. Same goes for any other functional unit. Now, to keep track of which functional unit is running which program requires some extra book keeping which needs more chip area and it also slows down both the running programs just a little bit. This means that both the running programs run a little bit slower but in parallel (so if you had to run both the programs, you still save time in the end).

Another way to look at hyperthreading is by thinking of a burger line at In and Out. The burger line has:
       - One person toasting the buns
       - One person adding lettuce/tomatoes/onions to the buns
       - One person grilling the patty
        - One person packaging up the final product
   
In a non __SMT(Simultaneous multithreading)__ model, each person will do their job and burgers are produced at some known rate. Now imagine that the person toasting the buns has some free time because it does not require a lot of manual intervention and they are able to also add lettuce/tomato/onions to the buns if they are not busy and the person grilling the patty is also able package the final product while they are not busy. This is akin to SMT since the same person is actually doing two different tasks during the same period of time. It is easy to see why this second method would produce more burgers in the same amount of time.... or how SMT can run two programs in less time than it would take to run the programs one after the other. 

# Overview

The central processing unit (CPU) in your computer does the computational work—running programs, basically. But modern CPUs offer features like multiple cores and hyper-threading. Some PCs even use multiple CPUs. We’re here to help sort it all out.

The clock speed for a CPU used to be enough when comparing performance. Things aren’t so simple anymore. A CPU that offers multiple cores or hyper-threading may perform significantly better than a single-core CPU of the same speed that doesn’t feature hyper-threading. And PCs with multiple CPUs can have an even bigger advantage. All of these features are designed to allow PCs to more easily run multiple processes at the same time—increasing your performance when multitasking or under the demands of powerful apps like video encoders and modern games. So, let’s take a look at each of these features and what they might mean to you.

##### Hyper-Threading

Hyper-threading was Intel’s first attempt to bring parallel computation to consumer PCs. It debuted on desktop CPUs with the Pentium 4 HT back in 2002. The Pentium 4’s of the day featured just a single CPU core, so it could really only perform one task at a time—even if it was able to switch between tasks quickly enough that it seemed like multitasking. Hyper-threading attempted to make up for that.

A single physical CPU core with hyper-threading appears as two logical CPUs to an operating system. The CPU is still a single CPU, so it’s a little bit of a cheat. While the operating system sees two CPUs for each core, the actual CPU hardware only has a single set of execution resources for each core. The CPU pretends it has more cores than it does, and it uses its own logic to speed up program execution. In other words, the operating system is tricked into seeing two CPUs for each actual CPU core.

Hyper-threading allows the two logical CPU cores to share physical execution resources. This can speed things up somewhat—if one virtual CPU is stalled and waiting, the other virtual CPU can borrow its execution resources. _Hyper-threading can help speed your system up, but it’s nowhere near as good as having actual additional cores._

Thankfully, hyper-threading is now a “bonus.” While the original consumer processors with hyper-threading only had a single core that masqueraded as multiple cores, modern Intel CPUs now have both multiple cores and hyper-threading technology. Your dual-core CPU with hyper-threading appears as four cores to your operating system, while your quad-core CPU with hyper-threading appears as eight cores. _Hyper-threading is no substitute for additional cores, but a dual-core CPU with hyper-threading should perform better than a dual-core CPU without hyper-threading._

##### Multiple Cores

Originally, CPUs had a single core. That meant the physical CPU had a single central processing unit on it. To increase performance, manufacturers add additional “cores,” or central processing units. A dual-core CPU has two central processing units, so it appears to the operating system as two CPUs. A CPU with two cores, for example, could run two different processes at the same time. This speeds up your system, because your computer can do multiple things at once.

Unlike hyper-threading, there are no tricks here — a dual-core CPU literally has two central processing units on the CPU chip. A quad-core CPU has four central processing units, an octa-core CPU has eight central processing units, and so on.

This helps dramatically improve performance while keeping the physical CPU unit small so it fits in a single socket. There only needs to be a single CPU socket with a single CPU unit inserted into it—not four different CPU sockets with four different CPUs, each needing their own power, cooling, and other hardware. There’s less latency because the cores can communicate more quickly, as they’re all on the same chip.

##### Multiple CPUs

Most computers only have a single CPU. That single CPU may have multiple cores or hyper-threading technology—but it’s still only one physical CPU unit inserted into a single CPU socket on the motherboard.

Before hyper-threading and multi-core CPUs came around, people attempted to add additional processing power to computers by adding additional CPUs. This requires a motherboard with multiple CPU sockets. The motherboard also needs additional hardware to connect those CPU sockets to the RAM and other resources. There’s a lot of overhead in this kind of setup. There’s additional latency if the CPUs need to communicate with each other, systems with multiple CPUs consume more power, and the motherboard needs more sockets and hardware.

Systems with multiple CPUs aren’t very common among home-user PCs today. Even a high-powered gaming desktop with multiple graphics cards will generally only have a single CPU. You’ll find multiple CPU systems among supercomputers, servers, and similar high-end systems that need as much number-crunching power as they can get.

The more CPUs or cores a computer has, the more things it can do at once, helping improve performance on most tasks.Most computers now have CPUs with multiple cores—the most efficient option we’ve discussed. You’ll even find CPUs with multiple cores on modern smartphones and tablets. Intel CPUs also feature hyper-threading, which is kind of a bonus. Some computers that need a large amount of CPU power may have multiple CPUs, but it’s much less efficient than it sounds.

