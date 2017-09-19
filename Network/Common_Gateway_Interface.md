In computing, __Common Gateway Interface (CGI)__ offers a standard protocol for web servers to execute programs that execute like Console applications (also called Command-line interface programs) running on a server that *generates web pages dynamically*. Such programs are known as CGI scripts or simply as CGIs. The specifics of how the script is executed by the server are determined by the server. In the common case, a CGI script executes at the time a request is made and generates HTML.

# Purpose of the CGI standard

Each web server runs HTTP server software, which responds to requests from web browsers. Generally, the HTTP server has a directory (folder), which is designated as a document collection — files that can be sent to Web browsers connected to this server. For example, if the Web server has the domain name example.com, and its document collection is stored at /usr/local/apache/htdocs in the local file system, then the Web server will respond to a request for http://example.com/index.html by sending to the browser the (pre-written) file /usr/local/apache/htdocs/index.html.

For pages constructed on the fly, the server software may defer requests to separate programs and relay the results to the requesting client (usually, a web browser that displays the page to the end user). In the early days of the web, such programs were usually small and written in a scripting language; hence, they were known as scripts.

Such programs usually require some additional information to be specified with the request. For instance, if Wikipedia were implemented as a script, one thing the script would need to know is whether the user is logged in and, if logged in, under which name. The content at the top of a Wikipedia page depends on this information.

HTTP provides ways for browsers to pass such information to the web server, e.g. as part of the URL. The server software must then pass this information through to the script somehow.

Conversely, upon returning, the script must provide all the information required by HTTP for a response to the request: the HTTP status of the request, the document content (if available), the document type (e.g. HTML, PDF, or plain text), etcetera.

Initially, different server software would use different ways to exchange this information with scripts. As a result, it wasn't possible to write scripts that would work unmodified for different server software, even though the information being exchanged was the same. Therefore, it was decided to establish a standard way for exchanging this information: CGI (the Common Gateway Interface, as it defines a common way for server software to interface with scripts). Webpage generating programs invoked by server software that operate according to the CGI standard are known as CGI scripts.

This standard was quickly adopted and is still supported by all well-known server software, such as Apache, IIS, Nginx, and (with an extension) node.js-based servers.

An early use of CGI scripts was to process forms. In the beginning of HTML, HTML forms typically had an "action" attribute and a button designated as the "submit" button. When the submit button is pushed the URI specified in the "action" attribute would be sent to the server with the data from the form sent as a query string. If the "action" specifies a CGI script then the CGI script would be executed and it then produces a HTML page.

# Deployment

A Web server that supports CGI can be configured to interpret a URL that it serves as a reference to a CGI script. A common convention is to have a cgi-bin/ directory at the base of the directory tree and treat all executable files within this directory (and no other, for security) as CGI scripts. Another popular convention is to use filename extensions; for instance, if CGI scripts are consistently given the extension .cgi, the web server can be configured to interpret all such files as CGI scripts. While convenient, and required by many prepackaged scripts, it opens the server to attack if a remote user can upload executable code with the proper extension.

In the case of HTTP PUT or POSTs, the user-submitted data are provided to the program via the standard input. The Web server creates a subset of the environment variables passed to it and adds details pertinent to the HTTP environment.

# Uses

CGI is often used to process inputs information from the user and produce the appropriate output. An example of a CGI program is one implementing a Wiki. The user agent requests the name of an entry; the Web server executes the CGI; the CGI program retrieves the source of that entry's page (if one exists), transforms it into HTML, and prints the result. The web server receives the input from the CGI and transmits it to the user agent. If the "Edit this page" link is clicked, the CGI populates an HTML textarea or other editing control with the page's contents, and saves it back to the server when the user submits the form in it.

















