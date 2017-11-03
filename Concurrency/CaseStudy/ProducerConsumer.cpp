#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <queue>
#include <condition_variable>

// This mutex is used to make sure only one thread can access the thread at anytime
std::mutex my_mutex;

std::queue<int> my_queue;
std::condition_variable cv;
bool finished(false);

// The producer thread will produce n items in total.
void producer(int n) {
  for (int i=0;i<n;++i) {
    // Using brackets to create the local scope so that lock_gard get unlocked
    // Otherwise, the waiting thread will only wake up and find that the mutex is still locked
    {
      std::lock_guard<std::mutex> lock(my_mutex);
      my_queue.push(i);
      std::cout << "pushing " << i << std::endl;
    }
    // Unblocks all threads currently waiting for this condition.
    // If no threads are waiting, the function does nothing.
    cv.notify_all();
  }

  // Finish pushing
  {
    std::lock_guard<std::mutex> lock(my_mutex);
    finished = true;
  }

  cv.notify_all();
}

void consumer() {
  while (true) {

    // lock_guard doesn't work with condition variable,
    // because condition_variable unlocks its mutex when
    // going to sleep upon calls to wait.
    std::unique_lock<std::mutex> lock(my_mutex);

    cv.wait(lock, []{ return !my_queue.empty() || finished; });

    while (!my_queue.empty()) {
      std::cout << "consuming " << my_queue.front() << std::endl;
      my_queue.pop();
    }

    if (finished) break;
  }
}

int main() {
  std::thread t1(producer, 100);
  std::thread t2(consumer);

  t2.join();
  t1.join();

  std::cout << "finished!" << std::endl;
  return 0;
}
