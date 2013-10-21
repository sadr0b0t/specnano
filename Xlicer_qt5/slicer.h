#ifndef SLICER_H
#define SLICER_H

#include<QList>
#include<QDebug>
#include<QVector>
#include<QFile>

#include "support/point2d.h"
#include "support/point3d.h"
#include "support/triangle3d.h"
#include "support/line2d.h"
#include "outlineShaider.h"
#include "inlineShaider.h"


class Slicer
{
public:
    Slicer();
    ~Slicer();

    void setImpulse(double imp)
    {
        impulse = imp;
    }
    double getImpulse()
    {
        return impulse;
    }
    void setLineWidth(double line)
    {
        lineWidth = line;
    }
    double getLineWidth()
    {
        return lineWidth;
    }

    void setSliceStep(double step)
    {
        step_Z = step;
    }
    double getSliceStep()
    {
        return step_Z;
    }
    void setBrokeScale(double scale1)
    {
        scale = scale1;
    }
    double getBrokeScale()
    {
        return scale;
    }
    void setInline(bool arg)
    {
        drawInline = arg;
    }
    bool getInline()
    {
        return drawInline;
    }
    void setOutline(bool arg)
    {
        drawOutline = arg;
    }
    bool getOutline()
    {
        return drawOutline;
    }
    void setOutside(bool arg)
    {
        outsideOutline = arg;
    }
    bool getOutside()
    {
        return outsideOutline;
    }
    void setInside(bool arg)
    {
        insideOutline = arg;
    }
    bool getInside()
    {
        return insideOutline;
    }

    void setFileModel(QList<Triangle3D>* _model, QString file);
    void slicing();
    bool solveRelation(Point3D p1, Point3D p2, double z, QList<Line2D> *res_l, QList<Point2D> *res_p);
    void removeRepeated(QList<Line2D>* slice);
    void removeEqual(QList<Line2D>* slice);
    void removeReverseRepeated(QList<Line2D>* slice);
    Point2D findMin(QList<Line2D>* slice);
    QList<Point2D> buildOrder(QList<Line2D>* slice);
    void reverseDirection(QList<Point2D>* slice);
    double findMaxY(QList<Point2D>* slice);
    void setSliceSize(double size);
    void roundToMesh(QList<Line2D>* slice);
    Point2D rounding(Point2D p, double rank);
    double height;
    QList<Triangle3D>* model;


private:
    double step_Z;
    double scale;
    double impulse;
    double lineWidth;
    bool drawOutline;
    bool outsideOutline;
    bool insideOutline;
    bool drawInline;
    Point2D start;
    QTextStream GCodeOutStream;
    QFile GCodeOut;
    OutlineShaider* osh;
    InlineShaider* ish;
    double maxY;
};

#endif // SLICER_H
