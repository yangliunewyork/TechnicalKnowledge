## 1.1 The Importance of Making Your Code Readable

Code is read more than it is written. An individual block of code takes moments to write, minutes or hours to debug, and can last forever without being touched again. It’s when you or someone else visits code written yesterday or ten years ago that having code written in a clear, consistent style becomes extremely useful. Understandable code frees mental bandwidth from having to puzzle out inconsistencies, making it easier to maintain and enhance projects of all sizes.

What this means is that you should go the extra mile to make your code as readable as possible:

* Avoid abbreviating variable names.  
* Write out your function argument names.  
* Document your classes and methods.  
* Comment your code.  
* Refactor repeated lines of code into reusable functions or methods.  
* Keep functions and methods short. A good rule of thumb is that scrolling should not be necessary to read an entire function or method.

## 1.2 PEP 8

PEP 8 is the official style guide for Python. We advise reading it in detail and learn to follow the PEP 8 coding conventions: http://www.python.org/dev/peps/pep-0008/

All the Python files in your Django projects should follow PEP 8. If you have trouble remembering the PEP 8 guidelines, find a plugin for your code editor that checks your code as you type.

PACKAGE TIP: Use flake8 For Checking Code Quality 

Created by Tarek Ziadé and now maintained by the PyCQA group, this is a very useful command-line tool for checking coding style, quality, and logic errors in projects. Use while developing locally and as a component of Continuous Integration.

## 1.3 The Word on Imports

PEP 8 suggests that imports should be grouped in the following order:

1. Standard library imports    
2. Related third-party imports    
3. Local application or library specific imports   

The import order in a Django project is:

1. Standard library imports.   
2. Imports from core Django.   
3. Imports from third-party apps including those unrelated to Django.   
4. Imports from the apps that you created as part of your Django project.  

## 1.4 Use Explicit Relative Imports

When writing code, it’s important to do so in such a way that it’s easier to move, rename, and version your work. In Python, explicit relative imports remove the need for hardcoding a module’s package, separating individual modules from being tightly coupled to the architecture around them. Since Django apps are simply Python packages, the same rules apply.

## 1.5 Avoid Using Import *

The reason for this is to avoid implicitly loading all of another Python module’s locals into and over our current module’s namespace, this can produce unpredictable and sometimes catastrophic results.


## 1.6 Django Coding Style

It goes without saying that it’s a good idea to be aware of common Django style conventions. In fact, internally Django has its own set of style guidelines that extend PEP 8: http://2scoops.co/1.8-coding-style .

Additionally, while the following are not specified in the official standards, they are common enough in the Django community that you will probably want to follow them in your projects.

## 1.7 Choose JS, HTML, and CSS Style Guides

#### 1.7.1 JavaScript Style Guides

* idiomatic.js: Principles of Writing Consistent, Idiomatic JavaScript https://github.com/rwaldron/idiomatic.js/  
* Pragmatic.js code style guidelines https://github.com/madrobby/pragmatic.js  
* Airbnb JavaScript Style Guide https://github.com/airbnb/javascript  
* Node.js Style Guide https://github.com/felixge/node-style-guide  
* Code Conventions for the JavaScript Programming Language  http://javascript.crockford.com/code.html  

#### 1.7.2 HTML and CSS Style Guides

* Code Guide by @mdo for HTML and CSS: http://codeguide.co
* idomatic-css: Principles of Writing Consistent, Idiomatic CSS: https://github.com/necolas/idiomatic-css  

CSScomb (http://csscomb.com/) is a coding style formatter for CSS. It checks for consistency against the rules for which you con􀅀gure it for, and it checks the sort order of your CSS properties. Just as for JSCS, there are CSScomb text editor and task/build tool plugins, including for Brunch.  







