#ifndef INLINESHAIDER_H
#define INLINESHAIDER_H

#include <QCoreApplication>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include "support/point2d.h"

class InlineShaider
{
public:
    InlineShaider();
    ~InlineShaider();
    void innerShading(double Z, double F, double scale);
    void setMaxY(double y);
    void setStream(QTextStream* stream);
    void setSlice(QList<Point2D> _slice);
    void extend_List(QList<Point2D> *slice, double fragm);
    Point2D search_point(Point2D target, int check);

private:
    QList<Point2D> slice;
    QTextStream* GCodeOutStream;
    double maxY;
};

#endif // INLINESHAIDER_H
