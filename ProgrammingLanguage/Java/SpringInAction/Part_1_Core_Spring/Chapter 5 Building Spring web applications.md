## 5.1 Getting started with Spring MVC

Spring moves requests between a dispatcher servlet, handler mappings, controllers, and view resolvers.Each of the components in Spring MVC performs
a specific purpose.

### 5.1.1 Following the life of a request

Every time a user clicks a link or submits a form in their web browser, a request goes to work. A request’s job description is that of a courier. Just like a postal carrier or a FedEx delivery person, a request lives to carry information from one place to another. The request is a busy creature. From the time it leaves the browser until it returns with a response, it makes several stops, each time dropping off a bit of information and picking up some more.

When the request leaves the browser B, it carries information about what the user is asking for. At the least, the request will be carrying the requested URL. But it may also carry additional data, such as the information submitted in a form by the user.

![alt](http://apprize.info/javascript/spring_1/spring_1.files/image065.jpg)

The first stop in the request travels is at Spring's DispatcherServlet. Like most Javabased web frameworks, Spring MVC funnels requests through a single front controller servlet. A front controller is a common web application pattern where a single servlet delegates responsibility for a request to other components of an application to perform actual processing. In the case of Spring MVC, DispatcherServlet is the front controller.

The DispatcherServlet’s job is to send the request on to a Spring MVC controller. A controller is a Spring component that processes the request. But a typical application may have several controllers, and DispatcherServlet needs some help deciding which controller to send the request to. So the DispatcherServlet consults one or more handler mappings C to figure out where the request’s next stop will be. The handler mapping pays particular attention to the URL carried by the request when making its decision.

Once an appropriate controller has been chosen, DispatcherServlet sends the request on its merry way to the chosen controller D. At the controller, the request drops off its payload (the information submitted by the user) and patiently waits while the controller processes that information. (Actually, a well-designed controller performs little or no processing itself and instead delegates responsibility for the business logic to one or more service objects.)

The logic performed by a controller often results in some information that needs to be carried back to the user and displayed in the browser. This information is referred to as the model. But sending raw information back to the user isn’t sufficient— it needs to be formatted in a user-friendly format, typically HTML. For that, the information needs to be given to a view, typically a __JavaServer Page (JSP)__.

One of the last things a controller does is package up the model data and identify the name of a view that should render the output. It then sends the request, along with the model and view name, back to the DispatcherServlet.

So that the controller doesn’t get coupled to a particular view, the view name passed back to DispatcherServlet doesn’t directly identify a specific JSP. It doesn’t even necessarily suggest that the view is a JSP. Instead, it only carries a logical name that will be used to look up the actual view that will produce the result. The DispatcherServlet consults a view resolver F to map the logical view name to a specific view implementation, which may or may not be a JSP.

Now that DispatcherServlet knows which view will render the result, the request’s job is almost over. Its final stop is at the view implementation G, typically a JSP, where it delivers the model data. The request’s job is finally done. The view will use the model data to render output that will be carried back to the client by the (notso- hardworking) response object.

As you can see, a request goes through several steps along its way to producing a response for the client. Most of these steps take place within the Spring MVC framework.

### 5.1.2 Setting up Spring MVC
