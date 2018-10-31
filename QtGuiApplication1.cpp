#include "QtGuiApplication1.h"

#include <QFileDialog.h>
#include <QMessageBox.h>

#include "MeshFile.h"
#include "main.h"
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
	QString filename = QFileDialog::getOpenFileName(this, "Load ply file", {}, tr("Model file (*.*)"));
	if(!filename.isEmpty())
	{
		try
		{
			GlobalVars().pMeshFile = std::make_unique<CMeshFile>(filename.toStdString());
			
			updateStatusBar(QString::fromStdString(MakeString("current file: ", filename.toStdString())));
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
			if (!GlobalVars().pMeshFile) throw std::runtime_error("nothing to be saved.");
			GlobalVars().pMeshFile->SaveToFile(filename.toStdString());
		}
		catch (const std::exception &e)
		{
			QMessageBox::warning(this, "Error", e.what());
		}
	}
}

void QtGuiApplication1::OnActionClear()
{
	// TO BE DONE
	
}

