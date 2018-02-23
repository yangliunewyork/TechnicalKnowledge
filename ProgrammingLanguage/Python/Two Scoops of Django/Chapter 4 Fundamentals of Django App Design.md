It’s not uncommon for new Django developers to become understandably confused by Django’s usage of the word “app.” So before we get into Django app design, it’s very important that we go over some definitions.

* A Django project is a web application powered by the Django web framework.  
* Django apps are small libraries designed to represent a single aspect of a project. A Django project is made up of many Django apps.   Some of those apps are internal to the project and will never be reused; others are third-party Django packages.  
* INSTALLED APPS is the list of Django apps used by a given project available in its INSTALLED APPS setting.  
* Third-party Django packages are simply pluggable, reusable Django apps that have been packaged with the Python packaging tools.  
* Sauce: Third-Party Packages.  

James Bennett volunteers as both a Django core developer and as its release manager. He taught us everything that we know about good Django app design. We quote him: "The art of creating and maintaining a good Django app is that it should follow the truncated Unix philosophy according to Douglas McIlroy: ‘Write programs that do one thing and do it well."

In essence, each app should be tightly focused on its task. If an app can’t be explained in a single sentence of moderate length, or you need to say ‘and’ more than once, it probably means the app is too big and should be broken up.

