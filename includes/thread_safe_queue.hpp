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

  TType pop_back() {
		std::lock_guard<std::mutex> lock(mtx);
		if (deque.empty()) throw std::runtime_error("Queue is empty!");
		auto last = *(deque.end());
		deque.pop_back();
		return last;
  }

  TType pop_front() {
		std::lock_guard<std::mutex> lock(mtx);
		if (deque.empty()) throw std::runtime_error("Queue is empty!");
		auto first = *(deque.begin());
		deque.pop_front();
		return first;
  }
};

template<typename TType>
std::mutex ThreadSafeQueue<TType>::mtx;

#endif
