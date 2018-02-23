## 2.2 Use Pip and Virtualenv

If you are not doing so already, we strongly urge you to familiarize yourself with both pip and virtualenv. They are the de facto standard for Django projects, and most companies that use Django rely on these tools. 

__Pip__ is a tool that fetches Python packages from the Python Package Index and its mirrors. It is used to manage and install Python packages. It’s like easy install but has more features, the key feature being support for virtualenv. 

__Virtualenv__ is a tool for creating isolated Python environments for maintaining package dependencies. It’s great for situations where you’re working on more than one project at a time, and where there are clashes between the version numbers of different libraries that your projects use.

* pip: http://pip-installer.org
* virtualenv: http://virtualenv.org


We also highly recommend __virtualenvwrapper__ for Mac OS X and Linux or virtualenvwrapper-win for Windows.Virtualenvwrapper is a popular companion tool to pip and virtualenv and makes our lives easier, but it’s not an absolute necessity.

## 2.3 Install Django and Other Dependencies via Pip

The official Django documentation describes several ways of installing Django. Our recommended installation method is with pip and requirements files. To summarize how this works: a requirements file is like a grocery list of Python packages that you want to install. It contains the name and desired version of each package. You use pip to install packages from this list into your virtual environment.

