#include <QtGui>
#include <QMessageBox>
#include "modelView.h"
#include "support/triangle3d.h"
#include "mainWindow.h"

int counter = 1;

ModelView::ModelView(QWidget* pwgt) : QGLWidget(pwgt)
{
    model = new QList<Triangle3D>();
    xRotate = 45;
    x = 1200;
    y = 1200;
    z = 1200;
    yRotate = 45;
    angle = 1;
    drawSTL = false;
}

struct BinSTL
{
    float normal[3];
    float vertex[3][3];
    unsigned short reserve;
};

int ModelView::readBinaryModel()
{
    float **normal;
    Triangle3D *tri;
    STLFile.reset();
    QDataStream stream(&STLFile);
    stream.setVersion(QDataStream::Qt_5_1);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    uint i = 0;
    unsigned int numbers;

    stream.skipRawData(80);
    stream >> numbers;

    normal = new float*[numbers];
    tri = new Triangle3D[numbers];

    while(i < numbers)
    {
        normal[i] = new float[3];

        for(int j = 0; j < 3; j++)
        {
            stream >> normal[i][j];
        }

        stream >> tri[i].vertexes_p1.x >> tri[i].vertexes_p1.y >> tri[i].vertexes_p1.z;
        stream >> tri[i].vertexes_p2.x >> tri[i].vertexes_p2.y >> tri[i].vertexes_p2.z;
        stream >> tri[i].vertexes_p3.x >> tri[i].vertexes_p3.y >> tri[i].vertexes_p3.z;

        stream.skipRawData(2);
        model->append(tri[i]);
        delete normal[i];
        i++;
    }

    delete normal;
    delete tri;
    drawSTL = true;
    update();
}

