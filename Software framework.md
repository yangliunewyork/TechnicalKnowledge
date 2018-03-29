# What is software framework?

__A software framework is software written to help you be productive. It is a skeleton, a complete set of tools that was built with the purpose of allowing you to focus on one or more specific tasks. You take that skeleton and build your application on top of it.__

Frameworks of all kinds are extremely important nowadays, because of the time factor. When building something you will need to invest a lot of your time in building the logic for your application - and you don't want to be forced to program any kind of low-level functionality. Software frameworks do that, they take care of the low-level stuff for you.

If you are making a website you will be highly productive with a web framework, which is a subtype of software framework that targets the web, and offers you the tools needed to be productive when making web applications so that you can only worry about your application logic.

Django (one of the many web frameworks available out there) for example is called: "Web framework for perfectionists with deadlines" - I think that's pretty self-explanatory, what a framework does.

# Defination

In computer programming, __a software framework is an abstraction in which software providing generic functionality can be selectively changed by additional user-written code, thus providing application-specific software__. A software framework provides a standard way to build and deploy applications. A software framework is a universal, reusable software environment that provides particular functionality as part of a larger software platform to facilitate development of software applications, products and solutions. Software frameworks may include support programs, compilers, code libraries, tool sets, and application programming interfaces (APIs) that bring together all the different components to enable development of a project or system.

Frameworks have key distinguishing features that separate them from normal libraries:

* __inversion of control__: In a framework, unlike in libraries or in standard user applications, the overall program's flow of control is not dictated by the caller, but by the framework.
* __extensibility__: A user can extend the framework - usually by selective overriding; or programmers can add specialized user code to provide specific functionality.
* __non-modifiable framework code__: The framework code, in general, is not supposed to be modified, while accepting user-implemented extensions. In other words, users can extend the framework, but should not modify its code.

# Rationale

__The designers of software frameworks aim to facilitate software developments by allowing designers and programmers to devote their time to meeting software requirements rather than dealing with the more standard low-level details of providing a working system, thereby reducing overall development time.__ For example, a team using a web framework to develop a banking website can focus on writing code particular to banking rather than the mechanics of request handling and state management.

Frameworks often add to the size of programs, a phenomenon termed "code bloat". Due to customer-demand driven applications needs, both competing and complementary frameworks sometimes end up in a product. Further, due to the complexity of their APIs, the intended reduction in overall development time may not be achieved due to the need to spend additional time learning to use the framework; this criticism is clearly valid when a special or new framework is first encountered by development staff. If such a framework is not used in subsequent job taskings, the time invested in learning the framework can cost more than purpose-written code familiar to the project's staff; many programmers keep copies of useful boilerplate for common needs.

However, once a framework is learned, future projects can be faster and easier to complete; the concept of a framework is to make a one-size-fits-all solution set, and with familiarity, code production should logically rise. There are no such claims made about the size of the code eventually bundled with the output product, nor its relative efficiency and conciseness. Using any library solution necessarily pulls in extras and unused extraneous assets unless the software is a compiler-object linker making a tight (small, wholly controlled, and specified) executable module.

The issue continues, but a decade-plus of industry experience has shown that the most effective frameworks turn out to be those that evolve from re-factoring the common code of the enterprise, instead of using a generic "one-size-fits-all" framework developed by third parties for general purposes. An example of that would be how the user interface in such an application package as an office suite grows to have common look, feel, and data-sharing attributes and methods, as the once disparate bundled applications grow unified into a suite which is tighter and smaller; the newer/evolved suite can be a product that shares integral utility libraries and user interfaces.

This trend in the controversy brings up an important issue about frameworks. Creating a framework that is elegant, versus one that merely solves a problem, is still an art rather than a science. "Software elegance" implies clarity, conciseness, and little waste (extra or extraneous functionality, much of which is user defined). For those frameworks that generate code, for example, "elegance" would imply the creation of code that is clean and comprehensible to a reasonably knowledgeable programmer (and which is therefore readily modifiable), versus one that merely generates correct code. The elegance issue is why relatively few software frameworks have stood the test of time: the best frameworks have been able to evolve gracefully as the underlying technology on which they were built advanced. Even there, having evolved, many such packages will retain legacy capabilities bloating the final software as otherwise replaced methods have been retained in parallel with the newer methods.
