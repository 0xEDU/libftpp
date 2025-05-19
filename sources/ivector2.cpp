#include "../includes/ivector2.hpp"

template <> IVector2<float> IVector2<float>::normalize() {
  float len = length();
  if (len == 0) {
    return IVector2<float>(0, 0);
  }
  return IVector2<float>(x / len, y / len);
}
