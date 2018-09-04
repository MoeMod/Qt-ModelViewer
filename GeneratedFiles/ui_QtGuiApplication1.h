/********************************************************************************
** Form generated from reading UI file 'QtGuiApplication1.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIAPPLICATION1_H
#define UI_QTGUIAPPLICATION1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_QtGuiApplication1Class
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClear;
    QAction *actionLight;
    QAction *actionShow_Normals;
    QAction *actionNormal_Map_Color;
    QAction *actionSnapShot;
    MyOpenGLWidget *centralWidget;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *QtGuiApplication1Class)
    {
        if (QtGuiApplication1Class->objectName().isEmpty())
            QtGuiApplication1Class->setObjectName(QStringLiteral("QtGuiApplication1Class"));
        QtGuiApplication1Class->resize(600, 480);
        QtGuiApplication1Class->setMinimumSize(QSize(600, 480));
        actionOpen = new QAction(QtGuiApplication1Class);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/QtGuiApplication1/Resources/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSave = new QAction(QtGuiApplication1Class);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/QtGuiApplication1/Resources/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionClear = new QAction(QtGuiApplication1Class);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/QtGuiApplication1/Resources/icons/eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon2);
        actionLight = new QAction(QtGuiApplication1Class);
        actionLight->setObjectName(QStringLiteral("actionLight"));
        actionLight->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/QtGuiApplication1/Resources/icons/lighton.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLight->setIcon(icon3);
        actionShow_Normals = new QAction(QtGuiApplication1Class);
        actionShow_Normals->setObjectName(QStringLiteral("actionShow_Normals"));
        actionShow_Normals->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/QtGuiApplication1/Resources/icons/heyzap_128x128-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShow_Normals->setIcon(icon4);
        actionNormal_Map_Color = new QAction(QtGuiApplication1Class);
        actionNormal_Map_Color->setObjectName(QStringLiteral("actionNormal_Map_Color"));
        actionNormal_Map_Color->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/QtGuiApplication1/Resources/icons/rgbt.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNormal_Map_Color->setIcon(icon5);
        actionSnapShot = new QAction(QtGuiApplication1Class);
        actionSnapShot->setObjectName(QStringLiteral("actionSnapShot"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/QtGuiApplication1/Resources/icons/125.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSnapShot->setIcon(icon6);
        centralWidget = new MyOpenGLWidget(QtGuiApplication1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtGuiApplication1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtGuiApplication1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtGuiApplication1Class->setStatusBar(statusBar);
        toolBar = new QToolBar(QtGuiApplication1Class);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        QtGuiApplication1Class->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addSeparator();
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionClear);
        toolBar->addSeparator();
        toolBar->addAction(actionLight);
        toolBar->addAction(actionShow_Normals);
        toolBar->addAction(actionNormal_Map_Color);
        toolBar->addSeparator();
        toolBar->addAction(actionSnapShot);

        retranslateUi(QtGuiApplication1Class);
        QObject::connect(actionClear, SIGNAL(triggered()), centralWidget, SLOT(update()));
        QObject::connect(actionLight, SIGNAL(toggled(bool)), centralWidget, SLOT(setLight(bool)));
        QObject::connect(actionShow_Normals, SIGNAL(toggled(bool)), centralWidget, SLOT(setShowNormals(bool)));
        QObject::connect(actionNormal_Map_Color, SIGNAL(toggled(bool)), centralWidget, SLOT(setNormalMapColor(bool)));
        QObject::connect(actionSnapShot, SIGNAL(triggered()), centralWidget, SLOT(onActionSnapshot()));
        QObject::connect(QtGuiApplication1Class, SIGNAL(updateStatusBar(QString)), statusBar, SLOT(showMessage(QString)));

        QMetaObject::connectSlotsByName(QtGuiApplication1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiApplication1Class)
    {
        QtGuiApplication1Class->setWindowTitle(QApplication::translate("QtGuiApplication1Class", "QtGuiApplication1", nullptr));
        actionOpen->setText(QApplication::translate("QtGuiApplication1Class", "Open", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("QtGuiApplication1Class", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("QtGuiApplication1Class", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("QtGuiApplication1Class", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionClear->setText(QApplication::translate("QtGuiApplication1Class", "Clear", nullptr));
        actionLight->setText(QApplication::translate("QtGuiApplication1Class", "Light", nullptr));
        actionShow_Normals->setText(QApplication::translate("QtGuiApplication1Class", "Show Normals", nullptr));
        actionNormal_Map_Color->setText(QApplication::translate("QtGuiApplication1Class", "Normal Map Color", nullptr));
        actionSnapShot->setText(QApplication::translate("QtGuiApplication1Class", "SnapShot", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSnapShot->setShortcut(QApplication::translate("QtGuiApplication1Class", "F5", nullptr));
#endif // QT_NO_SHORTCUT
        toolBar->setWindowTitle(QApplication::translate("QtGuiApplication1Class", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiApplication1Class: public Ui_QtGuiApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPPLICATION1_H
