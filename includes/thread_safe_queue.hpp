#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <mutex>

template<typename TType>
class ThreadSafeQueue {
	static std::mutex mtx;
	std::deque<TType> deque;

public:
  ThreadSafeQueue() = default;
  ThreadSafeQueue(const ThreadSafeQueue&) = delete;
  ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
  ~ThreadSafeQueue() = default;

  void push_back(const TType& newElement) {
		std::lock_guard<std::mutex> lock(mtx);
		deque.push_back(newElement);
  }

  void push_front(const TType& newElement) {
		std::lock_guard<std::mutex> lock(mtx);
		deque.push_front(newElement);
  }

  TType pop_back(const & newElement) {
		std::lock_guard<std::mutex> lock(mtx);
		if (deque.empty()) throw std::runtime_error("Queue is empty!");
		deque.pop_back();
  }

  TType pop_front(const TType& newElement) {
		std::lock_guard<std::mutex> lock(mtx);
		if (deque.empty()) throw std::runtime_error("Queue is empty!");
		deque.pop_front();
  }
};

template<typename TType>
std::mutex ThreadSafeQueue<TType>::mtx;

#endif
