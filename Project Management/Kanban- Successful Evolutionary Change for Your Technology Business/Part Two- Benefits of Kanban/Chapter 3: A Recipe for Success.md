
The six steps in the recipe are:

* Focus on Quality
* Reduce Work-in-Progress
* Deliver Often
* Balance Demand against Throughput
* Prioritize
* Attack Sources of Variability to Improve Predictability”

### Implementing the Recipe

The recipe is delivered in order of execution for a technical function manager. Focus on Quality is first, as it is under the sole control and influence of a manager such as a development or test manager, or the manager’s supervisor, with a title like Director of Engineering. Working down the list, there is gradually less control and more collaboration required with other downstream and upstream groups until the Prioritize step. Prioritization is rightly the job of the business sector, not the technology organization, and so should not be within a technical manager’s remit. Unfortunately, it is commonplace for business management to abdicate that responsibility and leave a technical manager to prioritize the work—and then blame that manager for making poor choices. Attack Sources of Variability to Improve Predictability is last on the list because some types of variability require behavioral changes in order to reduce them. Asking people to change behavior is difficult! So attacking variability is better left until a climate change results from some success with the earlier steps. It is sometimes necessary to address sources of variability in order to enable some of those earlier steps. The trick is to pick sources of variability that require little behavioral change and can be readily accepted.

Focusing on quality is easiest because it is a technical discipline that can be directed by the function manager. The other steps are more of a challenge because they depend on agreement and collaboration from other teams. They require skills in articulation, negotiation, psychology, sociology, and emotional intelligence. Building consensus around the need to Balance Demand against Throughput is crucial. Solving issues with dysfunction between roles and the responsibilities of team members requires even greater diplomatic and negotiation skills. It makes sense, then, to go after things that are directly under your control and that you know will have a positive effect on both your team’s and your business’s performance.

Developing an increased level of trust with other teams can enable the harder things. Building and demonstrating high quality code with few defects improves trust. Releasing high-quality code with regularity builds yet more trust. As the level of trust increases, the manager gains more political capital. This enables a move to the next step in the recipe. Ultimately your team will gain sufficient respect that you are able to influence product owners, your marketing team, and business sponsors to change their behavior and collaborate to prioritize the most valuable work for development.

Attacking sources of variability to improve predictability is hard. It should not be undertaken until a team is already performing at a more mature and greatly improved level. The first four steps in the recipe will have a significant impact. They will deliver success for a new manager. However, to truly create a culture of innovation and continuous improvement, it will be necessary to attack the sources of variability in the process. So the final step in the recipe is for extra credit: It’s the step that separates the truly great technical leaders from the merely competent managers.

### Focus on Quality

The Agile Manifesto doesn’t say anything about quality, although the Principles Behind the Manifesto[1] do talk about craftsmanship, and there is an implied focus on quality. So if quality doesn’t appear in the Manifesto, why is it first in my recipe for success? Put simply, excessive defects are the biggest waste in software development. The numbers on this are staggering and show several orders of magnitude variation. Capers Jones reports that in 2000, during the dot-com bubble, he measured software quality for North American teams that ranged from 6 defects per function point down to less than 3 per 100 function points, a range of 200 to 1. The midpoint is approximately 1 defect per 0.6 to 1.0 function points. This implies that it is common for teams to spend more than 90 percent of their effort fixing defects.

Encouraging high initial quality will have a big impact on the productivity and throughput of teams with high defect rates. A two- to four-times throughput improvement is reasonable. With truly bad teams, a ten-times improvement may be possible by focusing on quality.

Improving software quality is a well-understood problem.

Both agile development and traditional approaches to quality have merit. They should be used in combination. Professional testers should do testing. Using testers finds defects and prevents them from escaping into production code. Asking developers to write unit tests and automate them to provide automated regression testing also has a dramatic effect. There seems to be a psychological advantage in asking developers to write the tests first. So-called Test Driven Development (TDD) does seem to provide the advantage that test coverage is more complete. It is worth pointing out that well-disciplined teams I’ve managed who wrote tests after functional coding demonstrated industry-leading quality. Nevertheless, it appears evident that, for the average team, insisting on writing tests first, before functional coding, improves quality.

Code inspections improve quality. Whether it is pair programming, peer review, code walkthroughs, or full Fagan inspections, code inspections work. They help to improve both external quality and internal code quality. Code inspections are best done often and in small batches. I encourage teams to inspect code every day for at least 30 minutes.

Collaborative analysis and design improve quality. When teams are asked to work together to analyze problems and design solutions, the quality is higher. I encourage teams to hold collaborative team analysis and design modeling sessions. Design modeling should be done in small batches every day. Scott Ambler has called this Agile Modeling.

