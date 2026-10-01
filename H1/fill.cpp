#include "fill.hpp"

void abramov::fillArr(int *arr, size_t size, int seed)
{
  std::mt19937_64 gen(seed);
  std::uniform_int_distribution< int > dis(0, 1000000);
  for (size_t i = 0; i < size; ++i)
  {
    arr[i] = dis(gen);
  }
}
