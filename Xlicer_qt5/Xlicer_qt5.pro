#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T08:13:10
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Xlicer_qt5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    slicer.cpp \
    outlineShaider.cpp \
    inlineShaider.cpp \
    support/triangle3d.cpp \
    support/point3d.cpp \
    support/point2d.cpp \
    support/line2d.cpp \
    modelview.cpp

HEADERS  += mainwindow.h \
    slicer.h \
    outlineShaider.h \
    inlineShaider.h \
    support/triangle3d.h \
    support/point3d.h \
    support/point2d.h \
    support/line2d.h \
    modelview.h

FORMS    += mainwindow.ui
