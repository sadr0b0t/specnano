#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include"point3d.h"

class Triangle3D
{
public:
    Triangle3D();
    Triangle3D(Point3D v1, Point3D v2, Point3D v3);
    Point3D vertexes_p1;
    Point3D vertexes_p2;
    Point3D vertexes_p3;
};

#endif // TRIANGLE3D_H
