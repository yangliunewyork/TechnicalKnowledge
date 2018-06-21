### What is server side rendering?

A single page app (commonly known as an SPA) is a client-side rendered app. It's an application that runs solely in your browser. If you're using a framework like React, Vue.js or AngularJS, the client renders your app from scratch.
Browsers have work to do

A browser needs to go through a few steps before a SPA is booted and ready for use.

* Download scripts
* Parse scripts
* Run scripts
* Retrieve data (optional, but common)
* Render the app in a previously empty container (first meaningful paint)
* Ready! (time to interactive)

The user doesn't see anything meaningful until the browser has fully rendered the app, which takes a while! This creates a noticeable delay until the first meaningful paint and takes away from the user experience.

This is where server side rendering (commonly known as SSR) comes in. SSR prerenders the initial application state on your server. Here's what the browser's to-do list looks like with server side rendering:


* Render incoming HTML from the server (first meaningful paint)
* Download scripts
* Parse scripts
* Run scripts
* Retrieve data
* Make the existing HTML interactive
* Ready! (time to interactive)

Since the server provides a prerendered chunk of HTML, the user doesn't need to wait until everything's complete to see something meaningful. Note that the time to interactive is still at the end of the line, but the perceived performance got a huge boost.

Server side rendering's main benefit is an improved user experience. SSR is also a must-have if you're dealing with older web crawlers that can't execute JavaScript. The crawlers will be able to index a rendered page from the server instead of a nearly empty document.

