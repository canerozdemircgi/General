#include "penopacity.h"

#include "data/configuration.h"

PenOpacity::PenOpacity(QWidget *parent)
	: QSpinBox(parent)
{
}

void PenOpacity::init(PaintArea *paintArea)
{
	this->paintArea = paintArea;
	connect(this, &QSpinBox::valueChanged, this, &PenOpacity::this_valueChanged);

	this->setValue(Configuration::initialToolAlpha);
}

void PenOpacity::this_valueChanged(const int value)
{
	this->paintArea->setPenAlpha(value);
}