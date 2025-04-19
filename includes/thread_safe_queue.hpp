#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

template<typename TType>
class ThreadSafeQueue {
public:
  ThreadSafeQueue() = default;
  ThreadSafeQueue(const ThreadSafeQueue&) = delete;
  ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
  ~ThreadSafeQueue() = default;
};

#endif