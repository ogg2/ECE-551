#include "circle.hpp"
#include <cmath>
#include <cstdio>

void Circle::move (double dx, double dy) {
  point.Point::move (dx, dy);  
}

double Circle::intersectionArea (const Circle & otherCircle) {
  double d = point.Point::distanceFrom (otherCircle.point);
  double r1 = radius;
  double r2 = otherCircle.radius;
  if (r1 == 0 || r2 == 0) {
    return 0;
  }
  if (d == 0) {
    if (r1 < r2) {
      return pow (r1, 2) * M_PI;
    } else {
      return pow (r2, 2) * M_PI;
    }
  }
  if (d + fmin (r1, r2) < fmax (r1, r2)) {
    return fmin (pow (r1, 2) * M_PI, pow (r2, 2) * M_PI);
  }

  double cos1 = acos((pow(d, 2) + pow(r1, 2) - pow(r2, 2)) / (2 * d * r1));
  double cos2 = acos((pow(d, 2) - pow(r1, 2) + pow(r2, 2)) / (2 * d * r2));
  double sqroot = sqrt ((d + r1 - r2) * (d - r1 + r2) * (-d + r1 + r2) * (d + r1 + r2));

  return pow (r1, 2) * cos1 + pow (r2, 2) * cos2 - 0.5 * sqroot;
}
