#include "../includes/persistent_worker.hpp"
#include "../includes/thread_safe_iostream.hpp"
#include <chrono>

int main() {
  PersistentWorker worker;

  auto task1 = []() { threadSafeCout << "Executing Task 1" << '\n'; };

  auto task2 = []() { threadSafeCout << "Executing Task 2" << '\n'; };

  worker.addTask("Task1", task1);
  worker.addTask("Task2", task2);

  std::this_thread::sleep_for(std::chrono::seconds(1));

  worker.removeTask("Task1");

  std::this_thread::sleep_for(std::chrono::seconds(1));

  return 0;
}
