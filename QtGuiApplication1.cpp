#include "QtGuiApplication1.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QDropEvent>
#include <QDragEnterEvent>
#include <QFile>
#include <QMimeData>

#include "MeshFile.h"
#include "util.h"

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionOpen, &QAction::triggered, this, &QtGuiApplication1::OnActionOpen);
	connect(ui.actionSave, &QAction::triggered, this, &QtGuiApplication1::OnActionSave);
	connect(ui.actionClear, &QAction::triggered, this, &QtGuiApplication1::OnActionClear);
	connect(ui.actionAbout, &QAction::triggered, this, &QtGuiApplication1::OnActionAbout);
	updateStatusBar("Drag model file to open");
	setAcceptDrops(true);

}

// TODO(MoeMod) : 打开窗口里面应该加入OpenMesh所支持的扩展名限制。
void QtGuiApplication1::OnActionOpen()
{
	QString filename = QFileDialog::getOpenFileName(this, "Load model file", {}, tr(
			"Model file (*.*)"
			));
	if(!filename.isEmpty())
	{
		try
		{
			updateStatusBar(QString::fromStdString(MakeString("loading file: ", filename.toStdString())));
			OpenFile(filename);
			updateStatusBar(QString::fromStdString(MakeString("loaded file successfully: ", filename.toStdString())));
		}
		catch (const std::exception &e)
		{
			QMessageBox::warning(this, "Error", e.what());
		}
	}
}

void QtGuiApplication1::OnActionSave()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save model file", {}, tr("Model file (*.*)"));
	if (!filename.isEmpty())
	{
		try
		{
			if (!m_spFile) throw std::runtime_error("nothing to be saved.");
			m_spFile->SaveToFile(filename.toStdString());
		}
		catch (const std::exception &e)
		{
			QMessageBox::warning(this, "Error", e.what());
		}
	}
}

void QtGuiApplication1::OnActionClear()
{
	// auto freed by RAII
	emit onFileUpdated(nullptr);
	m_spFile = nullptr;
}

void QtGuiApplication1::OnActionAbout()
{
	QMessageBox::about(this, "About", "I am a simple Qt template. \n Made by MoeMod in Fall 2018.");
}


void QtGuiApplication1::dragEnterEvent(QDragEnterEvent *e)
{
	// only 1 file is accepted
	if (e->mimeData()->urls().size() != 1)
		return;

	e->acceptProposedAction();
}

void QtGuiApplication1::dropEvent(QDropEvent *e)
{
	QList<QUrl> urls = e->mimeData()->urls();
	if (urls.isEmpty())
		return;

	QString filename = urls.first().toLocalFile();

	if (filename.isEmpty())
		return;

	try
	{
		updateStatusBar(QString::fromStdString(MakeString("loading file: ", filename.toStdString())));
		OpenFile(filename);
		updateStatusBar(QString::fromStdString(MakeString("loaded file successfully: ", filename.toStdString())));
	}
	catch (const std::exception & e)
	{
		updateStatusBar(QString::fromStdString(MakeString("Error: ", e.what())));
	}
}

void QtGuiApplication1::OpenFile(QString filename)
{
	auto sp = std::make_shared<CMeshFile>(filename.toStdString());

	emit onFileUpdated(sp);

	m_spFile.swap(sp);
}