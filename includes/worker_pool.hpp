#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include <functional>

class WorkerPool {
public:
	WorkerPool();
	WorkerPool(const WorkerPool&);
	WorkerPool& operator=(const WorkerPool&);
	~WorkerPool();

	WorkerPool(int numWorkers);
	void addJob(std::function<void()>& jobToExecute);
};

#endif // !WORKER_POOL_HPP
