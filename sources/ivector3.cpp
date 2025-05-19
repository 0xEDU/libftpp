#include "../includes/ivector3.hpp"

template <> IVector3<float> IVector3<float>::normalize() {
  float len = length();
  if (len == 0) {
    return IVector3<float>(0, 0, 0);
  }
  return IVector3<float>(x / len, y / len, z / len);
}
