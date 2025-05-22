#include "../includes/ivector2.hpp"
#include "../includes/test_helper.hpp"
#include <iostream>

int main() {
  TestHelper testHelper;
  IVector2<int> vec1(3, 4);
  IVector2<int> vec2(1, 2);
  IVector2<float> vec3(3.0, 4.0);

  std::cout << "Vec1 : " << vec1.x << " / " << vec1.y << '\n';
  std::cout << "Vec2 : " << vec2.x << " / " << vec2.y << '\n';

  // Test operator overloads
  auto vecAdd = vec1 + vec2;
  std::cout << "vec1 + vec2 = (" << vecAdd.x << ", " << vecAdd.y << ")" << '\n';
  testHelper.expectTrue(vecAdd == IVector2<int>(4, 6),
                        "vec1 + vec2 should equal (4, 6)");

  auto vecSub = vec1 - vec2;
  std::cout << "vec1 - vec2 = (" << vecSub.x << ", " << vecSub.y << ")" << '\n';
  testHelper.expectTrue(vecSub == IVector2<int>(2, 2),
                        "vec1 - vec2 should equal (2, 2)");

  auto vecMul = vec1 * vec2;
  std::cout << "vec1 * vec2 = (" << vecMul.x << ", " << vecMul.y << ")" << '\n';
  testHelper.expectTrue(vecMul == IVector2<int>(3, 8),
                        "vec1 * vec2 should equal (3, 8)");

  auto vecDiv = vec1 / vec2;
  std::cout << "vec1 / vec2 = (" << vecDiv.x << ", " << vecDiv.y << ")" << '\n';
  testHelper.expectTrue(vecDiv == IVector2<int>(3, 2),
                        "vec1 / vec2 should equal (3, 2)");

  bool isEqual = vec1 == vec2;
  std::cout << "vec1 == vec2: " << (isEqual ? "true" : "false") << "" << '\n';
  testHelper.expectFalse(isEqual, "vec1 == vec2 should be false");

  bool isNotEqual = vec1 != vec2;
  std::cout << "vec1 != vec2: " << (isNotEqual ? "true" : "false") << ""
            << '\n';
  testHelper.expectTrue(isNotEqual, "vec1 != vec2 should be true");

  // Test additional methods
  float len = vec1.length();
  std::cout << "Length of vec1: " << len << "" << '\n';
  testHelper.expectTrue(len == 5,
                        "Length of vec1 should be 5 (or sqrt(3*3 + 4*4))");

  auto normVec = vec3.normalize();
  std::cout << "Normalized vec1 = (" << normVec.x << ", " << normVec.y << ")"
            << '\n';
  testHelper.expectTrue(normVec == IVector2<float>(0.6, 0.8),
                        "Normalized vec1 should be (0.6, 0.8)");

  float dotProd = vec1.dot(vec2);
  std::cout << "Dot product of vec1 and vec2: " << dotProd << "" << '\n';
  testHelper.expectTrue(
      dotProd == 11,
      "Dot product of vec1 and vec2 should be 11 (or 3*1 + 4*2)");

  auto crossProd = vec1.cross(vec2);
  std::cout << "Cross product of vec1: (" << crossProd.x << ", " << crossProd.y
            << ")" << '\n';
  testHelper.expectTrue(crossProd == IVector2<int>(2, -2),
                        "Cross product of vec1 should be (2, -2)");

  return 0;
}
