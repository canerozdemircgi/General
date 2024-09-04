#ifndef ZOOM_H
#define ZOOM_H

#include "paintarea.h"

#include <QDoubleSpinBox>

class Zoom : public QDoubleSpinBox
{
	Q_OBJECT

public:
	explicit Zoom(QWidget *parent = nullptr);
	void init(PaintArea *paintArea);

private:
	PaintArea *paintArea;

private slots:
	void this_valueChanged(const double value);
};

#endif // ZOOM_H