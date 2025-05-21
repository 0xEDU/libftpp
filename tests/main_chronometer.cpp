#include "../includes/chronometer.hpp"
#include <iostream>
#include <thread>

int main() {
  Chronometer chrono;

  std::cout << "Starting chronometer...\n";
  chrono.start();

  std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // simulate work

  chrono.stop();
  std::cout << "Elapsed time: " << chrono.elapsedMilliseconds() << " ms\n";
  std::cout << "Elapsed time: " << chrono.elapsedSeconds() << " s\n";

  chrono.reset();
  std::cout << "Chronometer reset. Elapsed: " << chrono.elapsedMilliseconds()
            << " ms\n";

  return 0;
}
