#include "../includes/thread_safe_iostream.hpp"
#include <mutex>

ThreadSafeIOStream::ThreadSafeIOStream() = default;
ThreadSafeIOStream::~ThreadSafeIOStream() = default;
ThreadSafeIOStream::ThreadSafeIOStream(const ThreadSafeIOStream &rhs) {
  *this = rhs;
};
ThreadSafeIOStream &
ThreadSafeIOStream::operator=(const ThreadSafeIOStream &rhs) {
  if (this != &rhs) {
    prefix = rhs.prefix;
    needPrefix = rhs.needPrefix;
  }
  return *this;
};

ThreadSafeIOStream &
ThreadSafeIOStream::operator<<(std::ostream &(*manip)(std::ostream &)) {
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
