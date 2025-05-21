#include "../includes/logger.hpp"

int main() {
  Logger logger;

  logger.info("Starting application...");
  logger.warn("Low memory warning.");
  logger.error("Failed to load configuration file.");

  logger.setLevel(LogLevel::WARNING);
  logger.info("This info message should NOT appear.");
  logger.error("This error message should appear.");

  return 0;
}
