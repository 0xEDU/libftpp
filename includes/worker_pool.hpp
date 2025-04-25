#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include <functional>
#include "../includes/thread_safe_queue.hpp"
#include "../includes/thread.hpp"

class WorkerPool {
	ThreadSafeQueue<std::function<void()>> tsQueue;
	std::vector<Thread> threads;

public:
	WorkerPool();
	WorkerPool(const WorkerPool&);
	WorkerPool& operator=(const WorkerPool&);
	~WorkerPool();

	WorkerPool(int numWorkers);
	void addJob(std::function<void()>& jobToExecute);
};

#endif // !WORKER_POOL_HPP
