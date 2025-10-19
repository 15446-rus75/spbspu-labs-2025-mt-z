#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <string>
#include <unordered_map>
#include "shape.hpp"

namespace abramov
{
  struct Circle final: Shape
  {
    Circle(int rad, int xcoord, int ycoord);
    ~Circle() override = default;
    int getRadius() const noexcept;
    int getX() const noexcept;
    int getY() const noexcept;
    std::ostream &printInfo(std::ostream &out = std::cout) const noexcept override;
  private:
    int r;
    int x;
    int y;

    void swap(Circle &other) noexcept;
  };

  struct ShapeCollection
  {
    void addShape(const std::string &name, Shape *shape);
    void printShapeInfo(const std::string &n, std::ostream &out = std::cout) const;
  private:
    std::unordered_map< std::string, Shape* > shapes;
  };
}
#endif
