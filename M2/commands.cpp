#include "commands.hpp"

void abramov::getCommands(std::map< std::string, std::function< void() > > &commands, Config &con, AreaConfig &area)
{
  commands["set-schedule"] = std::bind(readSetSchedule, std::ref(con));
  commands["show-schedule"] = std::bind(showSchedule, std::cref(con));
  commands["area-of"] = std::bind(printAreaOf, std::ref(area));
}
