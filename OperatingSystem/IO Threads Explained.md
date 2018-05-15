https://enterprisecraftsmanship.com/2014/12/13/io-threads-explained/

#### The difference between asynchronous programming and parallel programming

So, is there any difference between these two notions? Yes, there is. You can think of parallel programming as a subset of asynchronous programming: every parallel execution is asynchronous, but not every asynchronous execution is parallel.

Let’s take an example.

* When someone calls you, you usually pick up your phone and answer immediately, leaving your current tasks. It is a synchronous communication.
* When someone sends you an email, you can postpone the answer, say, to evening, and continue working on your current tasks. It is an asynchronous communication.
* When someone calls you, you can answer while working on your current tasks at the same time. It’s a parallel communication.

Returning to programming, the difference between synchronous and asynchronous execution is that in case of synchronous execution, the thread leaves its current task and starts working on a new task immediately. On the other hand, with asynchronous execution the thread continues working on its current task.

The difference between asynchronous and parallel execution is that with asynchronous execution you don’t always need another thread to execute a new task. The new task can be executed after the thread is done with its current task. Until that moment, this new task waits in a queue.

### What are I/O threads?

To use asynchronous and parallel features of the .NET properly, you should also understand the concept of I/O threads.

Not everything in a program consumes CPU time. When a thread tries to read data from a file on disk or sends a TCP/IP packet through network, the only thing it does is delegate the actual work to a device – disk or network adapter – and wait for results.

It’s very expensive to spend threads’ time on waiting. Even through threads sleep and don’t consume CPU time while waiting for the results, it doesn’t really pay off because it’s a waste of system resources. Every thread holds about 2Mb of memory for stack variables, local storage and so on. Also, the more threads you have, the more time it takes to switch among them.

It’s much more efficient for threads to send a command to device and ask to ping them back after the work is done. Threads shouldn’t spend their time on sleeping.

Think about the analogy. Let’s say there’s a cook making a dinner for a lot of people. He or she certainly has a gas-stove or a toaster or a human assistant. The cook’s time costs more than toaster’s, stove’s or even assistant’s time, so it would be better if the cook doesn’t waste their time on sitting and waiting for a toast to be made. Or for the assistant to return from a store. It’d be more efficient for them to put the cake in the oven and return back after the bell, cooking other stuff meanwhile. A single cook can be very productive in such a way.

I/O thread is an abstraction intended to hide work with devices behind a simple and familiar concept. The main point here is that you don’t have to work with those devices in a different way, you can think of the pipeline inside them just like it’s a usual CPU consuming thread. At the same time, I/O threads are extremely cheap in comparison with CPU-bound threads, because, in fact, they are merely requests to devices.

So, let’s summarize. When a program reads data from a file, we say it starts a new I/O thread, meaning that it actually sends a command to a hard drive. When the drive finishes reading, we say I/O thread is completed, meaning that the drive sends the data back to the program.

Let’s look at the code:

```C#
public void ReadData(string filePath, int byteCount)

{

    byte[] buffer = new byte[byteCount];

    using (FileStream fs = new FileStream(filePath, FileMode.Open))

    {

        fs.Read(buffer, 0, byteCount); // 1

    }

}
```

I/O thread is started at the line marked as “1”. The main thread falls to sleep and waits for the I/O thread to complete. After it’s done, it sends the data back to the main thread. Then the main thread wakes up and continues working.

#### How the device handle the request. isn't the device needs any resource process etc?

It has its own resources. You can think of each device as of separate sub-system that doesn't depend on each other. That's also true for CPU: it doesn't need to know about network adapter, nor should it interact with it anyhow.

Therefore, when dispatching work to some device, for instance, to the network adapter, it doesn't interfere with CPU so the latter can do some other work in the meanwhile.

