# What is Virtualenv?

A Virtual Environment, put simply, is an isolated working copy of Python which allows you to work on a specific project without worry of affecting other projects

It enables multiple side-by-side installations of Python, one for each project.

It doesn’t actually install separate copies of Python, but it does provide a clever way to keep different project environments isolated.

The basic problem being addressed is one of dependencies and versions, and indirectly permissions. Imagine you have an application that needs version 1 of LibFoo, but another application requires version 2. How can you use both these applications? If you install everything into /usr/lib/python2.7/site-packages (or whatever your platform’s standard location is), it’s easy to end up in a situation where you unintentionally upgrade an application that shouldn’t be upgraded.

Or more generally, what if you want to install an application and leave it be? If an application works, any change in its libraries or the versions of those libraries can break the application.

Also, what if you can’t install packages into the global site-packages directory? For instance, on a shared host.

In all these cases, virtualenv can help you. It creates an environment that has its own installation directories, that doesn’t share libraries with other virtualenv environments (and optionally doesn’t access the globally installed libraries either).



# What did Virtualenv do?

Packages installed here will not affect the global Python installation. 

Virtualenv does not create every file needed to get a whole new python environment

It uses links to global environment files instead in order to save disk space end speed up your virtualenv. 

Therefore, there must already have an active python environment installed on your system.

