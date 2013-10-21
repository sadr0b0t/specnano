#include "slicer.h"
#include <QMessageBox>

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
    osh = new OutlineShaider();
    ish = new InlineShaider();
    model = new QList<Triangle3D>();
}

Slicer::~Slicer()
{
    delete ish;
    delete osh;
}

void Slicer::setFileModel(QList<Triangle3D>* _model, QString file)
{
    GCodeOut.setFileName(file);
    GCodeOut.remove();
    GCodeOut.open(QIODevice::Append);
    GCodeOutStream.setDevice(&GCodeOut);

    osh->setStream(&GCodeOutStream);
    ish->setStream(&GCodeOutStream);
    model = _model;
}

bool Slicer::solveRelation(Point3D p1, Point3D p2, double z, QList<Line2D> *res_l, QList<Point2D> *res_p)
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
            res_p->append(p);
            return true;
        }
    }
    else
    {
        if(z >= p2.z && z <= p1.z)
        {
            res_p->append(p);
            return true;
        }
    }

    return false;
}

void Slicer::removeRepeated(QList<Line2D> *slice)
{
    for(int k = 0; k < slice->size(); k++)
    {
        Line2D l = slice->at(k);

        for(int i = k + 1; i < slice->size(); )
        {
            if(l.isEqual2(slice->at(i)))
            {
                slice->removeAt(i);
            }
            else
            {
                i++;
            }
        }
    }
}

void Slicer::removeEqual(QList<Line2D> *slice)
{
    for(int k = 0; k < slice->size(); )
    {
//        Point2D tmp1=rounding(slice->at(k).vertexes[0], 0);
        if(slice->at(k).vertexes[0].isEqual2(slice->at(k).vertexes[1]))
//        if(slice->at(k).vertexes[0].x == slice->at(k).vertexes[1].x && slice->at(k).vertexes[0].y == slice->at(k).vertexes[1].y)
//        if(tmp1.x==tmp2.x && tmp1.y==tmp2.y)
        {
//            qDebug() << "(" << slice->at(k).vertexes[0].x << ";" << slice->at(k).vertexes[0].y << ")"\
//                        << "->"\
//                        << "(" << slice->at(k).vertexes[1].x << ";" << slice->at(k).vertexes[1].y << ")";
            slice->removeAt(k);
        }
        else
        {
            k++;
//            qDebug() << "(" << slice->at(k).vertexes[0].x << ";" << slice->at(k).vertexes[0].y << ")"\
//                        << "->"\
//                        << "(" << slice->at(k).vertexes[1].x << ";" << slice->at(k).vertexes[1].y << ")";
        }
//        qDebug() << slice->size();
    }
}


void Slicer::removeReverseRepeated(QList<Line2D> *slice)
{
    for(int k=0; k<slice->size(); k++)
    {
        Line2D l=slice->at(k);
        for(int i=k+1; i<slice->size(); )
        {
            if(l.getReversed().isEqual2(slice->at(i)))
                slice->removeAt(i);
            else
                i++;
        }
    }
}

Point2D Slicer::findMin(QList<Line2D> *slice)
{
    Point2D min;
    if(slice->at(0).vertexes[0].y <= slice->at(0).vertexes[1].y)
        if(slice->at(0).vertexes[0].x <= slice->at(0).vertexes[1].x)
            min=slice->at(0).vertexes[0];
        else
            min=slice->at(0).vertexes[1];
    else
        min=slice->at(0).vertexes[1];

    for(int i=1; i<slice->size(); i++)
    {
        if(slice->at(i).vertexes[0].y==min.y)
            if(slice->at(i).vertexes[0].x<min.x)
                min=slice->at(i).vertexes[0];
            else
                ;
        else
            if(slice->at(i).vertexes[0].y<min.y)
                min=slice->at(i).vertexes[0];

        if(slice->at(i).vertexes[1].y==min.y)
            if(slice->at(i).vertexes[1].x<min.x)
                min=slice->at(i).vertexes[1];
            else
                ;
        else
            if(slice->at(i).vertexes[1].y<min.y)
                min=slice->at(i).vertexes[1];
    }
    return min;
}

QList<Point2D> Slicer::buildOrder(QList<Line2D> *slice)
{
    QList<Point2D> tmp;
    tmp.append(start);
    bool flag=true;

    while(slice->size()>0 && flag)
    {
        for(int i=0; i<slice->size(); )
        {
            if(slice->at(i).vertexes[0].isEqual2(tmp.at(tmp.size()-1)))
            {
                tmp.append(slice->at(i).vertexes[1]);
                slice->removeAt(i);
                flag=true;
                break;
            }
            if(slice->at(i).vertexes[1].isEqual2(tmp.at(tmp.size()-1)))
            {
                tmp.append(slice->at(i).vertexes[0]);
                slice->removeAt(i);
                flag=true;
                break;
            }
            i++;
            flag=false;
        }
//        qDebug() << slice->size();
    }

    tmp.removeAt(tmp.size()-1);
    return tmp;
}

