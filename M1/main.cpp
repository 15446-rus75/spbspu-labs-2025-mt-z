#include <random>
#include <iomanip>
#include <iostream>

bool isInCircle(double x, double y, int r)
{
  return std::sqrt(x * x + y * y) - r < 0;
}

double getArea(int r, long long int tries, long long int seed)
{
  if (r <= 0)
  {
    throw std::logic_error("Radius must be positive");
  }
  std::mt19937 gen(seed);
  std::uniform_real_distribution< double > rand(0, r);
  size_t in = 0;
  size_t all = 0;
  for (size_t i = 0; i < tries; ++i)
  {
    double x = rand(gen);
    double y = rand(gen);
    if (isInCircle(x, y, r))
    {
      ++in;
    }
    ++all;
  }
  double area = 2.0 * r * 2.0 * r * in / all;
  return area;
}

int main(int argc, char**argv)
{
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
