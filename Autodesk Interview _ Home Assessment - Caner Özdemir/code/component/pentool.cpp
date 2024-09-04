#include "pentool.h"

PenTool::PenTool(QWidget *parent)
	: QPushButton(parent)
{
	this->setCheckable(true);
}

void PenTool::init(PaintArea *paintArea)
{
	this->paintArea = paintArea;
	connect(this, &QPushButton::toggled, this, &PenTool::this_toggled);
}

void PenTool::this_toggled(const bool checked)
{
	if (!checked)
		return;

	this->paintArea->setPaintTool(PaintTool::Pen);
}