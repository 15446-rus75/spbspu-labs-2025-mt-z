#include "commands.hpp"

void abramov::getCommands(std::map< std::string, std::function< void() > > &commands, abramov::ShapeCollection &collect)
{
  commands["circle"] = std::bind(abramov::addCircle, std::ref(collect), std::ref(std::cin));
  commands["show"] = std::bind(abramov::showShape, std::cref(collect), std::ref(std::cin), std::ref(std::cout));
}
