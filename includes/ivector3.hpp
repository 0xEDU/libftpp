#ifndef IVECTOR3_HPP
#define IVECTOR3_HPP

#include <cmath>

template <typename TType> struct IVector3 {
  TType x;
  TType y;
  TType z;

  IVector3() = default;
  IVector3(const IVector3 &rhs) { *this = rhs; }
  auto operator=(const IVector3 &rhs) -> IVector3 & {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }
  ~IVector3() = default;

  IVector3(TType x, TType y, TType z) : x(x), y(y), z(z) {}

  IVector3 operator+(const IVector3 &rhs) const {
    return IVector3(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  IVector3 operator-(const IVector3 &rhs) const {
    return IVector3(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  IVector3 operator*(const IVector3 &rhs) const {
    return IVector3(x * rhs.x, y * rhs.y, z * rhs.z);
  }

  IVector3 operator/(const IVector3 &rhs) const {
    return IVector3(x / rhs.x, y / rhs.y, z / rhs.z);
  }

  bool operator==(const IVector3 &rhs) const {
    return (x == rhs.x && y == rhs.y && z == rhs.z);
  }

  bool operator!=(const IVector3 &rhs) const {
    return (x != rhs.x || y != rhs.y || z != rhs.z);
  }

  float length() const { return sqrt(x * x + y * y + z * z); }

  float dot(const IVector3 &rhs) { return (x * rhs.x + y * rhs.y + z * rhs.z); }

  IVector3 cross(const IVector3 &rhs) const {
    return IVector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
                    x * rhs.y - y * rhs.x);
  }

  IVector3<float> normalize();
};

#endif // !IVECTOR3_HPP
