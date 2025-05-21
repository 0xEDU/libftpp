#include "../includes/logger.hpp"

Logger::Logger(LogLevel level) : level(level) {}

void Logger::setLevel(LogLevel lvl) { level = lvl; }

void Logger::log(LogLevel level, const std::string &message) {
  if (static_cast<int>(level) >= static_cast<int>(level)) {
    std::cout << "[" << timestamp() << "] "
              << "[" << levelToString(level) << "] " << message << '\n';
  }
}

void Logger::info(const std::string &message) { log(LogLevel::INFO, message); }

void Logger::warn(const std::string &message) {
  log(LogLevel::WARNING, message);
}

void Logger::error(const std::string &message) {
  log(LogLevel::ERROR, message);
}

auto Logger::levelToString(LogLevel level) const -> std::string {
  switch (level) {
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARNING:
    return "WARNING";
  case LogLevel::ERROR:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}

auto Logger::timestamp() const -> std::string {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm tm = *std::localtime(&time);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
  return oss.str();
}
