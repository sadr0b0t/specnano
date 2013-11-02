#include "slicer.h"
#include <QMessageBox>
#include <QtAlgorithms>

Slicer::Slicer()
{
    height = 400;
    step_Z = 0.2;
    scale = 0.1;
    impulse = 3000;
    lineWidth = 0.1;

    drawOutline = false;
    drawInline = false;
    outsideOutline = false;
    insideOutline = false;
    slice = new QList<Point2D>();
    one_level = new QList<poid>();
    points = new QList<Point2D>();
    slice_byLine = new QList<Line2D>();
}

Slicer::~Slicer()
{
    delete slice_byLine;
    delete one_level;
    delete points;
    delete slice;
}

void Slicer::setFile(QString file)
{
    GCodeOut.setFileName(file);
    GCodeOut.remove();
    GCodeOut.open(QIODevice::Append);
    GCodeOutStream.setDevice(&GCodeOut);
}

bool Slicer::solveRelation(Point3D p1, Point3D p2, double z)
{
    if(p1.z == p2.z)
    {
        if(p1.z == z && p2.z == z)
        {
            Point2D p, pp;
            p.x = p1.x;
            p.y = p1.y;
            pp.x = p2.x;
            pp.y = p2.y;
//            res_l->append(Line2D(p, pp));
            return true;
        }
        else
        {
            return false;
        }
    }

    Point2D p;
    p.x = p1.x + (z - p1.z) * (p2.x - p1.x) / (p2.z - p1.z);
    p.y = p1.y + (z - p1.z) * (p2.y - p1.y) / (p2.z - p1.z);

    if(p1.z < p2.z)
    {
        if(z >= p1.z && z <= p2.z)
        {
            points->append(p);
            return true;
        }
    }
    else
    {
        if(z >= p2.z && z <= p1.z)
        {
            points->append(p);
            return true;
        }
    }

    return false;
}

void Slicer::removeRepeated()
{
    for(int k = 0; k < slice_byLine->size(); k++)
    {
        Line2D l = slice_byLine->at(k);

        for(int i = k + 1; i < slice_byLine->size(); )
        {
            if(l.isEqual2(slice_byLine->at(i)))
            {
                slice_byLine->removeAt(i);
            }
            else
            {
                i++;
            }
        }
    }
}

void Slicer::removeEqual()
{
    Point2D p1, p2;

    for(int k = 0; k < slice_byLine->size(); )
    {
        p1 = slice_byLine->at(k).vertexes_p1;
        p2 = slice_byLine->at(k).vertexes_p2;

        if(p1.isEqual2(p2))
        {
            slice_byLine->removeAt(k);
        }
        else
        {
            k++;
        }
    }
}


void Slicer::removeReverseRepeated()
{
    for(int k = 0; k < slice_byLine->size(); k++)
    {
        Line2D l = slice_byLine->at(k);

        for(int i = k + 1; i < slice_byLine->size(); )
        {
            if(l.getReversed().isEqual2(slice_byLine->at(i)))
            {
                slice_byLine->removeAt(i);
            }
            else
            {
                i++;
            }
        }
    }
}

Point2D Slicer::findMin()
{
    Point2D min;

    if(slice_byLine->at(0).vertexes_p1.y <= slice_byLine->at(0).vertexes_p2.y)
    {
        if(slice_byLine->at(0).vertexes_p1.x <= slice_byLine->at(0).vertexes_p2.x)
        {
            min = slice_byLine->at(0).vertexes_p1;
        }
        else
        {
            min = slice_byLine->at(0).vertexes_p2;
        }
    }
    else
    {
        min = slice_byLine->at(0).vertexes_p2;
    }

    for(int i = 1; i < slice_byLine->size(); i++)
    {
        if(slice_byLine->at(i).vertexes_p1.y == min.y)
        {
            if(slice_byLine->at(i).vertexes_p1.x < min.x)
            {
                min = slice_byLine->at(i).vertexes_p1;
            }
            else{}
        }
        else
        {
            if(slice_byLine->at(i).vertexes_p1.y < min.y)
            {
                min = slice_byLine->at(i).vertexes_p1;
            }
        }

        if(slice_byLine->at(i).vertexes_p2.y == min.y)
        {
            if(slice_byLine->at(i).vertexes_p2.x < min.x)
            {
                min = slice_byLine->at(i).vertexes_p2;
            }
            else{}
        }
        else
        {
            if(slice_byLine->at(i).vertexes_p2.y < min.y)
            {
                min = slice_byLine->at(i).vertexes_p2;
            }
        }
    }

    return min;
}

