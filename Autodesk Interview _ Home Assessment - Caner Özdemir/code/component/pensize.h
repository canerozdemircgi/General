#ifndef BRUSHSIZE_H
#define BRUSHSIZE_H

#include "paintarea.h"

#include <QDoubleSpinBox>

class PenSize : public QDoubleSpinBox
{
	Q_OBJECT

public:
	explicit PenSize(QWidget *parent = nullptr);
	void init(PaintArea *paintArea);

private:
	PaintArea *paintArea;

private slots:
	void this_valueChanged(const double value);
};

#endif // BRUSHSIZE_H