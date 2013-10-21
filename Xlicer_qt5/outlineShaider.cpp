#include "outlineShaider.h"

OutlineShaider::OutlineShaider()
{
}

OutlineShaider::~OutlineShaider()
{
}

void OutlineShaider::setStream(QTextStream *stream)
{
    GCodeOutStream=stream;
}

void OutlineShaider::setSlice(QList<Point2D> _slice)
{
    slice = _slice;
}

double module(Point2D p1, Point2D p2)
{
    return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

double module(Point2D p1)
{
    return (sqrt(p1.x * p1.x + p1.y * p1.y));
}

Point2D OutlineShaider::shift_point(int id, int key, Point2D *shift_start)
{
    Point2D curr, next;
    Point2D shift(0,0);

    curr = slice.at(id);

    if(id < slice.size() - 1)
    {
        next = slice.at(id + 1);
    }
    else
    {
        next = slice.at(0);
        next.x -= shift_start->x;
        next.y -= shift_start->y;
    }

    next.x -= curr.x;
    next.y -= curr.y;

    double hipotenuse = module(next);
    double cos = 0;
    double sin = 0;

    if(next.x == 0)
    {
        if(next.y > 0)
        {
            shift.x = 1 * key;
            shift.y = 1 * key;
        }
        if(next.y < 0)
        {
            shift.x = -1 * key;
            shift.y = -1 * key;
        }

        curr.x += shift.x;
        curr.y += shift.y;
    }
    if(next.y == 0)
    {
        if(next.x > 0)
        {
            shift.x = 1 * key;
            shift.y = -1 * key;
        }
        if(next.x < 0)
        {
            shift.x = -1 * key;
            shift.y = 1 * key;
        }

        curr.x += shift.x;
        curr.y += shift.y;
    }
    if(next.x != 0 && next.y != 0)
    {
        cos = fabs(next.y) / hipotenuse;
        sin = fabs(next.x) / hipotenuse;

        if(next.x > 0 && next.y > 0)
        {
            shift.x = cos * key;
            curr.x += shift.x;
        }
        if(next.x < 0 && next.y > 0)
        {
            shift.y = sin * key;
            curr.y += shift.y;
        }
        if(next.x < 0 && next.y < 0)
        {
            shift.x = cos * key;
            curr.x -= shift.x;
        }
        if(next.x > 0 && next.y < 0)
        {
            shift.y = sin * key;
            curr.y -= shift.y;
        }
    }

    if(id == 0)
    {
        *shift_start = shift;
    }

    return curr;
}

QList<Point2D> OutlineShaider::edgeShading(double width, bool key, double Z, double F)
{
    Point2D *shift_start = new Point2D(0,0);
    int arg_shift;

    if(key)
    {
        arg_shift = 1;
    }
    else
    {
        arg_shift = -1;
    }

    *GCodeOutStream << "\t\tG00 X" << slice.at(0).x << " Y" << slice.at(0).y << " Z" << Z << " F" << F << "\r\n";

    for(int i = 1; i < slice.size(); i++)
    {
        *GCodeOutStream << "\t\tG01 X" << slice.at(i).x << " Y" << slice.at(i).y << " Z" << Z << " F" << F << "\r\n";
    }

    *GCodeOutStream << "\t\tG01 X" << slice.at(0).x << " Y" << slice.at(0).y << " Z" << Z << " F" << F << "\r\n";

    for(int i = 1; i < width * 10; i++)
    {
        slice.replace(0, shift_point(0, arg_shift, shift_start));
        *GCodeOutStream << "\t\tG00 X" << slice.at(0).x << " Y" << slice.at(0).y << " Z" << Z << " F" << F << "\r\n";

        for(int j = 1; j < slice.size(); j++)
        {
            slice.replace(j, shift_point(j, arg_shift, shift_start));
            *GCodeOutStream << "\t\tG01 X" << slice.at(j).x << " Y" << slice.at(j).y << " Z" << Z << " F" << F << "\r\n";
        }

        *GCodeOutStream << "\t\tG01 X" << slice.at(0).x << " Y" << slice.at(0).y << " Z" << Z << " F" << F << "\r\n";
    }

    delete shift_start;

    return slice;
}
