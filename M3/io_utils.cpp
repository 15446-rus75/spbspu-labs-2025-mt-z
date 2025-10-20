#include "io_utils.hpp"

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
