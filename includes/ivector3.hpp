#ifndef IVECTOR3_HPP
#define IVECTOR3_HPP

#include <cmath>

template <typename TType> struct IVector3 {
  TType x;
  TType y;
  TType z;

  IVector3() = default;
  IVector3(const IVector3 &rhs) { *this = rhs; }
  IVector3(IVector3 &&rhs) = delete;
  auto operator=(const IVector3 &rhs) -> IVector3 & {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }
  auto operator=(IVector3 &&rhs) -> IVector3 & = delete;
  ~IVector3() = default;

  IVector3(TType x, TType y, TType z) : x(x), y(y), z(z) {}

  auto operator+(const IVector3 &rhs) const -> IVector3 {
    return IVector3(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  auto operator-(const IVector3 &rhs) const -> IVector3 {
    return IVector3(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  auto operator*(const IVector3 &rhs) const -> IVector3 {
    return IVector3(x * rhs.x, y * rhs.y, z * rhs.z);
  }

  auto operator/(const IVector3 &rhs) const -> IVector3 {
    return IVector3(x / rhs.x, y / rhs.y, z / rhs.z);
  }

  auto operator==(const IVector3 &rhs) const -> bool {
    return (x == rhs.x && y == rhs.y && z == rhs.z);
  }

  auto operator!=(const IVector3 &rhs) const -> bool {
    return (x != rhs.x || y != rhs.y || z != rhs.z);
  }

  auto length() const -> float { return sqrt(x * x + y * y + z * z); }

  auto dot(const IVector3 &rhs) -> float {
    return (x * rhs.x + y * rhs.y + z * rhs.z);
  }

  auto cross(const IVector3 &rhs) const -> IVector3 {
    return IVector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
                    x * rhs.y - y * rhs.x);
  }

  auto normalize() -> IVector3<float>;
};

#endif // !IVECTOR3_HPP
