#include "../includes/chronometer.hpp"

void Chronometer::start() {
  if (!running) {
    startTime = Clock::now();
    running = true;
  }
}

void Chronometer::stop() {
  if (running) {
    endTime = Clock::now();
    running = false;
  }
}

void Chronometer::reset() {
  running = false;
  startTime = Clock::now();
  endTime = startTime;
}

auto Chronometer::elapsedMilliseconds() const -> double {
  TimePoint end = running ? Clock::now() : endTime;
  return std::chrono::duration<double, std::milli>(end - startTime).count();
}

double Chronometer::elapsedSeconds() const {
  return elapsedMilliseconds() / 1000.0;
}

bool Chronometer::isRunning() const {
  return running;
}
