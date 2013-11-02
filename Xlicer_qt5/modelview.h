#ifndef MODELVIEW_H
#define MODELVIEW_H

#include    <QtOpenGL/QGLWidget>
#include    <QWheelEvent>
#include    "slicer.h"
#include    "support/triangle3d.h"

struct normalx
{
    float x;
    float y;
    float z;
};

class ModelView : public QGLWidget
{
private:
    GLuint  number;
    double angle;
    GLfloat xRotate;
    GLfloat yRotate;
    QPoint  mousePosition;
    QFile STLFile;

public:
    double x;
    double y;
    double z;
    QList<Triangle3D> *model;
    bool drawSTL;
    ModelView(QWidget* pwgt = 0);
    int readBinaryModel();
    inline void setFile(QString name)
    {
        STLFile.setFileName(name);
    }

    int readSTLModel();

    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void mouseMoveEvent (QMouseEvent* pe);
    void wheelEvent(QWheelEvent* pe);
    GLuint createMesh(double, double, double);
    void drawTriangles();
};
#endif  //MODELVIEW_H
