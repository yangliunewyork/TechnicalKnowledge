The Art of Unit Testing has the following to say about unit tests:

A unit test should have the following properties:

* It should be automated and repeatable.
* It should be easy to implement.
* Once it’s written, it should remain for future use.
* Anyone should be able to run it.
* It should run at the push of a button.
* It should run quickly.
* and then later adds it should be fully automated, trustworthy, readable, and maintainable.


Good Tests should be "A TRIP" (The acronymn isn't sticky enough - I have a printout of the cheatsheet in the book that I had to pull out to make sure I got this right..)

* Automatic : Invoking of tests as well as checking results for PASS/FAIL should be automatic  
* Thorough: Coverage; Although bugs tend to cluster around certain regions in the code, ensure that you test all key paths and scenarios.. Use tools if you must to know untested regions  
* Repeatable: Tests should produce the same results each time.. every time. Tests should not rely on uncontrollable params.  
* Independent: Very important.
  * Tests should test only one thing at a time. Multiple assertions are okay as long as they are all testing one feature/behavior. When a test fails, it should pinpoint the location of the problem.
  * Tests should not rely on each other - Isolated. No assumptions about order of test execution. Ensure 'clean slate' before each test by using setup/teardown appropriately
* Professional: In the long run you'll have as much test code as production (if not more), therefore follow the same standard of good-design for your test code. Well factored methods-classes with intention-revealing names, No duplication, tests with good names, etc.
Good tests also run Fast. any test that takes over half a second to run.. needs to be worked upon. The longer the test suite takes for a run.. the less frequently it will be run. The more changes the dev will try to sneak between runs.. if anything breaks.. it will take longer to figure out which change was the culprit.  
