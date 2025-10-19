#include <limits>
#include "commands.hpp"

int main()
{
  using namespace abramov;

  ShapeCollection collection;
  std::map< std::string, std::function< void() > > commands;
  getCommands(commands, collection);

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
