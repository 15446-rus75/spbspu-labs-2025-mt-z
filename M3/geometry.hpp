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
    bool isPointIn(const Point &p) const;
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
    bool isPointIn(const Point &p) const;
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
}
#endif
