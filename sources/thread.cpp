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
	stream.setPrefix(name);
}

void Thread::start() {
}

void Thread::stop() {
}
