#ifndef IO_UTILS_HPP
#define IO_UTILS_HPP
#include <iostream>
#include "geometry.hpp"

namespace abramov
{
  void addCircle(ShapeCollection &collect, std::istream &in = std::cin);
  void showShape(const ShapeCollection &collect, std::istream &in = std::cin, std::ostream &out = std::cout);
}
#endif
