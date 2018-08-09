# Creating Futures

Simply put, the Future class represents a future result of an asynchronous computation – a result that will eventually appear in the Future after the processing is complete.

Let’s see how to write methods that create and return a Future instance.

Long running methods are good candidates for asynchronous processing and the Future interface. This enables us to execute some other process while we are waiting for the task encapsulated in Future to complete.

Some examples of operations that would leverage the async nature of Future are:

* computational intensive processes (mathematical and scientific calculations)
* manipulating large data structures (big data)
* remote method calls (downloading files, HTML scrapping, web services).

## Implementing Futures with FutureTask

For our example, we are going to create a very simple class that calculates the square of an Integer. This definitely doesn’t fit the “long-running” methods category, but we are going to put a Thread.sleep() call to it to make it last 1 second to complete:

```java	
public class SquareCalculator {    
     
    private ExecutorService executor 
      = Executors.newSingleThreadExecutor();
     
    public Future<Integer> calculate(Integer input) {        
        return executor.submit(() -> {
            Thread.sleep(1000);
            return input * input;
        });
    }
}
```

The bit of code that actually performs the calculation is contained within the call() method, supplied as a lambda expression. As you can see there’s nothing special about it, except for the sleep() call mentioned earlier.

It gets more interesting when we direct our attention to the usage of Callable and ExecutorService.

Callable is an interface representing a task that returns a result and has a single call() method. Here, we’ve created an instance of it using a lambda expression.

Creating an instance of Callable does not take us anywhere, we still have to pass this instance to an executor that will take care of starting that task in a new thread and give us back the valuable Future object. That’s where ExecutorService comes in.

There are a few ways we can get ahold of an ExecutorService instance, most of them are provided by utility class Executors‘ static factory methods. In this example, we’ve used the basic newSingleThreadExecutor(), which gives us an ExecutorService capable of handling a single thread at a time.

Once we have an ExecutorService object, we just need to call submit() passing our Callable as an argument. submit() will take care of starting the task and return a FutureTask object, which is an implementation of the Future interface.

# Consuming Futures

Up to this point, we’ve learned how to create an instance of Future. In this section, we’ll learn how to work with this instance by exploring all methods that are part of

In this section, we’ll learn how to work with this instance by exploring all methods that are part of Future‘s API.

##  Using isDone() and get() to Obtain Results

Now we need to call calculate() and use the returned Future to get the resulting Integer. Two methods from the Future API will help us with this task.

Future.isDone() tells us if the executor has finished processing the task. If the task is completed, it will return true otherwise, it returns false.

The method that returns the actual result from the calculation is Future.get(). Notice that this method blocks the execution until the task is complete, but in our example, this won’t be an issue since we’ll check first if the task is completed by calling isDone().

By using these two methods we can run some other code while we wait for the main task to finish:

```java
Future<Integer> future = new SquareCalculator().calculate(10);
 
while(!future.isDone()) {
    System.out.println("Calculating...");
    Thread.sleep(300);
}
 
Integer result = future.get();
```

In this example, we write a simple message on the output to let the user know the program is performing the calculation.

The method get() will block the execution until the task is complete. But we don’t have to worry about that since our example only get to the point where get() is called after making sure that the task is finished. So, in this scenario, future.get() will always return immediately.

It is worth mentioning that get() has an overloaded version that takes a timeout and a TimeUnit as arguments:

```
Integer result = future.get(500, TimeUnit.MILLISECONDS);
```

The difference between get(long, TimeUnit) and get(), is that the former will throw a TimeoutException if the task doesn’t return before the specified timeout period.

## Canceling a Future with cancel()

Suppose we’ve triggered a task but, for some reason, we don’t care about the result anymore. We can use Future.cancel(boolean) to tell the executor to stop the operation and interrupt its underlying thread:

```java	
Future<Integer> future = new SquareCalculator().calculate(4);
 
boolean canceled = future.cancel(true);
```

Our instance of Future from the code above would never complete its operation. In fact, if we try to call get() from that instance, after the call to cancel(), the outcome would be a CancellationException. Future.isCancelled() will tell us if a Future was already canceled. This can be quite useful to avoid getting a CancellationException.

It is possible that a call to cancel() fails. In that case, its returned value will be false. Notice that cancel() takes a boolean value as an argument – this controls whether the thread executing this task should be interrupted or not.

# More Multithreading with Thread Pools

Our current ExecutorService is single threaded since it was obtained with the Executors.newSingleThreadExecutor. To highlight this “single threadness”, let’s trigger two calculations simultaneously:

```java
SquareCalculator squareCalculator = new SquareCalculator();
 
Future<Integer> future1 = squareCalculator.calculate(10);
Future<Integer> future2 = squareCalculator.calculate(100);
 
while (!(future1.isDone() && future2.isDone())) {
    System.out.println(
      String.format(
        "future1 is %s and future2 is %s", 
        future1.isDone() ? "done" : "not done", 
        future2.isDone() ? "done" : "not done"
      )
    );
    Thread.sleep(300);
}
 
Integer result1 = future1.get();
Integer result2 = future2.get();
 
System.out.println(result1 + " and " + result2);
 
squareCalculator.shutdown();
```

Now let’s analyze the output for this code:

```java
calculating square for: 10
future1 is not done and future2 is not done
future1 is not done and future2 is not done
future1 is not done and future2 is not done
future1 is not done and future2 is not done
calculating square for: 100
future1 is done and future2 is not done
future1 is done and future2 is not done
future1 is done and future2 is not done
100 and 10000
```

It is clear that the process is not parallel. Notice how the second task only starts once the first task is completed, making the whole process take around 2 seconds to finish.

To make our program really multi-threaded we should use a different flavor of ExecutorService. Let’s see how the behavior of our example changes if we use a thread pool, provided by the factory method Executors.newFixedThreadPool():

```java
public class SquareCalculator {
  
    private ExecutorService executor = Executors.newFixedThreadPool(2);
     
    //...
}
```

With a simple change in our SquareCalculator class now we have an executor which is able to use 2 simultaneous threads.

If we run the exact same client code again, we’ll get the following output:

```
calculating square for: 10
calculating square for: 100
future1 is not done and future2 is not done
future1 is not done and future2 is not done
future1 is not done and future2 is not done
future1 is not done and future2 is not done
100 and 10000
```

This is looking much better now. Notice how the 2 tasks start and finish running simultaneously, and the whole process takes around 1 second to complete.

There are other factory methods that can be used to create thread pools, like Executors.newCachedThreadPool() that reuses previously used Threads when they are available, and Executors.newScheduledThreadPool() which schedules commands to run after a given delay. 

