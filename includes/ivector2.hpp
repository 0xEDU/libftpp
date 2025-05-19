#ifndef IVECTOR2_HPP
#define IVECTOR2_HPP

#include <cmath>

template <typename TType> struct IVector2 {
  TType x;
  TType y;

  IVector2() {}
  IVector2(const IVector2 &rhs) { *this = rhs; }
  auto operator=(const IVector2 &rhs) -> IVector2 & {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  ~IVector2() {}

  IVector2(TType x, TType y) : x(x), y(y) {}

  IVector2 operator+(const IVector2 &rhs) const {
    return IVector2(x + rhs.x, y + rhs.y);
  }

  IVector2 operator-(const IVector2 &rhs) const {
    return IVector2(x - rhs.x, y - rhs.y);
  }

  IVector2 operator*(const IVector2 &rhs) const {
    return IVector2(x * rhs.x, y * rhs.y);
  }

  IVector2 operator/(const IVector2 &rhs) const {
    return IVector2(x / rhs.x, y / rhs.y);
  }

  bool operator==(const IVector2 &rhs) const {
    return (x == rhs.x && y == rhs.y);
  }

  bool operator!=(const IVector2 &rhs) const {
    return (x != rhs.x || y != rhs.y);
  }

  float length() const { return sqrt(x * x + y * y); }

  float dot(const IVector2 &rhs) { return (x * rhs.x + y * rhs.y); }

  IVector2 cross(const IVector2 &rhs) const {
    return IVector2(x * rhs.y - y * rhs.x, y * rhs.x - x * rhs.y);
  }

  IVector2<float> normalize();
};

#endif // !IVECTOR2_HPP
