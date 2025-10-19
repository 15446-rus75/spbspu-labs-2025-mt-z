#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <string>
#include <iostream>

namespace abramov
{
  struct Circle
  {
    Circle(const std::string &s, int rad, int xcoord, int ycoord);
    int getRadius() const noexcept;
    int getX() const noexcept;
    int getY() const noexcept;
    std::ostream &printInfo(std::ostream &out = std::cout) const noexcept;
  private:
    std::string name;
    int r;
    int x;
    int y;
  };
}
#endif
