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

omp_sched_t abramov::Config::getSchedule() const
{
  if (schedule == "static")
  {
    return omp_sched_static;
  }
  if (schedule == "dynamic")
  {
    return omp_sched_dynamic;
  }
  if (schedule == "guided")
  {
    return omp_sched_guided;
  }
  return omp_sched_auto;
}

size_t abramov::Config::getChunk() const noexcept
{
  return chunk;
}

void abramov::setSchedule(const Config &con)
{
  omp_set_schedule(con.getSchedule(), con.getChunk());
}

void abramov::showSchedule(const Config &con)
{
  std::cout << con.getSchedule() << ' ' << con.getChunk() << '\n';
}

abramov::AreaConfig::AreaConfig(int radius, long long int tr, long long int s, int t):
  r(radius),
  tries(tr),
  seed(s),
  ths(t)
{
  if (r <= 0 || tr <= 0 || s < 0 || t < 0)
  {
    throw std::logic_error("R, tries, seed, threads must be positive\n");
  }
}

int abramov::AreaConfig::getR() const noexcept
{
  return r;
}

long long int abramov::AreaConfig::getTries() const noexcept
{
  return tries;
}

long long int abramov::AreaConfig::getSeed() const noexcept
{
  return seed;
}

int abramov::AreaConfig::getThs() const noexcept
{
  return ths;
}
