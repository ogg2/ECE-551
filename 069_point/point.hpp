#ifndef __CODE_HPP__
#define __CODE_HPP__

class Point {
  private:
    double x;
    double y;
  public:
    Point () : x(0.0), y(0.0) {
    }
    void move (double dx, double dy);
    double distanceFrom (const Point & p);
};

#endif
