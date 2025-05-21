#ifndef PERLIN_NOISE_2D_HPP
#define PERLIN_NOISE_2D_HPP

#include "../includes/ivector2.hpp"
#include "../includes/random_2D_coordinate_generator.hpp"

class PerlinNoise2D {
  Random2DCoordinateGenerator _randomGenerator;

  auto fade(float t) -> float;
  auto lerp(float a, float b, float t) -> float;
  auto gradient(int ix, int iy) -> IVector2<float>;

public:
  PerlinNoise2D() = default;
  PerlinNoise2D(const PerlinNoise2D &rhs);
  PerlinNoise2D(PerlinNoise2D &&rhs) = delete;
  auto operator=(const PerlinNoise2D &rhs) -> PerlinNoise2D &;
  ~PerlinNoise2D() = default;

  auto sample(float x, float y) -> float;
};

#endif // !PERLIN_NOISE_2D_HPP
