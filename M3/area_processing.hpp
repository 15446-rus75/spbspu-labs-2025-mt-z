#ifndef AREA_PROCESSING_HPP
#define AREA_PROCESSING_HPP
#include "collections.hpp"

namespace abramov
{
  double getSetArea(const ShapeSet &set, size_t threads, size_t tries, long long int seed = 0);
}

#endif