void Slicer::buildOrder()
{
    Point2D p1, p2;
    slice->append(start);
    bool flag = true;

    while(slice_byLine->size() > 0 && flag)
    {
        for(int i = 0; i < slice_byLine->size(); )
        {
            p1 = slice_byLine->at(i).vertexes_p1;
            p2 = slice_byLine->at(i).vertexes_p2;
            if(p1.isEqual2((Point2D) slice->at(slice->size() - 1)))
            {
                slice->append(slice_byLine->at(i).vertexes_p2);
                slice_byLine->removeAt(i);
                flag = true;
                break;
            }
            if(p2.isEqual2((Point2D) slice->at(slice->size() - 1)))
            {
                slice->append(slice_byLine->at(i).vertexes_p1);
                slice_byLine->removeAt(i);
                flag = true;
                break;
            }

            i++;
            flag = false;
        }
//        qDebug() << slice_byLine->size();
    }

    slice->removeAt(slice->size() - 1);
}

void Slicer::reverseDirection()
{
    for(int i = 0; i < (slice_byLine->size() - 1) / 2; i++)
    {
        slice_byLine->swap(i + 1, slice_byLine->size() - 1 - i);
    }
}

double Slicer::findMaxY()
{
    double y = slice->at(0).y;

    for(int i = 1; i < slice->size(); i++)
    {
        if(slice->at(i).y > y)
        {
            y = slice->at(i).y;
        }
    }

    return y;
}
/*
void Slicer::roundToMesh(QList<Line2D> *slice)
{
    for(int i = 0; i < slice->size(); i++)
    {
        slice->at(i).vertexes_p1.getRounded(0.1);
        slice->at(i).vertexes_p2.getRounded(0.1);
    }
}
Point2D Slicer::rounding(Point2D p, double rank)
{
    Point2D tmp;
    tmp.x = round(p.x / rank) * rank;
    tmp.y = round(p.y / rank) * rank;
    return tmp;
}
*/

void Slicer::slicing(QList<Triangle3D> *model)
{
    int n = 0;
  //  qDebug() << "Start Slicing\n";

    if(drawOutline)
    {
        if(!outsideOutline && !insideOutline)
        {
            QMessageBox::about(0, "Ошибка", "Укажите параметр внешней обводки");
            return;
        }
    }

    double currHeight = 0.0;

    while(currHeight <= height)
    {
        slice_byLine->clear();
        /*
        qDebug() << "Slice at " << currHeight << height << ":\n";
        qDebug() << "size(slice)" << slice->size() * sizeof(Point2D);
        qDebug() << "size(slice_byLine)" << slice_byLine->size() * sizeof(Line2D);
        qDebug() << "size(points)" << points->size() * sizeof(Point2D);
        qDebug() << "size(one_level)" << one_level->size() * sizeof(poid);
        qDebug() << "size(model)" << model->size() * sizeof(Triangle3D);*/
        GCodeOutStream << "Slice at " << currHeight << ":\r\n";

        for(int i = 0; i < model->size(); i++)
        {
            points->clear();

            if(points->isEmpty())
            {
                solveRelation(model->at(i).vertexes_p1, model->at(i).vertexes_p2, currHeight);
                solveRelation(model->at(i).vertexes_p2, model->at(i).vertexes_p3, currHeight);
                solveRelation(model->at(i).vertexes_p3, model->at(i).vertexes_p1, currHeight);

                if(points->size() == 2)
                {
                    Line2D line(points->at(0), points->at(1));
                    *slice_byLine += line;
                }
            }
            else
            {
                qDebug() << "********";
            }
        }

        if(slice_byLine->isEmpty())
        {
            break;
        }

        removeEqual();
        removeRepeated();
        removeReverseRepeated();

        while(!slice_byLine->isEmpty())
        {
        //    qDebug() << "1";
            start = findMin();
            slice->clear();
            buildOrder();

            if(!slice->at(0).isBiggerCorner(slice->at(slice->size() - 1)))
            {
                reverseDirection();
            }
        //    qDebug() << "size slice =" << sizeof(slice);

            if(slice->size() > 1)
            {
                if(drawOutline)
                {
                    if(insideOutline)
                    {
                        GCodeOutStream << "\tOutline shading - inside option:\r\n";
                        edgeShading(lineWidth, true, currHeight, impulse);
                    }
                    else if(outsideOutline)
                    {
                        GCodeOutStream << "\tOutline shading - outside option:\r\n";
                        edgeShading(lineWidth, false, currHeight, impulse);
                    }
                }
            }

            if(slice->size() > 2)
            {
                if(drawInline)
                {
                    GCodeOutStream << "\tInner shading:\r\n";
                    maxY = findMaxY();
                    innerShading(currHeight, impulse, scale);
                }
            }
        }

        currHeight += step_Z;
    }

    GCodeOut.close();
    QMessageBox::about(0, "Прогресс", "Печать прошла успешно!");
}


