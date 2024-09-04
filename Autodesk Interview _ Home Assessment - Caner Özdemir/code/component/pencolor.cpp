#include "pencolor.h"

#include "data/configuration.h"

#include <QColorDialog>

PenColor::PenColor(QWidget *parent)
	: QPushButton(parent)
{
}

void PenColor::init(PaintArea *paintArea)
{
	this->paintArea = paintArea;
	this->setColor(QColor(Configuration::initialToolColor));
}

void PenColor::mouseReleaseEvent(QMouseEvent *event)
{
	const QColor color(QColorDialog::getColor(this->color, this, "Pick Color", QColorDialog::DontUseNativeDialog));
	if (color.isValid())
		this->setColor(color);
}

void PenColor::setColor(const QColor &color)
{
	this->color = color;
	this->paintArea->setPenColor(color);

	QPixmap icon(this->iconSize());
	icon.fill(color);
	this->setIcon(QIcon(icon));
}