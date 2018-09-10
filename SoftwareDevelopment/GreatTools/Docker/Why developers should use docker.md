Ever encountered a scenario where you came across a cool python / ruby / node package and you want to try it out without affecting your existing work environment? What about sharing your setup easily with your friends with just one simple command, or the ability to clone your setup to other work stations that you have?

Existing solutions includes using VMs, Virtual environment, package managers such as RVM gemsets. VMs are great, but they often takes up alot of space, memory and processing power. Package managers and virtual environment works - but what if a package you want requires modifying some environmental variables, or installing some new compilers that might affect your existing setup?

The solution: Use Docker! 

### What is Docker about?

Docker allows you to isolate your app from the underlying infrastructure. As long as you have a Docker VM installed on any of the supported base OS, you could simply load the desired Docker Image into a container that is to be executed on the VM.

You could create as many container as you want on the host machine, and each of the container are isolated from one another.

On top of that, each docker images are version controlled. One would write a "docker file" that describe a set of changes that is to be applied on the base image to bring it to a new state. Upon bringing it to a new state, such as installing some new packages, we could choose to save it and have it version controlled.

### How is docker different from a normal virtual machine?

Docker containers are lightweight processes that can run on a VM or a host machine. They usually takes seconds to boot too as compared to a VM. This is great as it allows developers to rapidly fire up multiple containers to test out their code. This is not possible with VMs, unless you have a ton of ram on your host machine. 

### How would this benefit you as a developer?

Imagine being able to accomplish the following:

* Having the exact same environment in prod / dev
* Clone your environment for any new hires! No more painful setups.
* Being able to roll back changes made to the environment
* Testing your app safely on many different environment easily
* Deploy to production and knowing that your code would definitely run without having to implement tweaks in the production server.
* Duplicate your database image easily, so that you can test your prod data without worrying about making mistakes.
* And the benefits just goes on and on ... 
    
    
