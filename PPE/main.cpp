#include "PPE.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PPE w;
	w.show();
	return a.exec();
}
