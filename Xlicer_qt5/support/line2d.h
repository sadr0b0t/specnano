#ifndef LINE2D_H
#define LINE2D_H

#include"point2d.h"

class Line2D
{
public:
    Line2D();
    //~Line2D();
    Line2D(Point2D v1, Point2D v2);
    bool isEqual(Line2D l);
    bool isEqual2(Line2D l);
    Line2D getReversed();
    void getRounded(double rank);

    Point2D vertexes_p1;
    Point2D vertexes_p2;
};

#endif // LINE2D_H
