#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <string>
#include <unordered_map>
#include "shape.hpp"

namespace abramov
{
  struct Point
  {
    Point(double xcoord, double ycoord);
    double getX() const noexcept;
    double getY() const noexcept;
    void print(std::ostream &out = std::cout) const;
  private:
    double x;
    double y;
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
    Circle(double rad, double xcoord, double ycoord);
    ~Circle() override = default;
    FrameRect getFrameRect() const;
    void rotate(double ksi) override;
    std::ostream &printInfo(std::ostream &out = std::cout) const noexcept override;
  private:
    double r;
    double x;
    double y;
  };

  struct Ellipse final: Shape
  {
    Ellipse(double rad_x, double rad_y, double xcoord, double ycoord);
    ~Ellipse() override = default;
    FrameRect getFrameRect() const;
    void rotate(double ksi) override;
    std::ostream &printInfo(std::ostream &out = std::cout) const noexcept override;
  private:
    double r_x;
    double r_y;
    double x;
    double y;
    Point p1;
    Point p2;
    double angle;
  };

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
