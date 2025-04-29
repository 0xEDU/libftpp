#include "../includes/thread.hpp"

std::mutex ThreadSafeIOStream::mtx;
thread_local ThreadSafeIOStream threadSafeCout;

Thread::Thread() = default;
Thread::Thread(const Thread& rhs) {
	*this = rhs;
}
Thread &Thread::operator=(const Thread& rhs) {
	if (this != &rhs) {
		name = rhs.name;
		func = rhs.func;
		thread = nullptr;
		stream = rhs.stream;
	}
	return *this;
}
Thread::~Thread() = default;


Thread::Thread(const std::string& name, std::function<void()> functToExecute) : name(), func(functToExecute), thread(), stream() {
	this->name = "[" + name + "] ";
}

void Thread::start() {
	thread = std::make_unique<std::thread>(&Thread::execThread, this);
}

void Thread::stop() {
	thread->join();
}

void Thread::execThread() {
	threadSafeCout.setPrefix(name);
	func();
}
