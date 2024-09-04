#include "menubar.h"
#include "./ui_menubar.h"

#include <QFileDialog>
#include <QMessageBox>

MenuBar::MenuBar(QWidget *parent)
	: QMenuBar(parent)
	, ui(new Ui::Main_QMenuBar)
{
	this->ui->setupUi(this);
}

MenuBar::~MenuBar()
{
	delete this->ui;
}

void MenuBar::init(PaintArea *paintArea)
{
	this->paintArea = paintArea;
	connect(this->ui->Open_QAction, &QAction::triggered, this, &MenuBar::this_Open_QAction_triggered);
}

void MenuBar::this_Open_QAction_triggered()
{
	const QString fileName(QFileDialog::getOpenFileName(this->parentWidget(), "Open Image File", nullptr, "All files (*.*);;JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp);;TIFF (*.tif *.tiff)"));
	if (fileName != nullptr)
	{
		const QPixmap imageSource(fileName);
		if (imageSource.isNull())
			QMessageBox::critical(this, "Error", "The Image File Could Not Be Recognized");
		else
			this->paintArea->setImageSource(imageSource);
	}
}