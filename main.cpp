#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>

#include "main.h"
#include "MeshFile.h"

GlobalVars_s &GlobalVars()
{
	static GlobalVars_s x;
	return x;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication1 w;
	w.show();
	return a.exec();
}
