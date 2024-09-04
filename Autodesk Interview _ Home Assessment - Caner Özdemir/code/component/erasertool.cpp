#include "erasertool.h"

EraserTool::EraserTool(QWidget *parent)
	: QPushButton(parent)
{
	this->setCheckable(true);
}

void EraserTool::init(PaintArea *paintArea)
{
	this->paintArea = paintArea;
	connect(this, &QPushButton::toggled, this, &EraserTool::this_toggled);
}

void EraserTool::this_toggled(const bool checked)
{
	if (!checked)
		return;

	this->paintArea->setPaintTool(PaintTool::Eraser);
}