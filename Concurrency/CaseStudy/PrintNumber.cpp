/***
There are 2 threads . How you will synchronize in linux so that 1 thread prints even numbers and other thread prints odd numbers 
hint: condition variable
***/

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>

bool RUN(true);
std::size_t number(0);
std::mutex my_mutex;
std::condition_variable cond;

void PrintEven() {
  while (RUN) {
    std::unique_lock<std::mutex> lock(my_mutex);
    cond.wait(lock, []() {return number % 2 == 0;});
    std::cout << "PrintEven : " << number++ << std::endl;
    cond.notify_one();
  }
}

void PrintOdd() {
  while (RUN) {
    std::unique_lock<std::mutex> lock(my_mutex);
    cond.wait(lock, []() {return number % 2 == 1;});
    std::cout << "PrintOdd : " << number++ << std::endl;
    cond.notify_one();
  }
}

void Timer() {
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  RUN = false;
}

int main() {
  std::thread t1(PrintEven), t2(PrintOdd), t3(Timer);
  t1.join();
  t2.join();
  t3.join();
  
  
  return 0;
}
