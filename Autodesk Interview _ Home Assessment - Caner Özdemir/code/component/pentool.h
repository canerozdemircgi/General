#ifndef PENTOOL_H
#define PENTOOL_H

#include "paintarea.h"

#include <QPushButton>

class PenTool : public QPushButton
{
	Q_OBJECT

public:
	explicit PenTool(QWidget *parent = nullptr);
	void init(PaintArea *paintArea);

private:
	PaintArea *paintArea;

private slots:
	void this_toggled(const bool checked);
};

#endif // PENTOOL_H