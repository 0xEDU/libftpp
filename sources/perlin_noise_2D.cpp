#include "../includes/perlin_noise_2D.hpp"

PerlinNoise2D::PerlinNoise2D(const PerlinNoise2D &rhs) { *this = rhs; };

auto PerlinNoise2D::operator=(const PerlinNoise2D &rhs) -> PerlinNoise2D & {
  if (this != &rhs) {
    _randomGenerator = rhs._randomGenerator;
  }
  return *this;
};

float PerlinNoise2D::fade(float t) {
  return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise2D::lerp(float a, float b, float t) { return a + t * (b - a); }

IVector2<float> PerlinNoise2D::gradient(int ix, int iy) {
  long long hash = _randomGenerator(ix, iy);
  float angle = static_cast<float>((hash % 10000) / 10000.0 * 2.0 * M_PI); // [0, 2π)
  return IVector2<float>(std::cos(angle), std::sin(angle));
}

float PerlinNoise2D::sample(float x, float y) {
  int x0 = static_cast<int>(std::floor(x));
  int x1 = x0 + 1;
  int y0 = static_cast<int>(std::floor(y));
  int y1 = y0 + 1;

  IVector2<float> p(x, y);
  IVector2<float> p00 = p - IVector2<float>(x0, y0);
  IVector2<float> p10 = p - IVector2<float>(x1, y0);
  IVector2<float> p01 = p - IVector2<float>(x0, y1);
  IVector2<float> p11 = p - IVector2<float>(x1, y1);

  auto g00 = gradient(x0, y0);
  auto g10 = gradient(x1, y0);
  auto g01 = gradient(x0, y1);
  auto g11 = gradient(x1, y1);

  float dot00 = g00.dot(p00);
  float dot10 = g10.dot(p10);
  float dot01 = g01.dot(p01);
  float dot11 = g11.dot(p11);

  float u = fade(p00.x); // x - x0
  float v = fade(p00.y); // y - y0

  float ix0 = lerp(dot00, dot10, u);
  float ix1 = lerp(dot01, dot11, u);
  float value = lerp(ix0, ix1, v);

  return value;
}
