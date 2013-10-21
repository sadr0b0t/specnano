#include "triangle3d.h"

Triangle3D::Triangle3D()
{
    vertexes = new Point3D[3];
}

Triangle3D::Triangle3D(Point3D v1, Point3D v2, Point3D v3)
{
    vertexes = new Point3D[3];
    vertexes[0] = v1;
    vertexes[1] = v2;
    vertexes[2] = v3;
}
