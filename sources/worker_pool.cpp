#include "../includes/worker_pool.hpp"

WorkerPool::WorkerPool() = default;
WorkerPool::WorkerPool(const WorkerPool& rhs) {
	*this = rhs;
}
WorkerPool& WorkerPool::operator=(const WorkerPool& rhs) {
	if (this != &rhs) {
	}
	return *this;
};
WorkerPool::~WorkerPool() = default;

WorkerPool::WorkerPool(int numWorkers) {
	threads.resize(numWorkers);
	for (int i = 0; i < numWorkers; ++i) {
		// My pool implementation is probably slopy, should add someting better
		auto thread = threads.acquire("Worker " + std::to_string(i), [this]() {
			while (true) {
				try {
					auto job = jobsQueue.pop_front();
					job();
				} catch(const std::runtime_error& e) {
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
			}
		});
	}
}

void WorkerPool::addJob(const std::function<void()>& jobToExecute) {
	jobsQueue.push_back(jobToExecute);
}
