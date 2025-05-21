#include "../includes/random_2D_coordinate_generator.hpp"

Random2DCoordinateGenerator::Random2DCoordinateGenerator() {
  _seed = static_cast<long long>(
      std::chrono::system_clock::now().time_since_epoch().count());
}

Random2DCoordinateGenerator::Random2DCoordinateGenerator(
    const Random2DCoordinateGenerator &rhs) {
  *this = rhs;
}

auto Random2DCoordinateGenerator::operator=(
    const Random2DCoordinateGenerator &rhs) -> Random2DCoordinateGenerator & {
  if (this != &rhs) {
    _seed = rhs._seed;
  }
  return *this;
}

auto Random2DCoordinateGenerator::seed() -> long long { return _seed; }

// Modified FNV-1a hash function
auto Random2DCoordinateGenerator::operator()(const long long &x,
                                             const long long &y) -> long long {
  long long seed = _seed;

  // Mix x
  seed ^= static_cast<uint64_t>(x);
  seed *= 0x100000001b3ULL; // FNV prime

  // Mix y
  seed ^= static_cast<uint64_t>(y);
  seed *= 0x100000001b3ULL; // FNV prime

  // Final mixing step
  seed ^= (seed >> 33);
  seed *= 0xff51afd7ed558ccdULL;
  seed ^= (seed >> 33);
  seed *= 0xc4ceb9fe1a85ec53ULL;
  seed ^= (seed >> 33);

  return seed;
}
