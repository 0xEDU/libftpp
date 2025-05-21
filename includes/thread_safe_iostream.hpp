#ifndef THREAD_SAFE_IOSTREAM_HPP
#define THREAD_SAFE_IOSTREAM_HPP

#include <iostream>
#include <mutex>
#include <sstream>

class ThreadSafeIOStream {
  static std::mutex mtx;
  std::ostream &os = std::cout;
  std::istream &is = std::cin;
  std::string prefix;
  bool needPrefix = true;

public:
  ThreadSafeIOStream();
  ThreadSafeIOStream(const ThreadSafeIOStream &);
  ThreadSafeIOStream &operator=(const ThreadSafeIOStream &);
  ~ThreadSafeIOStream();

  template <typename T> ThreadSafeIOStream &operator<<(const T &input) {
    std::lock_guard<std::mutex> lock(mtx);
    if (needPrefix && !prefix.empty()) {
      os << prefix;
      needPrefix = false;
    }
    os << input;

    // If ended in newline, insert prefix on next line
    std::stringstream ss;
    ss << input;
    if (!ss.str().empty() && ss.str().back() == '\n') {
      needPrefix = true;
    }
    return *this;
  };

  template <typename T> void prompt(const std::string &question, T &dest) {
    std::lock_guard lock(mtx);

    if (needPrefix && !prefix.empty()) {
      os << prefix;
    }

    os << question;
    os.flush(); // Ensure it is printed before input

    is >> dest;

    needPrefix = true;
  }

  // For manips like '\n'
  ThreadSafeIOStream &operator<<(std::ostream &(*manip)(std::ostream &));

  void setPrefix(const std::string &prefix);
};

extern thread_local ThreadSafeIOStream threadSafeCout;

#endif // !THREAD_SAFE_IOSTREAM_HPP
