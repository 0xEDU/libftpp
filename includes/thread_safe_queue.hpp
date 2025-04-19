#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

template<typename TType>
class ThreadSafeQueue {
public:
  ThreadSafeQueue() = default;
  ThreadSafeQueue(const ThreadSafeQueue&) = delete;
  ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
  ~ThreadSafeQueue() = default;

  void push_back(const TType& newElement) {
    
  }

  void push_front(const TType& newElement) {
    
  }

  TType pop_back(const & newElement) {
    
  }

  TType pop_front(const TType& newElement) {
    
  }
};

#endif