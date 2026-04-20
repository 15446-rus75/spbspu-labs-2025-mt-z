#include "io_utils.hpp"
#include "math_utils.hpp"

void abramov::readSetSchedule(Config &con)
{
  std::string schedule;
  size_t chunk = 0;
  std::cin >> schedule >> chunk;
  con = Config(schedule, chunk);
  setSchedule(con);
}

void abramov::printAreaOf(AreaConfig &areacon)
{
  int r = 0;
  int ths = 0;
  std::cin >> r >> ths;
  long long int seed = areacon.getSeed();
  long long int tries = areacon.getTries();
  areacon = AreaConfig(r, tries, seed, ths);
  std::cout << getArea(areacon) << '\n';
}
