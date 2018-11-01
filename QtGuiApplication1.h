#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"

class CMeshFile;

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);

	friend class MyOpenGLWidget;

	void OnActionOpen();
	void OnActionSave();
	void OnActionClear();
	void OnActionAbout();
	
signals:
	void onFileUpdated(std::shared_ptr<CMeshFile> sp);
	void updateStatusBar(QString str);

protected:
	void dragEnterEvent(QDragEnterEvent *e) override;
	void dropEvent(QDropEvent *e) override;

private:
	void OpenFile(QString str);

private:
	Ui::QtGuiApplication1Class ui;
	std::shared_ptr<CMeshFile> m_spFile;
};
