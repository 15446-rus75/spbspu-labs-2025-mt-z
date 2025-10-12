#include <chrono>
#include <limits>
#include <iomanip>
#include <iostream>
#include "math_utils.hpp"

int main(int argc, char**argv)
{
  using namespace abramov;

  long long int tries = 0;
  long long int seed = 0;
  if (argc >= 2 && argc <= 3)
  {
    tries = std::stoll(argv[1]);
    if (argc == 3)
    {
      seed = std::stoll(argv[2]);
    }
  }
  else
  {
    std::cerr << "Wrong num of parameters\n";
    return 1;
  }
  if (tries <= 0)
  {
    std::cerr << "Number of tries must be positive\n";
    return 1;
  }
  if (seed < 0)
  {
    std::cerr << "Seed must be positive\n";
    return 1;
  }

  std::cout << std::setprecision(3) << std::fixed;
  while (std::cin)
  {
    int r = 0;
    unsigned int number = 0;
    std::cin >> r >> number;
    if (std::cin.eof())
    {
      return 0;
    }
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    try
    {
      auto start = std::chrono::high_resolution_clock::now();
      double res = getArea(r, tries, seed, number);
      auto end = std::chrono::high_resolution_clock::now();
      auto time = std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count();
      std::cout << res << ' ' << time <<  '\n';
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what();
      return 2;
    }
  }
}