double module(Point2D p1)
{
    return (sqrt(p1.x * p1.x + p1.y * p1.y));
}

Point2D Slicer::shift_point(int id, int key, Point2D *shift_start)
{
    Point2D curr, next;
    Point2D shift(0,0);

    curr = slice->at(id);

    if(id < slice->size() - 1)
    {
        next = slice->at(id + 1);
    }
    else
    {
        next = slice->at(0);
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

void Slicer::edgeShading(double width, bool key, double Z, double F)
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

    GCodeOutStream << "\t\tG00 X" << slice->at(0).x << " Y" << slice->at(0).y << " Z" << Z << " F" << F << "\r\n";

    for(int i = 1; i < slice->size(); i++)
    {
        GCodeOutStream << "\t\tG01 X" << slice->at(i).x << " Y" << slice->at(i).y << " Z" << Z << " F" << F << "\r\n";
    }

    GCodeOutStream << "\t\tG01 X" << slice->at(0).x << " Y" << slice->at(0).y << " Z" << Z << " F" << F << "\r\n";

    for(int i = 1; i < width * 10; i++)
    {
        slice->replace(0, shift_point(0, arg_shift, shift_start));
        GCodeOutStream << "\t\tG00 X" << slice->at(0).x << " Y" << slice->at(0).y << " Z" << Z << " F" << F << "\r\n";

        for(int j = 1; j < slice->size(); j++)
        {
            slice->replace(j, shift_point(j, arg_shift, shift_start));
            GCodeOutStream << "\t\tG01 X" << slice->at(j).x << " Y" << slice->at(j).y << " Z" << Z << " F" << F << "\r\n";
        }

        GCodeOutStream << "\t\tG01 X" << slice->at(0).x << " Y" << slice->at(0).y << " Z" << Z << " F" << F << "\r\n";
    }

    delete shift_start;
}

bool p1leftp2(poid p1, poid p2)
{
    if(p1.p.x < p2.p.x)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Slicer::search_one_level(Point2D level, QList<Point2D> *set_p, int offset)
{
    QList<Point2D>::iterator it = set_p->begin() + offset + 1;
    one_level->clear();
    int i = offset + 1;
    poid pd;
    pd.p = level;
    pd.id = offset;
    one_level->append(pd);

    for(; it < set_p->end(); it++)
    {
        if(it->isOneLevel(level, 0.01))
        {
            pd.p = *it;
            pd.id = i;
            one_level->append(pd);
        }

        i++;
    }


    if(one_level->size() > 1)
    {
        qSort(one_level->begin(), one_level->end(), p1leftp2);
    }
}

void Slicer::innerShading(double Z, double F, double scale)
{
    QList<Point2D> *set_point = new QList<Point2D>(*slice);

    if(set_point->size() > 1)
    {
        extend_List(set_point, scale);

        poid temp1;
        poid temp2;
        Point2D t1_prev, t2_next, t1_next, t2_prev;
        GCodeOutStream << "\t\tG00 X" << set_point->at(0).x << " Y" << set_point->at(0).y << " Z" << Z << " F" << F << "\r\n";

        int id = -1;
        temp1.p = set_point->at(0);
        temp1.id = 0;
        temp2.p = set_point->at(1);
        temp1.id = 1;

        while(temp1.p.y < maxY && id < set_point->size() - 2)
        {
            //qDebug() << "size =" << set_point->size();
            id++;
            //qDebug() << "id =" << id;

            if(id == (set_point->size() - 1))
            {
                break;
            }

            temp1.p = set_point->at(id);
            temp1.id = id;
            temp2.p = set_point->at(id + 1);
            temp2.id = id + 1;

            if(temp2.p.y < temp1.p.y || temp1.p.y >= maxY)
            {
                continue;
            }

            search_one_level(temp1.p, set_point, id);

            QList<poid>::iterator iter = one_level->begin() + 1;
            temp2 = one_level->at(0);

            for(; iter < one_level->end(); iter++)
            {
                temp1 = temp2;
                temp2 = *iter;
                //qDebug() << temp1.id << '\t' << temp2.id;

                if(temp1.id == 0)
                {
                    //qDebug() << "!!!1";
                    t1_prev = set_point->at(set_point->size() - 1);
                   // qDebug() << "1!!!";
                }
                else
                {
                    t1_prev = set_point->at(temp1.id - 1);
                }

                if(temp1.id == set_point->size() - 1)
                {
                    t1_next = set_point->at(0);
                }
                else
                {
                    t1_next = set_point->at(temp1.id + 1);
                }

                if(temp2.id == 0)
                {
                    t2_prev = set_point->at(set_point->size() - 1);
                }
                else
                {
                    t2_prev = set_point->at(temp2.id - 1);
                }
                if(temp2.id == set_point->size() - 1)
                {
                    t2_next = set_point->at(0);
                }
                else
                {
                    t2_next = set_point->at(temp2.id + 1);
                }

                if((temp1.p.y > t1_prev.y && temp2.p.y > t2_next.y) || (temp1.p.y < t1_next.y && temp2.p.y < t2_prev.y))
                {
                    GCodeOutStream << "\t\tG00 X" << temp1.p.x << " Y" << temp1.p.y << " Z" << Z << " F" << F << "\r\n";
                    GCodeOutStream << "\t\tG01 X" << temp2.p.x << " Y" << temp2.p.y << " Z" << Z << " F" << F << "\r\n";
                }
            }
        }
    }

    delete set_point;
}

void Slicer::extend_List(QList<Point2D> *slice, double fragm)
{
    Point2D p0, p1;

    for(int index = 0; index < slice->size(); index++)
    {
       // qDebug() << slice->size();

        if(index == slice->size() - 1)
        {
            p1 = slice->at(0);
        }
        else
        {
            p1 = slice->at(index + 1);
        }

        p0 = slice->at(index);
      //  qDebug() << "p0 (" << p0.x << p0.y << ")";
      //  qDebug() << "p1 (" << p1.x << p1.y << ")";


        if(p0.x != p1.x && p0.y != p1.y)
        {
            p1.x -= p0.x;
            p1.y -= p0.y;
            double h = p1.x / p1.y;
           // qDebug() << "h = " << h;
            int sign = (p1.y > 0) ? 1 : -1;
            int points = p1.y / fragm;
            points *= sign;

            for(int i = 1; i < points; i++)
            {
                double y = p0.y + i * sign * fragm;
                double x = p0.x + y * h - p0.y * h;
                slice->insert(index + 1, Point2D(x, y));
                index++;
            }
        }
        else
        {
            if(p0.x == p1.x && p0.y == p1.y)
            {
                continue;
            }
            else if(p0.x == p1.x)
            {
                int sign = (p1.y > p0.y) ? 1 : -1;
                int points = (p1.y - p0.y) / fragm;
                points *= sign;

                for(int i = 1; i < points; i++)
                {
                    Point2D point(p1.x, p0.y + i * sign * fragm);
                    slice->insert(index + 1, point);
                    index++;
                }
            }
            else if(p0.y == p1.y)
            {
                continue;
            }
        }
    }
}
