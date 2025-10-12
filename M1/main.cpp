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

  while (std::cin)
  {
    int r = 0;
    std::cin >> r;
    if (std::cin.eof())
    {
      return 0;
    }
    std::cout << std::setprecision(3) << std::fixed;
    try
    {
      std::cout << getArea(r, tries, seed) << '\n';
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what();
      return 2;
    }
  }
}
