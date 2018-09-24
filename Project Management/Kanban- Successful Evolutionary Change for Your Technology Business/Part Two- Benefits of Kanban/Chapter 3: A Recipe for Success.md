
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

### Reduce Work-in-Progress and Deliver Often

Excerpt From: Anderson, David J. “Kanban: Successful Evolutionary Change for Your Technology Business.” iBooks. 
