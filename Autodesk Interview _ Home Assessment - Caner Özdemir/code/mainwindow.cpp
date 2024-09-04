#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::Main_QMainWindow)
{
	this->ui->setupUi(this);

	this->ui->Main_QMenuBar->init(this->ui->Image_QWidget);

	this->ui->Pen_QPushButton->init(this->ui->Image_QWidget);
	this->ui->Eraser_QPushButton->init(this->ui->Image_QWidget);

	this->ui->PenSize_QDoubleSpinBox->init(this->ui->Image_QWidget);
	this->ui->PenColor_QPushButton->init(this->ui->Image_QWidget);
	this->ui->PenOpacity_QSpinBox->init(this->ui->Image_QWidget);

	this->ui->Zoom_QDoubleSpinBox->init(this->ui->Image_QWidget);
}

MainWindow::~MainWindow()
{
	delete this->ui;
}