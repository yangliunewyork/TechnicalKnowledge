#### The need for Callable

There are two ways of creating threads – one by extending the Thread class and other by creating a thread with a Runnable. However, one feature lacking in  Runnable is that we cannot make a thread return result when it terminates, i.e. when run() completes. For supporting this feature, the Callable interface is present in Java.


* For implementing Runnable, the run() method needs to be implemented which does not return anything, while for a Callable, the call() method needs to be implemented which returns a result on completion. Note that a thread can’t be created with a Callable, it can only be created with a Runnable.
* Another difference is that the call() method can throw an exception whereas run() cannot.  

Here is the code for an example Callable, which will return a random number after a delay of around 0 – 4 seconds.

```java
// Java program to illustrate Callable
// to return a random number
import java.util.Random;
import java.util.concurrent.Callable;
import java.util.concurrent.FutureTask;
 
class CallableExample implements Callable
{
 
    public Object call() throws Exception
    {
        // Create random number generator
        Random generator = new Random();
 
        Integer randomNumber = generator.nextInt(5);
 
        // To simulate a heavy computation,
        // we delay the thread for some random time
        Thread.sleep(randomNumber * 1000);
 
        return randomNumber;
    }
}
```

When the call() method completes, answer must be stored in an object known to the main thread, so that the main thread can know about the result that the thread returned. How will the program store and obtain this result later? For this, a Future object can be used. Think of a Future as an object that holds the result – it may not hold it right now, but it will do so in the future (once the Callable returns). Thus, a Future is basically one way the main thread can keep track of the progress and result from other threads. To implement this interface, 5 methods have to be overridden, but as the example below uses a concrete implementation from the library, only the important methods are listed here.

Observe that Callable and Future do two different things – Callable is similar to Runnable, in that it encapsulates a task that is meant to run on another thread, whereas a Future is used to store a result obtained from a different thread. In fact, the Future can be made to work with Runnable as well, which is something that will become clear when Executors come into the picture.


* public boolean cancel(boolean mayInterrupt): Used to stop the task. It stops the task if it has not started. If it has started, it interrupts the task only if mayInterrupt is true.
* public Object get() throws InterruptedException, ExecutionException: Used to get the result of the task. If the task is complete, it returns the result immediately, otherwise it waits till the task is complete and then returns the result.
* public boolean isDone(): Returns true if the task is complete and false otherwise

The Java library has the concrete type FutureTask, which implements Runnable and Future, combining both functionality conveniently.

A FutureTask can be created by providing its constructor with a Callable. Then the FutureTask object is provided to the constructor of Thread to create the Thread object. Thus, indirectly, the thread is created with a Callable. For further emphasis, note that there is no way to create the thread directly with a Callable.

Here is the code for the full example using Callable and FutureTask.

```java
// Java program to illustrate Callable and FutureTask
// for random number generation
import java.util.Random;
import java.util.concurrent.Callable;
import java.util.concurrent.FutureTask;
 
class CallableExample implements Callable
{
 
  public Object call() throws Exception
  {
    Random generator = new Random();
    Integer randomNumber = generator.nextInt(5);
 
    Thread.sleep(randomNumber * 1000);
 
    return randomNumber;
  }
 
}
 
public class CallableFutureTest
{
  public static void main(String[] args) throws Exception
  {
 
    // FutureTask is a concrete class that
    // implements both Runnable and Future
    FutureTask[] randomNumberTasks = new FutureTask[5];
 
    for (int i = 0; i < 5; i++)
    {
      Callable callable = new CallableExample();
 
      // Create the FutureTask with Callable
      randomNumberTasks[i] = new FutureTask(callable);
 
      // As it implements Runnable, create Thread
      // with FutureTask
      Thread t = new Thread(randomNumberTasks[i]);
      t.start();
    }
 
    for (int i = 0; i < 5; i++)
    {
      // As it implements Future, we can call get()
      System.out.println(randomNumberTasks[i].get());
 
      // This method blocks till the result is obtained
      // The get method can throw checked exceptions
      // like when it is interrupted. This is the reason
      // for adding the throws clause to main
    }
  }
}
```

Output:

```
4
2
3
3
0
```

All interaction with the thread after it starts is using the FutureTask object as it implements the Future interface. Hence, there is no need to store the Thread objects. Using the FutureTask object, one can cancel the task, check if it is complete or try to get the result.

Here is the code using only Runnable.

```java
// Java program to illustrate Runnable
// for random number generation
import java.util.Random;
import java.util.concurrent.Callable;
import java.util.concurrent.FutureTask;
 
class RunnableExample implements Runnable
{
    // Shared object to store result
    private Object result = null;
 
    public void run()
    {
        Random generator = new Random();
        Integer randomNumber = generator.nextInt(5);
 
        // As run cannot throw any Exception
        try
        {
            Thread.sleep(randomNumber * 1000);
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
 
        // Store the return value in result when done
        result = randomNumber;
 
        // Wake up threads blocked on the get() method
        synchronized(this)
        {
            notifyAll();
        }
    }
 
    public synchronized Object get()
          throws InterruptedException
    {
        while (result == null)
            wait();
 
        return result;
    }
}
 
// Code is almost same as the previous example with a
// few changes made to use Runnable instead of Callable
public class RunnableTest
{
    public static void main(String[] args) throws Exception
    {
        RunnableExample[] randomNumberTasks = new RunnableExample[5];
 
        for (int i = 0; i < 5; i++)
        {
            randomNumberTasks[i] = new RunnableExample();
            Thread t = new Thread(randomNumberTasks[i]);
            t.start();
        }
 
        for (int i = 0; i < 5; i++)
            System.out.println(randomNumberTasks[i].get());
    }
}
```

Sample Output

```
0
4
3
1
4
2
```
