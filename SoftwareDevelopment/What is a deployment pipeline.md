https://medium.com/the-making-of-appear-in/what-is-a-deployment-pipeline-and-how-it-helps-software-development-teams-6cb29917ceea. 

Deployment pipeline is a concept for avoiding waste in the software development process, and it is used for providing quick feedback to the team during deployment. It works in the following way: the software deployment is divided in different stages, where tasks are run in each of these stages. In the same stage, tasks can be executed in parallel, for helping on the feedback loop. When all tasks in a stage passes, the tasks in the next stages can start (this can be triggered manually or in an automated way).

In the below image I tried to visually show you an example of a deployment pipeline, where after a developer pushes his/her code to a remote repository, the deployment pipeline starts. First building the application, then running code analysis, unit tests, and integration/API tests (all in parallel). If all the tasks in this stage of the pipeline passes, then a smoke test suite is triggered, and if the smoke test also passes, it triggers the regression test suite and the visual regression test suite (executed in parallel), and then, if this final stage passes as well, then we have a release candidate that can be promoted to production, so that users can enjoy.

<img src="https://cdn-images-1.medium.com/max/1200/1*ciSnNL0ypQRfn1UvdCT4ZQ.png">

The importance of using this approach, as already mentioned, is about avoiding waste. This means that if, for example, one or more tasks in some of the stages fail, it automatically fails all the deployment, and no time is waste running the other tasks unnecessarily.

Another important point about using deployment pipelines is that we can separate tasks that take longer time to execute from tasks that run faster. An example of this is a comparison of the time spent on executing a suite of unit tests versus a suite of end-to-end regression tests.


Last, but not least, a deployment pipeline can be used to show the value stream map of all the deployment workflow. This can be a powerful and valuable artifact for making non-technical people understand what is necessary to deliver high-quality software, and then having their help on providing the necessary resources to make it happens.

