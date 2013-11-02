#include "triangle3d.h"

Triangle3D::Triangle3D()
{
}

Triangle3D::Triangle3D(Point3D v1, Point3D v2, Point3D v3)
{
    vertexes_p1 = v1;
    vertexes_p2 = v2;
    vertexes_p3 = v3;
}
