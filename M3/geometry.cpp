#include "geometry.hpp"
#include <stdexcept>

abramov::Point::Point(int xcoord, int ycoord):
  x(xcoord),
  y(ycoord)
{}

int abramov::Point::getX() const noexcept
{
  return x;
}

int abramov::Point::getY() const noexcept
{
  return y;
}

void abramov::Point::print(std::ostream &out) const
{
  out << '(' << x << ' ' << y << ')';
}

abramov::FrameRect::FrameRect(const Point &point1, const Point &point2):
  p1(point1),
  p2(point2)
{
  if (p1.getX() >= p2.getX() || p1.getY() >= p2.getY())
  {
    throw std::logic_error("Invalid points");
  }
}

abramov::Point abramov::FrameRect::getMinPoint() const
{
  return p1;
}

abramov::Point abramov::FrameRect::getMaxPoint() const
{
  return p2;
}

void abramov::FrameRect::print(std::ostream &out) const
{
  p1.print(out);
  out << ' ';
  p2.print(out);
}

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

abramov::FrameRect abramov::Circle::getFrameRect() const
{
  return FrameRect(Point(x - r, y - r), Point(x + r, y + r));
}

std::ostream &abramov::Circle::printInfo(std::ostream &out) const noexcept
{
  out << r << ' ' << '(' << x << ' ' << y << ')';
  return out;
}

abramov::Ellipse::Ellipse(int rad_x, int rad_y, int xcoord, int ycoord):
  r_x(rad_x),
  r_y(rad_y),
  x(xcoord),
  y(ycoord)
{
  if (r_x <= 0 || r_y <= 0)
  {
    throw std::logic_error("Invalid radius");
  }
}

abramov::FrameRect abramov::Ellipse::getFrameRect() const
{
  return FrameRect(Point(x - r_x, y - r_y), Point(x + r_x, y + r_y));
}

std::ostream &abramov::Ellipse::printInfo(std::ostream &out) const noexcept
{
  out << r_x << ' ' << r_y << ' ' << '(' << x << ' ' << y << ')';
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
    throw std::logic_error("Figure already exists");
  }
  shapes.insert({ name, shape });
}

abramov::Shape *abramov::ShapeCollection::getShape(const std::string &name)
{
  auto it = shapes.find(name);
  if (it == shapes.end())
  {
    throw std::logic_error("There is no such figure");
  }
  return it->second;
}

void abramov::ShapeCollection::printShapeInfo(const std::string &name, std::ostream &out) const
{
  auto it = shapes.find(name);
  if (it == shapes.end())
  {
    throw std::logic_error("There is no such shape");
  }
  it->second->printInfo(out);
}

void abramov::ShapeCollection::printShapeFrameRect(const std::string &name, std::ostream &out) const
{
  auto it = shapes.find(name);
  if (it == shapes.end())
  {
    throw std::logic_error("There is no such shape");
  }
  FrameRect rect = it->second->getFrameRect();
  rect.print(out);
}

abramov::ShapeSet::ShapeSet(abramov::ShapeCollection &col):
  collect(col),
  shapes(std::unordered_map< std::string, Shape* >{})
{}

void abramov::ShapeSet::addShape(const std::string &name, Shape *shape)
{
  if (shapes.find(name) != shapes.end())
  {
    throw std::logic_error("Figure already exists");
  }
  shapes.insert({ name, shape });
}

void abramov::ShapeSet::printShapesInfo(std::ostream &out) const
{
  auto it = shapes.begin();
  while (it != shapes.end())
  {
    it->second->printInfo();
    out << '\n';
    ++it;
  }
}

abramov::FrameRect abramov::ShapeSet::getFrameRect() const
{
  int x_min = 0;
  int x_max = 0;
  int y_min = 0;
  int y_max = 0;
  auto it = shapes.begin();
  while (it != shapes.end())
  {
    FrameRect rect = it->second->getFrameRect();
    x_min = std::min(x_min, rect.getMinPoint().getX());
    y_min = std::min(y_min, rect.getMinPoint().getY());
    x_max = std::max(x_max, rect.getMaxPoint().getX());
    y_max = std::max(y_max, rect.getMaxPoint().getY());
    ++it;
  }
  return FrameRect(Point(x_min, y_min), Point(x_max, y_max));
}

void abramov::SetCollection::addSet(const std::string &name, const ShapeSet &set)
{
  if (sets.find(name) != sets.end())
  {
    throw std::logic_error("Set already exists");
  }
  sets.insert({ name, set });
}

void abramov::SetCollection::printSet(const std::string &name, std::ostream &out) const
{
  auto it = sets.find(name);
  if (it == sets.end())
  {
    throw std::logic_error("There is no such set");
  }
  it->second.printShapesInfo(out);
}

void abramov::SetCollection::printSetFrameRect(const std::string &name, std::ostream &out) const
{
  auto it = sets.find(name);
  if (it == sets.end())
  {
    throw std::logic_error("There is no such set");
  }
  FrameRect rect = it->second.getFrameRect();
  rect.print(out);
}
