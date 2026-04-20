#include "math_utils.hpp"
#include <omp.h>
#include <random>
#include <vector>
#include <stdexcept>

bool abramov::isInCircle(double x, double y, int r)
{
  return std::sqrt(x * x + y * y) - r < 0;
}

double abramov::getArea(const AreaConfig &areacon)
{
  int r = areacon.getR();
  long long int tries = areacon.getTries();
  long long int seed = areacon.getSeed();
  int ths = areacon.getThs();
  unsigned long long int in = 0;

  #pragma omp parallel num_threads(ths) reduction(+:in)
  {
    std::mt19937 gen(seed + omp_get_thread_num());
    std::uniform_real_distribution< double > rand(0, r);
    #pragma omp for schedule(runtime)
    for (size_t i = 0; i < tries; ++i)
    {
      double x = rand(gen);
      double y = rand(gen);
      if (isInCircle(x, y, r))
      {
        ++in;
      }
    }
  }
  double area = 2.0 * 2.0 * r * r * in / tries;
  return area;
}