void Slicer::reverseDirection(QList<Point2D> *slice)
{
    for(int i=0; i<(slice->size()-1)/2; i++)
    {
        slice->swap(i+1, slice->size()-1-i);
    }
}

double Slicer::findMaxY(QList<Point2D> *slice)
{
    double y = slice->at(0).y;
    for(int i = 1; i < slice->size(); i++)
        if(slice->at(i).y > y)
            y = slice->at(i).y;
    return y;
}

void Slicer::roundToMesh(QList<Line2D> *slice)
{
    for(int i=0; i<slice->size(); i++)
    {
        slice->at(i).vertexes[0].getRounded(0.1);
        slice->at(i).vertexes[1].getRounded(0.1);
    }
}

Point2D Slicer::rounding(Point2D p, double rank)
{
    Point2D tmp;
    tmp.x=(round(p.x/rank)*rank);
    tmp.y=round(p.y/rank)*rank;
    return tmp;
}

void Slicer::slicing()
{
    qDebug() << "Start Slicing\n";

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
        QList<Line2D> slice_byLine;

        qDebug() << "Slice at " << currHeight << ":\n";
        GCodeOutStream << "Slice at " << currHeight << ":\r\n";

        for(int i = 0; i < model->size(); i++)
        {
            QList<Point2D> points;

            solveRelation(model->at(i).vertexes[0], model->at(i).vertexes[1], currHeight, &slice_byLine, &points);
            solveRelation(model->at(i).vertexes[1], model->at(i).vertexes[2], currHeight, &slice_byLine, &points);
            solveRelation(model->at(i).vertexes[2], model->at(i).vertexes[0], currHeight, &slice_byLine, &points);

            if(points.size() == 2)
            {
                Line2D l(points.at(0), points.at(1));
                slice_byLine.append(l);
            }
        }

        if(slice_byLine.isEmpty())
        {
            break;
        }

        removeEqual(&slice_byLine);
        removeRepeated(&slice_byLine);
        removeReverseRepeated(&slice_byLine);

//      for(int i=0; i<slice_byLine.size(); i++)
//      {
//          qDebug() << "(" << slice_byLine.at(i).vertexes[0].x << ";" << slice_byLine.at(i).vertexes[0].y << ")"\
//                      << "->"\
//                      << "(" << slice_byLine.at(i).vertexes[1].x << ";" << slice_byLine.at(i).vertexes[1].y << ")";
//      }
//      qDebug() << slice_byLine.size();


        while(!slice_byLine.isEmpty())
        {
            start = findMin(&slice_byLine);
//            qDebug() << start.x << start.y;
//            qDebug();
            QList<Point2D> slice = buildOrder(&slice_byLine);

            if(!slice.at(0).isBiggerCorner(slice.at(slice.size() - 1)))
            {
                reverseDirection(&slice);
            }

//          qDebug() << slice.size();

            for(int i = 0; i < slice.size(); i++)
            {
                qDebug() << "(" << slice.at(i).x << ";" << slice.at(i).y << ")";
//              GCodeOutStream << "(" << con.at(k).points.at(i).x << ";" << con.at(k).points.at(i).y << ")\n";
            }

            qDebug();
//            GCodeOutStream << "\n";

            if(slice.size() > 1)
            {
                if(drawOutline)
                {
                    osh->setSlice(slice);

                    if(insideOutline)
                    {
                        GCodeOutStream << "\tOutline shading - inside option:\r\n";
                        osh->edgeShading(lineWidth, true, currHeight, impulse);
                    }
                    else if(outsideOutline)
                    {
                        GCodeOutStream << "\tOutline shading - outside option:\r\n";
                        osh->edgeShading(lineWidth, false, currHeight, impulse);
                    }
                }
            }
//            qDebug() << "here";
            if(slice.size() > 2)
            {
                if(drawInline)
                {
                    GCodeOutStream << "\tInner shading:\r\n";
                    ish->setMaxY(findMaxY(&slice));
                    ish->setSlice(slice);
                    ish->innerShading(currHeight, impulse, scale);
                }
            }
        }

//        return;

        currHeight += step_Z;
    }

    GCodeOut.close();
    QMessageBox::about(0, "Прогресс", "Печать прошла успешно!");
}
