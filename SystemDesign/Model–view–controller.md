
<img src="http://www.patricksoftwareblog.com/wp-content/uploads/2015/07/Model-View-Controller-High-Level-Diagram.png" height="500" width="800">

Model–view–controller (MVC) is an architectural pattern commonly used for developing user interfaces that divides an application into three interconnected parts. This is done to separate internal representations of information from the ways information is presented to and accepted from the user. The MVC design pattern decouples these major components allowing for efficient code reuse and parallel development.

Traditionally used for desktop graphical user interfaces (GUIs), this architecture has become popular for designing web applications and even mobile, desktop and other clients. Popular programming languages like Java, C#, Ruby, PHP and others have popular MVC frameworks that are currently being used in web application development straight out of the box.

# Descriptions

As with other software patterns, MVC expresses the "core of the solution" to a problem while allowing it to be adapted for each system.[4] Particular MVC architectures can vary significantly from the traditional description here.[5]

### Components

* The _model_ is the central component of the pattern. It expresses the application's behavior in terms of the problem domain, independent of the user interface. It directly manages the data, logic and rules of the application.
* A _view_ can be any output representation of information, such as a chart or a diagram. Multiple views of the same information are possible, such as a bar chart for management and a tabular view for accountants.
* The third part or section, the _controller_, accepts input and converts it to commands for the model or view.

### Interactions

In addition to dividing the application into three kinds of components, the model–view–controller design defines the interactions between them.

* The model is responsible for managing the data of the application. It receives user input from the controller.
* The view means presentation of the model in a particular format.
* The controller is responsible for responding to the user input and perform interactions on the data model objects. The controller receives the input, optionally validates the input and then passes the input to the model.


### Use in web applications

Although originally developed for desktop computing, MVC has been widely adopted as an architecture for World Wide Web applications in major programming languages. Several web frameworks have been created that enforce the pattern. These software frameworks vary in their interpretations, mainly in the way that the MVC responsibilities are divided between the client and server.

Some web MVC frameworks take a thin client approach that places almost the entire model, view and controller logic on the server. This is reflected in frameworks such as Django, Rails and ASP.NET MVC. In this approach, the client sends either hyperlink requests or form submissions to the controller and then receives a complete and updated web page (or other document) from the view; the model exists entirely on the server. Other frameworks such as AngularJS, EmberJS, JavaScriptMVC and Backbone allow the MVC components to execute partly on the client (also see Ajax).


