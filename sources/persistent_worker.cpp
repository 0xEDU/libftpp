#include "../includes/persistent_worker.hpp"
#include <mutex>
#include <utility>

std::mutex PersistentWorker::persistentWorkerMtx;

PersistentWorker::PersistentWorker() {
  worker = Thread("PersistentWorker", [this]() {
    while (true) {
      std::lock_guard<std::mutex> lock(persistentWorkerMtx);

      if (tasksMap.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      } else {
        for (auto &task : tasksMap) {
          task.second();
        }
      }
      if (halt) {
        break;
      }
    }
  });
  worker.start();
};

PersistentWorker::~PersistentWorker() {
  {
    std::lock_guard<std::mutex> lock(persistentWorkerMtx);
    halt = true;
  }
  worker.stop();
};

void PersistentWorker::addTask(const std::string &name,
                               const std::function<void()> &jobToExecute) {
  std::lock_guard<std::mutex> lock(persistentWorkerMtx);

  tasksMap[name] = jobToExecute;
}

void PersistentWorker::removeTask(const std::string &name) {
  std::lock_guard<std::mutex> lock(persistentWorkerMtx);

  tasksMap.erase(name);
}
