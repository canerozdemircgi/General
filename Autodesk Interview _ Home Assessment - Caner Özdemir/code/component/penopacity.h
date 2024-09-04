#ifndef BRUSHOPACITY_H
#define BRUSHOPACITY_H

#include "paintarea.h"

#include <QSpinBox>

class PenOpacity : public QSpinBox
{
	Q_OBJECT

public:
	explicit PenOpacity(QWidget *parent = nullptr);
	void init(PaintArea *paintArea);

private:
	PaintArea *paintArea;

private slots:
	void this_valueChanged(const int value);
};

#endif // BRUSHOPACITY_H