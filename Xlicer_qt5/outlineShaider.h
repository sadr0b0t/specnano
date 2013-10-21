#ifndef OUTLINESHAIDER_H
#define OUTLINESHAIDER_H

#include <QCoreApplication>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <qmath.h>
#include "support/point2d.h"

class OutlineShaider
{
public:
    OutlineShaider();
    ~OutlineShaider();
    Point2D shift_point(int id, int key, Point2D *shift_start);
    QList<Point2D> edgeShading(double width, bool key, double Z, double F);
    void setStream(QTextStream* stream);
    void setSlice(QList<Point2D> _slice);

private:
    QList<Point2D> slice;
    QTextStream* GCodeOutStream;
    double currentHeight;
};

#endif // OUTLINESHAIDER_H
