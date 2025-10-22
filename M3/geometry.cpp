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

double abramov::FrameRect::getArea() const
{
  return (p2.getX() - p1.getX()) * (p2.getY() - p1.getY());
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

bool abramov::Circle::isPointIn(const Point &p) const
{
  return std::sqrt((x - p.getX()) * (x - p.getX()) + (y - p.getY()) * (y - p.getY())) - r < 0;
}

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
    if (new_y1 < new_y2)
    {
      p1 = Point(new_x1, new_y1);
      p2 = Point(new_x2, new_y2);
    }
    else
    {
      p1 = Point(new_x1, new_y2);
      p2 = Point(new_x2, new_y1);
    }
  }
  else
  {
    if (new_y1 < new_y2)
    {
      p1 = Point(new_x2, new_y1);
      p2 = Point(new_x1, new_y2);
    }
    else
    {
      p1 = Point(new_x2, new_y2);
      p2 = Point(new_x1, new_y1);
    }
  }
  angle += ksi;
}

bool abramov::Ellipse::isPointIn(const Point &p) const
{
  return (((x - p.getX()) * (x - p.getX())) / (r_x * r_x) + (y - p.getY()) * (y - p.getY()) / (r_y * r_y)) <= 1;
}

std::ostream &abramov::Ellipse::printInfo(std::ostream &out) const noexcept
{
  out << r_x << ' ' << r_y << ' ' << '(' << x << ' ' << y << ')' << ' ' << std::setprecision(3) << angle;
  return out;
}

