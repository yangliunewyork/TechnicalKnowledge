# What is Virtualenv?

A Virtual Environment, put simply, is an isolated working copy of Python which allows you to work on a specific project without worry of affecting other projects

It enables multiple side-by-side installations of Python, one for each project.

It doesn’t actually install separate copies of Python, but it does provide a clever way to keep different project environments isolated. 

# What did Virtualenv do?

Packages installed here will not affect the global Python installation. 

Virtualenv does not create every file needed to get a whole new python environment

It uses links to global environment files instead in order to save disk space end speed up your virtualenv. 

Therefore, there must already have an active python environment installed on your system.

