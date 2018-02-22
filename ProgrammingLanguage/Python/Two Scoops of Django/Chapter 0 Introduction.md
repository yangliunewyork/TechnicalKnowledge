The best way to send us feedback is to file an issue at https://github.com/twoscoops/two-scoops-of-django-1.8/issues.

To use this book to its fullest extent, you should have an understanding of the Python programming language and have at least gone through the 6 page Django tutorial: https://docs.djangoproject.com/en/1.8/intro/tutorial01/.

Code samples are available online at http://www.2scoops.co/1.8-code-examples/.

# Core Concepts

When we build Django projects, we keep the following concepts in mind.

#### Keep It Simple, Stupid

Kelly Johnson, one of the most renowned and proli􀅀c aircraft design engineers in the history of aviation, said it this way about 50 years ago. Centuries earlier, Leonardo da Vinci meant the same thing when he said, __"Simplicity is the ultimate sophistication."__

When building software projects, each piece of unnecessary complexity makes it harder to add new features and maintain old ones. Attempt the simplest solution, but take care not to implement overly simplistic solutions that make bad assumptions. This concept is sometimes abbreviated as "KISS."

#### Fat Models, Utility Modules, Thin Views, Stupid Templates

When deciding where to put a piece of code, we like to follow the “Fat Models, Utility Modules, Thin Views, Stupid Templates” approach. 

We recommend that you err on the side of putting more logic into anything but views and templates. The results are pleasing. The code becomes clearer, more self-documenting, less duplicated, and a lot more reusable. As for template tags and 􀅀lters, they should contain the least amount of logic possible to function.

#### Be Familiar with Django's Design Philosophies

It is good to periodically read the documentation on Django’s design philosophy because it helps us understand why Django provides certain constraints and tools. Like any framework, Django is more than just a tool for providing views, it’s a way of doing things designed to help us put together maintainable projects in a reasonable amount of time.

https://docs.djangoproject.com/en/1.8/misc/design-philosophies/

#### The Twelve-Factor App

A comprehensive approach to web-based application design, the Twelve-Factor App approach is growing in popularity amongst many senior and core Django developers. It is a methodology for building deployable, scalable applications worth reading and understanding. Parts of it closely match the practices espoused in Two Scoops of Django, and we like to think of it as suggested reading for any web-based application developer.

https://12factor.net/

