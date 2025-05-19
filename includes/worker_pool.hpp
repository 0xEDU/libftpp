#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include "../includes/thread.hpp"
#include "../includes/thread_safe_queue.hpp"
#include <functional>
#include <vector>

class WorkerPool {
  static std::mutex haltMutex;
  bool halt = false;
  ThreadSafeQueue<std::function<void()>> jobsQueue;
  std::vector<std::unique_ptr<Thread>> threads;

public:
  WorkerPool();
  WorkerPool(const WorkerPool &);
  WorkerPool &operator=(const WorkerPool &);
  ~WorkerPool();

  WorkerPool(int numWorkers);
  void addJob(const std::function<void()> &jobToExecute);

  class IJobs {
  public:
    virtual ~IJobs() = default;
  };
};

#endif // !WORKER_POOL_HPP
