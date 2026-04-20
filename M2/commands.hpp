#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>
#include <functional>

#include "io_utils.hpp"

namespace abramov
{
  void getCommands(std::map< std::string, std::function< void() > > &commands, Config &con, AreaConfig &areacon);
}

#endif
