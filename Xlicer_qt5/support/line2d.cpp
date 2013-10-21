#include "line2d.h"

Line2D::Line2D()
{
    vertexes=new Point2D[2];
}

Line2D::Line2D(Point2D v1, Point2D v2)
{
    vertexes=new Point2D[2];
    vertexes[0]=v1;
    vertexes[1]=v2;
}

bool Line2D::isEqual(Line2D l)
{
    if(vertexes[0].isEqual(l.vertexes[0]) && vertexes[1].isEqual(l.vertexes[1]))
        return true;
    return false;
}

Line2D Line2D::getReversed()
{
    Line2D tmp;
    tmp.vertexes[0]=vertexes[1];
    tmp.vertexes[1]=vertexes[0];
    return tmp;
}

void Line2D::getRounded(double rank)
{
    vertexes[0].getRounded(rank);
    vertexes[1].getRounded(rank);
}

bool Line2D::isEqual2(Line2D l)
{
    if(vertexes[0].isEqual2(l.vertexes[0]) && vertexes[1].isEqual2(l.vertexes[1]))
        return true;
    return false;
}
