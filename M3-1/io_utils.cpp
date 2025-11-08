#include "io_utils.hpp"
#include <unistd.h>

void abramov::addCircle(ShapeCollection &collect, std::istream &in)
{
  using namespace abramov;

  std::string name;
  int r = 0;
  int x = 0;
  int y = 0;
  in >> name >> r >> x >> y;
  if (!in)
  {
    throw std::logic_error("Wrong shape params");
  }
  Circle *shape = nullptr;
  try
  {
    shape = new Circle(r, x, y);
    collect.addShape(name, shape);
  }
  catch (const std::exception &)
  {
    delete shape;
    throw;
  }
}

void abramov::addEllipse(ShapeCollection &collect, std::istream &in)
{
  using namespace abramov;

  std::string name;
  int r_x = 0;
  int r_y = 0;
  int x = 0;
  int y = 0;
  in >> name >> r_x >> r_y >> x >> y;
  if (!in)
  {
    throw std::logic_error("Wrong shape params");
  }
  Ellipse *shape = nullptr;
  try
  {
    shape = new Ellipse(r_x, r_y, x, y);
    collect.addShape(name, shape);
  }
  catch (const std::exception &e)
  {
    delete shape;
    throw;
  }
}

void abramov::showShape(const ShapeCollection &collect, std::istream &in, std::ostream &out)
{
  std::string name;
  in >> name;
  collect.printShapeInfo(name, out);
  out << '\n';
}

void abramov::addSet(ShapeCollection &collect, SetCollection &sets, std::istream &in)
{
  using namespace abramov;

  std::string set_name;
  in >> set_name;
  int size = 0;
  in >> size;
  if (!in || size <= 0)
  {
    throw std::logic_error("Wrong set-size");
  }
  ShapeSet set(collect);
  std::string name;
  for (size_t i = 0; i < size; ++i)
  {
    in >> name;
    set.addShape(name, collect.getShape(name));
  }
  sets.addSet(set_name, set);
}

void abramov::showSet(const SetCollection &sets, std::istream &in, std::ostream &out)
{
  std::string name;
  in >> name;
  sets.printSet(name, out);
}

void abramov::printFrame(const ShapeCollection &collect, std::istream &in, std::ostream &out)
{
  std::string name;
  in >> name;
  collect.printShapeFrameRect(name, out);
  out << '\n';
}

void abramov::printSetFrame(const SetCollection &sets, std::istream &in, std::ostream &out)
{
  std::string name;
  in >> name;
  sets.printSetFrameRect(name, out);
  out << '\n';
}

void abramov::spawnProcess(ProcessManager &man, std::istream &in)
{
  std::string name;
  long long int seed = 0;
  in >> name >> seed;
  man.spawnProcess(name, seed);
}

void abramov::computeSetArea(const SetCollection &sets, ProcessManager &man, std::istream &in)
{
  std::string process_name;
  std::string calc_name;
  std::string set_name;
  size_t threads = 0;
  size_t tries = 0;
  in >> process_name >> calc_name >> set_name >> threads >> tries;

  long long int seed = man.getProcessSeed(process_name);

  int pipe_fds[2];
  if (pipe(pipe_fds) < 0)
  {
    throw std::runtime_error("Can not to create pipe");
  }

  pid_t pid = fork();
  if (pid < 0)
  {
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    throw std::runtime_error("Can not to create process");
  }

  if (pid == 0)
  {
    close(pipe_fds[0]);
    double area = 0;
    try
    {
      area = sets.getAreaOfSet(set_name, threads, tries, seed);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      exit(0);
    }
    int bytes = 0;
    while (bytes < sizeof(double))
    {
      if (int ret = write(pipe_fds[1], &area + bytes, sizeof(double)); ret < 0)
      {
        std::cerr << "Failed to calculate\n";
        break;
      }
      else
      {
        bytes += ret;
      }
    }
    close(pipe_fds[1]);
    exit(0);
  }
  else
  {
    close(pipe_fds[1]);
    double area = 0;
    int bytes = 0;
    while (bytes < sizeof(double))
    {
      if (int ret = read(pipe_fds[0], &area + bytes, sizeof(double)); ret < 0)
      {
        std::cerr << "Failed to calculate\n";
        break;
      }
      else
      {
        bytes += ret;
      }
    }
    close(pipe_fds[0]);
    man.setCalcArea(process_name, calc_name, area);
  }
}

void abramov::showCalcStatus(const ProcessManager &man, std::istream &in, std::ostream &out)
{
  std::string calc_name;
  in >> calc_name;
  double area = man.getCalcArea(calc_name);
  if (!area)
  {
    out << "Calc is in progress or does not exist" << '\n';
    return;
  }
  out << area << '\n';
}

void abramov::rotateShape(ShapeCollection &collect, std::istream &in)
{
  std::string name;
  double ksi;
  in >> name >> ksi;
  if (!in)
  {
    throw std::logic_error("Wrong params");
  }
  collect.rotateShape(name, ksi);
}
