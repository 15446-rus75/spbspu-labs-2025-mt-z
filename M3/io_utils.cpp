#include "io_utils.hpp"

void abramov::addCircle(abramov::ShapeCollection &collect, std::istream &in)
{
  using namespace abramov;

  std::string name;
  int r = 0;
  int x = 0;
  int y = 0;
  in >> name >> r >> x >> y;
  if (!in)
  {
    throw std::logic_error("Wrong shape params\n");
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

void abramov::showShape(const ShapeCollection &collect, std::istream &in, std::ostream &out)
{
  std::string name;
  in >> name;
  collect.printShapeInfo(name, out);
  out << '\n';
}
