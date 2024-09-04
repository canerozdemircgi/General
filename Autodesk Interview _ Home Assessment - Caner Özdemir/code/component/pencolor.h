#ifndef BRUSHCOLORBUTTON_H
#define BRUSHCOLORBUTTON_H

#include "paintarea.h"

#include <QPushButton>

class PenColor : public QPushButton
{
	Q_OBJECT

public:
	explicit PenColor(QWidget *parent = nullptr);
	void init(PaintArea *paintArea);

	void setColor(const QColor &color);

private:
	PaintArea *paintArea;

	QColor color;

	void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // BRUSHCOLORBUTTON_H