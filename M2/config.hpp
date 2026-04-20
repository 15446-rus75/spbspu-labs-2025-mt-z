#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <string>
#include <stdexcept>
#include <omp.h>

namespace abramov
{
  struct Config
  {
    Config();
    Config(const std::string &sch, size_t ch);
    omp_sched_t getSchedule() const;
    std::string getStringSchedule() const;
    size_t getChunk() const noexcept;
  private:
    std::string schedule;
    size_t chunk;
  };

  void setSchedule(const Config &con);
  void showSchedule(const Config &con);

  struct AreaConfig
  {
    AreaConfig();
    AreaConfig(int radius, long long int tr, long long int s, int t);
    int getR() const noexcept;
    long long int getTries() const noexcept;
    long long int getSeed() const noexcept;
    int getThs() const noexcept;
  private:
    int r;
    long long int tries;
    long long int seed;
    int ths;
  };
}

#endif
