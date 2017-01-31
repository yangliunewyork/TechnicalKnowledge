#include <queue>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue {
public:
  explicit BlockingQueue() {

  }
  void Push(const T & item) {
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_queue.push(item);
    }
    m_condition_variable.notify_all();
  }

  void Pop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition_variable.wait(lock,[ & ](){ return !m_queue.empty(); });
    m_queue.pop();
  }

  T Front() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition_variable.wait(lock,[ & ](){ return !m_queue.empty(); });
    T reval = m_queue.front();
    return reval;
  }

  bool Empty() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
  }

private:
  std::mutex m_mutex;
  std::condition_variable m_condition_variable;
  std::queue<T> m_queue;
};


template<typename T>
void AddItemToBlockingQueue(BlockingQueue<T> & blocking_queue, std::size_t n,const std::string & thread_name) {
  for (std::size_t i=0; i<n; ++i) {
    int val = rand() % 1000;
    std::cout << "Thread " << thread_name << " pushed "<< val << " into blocking queue" << std::endl;
    blocking_queue.Push( val );
  }
  std::cout << "### Thread " << thread_name << "end" << std::endl;
}

template<typename T>
void PrintBlockingQueue(BlockingQueue<T> & blocking_queue){
  std::size_t i(0);
  while ( true ) {
    if ( !blocking_queue.Empty() ) {
      std::cout <<"Popping "<< (++i) << "th item from blocking queue " << blocking_queue.Front() << std::endl;
      blocking_queue.Pop();
    }
  }
}

void UnitTest() {
  BlockingQueue<int> blocking_queue;

  // In general, it is not a good idea to pass local variable to other threads unless
  // we are 100% sure that the lifetime of local object still exist during the lifetime of the threads.
  // Here we join all the threads here, so you know...
  std::thread t1(AddItemToBlockingQueue<int>,std::ref(blocking_queue),10,"Thread_"+std::to_string(1));
  std::thread t2(AddItemToBlockingQueue<int>,std::ref(blocking_queue),10,"Thread_"+std::to_string(2));
  std::thread t3(AddItemToBlockingQueue<int>,std::ref(blocking_queue),10,"Thread_"+std::to_string(3));

  std::thread print_thread(PrintBlockingQueue<int>,std::ref(blocking_queue));
  t1.join();
  t2.join();
  t3.join();
  print_thread.join();
  // Here blocking_queue get destroyed
}

int main() {
  UnitTest();
  return 0;
}
