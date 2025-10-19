#include "geometry.hpp"

abramov::Circle::Circle(const std::string &s, int rad, int xcoord, int ycoord):
  name(s),
  r(rad),
  x(xcoord),
  y(ycoord)
{}

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
