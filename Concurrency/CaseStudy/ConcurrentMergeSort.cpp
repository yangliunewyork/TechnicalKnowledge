#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <vector>
#include <climits> //INT_MAX

using namespace std::chrono;

namespace RegularMergeSort {

  void Merge(std::vector<int> & vec, std::size_t begin, std::size_t mid, std::size_t end) {

    std::vector<int> left(vec.begin()+begin, vec.begin()+mid+1);  // [begin,mid]
    std::vector<int> right(vec.begin() + mid + 1, vec.begin() + end +1); // [mid+1,end]

    std::size_t left_index(0), right_index(0);

    left.push_back(INT_MAX), right.push_back(INT_MAX); // Put sentinel item to both sub-array

    for (std::size_t i=begin;i<=end;++i) {
      if (left[left_index] < right[right_index]) {

        vec[i] = left[left_index++];
      } else {

        vec[i] = right[right_index++];
      }
    }
  }

  void MergeSort(std::vector<int> & vec, std::size_t begin, std::size_t end) {
    if (vec.empty() || begin >= end) return;
    std::size_t mid = begin + (end - begin) / 2 ;
    MergeSort(vec,begin,mid);
    MergeSort(vec,mid+1,end);
    Merge(vec,begin,mid,end);
  }
}

namespace ConcurrentMergeSort {

  void Merge(std::vector<int> & vec, std::size_t begin, std::size_t mid, std::size_t end) {

    std::vector<int> left(vec.begin()+begin, vec.begin()+mid+1);  // [begin,mid]
    std::vector<int> right(vec.begin() + mid + 1, vec.begin() + end +1); // [mid+1,end]

    std::size_t left_index(0), right_index(0);

    left.push_back(INT_MAX), right.push_back(INT_MAX); // Put sentinel item to both sub-array

    for (std::size_t i=begin;i<=end;++i) {
      if (left[left_index] < right[right_index]) {

        vec[i] = left[left_index++];
      } else {

        vec[i] = right[right_index++];
      }
    }
  }

  void MergeSort(std::vector<int> & vec, std::size_t begin, std::size_t end) {
    if (vec.empty() || begin >= end) return;
    std::size_t mid = begin + (end - begin) / 2 ;

    std::thread t1(MergeSort,std::ref(vec),begin,mid);
    std::thread t2(MergeSort,std::ref(vec),mid+1,end);
    t1.join();
    t2.join();
    //MergeSort(vec,begin,mid);
    //MergeSort(vec,mid+1,end);
    Merge(vec,begin,mid,end);
  }
}

void CallRegularMergeSort(std::vector<int> & vec) {
  high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  RegularMergeSort::MergeSort(vec,0,vec.size()-1);
  high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  auto duration = duration_cast<microseconds>( t2 - t1 ).count();
  std::cout << "Time cost for RegularMergeSort : " << duration << std::endl;
  for (int val : vec) {
    std::cout << val <<',';
  }
  std::cout << std::endl;

}


void CallConcurrentMergeSort(std::vector<int> & vec) {
  high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  ConcurrentMergeSort::MergeSort(vec,0,vec.size()-1);
  high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  auto duration = duration_cast<microseconds>( t2 - t1 ).count();
  std::cout << "Time cost for ConcurrentMergeSort : " << duration << std::endl;
  for (int val : vec) {
    std::cout << val <<',';
  }
  std::cout << std::endl;

}

int main() {
  const std::size_t vec_size(100);
  std::vector<int> vec;

  for (int i=0;i<vec_size;++i) {
    int temp = rand() % 1000;
    vec.push_back(temp);
  }

  std::vector<int> copy(vec.begin(),vec.end());

  CallRegularMergeSort(vec);

  CallConcurrentMergeSort(copy);

  return 0;
}
