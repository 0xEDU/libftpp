#include "../includes/chronometer.hpp"
#include "../includes/test_helper.hpp"
#include <iostream>
#include <thread>

int main() {
  TestHelper testHelper;
  Chronometer chrono;

  std::cout << "Starting chronometer...\n";
  chrono.start();
  testHelper.expectTrue(chrono.isRunning(), "Chronometer should be running");

  std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // simulate work

  chrono.stop();
  testHelper.expectFalse(chrono.isRunning(), "Chronometer should not be running");
  std::cout << "Elapsed time: " << chrono.elapsedMilliseconds() << " ms\n";
  std::cout << "Elapsed time: " << chrono.elapsedSeconds() << " s\n";

  chrono.reset();
  std::cout << "Chronometer reset. Elapsed: " << chrono.elapsedMilliseconds()
            << " ms\n";

  return 0;
}
