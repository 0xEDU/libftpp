#include "../includes/test_helper.hpp"
#include <assert.h>

void thrower() {
  throw std::runtime_error("Error");
}

void notThrower() {
  return;
}

auto main() -> int {
  TestHelper testHelper;
  int a = 2;
  int b = 2;

  testHelper.expectTrue(a == b, "expectTrue");
  assert(a == b);

  testHelper.expectFalse(a != b, "expectFalse");
  assert((a != b) == false);

  float c = 0.1;
  float d = 0.1;
  testHelper.expectFloatEqual(c, d, "expectFloatEqual");
  assert((c - d < 1e-6) == true);

  testHelper.expectThrow(thrower, "expectThrow");
  try {
    thrower();
  } catch (...) {
    assert(true);
  }

  testHelper.expectNotThrow(notThrower, "expectNotThrow");
  try {
    notThrower();
    assert(true);
  } catch (...) {
    assert(false);
  }

  return 0;
}
