#include <limits>
#include <string>
#include <cstring>
#include <iostream>
#include "commands.hpp"

int main(int argc, char **argv)
{
  using namespace abramov;

  long long int tries = 0;
  long long int seed = 0;
  std::string schedule;
  size_t chunk;
  Config config;

  if (argc >= 4 && argc <= 5)
  {
    try
    {
      tries = std::stoll(argv[1]);
      int index = 2;
      if (argc == 5)
      {
        index = 3;
        seed = std::stoll(argv[2]);
        if (seed < 0)
        {
          std::cerr << "Seed must be positive\n";
          return 1;
        }
      }
      if (std::strstr(argv[index], "--schedule="))
      {
        char schedule_temp[10];
        std::strcpy(schedule_temp, std::strstr(argv[index], "=") + 1);
        schedule = schedule_temp;
      }
      else
      {
        std::cerr << "--schedule is not found\n";
        return 1;
      }
      if (std::strstr(argv[++index], "--chunk-size="))
      {
        char chunk_temp[10];
        std::strcpy(chunk_temp, std::strstr(argv[index], "=") + 1);
        chunk = std::stoull(chunk_temp);
      }
      else
      {
        std::cerr << "--chunk-size is not found\n";
        return 1;
      }
      config = Config(schedule, chunk);
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

  AreaConfig areacon(1, tries, seed, 2);
  std::map< std::string, std::function< void() > > commands;
  getCommands(commands, config, areacon);

  std::string command;
  while (!(std::cin >> command).eof())
  {
    try
    {
      commands.at(command)();
    }
    catch (const std::exception &e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
