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
    ~ShapeCollection();
    void addShape(const std::string &name, Shape *shape);
    Shape *getShape(const std::string &name);
    void printShapeInfo(const std::string &n, std::ostream &out = std::cout) const;
  private:
    std::unordered_map< std::string, Shape* > shapes;
  };

  struct ShapeSet
  {
    ShapeSet(ShapeCollection &collect);
    void addShape(const std::string &name, Shape *shape);
    void printShapesInfo(std::ostream &out = std::cout) const;
  private:
    ShapeCollection &collect;
    std::unordered_map< std::string, Shape* > shapes;
  };

  struct SetCollection
  {
    void addSet(const std::string &name, const ShapeSet &set);
    void printSet(const std::string &name, std::ostream &out = std::cout) const;
  private:
    std::unordered_map< std::string, ShapeSet > sets;
  };
}
#endif
