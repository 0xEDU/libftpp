#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
  LogLevel level;

  auto levelToString(LogLevel level) const -> std::string;
  auto timestamp() const -> std::string;

public:
  Logger(LogLevel level = LogLevel::INFO);
  Logger(const Logger &rhs) = delete;
  Logger(Logger &&rhs) = delete;
  auto operator=(const Logger &rhs) -> Logger & = delete;
  ~Logger() = default;

  void setLevel(LogLevel level);
  void log(LogLevel level, const std::string &message);
  void info(const std::string &message);
  void warn(const std::string &message);
  void error(const std::string &message);
};

#endif // LOGGER_HPP
