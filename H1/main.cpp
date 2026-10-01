#include <iostream>
#include "calc.hpp"
#include "fill.hpp"

int main()
{
  using namespace abramov;

  constexpr size_t k = 2000000;
  //constexpr size_t k = 2000000000;
  int *ptr = new int[k];
  fillArr(ptr, k, 100);
  for (size_t i = 0; i < 10; ++i)
  {
    std::cout << ptr[i] << ' ';
  }
  std::cout << '\n';
  std::cout << "sum = " << sumArr(ptr, k) << '\n';
}
