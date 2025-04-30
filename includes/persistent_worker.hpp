#ifndef PERSISTENT_WORKER_HPP
#define PERSISTENT_WORKER_HPP

#include <functional>
#include <unordered_map>
#include "../includes/thread.hpp"

class PersistentWorker {
	static std::mutex persistentWorkerMtx;
	std::unordered_map<std::string, std::function<void()>> tasksMap;
	bool halt = false;
	Thread worker;

public:
	PersistentWorker();
	PersistentWorker(const PersistentWorker&) = delete;
	PersistentWorker operator=(const PersistentWorker&) = delete;
	~PersistentWorker();

	void addTask(const std::string& name, const std::function<void()>& jobToExecute);
	void removeTask(const std::string& name);
};

#endif // !PERSISTENT_WORKER_HPP
