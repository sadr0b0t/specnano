#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include    <QMainWindow>
#include    <QFileDialog>
#include    <QString>
#include    <QPushButton>

#include    "modelView.h"
#include    "slicer.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *pe);

private:
    QString STLFilePath;
    QString GCodeFilePath;
    Slicer *slicer;
    ModelView *genMod;
    Ui::MainWindow *ui;

private slots:
    void on_openButton_clicked();
    void on_openButton_activated();
    void on_printButton_clicked();
    void on_printButton_activated();

    void on_spinDz_valueChanged(double arg1);

    void on_spinScale_valueChanged(double ar1g1);

    void on_spinWidthline_valueChanged(double arg1);

    void on_outlineShadingBox_clicked(bool checked);

    void on_inlineShadingBox_clicked(bool checked);

    void on_insideRadio_clicked(bool checked);
    void on_outsideRadio_clicked(bool checked);
    void on_spinImpulse_valueChanged(double arg1);
    void on_maxX_valueChanged(int arg1);
    void on_maxY_valueChanged(int arg1);
    void on_maxZ_valueChanged(int arg1);
};

#endif // MAINWINDOW_H
