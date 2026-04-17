#include <iostream>

int main(int argc, char **argv)
{
  long long int tries = 0;
  long long int seed = 0;
  if (argc >= 2 && argc <= 3)
  {
    try
    {
      tries = std::stoll(argv[1]);
      if (argc == 3)
      {
        seed = std::stoll(argv[2]);
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      return 1;
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
}
