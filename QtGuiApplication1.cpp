#include "QtGuiApplication1.h"

#include <QFileDialog.h>
#include <QMessageBox.h>

#include "PointManager.h"
#include "util.h"

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionOpen, &QAction::triggered, this, &QtGuiApplication1::OnActionOpen);
	connect(ui.actionSave, &QAction::triggered, this, &QtGuiApplication1::OnActionSave);
	connect(ui.actionClear, &QAction::triggered, this, &QtGuiApplication1::OnActionClear);
	updateStatusBar("No file Loaded");
}

void QtGuiApplication1::OnActionOpen()
{
	QString filename = QFileDialog::getOpenFileName(this, "Load ply file", {}, tr("PLY file (*.ply)"));
	if(!filename.isEmpty())
	{
		try
		{
			PointManager().LoadFromFile(filename.toStdWString());
			
			updateStatusBar(QString::fromStdString(MakeString("Points Count:", PointManager().size())));
		}
		catch (const std::exception &e)
		{
			QMessageBox::warning(this, "Error", e.what());
		}
	}
}

void QtGuiApplication1::OnActionSave()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save ply file", {}, tr("PLY file (*.ply)"));
	if (!filename.isEmpty())
	{
		try
		{
			PointManager().SaveToFile(filename.toStdWString());
		}
		catch (const std::exception &e)
		{
			QMessageBox::warning(this, "Error", e.what());
		}
	}
}

void QtGuiApplication1::OnActionClear()
{
	PointManager().clear();
	
}

