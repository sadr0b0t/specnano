#include "mainwindow.h"
#include "ui_mainwindow.h"

int idopen = 0;
int idsave = 0;
bool outsRadio = false;
bool insRadio = false;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    genMod = new ModelView(ui->modelWidget);

    QWidget::connect(ui->openButton, SIGNAL(clicked()), SLOT(on_openButton_clicked()));
    QWidget::connect(ui->printButton, SIGNAL(clicked()), SLOT(on_printButton_clicked()));
    QWidget::connect(ui->exitButton, SIGNAL(clicked()), SLOT(close()));
    QWidget::connect(ui->menu_file_openSTL, SIGNAL(triggered()), SLOT(on_openButton_activated()));
    QWidget::connect(ui->menu_file_printGCode, SIGNAL(triggered()), SLOT(on_printButton_activated()));

    genMod->resizeGL(ui->modelWidget->width(), ui->modelWidget->height());
    genMod->resize(ui->modelWidget->width(), ui->modelWidget->height());

    slicer = new Slicer();
    STLFilePath = "";
    GCodeFilePath = "";
}

void MainWindow::resizeEvent(QResizeEvent *pe)
{
    ui->modelWidget->resize(pe->size().width() - 311, pe->size().height() - 134);
    genMod->resize(pe->size().width() - 311, pe->size().height() - 134);

}

void MainWindow::on_openButton_clicked()
{
    if(idopen % 2 == 0)
    {
        STLFilePath = QFileDialog::getOpenFileName(0, "Open STL file", "", "*.stl *.STL");

        if(STLFilePath != "")
        {
            genMod->setFile(STLFilePath);
            genMod->readSTLModel();
        }
    }

    idopen++;
}

void MainWindow::on_printButton_clicked()
{
    if(idsave % 2 == 0)
    {
        GCodeFilePath = QFileDialog::getSaveFileName(0, "Print to G-Code", "", "*.gcode *.GCODE");
        qDebug() << "GCode = " << GCodeFilePath;
        slicer->setFile(GCodeFilePath);
        qDebug() << "slicer->modelSIZE" << genMod->model->size();
        slicer->slicing(genMod->model);
    }

    idsave++;
}

void MainWindow::on_openButton_activated()
{
    STLFilePath = QFileDialog::getOpenFileName(0, "Open STL file", "", "*.stl *.STL");

    if(STLFilePath != "")
    {
        genMod->setFile(STLFilePath);
        genMod->readSTLModel();
    }
}

void MainWindow::on_printButton_activated()
{
    GCodeFilePath = QFileDialog::getSaveFileName(0, "Print to G-Code", "", "*.gcode *.GCODE");

    slicer->setFile(GCodeFilePath);
    slicer->slicing(genMod->model);
}

void MainWindow::on_spinDz_valueChanged(double arg1)
{
    slicer->setSliceStep(arg1);
}

void MainWindow::on_spinScale_valueChanged(double arg1)
{
    slicer->setBrokeScale(arg1);
}

void MainWindow::on_spinWidthline_valueChanged(double arg1)
{
    slicer->setLineWidth(arg1);
}

void MainWindow::on_outlineShadingBox_clicked(bool checked)
{
    slicer->setOutline(checked);
}

void MainWindow::on_inlineShadingBox_clicked(bool checked)
{
    slicer->setInline(checked);
}

void MainWindow::on_insideRadio_clicked(bool checked)
{
    slicer->setInside(checked);
    slicer->setOutside(false);
    ui->outsideRadio->setChecked(false);
}

void MainWindow::on_outsideRadio_clicked(bool checked)
{
    slicer->setOutside(checked);
    slicer->setInside(false);
    ui->insideRadio->setChecked(false);
}

void MainWindow::on_spinImpulse_valueChanged(double arg1)
{
    slicer->setImpulse(arg1);
}

void MainWindow::on_maxX_valueChanged(int arg1)
{
    genMod->z = arg1;
    genMod->updateGL();
}

void MainWindow::on_maxY_valueChanged(int arg1)
{
    genMod->x = arg1;
    genMod->updateGL();
}

void MainWindow::on_maxZ_valueChanged(int arg1)
{
    genMod->y = arg1;
    slicer->height = arg1;
    genMod->updateGL();
}
