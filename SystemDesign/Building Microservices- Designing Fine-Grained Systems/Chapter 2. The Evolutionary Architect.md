### Inaccurate Comparisons

Architects have an important job. They are in charge of making sure we have a joined-up technical vision, one that should help us deliver the system our customers need. In some places, they may only have to work with one team, in which case the role of the architect and technical lead is often the same. In others, they may be defining the vision for an entire program of work, coordinating with multiple teams across the world, or perhaps even an entire organization. At whatever level they operate, the role is a tricky one to pin down, and despite it often being the obvious career progression for developers in enterprise organizations, it is also a role that gets more criticism than virtually any other. More than any other role, architects can have a direct impact on the quality of the systems built, on the working conditions of their colleagues, and on their organization’s ability to respond to change, and yet we so frequently seem to get this role wrong. 

### An Evolutionary Vision for the Architect

Our requirements shift more rapidly than they do for people who design and build buildings—as do the tools and techniques at our disposal. The things we create are not fixed points in time. Once launched into production, our software will continue to evolve as the way it is used changes. For most things we create, we have to accept that once the software gets into the hands of our customers we will have to react and adapt, rather than it being a never-changing artifact. Thus, our architects need to shift their thinking away from creating the perfect end product, and instead focus on helping create a framework in which the right systems can emerge, and continue to grow as we learn more.

### Zoning

So, to continue the metaphor of the architect as town planner for a moment, what are our zones? These are our service boundaries, or perhaps coarse-grained groups of services. As architects, we need to worry much less about what happens inside the zone than what happens between the zones. That means we need to spend time thinking about how our services talk to each other, or ensuring that we can properly monitor the overall health of our system. How involved we get inside the zone will vary somewhat. Many organizations have adopted microservices in order to maximize for autonomy of teams. If you are in such an organization, you will rely more on the team to make the right local decision.

But between the zones, or the boxes on our traditional architecture diagram, we need to be careful; getting things wrong here leads to all sorts of problems and can be very hard to correct.

Between services is where things can get messy, however. If one service decides to expose REST over HTTP, another makes use of protocol buffers, and a third uses Java RMI, then integration can become a nightmare as consuming services have to understand and support multiple styles of interchange. This is why I try to stick to the guideline that we should “be worried about what happens between the boxes, and be liberal in what happens inside.

### The Required Standard

##### Monitoring

It is essential that we are able to draw up coherent, cross-service views of our system health. This has to be a system-wide view, not a service-specific view. As we’ll discuss in Chapter 8, knowing the health of an individual service is useful, but often only when you’re trying to diagnose a wider problem or understand a larger trend. To make this as easy as possible, I would suggest ensuring that all services emit health and general monitoring-related metrics in the same way.

You might choose to adopt a push mechanism, where each service needs to push this data into a central location. For your metrics this might be Graphite, and for your health it might be Nagios. Or you might decide to use polling systems that scrape data from the nodes themselves. But whatever you pick, try to keep it standardized. Make the technology inside the box opaque, and don’t require that your monitoring systems change in order to support it. Logging falls into the same category here: we need it in one place.

##### Interfaces

Picking a small number of defined interface technologies helps integrate new consumers. Having one standard is a good number. Two isn’t too bad, either. Having 20 different styles of integration is bad. This isn’t just about picking the technology and the protocol. If you pick HTTP/REST, for example, will you use verbs or nouns? How will you handle pagination of resources? How will you handle versioning of end points?

##### Architectural Safety

We cannot afford for one badly behaved service to ruin the party for everyone. We have to ensure that our services shield themselves accordingly from unhealthy, downstream calls. The more services we have that do not properly handle the potential failure of downstream calls, the more fragile our systems will be. This means you will probably want to mandate as a minimum that each downstream service gets its own connection pool, and you may even go as far as to say that each also uses a circuit breaker. 

Playing by the rules is important when it comes to response codes, too. If your circuit breakers rely on HTTP codes, and one service decides to send back 2XX codes for errors, or confuses 4XX codes with 5XX codes, then these safety measures can fall apart. Similar concerns would apply even if you’re not using HTTP; knowing the difference between a request that was OK and processed correctly, a request that was bad and thus prevented the service from doing anything with it, and a request that might be OK but we can’t tell because the server was down is key to ensuring we can fail fast and track down issues. If our services play fast and loose with these rules, we end up with a more vulnerable system.

### Governance Through Code

Getting together and agreeing on how things can be done is a good idea. But spending time making sure people are following these guidelines is less fun, as is placing a burden on developers to implement all these standard things you expect each service to do. I am a great believer in making it easy to do the right thing. Two techniques I have seen work well here are using exemplars and providing service templates.

##### Exemplars

Written documentation is good, and useful. I clearly see the value; after all, I’ve written this “book. But developers also like code, and code they can run and explore. If you have a set of standards or best practices you would like to encourage, then having exemplars that you can point people to is useful. The idea is that people can’t go far wrong just by imitating some of the better parts of your system.

Ideally, these should be real-world services you have that get things right, rather than isolated services that are just implemented to be perfect examples. By ensuring your exemplars are actually being used, you ensure that all the principles you have actually make sense.

### Summary

To summarize this chapter, here are what I see as the core responsibilities of the evolutionary architect:

* Vision : Ensure there is a clearly communicated technical vision for the system that will help your system meet the requirements of your customers and organization
* Empathy : Understand the impact of your decisions on your customers and colleagues
* Collaboration : Engage with as many of your peers and colleagues as possible to help define, refine, and execute the vision
* Adaptability : Make sure that the technical vision changes as your customers or organization requires it
* Autonomy : Find the right balance between standardizing and enabling autonomy for your teams
* Governance : Ensure that the system being implemented fits the technical vision


The evolutionary architect is one who understands that pulling off this feat is a constant balancing act. Forces are always pushing you one way or another, and understanding where to push back or where to go with the flow is often something that comes only with experience. But the worst reaction to all these forces that push us toward change is to become more rigid or fixed in our thinking.

While much of the advice in this chapter can apply to any systems architect, microservices give us many more decisions to make. Therefore, being better able to balance all of these trade-offs is essential.





