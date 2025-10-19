#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <map>
#include <functional>
#include "io_utils.hpp"

namespace abramov
{
  void getCommands(std::map< std::string, std::function< void() > > &commands, ShapeCollection &collect, SetCollection &sets);
}
#endif
