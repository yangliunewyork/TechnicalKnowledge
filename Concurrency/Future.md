## C++ STL future
Suppose you're going on holiday abroad by plane. Once you've got to the airport and cleared the various check-in procedures, you've still got to wait for the notification that your flight is ready for boarding, possibly for several hours. Yes, you might be able to find some means of passing the time, such as reading a book, surfing the internet, or eating in an overpriced airport café, but fundamentally you're just waiting for one thing: the signal that it's time to get on the plane. Not only that, but a given flight only goes once: next time you're going on holiday, you'll be waiting for a different flight.

The C++ Standard Library models this sort of one-off event with something called a future. If a thread needs to wait for a specific one-off event, then it somehow obtains a future representing this event. The thread can then poll the future to see if the event has occurred (check the departures board), whilst performing some other task (eating in the overpriced café), or it can just wait for the event to happen. A future may have data associated with it (such as which gate your flight is boarding at), or it may not. Once an event has happened (and the future has become ready), then the future cannot be reset.

There are two sorts of futures in the C++ Standard Library, implemented as two class templates: __unique futures (std::unique_future<>)__, and __shared futures (std::shared_future<>)__. These are modelled after std::unique_ptr and std::shared_ptr: an instance of std::unique_future is the one and only instance that refers to its associated event, whereas multiple instances of std::shared_future may refer to the same event. In the latter case, all the instances will of course become ready at the same time, and they may all access any data associated with the event. This associated data is the reason these are templates: just like std::unique_ptr and std::shared_ptr, the template parameter is the type of the associated data. The std:unique_future<void> and std::shared_future<void> template specializations should be used where there is no associated data.

```
void process_remote_file(
        std::string const& filename)
    {
        std::unique_future<
            file_contents> contents=
            server.download_file_in_background(   #1
                filename);
        while(!contents.is_ready())               #2
        {
            process_gui_events();                 #3
        }
        file_contents file_data(contents.get());  #4
        process_file(file_data);                  #5
    }
```

In this case, the future holds the response from a request to download a (potentially large) file in a background thread (#1). The use of the future allows this thread to continue processing GUI messages in the mean time (#3). Once the future is ready (#2), the file data can be extracted from the future (#4) and then processed (#5). Because this is a subsidiary task, we know there's only the one thread waiting, so std::unique_future is appropriate. unique_future<>::get() returns an rvalue, so we can also avoid copying the data when we extract it from the future if file_contents has a move constructor.


So, that's futures from the point of view of the waiting thread, but what about the thread that triggers the event? How do we make a future ready? How do we store the associated data? The C++ Standard Library provides the answers to these questions in the form of two function templates: std::packaged_task<> and std::promise<>.

### Packaged Tasks
std::packaged_task<> ties a future to the result of a function call: when the function completes, the future is ready, and the associated data is the value returned by the function. This is ideal for overall operations that can be subdivided into a set of self-contained tasks: these tasks can be written as functions, packaged up so each task is associated with a future using std::packaged_task, and then executed on separate threads. The driving function can then wait for the futures before processing the results of these subtasks.

### Promises
std::promise<> is a slightly lower-level tool that provides explicit functions for setting the data associated with a future, and making the future ready. This is good for the case where the data may come from multiple sources: in a parallel search algorithm, for example, the search space may be divided between threads, but only one result is required. A std::unique_future/std::promise pair can be used to manage the return value, and the first thread to find a match can set the future value through the std::promise instance, and instruct the other threads to stop searching.
