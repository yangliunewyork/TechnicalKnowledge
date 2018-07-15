### Four Reasons to Change Software

For simplicity’s sake, let’s look at four primary reasons to change software.

```
1. Adding a feature
2. Fixing a bug
3. Improving the design
4. Optimizing resource usage
```

> Behavior is the most important thing about software. It is what users depend on. Users like it when we add behavior (provided it is what they really wanted), but if we change or remove behavior they depend on (introduce bugs), they stop trusting us.

### Improving Design

Design improvement is a different kind of software change. When we want to alter software’s structure to make it more maintainable, generally we want to keep its behavior intact also. When we drop behavior in that process, we often call that a bug. One of the main reasons why many programmers don’t attempt to improve design often is because it is relatively easy to lose behavior or create bad behavior in the process of doing it.

The act of improving design without changing its behavior is called __refactoring__. The idea behind refactoring is that we can make software more maintainable without changing behavior if we write tests to make sure that existing behavior doesn’t change and take small steps to verify that all along the process. People have been cleaning up code in systems for years, but only in the last few years has refactoring taken off. Refactoring differs from general cleanup in that we aren’t just doing low-risk things such as reformatting source code, or invasive and risky things such as rewriting chunks of it. Instead, we are making a series of small structural modifications, supported by tests to make the code easier to change. The key thing about refactoring from a change point of view is that there aren’t supposed to be any functional changes when you refactor (although behavior can change somewhat because the structural changes that you make can alter performance, for better or worse).

### Optimization

Optimization is like refactoring, but when we do it, we have a different goal. With both refactoring and optimization, we say, “We’re going to keep functionality exactly the same when we make changes, but we are going to change something else.” In refactoring, the “something else” is program structure; we want to make it easier to maintain. In optimization, the “something else” is some resource used by the program, usually time or memory.

### Putting It All Together

In general, three different things can change when we do work in a system: structure, functionality, and resource usage.

### Risky Change

Preserving behavior is a large challenge. When we need to make changes and preserve behavior, it can involve considerable risk.

To mitigate risk, we have to ask three questions:

1. What changes do we have to make?
2. How will we know that we’ve done them correctly?
3. How will we know that we haven’t broken anything?

How much change can you afford if changes are risky?

Most teams that I’ve worked with have tried to manage risk in a very conservative way. They minimize the number of changes that they make to the code base. Sometimes this is a team policy: “If it’s not broke, don’t fix it.” At other times, it isn’t anything that anyone articulates. The developers are just very cautious when they make changes. “What? Create another method for that? No, I’ll just put the lines of code right here in the method, where I can see them and the rest of the code. It involves less editing, and it’s safer.”

Excerpt From: Michael C. Feathers. “Working Effectively with Legacy Code.” iBooks. 

It’s tempting to think that we can minimize software problems by avoiding them, but, unfortunately, it always catches up with us. When we avoid creating new classes and methods, the existing ones grow larger and harder to understand. When you make changes in any large system, you can expect to take a little time to get familiar with the area you are working with. The difference between good systems and bad ones is that, in the good ones, you feel pretty calm after you’ve done that learning, and you are confident in the change you are about to make. In poorly structured code, the move from figuring things out to making changes feels like jumping off a cliff to avoid a tiger. You hesitate and hesitate. “Am I ready to do it? Well, I guess I have to.”

Avoiding change has other bad consequences. When people don’t make changes often they get rusty at it. Breaking down a big class into pieces can be pretty involved work unless you do it a couple of times a week. When you do, it becomes routine. You get better at figuring out what can break and what can’t, and it is much easier to do.

The last consequence of avoiding change is fear. Unfortunately, many teams live with incredible fear of change and it gets worse every day. Often they aren’t aware of how much fear they have until they learn better techniques and the fear starts to fade away.

Excerpt From: Michael C. Feathers. “Working Effectively with Legacy Code.” iBooks. 
