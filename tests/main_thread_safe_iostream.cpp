#include "thread_safe_iostream.hpp"
#include <iostream>
#include <thread>

std::mutex ThreadSafeIOStream::mtx;
thread_local ThreadSafeIOStream threadSafeCout;

void printNumbers(const std::string &p_prefix) {
  threadSafeCout.setPrefix(p_prefix);
  for (int i = 1; i <= 5; ++i) {
    threadSafeCout << "Number: " << i << std::endl;
  }
  std::string answer;
  threadSafeCout.prompt("How are you? ", answer);
  threadSafeCout << answer << std::endl;
}

int main() {
  std::string prefix1 = "[Thread 1] ";
  std::string prefix2 = "[Thread 2] ";

  std::thread thread1(printNumbers, prefix1);
  std::thread thread2(printNumbers, prefix2);

  thread1.join();
  thread2.join();

  return 0;
}
