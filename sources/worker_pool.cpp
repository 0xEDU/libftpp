#include "../includes/worker_pool.hpp"
#include <string>

std::mutex WorkerPool::haltMutex;

WorkerPool::WorkerPool() = default;
WorkerPool::WorkerPool(const WorkerPool& rhs) {
	*this = rhs;
}
WorkerPool& WorkerPool::operator=(const WorkerPool& rhs) {
	if (this != &rhs) {
	}
	return *this;
};
WorkerPool::~WorkerPool() {
	{
		std::lock_guard<std::mutex> lock(haltMutex);
		halt = true;
	}
	for (auto& thread : threads) {
		thread->stop();
	}
}

WorkerPool::WorkerPool(int numWorkers) {
	threads.resize(numWorkers);

	for (int i = 0; i < numWorkers; ++i) {
		threads[i] = std::make_unique<Thread>("Worker " + std::to_string(i), [this]() {
			while (true) {
				try {
					auto job = jobsQueue.pop_front();
					job();
				} catch (const std::exception& e) {
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				{
					std::lock_guard<std::mutex> lock(haltMutex);
					if (halt) {
						break;
					}
				}
			}
		});
		threads[i]->start();
	}
}

void WorkerPool::addJob(const std::function<void()>& jobToExecute) {
	jobsQueue.push_back(jobToExecute);
}