The use of design patterns improves quality. Design patterns capture known solutions to known problems. Design patterns ensure that more information is available earlier in the lifecycle and that design defects are eliminated.
The use of modern development tools improves quality. Many modern tools include functions to perform static and dynamic code analysis. This should be switched on and tuned for each project. These analysis tools can prevent programmers from making elementary mistakes, such as introducing well-understood problems like security flaws.

More exotic modern development tools such as Software Product Lines (or Software Factories) and Domain Specific Languages reduce defects. Software Factories can be used to encapsulate design patterns as code fragments, thereby reducing the defect-insertion potential from entering code. They also can be used to automate away repetitive coding tasks; again, reducing the defect-insertion potential of entering code. The use of software factories also reduces the demands on code inspections, as factory code doesn’t need to be re-inspected. It has a known quality.

Some of these latter suggestions really fall into the category of reducing variability in the process. The use of software factories and perhaps even design patterns is asking developers to change their behavior. The big bang for the buck comes from using professional testers; writing tests first, automating regression testing, and code inspections. And one more thing…

Reducing the quantity of design-in-progress boosts software quality.

### WIP, Lead Time, and Defects

There is causation between quantity of work-in-progress and average lead time, and the relationship is linear. In the manufacturing industry, this relationship is known as Little’s Law. The evidence from these two teams at Motorola suggests that there is a correlation between increased lead time and poorer quality. Longer lead times seem to be associated with significantly poorer quality. In fact, an approximately six-and-a-half times increase in average lead time resulted in a greater than 30-fold increase in initial defects. Longer average lead times result from greater amounts of work-in-progress. Hence, the management leverage point for improving quality is to reduce the quantity of work-in-progress. Since uncovering this evidence I have managed work-in-progress as a means to control quality and have become convinced of the relationship between the quantity of WIP and initial quality. However, at the time of writing there is no scientific evidence to back up this empirically observed result.

Reducing work-in-progress, or shortening the length of an iteration, will have a significant impact on initial quality. It appears that the relationship between quantity of work-in-progress and initial quality is non-linear; that is, defects will rise disproportionately to increases in quantity of WIP. Therefore, it makes sense that two-week iterations are better than four-week iterations and that one-week iterations are better still. Shorter iterations will drive higher quality.

### Frequent Releases Build Trust

Reducing WIP shortens lead time. Shorter lead times mean that it is possible to release working code more often. More frequent releases build trust with external teams, particularly the marketing team or business sponsors. Trust is a hard thing to define. Sociologists call it social capital. What they’ve learned is that trust is event driven and that small, frequent gestures or events enhance trust more than larger gestures made only occasionally.

When I teach this in classes, I like to ask women in the class what they think after they go on a first date with a guy. I suggest that they had a nice time and then he doesn’t call them for two weeks. He then turns up on their doorstep with a bunch of flowers and an apology. I ask them to compare this to a guy who takes the time to type a text message on his way home that evening to say, “I had a great time tonight. I really want to see you again. Call you tomorrow?” and then follows up by actually calling the next day. Guess who they prefer? Small gestures often cost nothing but build more trust than large, expensive (or expansive) gestures bestowed occasionally.

And so it is with software development. Delivering small, frequent, high-quality releases builds more trust with partner teams than putting out larger releases less often.

Small releases show that the software development team can deliver and is committed to providing value. They build trust with the marketing team or business sponsors. High quality in the released code builds trust with downstream partners such as operations, technical support, field engineering, and sales.

### Tacit Knowledge

It’s quite easy to speculate why small batches of code improve quality. Complexity in knowledge-work problems grows exponentially with the quantity of work-in-progress. Meanwhile, our human brains struggle to cope with all this complexity. So much of knowledge transfer and information discovery in software development is tacit in nature and is created during collaborative working sessions, face-to-face. The information is verbal and visual but it’s in a casual format like a sketch on a whiteboard. Our minds have a limited capacity to store all this tacit knowledge and it degrades while we store it. We fail to recall precise details and make mistakes. If a team is co-located and always available to each other, this memory loss can be corrected through repeated discussion or tapping the shared memory of a group of people. So agile teams co-located in a shared workspace are more likely to retain tacit knowledge longer. Regardless of this, tacit knowledge depreciates with time, so shorter lead times are essential for tacit knowledge processes. We know that reducing work-in-progress is directly related to reducing lead times. Hence, we can infer that there will be lower tacit-knowledge depreciation when we have less work-in-progress, resulting in higher quality.

In summary, reducing work-in-progress improves quality and enables more frequent releases. More frequent releases of higher quality code improve trust with external teams.

### Balance Demand against Throughput

Balancing demand against throughput implies that we will set the rate at which we accept new requirements into our software development pipe to correspond with the rate at which we can deliver working code. When we do this, we are effectively fixing our work-in-progress to a given size. As work is delivered, we will pull new work (or requirements) from the people creating demand. So any discussion about prioritization and commitment to new work can happen only in the context of delivering some existing work.

