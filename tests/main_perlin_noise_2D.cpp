#include "perlin_noise_2D.hpp"
#include <cmath>
#include <iostream>

int main() {
  PerlinNoise2D perlin;

  const int gridSize = 50;
  const char* heatmapColors[] = {
      "\033[48;5;17m",  // dark blue
      "\033[48;5;18m",  // blue
      "\033[48;5;19m",  // medium blue
      "\033[48;5;28m",  // green
      "\033[48;5;34m",  // light green
      "\033[48;5;142m", // yellow-green
      "\033[48;5;220m", // yellow
      "\033[48;5;214m", // orange
      "\033[48;5;202m", // red-orange
      "\033[48;5;196m"  // red
  };
  const char* reset = "\033[0m";
  const char fillChar = ' ';

  std::cout << "Sampling 2D Perlin noise over a " << gridSize << "x" << gridSize
            << " grid:" << std::endl
            << std::endl;

  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridSize; ++x) {
      float sample = perlin.sample(x * 0.1f, y * 0.1f);
      sample = (sample + 1) / 2; // Map from [-1, 1] to [0, 1]
      int colorIndex = std::min(static_cast<int>(sample * 10), 9);

      std::cout << heatmapColors[colorIndex] << fillChar << fillChar;
    }
    std::cout << reset << std::endl;
  }

  return 0;
}
