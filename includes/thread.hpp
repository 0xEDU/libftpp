#ifndef THREAD_HPP
#define THREAD_HPP

#include <functional>
#include <thread>

#include "thread_safe_iostream.hpp"

class Thread {
  std::string name;
  std::function<void()> func;
  std::unique_ptr<std::thread> thread = nullptr;
  ThreadSafeIOStream stream;

  void execThread();

public:
  Thread();
  Thread(const Thread &rhs);
  Thread(Thread &&rhs) = delete;
  auto operator=(const Thread &rhs) -> Thread &;
  auto operator=(Thread &&rhs) -> Thread & = delete;
  ~Thread();

  Thread(const std::string &name, std::function<void()> functToExecute);
  void start();
  void stop();
};

#endif
