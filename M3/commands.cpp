#include "commands.hpp"

void abramov::getCommands(std::map< std::string, std::function< void() > > &commands, ShapeCollection &collect, SetCollection &sets)
{
  commands["circle"] = std::bind(abramov::addCircle, std::ref(collect), std::ref(std::cin));
  commands["show"] = std::bind(abramov::showShape, std::cref(collect), std::ref(std::cin), std::ref(std::cout));
  commands["set"] = std::bind(abramov::addSet, std::ref(collect), std::ref(sets), std::ref(std::cin));
  commands["showset"] = std::bind(abramov::showSet, std::cref(sets), std::ref(std::cin), std::ref(std::cout));
}
