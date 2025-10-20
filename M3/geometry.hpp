#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <string>
#include <unordered_map>
#include "shape.hpp"

namespace abramov
{
  struct Point
  {
    Point(int xcoord, int ycoord);
    int getX() const noexcept;
    int getY() const noexcept;
    void print(std::ostream &out = std::cout) const;
  private:
    int x;
    int y;
  };

  struct FrameRect
  {
    FrameRect(const Point &point1, const Point &point2);
    Point getMinPoint() const;
    Point getMaxPoint() const;
    void print(std::ostream &out = std::cout) const;
  private:
    Point p1;
    Point p2;
  };

  struct Circle final: Shape
  {
    Circle(int rad, int xcoord, int ycoord);
    ~Circle() override = default;
    FrameRect getFrameRect() const;
    std::ostream &printInfo(std::ostream &out = std::cout) const noexcept override;
  private:
    int r;
    int x;
    int y;
  };

  struct Ellipse final: Shape
  {
    Ellipse(int rad_x, int rad_y, int xcoord, int ycoord);
    ~Ellipse() override = default;
    FrameRect getFrameRect() const;
    std::ostream &printInfo(std::ostream &out = std::cout) const noexcept override;
  private:
    int r_x;
    int r_y;
    int x;
    int y;
  };

  struct ShapeCollection
  {
    ~ShapeCollection();
    void addShape(const std::string &name, Shape *shape);
    Shape *getShape(const std::string &name);
    void printShapeInfo(const std::string &name, std::ostream &out = std::cout) const;
    void printShapeFrameRect(const std::string &name, std::ostream &out = std::cout) const;
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
