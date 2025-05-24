#include "../includes/test_helper.hpp"

TestHelper::~TestHelper() {
  std::vector<std::string> failedTests;

  std::cout << "\n\n";
  for (auto &testCase : testCases) {
    if (testCase.first) {
      std::cout << GREEN << ".";
    } else {
      failedTests.push_back(testCase.second);
      std::cout << RED << "F";
    }
    std::cout << RESET;
  }
  std::cout << "\n";

  if (failedTests.empty()) {
    std::cout << GREEN << "\n[OK]" << WHITE << " All tests passed!" << RESET
              << "\n";
    return;
  }

  std::cout << RED << "\n[NOK]" << WHITE << " Some tests failed!" << RESET
            << "\n\n";

  for (auto &failedTest : failedTests) {
    std::cout << WHITE << "-> " << RED << failedTest << RESET << "\n";
  }
}

void TestHelper::expectTrue(bool condition, std::string testName) {
  if (condition) {
    testCases.push_back({true, testName});
  } else {
    testCases.push_back({false, testName});
  }
}

void TestHelper::expectFalse(bool condition, std::string testName) {
  if (!condition) {
    testCases.push_back({true, testName});
  } else {
    testCases.push_back({false, testName});
  }
}

void TestHelper::expectThrow(std::function<void()> func, std::string testName) {
  try {
    func();
    testCases.push_back({false, testName});
  } catch (...) {
    testCases.push_back({true, testName});
  }
}

void TestHelper::expectNotThrow(std::function<void()> func,
                                std::string testName) {
  try {
    func();
    testCases.push_back({true, testName});
  } catch (...) {
    testCases.push_back({false, testName});
  }
}

void TestHelper::expectFloatEqual(float a, float b, std::string testName) {
  if (std::fabs(a - b) < 1e-6) {
    testCases.push_back({true, testName});
  } else {
    testCases.push_back({false, testName});
  }
}
