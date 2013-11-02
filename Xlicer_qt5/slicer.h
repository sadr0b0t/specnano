#ifndef SLICER_H
#define SLICER_H

#include    <QList>
#include    <QDebug>
#include    <QVector>
#include    <QFile>
#include    <QDir>

#include "support/point2d.h"
#include "support/point3d.h"
#include "support/triangle3d.h"
#include "support/line2d.h"



struct poid
{
    Point2D p;
    int id;
};

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

    void setFile(QString file);
    void slicing(QList<Triangle3D>* model);
    bool solveRelation(Point3D p1, Point3D p2, double z);
    void removeRepeated();
    void removeEqual();
    void removeReverseRepeated();
    Point2D findMin();
    void buildOrder();
    void reverseDirection();
    double findMaxY();
   // void setSliceSize(double size);
   // void roundToMesh(QList<Line2D>* slice);
    //Point2D rounding(Point2D p, double rank);

    Point2D shift_point(int id, int key, Point2D *shift_start);
    void edgeShading(double width, bool key, double Z, double F);

    void extend_List(QList<Point2D> *slice, double fragm);
    Point2D search_point(Point2D target, int check);
    void innerShading(double Z, double F, double scale);

    double height;


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
    QList<Point2D> *slice;
    QList<Line2D> *slice_byLine;
    QList<Point2D> *points;
    QList<poid> *one_level;
    QTextStream GCodeOutStream;
    QFile GCodeOut;
    double maxY;
    void search_one_level(Point2D level, QList<Point2D> *set_p, int offset);
};

#endif // SLICER_H
