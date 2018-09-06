http://docs.behat.org/en/v2.5/guides/1.gherkin.html  

Behat is a tool to test the behavior of your application, described in special language called Gherkin. Gherkin is a Business Readable, Domain Specific Language created especially for behavior descriptions. It gives you the ability to remove logic details from behavior tests.

Gherkin serves two purposes: serving as your project’s documentation and automated tests. Behat also has a bonus feature: it talks back to you using real, human language telling you what code you should write.

### Gherkin Syntax

Like YAML or Python, Gherkin is a line-oriented language that uses indentation to define structure. Line endings terminate statements (called steps) and either spaces or tabs may be used for indentation. (We suggest you use spaces for portability.) Finally, most lines in Gherkin start with a special keyword:

```Gherkin
Feature: Some terse yet descriptive text of what is desired
  In order to realize a named business value
  As an explicit system actor
  I want to gain some beneficial outcome which furthers the goal

  Scenario: Some determinable business situation
    Given some precondition
      And some other precondition
     When some action by the actor
      And some other action
      And yet another action
     Then some testable outcome is achieved
      And something else we can check happens too

  Scenario: A different situation
      ...
```

The parser divides the input into features, scenarios and steps. Let’s walk through the above example:

1. Feature: Some terse yet descriptive text of what is desired starts the feature and gives it a title. Learn more about features in the “Features” section.  
2. Behat does not parse the next 3 lines of text. (In order to... As an... I want to...). These lines simply provide context to the people reading your feature, and describe the business value derived from the inclusion of the feature in your software.  
3. Scenario: Some determinable business situation starts the scenario, and contains a description of the scenario. Learn more about scenarios in the “Scenarios” section.  
4. The next 7 lines are the scenario steps, each of which is matched to a regular expression defined elsewhere. Learn more about steps in the “Steps” section.  
5. Scenario: A different situation starts the next scenario, and so on.  

When you’re executing the feature, the trailing portion of each step (after keywords like ```Given```, ```And```, ```When```, etc) is matched to a regular expression, which executes a PHP callback function.

### Features

Every *.feature file conventionally consists of a single feature. Lines starting with the keyword Feature: (or its localized equivalent) followed by three indented lines starts a feature. A feature usually contains a list of scenarios. You can write whatever you want up until the first scenario, which starts with Scenario: (or localized equivalent) on a new line. You can use tags to group features and scenarios together, independent of your file and directory structure.

Every scenario consists of a list of steps, which must start with one of the keywords ```Given```, ```When```, ```Then```, ```But``` or ```And``` (or localized one). Behat treats them all the same, but you shouldn’t. Here is an example:

```Gherkin
Feature: Serve coffee
  In order to earn money
  Customers should be able to
  buy coffee at all times

  Scenario: Buy last coffee
    Given there are 1 coffees left in the machine
    And I have deposited 1 dollar
    When I press the coffee button
    Then I should be served a coffee
```

In addition to basic scenarios, feature may contain scenario outlines and backgrounds.

### Scenarios

Scenario is one of the core Gherkin structures. Every scenario starts with the Scenario: keyword (or localized one), followed by an optional scenario title. Each feature can have one or more scenarios, and every scenario consists of one or more steps.

The following scenarios each have 3 steps:

```Gherkin
Scenario: Wilson posts to his own blog
  Given I am logged in as Wilson
  When I try to post to "Expensive Therapy"
  Then I should see "Your article was published."

Scenario: Wilson fails to post to somebody else's blog
  Given I am logged in as Wilson
  When I try to post to "Greg's anti-tax rants"
  Then I should see "Hey! That's not your blog!"

Scenario: Greg posts to a client's blog
  Given I am logged in as Greg
  When I try to post to "Expensive Therapy"
  Then I should see "Your article was published."
```

