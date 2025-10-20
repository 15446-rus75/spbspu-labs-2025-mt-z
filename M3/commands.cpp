#include "commands.hpp"

void abramov::getCommands(std::map< std::string, std::function< void() > > &commands, ShapeCollection &collect, SetCollection &sets)
{
  commands["circle"] = std::bind(abramov::addCircle, std::ref(collect), std::ref(std::cin));
  commands["set"] = std::bind(abramov::addSet, std::ref(collect), std::ref(sets), std::ref(std::cin));
  commands["show"] = std::bind(abramov::showShape, std::cref(collect), std::ref(std::cin), std::ref(std::cout));
  commands["showset"] = std::bind(showSet, std::cref(sets), std::ref(std::cin), std::ref(std::cout));
  commands["frame"] = std::bind(printFrame, std::cref(collect), std::ref(std::cin), std::ref(std::cout));
}
