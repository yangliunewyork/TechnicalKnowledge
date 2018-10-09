https://www.quora.com/What-is-difference-between-docker-puppet-chef-and-vagrant . 


Chef/Puppet are the "same", they are configuration management. While you can use them to manage virtual machines or public/private clouds, most people don't tend to use them that way. They are configuration management. They typically come into play after a virtual machine is fired up to get them in a desired state. That is to say, what software is needed on the virtual machine, what users need to be added, what configuration is needed, etc. Thus, it tends to be used for scaling infrastructure.

Vagrant, while also can be used to manage virtual machines and public/private clouds, is usually only used for one off environments. It provides a cohesive file for creating a virtual machine. It is similar to chef/puppet that way, but doesn't tend to be used at scale.

Docker is a separate beast. It has several components, but primarily it is used for "bundling" (Note: it does much more than that, but that is an ELI5 answer) software and requires a host system (or infrastructure) to run on. It adds a little security to applications but mostly provides a consistent "OS" for an application to run on.

In practice, all of these can be utilized in an environment. Here is an example:

Say you have application FunTime. You have eight developers who contribute to this, and FunTime is designed to be ran on a scale-able infrastructure on AWS. It is designed to have a front-end (FunTime-Front) and a back-end (FunTime-API), and requires postgres. 4 developers work on the front end, four developers work on the backend.

I would do the following (there are many ways to skin this cat, but this is one example):

I would use Docker for FunTime-Front and FunTime-API. I would use Vagrant to set up a dev environment for the developers (so that they can tweak various components). Vagrant would: start up the VM locally (or on a cloud if needed), Install docker, pull down the docker images for FunTime-Front and FunTime-API, install postgres, and populate postgres with dummy data, configure network ports to the various components.

Now the developer has the full FunTime stack on their local machine and doesn't have to screw around with configuring anything themselves: they can just type "vagrant up".

On the infrastructure side, I would use chef (or puppet) to configure the Environments: Production, Stage, and Development (or whatever is needed), then chef would install docker on the "application" servers, "postgres" on the postgres servers, apply security settings, etc. In this way all the related servers are the same. If I needed to update a server or add a patch, it would be trivial with configuration management.

In all cases Docker would be used so that there is no application difference between environments, including the developers work station.

This would make sure that you don't hear the excuse "Well, it works on my local machine!" very often. In addition, if there is a bungled deployment, rolling back the application would be VERY easy with Docker.
