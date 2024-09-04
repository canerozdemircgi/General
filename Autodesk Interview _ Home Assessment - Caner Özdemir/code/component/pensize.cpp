#include "pensize.h"

#include "data/configuration.h"

PenSize::PenSize(QWidget *parent)
	: QDoubleSpinBox(parent)
{
}

void PenSize::init(PaintArea *paintArea)
{
	this->paintArea = paintArea;
	connect(this, &QDoubleSpinBox::valueChanged, this, &PenSize::this_valueChanged);

	this->setValue(Configuration::initialToolSize);
}

void PenSize::this_valueChanged(const double value)
{
	this->paintArea->setPenSize(value);
}