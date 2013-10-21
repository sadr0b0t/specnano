#include "point2d.h"

Point2D::Point2D(double _x, double _y)
{
    x=_x; y=_y;
}

Point2D::Point2D()
{
    x=0.0; y=0.0;
}

bool Point2D::isOneLevel(Point2D p, double rank)
{
    int p1_y = (int) (y * (2 / rank));
    int p2_y = (int) (p.y * (2 / rank));

    if(p1_y == p2_y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Point2D::isBiggerCorner(const Point2D p) const
{
    // ATAN RETURNS +- PI/2 WHEN X == 0

    double MyCorner, OtherCorner;

    if(x == 0)
    {
        MyCorner = M_PI / 2;
    }
    else
    {
        MyCorner = atan(y/x);

        if(x < 0 || MyCorner < 0)
        {
            MyCorner += M_PI;
        }
        if(y == 0)
        {
            if(x > 0)
            {
                MyCorner = 0;
            }
            if(x < 0)
            {
                MyCorner = M_PI;
            }
        }
    }

    if(p.x == 0)
    {
        OtherCorner = M_PI / 2;
    }
    else
    {
        OtherCorner = atan(p.y/p.x);

        if(p.x < 0 || OtherCorner < 0)
        {
            OtherCorner += M_PI;
        }
        if(p.y == 0)
        {
            if(y == 0)
            {
                if(p.x > x)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            if(p.x > 0)
            {
                OtherCorner = 0;
            }
            if(p.x < 0)
            {
                OtherCorner = M_PI;
            }
        }
    }

    return MyCorner > OtherCorner;
}

void Point2D::getRounded(double rank)
{
    x=round(x/rank)*rank;
    y=round(y/rank)*rank;
}

bool Point2D::isEqual(Point2D p)
{
    if(x==p.x && y==p.y)
        return true;
    return false;
}

bool Point2D::isEqual2(Point2D p)
{
    int p_x=(int) p.x*1000;
    int p_y=(int) p.y*1000;
    int _x=(int) x*1000;
    int _y=(int) y*1000;
    if(p_x==_x && p_y==_y)
        return true;
    return false;
}
