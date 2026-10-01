#include "calc.hpp"
#include <vector>
#include <thread>
#include <numeric>

namespace
{
  void partialsumArr(const int *arr, size_t begin, size_t end, std::vector< long long int >::iterator it)
  {
    long long int sum = 0;
    for (size_t i = begin; i < end; ++i)
    {
      sum += arr[i];
    }
    *it = sum;
  }
}

long long int abramov::sumArr(int *arr, size_t size, size_t number)
{
  std::vector< long long int > sums(number, 0);
  {
    std::vector< std::jthread > ths;
    ths.reserve(number);
    size_t per_th = size / number;
    size_t index = 0;
    for (size_t i = 0; i < number - 1; ++i)
    {
      ths.emplace_back(partialsumArr, arr, index, index + per_th, sums.begin() + i);
      index += per_th;
    }
    partialsumArr(arr, index, size, sums.begin() + number - 1);
  }
  return std::accumulate(sums.begin(), sums.begin() + number, 0LL);
}
