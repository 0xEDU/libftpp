#ifndef CHRONOMETER_HPP
#define CHRONOMETER_HPP

#include <chrono>

class Chronometer {
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = Clock::time_point;

  TimePoint startTime;
  TimePoint endTime;
  bool running = false;

public:
  Chronometer() = default;
  Chronometer(const Chronometer &rhs) = delete;
  Chronometer(Chronometer &&rhs) = delete;
  auto operator=(const Chronometer &rhs) -> Chronometer & = delete;
  ~Chronometer() = default;

  void start();
  void stop();
  void reset();

  auto elapsedMilliseconds() const -> double;
  auto elapsedSeconds() const -> double;
  auto isRunning() const -> bool;
};

#endif // !CHRONOMETER_HPP
