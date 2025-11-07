#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP
#include <string>
#include <unordered_map>


namespace abramov
{
  struct Process
  {
    Process(const std::string &s, long long int seed_gen);
    void setArea(const std::string &n, double res);
    double getArea(const std::string &n) const;
    long long int getSeed() const noexcept;
  private:
    std::string name;
    long long int seed;
    std::unordered_map< std::string, double > areas;
  };

  struct ProcessManager
  {
    void spawnProcess(const std::string &name, long long int seed);
    void setCalcArea(const std::string &proc_name, const std::string &calc_name, double res);
    double getCalcArea(const std::string &calc_name) const;
    long long int getProcessSeed(const std::string &proc_name) const;
  private:
    std::unordered_map< std::string, abramov::Process > collect;
  };
}

#endif
