#include "math_utils.hpp"
#include <random>
#include <vector>

namespace
{
  using iterator = std::vector< size_t >::iterator;

  void getInAllPoints(int r, size_t per_th, long long int seed, iterator it_in, iterator it_all)
  {
    size_t in = 0;
    size_t all = 0;
    std::mt19937 gen(seed);
    std::uniform_real_distribution< double > rand(0, r);
    for (size_t i = 0; i < per_th; ++i)
    {
      double x = rand(gen);
      double y = rand(gen);
      if (abramov::isInCircle(x, y, r))
      {
        ++in;
      }
      ++all;
    }
    *it_in = in;
    *it_all = all;
  }
}

bool abramov::isInCircle(double x, double y, int r)
{
  return std::sqrt(x * x + y * y) - r < 0;
}
