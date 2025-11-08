#include "collections.hpp"
#include "area_processing.hpp"

abramov::ShapeCollection::~ShapeCollection()
{
  auto it = shapes.begin();
  while (it != shapes.end())
  {
    delete it->second;
    ++it;
  }
}

void abramov::ShapeCollection::addShape(const std::string &name, Shape* shape)
{
  if (shapes.find(name) != shapes.end())
  {
    throw std::logic_error("Figure already exists");
  }
  shapes.insert({ name, shape });
}

abramov::Shape *abramov::ShapeCollection::getShape(const std::string &name)
{
  auto it = shapes.find(name);
  if (it == shapes.end())
  {
    throw std::logic_error("There is no such figure");
  }
  return it->second;
}

void abramov::ShapeCollection::printShapeInfo(const std::string &name, std::ostream &out) const
{
  auto it = shapes.find(name);
  if (it == shapes.end())
  {
    throw std::logic_error("There is no such shape");
  }
  it->second->printInfo(out);
}

void abramov::ShapeCollection::printShapeFrameRect(const std::string &name, std::ostream &out) const
{
  auto it = shapes.find(name);
  if (it == shapes.end())
  {
    throw std::logic_error("There is no such shape");
  }
  FrameRect rect = it->second->getFrameRect();
  rect.print(out);
}

void abramov::ShapeCollection::rotateShape(const std::string &name, double ksi)
{
  auto it = shapes.find(name);
  if (it == shapes.end())
  {
    throw std::logic_error("There is no such shape");
  }
  it->second->rotate(ksi);
}

abramov::ShapeSet::ShapeSet(abramov::ShapeCollection &col):
  collect(col),
  shapes(std::unordered_map< std::string, Shape* >{})
{}

void abramov::ShapeSet::addShape(const std::string &name, Shape *shape)
{
  if (shapes.find(name) != shapes.end())
  {
    throw std::logic_error("Figure already exists");
  }
  shapes.insert({ name, shape });
}

void abramov::ShapeSet::printShapesInfo(std::ostream &out) const
{
  auto it = shapes.begin();
  while (it != shapes.end())
  {
    it->second->printInfo();
    out << '\n';
    ++it;
  }
}

abramov::FrameRect abramov::ShapeSet::getFrameRect() const
{
  double x_min = 0;
  double x_max = 0;
  double y_min = 0;
  double y_max = 0;
  auto it = shapes.begin();
  while (it != shapes.end())
  {
    FrameRect rect = it->second->getFrameRect();
    x_min = std::min(x_min, rect.getMinPoint().getX());
    y_min = std::min(y_min, rect.getMinPoint().getY());
    x_max = std::max(x_max, rect.getMaxPoint().getX());
    y_max = std::max(y_max, rect.getMaxPoint().getY());
    ++it;
  }
  return FrameRect(Point(x_min, y_min), Point(x_max, y_max));
}

bool abramov::ShapeSet::isPointIn(const Point &p) const
{
  auto it = shapes.begin();
  while (it != shapes.end())
  {
    if (it->second->isPointIn(p))
    {
      return true;
    }
    ++it;
  }
  return false;
}

void abramov::SetCollection::addSet(const std::string &name, const ShapeSet &set)
{
  if (sets.find(name) != sets.end())
  {
    throw std::logic_error("Set already exists");
  }
  sets.insert({ name, set });
}

double abramov::SetCollection::getAreaOfSet(const std::string &name, size_t threads, size_t tries, long long int seed) const
{
  auto it = sets.find(name);
  if (it == sets.end())
  {
    throw std::logic_error("There is no such set");
  }
  double area = getSetArea(it->second, threads, tries, seed);
  return area;
}

void abramov::SetCollection::printSet(const std::string &name, std::ostream &out) const
{
  auto it = sets.find(name);
  if (it == sets.end())
  {
    throw std::logic_error("There is no such set");
  }
  it->second.printShapesInfo(out);
}

void abramov::SetCollection::printSetFrameRect(const std::string &name, std::ostream &out) const
{
  auto it = sets.find(name);
  if (it == sets.end())
  {
    throw std::logic_error("There is no such set");
  }
  FrameRect rect = it->second.getFrameRect();
  rect.print(out);
}
