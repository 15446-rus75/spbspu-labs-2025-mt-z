#include "process_manager.hpp"
#include <stdexcept>

abramov::Process::Process(const std::string &s, long long int seed_gen):
  name(s),
  seed(seed_gen)
{}

void abramov::Process::setArea(const std::string &n, double res)
{
  areas[n] = res;
}

double abramov::Process::getArea(const std::string &n) const
{
  return areas.at(n);
}

long long int abramov::Process::getSeed() const noexcept
{
  return seed;
}

void abramov::ProcessManager::spawnProcess(const std::string &name, long long int s)
{
  if (collect.find(name) != collect.end())
  {
    throw std::logic_error("Such process already exists");
  }
  collect.insert({ name, Process(name, s) });
}

void abramov::ProcessManager::setCalcArea(const std::string &proc_name, const std::string &calc_name, double res)
{
  auto it = collect.find(proc_name);
  if (it == collect.end())
  {
    throw std::logic_error("There is no such process");
  }
  it->second.setArea(calc_name, res);
}

double abramov::ProcessManager::getCalcArea(const std::string &calc_name) const
{
  double area = 0;
  for (auto it = collect.begin(); it != collect.end(); ++it)
  {
    try
    {
      area = it->second.getArea(calc_name);
    }
    catch (const std::exception &e)
    {}
  }
  return area;
}

long long int abramov::ProcessManager::getProcessSeed(const std::string &proc_name) const
{
  auto it = collect.find(proc_name);
  if (it == collect.end())
  {
    throw std::logic_error("There is no such process");
  }
  return it->second.getSeed();

}
