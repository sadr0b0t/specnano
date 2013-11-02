#ifndef POINT2D_H
#define POINT2D_H

#include"qmath.h"

//const double PI = 3.1415926535897932384626433832795;

class Point2D
{
public:
    Point2D(float _x, float _y);
    Point2D();
    bool isEqual(Point2D p);
    bool isEqual2(Point2D p);
    bool isBiggerCorner(const Point2D p) const;
    bool isOneLevel(Point2D p, double rank);

    void getRounded(double rank);

    float x;
    float y;
};

#endif // POINT2D_H