int ModelView::readSTLModel()
{
    QRegExp headerExpr("(?:solid)(?:\\s+)(\\w)*");
    QRegExp vertexesExpr("(?:\\s*)(?:vertex)(?:\\s+)(-?\\d+(?:.\\d+)?(?:e[-|+]\\d+)?)(?:\\s+)(-?\\d+(?:.\\d+)?(?:e[-|+]\\d+)?)(?:\\s+)(-?\\d+(?:.\\d+)?(?:e[-|+]\\d+)?)(?:\\s*)");
    QRegExp normal1ExprStr("(?:\\s*)(?:facet)(?:\\s+)(?:normal)(?:\\s+)(-?\\d+(?:.\\d+)?(?:e[-|+]\\d+)?)(?:\\s+)(-?\\d+(?:.\\d+)?(?:e[-|+]\\d+)?)(?:\\s+)(-?\\d+(?:.\\d+)?(?:e[-|+]\\d+)?)(?:\\s*)");
    QRegExp loop1ExprStr("(?:\\s*)(?:outer)(?:\\s+)(?:loop)(?:\\s*)");
    QRegExp normal2ExprStr("(?:\\s*)(?:endfacet)(?:\\s*)");
    QRegExp loop2ExprStr("(?:\\s*)(?:endloop)(?:\\s*)");

    QString vendor;
    QString tmpStr;
    int tmpPos;
    STLFile.open(QIODevice::ReadOnly);

    tmpStr = STLFile.readLine();
    tmpPos = headerExpr.indexIn(tmpStr);

    if(tmpPos == -1)
    {
        readBinaryModel();
    }
    else
    {
        vendor = headerExpr.capturedTexts().at(1);
        tmpStr = STLFile.readLine();

        while(1)
        {
            tmpPos = normal1ExprStr.indexIn(tmpStr);

            if(tmpPos == -1)
            {
                qDebug() << "Error 1";
                QMessageBox::about(0, "Прогресс", "Ошибка чтения файла");
                return 0;
            }

            tmpStr = STLFile.readLine();
            tmpPos = loop1ExprStr.indexIn(tmpStr);

            if(tmpPos == -1)
            {
                qDebug() << "Error 2";
                QMessageBox::about(0, "Прогресс", "Ошибка чтения файла");
                return 0;
            }

            Triangle3D tri;

            for(int j = 0; j < 3; j++)
            {
                tmpStr = STLFile.readLine();
                tmpPos = vertexesExpr.indexIn(tmpStr);

                if(tmpPos == -1)
                {
                    qDebug() << "Error 3";
                    QMessageBox::about(0, "Прогресс", "Ошибка чтения файла");
                    return 0;
                }

                QList<QString> lst = vertexesExpr.capturedTexts();
                Point3D p;
                p.x = lst.at(1).toDouble();
                p.y = lst.at(2).toDouble();
                p.z = lst.at(3).toDouble();

                if(j == 0)
                {
                    tri.vertexes_p1 = p;
                }
                if(j == 1)
                {
                    tri.vertexes_p2 = p;
                }
                if(j == 2)
                {
                    tri.vertexes_p3 = p;
                }
            }

            model->append(tri);

            tmpStr = STLFile.readLine();
            tmpPos = loop2ExprStr.indexIn(tmpStr);

            if(tmpPos == -1)
            {
                qDebug() << "Error 4";
                QMessageBox::about(0, "Прогресс", "Ошибка чтения файла");
                return 0;
            }

            tmpStr = STLFile.readLine();
            tmpPos = normal2ExprStr.indexIn(tmpStr);

            if(tmpPos == -1)
            {
                qDebug() << "Error 5";
                QMessageBox::about(0, "Прогресс", "Ошибка чтения файла");
                return 0;
            }

            tmpStr = STLFile.readLine();
            tmpPos = QRegExp("(?:endsolid)(?:(?:\\s*)(\\w+))?").indexIn(tmpStr);

            if(tmpPos <= -1)
            {
                tmpPos = QRegExp("(?:end solid)(?:(?:\\s*)(\\w+))?").indexIn(tmpStr);

                if(tmpPos > -1)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    drawSTL = true;
    update();

    return 1;
}

void ModelView::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    //glEnable(GL_CULL_FACE);
    qDebug("init");
}

void ModelView::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    qDebug() << nWidth << nHeight;
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    //glFrustum(-400.0/2.0, 400.0/2.0, -400.0/2.0, 400.0/2.0, 1.0, 20.0);
    glFrustum(-1.5, 1.5, -1.5, 1.5, 1.0, 301.0);
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
    qDebug("resize");
}

void ModelView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    number = createMesh(x, y, z);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -100.0);

    glRotatef(xRotate, 1.0, 0.0, 0);
    glRotatef(yRotate, 0.0, 1.0, 0);
    glScalef(angle, angle, angle);

    glCallList(number);

    if(drawSTL)
    {
        drawTriangles();
    }
}

void ModelView::mousePressEvent(QMouseEvent* pe)
{
    mousePosition = pe->pos();
}

void ModelView::mouseMoveEvent(QMouseEvent* pe)
{
    xRotate += 180 * (GLfloat)(pe->y() - mousePosition.y()) / height();
    yRotate += 180 * (GLfloat)(pe->x() - mousePosition.x()) / width();
    updateGL();

    mousePosition = pe->pos();
}


void ModelView::wheelEvent(QWheelEvent* pe)
{
    if(angle < 1 && pe->delta() >= 0)
    {
        angle = (10 - counter) * 0.125;
        counter--;
        qDebug() << "ff" << angle;
        updateGL();
        return;
    }

    angle += pe->delta() / 120;

    if(angle < 0.5 && pe->delta() < 0)
    {
       angle = 1 - counter * 0.125;
       counter++;
       if(counter == 8)
       {
           counter = 7;
       }
    }
    qDebug() << angle;


    if(angle > 15)
    {
        angle = 15;
    }
//    resizeGL(width() / angle, height() / angle);
    updateGL();
}

