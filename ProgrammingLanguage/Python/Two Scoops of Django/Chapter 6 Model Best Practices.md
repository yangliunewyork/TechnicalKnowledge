Models are the foundation of most Django projects. Racing to write Django models without thinking things through can lead to problems down the road. All too frequently we developers rush into adding or modifying models without considering the rami􀅀cations of what we are doing. The quick fix or sloppy “temporary” design decision that we toss into our code base now can hurt us in the months or years to come, forcing crazy workarounds or corrupting existing data.

So keep this in mind when adding new models in Django or modifying existing ones. Take your time to think things through, and design your foundation to be as strong and sound as possible.

Here’s a quick list of the model-related Django packages that we use in practically every project. 

* __django-model-utils__ to handle common patterns like TimeStampedModel. 
* __django-extensions__ has a powerful management command called shell plus which autoloads the model classes for all installed apps. The downside of this library is that it includes a lot of other functionality which breaks from our preference for small, focused apps.

## 6.1 Basics

