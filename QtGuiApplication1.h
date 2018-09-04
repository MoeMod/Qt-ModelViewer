#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);

	friend class MyOpenGLWidget;

	void OnActionOpen();
	void OnActionSave();
	void OnActionClear();
	
signals:
	void updateStatusBar(QString str);

private:
	Ui::QtGuiApplication1Class ui;
};
