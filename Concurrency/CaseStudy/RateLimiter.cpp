#include <ctime>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

class TokenBucket {
public:
  TokenBucket(std::size_t rate, std::size_t second)
    : m_tokens(rate), m_rate(rate), m_second(second), m_last_check(std::time(0)) {
  }

  bool GetToken() {

    std::time_t current = std::time(0);
    std::time_t elapsed_second = current - m_last_check;

    std::lock_guard<std::mutex> guard(m_mutex);

    m_tokens += elapsed_second * m_rate /  m_second;
    std::cout << "elapsed time = " << elapsed_second << ", token = " << m_tokens << std::endl;
    if (m_tokens > m_rate) {
      m_tokens = m_rate;
    }

    if (m_tokens < 1) {
      return false;
    } else {
      m_last_check = current;
      -- m_tokens;
      return true;
    }

  }

private:
  std::mutex m_mutex;
  std::size_t m_tokens;
  std::size_t m_rate;
  std::size_t m_second;
  std::time_t m_last_check;
};


void HitService(TokenBucket & token) {
  while (true) {
    std::cout << (token.GetToken() ? "Processed" : "Ignored" )<< std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

int main() {
  TokenBucket token_bucket(5,8);// permit one token every 5 seconds
  std::thread t1(HitService,std::ref(token_bucket));
  std::thread t2(HitService,std::ref(token_bucket));
  t1.join();
  t2.join();
  return 0;
}
