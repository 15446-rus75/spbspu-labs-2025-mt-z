#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <string>
#include <stdexcept>

namespace abramov
{
  struct Config
  {
    Config();
    Config(const std::string &sch, size_t ch);
    std::string getSchedule() const;
    size_t getChunk() const noexcept;
  private:
    std::string schedule;
    size_t chunk;
  };
}

#endif
