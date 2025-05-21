#include "../includes/ivector3.hpp"

template <> auto IVector3<float>::normalize() -> IVector3<float> {
  float len = length();
  if (len == 0) {
    return IVector3<float>(0, 0, 0);
  }
  return IVector3<float>(x / len, y / len, z / len);
}
