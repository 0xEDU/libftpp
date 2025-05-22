#include "../includes/ivector3.hpp"
#include "../includes/test_helper.hpp"
#include <iostream>

int main() {
  TestHelper testHelper;
  IVector3<int> vec1(3, 4, 1);
  IVector3<int> vec2(1, 2, 3);
  IVector3<float> vec3(3.0, 4.0, 1.0);

  std::cout << "Vec1 : " << vec1.x << " / " << vec1.y << " / " << vec1.z
            << '\n';
  std::cout << "Vec2 : " << vec2.x << " / " << vec2.y << " / " << vec2.z
            << '\n';

  // Test operator overloads
  auto vecAdd = vec1 + vec2;
  std::cout << "vec1 + vec2 = (" << vecAdd.x << ", " << vecAdd.y << ", "
            << vecAdd.z << ")" << '\n';
  testHelper.expectTrue(vecAdd == IVector3<int>(4, 6, 4),
                        "vec1 + vec2 should equal (4, 6, 4)");

  auto vecSub = vec1 - vec2;
  std::cout << "vec1 - vec2 = (" << vecSub.x << ", " << vecSub.y << ", "
            << vecSub.z << ")" << '\n';
  testHelper.expectTrue(vecSub == IVector3<int>(2, 2, -2),
                        "vec1 - vec2 should equal (2, 2, -2)");

  auto vecMul = vec1 * vec2;
  std::cout << "vec1 * vec2 = (" << vecMul.x << ", " << vecMul.y << ", "
            << vecMul.z << ")" << '\n';
  testHelper.expectTrue(vecMul == IVector3<int>(3, 8, 3),
                        "vec1 * vec2 should equal (3, 8, 3)");

  auto vecDiv = vec1 / vec2;
  std::cout << "vec1 / vec2 = (" << vecDiv.x << ", " << vecDiv.y << ", "
            << vecDiv.z << ")" << '\n';
  testHelper.expectTrue(vecDiv == IVector3<int>(3, 2, 0),
                        "vec1 / vec2 should equal (3, 2, 0)");

  bool isEqual = vec1 == vec2;
  std::cout << "vec1 == vec2: " << (isEqual ? "true" : "false") << '\n';
  testHelper.expectFalse(isEqual, "vec1 == vec2 should be false");

  bool isNotEqual = vec1 != vec2;
  std::cout << "vec1 != vec2: " << (isNotEqual ? "true" : "false") << '\n';
  testHelper.expectTrue(isNotEqual, "vec1 != vec2 should be true");

  // Test additional methods
  float len = vec1.length();
  std::cout << "Length of vec1: " << len << '\n';
  testHelper.expectFloatEqual(len, 5.09902,
                              "Length of vec1 should be approximately 5.099");
  // Expected: Length of vec1: 5.099 (or sqrt(3*3 + 4*4 + 1*1))

  auto normVec = vec3.normalize();
  std::cout << "Normalized vec1 = (" << normVec.x << ", " << normVec.y << ", "
            << normVec.z << ")" << '\n';
  testHelper.expectFloatEqual(normVec.x, 0.588348,
                              "Normalized vec1.x should be 0.588348");
  testHelper.expectFloatEqual(normVec.y, 0.784465,
                              "Normalized vec1.y should be 0.784465");
  testHelper.expectFloatEqual(normVec.z, 0.196116,
                              "Normalized vec1.z should be 0.196116");

  float dotProd = vec1.dot(vec2);
  std::cout << "Dot product of vec1 and vec2: " << dotProd << '\n';
  testHelper.expectTrue(
      dotProd == 14,
      "Dot product of vec1 and vec2 should be 14 (or 3*1 + 4*2 + 1*3)");
  // Expected: Dot product of vec1 and vec2: 14 (or 3*1 + 4*2 + 1*3)

  auto crossProd = vec1.cross(vec2);
  std::cout << "Cross product of vec1 and vec2: (" << crossProd.x << ", "
            << crossProd.y << ", " << crossProd.z << ")" << '\n';
  testHelper.expectTrue(crossProd == IVector3<int>(10, -8, 2),
                        "Cross product of vec1 and vec2 should be (10, -8, 2)");
  // Expected: Cross product of vec1 and vec2: (some_value, some_value,
  // some_value)

  return 0;
}
