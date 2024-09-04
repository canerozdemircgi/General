#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include "paintarea.h"

#include <QPushButton>

class EraserTool : public QPushButton
{
	Q_OBJECT

public:
	explicit EraserTool(QWidget *parent = nullptr);
	void init(PaintArea *paintArea);

private:
	PaintArea *paintArea;

private slots:
	void this_toggled(const bool checked);
};

#endif // ERASERTOOL_H