### Introduction

Selenium is an open-source and a portable automated software testing tool for testing web applications. It has capabilities to operate across different browsers and operating systems. Selenium is not just a single tool but a set of tools that helps testers to automate web-based applications more efficiently.

Let us now understand each one of the tools available in the Selenium suite and their usage.

### Advantages of Selenium

* Selenium is an open-source tool.  
* Can be extended for various technologies that expose DOM.  
* Has capabilities to execute scripts across different browsers.  
* Can execute scripts on various operating systems.  
* Supports mobile devices.  
* Executes tests within the browser, so focus is NOT required while script execution is in progress.  
* Can execute tests in parallel with the use of Selenium Grids.   

### Disadvantages of Selenium

* Supports only web based applications.  
* No feature such as Object Repository/Recovery Scenario.
* No IDE, so the script development won't be as fast as QTP.  
* Cannot access controls within the browser.  
* No default test report generation.  
* For parameterization, users has to rely on the programming language.  

### Selenium - Webdriver

<img src="https://www.tutorialspoint.com/selenium/images/selenium_ide_92.jpg">

WebDriver is a tool for automating testing web applications. It is popularly known as Selenium 2.0. WebDriver uses a different underlying framework, while Selenium RC uses JavaScript Selenium-Core embedded within the browser which has got some limitations. WebDriver interacts directly with the browser without any intermediary, unlike Selenium RC that depends on a server. It is used in the following context −

* Multi-browser testing including improved functionality for browsers which is not well-supported by Selenium RC (Selenium 1.0).
* Handling multiple frames, multiple browser windows, popups, and alerts.
* Complex page navigation.
* Advanced user navigation such as drag-and-drop.
* AJAX-based UI elements.
