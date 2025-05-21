#include "../includes/ivector2.hpp"
#include <iostream>

int main() {
  IVector2<int> vec1(3, 4);
  IVector2<int> vec2(1, 2);
  IVector2<float> vec3(3.0, 4.0);

  std::cout << "Vec1 : " << vec1.x << " / " << vec1.y << '\n';
  std::cout << "Vec2 : " << vec2.x << " / " << vec2.y << '\n';

  // Test operator overloads
  auto vecAdd = vec1 + vec2;
  std::cout << "vec1 + vec2 = (" << vecAdd.x << ", " << vecAdd.y << ")" << '\n';
  // Expected: vec1 + vec2 = (4, 6)

  auto vecSub = vec1 - vec2;
  std::cout << "vec1 - vec2 = (" << vecSub.x << ", " << vecSub.y << ")" << '\n';
  // Expected: vec1 - vec2 = (2, 2)

  auto vecMul = vec1 * vec2;
  std::cout << "vec1 * vec2 = (" << vecMul.x << ", " << vecMul.y << ")" << '\n';
  // Expected: vec1 * vec2 = (3, 8)

  auto vecDiv = vec1 / vec2;
  std::cout << "vec1 / vec2 = (" << vecDiv.x << ", " << vecDiv.y << ")" << '\n';
  // Expected: vec1 / vec2 = (3, 2)

  bool isEqual = vec1 == vec2;
  std::cout << "vec1 == vec2: " << (isEqual ? "true" : "false") << "" << '\n';
  // Expected: vec1 == vec2: false

  bool isNotEqual = vec1 != vec2;
  std::cout << "vec1 != vec2: " << (isNotEqual ? "true" : "false") << ""
            << '\n';
  // Expected: vec1 != vec2: true

  // Test additional methods
  float len = vec1.length();
  std::cout << "Length of vec1: " << len << "" << '\n';
  // Expected: Length of vec1: 5 (or sqrt(3*3 + 4*4))

  auto normVec = vec3.normalize();
  std::cout << "Normalized vec1 = (" << normVec.x << ", " << normVec.y << ")"
            << '\n';
  // Expected: Normalized vec1 = (0.6, 0.8)

  float dotProd = vec1.dot(vec2);
  std::cout << "Dot product of vec1 and vec2: " << dotProd << "" << '\n';
  // Expected: Dot product of vec1 and vec2: 11 (or 3*1 + 4*2)

  auto crossProd = vec1.cross(vec2);
  std::cout << "Cross product of vec1: (" << crossProd.x << ", " << crossProd.y
            << ")" << '\n';
  // Expected: Cross product of vec1: (2, -2)

  return 0;
}
