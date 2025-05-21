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

  auto operator+(const IVector2 &rhs) const -> IVector2 {
    return IVector2(x + rhs.x, y + rhs.y);
  }

  auto operator-(const IVector2 &rhs) const -> IVector2 {
    return IVector2(x - rhs.x, y - rhs.y);
  }

  auto operator*(const IVector2 &rhs) const -> IVector2 {
    return IVector2(x * rhs.x, y * rhs.y);
  }

  auto operator/(const IVector2 &rhs) const -> IVector2 {
    return IVector2(x / rhs.x, y / rhs.y);
  }

  auto operator==(const IVector2 &rhs) const -> bool {
    return (x == rhs.x && y == rhs.y);
  }

  auto operator!=(const IVector2 &rhs) const -> bool {
    return (x != rhs.x || y != rhs.y);
  }

  auto length() const -> float { return sqrt(x * x + y * y); }

  auto dot(const IVector2 &rhs) -> float { return (x * rhs.x + y * rhs.y); }

  auto cross(const IVector2 &rhs) const -> IVector2 {
    return IVector2(x * rhs.y - y * rhs.x, y * rhs.x - x * rhs.y);
  }

  auto normalize() -> IVector2<float>;
};

#endif // !IVECTOR2_HPP
