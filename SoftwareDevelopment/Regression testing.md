###  What is Regression Testing?

Regression Testing is defined as a type of software testing to confirm that a recent program or code change has not adversely affected existing features.

Regression Testing is nothing but full or partial selection of already executed test cases which are re-executed to ensure existing functionalities work fine.

This testing is done to make sure that new code changes should not have side effects on the existing functionalities. It ensures that old code still works once the new code.

####  Need of Regression Testing

Regression Testing is required when there is a

* Change in requirements and code is modified according to the requirement
* New feature is added to the software
* Defect fixing
* Performance issue fix

#### Benefits and drawbacks

Regression testing is performed when changes are made to the existing functionality of the software or if there is a bug fix in the software. Regression testing can be achieved through multiple approaches, if a test all approach is followed, it provides certainty that the changes made to the software have not affected the existing functionalities, which are unaltered.

In agile software development—where the software development life cycles are very short, resources are scarce, and changes to the software are very frequent—regression testing might introduce a lot of unnecessary overhead.

Typically, regression testing is carried out by automation tools, but the existing generation of regression testing tools is not equipped to handle database applications. For this reason, performing a regression test on a database application could prove to be taxing, as it would require a great deal of manual effort.

Moreover, in a software development environment, which tends to use black box components from a third party, performing regression testing can be tricky, as any change in the third-party component may interfere with the rest of the system (and performing regression testing on a third-party component is difficult, because it is an unknown entity).

### Background

As software is updated or changed, or reused on a modified target, emergence of new faults and/or re-emergence of old faults is quite common. Sometimes re-emergence occurs because a fix gets lost through poor revision control practices (or simple human error in revision control). Often, a fix for a problem will be "fragile" in that it fixes the problem in the narrow case where it was first observed but not in more general cases which may arise over the lifetime of the software. Frequently, a fix for a problem in one area inadvertently causes a software bug in another area. Finally, it may happen that, when some feature is redesigned, some of the same mistakes that were made in the original implementation of the feature are made in the redesign.

Therefore, in most software development situations, it is considered good coding practice, when a bug is located and fixed, to record a test that exposes the bug and re-run that test regularly after subsequent changes to the program.[5] Although this may be done through manual testing procedures using programming techniques, it is often done using automated testing tools.[6] Such a test suite contains software tools that allow the testing environment to execute all the regression test cases automatically; some projects even set up automated systems to re-run all regression tests at specified intervals and report any failures (which could imply a regression or an out-of-date test).[7] Common strategies are to run such a system after every successful compile (for small projects), every night, or once a week. Those strategies can be automated by an external tool.

Regression testing is an integral part of the extreme programming software development method. In this method, design documents are replaced by extensive, repeatable, and automated testing of the entire software package throughout each stage of the software development process. Regression testing is done after functional testing has concluded, to verify that the other functionalities are working.

In the corporate world, regression testing has traditionally been performed by a software quality assurance team after the development team has completed work. However, defects found at this stage are the most costly to fix. This problem is being addressed by the rise of unit testing. Although developers have always written test cases as part of the development cycle, these test cases have generally been either functional tests or unit tests that verify only intended outcomes. Developer testing compels a developer to focus on unit testing and to include both positive and negative test cases.

