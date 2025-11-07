#include "commands.hpp"

void abramov::getCommands(std::map< std::string, std::function< void() > > &commands, ShapeCollection &collect, SetCollection &sets, ProcessManager &man)
{
  commands["circle"] = std::bind(addCircle, std::ref(collect), std::ref(std::cin));
  commands["ellipse"] = std::bind(addEllipse, std::ref(collect), std::ref(std::cin));
  commands["set"] = std::bind(addSet, std::ref(collect), std::ref(sets), std::ref(std::cin));
  commands["show"] = std::bind(showShape, std::cref(collect), std::ref(std::cin), std::ref(std::cout));
  commands["showset"] = std::bind(showSet, std::cref(sets), std::ref(std::cin), std::ref(std::cout));
  commands["frame"] = std::bind(printFrame, std::cref(collect), std::ref(std::cin), std::ref(std::cout));
  commands["frameset"] = std::bind(printSetFrame, std::cref(sets), std::ref(std::cin), std::ref(std::cout));
  commands["spawn"] = std::bind(spawnProcess, std::ref(man), std::ref(std::cin));
  commands["area-on"] = std::bind(computeSetArea, std::cref(sets), std::ref(man), std::ref(std::cin));
  commands["status"] = std::bind(showCalcStatus, std::cref(man), std::ref(std::cin), std::ref(std::cout));
  commands["rotate"] = std::bind(rotateShape, std::ref(collect), std::ref(std::cin));
}
