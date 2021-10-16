#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "point.hpp"

class Circle {
  private:
    Point point;
    const double radius;
  public:
    Circle (Point p, double r) : point (p), radius (r) {
    }
    void move (double dx, double dy);
    double intersectionArea (const Circle & otherCircle);
};

#endif
