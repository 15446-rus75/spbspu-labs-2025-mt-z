#include "math_utils.hpp"
#include <random>
#include <thread>
#include <vector>
#include <stdexcept>

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

double abramov::getArea(int r, long long int tries, long long int seed, unsigned int number)
{
  if (r <= 0)
  {
    throw std::logic_error("Radius must be positive");
  }
  std::vector< std::thread > ths;
  ths.reserve(number);
  std::vector< size_t > ins(number, 0);
  std::vector< size_t > alls(number , 0);
  size_t per_th = tries / number;
  size_t i = 0;
  for (; i < number - 1; ++i)
  {
    ths.emplace_back(getInAllPoints, r, per_th, seed, ins.begin() + i, alls.begin() + i);
  }
  getInAllPoints(r, per_th, seed, ins.begin() + i, alls.begin() + i);
  for (auto && th: ths)
  {
    th.join();
  }

  size_t in = std::accumulate(ins.begin(), ins.end(), 0);
  size_t all = std::accumulate(alls.begin(), alls.end(), 0);
  double area = 2.0 * r * 2.0 * r * in / all;
  return area;
}
