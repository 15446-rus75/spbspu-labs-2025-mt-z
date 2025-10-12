#include "math_utils.hpp"
#include <random>
#include <stdexcept>

bool abramov::isInCircle(double x, double y, int r)
{
  return std::sqrt(x * x + y * y) - r < 0;
}

double abramov::getArea(int r, long long int tries, long long int seed)
{
  if (r <= 0)
  {
    throw std::logic_error("Radius must be positive");
  }
  std::mt19937 gen(seed);
  std::uniform_real_distribution< double > rand(0, r);
  size_t in = 0;
  size_t all = 0;
  for (size_t i = 0; i < tries; ++i)
  {
    double x = rand(gen);
    double y = rand(gen);
    if (isInCircle(x, y, r))
    {
      ++in;
    }
    ++all;
  }
  double area = 2.0 * r * 2.0 * r * in / all;
  return area;
}