The effect of this change is profound. The throughput of your process will be constrained by a bottleneck. It’s unlikely you know where that bottleneck is. In fact, if you speak to everyone in the value stream, they will probably all claim to be completely overloaded. However, once you balance demand against throughput and limit the work-in-progress within your value stream, magic will happen. Only the bottleneck resources will remain fully loaded. Very quickly, other workers in the value stream will find they have slack capacity. Meanwhile, those working in the bottleneck will be busy, but not swamped. For the first time, perhaps in years, the team will no longer be overloaded and many people will experience something very rare in their careers, the feeling of having time on their hands.

### Create Slack

Much of the stress will be lifted off the organization and people will be able to focus on doing their jobs with precision and quality. They’ll be able to take pride in their work and will enjoy the experience all the more. Those with time on their hands will start to put that time toward improving their own circumstances; they may tidy up their workspace or take some training. They will likely start to apply themselves to bettering their skills, their tools, and how they interact with others up- and downstream. As time passes and one small improvement leads to another, the team will be seen as continuously improving. The culture will have changed. The slack capacity created by the act of limiting work-in-progress and pulling new work only as capacity is available will enable improvement no one thought was possible.

You need slack to enable continuous improvement. You need to balance demand against throughput and limit the quantity of work-in-progress to enable slack.

Intuitively, people believe they have to eliminate slack. So after limiting work-in-progress by balancing demand against throughput, the tendency is to “balance the line” by adjusting resources so that everyone is efficiently fully utilized. Although this may look efficient and satisfy typical twentieth-century management accounting practices, it will impede the creation of an improvement culture. You need slack to enable continuous improvement. In order to have slack, you must have an unbalanced value stream with a bottleneck resource. Optimizing for utilization is not desirable.

### Prioritize

If the first three steps in the recipe have been implemented, things will be running smoothly. High-quality code should be arriving frequently. Development lead times should be relatively short, as work-in-progress is limited. New work should be pulled in to development only as capacity is freed up on completion of existing work. At this point, management’s attention can turn to optimizing the value delivered rather than merely the quantity of code delivered. There is little point in paying attention to prioritization when there is no predictability in delivery. Why waste effort trying to order the input when there is no dependability in the order of delivery? Until this is fixed, management time is better used to focus on improving both the ability to deliver and the predictability of delivery. You should turn your thoughts to ordering the priority of the input once you know you can actually deliver things in approximately the order they are requested.

### Influence

Prioritization should not be controlled by the engineering organization and hence is not under the control of engineering management. Improving prioritization requires the product owner, business sponsor, or marketing department to change their behavior. At best, engineering management can seek only to influence how prioritization is done.

In order to have political and social capital to influence change, a level of trust must have been established. Without the capability to deliver high-quality code regularly, there can be no trust and hence little possibility to influence prioritization and thus optimize the value being delivered from the software team.

Recently, it’s become popular in the Agile community to talk about business-value optimization and how the production rate of working code (called the “velocity” of software development) is not an important metric. This is because business value delivered is the true measure of success. While this may ultimately be true, it is important not to lose sight of the capability maturity ladder that a team must climb. Most organizations are incapable of measuring and reporting business value delivered. They must first build capability in basic skills before they try greater challenges.

### Building Maturity

This is how I think a team should mature: First, learn to build high-quality code. Then reduce the work-in-progress, shorten lead times, and release often. Next, balance demand against throughput, limit work-in-progress, and create slack to free up bandwidth, which will enable improvements. Then, with a smoothly functioning and optimizing software development capability, improve prioritization to optimize value delivery. Hoping for business value optimization is wishful thinking. Take actions to get to this level of maturity incrementally—follow the Recipe for Success.

### Takeaways

* Kanban delivers all aspects of the Recipe for Success.  
* The Recipe for Success explains why Kanban has value.  
* Poor quality can represent the largest waste in software development.  
* Reducing work-in-progress improves quality.   
* Improved quality improves trust with downstream partners such as operations.   
* Releasing frequently improves trust with upstream partners such as marketing.    
* Demand can be balanced against throughput with a pull system.    
* Pull systems expose the bottlenecks and create slack in non-bottlenecks.    
* Good quality prioritization maximizes the value delivered by a well-functioning software development value chain.  
* Prioritization is of little value without good initial quality and predictability of delivery.  
* Making changes to reduce variability requires slack.  
* Reducing variability reduces the need for slack.  
* Reducing variability enables a resource balancing (and, potentially, a reduction in headcount).  
* Reducing variability reduces resource requirements.  
* Reducing variability allows reduced kanban tokens, less WIP, and results in reduced average lead time.  
* Slack enables improvement opportunities.  
* Process improvement leads to greater productivity and greater predictability.  

