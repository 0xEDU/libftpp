#include "../includes/ivector3.hpp"
#include <iostream>

int main() {
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
  // Expected: vec1 + vec2 = (4, 6, 4)

  auto vecSub = vec1 - vec2;
  std::cout << "vec1 - vec2 = (" << vecSub.x << ", " << vecSub.y << ", "
            << vecSub.z << ")" << '\n';
  // Expected: vec1 - vec2 = (2, 2, -2)

  auto vecMul = vec1 * vec2;
  std::cout << "vec1 * vec2 = (" << vecMul.x << ", " << vecMul.y << ", "
            << vecMul.z << ")" << '\n';
  // Expected: vec1 * vec2 = (3, 8, 3)

  auto vecDiv = vec1 / vec2;
  std::cout << "vec1 / vec2 = (" << vecDiv.x << ", " << vecDiv.y << ", "
            << vecDiv.z << ")" << '\n';
  // Expected: vec1 / vec2 = (3, 2, 0)

  bool isEqual = vec1 == vec2;
  std::cout << "vec1 == vec2: " << (isEqual ? "true" : "false") << '\n';
  // Expected: vec1 == vec2: false

  bool isNotEqual = vec1 != vec2;
  std::cout << "vec1 != vec2: " << (isNotEqual ? "true" : "false") << '\n';
  // Expected: vec1 != vec2: true

  // Test additional methods
  float len = vec1.length();
  std::cout << "Length of vec1: " << len << '\n';
  // Expected: Length of vec1: 5.099 (or sqrt(3*3 + 4*4 + 1*1))

  auto normVec = vec3.normalize();
  std::cout << "Normalized vec1 = (" << normVec.x << ", " << normVec.y << ", "
            << normVec.z << ")" << '\n';
  // Expected: Normalized vec1 = (some_value, some_value, some_value)

  float dotProd = vec1.dot(vec2);
  std::cout << "Dot product of vec1 and vec2: " << dotProd << '\n';
  // Expected: Dot product of vec1 and vec2: 14 (or 3*1 + 4*2 + 1*3)

  auto crossProd = vec1.cross(vec2);
  std::cout << "Cross product of vec1 and vec2: (" << crossProd.x << ", "
            << crossProd.y << ", " << crossProd.z << ")" << '\n';
  // Expected: Cross product of vec1 and vec2: (some_value, some_value,
  // some_value)

  return 0;
}
