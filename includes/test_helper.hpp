#ifndef TEST_HELPER_HPP
#define TEST_HELPER_HPP

#include <functional>
#include <iostream>
#include <vector>

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define WHITE "\033[1;37m"

#define RESET "\033[0m"

class TestHelper {
  using TestCase = std::pair<bool, std::string>;

  std::vector<TestCase> testCases;

public:
  TestHelper() = default;
  TestHelper(const TestHelper &) = delete;
  TestHelper &operator=(const TestHelper &) = delete;
  ~TestHelper();

  void expectTrue(bool condition, std::string testName);
  void expectFalse(bool condition, std::string testName);
  void expectThrow(std::function<void()> func, std::string testName);
  void expectNotThrow(std::function<void()> func, std::string testName);
};

#endif
