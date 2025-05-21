#ifndef RANDOM_2D_COORDINATE_GENERATOR_HPP
#define RANDOM_2D_COORDINATE_GENERATOR_HPP

#include <chrono>

class Random2DCoordinateGenerator {
  long long _seed = 0;

public:
  Random2DCoordinateGenerator();
  Random2DCoordinateGenerator(const Random2DCoordinateGenerator &rhs);
  auto operator=(const Random2DCoordinateGenerator &rhs)
      -> Random2DCoordinateGenerator &;
  ~Random2DCoordinateGenerator() = default;

  auto seed() -> long long;
  auto operator()(const long long &x, const long long &y) -> long long;
};

#endif // !RANDOM_2D_COORDINATE_GENERATOR_HPP
