#include "config.hpp"

abramov::Config::Config():
  schedule("static"),
  chunk(1)
{}

abramov::Config::Config(const std::string &sch, size_t ch):
  schedule(sch),
  chunk(ch)
{
  if (sch != "static" && sch != "dynamic" && sch != "guided" && sch != "auto")
  {
    throw std::logic_error("Schedule must be static/dynamic/guided/auto");
  }
  if (chunk == 0)
  {
    throw std::logic_error("Chunk must be positive\n");
  }
}

std::string abramov::Config::getSchedule() const
{
  return schedule;
}

size_t abramov::Config::getChunk() const noexcept
{
  return chunk;
}
