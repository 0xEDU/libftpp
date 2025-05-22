#include "../includes/random_2D_coordinate_generator.hpp"
#include "../includes/test_helper.hpp"
#include <iostream>
#include <utility>
#include <vector>

int main() {
  TestHelper testHelper;
  Random2DCoordinateGenerator randomGenerator;

  // Store a list of coordinates to test
  std::vector<std::pair<long long, long long>> coordinates = {
      {5, 3}, {7, 2}, {1, 9}, {0, 0}};

  // Store the random numbers generated the first time
  std::vector<long long> firstGenerated;

  std::cout << "First round of generation:" << '\n';
  for (const auto &coord : coordinates) {
    long long x = coord.first;
    long long y = coord.second;
    long long randomNumber = randomGenerator(x, y);
    firstGenerated.push_back(randomNumber);
    std::cout << "Random number using coordinates (" << x << ", " << y
              << "): " << randomNumber << '\n';
  }
  std::cout << '\n';

  std::cout << "Second round of generation:" << '\n';
  for (size_t i = 0; i < coordinates.size(); ++i) {
    long long x = coordinates[i].first;
    long long y = coordinates[i].second;
    long long randomNumber = randomGenerator(x, y);

    std::cout << "Random number using coordinates (" << x << ", " << y
              << "): " << randomNumber << '\n';

    // Check if the number is the same as generated the first time
    testHelper.expectTrue(
        randomNumber == firstGenerated[i],
        "Random number should be the same as the first generated value.");
  }
  std::cout << '\n';

  return 0;
}
