#ifndef THREAD_HPP
#define THREAD_HPP

#include <functional>
#include <thread>

#include "thread_safe_iostream.hpp"

class Thread {
	std::string name;
	std::function<void()> func;
	std::unique_pointer<std::thread> thread = nullptr;
	ThreadSafeIOStream stream;

public:
	Thread();
	Thread(const Thread&);
	Thread &operator=(const Thread&);
	~Thread();

	Thread(const std::string& name, std::function<void()> functToExecute);
	void start();
	void stop();
};

#endif
