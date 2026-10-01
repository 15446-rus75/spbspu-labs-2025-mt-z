#include "calc.hpp"

long long int abramov::sumArr(int *arr, size_t size)
{
  long long int sum = 0;
  for (size_t i = 0; i < size; ++i)
  {
    sum += arr[i];
  }
  return sum;
}
