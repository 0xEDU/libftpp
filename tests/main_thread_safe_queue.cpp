#include "../includes/thread_safe_iostream.hpp"
#include "../includes/thread_safe_queue.hpp"
#include <thread>

void testPushFront(ThreadSafeQueue<int> &p_queue, int p_value) {
  p_queue.push_back(p_value);
  threadSafeCout << "Pushed value: " << p_value << '\n';
}

void testPushBack(ThreadSafeQueue<int> &p_queue, int p_value) {
  p_queue.push_front(p_value);
  threadSafeCout << "Pushed value: " << p_value << '\n';
}

void testPopFront(ThreadSafeQueue<int> &p_queue) {
  try {
    int value = p_queue.pop_front();
    threadSafeCout << "Popped value: " << value << '\n';
  } catch (const std::runtime_error &e) {
    threadSafeCout << e.what() << '\n';
  }
}

void testPopBack(ThreadSafeQueue<int> &p_queue) {
  try {
    int value = p_queue.pop_back();
    threadSafeCout << "Popped value: " << value << '\n';
  } catch (const std::runtime_error &e) {
    threadSafeCout << e.what() << '\n';
  }
}

int main() {
  ThreadSafeQueue<int> myQueue;

  std::thread thread1(testPushFront, std::ref(myQueue), 10);
  std::thread thread2(testPushBack, std::ref(myQueue), 20);
  std::thread thread3(testPopFront, std::ref(myQueue));
  std::thread thread4(testPopBack, std::ref(myQueue));
  std::thread thread5(testPopFront, std::ref(myQueue));

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();
  thread5.join();

  return 0;
}
