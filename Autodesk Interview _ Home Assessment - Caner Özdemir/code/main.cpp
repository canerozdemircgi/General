#include "mainwindow.h"

#include "data/configuration.h"

#include <QApplication>
#include <QStyleFactory>
#include <QFile>

int main(int argc, char *argv[])
{
	const QApplication a(argc, argv);
	a.setStyle(QStyleFactory::create(Configuration::initialStyle));

	MainWindow w;

	QFile file(Configuration::initialStyleSheet);
	if (file.open(QFile::ReadOnly))
	{
		w.setStyleSheet(file.readAll());
		file.close();
	}

	w.show();

	return a.exec();
}