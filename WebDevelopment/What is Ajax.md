AJAX is a developer's dream, because you can:

* Update a web page without reloading the page
* Request data from a server - after the page has loaded
* Receive data from a server - after the page has loaded
* Send data to a server - in the background

Ajax (also AJAX; /ˈeɪdʒæks/; short for "Asynchronous JavaScript + XML") is a set of Web development techniques using many Web technologies on the client side to create asynchronous Web applications. __With Ajax, Web applications can send and retrieve data from a server asynchronously (in the background) without interfering with the display and behavior of the existing page. By decoupling the data interchange layer from the presentation layer, Ajax allows Web pages, and by extension Web applications, to change content dynamically without the need to reload the entire page.__ In practice, modern implementations commonly utilize JSON instead of XML due to the advantages of JSON being native to JavaScript.

Ajax is not a single technology, but rather a group of technologies. HTML and CSS can be used in combination to mark up and style information. The webpage can then be modified by JavaScript to dynamically display – and allow the user to interact with — the new information. The built-in ```XMLHttpRequest``` object within JavaScript is commonly used to execute Ajax on webpages allowing websites to load content onto the screen without refreshing the page. __Ajax is also not a new technology, or another different language, just existing technologies used in new ways.__

# Technologies

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/0b/Ajax-vergleich-en.svg/600px-Ajax-vergleich-en.svg.png" width="600" height="800">

The term Ajax has come to represent a broad group of Web technologies that can be used to implement a Web application that communicates with a server in the background, without interfering with the current state of the page. In the article that coined the term Ajax,[1][3] Jesse James Garrett explained that the following technologies are incorporated:

* HTML (or XHTML) and CSS for presentation
* The Document Object Model (DOM) for dynamic display of and interaction with data
* JSON or XML for the interchange of data, and XSLT for its manipulation
* The XMLHttpRequest object for asynchronous communication
* JavaScript to bring these technologies together

Since then, however, there have been a number of developments in the technologies used in an Ajax application, and in the definition of the term Ajax itself. XML is no longer required for data interchange and, therefore, XSLT is no longer required for the manipulation of data. JavaScript Object Notation (JSON) is often used as an alternative format for data interchange, although other formats such as preformatted HTML or plain text can also be used. A variety of popular JavaScript libraries, including JQuery, include abstractions to assist in executing Ajax requests.

Asynchronous HTML and HTTP (AHAH) involves using XMLHTTPRequest to retrieve (X)HTML fragments, which are then inserted directly into the Web page.

# Drawbacks

* Any user whose browser does not support JavaScript or XMLHttpRequest, or has this functionality disabled, will not be able to properly use pages that depend on Ajax. Simple devices (such as smartphones and PDAs) may not support the required technologies. The only way to let the user carry out functionality is to fall back to non-JavaScript methods. This can be achieved by making sure links and forms can be resolved properly and not relying solely on Ajax.[17]
* Similarly, some Web applications that use Ajax are built in a way that cannot be read by screen-reading technologies, such as JAWS. The WAI-ARIA standards provide a way to provide hints in such a case.[18]
* Screen readers that are able to use Ajax may still not be able to properly read the dynamically generated content.[19]
* The same-origin policy prevents some Ajax techniques from being used across domains,[12] although the W3C has a draft of the XMLHttpRequest object that would enable this functionality.[20] Methods exist to sidestep this security feature by using a special Cross Domain Communications channel embedded as an iframe within a page,[21] or by the use of JSONP.
* The asynchronous callback-style of programming required can lead to complex code that is hard to maintain, to debug[22] and to test.
* Because of the asynchronous nature of Ajax, each chunk of data that is sent or received by the client occurs in a connection established specifically for that event. This creates a requirement that for every action, the client must poll the server, instead of listening, which incurs significant overhead. This overhead leads to several times higher latency with Ajax than what can be achieved with a technology such as websockets.[24]
* In pre-HTML5 browsers, pages dynamically created using successive Ajax requests did not automatically register themselves with the browser's history engine, so clicking the browser's "back" button may not have returned the browser to an earlier state of the Ajax-enabled page, but may have instead returned to the last full page visited before it. Such behavior — navigating between pages instead of navigating between page states — may be desirable, but if fine-grained tracking of page state is required, then a pre-HTML5 workaround was to use invisible iframes to trigger changes in the browser's history. A workaround implemented by Ajax techniques is to change the URL fragment identifier (the part of a URL after the "#") when an Ajax-enabled page is accessed and monitor it for changes.[25][26] HTML5 provides an extensive API standard for working with the browser's history engine.[27]
* Dynamic Web page updates also make it difficult to bookmark and return to a particular state of the application. Solutions to this problem exist, many of which again use the URL fragment identifier.[25][26] On the other hand, as AJAX-intensive pages tend to function as applications rather than content, bookmarking interim states rarely makes sense. Nevertheless, the solution provided by HTML5 for the above problem also applies for this.[27]
* Depending on the nature of the Ajax application, dynamic page updates may disrupt user interactions, particularly if the Internet connection is slow or unreliable. For example, editing a search field may trigger a query to the server for search completions, but the user may not know that a search completion popup is forthcoming, and if the Internet connection is slow, the popup list may show up at an inconvenient time, when the user has already proceeded to do something else.
* Excluding Google,[28] most major Web crawlers do not execute JavaScript code,[29] so in order to be indexed by Web search engines, a Web application must provide an alternative means of accessing the content that would normally be retrieved with Ajax. It has been suggested that a headless browser may be used to index content provided by Ajax-enabled websites, although Google is no longer recommending the Ajax crawling proposal they made in 2009.[30]
