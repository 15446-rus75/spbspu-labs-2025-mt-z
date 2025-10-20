#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>

namespace abramov
{
  struct FrameRect;

  struct Shape
  {
    virtual ~Shape() = default;
    virtual std::ostream &printInfo(std::ostream &out = std::cout) const noexcept = 0;
    virtual FrameRect getFrameRect() const = 0;
  };
}

#endif
