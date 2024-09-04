#include "zoom.h"

#include "data/configuration.h"

Zoom::Zoom(QWidget *parent)
	: QDoubleSpinBox(parent)
{
}

void Zoom::init(PaintArea *paintArea)
{
	this->paintArea = paintArea;
	connect(this, &QDoubleSpinBox::valueChanged, this, &Zoom::this_valueChanged);

	this->setValue(Configuration::initialImageZoom);
}

void Zoom::this_valueChanged(const double value)
{
	this->paintArea->setImageZoom(value);
}