#include "fill.hpp"
#include <thread>
#include <vector>

namespace
{
  void partialFillArr(int *arr, size_t begin, size_t end, int seed)
  {
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution< int > dis(-1000000, 1000000);
    for (size_t i = begin; i < end; ++i)
    {
      arr[i] = dis(gen);
    }
  }
}

void abramov::fillArr(int *arr, size_t size, int seed, size_t number)
{
  std::vector< std::jthread > ths;
  ths.reserve(number);
  size_t per_th = size / number;
  size_t index = 0;
  size_t i = 0;
  for (; i < number - 1; ++i)
  {
    ths.emplace_back(partialFillArr, arr, index, index + per_th, seed + i + 1);
    index += per_th;
  }
  partialFillArr(arr, index, size, seed);
}
