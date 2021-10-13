#include "point.hpp"
#include <cmath>
#include <cstdio>

void Point::move (double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom (const Point & p) {
  double xDiff = x - p.x;
  double yDiff = y - p.y;

  return sqrt (pow(xDiff, 2) + pow(yDiff, 2));
}
