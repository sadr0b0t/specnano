#include "line2d.h"

Line2D::Line2D()
{
}

Line2D::Line2D(Point2D v1, Point2D v2)
{
    vertexes_p1 = v1;
    vertexes_p2 = v2;
}

//Line2D::~Line2D()
//{
//    delete vertexes;
//}

bool Line2D::isEqual(Line2D l)
{
    if(vertexes_p1.isEqual(l.vertexes_p1) && vertexes_p2.isEqual(l.vertexes_p2))
        return true;
    return false;
}

Line2D Line2D::getReversed()
{
    Line2D tmp;
    tmp.vertexes_p1 = vertexes_p2;
    tmp.vertexes_p2 = vertexes_p1;
    return tmp;
}

void Line2D::getRounded(double rank)
{
    vertexes_p1.getRounded(rank);
    vertexes_p2.getRounded(rank);
}

bool Line2D::isEqual2(Line2D l)
{
    if(vertexes_p1.isEqual2(l.vertexes_p1) && vertexes_p2.isEqual2(l.vertexes_p2))
        return true;
    return false;
}
