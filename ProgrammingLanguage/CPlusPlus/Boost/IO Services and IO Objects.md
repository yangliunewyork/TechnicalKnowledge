https://theboostcpplibraries.com/boost.asio-io-services-and-io-objects

Programs that use Boost.Asio for asynchronous data processing are based on I/O services and I/O objects. I/O services abstract the operating system interfaces that process data asynchronously. I/O objects initiate asynchronous operations. These two concepts are required to separate tasks cleanly: I/O services look towards the operating system API, and I/O objects look towards tasks developers need to do.

As a user of Boost.Asio you normally don’t connect with I/O services directly. I/O services are managed by an I/O service object. An I/O service object is like a registry where I/O services are listed. Every I/O object knows its I/O service and gets access to its I/O service through the I/O service object.

Boost.Asio defines boost::asio::io_service, a single class for an I/O service object. Every program based on Boost.Asio uses an object of type boost::asio::io_service. This can also be a global variable.

While there is only one class for an I/O service object, several classes for I/O objects exist. Because I/O objects are task oriented, the class that needs to be instantiated depends on the task. For example, if data has to be sent or received over a TCP/IP connection, an I/O object of type boost::asio::ip::tcp::socket can be used. If data has to be transmitted asynchronously over a serial port, boost::asio::serial_port can be instantiated. If you want to wait for a time period to expire, you can use the I/O object boost::asio::steady_timer.

boost::asio::steady_timer is like an alarm clock. Instead of waiting for a blocking function to return when the alarm clock rings, your program will be notified. Because boost::asio::steady_timer just waits for a time period to expire, it would seem as though no external resource is accessed. However, in this case the external resource is the capability of the operating system to notify a program when a time period expires. This frees a program from creating a new thread just to call a blocking function. Since boost::asio::steady_timer is a very simple I/O object, it will be used to introduce Boost.Asio.