GLuint ModelView::createMesh(double x, double y, double z)
{
    GLuint n = glGenLists(5);
    double i = x / 20.0;
    double j = y / 20.0;
    double k = z / 20.0;
    glNewList(n, GL_COMPILE);
        glBegin(GL_LINES);
        qglColor(Qt::white);
            glVertex3d(0, -y, 0);
            glVertex3d(0, y, 0);
            glVertex3d(-x, 0, 0);
            glVertex3d(x, 0, 0);
            glVertex3d(0, 0, z);
            glVertex3d(0, 0, -z);

            glVertex3d(0, y, 0);
            glVertex3d(1.5, y - 7.5, 0);
            glVertex3d(0, y, 0);
            glVertex3d(-1.5, y - 7.5, 0);

            glVertex3d(x, 0, 0);
            glVertex3d(x - 7.5, 1.5, 0);
            glVertex3d(x, 0, 0);
            glVertex3d(x - 7.5, -1.5, 0);

            glVertex3d(0, 0, z);
            glVertex3d(1.5, 0, z - 7.5);
            glVertex3d(0, 0, z);
            glVertex3d(-1.5, 0, z - 7.5);

            glVertex3d(x, y, -z);
            glVertex3d(x, y, z);

            glVertex3d(-x, y, -z);
            glVertex3d(-x, y, z);

            glVertex3d(x, -y, -z);
            glVertex3d(x, -y, z);

            glVertex3d(x, -y, -z);
            glVertex3d(x, y, -z);

            glVertex3d(x, -y, z);
            glVertex3d(x, y, z);

            glVertex3d(-x, -y, z);
            glVertex3d(-x, y, z);

            glVertex3d(-x, -y, -z);
            glVertex3d(-x, y, -z);

            glVertex3d(-x, -y, z);
            glVertex3d(-x, -y, -z);

            glVertex3d(-x, -y, z);
            glVertex3d(x, -y, z);

            glVertex3d(-x, -y, -z);
            glVertex3d(x, -y, -z);

            glVertex3d(-x, y, z);
            glVertex3d(x, y, z);

            glVertex3d(-x, y, -z);
            glVertex3d(x, y, -z);

            while(i < x && k < z)
            {
                qglColor(Qt::yellow);
                glVertex3d(i, 0, -z);
                glVertex3d(i, 0, z);

                glVertex3d(-i, 0, -z);
                glVertex3d(-i, 0, z);

                glVertex3d(-x, 0, k);
                glVertex3d(x, 0, k);

                glVertex3d(-x, 0, -k);
                glVertex3d(x, 0, -k);

                i = i + x / 20;
                k = k + z / 20;
            }

            i = x / 20;
            j = y / 20;
            k = z / 20;
        glEnd();

        glBegin(GL_LINES);
            qglColor(Qt::white);
            while(i < x && j < y && k < z)
            {
                glVertex3d(i, -1.5, 0);
                glVertex3d(i, 1.5, 0);

                glVertex3d(-i, -1.5, 0);
                glVertex3d(-i, 1.5, 0);

                glVertex3d(1.5, j, 0);
                glVertex3d(-1.5, j, 0);

                glVertex3d(1.5, -j, 0);
                glVertex3d(-1.5, -j, 0);

                glVertex3d(0, -1.5, k);
                glVertex3d(0, 1.5, k);

                glVertex3d(0, -1.5, -k);
                glVertex3d(0, 1.5, -k);

                i += x / 20;
                j += y / 20;
                k += z / 20;
            }
        glEnd();
    glEndList();
    return n;
}

void ModelView::drawTriangles()
{
    QList<Triangle3D>::iterator it = model->begin();
    int id = 0;
    qDebug() << "start draw";
    glBegin(GL_TRIANGLES);
        qglColor(Qt::lightGray);

        while(it != model->end())
        {
            glVertex3d(it->vertexes_p1.x, it->vertexes_p1.y, it->vertexes_p1.z);
            glVertex3d(it->vertexes_p2.x, it->vertexes_p2.y, it->vertexes_p2.z);
            glVertex3d(it->vertexes_p3.x, it->vertexes_p3.y, it->vertexes_p3.z);

            id++;
            it += 1;
        }
    glEnd();
    qDebug() << "end draw";
}
