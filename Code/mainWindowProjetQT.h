/********************************************************************************
** Form generated from reading ui file 'mainWindowProjetQT.ui'
**
** Created: Wed 20. Jul 15:28:27 2011
**      by: Qt User Interface Compiler version 4.3.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef MAINWINDOWPROJETQT_H
#define MAINWINDOWPROJETQT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

class Ui_Assets
{
public:
    QAction *actionExit;
    QAction *actionNew_Scene;
    QAction *actionExport_obj;
    QAction *actionExport_ma;
    QAction *actionLoad_ma;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QGroupBox *Objects_groupBox;

    QPushButton *Objects_pushButton_void0;
    QPushButton *Objects_pushButton_void1;

    QPushButton *Objects_pushButton_terGen;
    QPushButton *Objects_pushButton_terRender;
    QPushButton *Objects_pushButton_terWater;

	/*
    QPushButton *Objects_o05_pushButton;
    QPushButton *Objects_o01_pushButton;
    QPushButton *Objects_o03_pushButton;
    QPushButton *Objects_o04_pushButton;
    QPushButton *Objects_o02_pushButton;
    QPushButton *Objects_o06_pushButton;
    QPushButton *Objects_o10_pushButton;
    QPushButton *Objects_o08_pushButton;
    QPushButton *Objects_o09_pushButton;
    QPushButton *Objects_o07_pushButton;
    QPushButton *Objects_o11_pushButton;
    QPushButton *Objects_o15_pushButton;
    QPushButton *Objects_o13_pushButton;
    QPushButton *Objects_o14_pushButton;
    QPushButton *Objects_o12_pushButton;
    QPushButton *Objects_o16_pushButton;
    QPushButton *Objects_o20_pushButton;
    QPushButton *Objects_o18_pushButton;
    QPushButton *Objects_o19_pushButton;
    QPushButton *Objects_o17_pushButton;
    QPushButton *Objects_o21_pushButton;
    QPushButton *Objects_o25_pushButton;
    QPushButton *Objects_o23_pushButton;
    QPushButton *Objects_o24_pushButton;
    QPushButton *Objects_o22_pushButton;
    QPushButton *Objects_o26_pushButton;
    QPushButton *Objects_o30_pushButton;
    QPushButton *Objects_o28_pushButton;
    QPushButton *Objects_o29_pushButton;
    QPushButton *Objects_o27_pushButton;
    QPushButton *Objects_o31_pushButton;
    QPushButton *Objects_o35_pushButton;
    QPushButton *Objects_o33_pushButton;
    QPushButton *Objects_o34_pushButton;
    QPushButton *Objects_o32_pushButton;
	*/

    QFrame *line_2;
    QWidget *widget_GL;
    QFrame *line;
    QGroupBox *Parameters_groupBox;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuExport;

    void setupUi(QMainWindow *Assets)
    {
    if (Assets->objectName().isEmpty())
        Assets->setObjectName(QString::fromUtf8("Assets"));
    Assets->resize(781, 577);
    Assets->setMinimumSize(QSize(420, 300));
    actionExit = new QAction(Assets);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    actionNew_Scene = new QAction(Assets);
    actionNew_Scene->setObjectName(QString::fromUtf8("actionNew_Scene"));
    actionExport_obj = new QAction(Assets);
    actionExport_obj->setObjectName(QString::fromUtf8("actionExport_obj"));
    actionExport_ma = new QAction(Assets);
    actionExport_ma->setObjectName(QString::fromUtf8("actionExport_ma"));
    actionLoad_ma = new QAction(Assets);
    actionLoad_ma->setObjectName(QString::fromUtf8("actionLoad_ma"));
    centralwidget = new QWidget(Assets);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    hboxLayout = new QHBoxLayout(centralwidget);
    hboxLayout->setSpacing(0);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    Objects_groupBox = new QGroupBox(centralwidget);
    Objects_groupBox->setObjectName(QString::fromUtf8("Objects_groupBox"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(Objects_groupBox->sizePolicy().hasHeightForWidth());
    Objects_groupBox->setSizePolicy(sizePolicy);
    Objects_groupBox->setMinimumSize(QSize(153, 230));

    Objects_pushButton_void0 = new QPushButton(Objects_groupBox);
    Objects_pushButton_void0->setObjectName(QString::fromUtf8("Objects_pushButton_void0"));
    Objects_pushButton_void0->setGeometry(QRect(0, 20, 70, 23));
    Objects_pushButton_void0->setCheckable(true);

    Objects_pushButton_void1 = new QPushButton(Objects_groupBox);
    Objects_pushButton_void1->setObjectName(QString::fromUtf8("Objects_pushButton_void1"));
    Objects_pushButton_void1->setGeometry(QRect(70, 20, 70, 23));
    Objects_pushButton_void1->setCheckable(true);

    Objects_pushButton_terGen = new QPushButton(Objects_groupBox);
    Objects_pushButton_terGen->setObjectName(QString::fromUtf8("Objects_pushButton_terGen"));
    Objects_pushButton_terGen->setGeometry(QRect(0, 43, 140, 23));
    Objects_pushButton_terGen->setCheckable(true);

    Objects_pushButton_terRender = new QPushButton(Objects_groupBox);
    Objects_pushButton_terRender->setObjectName(QString::fromUtf8("Objects_pushButton_terRender"));
    Objects_pushButton_terRender->setGeometry(QRect(0, 66, 140, 23));
    Objects_pushButton_terRender->setCheckable(true);

    Objects_pushButton_terWater = new QPushButton(Objects_groupBox);
    Objects_pushButton_terWater->setObjectName(QString::fromUtf8("Objects_pushButton_terWater"));
    Objects_pushButton_terWater->setGeometry(QRect(0, 89, 140, 23));
    Objects_pushButton_terWater->setCheckable(true);

	/*
    Objects_o05_pushButton = new QPushButton(Objects_groupBox);
    Objects_o05_pushButton->setObjectName(QString::fromUtf8("Objects_o05_pushButton"));
    Objects_o05_pushButton->setGeometry(QRect(120, 20, 31, 23));
    Objects_o05_pushButton->setCheckable(true);
    Objects_o03_pushButton = new QPushButton(Objects_groupBox);
    Objects_o03_pushButton->setObjectName(QString::fromUtf8("Objects_o03_pushButton"));
    Objects_o03_pushButton->setGeometry(QRect(60, 20, 31, 23));
    Objects_o03_pushButton->setCheckable(true);
    Objects_o06_pushButton = new QPushButton(Objects_groupBox);
    Objects_o06_pushButton->setObjectName(QString::fromUtf8("Objects_o06_pushButton"));
    Objects_o06_pushButton->setGeometry(QRect(0, 50, 31, 23));
    Objects_o06_pushButton->setCheckable(true);
    Objects_o10_pushButton = new QPushButton(Objects_groupBox);
    Objects_o10_pushButton->setObjectName(QString::fromUtf8("Objects_o10_pushButton"));
    Objects_o10_pushButton->setGeometry(QRect(120, 50, 31, 23));
    Objects_o10_pushButton->setCheckable(true);
    Objects_o08_pushButton = new QPushButton(Objects_groupBox);
    Objects_o08_pushButton->setObjectName(QString::fromUtf8("Objects_o08_pushButton"));
    Objects_o08_pushButton->setGeometry(QRect(60, 50, 31, 23));
    Objects_o08_pushButton->setCheckable(true);
    Objects_o09_pushButton = new QPushButton(Objects_groupBox);
    Objects_o09_pushButton->setObjectName(QString::fromUtf8("Objects_o09_pushButton"));
    Objects_o09_pushButton->setGeometry(QRect(90, 50, 31, 23));
    Objects_o09_pushButton->setCheckable(true);
    Objects_o07_pushButton = new QPushButton(Objects_groupBox);
    Objects_o07_pushButton->setObjectName(QString::fromUtf8("Objects_o07_pushButton"));
    Objects_o07_pushButton->setGeometry(QRect(30, 50, 31, 23));
    Objects_o07_pushButton->setCheckable(true);
    Objects_o11_pushButton = new QPushButton(Objects_groupBox);
    Objects_o11_pushButton->setObjectName(QString::fromUtf8("Objects_o11_pushButton"));
    Objects_o11_pushButton->setGeometry(QRect(0, 80, 31, 23));
    Objects_o11_pushButton->setCheckable(true);
    Objects_o15_pushButton = new QPushButton(Objects_groupBox);
    Objects_o15_pushButton->setObjectName(QString::fromUtf8("Objects_o15_pushButton"));
    Objects_o15_pushButton->setGeometry(QRect(120, 80, 31, 23));
    Objects_o15_pushButton->setCheckable(true);
    Objects_o13_pushButton = new QPushButton(Objects_groupBox);
    Objects_o13_pushButton->setObjectName(QString::fromUtf8("Objects_o13_pushButton"));
    Objects_o13_pushButton->setGeometry(QRect(60, 80, 31, 23));
    Objects_o13_pushButton->setCheckable(true);
    Objects_o14_pushButton = new QPushButton(Objects_groupBox);
    Objects_o14_pushButton->setObjectName(QString::fromUtf8("Objects_o14_pushButton"));
    Objects_o14_pushButton->setGeometry(QRect(90, 80, 31, 23));
    Objects_o14_pushButton->setCheckable(true);
    Objects_o12_pushButton = new QPushButton(Objects_groupBox);
    Objects_o12_pushButton->setObjectName(QString::fromUtf8("Objects_o12_pushButton"));
    Objects_o12_pushButton->setGeometry(QRect(30, 80, 31, 23));
    Objects_o12_pushButton->setCheckable(true);
    Objects_o16_pushButton = new QPushButton(Objects_groupBox);
    Objects_o16_pushButton->setObjectName(QString::fromUtf8("Objects_o16_pushButton"));
    Objects_o16_pushButton->setGeometry(QRect(0, 110, 31, 23));
    Objects_o16_pushButton->setCheckable(true);
    Objects_o20_pushButton = new QPushButton(Objects_groupBox);
    Objects_o20_pushButton->setObjectName(QString::fromUtf8("Objects_o20_pushButton"));
    Objects_o20_pushButton->setGeometry(QRect(120, 110, 31, 23));
    Objects_o20_pushButton->setCheckable(true);
    Objects_o18_pushButton = new QPushButton(Objects_groupBox);
    Objects_o18_pushButton->setObjectName(QString::fromUtf8("Objects_o18_pushButton"));
    Objects_o18_pushButton->setGeometry(QRect(60, 110, 31, 23));
    Objects_o18_pushButton->setCheckable(true);
    Objects_o19_pushButton = new QPushButton(Objects_groupBox);
    Objects_o19_pushButton->setObjectName(QString::fromUtf8("Objects_o19_pushButton"));
    Objects_o19_pushButton->setGeometry(QRect(90, 110, 31, 23));
    Objects_o19_pushButton->setCheckable(true);
    Objects_o17_pushButton = new QPushButton(Objects_groupBox);
    Objects_o17_pushButton->setObjectName(QString::fromUtf8("Objects_o17_pushButton"));
    Objects_o17_pushButton->setGeometry(QRect(30, 110, 31, 23));
    Objects_o17_pushButton->setCheckable(true);
    Objects_o21_pushButton = new QPushButton(Objects_groupBox);
    Objects_o21_pushButton->setObjectName(QString::fromUtf8("Objects_o21_pushButton"));
    Objects_o21_pushButton->setGeometry(QRect(0, 140, 31, 23));
    Objects_o21_pushButton->setCheckable(true);
    Objects_o25_pushButton = new QPushButton(Objects_groupBox);
    Objects_o25_pushButton->setObjectName(QString::fromUtf8("Objects_o25_pushButton"));
    Objects_o25_pushButton->setGeometry(QRect(120, 140, 31, 23));
    Objects_o25_pushButton->setCheckable(true);
    Objects_o23_pushButton = new QPushButton(Objects_groupBox);
    Objects_o23_pushButton->setObjectName(QString::fromUtf8("Objects_o23_pushButton"));
    Objects_o23_pushButton->setGeometry(QRect(60, 140, 31, 23));
    Objects_o23_pushButton->setCheckable(true);
    Objects_o24_pushButton = new QPushButton(Objects_groupBox);
    Objects_o24_pushButton->setObjectName(QString::fromUtf8("Objects_o24_pushButton"));
    Objects_o24_pushButton->setGeometry(QRect(90, 140, 31, 23));
    Objects_o24_pushButton->setCheckable(true);
    Objects_o22_pushButton = new QPushButton(Objects_groupBox);
    Objects_o22_pushButton->setObjectName(QString::fromUtf8("Objects_o22_pushButton"));
    Objects_o22_pushButton->setGeometry(QRect(30, 140, 31, 23));
    Objects_o22_pushButton->setCheckable(true);
    Objects_o26_pushButton = new QPushButton(Objects_groupBox);
    Objects_o26_pushButton->setObjectName(QString::fromUtf8("Objects_o26_pushButton"));
    Objects_o26_pushButton->setGeometry(QRect(0, 170, 31, 23));
    Objects_o26_pushButton->setCheckable(true);
    Objects_o30_pushButton = new QPushButton(Objects_groupBox);
    Objects_o30_pushButton->setObjectName(QString::fromUtf8("Objects_o30_pushButton"));
    Objects_o30_pushButton->setGeometry(QRect(120, 170, 31, 23));
    Objects_o30_pushButton->setCheckable(true);
    Objects_o28_pushButton = new QPushButton(Objects_groupBox);
    Objects_o28_pushButton->setObjectName(QString::fromUtf8("Objects_o28_pushButton"));
    Objects_o28_pushButton->setGeometry(QRect(60, 170, 31, 23));
    Objects_o28_pushButton->setCheckable(true);
    Objects_o29_pushButton = new QPushButton(Objects_groupBox);
    Objects_o29_pushButton->setObjectName(QString::fromUtf8("Objects_o29_pushButton"));
    Objects_o29_pushButton->setGeometry(QRect(90, 170, 31, 23));
    Objects_o29_pushButton->setCheckable(true);
    Objects_o27_pushButton = new QPushButton(Objects_groupBox);
    Objects_o27_pushButton->setObjectName(QString::fromUtf8("Objects_o27_pushButton"));
    Objects_o27_pushButton->setGeometry(QRect(30, 170, 31, 23));
    Objects_o27_pushButton->setCheckable(true);
    Objects_o31_pushButton = new QPushButton(Objects_groupBox);
    Objects_o31_pushButton->setObjectName(QString::fromUtf8("Objects_o31_pushButton"));
    Objects_o31_pushButton->setGeometry(QRect(0, 200, 31, 23));
    Objects_o31_pushButton->setCheckable(true);
    Objects_o35_pushButton = new QPushButton(Objects_groupBox);
    Objects_o35_pushButton->setObjectName(QString::fromUtf8("Objects_o35_pushButton"));
    Objects_o35_pushButton->setGeometry(QRect(120, 200, 31, 23));
    Objects_o35_pushButton->setCheckable(true);
    Objects_o33_pushButton = new QPushButton(Objects_groupBox);
    Objects_o33_pushButton->setObjectName(QString::fromUtf8("Objects_o33_pushButton"));
    Objects_o33_pushButton->setGeometry(QRect(60, 200, 31, 23));
    Objects_o33_pushButton->setCheckable(true);
    Objects_o34_pushButton = new QPushButton(Objects_groupBox);
    Objects_o34_pushButton->setObjectName(QString::fromUtf8("Objects_o34_pushButton"));
    Objects_o34_pushButton->setGeometry(QRect(90, 200, 31, 23));
    Objects_o34_pushButton->setCheckable(true);
    Objects_o32_pushButton = new QPushButton(Objects_groupBox);
    Objects_o32_pushButton->setObjectName(QString::fromUtf8("Objects_o32_pushButton"));
    Objects_o32_pushButton->setGeometry(QRect(30, 200, 31, 23));
    Objects_o32_pushButton->setCheckable(true);
*/
    hboxLayout->addWidget(Objects_groupBox);

    line_2 = new QFrame(centralwidget);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setFrameShape(QFrame::VLine);
    line_2->setFrameShadow(QFrame::Sunken);

    hboxLayout->addWidget(line_2);

    widget_GL = new QWidget(centralwidget);
    widget_GL->setObjectName(QString::fromUtf8("widget_GL"));

    hboxLayout->addWidget(widget_GL);

    line = new QFrame(centralwidget);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    hboxLayout->addWidget(line);

    Parameters_groupBox = new QGroupBox(centralwidget);
    Parameters_groupBox->setObjectName(QString::fromUtf8("Parameters_groupBox"));
    QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(Parameters_groupBox->sizePolicy().hasHeightForWidth());
    Parameters_groupBox->setSizePolicy(sizePolicy1);
    Parameters_groupBox->setMinimumSize(QSize(141, 141));

    hboxLayout->addWidget(Parameters_groupBox);

    Assets->setCentralWidget(centralwidget);
    menubar = new QMenuBar(Assets);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 781, 21));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuExport = new QMenu(menuFile);
    menuExport->setObjectName(QString::fromUtf8("menuExport"));
    Assets->setMenuBar(menubar);

    menubar->addAction(menuFile->menuAction());
    menuFile->addAction(actionNew_Scene);
    menuFile->addAction(menuExport->menuAction());
    menuFile->addAction(actionLoad_ma);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);
    menuExport->addAction(actionExport_obj);
    menuExport->addAction(actionExport_ma);

    retranslateUi(Assets);

    QMetaObject::connectSlotsByName(Assets);
    } // setupUi

    void retranslateUi(QMainWindow *Assets)
    {
    Assets->setWindowTitle(QApplication::translate("Assets", "Projet QT", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("Assets", "Exit", 0, QApplication::UnicodeUTF8));
    actionNew_Scene->setText(QApplication::translate("Assets", "New Scene", 0, QApplication::UnicodeUTF8));
    actionExport_obj->setText(QApplication::translate("Assets", "OBJ File (.obj)", 0, QApplication::UnicodeUTF8));
    actionExport_ma->setText(QApplication::translate("Assets", "Maya File (.ma)", 0, QApplication::UnicodeUTF8));
    actionLoad_ma->setText(QApplication::translate("Assets", "Load", 0, QApplication::UnicodeUTF8));
    Objects_groupBox->setTitle(QApplication::translate("Assets", "Objects", 0, QApplication::UnicodeUTF8));

    Objects_pushButton_void0->setText(QApplication::translate("Assets", "Cube", 0, QApplication::UnicodeUTF8));
    Objects_pushButton_void1->setText(QApplication::translate("Assets", "Truc", 0, QApplication::UnicodeUTF8));
    Objects_pushButton_terGen->setText(QApplication::translate("Assets", "Generate terrain", 0, QApplication::UnicodeUTF8));
    Objects_pushButton_terRender->setText(QApplication::translate("Assets", "Render terrain", 0, QApplication::UnicodeUTF8));
    Objects_pushButton_terWater->setText(QApplication::translate("Assets", "Erosion simulation", 0, QApplication::UnicodeUTF8));

    /*Objects_o05_pushButton->setText(QApplication::translate("Assets", "o5", 0, QApplication::UnicodeUTF8));
    Objects_o03_pushButton->setText(QApplication::translate("Assets", "o3", 0, QApplication::UnicodeUTF8));
    Objects_o06_pushButton->setText(QApplication::translate("Assets", "o6", 0, QApplication::UnicodeUTF8));
    Objects_o10_pushButton->setText(QApplication::translate("Assets", "o10", 0, QApplication::UnicodeUTF8));
    Objects_o08_pushButton->setText(QApplication::translate("Assets", "o8", 0, QApplication::UnicodeUTF8));
    Objects_o09_pushButton->setText(QApplication::translate("Assets", "o9", 0, QApplication::UnicodeUTF8));
    Objects_o07_pushButton->setText(QApplication::translate("Assets", "o7", 0, QApplication::UnicodeUTF8));
    Objects_o11_pushButton->setText(QApplication::translate("Assets", "o11", 0, QApplication::UnicodeUTF8));
    Objects_o15_pushButton->setText(QApplication::translate("Assets", "o15", 0, QApplication::UnicodeUTF8));
    Objects_o13_pushButton->setText(QApplication::translate("Assets", "o13", 0, QApplication::UnicodeUTF8));
    Objects_o14_pushButton->setText(QApplication::translate("Assets", "o14", 0, QApplication::UnicodeUTF8));
    Objects_o12_pushButton->setText(QApplication::translate("Assets", "o12", 0, QApplication::UnicodeUTF8));
    Objects_o16_pushButton->setText(QApplication::translate("Assets", "o16", 0, QApplication::UnicodeUTF8));
    Objects_o20_pushButton->setText(QApplication::translate("Assets", "o20", 0, QApplication::UnicodeUTF8));
    Objects_o18_pushButton->setText(QApplication::translate("Assets", "o18", 0, QApplication::UnicodeUTF8));
    Objects_o19_pushButton->setText(QApplication::translate("Assets", "o19", 0, QApplication::UnicodeUTF8));
    Objects_o17_pushButton->setText(QApplication::translate("Assets", "o17", 0, QApplication::UnicodeUTF8));
    Objects_o21_pushButton->setText(QApplication::translate("Assets", "o21", 0, QApplication::UnicodeUTF8));
    Objects_o25_pushButton->setText(QApplication::translate("Assets", "o25", 0, QApplication::UnicodeUTF8));
    Objects_o23_pushButton->setText(QApplication::translate("Assets", "o23", 0, QApplication::UnicodeUTF8));
    Objects_o24_pushButton->setText(QApplication::translate("Assets", "o24", 0, QApplication::UnicodeUTF8));
    Objects_o22_pushButton->setText(QApplication::translate("Assets", "o22", 0, QApplication::UnicodeUTF8));
    Objects_o26_pushButton->setText(QApplication::translate("Assets", "o26", 0, QApplication::UnicodeUTF8));
    Objects_o30_pushButton->setText(QApplication::translate("Assets", "o30", 0, QApplication::UnicodeUTF8));
    Objects_o28_pushButton->setText(QApplication::translate("Assets", "o28", 0, QApplication::UnicodeUTF8));
    Objects_o29_pushButton->setText(QApplication::translate("Assets", "o29", 0, QApplication::UnicodeUTF8));
    Objects_o27_pushButton->setText(QApplication::translate("Assets", "o27", 0, QApplication::UnicodeUTF8));
    Objects_o31_pushButton->setText(QApplication::translate("Assets", "o31", 0, QApplication::UnicodeUTF8));
    Objects_o35_pushButton->setText(QApplication::translate("Assets", "o35", 0, QApplication::UnicodeUTF8));
    Objects_o33_pushButton->setText(QApplication::translate("Assets", "o33", 0, QApplication::UnicodeUTF8));
    Objects_o34_pushButton->setText(QApplication::translate("Assets", "o34", 0, QApplication::UnicodeUTF8));
    Objects_o32_pushButton->setText(QApplication::translate("Assets", "o32", 0, QApplication::UnicodeUTF8));*/
    Parameters_groupBox->setTitle(QApplication::translate("Assets", "Parameters", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("Assets", "File", 0, QApplication::UnicodeUTF8));
    menuExport->setTitle(QApplication::translate("Assets", "Export", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Assets: public Ui_Assets {};
} // namespace Ui

#endif // MAINWINDOWPROJETQT_H
