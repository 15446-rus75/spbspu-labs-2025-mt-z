#ifndef COLLECTIONS_HPP
#define COLLECTIONS_HPP
#include "geometry.hpp"

namespace abramov
{
  struct ShapeCollection
  {
    ~ShapeCollection();
    void addShape(const std::string &name, Shape *shape);
    Shape *getShape(const std::string &name);
    void printShapeInfo(const std::string &name, std::ostream &out = std::cout) const;
    void printShapeFrameRect(const std::string &name, std::ostream &out = std::cout) const;
    void rotateShape(const std::string &name, double ksi);
  private:
    std::unordered_map< std::string, Shape* > shapes;
  };

  struct ShapeSet
  {
    ShapeSet(ShapeCollection &collect);
    void addShape(const std::string &name, Shape *shape);
    void printShapesInfo(std::ostream &out = std::cout) const;
    FrameRect getFrameRect() const;
  private:
    ShapeCollection &collect;
    std::unordered_map< std::string, Shape* > shapes;
  };

  struct SetCollection
  {
    void addSet(const std::string &name, const ShapeSet &set);
    void printSet(const std::string &name, std::ostream &out = std::cout) const;
    void printSetFrameRect(const std::string &name, std::ostream &out = std::cout) const;
  private:
    std::unordered_map< std::string, ShapeSet > sets;
  };
}
#endif

