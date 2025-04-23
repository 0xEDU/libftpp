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
}

void WorkerPool::addJob(std::function<void()>& jobToExecute) {
}
