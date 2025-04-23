#include "../includes/thread.hpp"

std::mutex ThreadSafeIOStream::mtx;
thread_local ThreadSafeIOStream threadSafeCout;

Thread::Thread() = default;
Thread::Thread(const Thread& rhs) {
	*this = rhs;
}
Thread &Thread::operator=(const Thread& rhs) {
	if (this != &rhs) {
	}
	return *this;
}
Thread::~Thread() = default;


Thread::Thread(const std::string& name, std::function<void()> functToExecute) : name(name), func(functToExecute), thread(), stream() {
}

void Thread::start() {
	threadSafeCout.setPrefix(name);
	thread = std::make_unique<std::thread>(func);
}

void Thread::stop() {
	thread->join();
}
