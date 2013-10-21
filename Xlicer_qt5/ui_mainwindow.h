/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <modelview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *menu_file_openSTL;
    QAction *menu_file_printGCode;
    QAction *menu_file_saveAs;
    QWidget *centralWidget;
    ModelView *modelWidget;
    QWidget *widget;
    QWidget *buttonsWidget;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *openButton;
    QPushButton *printButton;
    QPushButton *exitButton;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_7;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QSpinBox *maxX;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QSpinBox *maxY;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QSpinBox *maxZ;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *outlineShadingBox;
    QCheckBox *inlineShadingBox;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *insideRadio;
    QRadioButton *outsideRadio;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *spinDz;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *spinScale;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *spinWidthline;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *spinImpulse;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1130, 660);
        menu_file_openSTL = new QAction(MainWindow);
        menu_file_openSTL->setObjectName(QStringLiteral("menu_file_openSTL"));
        menu_file_openSTL->setCheckable(false);
        menu_file_printGCode = new QAction(MainWindow);
        menu_file_printGCode->setObjectName(QStringLiteral("menu_file_printGCode"));
        menu_file_printGCode->setCheckable(false);
        menu_file_saveAs = new QAction(MainWindow);
        menu_file_saveAs->setObjectName(QStringLiteral("menu_file_saveAs"));
        menu_file_saveAs->setCheckable(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        modelWidget = new ModelView(centralWidget);
        modelWidget->setObjectName(QStringLiteral("modelWidget"));
        modelWidget->setGeometry(QRect(10, 10, 821, 541));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(210, 549, 120, 121));
        buttonsWidget = new QWidget(centralWidget);
        buttonsWidget->setObjectName(QStringLiteral("buttonsWidget"));
        buttonsWidget->setGeometry(QRect(10, 550, 1121, 51));
        widget1 = new QWidget(buttonsWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(11, 10, 1101, 30));
        horizontalLayout_7 = new QHBoxLayout(widget1);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        openButton = new QPushButton(widget1);
        openButton->setObjectName(QStringLiteral("openButton"));

        horizontalLayout_7->addWidget(openButton);

        printButton = new QPushButton(widget1);
        printButton->setObjectName(QStringLiteral("printButton"));

        horizontalLayout_7->addWidget(printButton);

        exitButton = new QPushButton(widget1);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        horizontalLayout_7->addWidget(exitButton);

        widget2 = new QWidget(centralWidget);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(840, 10, 281, 533));
        verticalLayout_4 = new QVBoxLayout(widget2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget2);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font;
        font.setPointSize(14);
        font.setItalic(true);
        label_4->setFont(font);

        verticalLayout_4->addWidget(label_4);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        label_7 = new QLabel(widget2);
        label_7->setObjectName(QStringLiteral("label_7"));
        QFont font1;
        font1.setPointSize(12);
        label_7->setFont(font1);

        verticalLayout_4->addWidget(label_7);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(widget2);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font2;
        font2.setPointSize(10);
        label_6->setFont(font2);

        horizontalLayout_8->addWidget(label_6);

        maxX = new QSpinBox(widget2);
        maxX->setObjectName(QStringLiteral("maxX"));
        maxX->setMaximum(1200);
        maxX->setValue(1200);

        horizontalLayout_8->addWidget(maxX);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(widget2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font2);

        horizontalLayout_9->addWidget(label_8);

        maxY = new QSpinBox(widget2);
        maxY->setObjectName(QStringLiteral("maxY"));
        maxY->setMaximum(1200);
        maxY->setValue(1200);

        horizontalLayout_9->addWidget(maxY);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_9 = new QLabel(widget2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font2);

        horizontalLayout_10->addWidget(label_9);

        maxZ = new QSpinBox(widget2);
        maxZ->setObjectName(QStringLiteral("maxZ"));
        maxZ->setMaximum(1200);
        maxZ->setValue(1200);

        horizontalLayout_10->addWidget(maxZ);


        verticalLayout->addLayout(horizontalLayout_10);


        verticalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(horizontalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        outlineShadingBox = new QCheckBox(widget2);
        outlineShadingBox->setObjectName(QStringLiteral("outlineShadingBox"));
        outlineShadingBox->setFont(font2);

        verticalLayout_2->addWidget(outlineShadingBox);

        inlineShadingBox = new QCheckBox(widget2);
        inlineShadingBox->setObjectName(QStringLiteral("inlineShadingBox"));
        inlineShadingBox->setFont(font2);

        verticalLayout_2->addWidget(inlineShadingBox);


        verticalLayout_4->addLayout(verticalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        insideRadio = new QRadioButton(widget2);
        insideRadio->setObjectName(QStringLiteral("insideRadio"));
        insideRadio->setFont(font2);

        verticalLayout_3->addWidget(insideRadio);

        outsideRadio = new QRadioButton(widget2);
        outsideRadio->setObjectName(QStringLiteral("outsideRadio"));
        outsideRadio->setFont(font2);

        verticalLayout_3->addWidget(outsideRadio);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(widget2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font2);

        horizontalLayout_3->addWidget(label_3);

        spinDz = new QDoubleSpinBox(widget2);
        spinDz->setObjectName(QStringLiteral("spinDz"));
        spinDz->setFont(font2);
        spinDz->setMinimum(0.1);
        spinDz->setMaximum(10);
        spinDz->setSingleStep(0.1);

        horizontalLayout_3->addWidget(spinDz);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font2);

        horizontalLayout_2->addWidget(label_2);

        spinScale = new QDoubleSpinBox(widget2);
        spinScale->setObjectName(QStringLiteral("spinScale"));
        spinScale->setFont(font2);
        spinScale->setMinimum(0);
        spinScale->setMaximum(1);
        spinScale->setSingleStep(0.001);
        spinScale->setValue(0.1);

        horizontalLayout_2->addWidget(spinScale);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget2);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font2);

        horizontalLayout->addWidget(label);

        spinWidthline = new QDoubleSpinBox(widget2);
        spinWidthline->setObjectName(QStringLiteral("spinWidthline"));
        spinWidthline->setFont(font2);
        spinWidthline->setMaximum(10);
        spinWidthline->setSingleStep(0.1);
        spinWidthline->setValue(0.3);

        horizontalLayout->addWidget(spinWidthline);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(widget2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font2);

        horizontalLayout_5->addWidget(label_5);

        spinImpulse = new QDoubleSpinBox(widget2);
        spinImpulse->setObjectName(QStringLiteral("spinImpulse"));
        spinImpulse->setFont(font2);
        spinImpulse->setMaximum(10000);
        spinImpulse->setSingleStep(100);
        spinImpulse->setValue(3000);

        horizontalLayout_5->addWidget(spinImpulse);


        verticalLayout_4->addLayout(horizontalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1130, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(menu_file_openSTL);
        menu->addSeparator();
        menu->addAction(menu_file_printGCode);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        menu_file_openSTL->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 STL", 0));
        menu_file_printGCode->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\207\320\260\321\202\321\214 \320\262 G-code", 0));
        menu_file_saveAs->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", 0));
        openButton->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0));
        printButton->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\207\320\260\321\202\321\214", 0));
        exitButton->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
        label_4->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\277\320\265\321\207\320\260\321\202\320\270:", 0));
        label_7->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\320\275\320\270\321\206\321\213 \320\276\320\261\320\273\320\260\321\201\321\202\320\270", 0));
        label_6->setText(QApplication::translate("MainWindow", "max X", 0));
        label_8->setText(QApplication::translate("MainWindow", "max Y", 0));
        label_9->setText(QApplication::translate("MainWindow", "max Z", 0));
        outlineShadingBox->setText(QApplication::translate("MainWindow", "\320\222\320\275\320\265\321\210\320\275\321\217\321\217 \320\276\320\261\320\262\320\276\320\264\320\272\320\260 \320\272\320\276\320\275\321\202\321\203\321\200\320\260", 0));
        inlineShadingBox->setText(QApplication::translate("MainWindow", "\320\222\320\275\321\203\321\202\321\200\320\265\320\275\320\275\321\217\321\217 \320\267\320\260\320\273\320\270\320\262\320\272\320\260 \321\204\320\270\320\263\321\203\321\200\321\213", 0));
        insideRadio->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\262\320\276\320\264\320\272\320\260 \320\262\320\276\320\262\320\275\321\203\321\202\321\200\321\214", 0));
        outsideRadio->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\262\320\276\320\264\320\272\320\260 \320\275\320\260\321\200\321\203\320\266\321\203", 0));
        label_3->setText(QApplication::translate("MainWindow", "\320\250\320\260\320\263 \320\277\320\276 Z", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261 \321\200\320\260\320\267\320\261\320\270\320\265\320\275\320\270\321\217", 0));
        label->setText(QApplication::translate("MainWindow", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260 \320\273\320\270\320\275\320\270\320\270 \320\276\320\261\320\262\320\276\320\264\320\272\320\270", 0));
        label_5->setText(QApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\276\321\202\321\200\320\270\321\201\320\276\320\262\320\272\320\270", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
