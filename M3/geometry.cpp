#include "geometry.hpp"
#include <cmath>
#include <iomanip>
#include <stdexcept>

abramov::Point::Point(double xcoord, double ycoord):
  x(xcoord),
  y(ycoord)
{}

double abramov::Point::getX() const noexcept
{
  return x;
}

double abramov::Point::getY() const noexcept
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

abramov::Circle::Circle(double rad, double xcoord, double ycoord):
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

void abramov::Circle::rotate(double ksi)
{}

std::ostream &abramov::Circle::printInfo(std::ostream &out) const noexcept
{
  out << r << ' ' << '(' << x << ' ' << y << ')';
  return out;
}

abramov::Ellipse::Ellipse(double rad_x, double rad_y, double xcoord, double ycoord):
  r_x(rad_x),
  r_y(rad_y),
  x(xcoord),
  y(ycoord),
  p1(xcoord - rad_x, ycoord - rad_y),
  p2(xcoord + rad_x, ycoord + rad_y),
  angle(0)
{
  if (r_x <= 0 || r_y <= 0)
  {
    throw std::logic_error("Invalid radius");
  }
}

abramov::FrameRect abramov::Ellipse::getFrameRect() const
{
  return FrameRect(p1, p2);
}

void abramov::Ellipse::rotate(double ksi)
{
  double x1 = p1.getX();
  double y1 = p1.getY();
  double x2 = p2.getX();
  double y2 = p2.getY();
  double new_x1 = (x1 - x) * std::cos(ksi) - (y1 - y) * std::sin(ksi) + x;
  double new_y1 = (x1 - x) * std::sin(ksi) + (y1 - y) * std::cos(ksi) + y;
  double new_x2 = (x2 - x) * std::cos(ksi) - (y2 - y) * std::sin(ksi) + x;
  double new_y2 = (x2 - x) * std::sin(ksi) + (y2 - y) * std::cos(ksi) + y;
  if (new_x1 < new_x2)
  {
    p1 = Point(new_x1, new_y1);
    p2 = Point(new_x2, new_y2);
  }
  else
  {
    p1 = Point(new_x2, new_y2);
    p2 = Point(new_x1, new_y1);
  }
  angle += ksi;
}

std::ostream &abramov::Ellipse::printInfo(std::ostream &out) const noexcept
{
  out << r_x << ' ' << r_y << ' ' << '(' << x << ' ' << y << ')' << ' ' << std::setprecision(3) << angle;
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

void abramov::ShapeCollection::rotateShape(const std::string &name, double ksi)
{
  auto it = shapes.find(name);
  if (it == shapes.end())
  {
    throw std::logic_error("There is no such shape");
  }
  it->second->rotate(ksi);
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
  double x_min = 0;
  double x_max = 0;
  double y_min = 0;
  double y_max = 0;
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
