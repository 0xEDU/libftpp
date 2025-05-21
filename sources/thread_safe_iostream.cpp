#include "../includes/thread_safe_iostream.hpp"
#include <mutex>

std::mutex ThreadSafeIOStream::mtx;
thread_local ThreadSafeIOStream threadSafeCout;

ThreadSafeIOStream::ThreadSafeIOStream() = default;
ThreadSafeIOStream::~ThreadSafeIOStream() = default;
ThreadSafeIOStream::ThreadSafeIOStream(const ThreadSafeIOStream &rhs) {
  *this = rhs;
};
auto ThreadSafeIOStream::operator=(const ThreadSafeIOStream &rhs)
    -> ThreadSafeIOStream & {
  if (this != &rhs) {
    prefix = rhs.prefix;
    needPrefix = rhs.needPrefix;
  }
  return *this;
};

auto ThreadSafeIOStream::operator<<(std::ostream &(*manip)(std::ostream &))
    -> ThreadSafeIOStream & {
  std::lock_guard<std::mutex> lock(mtx);
  os << manip;
  if (manip == static_cast<std::ostream &(*)(std::ostream &)>(std::endl)) {
    needPrefix = true;
  }
  return *this;
}

void ThreadSafeIOStream::setPrefix(const std::string &p) {
  std::lock_guard<std::mutex> lock(mtx);
  prefix = p;
}
