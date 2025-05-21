#include "../includes/ivector2.hpp"

template <> auto IVector2<float>::normalize() -> IVector2<float> {
  float len = length();
  if (len == 0) {
    return IVector2<float>(0, 0);
  }
  return IVector2<float>(x / len, y / len);
}
