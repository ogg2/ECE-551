#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
double Vector2D::getMagnitude() const {
  return std::sqrt (x * x + y * y);
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  double myX = x + rhs.x;
  double myY = y + rhs.y;
  Vector2D v;
  v.initVector (myX, myY);
  return v;
}
  
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x = x + rhs.x;
  y = y + rhs.y;
  return *this;
}

double Vector2D::dot (const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}

void Vector2D::print() const {
  std::printf ("<%.2f, %.2f>", x, y);
}
