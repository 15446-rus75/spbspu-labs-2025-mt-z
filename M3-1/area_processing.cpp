#include "area_processing.hpp"
#include <random>
#include <thread>
#include <vector>

namespace
{
  using namespace abramov;
  using iterator = std::vector< size_t >::iterator;

  void getInAllPoints(const ShapeSet &set, size_t per_th, long long int seed, iterator it_in, iterator it_all)
  {

    size_t in = 0;
    size_t all = 0;
    FrameRect rect = set.getFrameRect();
    std::mt19937 gen(seed);
    std::uniform_real_distribution< double > randx(rect.getMinPoint().getX(), rect.getMaxPoint().getX());
    std::uniform_real_distribution< double > randy(rect.getMinPoint().getY(), rect.getMaxPoint().getY());
    for (size_t i = 0; i < per_th; ++i)
    {
      double x = randx(gen);
      double y = randy(gen);
      if (set.isPointIn(Point(x, y)))
      {
        ++in;
      }
      ++all;
    }
    *it_in = in;
    *it_all = all;
  }
}

double abramov::getSetArea(const ShapeSet &set, size_t threads, size_t tries, long long int seed)
{
  std::vector< std::thread > ths;
  ths.reserve(threads);
  std::vector< size_t > ins(threads, 0);
  std::vector< size_t > alls(threads, 0);
  size_t per_th = tries / threads;
  size_t i = 0;
  for (; i < threads - 1; ++i)
  {
    ths.emplace_back(getInAllPoints, set, per_th, seed, ins.begin() + i, alls.begin() + i);
  }
  getInAllPoints(set, per_th, seed, ins.begin() + i, alls.begin() + i);
  for (auto &&th: ths)
  {
    th.join();
  }
  size_t in = std::accumulate(ins.begin(), ins.end(), 0);
  size_t all = std::accumulate(alls.begin(), alls.end(), 0);
  double area = set.getFrameRect().getArea() * in / all;
  return area;
}
