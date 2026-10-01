#include <chrono>
#include <iostream>
#include "calc.hpp"
#include "fill.hpp"

int main()
{
  using namespace abramov;

  //constexpr size_t k = 2000000000;

  constexpr size_t k = 8000000;
  int seed = 100;
  size_t number = 1;
  int *arr = new int[k];

  std::cout << "Enter seed" << '\n';
  std::cin >> seed;
  fillArr(arr, k, seed, 16);

  while (number < 1025)
  {
    int times[5] = {};
    for (size_t i = 0; i < 4; ++i)
    {
      auto start = std::chrono::high_resolution_clock::now();
      sumArr(arr, k, number);
      auto end = std::chrono::high_resolution_clock::now();
      auto time = std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count();
      times[i] = std::chrono::duration< int >(time).count();
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "sum = " << sumArr(arr, k, number) << ' ' << "threads " << number << '\n';
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count();
    times[4] = std::chrono::duration< int >(time).count();
    std::cout << "time = " << mediana(times) << "ms" << '\n' << '\n';
    number *= 2;
  }

  delete[] arr;
}
