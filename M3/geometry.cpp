#include "geometry.hpp"
#include <stdexcept>

abramov::Circle::Circle(int rad, int xcoord, int ycoord):
  r(rad),
  x(xcoord),
  y(ycoord)
{
  if (r <= 0)
  {
    throw std::logic_error("Radius must be positive");
  }
}

int abramov::Circle::getRadius() const noexcept
{
  return r;
}

int abramov::Circle::getX() const noexcept
{
  return x;
}

int abramov::Circle::getY() const noexcept
{
  return y;
}

std::ostream &abramov::Circle::printInfo(std::ostream &out) const noexcept
{
  out << r << ' ' << '(' << x << ' ' << y << ')';
  return out;
}

abramov::ShapeCollection::~ShapeCollection()
{
  auto it = shapes.begin();
  while (it != shapes.end())
  {
    delete it->second;
    ++it;
  }
}

void abramov::ShapeCollection::addShape(const std::string &name, Shape* shape)
{
  if (shapes.find(name) != shapes.end())
  {
    throw std::logic_error("Figure already exists\n");
  }
  shapes.insert({ name, shape });
}

void abramov::ShapeCollection::printShapeInfo(const std::string &name, std::ostream &out) const
{
  auto it = shapes.find(name);
  if (it == shapes.end())
  {
    throw std::logic_error("There is no such shape\n");
  }
  it->second->printInfo(out);
}
