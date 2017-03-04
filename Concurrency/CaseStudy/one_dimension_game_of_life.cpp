#include <vector>
#include <iostream>
#include <sstream>
#include <cassert>
#include <thread>

void OneDimensionGameOfLife(std::vector<int> & board, std::size_t begin, std::size_t end) {
  const std::size_t size(board.size());

  for (std::size_t i = begin; i <= end; ++i) {
    std::size_t left = (i + size - 1) % size;
    std::size_t right = (i + size + 1) % size;

    int live = (board[left] & 1) + (board[right] & 1);
    if (live != 1) { // no change
      board[i] += ( (board[i]&1) << 1 ) ;
    } else { // change
      if ( (board[i]&1) == 0) board[i] |= 2;
    }
  }

}


void UnitTest() {

  std::vector<int> board;
  for (int i = 0; i< 100; ++i) {
    board.push_back(rand() % 2);
  }

  std::ostringstream oss;
  for (int num : board) {
    oss <<num;
  }
  std::cout << oss.str() << std::endl;

  std::vector<std::thread> threads;
  std::size_t begin(0), interval(25);
  for (int i = 0; i < 4 ; ++i) {
    threads.push_back(std::thread(OneDimensionGameOfLife, std::ref(board), begin, begin+interval-1) );
    begin += interval;
  }

  for (std::thread & t : threads) {
    t.join();
  }


  for (int & val : board) {
    val >>= 1 ;
  }

  oss.str("");
  for (int num : board) {
    oss <<num;
  }
  std::cout << oss.str() << std::endl;
}


int main() {
  UnitTest();
  return 0;
}
