Java is a multi-threaded programming language which means we can develop multi-threaded program using Java. A multi-threaded program contains two or more parts that can run concurrently and each part can handle a different task at the same time making optimal use of the available resources specially when your computer has multiple CPUs. Multi-threading enables you to write in a way where multiple activities can proceed concurrently in the same program.

# Java Concurrency - Overview

Java is a multi-threaded programming language which means we can develop multi-threaded program using Java. A multi-threaded program contains two or more parts that can run concurrently and each part can handle a different task at the same time making optimal use of the available resources specially when your computer has multiple CPUs.

By definition, multitasking is when multiple processes share common processing resources such as a CPU. Multi-threading extends the idea of multitasking into applications where you can subdivide specific operations within a single application into individual threads. Each of the threads can run in parallel. The OS divides processing time not only among different applications, but also among each thread within an application.

Multi-threading enables you to write in a way where multiple activities can proceed concurrently in the same program.

### Life Cycle of a Thread

![alt](https://www.tutorialspoint.com/java/images/Thread_Life_Cycle.jpg)

A thread goes through various stages in its life cycle. For example, a thread is born, started, runs, and then dies. The following diagram shows the complete life cycle of a thread.

Following are the stages of the life cycle :

* New − A new thread begins its life cycle in the new state. It remains in this state until the program starts the thread. It is also referred to as a born thread.

* Runnable − After a newly born thread is started, the thread becomes runnable. A thread in this state is considered to be executing its task.

* Waiting − Sometimes, a thread transitions to the waiting state while the thread waits for another thread to perform a task. A thread transitions back to the runnable state only when another thread signals the waiting thread to continue executing.

* Timed Waiting − A runnable thread can enter the timed waiting state for a specified interval of time. A thread in this state transitions back to the runnable state when that time interval expires or when the event it is waiting for occurs.

* Terminated (Dead) − A runnable thread enters the terminated state when it completes its task or otherwise terminates.

#### Thread Priorities

Every Java thread has a priority that helps the operating system determine the order in which threads are scheduled.

Java thread priorities are in the range between MIN_PRIORITY (a constant of 1) and MAX_PRIORITY (a constant of 10). By default, every thread is given priority NORM_PRIORITY (a constant of 5).

Threads with higher priority are more important to a program and should be allocated processor time before lower-priority threads. However, thread priorities cannot guarantee the order in which threads execute and are very much platform dependent.

### Create a Thread by Implementing a Runnable Interface

If your class is intended to be executed as a thread then you can achieve this by implementing a Runnable interface. You will need to follow three basic step:

##### Step 1

As a first step, you need to implement a run() method provided by a Runnable interface. This method provides an entry point for the thread and you will put your complete business logic inside this method. Following is a simple syntax of the run() method.

```
public void run( )
```

##### Step 2

As a second step, you will instantiate a Thread object using the following constructor

```
Thread(Runnable threadObj, String threadName);
```

Where, threadObj is an instance of a class that implements the Runnable interface and threadName is the name given to the new thread.

##### Step 3

Once a Thread object is created, you can start it by calling start() method, which executes a call to run( ) method. Following is a simple syntax of start() method:

```
void start();
```

### Create a Thread by Extending a Thread Class

The second way to create a thread is to create a new class that extends Thread class using the following two simple steps. This approach provides more flexibility in handling multiple threads created using available methods in Thread class.

##### Step 1

You will need to override run( ) method available in Thread class. This method provides an entry point for the thread and you will put your complete business logic inside this method. Following is a simple syntax of run() method:

```
public void run( )
```

##### Step 2

Once Thread object is created, you can start it by calling start() method, which executes a call to run( ) method. Following is a simple syntax of start() method :

```
void start( );
```

### Java Concurrency - Major Operations

Core Java provides complete control over multithreaded program. You can develop a multithreaded program which can be suspended, resumed, or stopped completely based on your requirements. There are various static methods which you can use on thread objects to control their behavior. Following table lists down those methods:

```
public void wait() : Causes the current thread to wait until another thread invokes the notify().
public void notify() : Wakes up a single thread that is waiting on this object's monitor.

// Being deprecated!
public void suspend() : This method puts a thread in the suspended state and can be resumed using resume() method.
public void stop() : This method stops a thread completely.
public void resume() : This method resumes a thread, which was suspended using suspend() method.
```

Be aware that the latest versions of Java has deprecated the usage of suspend( ), resume( ), and stop( ) methods and so you need to use available alternatives.

### Interthread Communication

If you are aware of interprocess communication then it will be easy for you to understand interthread communication. Interthread communication is important when you develop an application where two or more threads exchange some information.

There are three simple methods and a little trick which makes thread communication possible. All the three methods are listed below:

```
public void wait() : Causes the current thread to wait until another thread invokes the notify().
public void notify() : Wakes up a single thread that is waiting on this object's monitor.
public void notifyAll() : Wakes up all the threads that called wait( ) on the same object.
```

These methods have been implemented as final methods in Object, so they are available in all the classes. All three methods can be called only from within a __synchronized__ context.

```java
class Chat {
   boolean askedNewQuestion = false;

   public synchronized void Question(String msg) {

      if (askedNewQuestion) {
         
         try {
            wait();
         } catch (InterruptedException e) {
            e.printStackTrace();
         }
      }
      System.out.println(msg);
      askedNewQuestion = true;
      notify();
   }

   public synchronized void Answer(String msg) {

      if (!askedNewQuestion) {
         
         try {
            wait();
         } catch (InterruptedException e) {
            e.printStackTrace();
         }
      }
      System.out.println(msg);
      askedNewQuestion = false;
      notify();
   }
}

class T1 implements Runnable {
   Chat m;
   String[] s1 = { "Hi", "How are you ?", "I am also doing fine!" };

   public T1(Chat m1) {
      this.m = m1;
      new Thread(this, "Question").start();
   }

   public void run() {
   
      for (int i = 0; i < s1.length; i++) {
         m.Question(s1[i]);
      }
   }
}

class T2 implements Runnable {
   Chat m;
   String[] s2 = { "Hi", "I am good, what about you?", "Great!" };

   public T2(Chat m2) {
      this.m = m2;
      new Thread(this, "Answer").start();
   }

   public void run() {

      for (int i = 0; i < s2.length; i++) {
         m.Answer(s2[i]);
      }
   }
}

public class TestThread {

   public static void main(String[] args) {
      Chat m = new Chat();
      new T1(m);
      new T2(m);
   }
}
```

Output

```
Hi
Hi
How are you ?
I am good, what about you?
I am also doing fine!
Great!
```


### Java Concurrency - Deadlock

Deadlock describes a situation where two or more threads are blocked forever, waiting for each other. Deadlock occurs when multiple threads need the same locks but obtain them in different order. A Java multithreaded program may suffer from the deadlock condition because the __synchronized__ keyword causes the executing thread to block while waiting for the lock, or monitor, associated with the specified object. 

##### Synchronization vs Lock

If you're simply locking an object, I'd prefer to use synchronized

Example:

```
Lock.acquire();
doSomethingNifty(); // Throws a NPE!
Lock.release(); // Oh noes, we never release the lock!
```

You have to explicitly do try{} finally{} everywhere.

Whereas with synchronized, it's super clear and impossible to get wrong:

```
synchronized(myObject) {
    doSomethingNifty();
}
```

That said, Locks may be more useful for more complicated things where you can't acquire and release in such a clean manner. I would honestly prefer to avoid using bare Locks in the first place, and just go with a more sophisticated concurrency control such as a CyclicBarrier or a LinkedBlockingQueue, if they meet your needs.



